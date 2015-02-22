#pragma once

#include "vector.h"


namespace MOSST {


class String : Vector<char> {
	public:
		String(void);
		String(const char* data);
		virtual ~String(void);

		int get_size(void) const override;

		String operator+(const String& other);

		String& operator+=(const char* other);
		String& operator+=(const String& other);

		const char* c_str(void) const;
};


}