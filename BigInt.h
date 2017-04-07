#ifndef EINT_H
#define EINT_H

#include <string>
#include <cstdint>
//#include <memory>
//#include <cmath>
//#include <iostream>
#include <sstream>
//#include <iomanip>

#pragma once

#define BIGINT(A) #A

#define LIMITS_NUM 999999999
#define LIMITS_MAX 1000000000

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
		explicit BigInt(const std::string num);
		explicit BigInt(const BigInt &other);
		//explicit BigInt(size_t num);
		explicit BigInt(BigInt &&other);

		uint_least32_t* values_t;

		const char* toString();
		size_t getNumNodes() const;

		friend bool operator==(const BigInt& lhs, const BigInt& rhs) {
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
		//friend bool operator==(int& lhs, const BigInt& rhs) {
		//	return true;
		//}

		//friend bool operator==(const BigInt& lhs, int& rhs) {
		//	return true;
		//}

		friend bool operator!=(const BigInt& lhs, const BigInt& rhs) { 
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

		//friend bool operator!=(int& lhs, const BigInt& rhs) {
		//	return true;
		//}

		//friend bool operator!=(const BigInt& lhs, int& rhs) {
		//	return true;
		//}

		friend bool operator<(const BigInt& lhs, const BigInt& rhs) { 
			if (lhs.getNumNodes() > rhs.getNumNodes()) {
				return false;
			} else if(lhs.getNumNodes() == rhs.getNumNodes()){
				for (size_t i = 0; i < lhs.getNumNodes(); i++) {
					if (lhs.values_t[i] > rhs.values_t[i]) {
						return false;
					}
				}
			}
			return true;
		}
		friend bool operator>(const BigInt& lhs, const BigInt& rhs) { 
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

		friend bool operator<=(const BigInt& lhs, const BigInt& rhs) { 
			return (lhs < rhs) || (lhs == rhs);
		}

		friend bool operator>=(const BigInt& lhs, const BigInt& rhs) {
			return (lhs > rhs) || (lhs == rhs);
		}

		virtual ~BigInt();
		

	private:
		
		size_t _bits = 0;
		size_t _nodes = 0;
		unsigned char _sign = Magnitude::UNSIGNED;
		bool _empty = true;

		const int _archbits = 9;
	};

	BigInt::BigInt() {
		this->_bits = 1; //Only '0'
		this->_sign = Magnitude::UNSIGNED;
		this->_nodes = 1;
		this->values_t = new uint_least32_t[this->_nodes * sizeof(uint_least32_t)];
		this->values_t[0] = 0;
	}

	inline BigInt::BigInt(char const * num)
	{
		if (num[0] == static_cast<char>(Magnitude::SIGNED)) {
			this->_sign = Magnitude::SIGNED;
			for (this->_bits = 1; num[this->_bits] != '\0'; this->_bits++);
		}
		else {
			this->_sign = Magnitude::UNSIGNED;
			for (this->_bits = 0; num[this->_bits] != '\0'; this->_bits++);
		}
		
		this->_nodes = static_cast<size_t>(ceil(static_cast<double>(this->_bits) / static_cast<double>(this->_archbits)));
		//if (this->_nodes <= 0) {
		//	this->_nodes = 1;
		//}

		this->values_t = new uint_least32_t[this->_nodes * sizeof(uint_least32_t)];
		std::string s(num);
		size_t i, j;
		for (i = s.size(), j = this->_nodes - 1; i >= this->_archbits && j >= 0; i -= this->_archbits, j--)
		{
			this->values_t[j] = stoi(s.substr(i - this->_archbits, this->_archbits));
		}

		size_t v = s.size() % this->_archbits;
		if (v) {
			this->values_t[j] = stoi(s.substr(0, v));
		}
		this->_empty = false;
	}

	inline BigInt::BigInt(const std::string num)
	{
		if (num[0] == static_cast<char>(Magnitude::SIGNED)) {
			this->_sign = Magnitude::SIGNED;
			for (this->_bits = 1; num[this->_bits] != '\0'; this->_bits++);
		}
		else {
			this->_sign = Magnitude::UNSIGNED;
			for (this->_bits = 0; num[this->_bits] != '\0'; this->_bits++);
		}

		this->_nodes = static_cast<size_t>(ceil(static_cast<double>(this->_bits) / static_cast<double>(this->_archbits)));
		//if (this->_nodes <= 0) {
		//	this->_nodes = 1;
		//}

		this->values_t = (uint_least32_t *)calloc(this->_nodes, sizeof(uint_least32_t));
		std::string s(num);
		size_t i, j;
		for (i = s.size(), j = this->_nodes - 1; i >= this->_archbits && j >= 0; i -= this->_archbits, j--)
		{
			this->values_t[j] = stoi(s.substr(i - this->_archbits, this->_archbits));
		}

		size_t v = s.size() % this->_archbits;
		if (v) {
			this->values_t[j] = stoi(s.substr(0, v));
		}
		this->_empty = false;
	}

	inline BigInt::BigInt(const BigInt & other)
	{
	}

	//inline BigInt::BigInt(int * num)
	//{
	//}

	inline BigInt::BigInt(BigInt && other)
	{
	}

	inline const char *BigInt::toString()
	{
		static std::string s = std::to_string(this->values_t[0]);
		std::stringstream stream;
		bool first_node = true;
		if (!this->_empty) {
			for (size_t i = 0; i < this->_nodes; i++)
			{
				if (this->values_t[i] > 0) {
					if (first_node) {
						size_t v = s.size() % this->_archbits;
						stream.width(v * sizeof(char));
						stream << std::right << this->values_t[i];
						first_node = false;
					}
					else {
						stream.fill('0');
						stream.width(this->_archbits * sizeof(char));
						stream << std::right << this->values_t[i];
					}
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

	inline BigInt::~BigInt()
	{
	}

}
#endif
