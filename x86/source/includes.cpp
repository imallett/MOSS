#include "includes.h"

#include "kernel/text_mode_terminal.h"


namespace MOSS {
	#ifdef MOSS_DEBUG
	void moss_assert(bool condition, const char* failure_message) {
		if (!condition) {
			Kernel::terminal->write(failure_message);
			LOOP: goto LOOP;
		}
	}
	#endif
}