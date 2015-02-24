#include "disk.h"

#include "../kernel.h"

#include "ata/controller.h"


namespace MOSS { namespace Disk {


void Partition:: read_sectors(uint8_t*       data_buffer, uint64_t relative_lba,int num_sectors) const {
	assert_term(
		relative_lba+num_sectors <= entry->total_sectors,
		"Read (offset %u, sectors %d) requested outside of partition (sectors %u)!",
		static_cast<uint32_t>(relative_lba), num_sectors, entry->total_sectors
	);
	drive->read_sectors(data_buffer, entry->relative_sector+relative_lba,num_sectors);
}
void Partition::write_sectors(uint8_t const* data_buffer, uint64_t relative_lba,int num_sectors)       {
	assert_term(
		relative_lba+num_sectors <= entry->total_sectors,
		"Write (offset %u, sectors %d) requested outside of partition (sectors %u)!",
		static_cast<uint32_t>(relative_lba), num_sectors, entry->total_sectors
	);
	drive->write_sectors(data_buffer, entry->relative_sector+relative_lba,num_sectors);
}

void Partition::print(int indent) const {
	for (int i=0;i<indent;++i) kernel->write("  ");
	kernel->write("%d: Partition (begin %u, sectors %u)",index,entry->relative_sector,entry->total_sectors);
	if (entry->bootable==0x80) {
		kernel->write(" (bootable)");
	}
	kernel->write("\n");
}


HardDiskDrive::HardDiskDrive(ATA::Controller* controller, int index_bus,int index_device) :
	controller(controller), index_bus(index_bus), index_device(index_device),
	_HPC(16ull), _SPT(63ull) //TODO: better calculation of these!
{
	uint8_t mbr[512];
	read_sectors(mbr, 0,1);

	for (int i=0;i<64;++i) {
		partition_table_data[i] = mbr[0x01BE + i]; //Weird GCC compilation error without space: "0x01BE+i".  TODO: look into it?
	}

	for (int i=0;i<4;++i) {
		//"If a Partition Table entry is unused, then it should be set to all 0."  So, we can just check the
		//	total number of sectors.  If it's zero, then it doesn't exist.  Makes sense.
		if (partition_table.entries[i].total_sectors == 0) {
			partitions[i] = nullptr;
		} else {
			partitions[i] = new Partition(this, partition_table.entries+i,i);
		}
	}
}
HardDiskDrive::~HardDiskDrive(void) {
	for (int i=0;i<4;++i) {
		if (partitions[i]!=nullptr) delete partitions[i];
	}
}

void HardDiskDrive:: read_sectors(uint8_t*         data_buffer,   uint64_t   absolute_lba,  int   num_sectors  ) const {
	controller->read_sectors(data_buffer, absolute_lba,num_sectors, index_bus,index_device);
}
void HardDiskDrive::write_sectors(uint8_t const* /*data_buffer*/, uint64_t /*absolute_lba*/,int /*num_sectors*/)       {
	assert_term(false,"Not implemented!");
}

uint64_t HardDiskDrive::chs_to_lba(uint64_t cylinder,uint64_t head,uint64_t sector) const {
	return (cylinder*_HPC + head)*_SPT + (sector-1ull);
}
void HardDiskDrive::lba_to_chs(uint64_t absolute_lba, uint64_t*restrict cylinder,uint64_t*restrict head,uint64_t*restrict sector) const {
	*cylinder =  absolute_lba/(_HPC*_SPT);
	*head     = (absolute_lba/_SPT)%_HPC;
	*sector   = (absolute_lba%_SPT) + 1ull;
}

void HardDiskDrive::print(int indent) const {
	for (int i=0;i<indent;++i) kernel->write("  ");
	kernel->write("Hard disk drive (on ATA bus %d, device %d); partitions:\n",index_bus,index_device);

	for (int i=0;i<4;++i) {
		if (partitions[i]==nullptr) {
			for (int i=0;i<indent+1;++i) kernel->write("  ");
			kernel->write("%d: Invalid\n",i);
		} else {
			partitions[i]->print(indent+1);
		}
	}
}


}}