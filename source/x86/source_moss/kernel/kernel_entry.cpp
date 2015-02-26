#include "kernel_entry.h"

#include "../mossc/_misc.h"

#include "disk/ata/controller.h"
#include "disk/filesystems/ext2/ext2.h"
#include "disk/filesystems/fat/fat.h"
#include "disk/disk.h"

#include "boot/multiboot.h"

#include "graphics/gui/manager.h"
#include "graphics/vesa/controller.h"

#include "input/devices/controller_ps2.h"

#include "interrupt/idt.h"
#include "interrupt/irq_isr.h"
#include "interrupt/misc.h"
#include "interrupt/pic.h"

#include "memory/gdt.h"
#include "memory/simple.h"

#include "text_mode_terminal.h"

#include "kernel.h"


namespace MOSS {


extern Kernel* kernel;

extern "C" void kernel_entry(unsigned long magic, unsigned long addr) {
	//Allocate the kernel object on the stack
	Kernel kernel2;
	kernel = &kernel2;

	//The text mode terminal
	Terminal::TextModeTerminal terminal;
	kernel->terminal = &terminal;
	terminal.set_color_text(Terminal::TextModeTerminal::COLOR_RED);

	//Check boot went okay
	Boot::multiboot_info_t* mbi = reinterpret_cast<Boot::multiboot_info_t*>(addr);
	assert_term(magic==MULTIBOOT_BOOTLOADER_MAGIC,"Invalid multiboot magic number!\n");
	assert_term(mbi->flags&(1<<0),"Invalid GRUB memory flag!\n");
	assert_term(mbi->flags&(1<<6),"Invalid GRUB memory map!\n");

	//Setup dynamic memory (some of the setup, i.e. PS/2, requires it, so do it first)
	Memory::MemoryManager memory(mbi);
	kernel->memory = &memory;

	//The GRUB documentation http://www.gnu.org/software/grub/manual/multiboot/multiboot.html implies
	//	that interrupts are already disabled.  That's good, because the following allows us to deal with
	//	them for the first time.
	//terminal.write("Forcing disable hardware interrupts\n");
	//MOSS::Interrupts::disable_hw_int();

	#if 1 //Set up memory segments
		kernel->write("Loading GDT\n");
		MOSS::Memory::load_gdt();
		kernel->write("Reloading segments\n\n");
		MOSS::Memory::reload_segments();
	#endif
	#if 1 //Set up interrupts
		kernel->write("Loading IDT\n");
		MOSS::Interrupts::load_idt();
		kernel->write("Setting up IRQs\n");
		MOSS::Interrupts::init_irqs();
		kernel->write("Remapping PIC\n\n");
		MOSS::Interrupts::PIC::remap(32,40);
	#endif
	#if 0 //Set up PS/2 devices
		kernel->write("Setting up PS/2 controller\n\n");
		Input::Devices::ControllerPS2 controller_ps2;
		kernel->controller_ps2 = &controller_ps2;
	#endif
	#if 1 //Set up ATA and hard disk
		kernel->write("Setting up ATA controller\n");
		Disk::ATA::Controller controller_ata;
		kernel->controller_ata = &controller_ata;
		controller_ata.print(1);
	#endif
	#if 1 //Set up FPU
		//TODO: assumes it exists and is on-board the CPU
		kernel->write("Setting up FPU\n\n");
		__asm__ __volatile__("fninit");
	#endif
	#if 1 //Enable hardware interrupts
		kernel->write("Enabling hardware interrupts\n");
		MOSS::Interrupts::enable_hw_int();
	#endif
	#if 1 //Set up HDD representation (note must come after ATA and enable interrupts)
		kernel->write("Setting up hard disk drive\n");
		Disk::HardDiskDrive disk(&controller_ata, 0,0);
		kernel->disk = &disk;
		disk.print(1);
	#endif
	#if 1 //Set up file system representation (note must come after ATA, enable interrupts, and HDD representation)
		kernel->write("Setting up file system\n");
		Disk::FileSystem::FileSystemFAT filesystem(disk.partitions[0]);
		kernel->filesystem = &filesystem;
		kernel->filesystem->print();
		while (true);
	#endif

	/*kernel->write("float a\n");
	float a = 1.0f;
	kernel->write("float b\n");
	float b = 255.0f;
	kernel->write("float c\n");
	float c = a / b;
	kernel->write("float success!\n"); while (true);*/

	/*terminal->write("Test firing . . .\n");
	MOSS::Interrupts::fire_int13h();
	terminal->write("fired!\n");*/

	//The VESA controller needs access to lower memory (less than 1MiB) load information.  Therefore, it
	//	needs to come after all of the information we want is out of the bootloader.
	Graphics::VESA::Controller graphics;
	kernel->graphics = &graphics;

	//Set up the GUI manager
	Graphics::GUI::Manager gui;
	kernel->gui = &gui;

	#if 0
		uint8_t buffer[512];
		kernel->write("Reading bootsector from HDD . . .\n");
		kernel->controller_ata->read_sectors(buffer, 0,1);
		kernel->write("Doing it again . . .\n");
		kernel->controller_ata->read_sectors(buffer, 0,1);
		#if 1
			kernel->write("Outputting data . . .\n");
			//for (int i=0;i<512;++i) kernel->write("%X ",static_cast<int>(buffer[i]));
			//for (int i=0;i<512;++i) kernel->write("%d ",static_cast<int>(buffer[i]));
			kernel->write("Bytes at index 510, 511: 0x%X 0x%X\n",buffer[510],buffer[511]); //For MBR should be 0x55 0xAA
		#endif
		kernel->write("Complete!\n"); while (true);
	#endif

	kernel->init();
	kernel->main();
}


}
