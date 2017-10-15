#ifndef BINT_H
#define BINT_H

#include <string>
#include <cstdint>
#include <sstream>
#include <cmath>
#include <iostream>

#pragma once

#define BIGINT(A) bnum::BigInt(#A)

#define LIMITS_NUM 999999999
#define LIMITS_MAX 1000000000

#define DOUBLE_LIMITS_NUM 999999999999999999
#define DOUBLE_LIMITS_MAX 1000000000000000000

#define SIZE_LIMITS_NUM 9
#define SIZE_DOUBLE_LIMITS_NUM 18

namespace  bnum {

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

		std::string to_string() const;
		size_t get_num_nodes() const;
		size_t lenght() const;
		size_t size() const;
		bool is_sinalized() const;
		bool is_empty() const;

		static std::string convertBase(const BigInt& num, int from, int to);

		//assignment
		BigInt& operator=(char const* num);
		BigInt& operator=(const std::string &num);
		BigInt& operator=(const BigInt& b);
		BigInt& operator=(unsigned int num);
		BigInt& operator=(int num);
		BigInt& operator=(unsigned long long num);
		BigInt& operator=(long long num);
		BigInt& operator=(unsigned long num);
		BigInt& operator=(long num);


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

		uint_least32_t* values_t;
		size_t nodes = 0;
		Magnitude signal = Magnitude::UNSIGNED;
		
		bool nan = false;
		bool infinity = false;

	private:
		const size_t _archbits = 9;
		BigInt(uint_least32_t *values_t, Magnitude signal, size_t numnodes);

	};

	static inline BigInt& powi(const BigInt& base, const BigInt& exponent) {
		BigInt *p;
		if (exponent == 1) {
			p = new BigInt(base);
			return *p;
		}

		p = new BigInt(1);
		if (exponent != 0) {
			for (BigInt i = 0; i < exponent; i++) {
				*p = *p * base;
			}
		}
		return *p;
	}

	inline BigInt::BigInt() {
		this->signal = Magnitude::UNSIGNED;
		this->nodes = 1;
		this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];
		this->values_t[0] = 0;
	}

	inline BigInt::BigInt(char const *num)
	{
		size_t size;
		for (size = 0; num[size] != '\0'; size++);
		if (num[0] == '-') {
			if (size == 2 && num[1] == '0') {
				this->signal = Magnitude::UNSIGNED;
			}
			else {
				this->signal = Magnitude::SIGNED;
			}
		}
		else {
			this->signal = Magnitude::UNSIGNED;
		}

		std::string s(num);
		size_t i, j;

		if (this->signal == Magnitude::SIGNED) {
			this->nodes = static_cast<size_t>(ceil(static_cast<double>(size - 1) / static_cast<double>(this->_archbits)));

			this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];

			size_t v = (size - 1) % this->_archbits;

			if (v) {
				for (i = size, j = 0; i >= this->_archbits && j < this->nodes - 1; i -= this->_archbits, j++)
				{
					this->values_t[j] = std::stoul(s.substr(i - this->_archbits, this->_archbits));
				}
				this->values_t[j] = std::stoul(s.substr(1, v));
			}
			else {
				for (i = size, j = 0; i >= this->_archbits && j < this->nodes; i -= this->_archbits, j++)
				{
					this->values_t[j] = std::stoul(s.substr(i - this->_archbits, this->_archbits));
				}
			}
		}
		else {
			this->nodes = static_cast<size_t>(ceil(static_cast<double>(size) / static_cast<double>(this->_archbits)));

			this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];

			size_t v = size % this->_archbits;

			if (v) {
				for (i = size, j = 0; i >= this->_archbits && j < this->nodes - 1; i -= this->_archbits, j++)
				{
					this->values_t[j] = std::stoul(s.substr(i - this->_archbits, this->_archbits));
				}

				this->values_t[j] = std::stoul(s.substr(0, v));
			}
			else {
				for (i = size, j = 0; i >= this->_archbits && j < this->nodes; i -= this->_archbits, j++)
				{
					this->values_t[j] = std::stoul(s.substr(i - this->_archbits, this->_archbits));
				}
			}
		}
	}

	inline BigInt::BigInt(const std::string &num)
	{
		size_t size;
		for (size = 0; num[size] != '\0'; size++);

		if (num[0] == '-') {
			if (size == 2 && num[1] == '0') {
				this->signal = Magnitude::UNSIGNED;
			}
			else {
				this->signal = Magnitude::SIGNED;
			}
		}
		else {
			this->signal = Magnitude::UNSIGNED;
		}

		size_t i, j;

		if (this->signal == Magnitude::SIGNED) {
			this->nodes = static_cast<size_t>(ceil(static_cast<double>(size - 1) / static_cast<double>(this->_archbits)));

			this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];

			size_t v = (size - 1) % this->_archbits;

			if (v) {
				for (i = size, j = 0; i >= this->_archbits && j < this->nodes - 1; i -= this->_archbits, j++)
				{
					this->values_t[j] = std::stoul(num.substr(i - this->_archbits, this->_archbits));
				}
				this->values_t[j] = std::stoul(num.substr(1, v));
			}
			else {
				for (i = size, j = 0; i >= this->_archbits && j < this->nodes; i -= this->_archbits, j++)
				{
					this->values_t[j] = std::stoul(num.substr(i - this->_archbits, this->_archbits));
				}
			}
		}
		else {
			this->nodes = static_cast<size_t>(ceil(static_cast<double>(size) / static_cast<double>(this->_archbits)));

			this->values_t = new uint_least32_t[this->nodes * sizeof(uint_least32_t)];

			size_t v = size % this->_archbits;

			if (v) {
				for (i = size, j = 0; i >= this->_archbits && j < this->nodes - 1; i -= this->_archbits, j++)
				{
					this->values_t[j] = std::stoul(num.substr(i - this->_archbits, this->_archbits));
				}

				this->values_t[j] = std::stoul(num.substr(0, v));
			}
			else {
				for (i = size, j = 0; i >= this->_archbits && j < this->nodes; i -= this->_archbits, j++)
				{
					this->values_t[j] = std::stoul(num.substr(i - this->_archbits, this->_archbits));
				}
			}
		}
	}

	inline BigInt::BigInt(const BigInt &other)
	{
		this->signal = other.signal;
		this->nodes = other.get_num_nodes();
		//std::cout << other.to_string() << std::endl;
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
				this->values_t[2] = std::stoul(str.substr(1, idx - 1));
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
			this->values_t[1] = std::stoul(str.substr(1, idx - 1));
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
		this->nodes = other.get_num_nodes();
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
	}

	inline std::string BigInt::to_string() const
	{

		std::ostringstream stream;
		if (this->nan) {
			stream << "NaN";
		}
		else if(this->infinity){
			stream << "Inf";
		}
		else {
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
		}

		
		return stream.str();
	}

	inline size_t BigInt::get_num_nodes() const
	{
		return this->nodes;
	}

	inline size_t BigInt::lenght() const
	{
		std::string r;
		r = this->to_string();
		if (r[0] != Magnitude::SIGNED) {
			return r.size() - 1;
		}
		return r.size();
	}

	inline size_t BigInt::size() const
	{
		std::string r;
		r = this->to_string();
		if (r[0] != Magnitude::SIGNED) {
			return r.size();
		}
		return r.size() - 1;
	}

	inline bool BigInt::is_sinalized() const
	{
		return  (this->signal == Magnitude::SIGNED);
	}

	inline bool BigInt::is_empty() const
	{
		return (this->nodes == 0);
	}

	inline std::string BigInt::convertBase(const BigInt& num, int from, int to) {
		std::string snum = num.to_string();

		if (num == nullptr) {
			return nullptr;
		}

		if (from < 2 || to < 2) {
			return nullptr;
		}

		//size_t lsnum = snum.size();

		//int *strnum = new int[snum.size()];



		std::string sout;

		return sout;
	}

	inline BigInt & BigInt::operator=(char const * num)
	{
		BigInt b(num);
		this->nodes = b.nodes;
		this->signal = b.signal;
		delete[] this->values_t;
		this->values_t = &b.values_t[0];
		return *this;
	}

	inline BigInt & BigInt::operator=(const std::string & num)
	{
		BigInt b(num);
		this->nodes = b.nodes;
		this->signal = b.signal;
		delete[] this->values_t;
		this->values_t = &b.values_t[0];
		return *this;
	}

	inline BigInt& BigInt::operator=(const BigInt &b)
	{
		this->nan = b.nan;
		this->infinity = b.infinity;
		this->nodes = b.nodes;
		this->signal = b.signal;
		delete[] this->values_t;
		this->values_t = &b.values_t[0];
		return *this;
	}

	inline BigInt & BigInt::operator=(unsigned int num)
	{
		BigInt b(num);
		this->nodes = b.nodes;
		this->signal = b.signal;
		delete[] this->values_t;
		this->values_t = &b.values_t[0];
		return *this;
	}

	inline BigInt & BigInt::operator=(int num)
	{
		BigInt b(num);
		this->nodes = b.nodes;
		this->signal = b.signal;
		delete[] this->values_t;
		this->values_t = &b.values_t[0];
		return *this;
	}

	inline BigInt & BigInt::operator=(unsigned long long num)
	{
		BigInt b(num);
		this->nodes = b.nodes;
		this->signal = b.signal;
		delete[] this->values_t;
		this->values_t = &b.values_t[0];
		return *this;
	}

	inline BigInt & BigInt::operator=(long long num)
	{
		BigInt b(num);
		this->nodes = b.nodes;
		this->signal = b.signal;
		delete[] this->values_t;
		this->values_t = &b.values_t[0];
		return *this;
	}

	inline BigInt & BigInt::operator=(unsigned long num)
	{
		BigInt b(num);
		this->nodes = b.nodes;
		this->signal = b.signal;
		delete[] this->values_t;
		this->values_t = &b.values_t[0];
		return *this;
	}

	inline BigInt & BigInt::operator=(long num)
	{
		BigInt b(num);
		this->nodes = b.nodes;
		this->signal = b.signal;
		delete[] this->values_t;
		this->values_t = &b.values_t[0];
		return *this;
	}

	std::ostream & operator<<(std::ostream & out, const BigInt & t)
	{
		out << t.to_string();
		return out;
	}

	inline bool operator==(const BigInt & lhs, const BigInt & rhs)
	{
		if (lhs.get_num_nodes() != rhs.get_num_nodes()) {
			return false;
		}
		else {
			for (size_t i = 0; i < lhs.get_num_nodes(); i++) {
				if (lhs.values_t[i] != rhs.values_t[i]) {
					return false;
				}
			}
		}
		return true;
	}

	inline bool operator==(int & lhs, const BigInt & rhs)
	{
		return bnum::BigInt(lhs) == rhs;
	}

	inline bool operator==(const BigInt & lhs, int & rhs)
	{
		return lhs == bnum::BigInt(rhs);
	}

	inline bool operator!=(const BigInt & lhs, const BigInt & rhs)
	{
		if (lhs.get_num_nodes() != rhs.get_num_nodes()) {
			return true;
		}
		else {
			for (size_t i = 0; i < lhs.get_num_nodes(); i++) {
				if (lhs.values_t[i] != rhs.values_t[i]) {
					return true;
				}
			}
		}
		return false;
	}

	inline bool operator!=(int & lhs, const BigInt & rhs)
	{
		return bnum::BigInt(lhs) != rhs;
	}

	inline bool operator!=(const BigInt & lhs, int & rhs)
	{
		return lhs != bnum::BigInt(rhs);
	}

	inline bool operator<(const BigInt & lhs, const BigInt & rhs)
	{
		if (lhs.get_num_nodes() > rhs.get_num_nodes()) {
			return false;
		}
		else if (lhs.get_num_nodes() == rhs.get_num_nodes()) {
			for (size_t i = 0; i < lhs.get_num_nodes(); i++) {
				if (lhs.values_t[i] >= rhs.values_t[i]) {
					return false;
				}
			}
		}
		return true;
	}

	inline bool operator>(const BigInt & lhs, const BigInt & rhs)
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

	inline bool operator<=(const BigInt & lhs, const BigInt & rhs)
	{
		return (lhs < rhs) || (lhs == rhs);
	}

	inline bool operator>=(const BigInt & lhs, const BigInt & rhs)
	{
		return (lhs > rhs) || (lhs == rhs);
	}

	inline BigInt operator+(const BigInt &a, const BigInt &b)
	{
		uint_least32_t carry = 0;
		uint_least32_t sum = 0;
		size_t maxbits = 0;
		bnum::Magnitude m;
		bool signal = false;
		uint_least32_t *r = nullptr;

		if (a.signal == b.signal) {

			if (a.nodes >= b.nodes) {
				maxbits = a.nodes;
				r = new uint_least32_t[maxbits];
				for (int i = 0; i < maxbits; i++) {
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
				for (int i = 0; i < maxbits; i++) {
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
			if (maxbits == 1) {
				if (r[0] == 0) {
					m = Magnitude::UNSIGNED;
				}
			}
			return bnum::BigInt(r, a.signal, maxbits);
		}
		else {
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
							if (a.nodes == 1 && a.nodes == b.nodes) {
								r[i] = sum - a.values_t[i];
								carry = 0;
								signal = true;
							}
							else {
								r[i] = a.values_t[i] + LIMITS_MAX - sum;
								carry = 1;
							}
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
				if (signal) {
					m = Magnitude::SIGNED;
				}
				else {
					m = a.signal;
				}
				if (maxbits == 1) {
					if (r[0] == 0) {
						m = Magnitude::UNSIGNED;
					}
				}
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
							if (b.nodes == 1 && a.nodes == b.nodes) {
								r[i] = sum - b.values_t[i];
								carry = 0;
								signal = true;
							}
							else {
								r[i] = b.values_t[i] + LIMITS_MAX - sum;
								carry = 1;
							}
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
				if (signal) {
					m = Magnitude::SIGNED;
				}
				else {
					m = b.signal;
				}
				if (maxbits == 1) {
					if (r[0] == 0) {
						m = Magnitude::UNSIGNED;
					}
				}
			}
			sum = 0;

			if (r[maxbits - 1] == 0 && maxbits > 1) {
				maxbits--;
				r = (uint_least32_t *)realloc(r, maxbits * sizeof(uint_least32_t));
				if (!r) {
					exit(-1);
				}
				if (maxbits == 1) {
					if (r[0] == 0) {
						m = Magnitude::UNSIGNED;
					}
				}
			}
			return bnum::BigInt(r, m, maxbits);
		}
	}

	inline BigInt operator-(const BigInt & a, const BigInt & b)
	{
		uint_least32_t carry = 0;
		uint_least32_t sum = 0;
		size_t maxbits = 0;
		bnum::Magnitude m;
		bool signal = false;
		uint_least32_t *r = nullptr;


		if (a.signal == b.signal) {
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
							if (a.nodes == 1 && a.nodes == b.nodes) {
								r[i] = sum - a.values_t[i];
								carry = 0;
								signal = true;
							}
							else {
								r[i] = a.values_t[i] + LIMITS_MAX - sum;
								carry = 1;
							}
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
				if (signal) {
					m = Magnitude::SIGNED;
				}
				else {
					m = a.signal;
				}

				if (maxbits == 1) {
					if (r[0] == 0) {
						m = Magnitude::UNSIGNED;
					}
				}
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
				if (b.signal == bnum::Magnitude::SIGNED) {
					m = bnum::Magnitude::UNSIGNED;
				}
				else
				{
					m = bnum::Magnitude::SIGNED;
				}
			}
			sum = 0;

			if (r[maxbits - 1] == 0 && maxbits > 1) {
				maxbits--;
				r = (uint_least32_t *)realloc(r, maxbits * sizeof(uint_least32_t));
				if (!r) {
					exit(-1);
				}
				if (maxbits == 1) {
					if (r[0] == 0) {
						m = Magnitude::UNSIGNED;
					}
				}
			}

			return bnum::BigInt(r, m, maxbits);
		}
		else
		{
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
				r = (uint_least32_t *)realloc(r, maxbits * sizeof(uint_least32_t));
				if (!r) {
					exit(-1);
				}
				r[maxbits - 1] = carry;
			}
			if (maxbits == 1) {
				if (r[0] == 0) {
					m = Magnitude::UNSIGNED;
				}
			}
			return bnum::BigInt(r, a.signal, maxbits);
		}
	}

	inline BigInt operator*(const BigInt & a, const BigInt & b)
	{
		uint_least64_t value;
#if _MSC_VER >= 1900
		uint_least32_t carry = 0;
#elif __GNUC__ >= 5
		uint_least64_t carry = 0;
#endif

		bnum::Magnitude m;

		size_t maxbits;
		maxbits = a.nodes + b.nodes;
		uint_least32_t *r = (uint_least32_t *)calloc(maxbits, sizeof(uint_least32_t));

		if (a == 0 || b == 0) {
			return bnum::BigInt(0);
		}

		size_t i = 0, j = 0;
		if (a.nodes >= b.nodes) {
			for (i = 0; i < b.nodes; i++) {
				carry = 0;
				for (j = i; j < (a.nodes + i); j++) {
					value = a.values_t[j - i] * (static_cast<uint_least64_t>(b.values_t[i])) + carry + r[j];
#if _MSC_VER >= 1900
#pragma warning( push )
#pragma warning( disable : 4244)
					carry = value / LIMITS_MAX;
					r[j] = static_cast<uint_least32_t>(value - carry*LIMITS_MAX);
#pragma warning( pop ) 
#elif __GNUC__ >= 5
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
					carry = value / LIMITS_MAX;
					r[j] = static_cast<uint_least32_t>(value - (carry)*LIMITS_MAX);
#pragma GCC diagnostic pop
#endif
				}
				r[j] += carry;
			}
		}
		else {
			for (i = 0; i < a.nodes; i++) {
				carry = 0;
				for (j = i; j < (b.nodes + i); j++) {
					value = b.values_t[j - i] * (static_cast<uint_least64_t>(a.values_t[i])) + carry + r[j];
#if _MSC_VER >= 1900
#pragma warning( push )
#pragma warning( disable : 4244)
					carry = value / LIMITS_MAX;
					r[j] = static_cast<uint_least32_t>(value - (carry)*LIMITS_MAX);
#pragma warning( pop ) 
#elif __GNUC__ >= 5
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
					carry = value / LIMITS_MAX;
					r[j] = static_cast<uint_least32_t>(value - (carry)*LIMITS_MAX);
#pragma GCC diagnostic pop
#endif
				}
				r[j] += carry;
			}
		}

		//r[maxbits - 1] = static_cast<uint_least32_t>(carry);
		if (r[maxbits - 1] == 0) {
			maxbits--;
			r = (uint_least32_t *)realloc(r, maxbits * sizeof(uint_least32_t));
			if (!r) {
				exit(-1);
			}
		}

		if (a.signal == b.signal) {
			m = Magnitude::UNSIGNED;
		}
		else {
			m = Magnitude::SIGNED;
		}

		return bnum::BigInt(r, m, maxbits);
	}

	inline BigInt operator/(const BigInt & a, const BigInt & b)
	{
		size_t value;
		std::string str;
		size_t idx = 0;
		bnum::BigInt t;

		BigInt number_a;

		std::string sa = a.to_string();
		size_t size_b = b.to_string().size();

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
			bnum::BigInt res = 0;
			res.infinity = true;
			//std::cout << "ERROR: Division by zero!!!" << std::endl;
			return bnum::BigInt(res);
		}

		if (a.nodes > b.nodes) {
			while (end_sa < sa.size()) {
				value = 9;
				parcial_sa += sa.substr(begin_sa, idx);
				number_a = parcial_sa;
				//bnum::BigInt m(b*value);
				while (b*value > number_a)
				{
					value--;
				}
				if (value > 0) {
					bnum::BigInt m(b*value);
					t = number_a - m;
					if (t == 0) {
						parcial_sa.clear();
						end_sa += 1;
						begin_sa = end_sa;
					}
					else {
						parcial_sa.clear();
						parcial_sa += t.to_string();
						//idx = size_b - t.size();
						end_sa += 1;
						begin_sa = end_sa;
					}
					idx = 1;
				}
				else {
					parcial_sa.clear();
					parcial_sa += t.to_string();
					end_sa++;
					idx++;
				}

				str += std::to_string(value);
			}
		}
		else if (a.nodes < b.nodes) {
			return bnum::BigInt(0);
		}
		else {
			if (a < b) {
				return bnum::BigInt(0);
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

		return bnum::BigInt(str);
	}

	inline BigInt & operator+=(BigInt & a, const BigInt & b)
	{
		a = a + b;
		return a;
	}

	inline BigInt & operator-=(BigInt & a, const BigInt & b)
	{
		a = a - b;
		return a;
	}


	inline BigInt & operator++(BigInt & a)
	{
		a = a + 1;
		return a;
	}

	inline BigInt & operator--(BigInt & a)
	{
		a = a - 1;
		return a;
	}

	inline BigInt operator++(BigInt & a, int)
	{
		a = a + 1;
		return a;
	}

	inline BigInt operator--(BigInt & a, int)
	{
		a = a - 1;
		return a;
	}

	inline BigInt::~BigInt() {
		//delete[] values_t;
	}
}
#endif
