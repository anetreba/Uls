#include "libmx.h"

int mx_count_words(const char *str, char c) {
	int in_word = 0;
	int count = 0;

	if (str) { 
		for (int i = 0; str[i]; i++) {
			if (str[i] != c && in_word == 0)
				in_word = 1;
			if (str[i] == c  && in_word == 1) {
				count++;
				in_word = 0;
			}
		}
		return in_word ? ++count : count;
	}
	return -1;
}
