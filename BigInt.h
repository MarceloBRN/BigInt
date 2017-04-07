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
		explicit BigInt(size_t num);
		explicit BigInt(BigInt &&other);

		uint_least32_t* values_t;
		Magnitude signal = Magnitude::UNSIGNED;

		const char* toString();
		size_t getNumNodes() const;
		size_t lenght() const;
		size_t size() const;
		bool is_sinalized();

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
		
		size_t _size = 0;
		size_t _nodes = 0;
		
		bool _empty = true;

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
		if (num[0] == static_cast<char>(Magnitude::SIGNED)) {
			this->signal = Magnitude::SIGNED;
			for (this->_size = 1; num[this->_size] != '\0'; this->_size++);
		}
		else {
			this->signal = Magnitude::UNSIGNED;
			for (this->_size = 0; num[this->_size] != '\0'; this->_size++);
		}
		
		this->_nodes = static_cast<size_t>(ceil(static_cast<double>(this->_size) / static_cast<double>(this->_archbits)));
		//if (this->_nodes <= 0) {
		//	this->_nodes = 1;
		//}

		this->values_t = new uint_least32_t[this->_nodes * sizeof(uint_least32_t)];
		std::string s(num);
		size_t i, j;
		for (i = s.size(), j = this->_nodes - 1; i >= this->_archbits && j >= 0; i -= this->_archbits, j--)
		{
			this->values_t[j] = std::stoi(s.substr(i - this->_archbits, this->_archbits));
		}

		size_t v = s.size() % this->_archbits;
		if (v) {
			this->values_t[j] = std::stoi(s.substr(0, v));
		}
		this->_empty = false;
	}

	inline BigInt::BigInt(const std::string num)
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
		//if (this->_nodes <= 0) {
		//	this->_nodes = 1;
		//}

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
		this->_empty = false;
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

	inline BigInt::BigInt(size_t num)
	{

	}

	inline BigInt::BigInt(BigInt &&other)
	{
		this->_size = 1; //Only '0'
		this->signal = Magnitude::UNSIGNED;
		this->_nodes = 1;
		this->values_t = new uint_least32_t[this->_nodes * sizeof(uint_least32_t)];
		this->values_t[0] = 0;
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

	inline BigInt::~BigInt()
	{
	}
}
#endif
