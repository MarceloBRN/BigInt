#include <iostream>
#include "BigInt.h"

int main() {

	bnum::BigInt sum1(BIGINT(1057409508754987827492837492834234234));
	bnum::BigInt sum2(BIGINT(3304709813274918274927491349824712));
	bnum::BigInt res1 = sum1 + sum2;

	if (res1.to_string() != "1060714218568262745767764984184058946") {
		std::cout << "(WRONG)";
	}
	std::cout << "add1: " << res1 << std::endl;

	sum1 = BIGINT(3304709813274918274927491349824712);
	sum2 = BIGINT(1057409508754987827492837492834234234);
	res1 = sum1 + sum2;

	if (res1.to_string() != "1060714218568262745767764984184058946") {
		std::cout << "(WRONG)";
	}
	std::cout << "add2: " << res1 << std::endl;

	sum1 = BIGINT(-1057409508754987827492837492834234234);
	sum2 = BIGINT(3304709813274918274927491349824712);
	res1 = sum1 + sum2;

	if (res1.to_string() != "-1054104798941712909217910001484409522") {
		std::cout << "(WRONG)";
	}
	std::cout << "add3: " << res1 << std::endl;

	sum1 = BIGINT(3304709813274918274927491349824712);
	sum2 = BIGINT(-1057409508754987827492837492834234234);
	res1 = sum1 + sum2;

	if (res1.to_string() != "-1054104798941712909217910001484409522") {
		std::cout << "(WRONG)";
	}
	std::cout << "add4: " << res1 << std::endl;

	sum1 = BIGINT(1057409508754987827492837492834234234);
	sum2 = BIGINT(-3304709813274918274927491349824712);
	res1 = sum1 + sum2;

	if (res1.to_string() != "1054104798941712909217910001484409522") {
		std::cout << "(WRONG)";
	}
	std::cout << "add5: " << res1 << std::endl;


	sum1 = BIGINT(-3304709813274918274927491349824712);
	sum2 = BIGINT(1057409508754987827492837492834234234);
	res1 = sum1 + sum2;

	if (res1.to_string() != "1054104798941712909217910001484409522") {
		std::cout << "(WRONG)";
	}
	std::cout << "add6: " << res1 << std::endl;

	sum1 = BIGINT(0);
	sum2 = BIGINT(497287433304709813274918274927491349824712);
	res1 = sum1 + sum2;

	if (res1.to_string() != "497287433304709813274918274927491349824712") {
		std::cout << "(WRONG)";
	}
	std::cout << "add7: " << res1 << std::endl;

	sum1 = BIGINT(497287433304709813274918274927491349824712);
	sum2 = BIGINT(0);
	res1 = sum1 + sum2;

	if (res1.to_string() != "497287433304709813274918274927491349824712") {
		std::cout << "(WRONG)";
	}
	std::cout << "add8: " << res1 << std::endl;

	sum1 = BIGINT(0);
	sum2 = BIGINT(-497287433304709813274918274927491349824712);
	res1 = sum1 + sum2;

	if (res1.to_string() != "-497287433304709813274918274927491349824712") {
		std::cout << "(WRONG)";
	}
	std::cout << "add9: " << res1 << std::endl;

	sum1 = BIGINT(-497287433304709813274918274927491349824712);
	sum2 = BIGINT(0);
	res1 = sum1 + sum2;

	if (res1.to_string() != "-497287433304709813274918274927491349824712") {
		std::cout << "(WRONG)";
	}
	std::cout << "add10: " << res1 << std::endl;

	sum1 = BIGINT(1);
	sum2 = BIGINT(0);
	res1 = sum1 + sum2;

	if (res1.to_string() != "1") {
		std::cout << "(WRONG)";
	}
	std::cout << "add11: " << res1 << std::endl;

	sum1 = BIGINT(0);
	sum2 = BIGINT(1);
	res1 = sum1 + sum2;

	if (res1.to_string() != "1") {
		std::cout << "(WRONG)";
	}
	std::cout << "add12: " << res1 << std::endl;

	sum1 = BIGINT(0);
	sum2 = BIGINT(-1);
	res1 = sum1 + sum2;

	if (res1.to_string() != "-1") {
		std::cout << "(WRONG)";
	}
	std::cout << "add13: " << res1 << std::endl;

	sum1 = BIGINT(-1);
	sum2 = BIGINT(1);
	res1 = sum1 + sum2;

	if (res1.to_string() != "0") {
		std::cout << "(WRONG)";
	}
	std::cout << "add14: " << res1 << std::endl;

	sum1 = BIGINT(1);
	sum2 = BIGINT(-1);
	res1 = sum1 + sum2;

	if (res1.to_string() != "0") {
		std::cout << "(WRONG)";
	}
	std::cout << "add15: " << res1 << std::endl;

	sum1 = BIGINT(-1);
	sum2 = BIGINT(-1);
	res1 = sum1 + sum2;
	if (res1.to_string() != "-2") {
		std::cout << "(WRONG)";
	}
	std::cout << "add16: " << res1 << std::endl;

	sum1 = BIGINT(34809328409121348019480148014801948109348194810);
	res1 = sum1 + 2345667;
	if (res1.to_string() != "34809328409121348019480148014801948109350540477") {
		std::cout << "(WRONG)";
	}
	std::cout << "add17: " << res1 << std::endl;

	sum1 = BIGINT(34809328409121348019480148014801948109348194810);
	res1 = sum1 + (-2345667);
	if (res1.to_string() != "34809328409121348019480148014801948109345849143") {
		std::cout << "(WRONG)";
	}
	std::cout << "add18: " << res1 << std::endl;

	return 0;
}