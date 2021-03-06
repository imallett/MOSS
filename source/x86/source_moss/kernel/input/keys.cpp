#include "keys.hpp"

#include "../../mossc/cstring"
#include "../../includes.hpp"

#include "../input/devices/controller_ps2.hpp"
#include "../input/devices/interface_keyboard_ps2.hpp"
#include "../kernel.hpp"


namespace MOSS { namespace Input { namespace Keys {


bool is_printable(Codes::MossKey key) {
	switch (key) {
		#define PRINTABLE(NAME,SHIFT_NAME, DESC,SHIFT_DESC, SC) case Codes::KEY_##NAME: return MOSSC::strlen(DESC)==1;
		MOSS_KEY_MACRO(PRINTABLE)
		#undef MOSS_KEYS
		case Codes::KEY_INVALID: return false;
	}
	return false;
}

char const* get_printable(Codes::MossKey key) {
	Devices::InterfaceDevicePS2Keyboard* keyboard = static_cast<Devices::InterfaceDevicePS2Keyboard*>(kernel->controller_ps2->device0); //TODO: kinda blecherous
	assert_term(keyboard!=nullptr,"Cannot convert to a printable value; keyboard does not exist yet!");
	switch (key) {
		#define CASE_STRING(NAME,SHIFT_NAME, DESC,SHIFT_DESC, SC)\
			case SC:\
				if (keyboard->get_shift_state()) {\
					return SHIFT_DESC;\
				} else {\
					return       DESC;\
				}
		MOSS_KEY_MACRO(CASE_STRING)
		case Codes::KEY_INVALID: return "[INVALID]";
		#undef CASE_STRING
	}
	return "[UNKOWN]";
}


}}}
