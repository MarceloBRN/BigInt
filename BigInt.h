#ifndef EINT_H
#define EINT_H

#include <string>
#include <cstdint>
#include <sstream>

#pragma once

#define BIGINT(A) ether::BigInt(#A)

#define LIMITS_NUM 999999999
#define LIMITS_MAX 1000000000

#define DOUBLE_LIMITS_NUM 999999999999999999
#define DOUBLE_LIMITS_MAX 1000000000000000000

#define SIZE_LIMITS_NUM 9
#define SIZE_DOUBLE_LIMITS_NUM 18

namespace  ether {

	class BigInt
	{
		enum Magnitude {
			UNSIGNED = '+',
			SIGNED = '-'
		};

	public:
		explicit BigInt();
		explicit BigInt(char const* num);
		explicit BigInt(const std::string &num);
		explicit BigInt(const BigInt &other);
		explicit BigInt(unsigned int num);
		explicit BigInt(int num);
		explicit BigInt(unsigned long long num);
		explicit BigInt(long long num);
		explicit BigInt(unsigned long num);
		explicit BigInt(long num);
		explicit BigInt(BigInt &&other);

		uint_least32_t* values_t;
		
		std::string toString();
		size_t getNumNodes() const;
		size_t lenght() const;
		size_t size() const;
		bool is_sinalized();
		bool is_empty();

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

		virtual ~BigInt();

	private:
		size_t _size = 0;
		size_t _nodes = 0;
		Magnitude signal = Magnitude::UNSIGNED;
		const int _archbits = 9;
	};

	BigInt::BigInt() {
		this->_size = 1; //Only '0'
		this->signal = Magnitude::UNSIGNED;
		this->_nodes = 1;
		this->values_t = new uint_least32_t[this->_nodes * sizeof(uint_least32_t)];
		this->values_t[0] = 0;
	}

	inline BigInt::BigInt(char const * num)
	{
		for (this->_size = 0; num[this->_size] != '\0'; this->_size++);
		if (num[0] == static_cast<char>(Magnitude::SIGNED)) {
			this->signal = Magnitude::SIGNED;
			this->_size--;
		}
		else {
			this->signal = Magnitude::UNSIGNED;
		}
		
		this->_nodes = static_cast<size_t>(ceil(static_cast<double>(this->_size) / static_cast<double>(this->_archbits)));

		this->values_t = new uint_least32_t[this->_nodes * sizeof(uint_least32_t)];
		std::string s(num);
		size_t i, j;

		size_t v = this->_size % this->_archbits;
		if (this->signal == Magnitude::SIGNED) {
			for (i = this->_size, j = this->_nodes - 1; i >= this->_archbits && j >= 0; i -= this->_archbits, j--)
			{
				this->values_t[j] = std::stoi(s.substr(i - this->_archbits + 1, this->_archbits));
			}
			if (v) {
				this->values_t[j] = std::stoi(s.substr(1, v));
			}
		}
		else {
			for (i = this->_size, j = this->_nodes - 1; i >= this->_archbits && j >= 0; i -= this->_archbits, j--)
			{
				this->values_t[j] = std::stoi(s.substr(i - this->_archbits, this->_archbits));
			}
			if (v) {
				this->values_t[j] = std::stoi(s.substr(0, v));
			}
		}
	}

	inline BigInt::BigInt(const std::string &num)
	{
		if (num[0] == static_cast<char>(Magnitude::SIGNED)) {
			this->signal = Magnitude::SIGNED;
			this->_size = num.size() - 1;
		}
		else {
			this->signal = Magnitude::UNSIGNED;
			this->_size = num.size();
		}

		this->_nodes = static_cast<size_t>(ceil(static_cast<double>(this->_size) / static_cast<double>(this->_archbits)));

		this->values_t = new uint_least32_t[this->_nodes * sizeof(uint_least32_t)];
		size_t i, j;
		for (i = num.size(), j = this->_nodes - 1; i >= this->_archbits && j >= 0; i -= this->_archbits, j--)
		{
			this->values_t[j] = std::stoi(num.substr(i - this->_archbits, this->_archbits));
		}

		size_t v = num.size() % this->_archbits;
		if (v) {
			this->values_t[j] = std::stoi(num.substr(0, v));
		}
	}

	inline BigInt::BigInt(const BigInt &other)
	{
		this->_size = other.lenght();
		this->signal = other.signal;
		this->_nodes = other.getNumNodes();
		this->values_t = new uint_least32_t[this->_nodes * sizeof(uint_least32_t)];
		for (size_t i = 0; i < this->_size; i++)	{
			this->values_t[i] = other.values_t[i];
		}
	}

	inline BigInt::BigInt(unsigned int num)
	{
		std::string str = std::to_string(num);
		this->_size = str.size();
		this->signal = Magnitude::UNSIGNED;
		this->_nodes = 1;
		this->values_t = new uint_least32_t[this->_nodes * sizeof(uint_least32_t)];
		this->values_t[0] = num;
	}

	inline BigInt::BigInt(int num)
	{
		std::string str = std::to_string(num);
		if (num >= 0) {
			this->_size = str.size();
			this->signal = Magnitude::UNSIGNED;
			this->_nodes = 1;
			this->values_t = new uint_least32_t[this->_nodes * sizeof(uint_least32_t)];
			this->values_t[0] = num;
		} else {
			this->_size = str.size() - 1;
			this->signal = Magnitude::SIGNED;
			this->_nodes = 1;
			this->values_t = new uint_least32_t[this->_nodes * sizeof(uint_least32_t)];
			this->values_t[0] = num*(-1);
		}
	}

	inline BigInt::BigInt(unsigned long long num)
	{
		std::string str = std::to_string(num);
		if (str.size() > SIZE_DOUBLE_LIMITS_NUM) {
			this->_size = str.size();
			this->signal = Magnitude::UNSIGNED;
			this->_nodes = 3;
			this->values_t = new uint_least32_t[this->_nodes * sizeof(uint_least32_t)];
			size_t idx = str.size() - SIZE_DOUBLE_LIMITS_NUM;
			this->values_t[0] = std::stoul(str.substr(0, idx));
			this->values_t[1] = std::stoul(str.substr(idx, SIZE_LIMITS_NUM));
			this->values_t[2] = std::stoul(str.substr(idx + SIZE_LIMITS_NUM, SIZE_LIMITS_NUM));
		}
		else if (str.size() > SIZE_LIMITS_NUM) {
			this->_size = str.size();
			this->signal = Magnitude::UNSIGNED;
			this->_nodes = 2;
			this->values_t = new uint_least32_t[this->_nodes * sizeof(uint_least32_t)];
			size_t idx = str.size() - SIZE_LIMITS_NUM;
			this->values_t[0] = std::stoul(str.substr(0, idx));
			this->values_t[1] = std::stoul(str.substr(idx, SIZE_LIMITS_NUM));
		}
		else {
			this->_size = str.size();
			this->signal = Magnitude::UNSIGNED;
			this->_nodes = 1;
			this->values_t = new uint_least32_t[this->_nodes * sizeof(uint_least32_t)];
			this->values_t[0] = std::stoul(str);
		}
	}

	inline BigInt::BigInt(long long num)
	{
		std::string str = std::to_string(num);
		if (str.size() > SIZE_DOUBLE_LIMITS_NUM) {
			this->_nodes = 3;
			this->values_t = new uint_least32_t[this->_nodes * sizeof(uint_least32_t)];
			if (str[0] == Magnitude::SIGNED) {
				this->_size = str.size() - 1;
				this->signal = Magnitude::SIGNED;
				size_t idx = str.size() - SIZE_DOUBLE_LIMITS_NUM;
				this->values_t[0] = std::stoul(str.substr(1, idx));
				this->values_t[1] = std::stoul(str.substr(idx, SIZE_LIMITS_NUM));
				this->values_t[2] = std::stoul(str.substr(idx + SIZE_LIMITS_NUM, SIZE_LIMITS_NUM));
			}
			else
			{
				this->_size = str.size();
				this->signal = Magnitude::UNSIGNED;
				size_t idx = str.size() - SIZE_DOUBLE_LIMITS_NUM;
				this->values_t[0] = std::stoul(str.substr(0, idx));
				this->values_t[1] = std::stoul(str.substr(idx, SIZE_LIMITS_NUM));
				this->values_t[2] = std::stoul(str.substr(idx + SIZE_LIMITS_NUM, SIZE_LIMITS_NUM));
			}			
		}
		else if (str.size() > SIZE_LIMITS_NUM) {
			this->_size = str.size();
			this->signal = Magnitude::SIGNED;
			this->_nodes = 2;
			this->values_t = new uint_least32_t[this->_nodes * sizeof(uint_least32_t)];
			size_t idx = str.size() - SIZE_LIMITS_NUM;
			this->values_t[0] = std::stoul(str.substr(1, idx));
			this->values_t[1] = std::stoul(str.substr(idx, SIZE_LIMITS_NUM));
		}
		else {
			this->_size = str.size();
			this->signal = Magnitude::SIGNED;
			this->_nodes = 1;
			this->values_t = new uint_least32_t[this->_nodes * sizeof(uint_least32_t)];
			this->values_t[0] = std::stoul(str);
		}
	}

	inline BigInt::BigInt(unsigned long num)
	{
		std::string str = std::to_string(num);
		this->_size = str.size();
		this->signal = Magnitude::UNSIGNED;
		this->_nodes = 1;
		this->values_t = new uint_least32_t[this->_nodes * sizeof(uint_least32_t)];
		this->values_t[0] = num;
	}

	inline BigInt::BigInt(long num)
	{
		std::string str = std::to_string(num);
		if (num >= 0) {
			this->_size = str.size();
			this->signal = Magnitude::UNSIGNED;
			this->_nodes = 1;
			this->values_t = new uint_least32_t[this->_nodes * sizeof(uint_least32_t)];
			this->values_t[0] = num;
		}
		else {
			this->_size = str.size() - 1;
			this->signal = Magnitude::SIGNED;
			this->_nodes = 1;
			this->values_t = new uint_least32_t[this->_nodes * sizeof(uint_least32_t)];
			this->values_t[0] = num*(-1);
		}
	}

	inline BigInt::BigInt(BigInt &&other)
	{
		this->_size = other.lenght();
		this->signal = other.signal;
		this->_nodes = other.getNumNodes();
		this->values_t = new uint_least32_t[this->_nodes * sizeof(uint_least32_t)];
		for (size_t i = 0; i < this->_size; i++) {
			this->values_t[i] = other.values_t[i];
		}
	}

	inline std::string BigInt::toString()
	{
		std::string s = std::to_string(this->values_t[0]);
		std::stringstream stream;
		bool first_node = true;
		if (!this->is_empty()) {
			for (size_t i = 0; i < this->_nodes; i++)
			{
				if (first_node) {
					if (this->is_sinalized()) {
						stream << '-';
					}
					stream << this->values_t[i];
					first_node = false;
				}
				else {
					stream.width(this->_archbits * sizeof(char));
					stream.fill('0');
					stream << this->values_t[i];
				}
			}
			s = stream.str();		
		}
		return s.data();
	}

	inline size_t BigInt::getNumNodes() const
	{
		return this->_nodes;
	}

	inline size_t BigInt::lenght() const
	{
		return this->_size;
	}

	inline size_t BigInt::size() const
	{
		return this->_size;
	}

	inline bool BigInt::is_sinalized()
	{
		return  (this->signal == Magnitude::SIGNED);
	}

	inline bool BigInt::is_empty()
	{
		return (this->_nodes == 0);
	}

	bool ether::operator==(const BigInt & lhs, const BigInt & rhs)
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

	bool ether::operator==(int & lhs, const BigInt & rhs)
	{
		return ether::BigInt(lhs) == rhs;
	}

	bool ether::operator==(const BigInt & lhs, int & rhs)
	{
		return lhs == ether::BigInt(rhs);
	}

	bool ether::operator!=(const BigInt & lhs, const BigInt & rhs)
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

	bool ether::operator!=(int & lhs, const BigInt & rhs)
	{
		return ether::BigInt(lhs) != rhs;
	}

	bool ether::operator!=(const BigInt & lhs, int & rhs)
	{
		return lhs != ether::BigInt(rhs);
	}

	bool ether::operator<(const BigInt & lhs, const BigInt & rhs)
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

	bool ether::operator>(const BigInt & lhs, const BigInt & rhs)
	{
		if (lhs.getNumNodes() < rhs.getNumNodes()) {
			return false;
		}
		else if (lhs.getNumNodes() == rhs.getNumNodes()) {
			for (size_t i = 0; i < lhs.getNumNodes(); i++) {
				if (lhs.values_t[i] < rhs.values_t[i]) {
					return false;
				}
			}
		}
		return true;
	}

	bool ether::operator<=(const BigInt & lhs, const BigInt & rhs)
	{
		return (lhs < rhs) || (lhs == rhs);
	}

	bool ether::operator>=(const BigInt & lhs, const BigInt & rhs)
	{
		return (lhs > rhs) || (lhs == rhs);
	}

	inline BigInt::~BigInt()
	{
		delete[] values_t;
	}
}
#endif
