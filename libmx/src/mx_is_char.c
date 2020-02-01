#include "libmx.h"

bool mx_is_char(char *s) {
	for (int i = 0; s[i]; i++) {
		if (!((s[i] >= 65 && s[i] <= 90)
			|| (s[i] >= 97 && s[i] <= 122)))
			return false;
	}
	return true;
}
