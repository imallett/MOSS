#include "string.h"

#include "../mossc/cstring"


namespace MOSST {


String::String(char const* data) : Vector() {
	*this += data;
}

void String::insert_back(char const& object) /*override*/ {
	Vector::insert_back(object);

	//Push a null character onto the string, but pretend it doesn't exist.
	Vector::insert_back('\0');
	--size;
}

String String::operator+(String const& other) {
	String result(this->c_str());
	result += other.c_str();
	return result;
}

String& String::operator+=(char const* other) {
	reserve(MOSSC::strlen(other));

	int i = 0;
	LOOP:
		char c = other[i];
		if (c!='\0') {
			insert_back(c);
			++i;
			goto LOOP;
		}

	return *this;
}
String& String::operator+=(String const& other) {
	reserve(size + other.size);

	for (int i=0;i<other.size;++i) {
		insert_back(other[i]);
	}

	return *this;
}

char const* String::c_str(void) const {
	return reinterpret_cast<char const*>(_data);
}


}
