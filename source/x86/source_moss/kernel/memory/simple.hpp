#pragma once

#include "../../includes.hpp"


namespace MOSS {
	namespace Boot {
		class multiboot_info_t;
		class multiboot_memory_map_t;
	}
namespace Memory {


class Block;
class BlockHeader final { public:
	bool allocated;
	Block* prev;
	Block* next;
};
class Block final { public:
	BlockHeader header;
	unsigned int first_data;

	uint64_t get_size(void) const;

	void print(void) const;
};

class BlockGRUB final {
	public:
		unsigned int record_size;
		uint64_t start;
		uint64_t size;
		unsigned int type;

		inline BlockGRUB(void) = default;
		explicit BlockGRUB(BlockGRUB const& block);
		explicit BlockGRUB(Boot::multiboot_memory_map_t* mmap);
		inline ~BlockGRUB(void) = default;

		void print(void) const;
};

class MemoryManager final {
	private:
		uint64_t start; //inclusive
		uint64_t   end; //exclusive

	public:
		explicit MemoryManager(Boot::multiboot_info_t const* mbi);
		inline ~MemoryManager(void) = default;

		void* malloc(size_t size);
		void free(void* ptr);

		void print(void) const;
};


}}
