#include <iostream>
#include <ctime>
#include <string>
#include "BigInt.h"

int main() {

	integer::BigInt bint1(BIGINT(-3000006536563535635765765855356365365980435765765854843653656353563576576585484));
	if (bint1.to_string() != "-3000006536563535635765765855356365365980435765765854843653656353563576576585484") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor1: " << bint1 << std::endl;

	integer::BigInt bint2(BIGINT(65765854843653656353563576536563535636585658548435765765854843653656353563576576585484));
	if (bint2.to_string() != "65765854843653656353563576536563535636585658548435765765854843653656353563576576585484") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor2: " << bint2 << std::endl;

	if (BIGINT(29384023843).to_string() != "29384023843") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor3: " << BIGINT(29384023843) << std::endl;

	if (BIGINT(-3656353563658565).to_string() != "-3656353563658565") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor4: " << BIGINT(-3656353563658565) << std::endl;

	integer::BigInt bint3(18446744073709551615);
	if (bint3.to_string() != "18446744073709551615") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor5: " << bint3 << std::endl;

	integer::BigInt bint4(-9223372036854775807);
	if (bint4.to_string() != "-9223372036854775807") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor6: " << bint4 << std::endl;

	integer::BigInt bint5(1000000000000000000);
	if (bint5.to_string() != "1000000000000000000") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor7: " << bint5 << std::endl;

	integer::BigInt bint6(4294967295);
	if (bint6.to_string() != "4294967295") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor8: " << bint6 << std::endl;

	integer::BigInt bint7(5371652);
	if (bint7.to_string() != "5371652") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor9: " << bint7 << std::endl;

	integer::BigInt bint8(2147483647);
	if (bint8.to_string() != "2147483647") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor10: " << bint8 << std::endl;

	integer::BigInt bint9("48901790719384732809440214");
	if (bint9.to_string() != "48901790719384732809440214") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor11: " << bint9 << std::endl;

	integer::BigInt bint10("-49730091022146768130952309");
	if (bint10.to_string() != "-49730091022146768130952309") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor12: " << bint10 << std::endl;

	integer::BigInt bint11(0);
	if (bint11.to_string() != "0") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor13: " << bint11 << std::endl;

	integer::BigInt bint12(-0);
	if (bint12.to_string() != "0") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor14: " << bint12 << std::endl;

	integer::BigInt bint13(+0);
	if (bint13.to_string() != "0") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor15: " << bint13 << std::endl;

	integer::BigInt bint14("0");
	if (bint14.to_string() != "0") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor16: " << bint14 << std::endl;

	integer::BigInt bint15("-0");
	if (bint15.to_string() != "0") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor17: " << bint15 << std::endl;

	integer::BigInt bint16("+0");
	if (bint16.to_string() != "0") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor18: " << bint16 << std::endl;

	std::string s17("36489365472365723645869352736586459238765293652865");
	integer::BigInt bint17(s17);
	if (bint17.to_string() != "36489365472365723645869352736586459238765293652865") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor19: " << bint17 << std::endl;

	std::string s18("-93261273636489365472365723645869350904021012704124712");
	integer::BigInt bint18(s18);
	if (bint18.to_string() != "-93261273636489365472365723645869350904021012704124712") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor20: " << bint18 << std::endl;


	std::string s19("0");
	integer::BigInt bint19(s19);
	if (bint19.to_string() != "0") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor21: " << bint19 << std::endl;


	std::string s20("+0");
	integer::BigInt bint20(s20);
	if (bint20.to_string() != "0") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor22: " << bint20 << std::endl;

	std::string s21("-0");
	integer::BigInt bint21(s21);
	if (bint21.to_string() != "0") {
		std::cout << "(WRONG)";
	}
	std::cout << "constructor23: " << bint21 << std::endl;


	return 0;
}