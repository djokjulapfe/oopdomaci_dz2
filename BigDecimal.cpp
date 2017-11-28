#include "BigDecimal.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

BigDecimal::BigDecimal(char *num) : mantis(num) {
	if (mantis[0] == '-') {
		sign = -1;
		mantis =
	}
}
