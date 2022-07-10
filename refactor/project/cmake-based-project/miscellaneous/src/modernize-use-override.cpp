#include "use_override/Base.h"
#include "use_override/Derived.h"
#include <iostream>

void Base::Reimplement(int a)
{
	std::cout << "Base::Reimplement" << std::endl;
}

void Derived::Reimplement(int a)
{
	std::cout << "Derived::Reimplement" << std::endl;
}
