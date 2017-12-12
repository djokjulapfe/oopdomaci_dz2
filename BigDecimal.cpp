#include <algorithm>
#include "BigDecimal.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

// TODO: comment functions

BigDecimal::BigDecimal(const char *num) : mantis(num), sign(1) {

	// check sign
	if (mantis[0] == '-') {
		sign = -1;
		mantis.erase(0, 1);
	} else if (mantis[0] == '+') {
		mantis.erase(0, 1);
	}

	// find and calculate exponent
	exp = (int) mantis.find(".");
	if (exp == std::string::npos)
		exp = (int) mantis.length();
	mantis.erase(static_cast<unsigned long>(exp), 1);

	// errase all leading zeros
	auto last = MIN(mantis.find_first_not_of('0'), mantis.length());
	mantis.erase(0, last);

	// erase all trailing zeros
	auto first = MAX(mantis.find_last_not_of('0'), 0);
	mantis.erase(first + 1, mantis.length());

	// update exponent after erasing zeros
	exp -= last;

	// if the mantis has no symbols left, it means the number passed is 0
	if (mantis == "") {
		exp = 1;
		sign = 1;
		mantis = "0";
	}
}

BigDecimal::~BigDecimal() {
	// there is no dynamic memory allocations
}

BigDecimal BigDecimal::add(const BigDecimal *b) const {

	// helper pointer for this
	const BigDecimal *a = this;

	if (a->sign != b->sign) {

		// if the signs are different, then a + b = a - (-b)
		BigDecimal bneg = b->neg();
		return a->sub(&bneg);

	} else {

		// first and last index for adding
		long maxidx = MAX(a->maxIdx(), b->maxIdx());
		long minidx = MIN(a->minIdx(), b->minIdx());

		// stores the carry of a digit addition
		int carry = 0;

		// temporary return string
		std::string ret_s = "";

		// main adding loop
		for (long i = minidx; i <= maxidx + 1; ++i) {

			// add two digits and the carry (initially carry = 0)
			int sum = a->numAt(i) + b->numAt(i) + carry;

			// add the number to the last place of the string (storing it inverted)
			ret_s.push_back('0' + sum % 10);

			// calculate the carry for the next addition
			carry = sum / 10;
		}

		// first guess of the exponent
		long t_exp = maxidx;

		while (t_exp < -1) {
			// if the exponent is negative, add zeros until the decimal point
			ret_s.push_back('0');
			t_exp++;
		}

		// reverse the string, since it was stored inverted
		std::reverse(ret_s.begin(), ret_s.end());

		while (t_exp > static_cast<long>(ret_s.length() - 2)) {

			// if the exponent is larger than the number of significant digits, add zeros until the decimal point
			ret_s.push_back('0');

		}

		// add the decimal point
		ret_s.insert(t_exp + 2, ".");

		// add the negative sign if the number is positive
		if (a->sign == -1) {
			ret_s.insert(0, "-");
		}

		// return the BigDecimal formed from a char*
		return BigDecimal(ret_s.c_str());
	}
}

BigDecimal BigDecimal::sub(const BigDecimal *b) const {

	// helper pointer for this
	const BigDecimal *a = this;

	if (a->sign != b->sign) {

		// if the signs are different, then a + b = a - (-b)
		BigDecimal bneg = b->neg();
		return a->add(&bneg);

	} else {

		if (a->sign == 1) {
			if (b->greater(a)) {
				// if b > a >= 0, then return -(b - a)
				BigDecimal ret = b->sub(a);
				return ret.neg();
			}
		} else {
			if (a->greater(b)) {
				// if 0 > a > b, then return -(b - a)
				BigDecimal ret = b->sub(a);
				return ret.neg();
			}
		}

		// first and last index for adding
		long maxidx = MAX(a->maxIdx(), b->maxIdx());
		long minidx = MIN(a->minIdx(), b->minIdx());

		// stores the carry of a digit addition
		int carry = 0;

		// temporary return string
		std::string ret_s = "";

		// main subtracting loop
		for (long i = minidx; i <= maxidx + 1; ++i) {

			// subtracts two digits and the carry (initially carry = 0)
			int sum = a->numAt(i) - b->numAt(i) + carry;

			// add the number to the last place of the string (storing it inverted)
			ret_s.push_back('0' + (sum + 10) % 10);

			// calculate the carry for the next addition
			carry = (sum - 9) / 10;
		}

		// first guess of the exponent
		long t_exp = maxidx;

		while (t_exp < -1) {

			// if the exponent is negative, add zeros until the decimal point
			ret_s.push_back('0');
			t_exp++;

		}

		// reverse the string, since it was stored inverted
		std::reverse(ret_s.begin(), ret_s.end());

		while (t_exp > static_cast<long>(ret_s.length() - 2)) {

			// if the exponent is larger than the number of significant digits, add zeros until the decimal point
			ret_s.push_back('0');

		}

		// add the decimal point
		ret_s.insert(t_exp + 2, ".");

		// add the negative sign if the number is positive
		if (a->sign == -1) {
			ret_s.insert(0, "-");
		}

		// return the BigDecimal formed from a char*
		return BigDecimal(ret_s.c_str());
	}
}

BigDecimal BigDecimal::abs() const {

	// temporary return value
	BigDecimal ret(*this);

	// remove the sign if it exists
	ret.sign = 1;

	// return the absolute value
	return ret;
}

bool BigDecimal::greater(const BigDecimal *b) const {

	if (sign != b->sign) {

		// if a is positive and b is negative than a > b
		return sign > b->sign;

	} else if (exp != b->exp) {

		// if the numbers have equal sign, the exponent changes the value
		if (exp > b->exp) {

			// if the exponent of a is larger then b, then a > b iff sign(a) == 1
			return sign == 1;

		} else {

			// if the exponent of b is larger then a, then a > b iff sign(a) == -1
			return sign == -1;

		}

	} else {

		// find the first different digit
		for (long i = maxIdx(); i >= MIN(minIdx(), b->minIdx()); --i) {

			// if the numbers are different, the answer is known
			if (numAt(i) > b->numAt(i)) {

				// if the mantis of a is greater than b, then a > b iff sign(a) == 1
				return sign == 1;

			} else if (numAt(i) < b->numAt(i)) {

				// if the mantis of b is greater than a, then a > b iff sign(a) == -1
				return sign == -1;

			}

		}

	}

	// if the numbers are equal, one is not greater than the other
	return false;
}

bool BigDecimal::less(const BigDecimal *b) const {

	if (sign != b->sign) {

		// if a is negative and b is positive than a < b
		return sign < b->sign;

	} else if (exp != b->exp) {

		// if the numbers have equal sign, the exponent changes the value
		if (exp < b->exp) {

			// if the exponent of a is less then b, then a < b iff sign(a) == 1
			return sign == 1;

		} else {

			// if the exponent of b is less then a, then a < b iff sign(a) == -1
			return sign == -1;

		}

	} else {

		// find the first different digit
		for (long i = maxIdx(); i >= MIN(minIdx(), b->minIdx()); --i) {

			// if the numbers are different, the answer is known
			if (numAt(i) < b->numAt(i)) {

				// if the mantis of a is less than b, then a < b iff sign(a) == 1
				return sign == 1;

			} else if (numAt(i) > b->numAt(i)) {

				// if the mantis of b is less than a, then a < b iff sign(a) == -1
				return sign == -1;

			}

		}

	}

	// if the numbers are equal, one is not less than the other
	return false;
}

bool BigDecimal::equals(const BigDecimal *b) const {

	// check if the values have the same sign and exponent
	if (sign == b->sign && exp == b->exp) {

		// find the first digit that differs, if it exists
		for (int i = maxIdx(); i >= MIN(minIdx(), b->minIdx()); --i) {

			// if there is a digit that differs, the numbers aren't equal
			if (numAt(i) != b->numAt(i)) {
				return false;
			}

		}

		// if no different digits are found, the numbers are the same
		return true;
	} else {
		// if the values differ by sign or exponent, return false
		return false;
	}

}

BigDecimal BigDecimal::shl(int n) const {

	// temporary return value
	BigDecimal ret(*this);

	// move the exponent n times
	ret.exp -= n;

	// return the value with the moved exponent
	return ret;

}

BigDecimal BigDecimal::shr(int n) const {

	// temporary return value
	BigDecimal ret(*this);

	// move the exponent n times
	ret.exp += n;

	// return the value with the moved exponent
	return ret;

}

BigDecimal BigDecimal::rmd(int *n) const {

	// temporary return value
	BigDecimal ret(*this);

	// move the exponent to one past the last digit
	ret.exp = mantis.length();

	// return the value with the moved exponent
	return ret;

}

BigDecimal::BigDecimal(const BigDecimal &bigDecimal) {

	// copies all the fields
	exp = bigDecimal.exp;
	sign = bigDecimal.sign;
	mantis = bigDecimal.mantis;

}

BigDecimal BigDecimal::neg() const {

	// temporary return value
	BigDecimal ret(*this);

	// change the sign
	ret.sign *= -1;

	// return the value with the different sign
	return ret;

}

std::ostream &operator<<(std::ostream &out, const BigDecimal &bigDecimal) {

	// use the toString helper method for printing
	out << bigDecimal.toString();
	return out;

}

BigDecimal::BigDecimal() {

	// default to 0
	exp = 1;
	sign = 1;
	mantis = "0";

}

const BigDecimal BigDecimal::operator=(const BigDecimal &bigDecimal) {
	exp = bigDecimal.exp;
	sign = bigDecimal.sign;
	mantis = bigDecimal.mantis;
	return *this;
}

const BigDecimal BigDecimal::operator+(const BigDecimal &bigDecimal) const {
	BigDecimal ret = this->add(&bigDecimal);
	return ret;
}

const BigDecimal BigDecimal::operator+() const {
	return this->abs();
}

const BigDecimal BigDecimal::operator+=(const BigDecimal &bigDecimal) {
	*this = *this + bigDecimal;
	return *this;
}

const BigDecimal BigDecimal::operator-(const BigDecimal &bigDecimal) const {
	BigDecimal ret = this->sub(&bigDecimal);
	return ret;
}

const BigDecimal BigDecimal::operator-() const {
	return this->neg();
}

const BigDecimal BigDecimal::operator-=(const BigDecimal &bigDecimal) {
	*this = *this - bigDecimal;
	return *this;
}

bool BigDecimal::operator==(const BigDecimal &bigDecimal) const {
	return this->equals(&bigDecimal);
}

bool BigDecimal::operator>(const BigDecimal &bigDecimal) const {
	return this->greater(&bigDecimal);
}

bool BigDecimal::operator>=(const BigDecimal &bigDecimal) const {
	return !this->less(&bigDecimal);
}

bool BigDecimal::operator<(const BigDecimal &bigDecimal) const {
	return this->less(&bigDecimal);
}

bool BigDecimal::operator<=(const BigDecimal &bigDecimal) const {
	return !this->greater(&bigDecimal);
}

const BigDecimal BigDecimal::operator<<(const int &n) const {
	return this->shl(n);
}

const BigDecimal BigDecimal::operator>>(const int &n) const {
	return this->shr(n);
}

const BigDecimal BigDecimal::operator>>=(int *n) const {
	return this->rmd(n);
}

