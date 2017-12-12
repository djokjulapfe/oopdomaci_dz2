#ifndef DZ2_BIGDECIMAL_H
#define DZ2_BIGDECIMAL_H

#include <iostream>

/**
 * @brief Class can store large decimal numbers.
 * TODO: standardize capitalization
 */

class BigDecimal {

public:
	/**
	 * @brief Main constructor
	 * @param num a string containing a decimal number
	 */
	BigDecimal(const char *num);

	/**
	 * @brief Standard destructor. Doesn't do anything since there is no dynamic memory
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
	 * @brief Calculates the absolute value of this
	 * @return the absolute value
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
	 * @param b number to be checked against
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
	 * @param n the number of times the number is shifted (mutable)
	 * @return the number without the decimal point
	 */
	BigDecimal rmd(int *n) const;

	/**
	 * @brief Copy constructor that safely copies a BigDecimal
	 * @param bigDecimal the number to be copied
	 */
	BigDecimal(const BigDecimal &bigDecimal);

	/**
	 * @brief standard assignment constructor (copies data)
	 * @param bigDecimal value to be assigned
	 * @return *this
	 */
	const BigDecimal operator=(const BigDecimal &bigDecimal);

	/**
	 * @brief calculates the sum of two values
	 * @param bigDecimal value to be summed with
	 * @return the sum of two values
	 */
	const BigDecimal operator+(const BigDecimal &bigDecimal) const;

	/**
	 * @brief calculates the absolute value of a number
	 * @return the absolute value of the number
	 */
	const BigDecimal operator+() const;

	/**
	 * @brief increments by a value
	 * @param bigDecimal value to be incremented by
	 * @return *this
	 */
	const BigDecimal operator+=(const BigDecimal &bigDecimal);

	/**
	 * @brief calculates the difference of two values
	 * @param bigDecimal the value to be decreased by
	 * @return the difference this - bigDecimal
	 */
	const BigDecimal operator-(const BigDecimal &bigDecimal) const;

	/**
	 * @brief calculates the negative value of a number
	 * @return the negative value of a number
	 */
	const BigDecimal operator-() const;

	/**
	 * @brief decrements by a value
	 * @param bigDecimal value to be decremented by
	 * @return *this
	 */
	const BigDecimal operator-=(const BigDecimal &bigDecimal);

	/**
	 * @brief checks whether two values are equal
	 * @param bigDecimal the value to be checked against
	 * @return true iff this == bigDecimal
	 */
	bool operator==(const BigDecimal &bigDecimal) const;

	/**
	 * @brief checks whether this is greater than a value
	 * @param bigDecimal the value to be checked against
	 * @return true iff this > bigDecimal
	 */
	bool operator>(const BigDecimal &bigDecimal) const;

	/**
	 * @brief checks whether this is greater than or equal to a value
	 * @param bigDecimal the value to be checked against
	 * @return true iff this >= bigDecimal
	 */
	bool operator>=(const BigDecimal &bigDecimal) const;

	/**
	 * @brief checks whether this is smaller than a value
	 * @param bigDecimal the value to be checked against
	 * @return true iff this < bigDecimal
	 */
	bool operator<(const BigDecimal &bigDecimal) const;

	/**
	 * @brief checks whether this is smaller than or equal to a value
	 * @param bigDecimal the value to be checked against
	 * @return true iff this <= bigDecimal
	 */
	bool operator<=(const BigDecimal &bigDecimal) const;

	/**
	 * @brief Shifts the number left n times
	 * @param n number of times to be shifted left
	 * @return the number shifted n times to the left
	 */
	const BigDecimal operator<<(const int &n) const;

	/**
	 * @brief Shifts the number right n times
	 * @param n number of times to be shifted right
	 * @return the number shifted n times to the right
	 */
	const BigDecimal operator>>(const int &n) const;

	/**
	 * @brief Shifts the number so that the decimal point gets erased
	 * @param n the number of times the number is shifted (mutable)
	 * @return the number without the decimal point
	 */
	const BigDecimal operator>>=(int *n) const;

private:

	/**
	 * @brief default constructor for internal use
	 */
	BigDecimal();

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

	/**
	 * @brief converts a BigDecimal to std::string
	 * @return value of the BigDecimal as a string
	 * TODO: comment function
	 */
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

	// Sign of the big decimal. Can take values of -1 and 1.
	int sign;

	// Exponent of the big decimal.
	long exp;

	// Mantis of the big number
	std::string mantis;

	/**
	 * @brief function for std::ostream operator<< overloading
	 * @return std::ostream that can print a BigDecimal
	 */
	friend std::ostream &operator<<(std::ostream &, const BigDecimal &);
};

#endif //DZ2_BIGDECIMAL_H
