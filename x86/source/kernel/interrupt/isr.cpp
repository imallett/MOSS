#include "isr.h"

#include "../../includes.h" //For magic breakpoint

#include "../input/devices/controller_ps2.h"
#include "../kernel.h"
#include "../text_mode_terminal.h"
#include "pic.h"


namespace MOSS { namespace Interrupts {


//Exactly what the lower interrupts (0-31) are is very inconsistent accross the web, and sources frequently disagree, especially about
//certain interrupts.  The authoritative source for MOSS is taken to be the Intel Manual
//(http://www.intel.com/Assets/en_US/PDF/manual/253668.pdf, around page 233), listed along with mnemonic (if available) and type.
//Where conflicting (or extra), other sources' input is listed on tab-indented lines below.

//One alternate source: http://www.osdever.net/bkerndev/Docs/isrs.htm

//"#DE": Fault: Divide Error (generated by "div", "idiv")
//No error code
//	Also divide by 0 exception
void isr0(void) {
	Kernel::terminal->write("Handling divide-by-zero (stub)\n");
}

//"#DB": (Fault/Trap): RESERVED (for Intel use only)
//No error code
//	Debug exceptions/single step (debugger) (trap xor fault)  Error code: "None. Can be retrived from debug registers"; see http://www.brokenthorn.com/Resources/OSDev15.html.
void isr1(void) {
	ASSERT(false,"Got Intel-reserved exception 1!");
}

//     : (Interrupt): NMI Interrupt (generated by a nonmaskable, external interrupt)
//No error code
//	Intel reserved/non-maskable interrupt (NMI) pin (unclassed/trap).
void isr2(void) {
	Kernel::terminal->write("Handling NMI (stub)\n");
}

//"#BP": (Trap): Breakpoint (generated by "int $0x3")
//No error code
//	Breakpoint exception (debugger).
void isr3(void) {
	Kernel::terminal->write("Handling breakpoint (stub)\n");
}

//"#OF": (Trap): Overflow (generated by "int0")
//No error code
//	Overflow/"Into detected overflow" (trap).
void isr4(void) {
	Kernel::terminal->write("Handling overflow (stub)\n");
}

//"#BR": (Fault): BOUND Range Exceeded (generated by "bound")
//No error code
//	Bounds check/out of bound exception (trap/fault?).
void isr5(void) {
	Kernel::terminal->write("Handling bounds exceeded (stub)\n");
}

//"#UD": (Fault): Invalid Opcode (Undefined Opcode) (generated by "ud2" (Pentium Pro+) or reserved opcode)
//No error code
//	Invalid/undefined opcode exception (trap/fault?).
void isr6(void) {
	Kernel::terminal->write("Handling invalid opcode (stub)\n");
}

//"#NM": (Fault): Device Not Available (No Math Coprocessor) (generated by a floating-point or "wait"/"fwait" instruction)
//No error code
//	Coprocessor not available/device not available exception (trap/fault?).
void isr7(void) {
	Kernel::terminal->write("Handling no math (stub)\n");
}

//"#DF": (Abort): Double Fault (generated by any instruction that can generate an exception, NMI, or an interrupt)
//Has error code (always 0)
void isr8(ErrorCode/* error*/) {
	Kernel::terminal->write("Handling double-fault (stub)\n");
}

//     : (Fault): Coprocessor Segment Overrun (reserved) (generated by a floating-point instruction)
//No error code
//Processors after the i386 do not generate this exception.
//	do not use (abort?/fault).
void isr9(void) {
	ASSERT(false,"Got Intel-reserved exception 9!");
}

//"#TS": (Fault): Invalid TSS (generated by task switch or TSS access)
//Has error code
void isr10(ErrorCode/* error*/) {
	Kernel::terminal->write("Handling TSS (stub)\n");
}

//"#NP": (Fault): Segment Not Present (generated by loading segment registers or accessing system segments)
//Has error code
void isr11(ErrorCode/* error*/) {
	Kernel::terminal->write("Handling segment (stub)\n");
}

//"#SS": (Fault): Stack-Segment Fault (generated by stack operations or "ss" register loads)
//Has error code
//	Stack fault exception/stack segment overrun (fault).
void isr12(ErrorCode/* error*/) {
	Kernel::terminal->write("Handling stack (stub)\n");
}

//"#GP": (Fault): General Protection (generated by any memory reference or other protection checks)
//Has error code
//	General protection exception/general protection fault/triple fault (fault xor trap).
void isr13(ErrorCode/* error*/) {
	Kernel::terminal->write("Handling GPF (stub)\n");
}

//"#PF": (Fault): Page Fault (generated by any memory reference)
//Has error code
void isr14(ErrorCodePF/* error*/) {
	Kernel::terminal->write("Handling PF (stub)\n");
}

//     : (Unlisted): Intel reserved.  Do not use.
//No error code
//	Intel reserved?/unassigned.
void isr15(void) {
	ASSERT(false,"Got Intel-reserved exception 15!");
}

//"#MF": (Fault): x87 FPU Floating-Point Error (Math Fault) (generated by x87 FPU floating-point or "wait"/"fwait" instruction)
//No error code
//	Coprocessor error/x87 FPU floating-point error (math fault) (fault).  No error code (x87 FPU provides own error information).
void isr16(void) {
	Kernel::terminal->write("Handling FPU (stub)\n");
}

//"#AC": (Fault): Alignment Check (generated by any data reference in memory)
//Has error code (always 0)
//i486+ only
//	exception.
//	Different sources disagree about whether it has an error code.  E.g.
//		http://www.acm.uiuc.edu/sigops/roll_your_own/i386/idt.html says none
//		http://www.brokenthorn.com/Resources/OSDev15.html says there is one and it's always 0
//		The last post here: http://forum.osdev.org/viewtopic.php?f=1&t=23998&sid=98cd3b1e6b1256f0dbdb0885e84ba05f&start=15 mentions this issue.
void isr17(ErrorCode/* error*/) {
	Kernel::terminal->write("Handling alignment (stub)\n");
}

//"#MC": (Abort): Machine Check (generation method(s) unlisted)
//No error code, although Intel manual implies that there may be error codes, and if so, that they are model-dependent.
//Introduced in Pentium, improved in P6 family
//	Machine check exception (Pentium/586+ only) (abort).  No error code (MSRs provide error information).
void isr18(void) {
	Kernel::terminal->write("Handling machine check (stub)\n");
}

//"#XM": (Fault): SIMD Floating-Point Exception (generated by SSE/SSE2/SSE3 floating-point instructions).
//No error code
//Pentium III+ only
//	SIMD FPU exception (fault).
void isr19(void) {
	Kernel::terminal->write("Handling SIMD FPU (stub)\n");
}

//     : (Unlisted): Intel reserved.  Do not use.
//Whether has error code is unlisted
void isr20through31(void) {
	ASSERT(false,"Got Intel reserved interrupt [20,31]!");
}

//     : (Interrupt): User-Defined (Non-reserved) Interrupts (generated by external iterrupt or "int _" instruction)
//No error codes (either called by PICs or "int" instructions, neither of which push error codes.
//<All the rest of the ISRs>


//The first 16 are where the PICs' output is remapped, so the description for each ISR is the description of the IRQ it handles (see http://wiki.osdev.org/Interrupts)

//ISR 32 = IRQ 0 (Programmable Interrupt Timer Interrupt)
bool isr32(void) {
	//For now, we just ignore the timer
	return true;
}

//ISR 33 = IRQ 1 (Keyboard Interrupt)
bool isr33(void) {
	Kernel::terminal->write("keyboard!\n"); return true; //Will only work once because we don't read the data
	//return Kernel::controller->handle_irq_keyboard();
}

//ISR 34 = IRQ 2 (Cascade (used internally by the two PICs. never raised))
void isr34(void) {
	ASSERT(false,"Got IRQ 2!");
}

//ISR 35 = IRQ 3 (COM2 (if enabled))
void isr35(void) {
	Kernel::terminal->write("Handling IRQ 3 (stub)\n");
}

//ISR 36 = IRQ 4 (COM1 (if enabled))
void isr36(void) {
	Kernel::terminal->write("Handling IRQ 4 (stub)\n");
}

//ISR 37 = IRQ 5 (LPT2 (if enabled))
void isr37(void) {
	Kernel::terminal->write("Handling IRQ 5 (stub)\n");
}

//ISR 38 = IRQ 6 (Floppy Disk)
void isr38(void) {
	Kernel::terminal->write("Handling IRQ 6 (stub)\n");
}

//ISR 39 = IRQ 7 (LPT1 / Unreliable "spurious" interrupt (usually))
void isr39(void) {
	Kernel::terminal->write("Handling IRQ 7 (stub)\n");
}

//ISR 40 = IRQ 8 (CMOS real-time clock (if enabled))
void isr40(void) {
	Kernel::terminal->write("Handling IRQ 8 (stub)\n");
}

//ISR 41 = IRQ 9 (Free for peripherals / legacy SCSI / NIC)
void isr41(void) {
	Kernel::terminal->write("Handling IRQ 9 (stub)\n");
}

//ISR 42 = IRQ 10 (Free for peripherals / SCSI / NIC)
void isr42(void) {
	Kernel::terminal->write("Handling IRQ 10 (stub)\n");
}

//ISR 43 = IRQ 11 (Free for peripherals / SCSI / NIC)
void isr43(void) {
	Kernel::terminal->write("Handling IRQ 11 (stub)\n");
}

//ISR 44 = IRQ 12 (PS2 Mouse)
bool isr44(void) {
	//MOSS_DEBUG_BOCHSBREAK;
	//Kernel::terminal->write("Handling IRQ 12 (stub)\n"); return true;
	//return true;
	//Kernel::terminal->write("Handling IRQ 12 (mouse)\n");
	return Kernel::controller->handle_irq_mouse();
}

//ISR 45 = IRQ 13 (FPU / Coprocessor / Inter-processor)
void isr45(void) {
	Kernel::terminal->write("Handling IRQ 13 (stub)\n");
}

//ISR 46 = IRQ 14 (Primary ATA Hard Disk)
void isr46(void) {
	Kernel::terminal->write("Handling IRQ 14 (stub)\n");
}

//ISR 47 = IRQ 15 (Secondary ATA Hard Disk)
void isr47(void) {
	Kernel::terminal->write("Handling IRQ 15 (stub)\n");
}

//Unassigned [48,255]


void isr_common(State* state) {
	//MOSS_DEBUG_BOCHSBREAK;

	//See sign-extending about unsigned bytes here: http://forum.osdev.org/viewtopic.php?f=1&t=23998&sid=98cd3b1e6b1256f0dbdb0885e84ba05f&start=15.
	//Shouldn't be an issue since everything pushed is 32 bits.

	uint32_t& which = state->int_ind;

	/*Kernel::terminal->write("Received interrupt:\n");
	Kernel::terminal->write("  Interrupt index: %d\n",state->int_ind);
	Kernel::terminal->write("  Error code:      %d\n",state->err_code);
	if (state->err_code == 14) {
		Kernel::terminal->write("    Is special error code for page faults (interrupt 14):\n");
		Kernel::terminal->write("    Diagnostic output not implemented!\n"); //TODO: this
	} else {
		Kernel::terminal->write("    Is normal error code for exceptions:\n");

		union {
			uint32_t data;
			ErrorCode code;
		} convert;
		ErrorCode code = convert.code;

		if (code.external_event==0) {
			Kernel::terminal->write("      0 : ?\n");
		} else {
			Kernel::terminal->write("      1 : <External Event>\n");
		}

		if (code.descr_location==0) {
			if (code.descr_in_LDT==0) {
				Kernel::terminal->write("      0 : index into GDT\n");
			} else {
				Kernel::terminal->write("      1 : index into LDT\n");
			}
		} else {
			Kernel::terminal->write("      1 : index is into IDT\n");
		}

		Kernel::terminal->write("      %d\n",code.segement_selector_index);
	}
	Kernel::terminal->write("Delegating\n");*/

	//Kernel::terminal->write("Got interrupt %d!\n",which);

	ASSERT(which<=255,"Got interrupt that was outside the ISR table!");
	ASSERT(which<=47,"Got interrupt that was unallocated!");
	if (which>=32) { //remapped IRQ from a PIC
		bool handled = true;
		switch (which) {
			case 32: handled&=isr32(); break;
			case 33: handled&=isr33(); break;
			case 34: isr34(); break;
			case 35: isr35(); break;
			case 36: isr36(); break;
			case 37: isr37(); break;
			case 38: isr38(); break;
			case 39: isr39(); break;
			case 40: isr40(); break;
			case 41: isr41(); break;
			case 42: isr42(); break;
			case 43: isr43(); break;
			case 44: handled&=isr44(); break;
			case 45: isr45(); break;
			case 46: isr46(); break;
			case 47: isr47(); break;
		}
		if (handled) {
			//Tell the PIC that we handled the interrupt and that it can send another/reset hardware interrupt at 8259 chip
			//The only reason why we wouldn't is if the interrupt was erroneous (spurious, for example).
			Interrupts::PIC::send_EOI(which);
		}
	} else {
		ASSERT(which<=19,"Got interrupt from Intel reserved area!");
		switch (which) {
			#define ERRORCODE_ISR_CASE(I,TYPE) case I: {\
				union {\
					uint32_t data;\
					TYPE code;\
				} convert;\
				convert.data = state->err_code;\
				isr##I(convert.code);\
				break;\
			}
			case  0:  isr0(); break;
			case  1:  isr1(); break;
			case  2:  isr2(); break;
			case  3:  isr3(); break;
			case  4:  isr4(); break;
			case  5:  isr5(); break;
			case  6:  isr6(); break;
			case  7:  isr7(); break;
			ERRORCODE_ISR_CASE( 8,  ErrorCode)
			case  9:  isr9(); break;
			ERRORCODE_ISR_CASE(10,  ErrorCode)
			ERRORCODE_ISR_CASE(11,  ErrorCode)
			ERRORCODE_ISR_CASE(12,  ErrorCode)
			ERRORCODE_ISR_CASE(13,  ErrorCode)
			ERRORCODE_ISR_CASE(14,ErrorCodePF)
			case 15: isr15(); break;
			case 16: isr16(); break;
			ERRORCODE_ISR_CASE(17,  ErrorCode)
			case 18: isr18(); break;
			case 19: isr19(); break;
			#undef ERRORCODE_ISR_CASE
		}
	}
}


}}