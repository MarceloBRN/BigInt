#include <iostream>
#include <ctime>
#include "BigInt.h"

int main() {

	clock_t begin;
	clock_t end;
	double timeSec;

	size_t itsum = 823456;
	bnum::BigInt sum(0);
	bnum::BigInt fator1(BIGINT(999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999));

	begin = clock();
	for (size_t i = 1; i <= itsum; i++) {
		sum = sum + fator1;
	}
	end = clock();
	timeSec = (end - begin) / static_cast<double>(CLOCKS_PER_SEC);
	std::cout << "add: " << timeSec << std::endl;
	//std::cout << sum << std::endl;

	size_t itsub = 823456;
	bnum::BigInt sub(BIGINT(10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000));
	bnum::BigInt fator2(BIGINT(999999999));

	begin = clock();
	for (size_t i = 1; i <= itsub; i++) {
		sub = sub - fator2;
	}
	end = clock();
	timeSec = (end - begin) / static_cast<double>(CLOCKS_PER_SEC);
	std::cout << "sub: " << timeSec << std::endl;
	//std::cout << sub << std::endl;

	size_t itmult = 10000;
	bnum::BigInt mult(BIGINT(1));
	bnum::BigInt fator3(BIGINT(999999999));

	begin = clock();
	for (size_t i = 1; i <= itmult; i++) {
		mult = mult * fator3;
	}
	end = clock();
	timeSec = (end - begin) / static_cast<double>(CLOCKS_PER_SEC);
	std::cout << "mult: " << timeSec << std::endl;
	//std::cout << mult << std::endl;

	size_t itmult2 = 10000;
	bnum::BigInt mult2(BIGINT(999999999));
	bnum::BigInt fator3_2(BIGINT(2));

	begin = clock();
	for (size_t i = 1; i <= itmult2; i++) {
		mult2 = mult2 * fator3_2;
	}
	end = clock();
	timeSec = (end - begin) / static_cast<double>(CLOCKS_PER_SEC);
	std::cout << "mult2: " << timeSec << std::endl;
	//std::cout << mult2 << std::endl;

	size_t itdiv = 10;
	bnum::BigInt div(BIGINT(999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999));
	bnum::BigInt fator4(BIGINT(99999999999));

	begin = clock();
	for (size_t i = 1; i <= itdiv; i++) {
		div = div / fator4;
	}
	end = clock();
	timeSec = (end - begin) / static_cast<double>(CLOCKS_PER_SEC);
	std::cout << "div: " << timeSec << std::endl;
	std::cout << div.to_string() << std::endl;

	//std::cout << (BIGINT(1739551615) & BIGINT(480127440)).to_string() << std::endl;

	//std::string out = bnum::BigInt::convertBase(BIGINT(480127440), 10, 2);

	//std::cout << out << std::endl;

	return 0;
}