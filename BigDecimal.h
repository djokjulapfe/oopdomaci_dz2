#ifndef DZ2_BIGDECIMAL_H
#define DZ2_BIGDECIMAL_H

#include <iostream>

/**
 * @brief Class can store large decimal numbers.
 * TODO: override operators +, -, ==, !=, <, >, <=, >=, -, +, <<, >>, >>=
 */

class BigDecimal {

public:
	/**
	 * @brief Main constructor class
	 * @param num a string containing a decimal number
	 */
	BigDecimal(const char *num);

	/**
	 * @brief Standard destructor that deletes the internal char array
	 */
	~BigDecimal();

	/**
	 * @brief Adds two numbers
	 * @param b number to be added
	 * @return the sum of b and this
	 */
	BigDecimal add(const BigDecimal *b) const;

	/**
	 * @brief Subtracts two numbers
	 * @param b number to be subtracted
	 * @return the difference this - b
	 */
	BigDecimal sub(const BigDecimal *b) const;

	/**
	 * @brief Calculates the absolute value of a number
	 * @return the absolute number
	 */
	BigDecimal abs() const;

	/**
	 * @brief Checks if this > b
	 * @param b number to be checked against
	 * @return true iff this > b
	 */
	bool greater(const BigDecimal *b) const;

	/**
	 * @brief Checks if this < b
	 * @param b number to be checked agaianst
	 * @return true iff this < b
	 */
	bool less(const BigDecimal *b) const;

	/**
	 * @brief Checks if two numbers are equal
	 * @param b number to be checked against
	 * @return true iff this == b
	 */
	bool equals(const BigDecimal *b) const;

	/**
	 * @brief Shifts the number left n times
	 * @param n number of times to be shifted left
	 * @return the number shifted n times to the left
	 */
	BigDecimal shl(int n) const;

	/**
	 * @brief Shifts the number right n times
	 * @param n number of times to be shifted right
	 * @return the number shifted n times to the right
	 */
	BigDecimal shr(int n) const;

	/**
	 * @brief Shifts the number so that the decimal point gets erased
	 * @param n the number of times the number is shifted
	 * @return the number without the decimal point
	 */
	BigDecimal rmd(int *n) const;

	/**
	 * @brief Copy constructor that safely copies a BigDecimal
	 * @param bigDecimal the number to be copied
	 */
	BigDecimal(const BigDecimal &bigDecimal);

	const BigDecimal operator=(const BigDecimal &bigDecimal);

	const BigDecimal operator+(const BigDecimal &bigDecimal) const;

	const BigDecimal operator+() const;

	const BigDecimal operator+=(const BigDecimal &bigDecimal);

	const BigDecimal operator-(const BigDecimal &bigDecimal) const;

	const BigDecimal operator-() const;

	const BigDecimal operator-=(const BigDecimal &bigDecimal);

	bool operator==(const BigDecimal &bigDecimal) const;

	bool operator>(const BigDecimal &bigDecimal) const;

	bool operator>=(const BigDecimal &bigDecimal) const;

	bool operator<(const BigDecimal &bigDecimal) const;

	bool operator<=(const BigDecimal &bigDecimal) const;

	const BigDecimal operator<<(const int &n) const;

	const BigDecimal operator>>(const int &n) const;

	const BigDecimal operator>>=(int *n) const;

	BigDecimal();

private:

	/**
	 * @brief Calculates the negative of a number
	 * @return -this
	 */
	BigDecimal neg() const;

	/**
	 * @brief Helper function for transforming logical indices to memory
	 * @param idx logical index
	 * @return number at logical index
	 */
	int numAt(long idx) const {
		// convert logical index to memory index
		long char_idx = exp - idx - 1;

		// check if memory index exceeds string indices
		if (char_idx < 0 || char_idx >= mantis.length()) return 0;
		else return mantis[char_idx] - '0';
	}

	/**
	 * @return logical index of the first digit
	 */
	long maxIdx() const {
		return exp - 1;
	}

	/**
	 * @return logical index of the last digit
	 */
	long minIdx() const {
		return exp - mantis.length();
	}

	std::string toString() const {
		std::string ret;
		ret = sign == -1 ? "-" : "";
		if (exp >= (int) mantis.length()) {
			ret.append(mantis);
			ret.append(std::string(exp - mantis.length(), '0'));
		} else if (exp < 1) {
			ret.append("0.");
			ret.append(std::string(-exp, '0'));
			ret.append(mantis);
		} else {
			std::string t = mantis;
			t.insert(exp, ".");
			ret.append(t);
		}
		return ret;
	}

	int sign; /* Sign of the big decimal. Can take values of -1 and 1. */
	long exp; /* Exponent of the big decimal. */
	std::string mantis; /* Mantis of the big number */

	/**
	 * @brief function for std::ostream operator<< overloading
	 * @return std::ostream that can print a BigDecimal
	 */
	friend std::ostream &operator<<(std::ostream &, const BigDecimal &);
};

#endif //DZ2_BIGDECIMAL_H
