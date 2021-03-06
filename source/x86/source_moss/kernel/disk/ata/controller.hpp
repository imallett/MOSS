#pragma once

#include "../../../includes.hpp"

#include "../disk.hpp"


namespace MOSS { namespace Disk { namespace ATA {


//Based on information here:
//	http://wiki.osdev.org/ATA_PIO_Mode
//		A lot of good information, although http://wiki.osdev.org/ATA_PIO_Mode#Primary.2FSecondary_Bus seems inaccurate.
//	http://forum.osdev.org/viewtopic.php?f=1&p=167798#p167798

class Bus;

class Controller final {
	public:
		Bus*restrict buses[4];

	public:
		Controller(void);
		~Controller(void);

		void read_sectors(uint8_t* data_buffer, AbsoluteLBA lba,int num_sectors, int index_bus,int index_device) const;

		void print(int level) const;
};


}}}
