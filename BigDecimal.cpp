#include "BigDecimal.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

BigDecimal::BigDecimal(char *num) : mantis(num), sign(1) {

	if (mantis[0] == '-') {
		sign = -1;
		mantis.erase(0, 1);
	} else if (mantis[0] == '+') {
		mantis.erase(0, 1);
	}

	exp = (int) mantis.find(".");
	if (exp == std::string::npos)
		exp = (int) mantis.length();
	mantis.erase(static_cast<unsigned long>(exp), 1);

	auto last = MIN(mantis.find_first_not_of('0'), mantis.length());
	mantis.erase(0, last);

	auto first = MAX(mantis.find_last_not_of('0'), 0);
	mantis.erase(first + 1, mantis.length());

	exp -= last;

	std::cout << (sign == -1 ? "-" : "") << "0." << mantis << "*10^" << exp <<
	          std::endl;
}

BigDecimal::~BigDecimal() {
	// there is no dynamic memory allocations
}

BigDecimal BigDecimal::add(BigDecimal *b) {
	return BigDecimal(nullptr);
}

BigDecimal BigDecimal::sub(BigDecimal *b) {
	return BigDecimal(nullptr);
}

BigDecimal BigDecimal::abs() {
	BigDecimal ret(*this);
	ret.sign = 1;
	return ret;
}

bool BigDecimal::greater(BigDecimal *b) {
	return false;
}

bool BigDecimal::less(BigDecimal *b) {
	return false;
}

bool BigDecimal::equals(BigDecimal *b) {
	return false;
}

BigDecimal BigDecimal::shl(int n) {
	return BigDecimal(nullptr);
}

BigDecimal BigDecimal::shr(int n) {
	return BigDecimal(nullptr);
}

BigDecimal BigDecimal::rmd(int *n) {
	return BigDecimal(nullptr);
}

BigDecimal::BigDecimal(const BigDecimal &bigDecimal) {

}

BigDecimal BigDecimal::neg() {
	BigDecimal ret;
	ret.sign *= -1;
	return ret;
}

std::ostream &operator<<(std::ostream &out, const BigDecimal &bigDecimal) {
	out << bigDecimal.toString() << std::endl;
	return out;
}

BigDecimal::BigDecimal() {
	sign = 1;
	exp = 0;
	mantis = "0";
}
