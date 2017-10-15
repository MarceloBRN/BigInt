#include <iostream>
#include <ctime>
#include "BigInt.h"

int main() {
	/* SUB TEST
	*/

	bnum::BigInt sub1(BIGINT(1057409508754987827492837492834234234));
	bnum::BigInt sub2(BIGINT(3304709813274918274927491349824712));
	bnum::BigInt ressub1 = sub1 - sub2;

	if (ressub1.to_string() != "1054104798941712909217910001484409522") {
		std::cout << "(WRONG)";
	}
	std::cout << "sub: " << ressub1 << std::endl;

	sub1 = BIGINT(3304709813274918274927491349824712);
	sub2 = BIGINT(1057409508754987827492837492834234234);
	ressub1 = sub1 - sub2;

	if (ressub1.to_string() != "-1054104798941712909217910001484409522") {
		std::cout << "(WRONG)";
	}
	std::cout << "sub: " << ressub1 << std::endl;

	sub1 = BIGINT(-1057409508754987827492837492834234234);
	sub2 = BIGINT(3304709813274918274927491349824712);
	ressub1 = sub1 - sub2;

	if (ressub1.to_string() != "-1060714218568262745767764984184058946") {
		std::cout << "(WRONG)";
	}
	std::cout << "sub: " << ressub1 << std::endl;

	sub1 = BIGINT(3304709813274918274927491349824712);
	sub2 = BIGINT(-1057409508754987827492837492834234234);
	ressub1 = sub1 - sub2;

	if (ressub1.to_string() != "1060714218568262745767764984184058946") {
		std::cout << "(WRONG)";
	}
	std::cout << "sub: " << ressub1 << std::endl;

	sub1 = BIGINT(1057409508754987827492837492834234234);
	sub2 = BIGINT(-3304709813274918274927491349824712);
	ressub1 = sub1 - sub2;

	if (ressub1.to_string() != "1060714218568262745767764984184058946") {
		std::cout << "(WRONG)";
	}
	std::cout << "sub: " << ressub1 << std::endl;


	sub1 = BIGINT(-3304709813274918274927491349824712);
	sub2 = BIGINT(1057409508754987827492837492834234234);
	ressub1 = sub1 - sub2;

	if (ressub1.to_string() != "-1060714218568262745767764984184058946") {
		std::cout << "(WRONG)";
	}
	std::cout << "sub: " << ressub1 << std::endl;

	sub1 = BIGINT(0);
	sub2 = BIGINT(497287433304709813274918274927491349824712);
	ressub1 = sub1 - sub2;

	if (ressub1.to_string() != "-497287433304709813274918274927491349824712") {
		std::cout << "(WRONG)";
	}
	std::cout << "sub: " << ressub1 << std::endl;

	sub1 = BIGINT(497287433304709813274918274927491349824712);
	sub2 = BIGINT(0);
	ressub1 = sub1 - sub2;

	if (ressub1.to_string() != "497287433304709813274918274927491349824712") {
		std::cout << "(WRONG)";
	}
	std::cout << "sub: " << ressub1 << std::endl;

	sub1 = BIGINT(0);
	sub2 = BIGINT(-497287433304709813274918274927491349824712);
	ressub1 = sub1 - sub2;

	if (ressub1.to_string() != "497287433304709813274918274927491349824712") {
		std::cout << "(WRONG)";
	}
	std::cout << "sub: " << ressub1 << std::endl;

	sub1 = BIGINT(-497287433304709813274918274927491349824712);
	sub2 = BIGINT(0);
	ressub1 = sub1 - sub2;

	if (ressub1.to_string() != "-497287433304709813274918274927491349824712") {
		std::cout << "(WRONG)";
	}
	std::cout << "sub: " << ressub1 << std::endl;


	sub1 = BIGINT(1);
	sub2 = BIGINT(0);
	ressub1 = sub1 - sub2;

	if (ressub1.to_string() != "1") {
		std::cout << "(WRONG)";
	}
	std::cout << "sub: " << ressub1 << std::endl;

	sub1 = BIGINT(0);
	sub2 = BIGINT(1);
	ressub1 = sub1 - sub2;

	if (ressub1.to_string() != "-1") {
		std::cout << "(WRONG)";
	}
	std::cout << "sub: " << ressub1 << std::endl;

	sub1 = BIGINT(0);
	sub2 = BIGINT(-1);
	ressub1 = sub1 - sub2;

	if (ressub1.to_string() != "1") {
		std::cout << "(WRONG)";
	}
	std::cout << "sub: " << ressub1 << std::endl;

	sub1 = BIGINT(-1);
	sub2 = BIGINT(1);
	ressub1 = sub1 - sub2;

	if (ressub1.to_string() != "-2") {
		std::cout << "(WRONG)";
	}
	std::cout << "sub: " << ressub1 << std::endl;

	sub1 = BIGINT(1);
	sub2 = BIGINT(-1);
	ressub1 = sub1 - sub2;

	if (ressub1.to_string() != "2") {
		std::cout << "(WRONG)";
	}
	std::cout << "sub: " << ressub1 << std::endl;

	sub1 = BIGINT(-1);
	sub2 = BIGINT(-1);
	ressub1 = sub1 - sub2;

	if (ressub1.to_string() != "0") {
		std::cout << "(WRONG)";
	}
	std::cout << "sub: " << ressub1 << std::endl;

	return 0;
}