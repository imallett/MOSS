#include "controller.h"

#include "../../kernel.h"

#include "bus.h"


namespace MOSS { namespace Disk { namespace ATA {


Controller::Controller(void) {
	for (int i=0;i<4;++i) {
		buses[i] = new Bus(this, i);
		if (!buses[i]->valid) {
			delete buses[i];
			buses[i] = nullptr;
		}
	}
}
Controller::~Controller(void) {
	for (int i=0;i<4;++i) {
		if (buses[i]!=nullptr) delete buses[i];
	}
}

void Controller::read_sectors(uint8_t* data_buffer, uint64_t absolute_lba,int num_sectors, int index_bus,int index_device) const {
	assert_term(index_bus>=0&&index_bus<=1,"Invalid bus index \"%d\"!",index_bus);
	assert_term(buses[index_bus]!=nullptr,"Invalid bus %d!",index_bus);

	buses[index_bus]->command_readsectors(index_device, data_buffer, absolute_lba,num_sectors);
}

void Controller::print(int indent) const {
	for (int i=0;i<indent;++i) kernel->write("  "); kernel->write("Controller's buses:\n");
	for (int i=0;i<4;++i) {
		Bus* bus = buses[i];
		if (bus==nullptr) {
			for (int i=0;i<indent+1;++i) kernel->write("  "); kernel->write("%d: Bus nonexistent (or contains no devices)\n",i);
		} else {
			bus->print(indent+1);
		}
	}
}


}}}