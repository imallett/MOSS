#pragma once

#include "../includes.h"


namespace MOSS { namespace Serial {


//http://wiki.osdev.org/Serial_Ports

void init(void);

void write(uint8_t value);

uint8_t read(void);


}}