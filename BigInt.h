#ifndef BINT_H
#define BINT_H

#include <string>
#include <cstdint>
#include <sstream>
#include <cmath>

#pragma once

#define BIGINT(A) integer::BigInt(#A)

#define LIMITS_NUM 999999999
#define LIMITS_MAX 1000000000

#define DOUBLE_LIMITS_NUM 999999999999999999
#define DOUBLE_LIMITS_MAX 1000000000000000000

#define SIZE_LIMITS_NUM 9
#define SIZE_DOUBLE_LIMITS_NUM 18

namespace  integer {

	enum Magnitude {
		UNSIGNED = '+',
		SIGNED = '-'
	};

	class BigInt
	{


	public:
		BigInt();
		BigInt(char const* num);
		BigInt(const std::string &num);
		BigInt(const BigInt &other);
		BigInt(unsigned int num);
		BigInt(int num);
		BigInt(unsigned long long num);
		BigInt(long long num);
		BigInt(unsigned long num);
		BigInt(long num);
		BigInt(BigInt &&other);

		uint_least32_t* values_t;

		std::string toString() const;
		size_t getNumNodes() const;
		size_t lenght() const;
		size_t size() const;
		bool is_sinalized();
		bool is_empty();

		static std::string convertBase(const BigInt& num, int from, int to);

		BigInt& operator=(const BigInt& b);
		BigInt& operator=(const std::string &num);

		//stream
		friend std::ostream & operator<< (std::ostream &out, const BigInt &t);

		//comparison operators
		friend bool operator==(const BigInt& lhs, const BigInt& rhs);
		friend bool operator==(int& lhs, const BigInt& rhs);
		friend bool operator==(const BigInt& lhs, int& rhs);
		friend bool operator!=(const BigInt& lhs, const BigInt& rhs);
		friend bool operator!=(int& lhs, const BigInt& rhs);
		friend bool operator!=(const BigInt& lhs, int& rhs);
		friend bool operator<(const BigInt& lhs, const BigInt& rhs);
		friend bool operator>(const BigInt& lhs, const BigInt& rhs);
		friend bool operator<=(const BigInt& lhs, const BigInt& rhs);
		friend bool operator>=(const BigInt& lhs, const BigInt& rhs);

		//arithmetic operators
		friend BigInt operator+(const BigInt& a, const BigInt& b);
		friend BigInt operator-(const BigInt& a, const BigInt& b);
		friend BigInt operator*(const BigInt& a, const BigInt& b);
		friend BigInt operator*(const BigInt& a, unsigned long& b);
		friend BigInt operator/(const BigInt& a, const BigInt& b);
		friend BigInt operator%(const BigInt& a, const BigInt& b);
		friend BigInt operator~(const BigInt& a);
		friend BigInt operator&(const BigInt& a, const BigInt& b);
		friend BigInt operator|(const BigInt& a, const BigInt& b);
		friend BigInt operator^(const BigInt& a, const BigInt& b);
		friend BigInt operator<<(const BigInt &a, size_t b);
		friend BigInt operator>>(const BigInt &a, size_t b);

		//assignment operators
		friend BigInt& operator+=(BigInt& a, const BigInt& b);
		friend BigInt& operator-=(BigInt& a, const BigInt& b);
		friend BigInt& operator*=(BigInt& a, const BigInt& b);
		friend BigInt& operator/=(BigInt& a, const BigInt& b);
		friend BigInt& operator%=(BigInt& a, const BigInt& b);
		friend BigInt& operator&=(BigInt& a, const BigInt& b);
		friend BigInt& operator|=(BigInt& a, const BigInt& b);
		friend BigInt& operator^=(BigInt& a, const BigInt& b);

		//increment / decrement operators
		friend BigInt& operator++(BigInt& a);
		friend BigInt& operator--(BigInt& a);
		friend BigInt operator++(BigInt& a, int);
		friend BigInt operator--(BigInt& a, int);

		virtual ~BigInt();

		Magnitude signal = Magnitude::UNSIGNED;
		size_t nodes = 0;

	private:

		BigInt(uint_least32_t *values_t, Magnitude signal, size_t numnodes);
		const size_t _archbits = 9;

	};

	BigInt::BigInt() {
		this->signal = Magnitude::UNSIGNED;
		this->nodes = 1;
		this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];
		this->values_t[0] = 0;
	}

	inline BigInt::BigInt(char const * num)
	{
		size_t size;
		for (size = 0; num[size] != '\0'; size++);
		if (num[0] == static_cast<char>(Magnitude::SIGNED)) {
			this->signal = Magnitude::SIGNED;
		}
		else {
			this->signal = Magnitude::UNSIGNED;
		}

		this->nodes = static_cast<size_t>(ceil(static_cast<double>(size) / static_cast<double>(this->_archbits)));

		this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];
		std::string s(num);
		size_t i, j;

		size_t v = size % this->_archbits;
		if (this->signal == Magnitude::SIGNED) {
			for (i = size, j = 0; i >= this->_archbits && j < this->nodes; i -= this->_archbits, j++)
			{
				this->values_t[j] = std::stoul(s.substr(i - this->_archbits, this->_archbits));
			}
			if (v) {
				this->values_t[j] = std::stoul(s.substr(1, v - 1));
			}
		}
		else {
			for (i = size, j = 0; i >= this->_archbits && j < this->nodes; i -= this->_archbits, j++)
			{
				this->values_t[j] = std::stoul(s.substr(i - this->_archbits, this->_archbits));
			}
			if (v) {
				this->values_t[j] = std::stoul(s.substr(0, v));
			}
		}
	}

	inline BigInt::BigInt(const std::string &num)
	{
		size_t size;
		for (size = 0; num[size] != '\0'; size++);
		if (num[0] == static_cast<char>(Magnitude::SIGNED)) {
			this->signal = Magnitude::SIGNED;
		}
		else {
			this->signal = Magnitude::UNSIGNED;
		}

		this->nodes = static_cast<size_t>(ceil(static_cast<double>(size) / static_cast<double>(this->_archbits)));

		this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];
		size_t i, j;
		for (i = num.size(), j = 0; i >= this->_archbits && j < this->nodes; i -= this->_archbits, j++)
		{
			this->values_t[j] = std::stoul(num.substr(i - this->_archbits, this->_archbits));
		}

		size_t v = num.size() % this->_archbits;
		if (v) {
			this->values_t[j] = std::stoul(num.substr(0, v));
		}
	}

	inline BigInt::BigInt(const BigInt &other)
	{
		this->signal = other.signal;
		this->nodes = other.getNumNodes();
		//std::cout << other.toString() << std::endl;
		this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];
		for (size_t i = 0; i < this->nodes; i++) {
			this->values_t[i] = other.values_t[i];
		}
	}

	inline BigInt::BigInt(unsigned int num)
	{
		std::string str = std::to_string(num);
		this->signal = Magnitude::UNSIGNED;
		this->nodes = 1;
		this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];
		this->values_t[0] = num;
	}

	inline BigInt::BigInt(int num)
	{
		std::string str = std::to_string(num);
		if (num >= 0) {
			this->signal = Magnitude::UNSIGNED;
			this->nodes = 1;
			this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];
			this->values_t[0] = num;
		}
		else {
			this->signal = Magnitude::SIGNED;
			this->nodes = 1;
			this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];
			this->values_t[0] = num*(-1);
		}
	}

	inline BigInt::BigInt(unsigned long long num)
	{
		std::string str = std::to_string(num);
		if (str.size() > SIZE_DOUBLE_LIMITS_NUM) {
			this->signal = Magnitude::UNSIGNED;
			this->nodes = 3;
			this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];
			size_t idx = str.size() - SIZE_DOUBLE_LIMITS_NUM;
			this->values_t[2] = std::stoul(str.substr(0, idx));
			this->values_t[1] = std::stoul(str.substr(idx, SIZE_LIMITS_NUM));
			this->values_t[0] = std::stoul(str.substr(idx + SIZE_LIMITS_NUM, SIZE_LIMITS_NUM));
		}
		else if (str.size() > SIZE_LIMITS_NUM) {
			this->signal = Magnitude::UNSIGNED;
			this->nodes = 2;
			this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];
			size_t idx = str.size() - SIZE_LIMITS_NUM;
			this->values_t[1] = std::stoul(str.substr(0, idx));
			this->values_t[0] = std::stoul(str.substr(idx, SIZE_LIMITS_NUM));
		}
		else {
			this->signal = Magnitude::UNSIGNED;
			this->nodes = 1;
			this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];
			this->values_t[0] = std::stoul(str);
		}
	}

	inline BigInt::BigInt(long long num)
	{
		std::string str = std::to_string(num);
		if (str.size() > SIZE_DOUBLE_LIMITS_NUM) {
			this->nodes = 3;
			this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];
			if (str[0] == Magnitude::SIGNED) {
				this->signal = Magnitude::SIGNED;
				size_t idx = str.size() - SIZE_DOUBLE_LIMITS_NUM;
				this->values_t[2] = std::stoul(str.substr(1, idx));
				this->values_t[1] = std::stoul(str.substr(idx, SIZE_LIMITS_NUM));
				this->values_t[0] = std::stoul(str.substr(idx + SIZE_LIMITS_NUM, SIZE_LIMITS_NUM));
			}
			else
			{
				this->signal = Magnitude::UNSIGNED;
				size_t idx = str.size() - SIZE_DOUBLE_LIMITS_NUM;
				this->values_t[2] = std::stoul(str.substr(0, idx));
				this->values_t[1] = std::stoul(str.substr(idx, SIZE_LIMITS_NUM));
				this->values_t[0] = std::stoul(str.substr(idx + SIZE_LIMITS_NUM, SIZE_LIMITS_NUM));
			}
		}
		else if (str.size() > SIZE_LIMITS_NUM) {
			this->signal = Magnitude::SIGNED;
			this->nodes = 2;
			this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];
			size_t idx = str.size() - SIZE_LIMITS_NUM;
			this->values_t[1] = std::stoul(str.substr(1, idx));
			this->values_t[0] = std::stoul(str.substr(idx, SIZE_LIMITS_NUM));
		}
		else {
			this->signal = Magnitude::SIGNED;
			this->nodes = 1;
			this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];
			this->values_t[0] = std::stoul(str);
		}
	}

	inline BigInt::BigInt(unsigned long num)
	{
		std::string str = std::to_string(num);
		this->signal = Magnitude::UNSIGNED;
		this->nodes = 1;
		this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];
		this->values_t[0] = num;
	}

	inline BigInt::BigInt(long num)
	{
		std::string str = std::to_string(num);
		if (num >= 0) {
			this->signal = Magnitude::UNSIGNED;
			this->nodes = 1;
			this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];
			this->values_t[0] = num;
		}
		else {
			this->signal = Magnitude::SIGNED;
			this->nodes = 1;
			this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];
			this->values_t[0] = num*(-1);
		}
	}

	inline BigInt::BigInt(BigInt &&other)
	{
		this->signal = other.signal;
		this->nodes = other.getNumNodes();
		this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];
		for (size_t i = 0; i < this->nodes; i++) {
			this->values_t[i] = other.values_t[i];
		}
	}

	inline BigInt::BigInt(uint_least32_t *values_t, Magnitude signal, size_t numnodes)
	{
		this->signal = signal;
		this->nodes = numnodes;
		this->values_t = &values_t[0];
		values_t = nullptr;
		//this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];
		//for (size_t i = 0; i < this->nodes; i++) {
		//	this->values_t[i] = values_t[i];
		//}
	}

	inline std::string BigInt::toString() const
	{
		std::ostringstream stream;
		bool first_node = true;
		if (!(this->nodes == 0)) {
			for (size_t i = 0; i < this->nodes; i++)
			{
				if (first_node) {
					if (this->signal == Magnitude::SIGNED) {
						stream << '-';
					}
					stream << this->values_t[this->nodes - i - 1];
					first_node = false;
				}
				else {
					stream.width(this->_archbits * sizeof(char));
					stream.fill('0');
					stream << this->values_t[this->nodes - i - 1];
				}
			}
		}
		return stream.str();
	}

	inline size_t BigInt::getNumNodes() const
	{
		return this->nodes;
	}

	inline size_t BigInt::lenght() const
	{
		std::string r;
		r = this->toString();
		if (r[0] != Magnitude::SIGNED) {
			return r.size() - 1;
		}
		return r.size();
	}

	inline size_t BigInt::size() const
	{
		std::string r;
		r = this->toString();
		if (r[0] != Magnitude::SIGNED) {
			return r.size();
		}
		return r.size() - 1;
	}

	inline bool BigInt::is_sinalized()
	{
		return  (this->signal == Magnitude::SIGNED);
	}

	inline bool BigInt::is_empty()
	{
		return (this->nodes == 0);
	}

	inline std::string BigInt::convertBase(const BigInt& num, int from, int to) {
		std::string snum = num.toString();

		if (num == nullptr) {
			return nullptr;
		}

		if (from < 2 || to < 2) { 
			return nullptr;
		}

		size_t lsnum = snum.size();

		int *strnum = new int[snum.size()];



		std::string sout;

		return sout;
	}

	//inline std::string BigInt::convertBase(const BigInt& num, int from, int to)
	//{
	//	//if (num == nullptr) {
	//	//	return nullptr;
	//	//}

	//	if (from < 2 || from > 36 || to < 2 || to > 36) { 
	//		return nullptr;
	//	}

	//	std::string s = num.toString();
	//	size_t il = s.size();

	//	//String of Values
	//	int *fs = new int[il];
	//	size_t k = 0;
	//	size_t i, j;

	//	for (i = il, k = 0; i >= 1; i--, k++)
	//	{
	//		if (s[i-1] >= '0' && s[i-1] <= '9')
	//		{
	//			fs[k] = s[i - 1] - '0';
	//		}
	//		else
	//		{
	//			if (s[i - 1] >= 'A' && s[i - 1] <= 'Z')
	//			{
	//				fs[k] = 10 + s[i - 1] - 'A';
	//			}
	//			else if (s[i - 1] >= 'a' && s[i - 1] <= 'z')
	//			{
	//				fs[k] = 10 + s[i - 1] - 'a';
	//			}
	//			else
	//			{
	//				delete[] fs;
	//				return "Error: Input string must only contain any of [0 - 9] or [a- z] or [A - Z]";
	//			}
	//		}
	//	}

	//	for (i = 0; i < il; i++)
	//	{
	//		if (fs[i] >= from) {
	//			return "Error: Not a valid number for this input base";
	//		}
	//	}

	//	size_t ol = il * (from / to + 1);
	//	//accumulation array
	//	int *as = new int[ol + 10];
	//	//result array
	//	int *rs = new int[ol + 10];

	//	for (i = 0;i<ol;i++)
	//	{
	//		as[i] = 0;
	//		rs[i] = 0;
	//	}
	//	as[0] = 1;

	//	//evaluate the output
	//	for (int i = 0; i < il; i++) //for each input digit
	//	{
	//		for (int j = 0; j < ol; j++) //add the input digit 
	//									 // times (base:to from^i) to the output cumulator
	//		{
	//			rs[j] += as[j] * fs[i];
	//			int temp = rs[j];
	//			int rem = 0;
	//			int ip = j;
	//			do // fix up any remainders in base:to
	//			{
	//				rem = temp / to;
	//				rs[ip] = temp - rem*to;
	//				ip++;
	//				rs[ip] += rem;
	//				temp = rs[ip];
	//			} while (temp >= to);
	//		}

	//		//calculate the next power from^i) in base:to format
	//		for (int j = 0; j < ol; j++)
	//		{
	//			as[j] = as[j] * from;
	//		}
	//		for (int j = 0;j<ol;j++) //check for any remainders
	//		{
	//			int temp = as[j];
	//			int rem = 0;
	//			int ip = j;
	//			do  //fix up any remainders
	//			{
	//				rem = temp / to;
	//				as[ip] = temp - rem * to; 
	//				ip++;
	//				as[ip] += rem;
	//				temp = as[ip];
	//			} while (temp >= to);
	//		}
	//	}

	//	std::string sout; //initialize output string
	//	bool first = false; //leading zero flag
	//	for (int i = ol; i >= 0; i--)
	//	{
	//		if (rs[i] != 0) { first = true; }
	//		if (!first) { continue; }
	//		if (rs[i] < 10) { sout += (char)(rs[i] + '0'); }
	//		else { sout += (char)(rs[i] + 'A' - 10); }
	//	}
	//	if (sout.empty()) { return "0"; } //input was zero, return 0
	//													//return the converted string

	//	delete[]as;
	//	delete[]rs;
	//	delete[]fs;

	//	return sout;
	//}

	inline BigInt& BigInt::operator=(const BigInt &b)
	{
		this->nodes = b.nodes;
		this->signal = b.signal;
		delete[] this->values_t;
		this->values_t = &b.values_t[0];
		//this->values_t = new uint_least32_t[this->nodes];
		//for (size_t i = 0; i < b.nodes; i++) {
		//	this->values_t[i] = b.values_t[i];
		//}
		return *this;
	}

	inline BigInt & BigInt::operator=(const std::string & num)
	{
		BigInt b(num);
		this->nodes = b.nodes;
		this->signal = b.signal;
		delete[] this->values_t;
		this->values_t = &b.values_t[0];
		//this->values_t = new uint_least32_t[this->nodes];
		//for (size_t i = 0; i < b.nodes; i++) {
		//	this->values_t[i] = b.values_t[i];
		//}
		return *this;
	}

	std::ostream & operator<<(std::ostream & out, const BigInt & t)
	{
		out << t.toString();
		return out;
	}

	bool operator==(const BigInt & lhs, const BigInt & rhs)
	{
		if (lhs.getNumNodes() != rhs.getNumNodes()) {
			return false;
		}
		else {
			for (size_t i = 0; i < lhs.getNumNodes(); i++) {
				if (lhs.values_t[i] != rhs.values_t[i]) {
					return false;
				}
			}
		}
		return true;
	}

	bool operator==(int & lhs, const BigInt & rhs)
	{
		return integer::BigInt(lhs) == rhs;
	}

	bool operator==(const BigInt & lhs, int & rhs)
	{
		return lhs == integer::BigInt(rhs);
	}

	bool operator!=(const BigInt & lhs, const BigInt & rhs)
	{
		if (lhs.getNumNodes() == rhs.getNumNodes()) {
			return false;
		}
		else {
			for (size_t i = 0; i < lhs.getNumNodes(); i++) {
				if (lhs.values_t[i] == rhs.values_t[i]) {
					return false;
				}
			}
		}
		return true;
	}

	bool operator!=(int & lhs, const BigInt & rhs)
	{
		return integer::BigInt(lhs) != rhs;
	}

	bool operator!=(const BigInt & lhs, int & rhs)
	{
		return lhs != integer::BigInt(rhs);
	}

	bool operator<(const BigInt & lhs, const BigInt & rhs)
	{
		if (lhs.getNumNodes() > rhs.getNumNodes()) {
			return false;
		}
		else if (lhs.getNumNodes() == rhs.getNumNodes()) {
			for (size_t i = 0; i < lhs.getNumNodes(); i++) {
				if (lhs.values_t[i] > rhs.values_t[i]) {
					return false;
				}
			}
		}
		return true;
	}

	bool operator>(const BigInt & lhs, const BigInt & rhs)
	{
		if (lhs.nodes < rhs.nodes) {
			return false;
		}
		else if (lhs.nodes == rhs.nodes) {
			for (size_t i = 0; i < lhs.nodes; i++) {
				if (lhs.values_t[i] <= rhs.values_t[i]) {
					return false;
				}
			}
		}
		return true;
	}

	bool operator<=(const BigInt & lhs, const BigInt & rhs)
	{
		return (lhs < rhs) || (lhs == rhs);
	}

	bool operator>=(const BigInt & lhs, const BigInt & rhs)
	{
		return (lhs > rhs) || (lhs == rhs);
	}

	BigInt operator+(const BigInt &a, const BigInt &b)
	{
		uint_least32_t carry = 0;
		uint_least32_t sum = 0;
		size_t maxbits = 0;
		//char *strsum;
		uint_least32_t *r = nullptr;

		if (a.signal == b.signal) {

			if (a.nodes >= b.nodes) {
				maxbits = a.nodes;
				r = new uint_least32_t[maxbits];
				for (size_t i = 0; i < maxbits; i++) {
					if (i < b.nodes) {
						sum = a.values_t[i] + b.values_t[i] + carry;
						if (sum > LIMITS_NUM) {
							carry = 1;
							r[i] = sum - LIMITS_MAX;
						}
						else {
							carry = 0;
							r[i] = sum;
						}
					}
					else {
						if (carry == 0) {
							r[i] = a.values_t[i];
						}
						else {
							sum = a.values_t[i] + carry;
							if (sum > LIMITS_NUM) {
								carry = 1;
								r[i] = sum - LIMITS_MAX;
							}
							else {
								carry = 0;
								r[i] = sum;
							}
						}
					}
				}
			}
			else {
				maxbits = b.nodes;
				r = new uint_least32_t[maxbits];
				size_t i = 0;
				for (i = 0; i < maxbits; i++) {
					if (i < a.nodes) {
						sum = a.values_t[i] + b.values_t[i] + carry;
						if (sum > LIMITS_NUM) {
							carry = 1;
							r[i] = sum - LIMITS_MAX;
						}
						else {
							carry = 0;
							r[i] = sum;
						}
					}
					else {
						if (carry == 0) {
							r[i] = b.values_t[i];
						}
						else {
							sum = b.values_t[i] + carry;
							if (sum > LIMITS_NUM) {
								carry = 1;
								r[i] = sum - LIMITS_MAX;
							}
							else {
								carry = 0;
								r[i] = sum;
							}
						}
					}
				}
			}
			sum = 0;

			if (carry > 0) {
				maxbits++;
				//strsum += '1';
				r = (uint_least32_t *)realloc(r, maxbits * sizeof(uint_least32_t));
				if (!r) {
					exit(-1);
				}
				r[maxbits - 1] = carry;
			}
			return integer::BigInt(r, a.signal, maxbits);
		}
		else {
			return a - b;
		}

		
	}

	BigInt operator-(const BigInt & a, const BigInt & b)
	{
		uint_least32_t carry = 0;
		uint_least32_t sum = 0;
		uint_least32_t sub = 0;
		size_t maxbits = 0;
		integer::Magnitude m;
		//char *strsum;
		uint_least32_t *r = nullptr;


		if (a.signal != b.signal) {
			if (a.nodes >= b.nodes) {
				maxbits = a.nodes;
				r = new uint_least32_t[maxbits];
				for (size_t i = 0; i < maxbits; i++) {
					if (i < b.nodes) {
						sum = b.values_t[i] + carry;
						if (a.values_t[i] >= sum) {
							r[i] = a.values_t[i] - sum;
							carry = 0;
						}
						else {
							r[i] = a.values_t[i] + LIMITS_MAX - sum;
							carry = 1;
						}
					}
					else {
						if (carry == 0) {
							r[i] = a.values_t[i];
						}
						else {
							r[i] = a.values_t[i] - carry;
							carry = 0;
						}
					}
				}
				m = a.signal;
			}
			else {
				maxbits = b.nodes;
				r = new uint_least32_t[maxbits];
				for (size_t i = 0; i < maxbits; i++) {
					if (i < a.nodes) {
						sum = a.values_t[i] + carry;
						if (b.values_t[i] >= sum) {
							r[i] = b.values_t[i] - sum;
							carry = 0;
						}
						else {
							r[i] = b.values_t[i] + LIMITS_MAX - sum;
							carry = 1;
						}
					}
					else {
						if (carry == 0) {
							r[i] = b.values_t[i];
						}
						else {
							r[i] = a.values_t[i] - carry;
							carry = 0;
						}
					}
				}
				m = b.signal;
			}
			sum = 0;

			if (r[maxbits - 1] == 0 && maxbits > 1) {
				maxbits--;
				r = (uint_least32_t *)realloc(r, maxbits * sizeof(uint_least32_t));
				if (!r) {
					exit(-1);
				}
			}

			return integer::BigInt(r, m, maxbits);
		}
		else
		{
			return a + b;
		}
	}

	BigInt operator*(const BigInt & a, const BigInt & b)
	{
		uint_least64_t value;
		uint_least64_t carry = 0;

		size_t maxbits;
		maxbits = a.nodes + b.nodes;
		uint_least32_t *r = (uint_least32_t *)calloc(maxbits, sizeof(uint_least32_t));

		size_t i = 0, j = 0;
		for (i = 0; i < b.nodes; i++) {
			carry = 0;
			for (j = i; j < (a.nodes + i); j++) {
				value = a.values_t[j] * (static_cast<uint_least64_t>(b.values_t[i])) + carry + r[j];
				carry = value / LIMITS_MAX;
				r[j] = static_cast<uint_least32_t>(value - (carry)*LIMITS_MAX);
			}
		}

		r[maxbits - 1] = static_cast<uint_least32_t>(carry);
		if (r[maxbits - 1] == 0) {
			maxbits--;
			r = (uint_least32_t *)realloc(r, maxbits * sizeof(uint_least32_t));
			if (!r) {
				exit(-1);
			}
		}

		return integer::BigInt(r, integer::Magnitude::UNSIGNED, maxbits);
	}

	BigInt operator*(const BigInt & a, unsigned long & b)
	{
		uint_least64_t value;
		uint_least64_t carry = 0;

		size_t maxbits;
		maxbits = a.nodes + 1;
		uint_least32_t *r = (uint_least32_t *)calloc(maxbits, sizeof(uint_least32_t));

		size_t i = 0, j = 0;
		carry = 0;
		for (j = 0; j < a.nodes; j++) {
			value = a.values_t[j] * (static_cast<uint_least64_t>(b)) + carry + r[j];
			carry = value / LIMITS_MAX;
			r[j] = static_cast<uint_least32_t>(value - (carry)*LIMITS_MAX);
		}

		r[maxbits - 1] = static_cast<uint_least32_t>(carry);
		if (r[maxbits - 1] == 0) {
			maxbits--;
			r = (uint_least32_t *)realloc(r, maxbits * sizeof(uint_least32_t));
			if (!r) {
				exit(-1);
			}
		}

		return integer::BigInt(r, integer::Magnitude::UNSIGNED, maxbits);
	}

	BigInt operator/(const BigInt & a, const BigInt & b)
	{
		int value;
		uint_least64_t carry = 0;
		uint_least32_t *r = nullptr;
		//size_t maxbits;
		std::string str;
		size_t idx = 0;
		integer::BigInt t;

		BigInt number_a;

		std::string sa = a.toString();
		size_t size_b = b.toString().size();

		size_t begin_sa;
		size_t end_sa;

		
		if (sa[0] == Magnitude::SIGNED) {
			begin_sa = 1;
			end_sa = size_b;
			idx = size_b;
		}
		else {
			begin_sa = 0;
			end_sa = size_b - 1;
			idx = size_b;
		}
		
		std::string parcial_sa = "";

		if (b == 0) {
			std::cout << "ERROR: Division by zero!!!" << std::endl;
			exit(-1);
		}

		if (a.nodes > b.nodes) {
			while (end_sa < sa.size()) {
				value = 9;
				parcial_sa += sa.substr(begin_sa, idx);
				number_a = parcial_sa;
				//integer::BigInt m(b*value);
				while (b*value > number_a)
				{
					value--;
				}
				if (value > 0) {
					integer::BigInt m(b*value);
					t = number_a - m;
					if (t == 0) {
						parcial_sa.clear();
						end_sa += 1;
						begin_sa = end_sa;
					}
					else {
						parcial_sa.clear();
						parcial_sa += t.toString();
						//idx = size_b - t.size();
						end_sa += 1;
						begin_sa = end_sa;
					}
					idx = 1;
				}
				else {
					parcial_sa.clear();
					parcial_sa += t.toString();
					end_sa++;
					idx++;
				}
				
				str += std::to_string(value);
			}
		}
		else if (a.nodes < b.nodes) {
			return integer::BigInt(0);
		}
		else {
			if (a < b) {
				return integer::BigInt(0);
			}
			else {
				value = a.values_t[a.nodes - 1] / b.values_t[b.nodes - 1];
				size_t j;
				for (j = value; j <= value + 1; j++) {
					if (b*j > a) {
						str += std::to_string(j - 1);
						break;
					}
				}
			}
		}

		return integer::BigInt(str);
	}

	BigInt operator&(const BigInt & a, const BigInt & b)
	{
		BigInt r;
		size_t i, j;
		uint_least32_t value;
		uint_least32_t carry = 0;

		size_t maxbits;
		maxbits = a.nodes > b.nodes ? a.nodes : b.nodes;

		delete[] r.values_t;
		r.values_t = (uint_least32_t *)calloc(maxbits, sizeof(uint_least32_t));
		r.nodes = a.nodes;
		for (i = 0; i < b.nodes; i++) {
			carry = 0;
			for (j = i; j < (a.nodes + i); j++) {
				value = (a.values_t[j] & b.values_t[i]) + carry + r.values_t[j];
				carry = value / LIMITS_MAX;
				r.values_t[j] = value - (carry)*LIMITS_MAX;
			}
		}
		r.values_t[maxbits - 1] = static_cast<uint_least32_t>(carry);
		while (r.values_t[maxbits - 1] == 0) {
			maxbits--;
			if (maxbits < 0) {
				r.values_t[0] = 0;
				r.nodes = 1;
				break;
			}
			r.values_t = (uint_least32_t *)realloc(r.values_t, maxbits * sizeof(uint_least32_t));
			if (!r.values_t) {
				exit(-1);
			}
		}
		r.nodes = maxbits;
		return r;
	}

	//BigInt operator<<(const BigInt & a, size_t b)
	//{
	//	if (b == 0) {
	//		return a;
	//	}
	//	return BigInt();
	//}

	inline BigInt::~BigInt() {
		//delete[] values_t;
	}
}
#endif
