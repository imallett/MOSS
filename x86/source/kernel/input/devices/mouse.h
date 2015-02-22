#pragma once
#include "../../../includes.h"

#include "device.h"


namespace MOSS { namespace Input { namespace Devices {


//http://forum.osdev.org/viewtopic.php?t=10247
//http://houbysoft.com/download/ps2mouse.html (essentially the same?)
//http://wiki.osdev.org/Mouse_Input (also see http://wiki.osdev.org/PS/2_Mouse)

class ControllerPS2;

class DevicePS2Mouse : public DevicePS2Base {
	private:
		int mouse_cycle;

		//http://www.computer-engineering.org/ps2mouse/
		union {
			struct {
				bool      button_left : 1;
				bool     button_right : 1;
				bool    button_middle : 1;
				bool           unused : 1; //Should be 1
				uint32_t  dx_sign_bit : 1; //Two's complement
				uint32_t  dy_sign_bit : 1; //Two's complement
				bool    dx_overflowed : 1;
				bool    dy_overflowed : 1;
				uint32_t           dx : 8;
				uint32_t           dy : 8;
				//See http://wiki.osdev.org/Mouse_Input#Formats_of_Optional_4th_Packet_Byte
				int32_t       dwheel : 4; //Only exists and valid for Intellimouse Extensions
				bool        button_4 : 1; //Only exists and valid for Intellimouse Extensions (and only iff initialized extra)
				bool        button_5 : 1; //Only exists and valid for Intellimouse Extensions (and only iff initialized extra)
				uint8_t mostly_zero1 : 1; //Only exists for Intellimouse Extensions
				uint8_t mostly_zero2 : 1; //Only exists for Intellimouse Extensions
			};
			struct {
				uint32_t      byte1 : 8;
				uint32_t      byte2 : 8;
				uint32_t      byte3 : 8;
				uint32_t      byte4 : 8; //Only exists for Intellimouse Extensions
			};
		} received_data;

	public:
		int x,y;
		int last_x,last_y;

		bool buttons[5];

	public:
		DevicePS2Mouse(ControllerPS2* controller);
		virtual ~DevicePS2Mouse(void);

		void reset(void);

		void  enable_streaming(void);
		void disable_streaming(void);

		void set_position(int x, int y);
		void   click(int button_index);
		void unclick(int button_index);

		void handle_irq(void) override;

		void send_command_device(uint8_t command);
		void wait_response(uint8_t wait_byte=0xFA);

	private:
		void _handle_current_packet(void);
};


}}}