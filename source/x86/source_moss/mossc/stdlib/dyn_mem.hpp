#pragma once

#include "../../includes.hpp"


namespace MOSSC {


void* calloc(size_t num, size_t size);
void* malloc(size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);


}


//TODO: these don't go here!
void* operator new  (size_t size);
void* operator new[](size_t size);
void operator delete  (void* p);
void operator delete[](void* p);
