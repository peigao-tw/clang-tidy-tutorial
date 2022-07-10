#include <iostream>
#include "use_override/Base.h"
#include "use_override/Derived.h"

int main()
{
	std::cout << "hello world" << std::endl;

	Base base;
	Derived derived;

	base.Reimplement(1);
	derived.Reimplement(1);

	return 0;
}
