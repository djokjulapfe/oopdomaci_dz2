#include <algorithm>
#include "BigDecimal.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

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
	const BigDecimal *a = this;
	if (a->sign != b->sign) {
		BigDecimal bneg = b->neg();
		return a->sub(&bneg);
	} else {
		long maxidx = MAX(a->maxIdx(), b->maxIdx());
		long minidx = MIN(a->minIdx(), b->minIdx());
		int carry = 0;
		std::string ret_s = "";
		for (long i = minidx; i <= maxidx + 1; ++i) {
			int sum = a->numAt(i) + b->numAt(i) + carry;
			ret_s.push_back('0' + sum % 10);
			carry = sum / 10;
		}
		long t_exp = maxidx;
		while (t_exp < -1) {
			ret_s.push_back('0');
			t_exp++;
		}
		std::reverse(ret_s.begin(), ret_s.end());
		while (t_exp > static_cast<long>(ret_s.length() - 2)) {
			ret_s.push_back('0');
		}
		ret_s.insert(t_exp + 2, ".");
		if (a->sign == -1) {
			ret_s.insert(0, "-");
		}
		return BigDecimal(ret_s.c_str());
	}
}

BigDecimal BigDecimal::sub(const BigDecimal *b) const {
	const BigDecimal *a = this;
	if (a->sign != b->sign) {
		BigDecimal bneg = b->neg();
		return a->add(&bneg);
	} else {
		if (a->sign == 1) {
			if (b->greater(a)) {
				BigDecimal ret = b->sub(a);
				return ret.neg();
			}
		} else {
			if (a->greater(b)) {
				BigDecimal ret = b->sub(a);
				return ret.neg();
			}
		}
		long maxidx = MAX(a->maxIdx(), b->maxIdx());
		long minidx = MIN(a->minIdx(), b->minIdx());
		int carry = 0;
		std::string ret_s = "";
		for (long i = minidx; i <= maxidx + 1; ++i) {
			int sum = a->numAt(i) - b->numAt(i) + carry;
			ret_s.push_back('0' + (sum + 10) % 10);
			carry = (sum - 9) / 10;
		}
		long t_exp = maxidx;
		while (t_exp < -1) {
			ret_s.push_back('0');
			t_exp++;
		}
		std::reverse(ret_s.begin(), ret_s.end());
		while (t_exp > static_cast<long>(ret_s.length() - 2)) {
			ret_s.push_back('0');
		}
		ret_s.insert(t_exp + 2, ".");
		if (a->sign == -1) {
			ret_s.insert(0, "-");
		}
		return BigDecimal(ret_s.c_str());
	}
}

BigDecimal BigDecimal::abs() const {
	BigDecimal ret(*this);
	ret.sign = 1;
	return ret;
}

bool BigDecimal::greater(const BigDecimal *b) const {
	if (sign != b->sign) {
		return sign > b->sign;
	} else if (exp != b->exp) {
		if (exp > b->exp) {
			return sign == 1;
		} else {
			return sign == -1;
		}
	} else {
		for (int i = maxIdx(); i >= MIN(minIdx(), b->minIdx()); --i) {
			if (numAt(i) > b->numAt(i)) {
				return sign == 1;
			} else if (numAt(i) < b->numAt(i)) {
				return sign == -1;
			}
		}
	}
	return false;
}

bool BigDecimal::less(const BigDecimal *b) const {
	if (sign != b->sign) {
		return sign < b->sign;
	} else if (exp != b->exp) {
		if (exp < b->exp) {
			return sign == 1;
		} else {
			return sign == -1;
		}
	} else {
		for (int i = maxIdx(); i >= MIN(minIdx(), b->minIdx()); --i) {
			if (numAt(i) < b->numAt(i)) {
				return sign == 1;
			} else if (numAt(i) > b->numAt(i)) {
				return sign == -1;
			}
		}
	}
	return false;
}

bool BigDecimal::equals(const BigDecimal *b) const {
	if (sign == b->sign && exp == b->exp) {
		for (int i = maxIdx(); i >= MIN(minIdx(), b->minIdx()); --i) {
			if (numAt(i) != b->numAt(i)) {
				return false;
			}
		}
		return true;
	} else return false;
}

BigDecimal BigDecimal::shl(int n) const {
	BigDecimal ret(*this);
	ret.exp -= n;
	return ret;
}

BigDecimal BigDecimal::shr(int n) const {
	BigDecimal ret(*this);
	ret.exp += n;
	return ret;
}

BigDecimal BigDecimal::rmd(int *n) const {
	BigDecimal ret(*this);
	ret.exp = mantis.length();
	return ret;
}

BigDecimal::BigDecimal(const BigDecimal &bigDecimal) {
	exp = bigDecimal.exp;
	sign = bigDecimal.sign;
	mantis = bigDecimal.mantis;
}

BigDecimal BigDecimal::neg() const {
	BigDecimal ret(*this);
	ret.sign *= -1;
	return ret;
}

std::ostream &operator<<(std::ostream &out, const BigDecimal &bigDecimal) {
	out << bigDecimal.toString();
	return out;
}

BigDecimal::BigDecimal() {
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

