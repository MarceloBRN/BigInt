#include <iostream>
#include <ctime>
#include "BigInt.h"

int main() {

	integer::BigInt incpos1 = BIGINT(-497287433304709813274918274927491349824712);
	incpos1++;
	if (incpos1.to_string() != "-497287433304709813274918274927491349824711") {
		std::cout << "(WRONG)";
	}
	std::cout << "++(pos): " << incpos1 << std::endl;

	incpos1 = BIGINT(39475353445876458326598218274927491349824719);
	incpos1++;
	if (incpos1.to_string() != "39475353445876458326598218274927491349824720") {
		std::cout << "(WRONG)";
	}
	std::cout << "++(pos): " << incpos1 << std::endl;

	incpos1 = BIGINT(0);
	incpos1++;
	if (incpos1.to_string() != "1") {
		std::cout << "(WRONG)";
	}
	std::cout << "++(pos): " << incpos1 << std::endl;

	incpos1 = BIGINT(1);
	incpos1++;
	if (incpos1.to_string() != "2") {
		std::cout << "(WRONG)";
	}
	std::cout << "++(pos): " << incpos1 << std::endl;

	incpos1 = BIGINT(-1);
	incpos1++;
	if (incpos1.to_string() != "0") {
		std::cout << "(WRONG)";
	}
	std::cout << "++(pos): " << incpos1 << std::endl;

	return 0;
}