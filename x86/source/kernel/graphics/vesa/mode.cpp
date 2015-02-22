#include "mode.h"

#include "../../../mossc/cstring"
#include "../../../mossc/cstdio"
#include "../../interrupt/int32.h"
#include "../../text_mode_terminal.h"


namespace MOSS { namespace Graphics { namespace VESA {


Mode::Mode(uint16_t index) : index(index) {
	MODE_INFO* info2 = (MODE_INFO*)(0x500);

	MOSSC::memset(info2,0,sizeof(MODE_INFO));
	int ptr = (int)(info2);

	Interrupts::regs16_t regs;
	regs.ax = 0x4F01;
	regs.di = ptr & 0xF;
	regs.es = (ptr>>4) & 0xFFFF;
	regs.cx = index;
	Interrupts::int32(0x10,&regs);

	valid = regs.ax==0x004F;

	MOSSC::memcpy(&info,info2,sizeof(MODE_INFO));
}
Mode::~Mode(void) {}

void Mode::get_printable(char* buffer) const {
	MOSSC::sprintf(buffer,"Mode %u: %ux%u@%ubpp", index, info.XResolution,info.YResolution,info.BitsPerPixel);
}
void Mode::print(Terminal::TextModeTerminal* terminal) const {
	char buffer[256];
	get_printable(buffer);
	terminal->write(buffer);
}


}}}