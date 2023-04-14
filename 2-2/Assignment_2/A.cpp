#include "A.h"
#include <iostream>

A::A(double a) {
	this->setValue(a);
	cout << "Class A is created with " << a << endl;
}

void A::setValue(double input) {
	this->a = input;
}

A::~A() {
	cout<<"Class A is destroyed with "<<this->a<<endl;
}