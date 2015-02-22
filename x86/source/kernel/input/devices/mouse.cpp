#include "mouse.h"

#include "../../graphics/vesa.h"

#include "../../io/io.h"

#include "../../kernel.h"

#include "../mouse.h"

#include "controller_ps2.h"


namespace MOSS { namespace Input { namespace Devices {


DevicePS2Mouse::DevicePS2Mouse(ControllerPS2* controller) : DevicePS2Base(controller) {
	mouse_cycle = 0;
	x = last_x = 0;
	y = last_y = 0;

	//Enable the auxiliary mouse device
	send(0x64,0xA8);

	//Enable the interrupts
	//	Must modify the "Compaq status byte" (which is isn't actually Compaq-specific (anymore).
	//	Get it, which is done by sending the 0x20 command to the 0x64 port
	send(0x64,0x20);
	uint8_t status = recv(0x60);

	status |= 0x02; //Change flag to enable IRQ 12

	send(0x64,0x60);
	send(0x60,status);

	//Tell the mouse to use default settings
	_command(0xF6);
	recv(0x60);

	//Enable the mouse
	_command(0xF4);
	recv(0x60);
}
DevicePS2Mouse::~DevicePS2Mouse(void) {
}

void DevicePS2Mouse::handle_irq(void) /*override*/ {
	switch (mouse_cycle) {
		case 0:
			mouse_byte[0] = IO::recv<uint8_t>(0x60);
			++mouse_cycle;
			break;
		case 1:
			mouse_byte[1] = IO::recv<uint8_t>(0x60);
			++mouse_cycle;
			break;
		case 2:
			mouse_byte[2] = IO::recv<uint8_t>(0x60);
			set_position(x+mouse_byte[1],y+mouse_byte[2]);
			mouse_cycle = 0;
			break;
	}
}

void DevicePS2Mouse::set_position(int x, int y) {
	ASSERT(Kernel::graphics!=NULL,"Mouse pointer can only be operated in a graphics mode!"); //But only because we need to check where to put it.
	if      (x <                       0) x=                         0;
	else if (x>= Kernel::graphics->width) x=Kernel::graphics-> width-1;
	if      (y <                       0) y=                         0;
	else if (y>=Kernel::graphics->height) y=Kernel::graphics->height-1;

	int dx = x - this->x;
	int dy = y - this->y;
	if (dx!=0 || dy!=0) {
		last_x = this->x;
		last_y = this->y;
		this->x += dx;
		this->y += dy;
		Kernel::handle_mouse_move(Mouse::EventMove(this->x,this->y,dx,dy));
	}
}

void DevicePS2Mouse::send(uint16_t destination, uint8_t byte) const {
	controller->wait_for_inputbuffer_clear();
	IO::send<uint8_t>(destination,byte);
}
uint8_t DevicePS2Mouse::recv(uint16_t from) const {
	controller->wait_for_outputbuffer_full();
	return IO::recv<uint8_t>(from);
}

void DevicePS2Mouse::_command(uint8_t data) {
	//Wait to be able to send a command
	controller->wait_for_inputbuffer_clear();
	//Tell the mouse we are sending a command
	IO::send<uint8_t>(0x64, 0xD4);
	//Wait for the final part
	controller->wait_for_inputbuffer_clear();
	//Finally write
	IO::send<uint8_t>(0x60, data); //Yes, port 0x60
}


}}}