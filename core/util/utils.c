#include "utils.h"

int strlen(char *s){
	int i = 0;
	while(*s != '\0'){
		i++;
		s++;
	}
	return i;
}
void reverse(char s[]){
	int c, i, j;
	for(i = 0, j = strlen(s) - 1; i < j; i++, j--){
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

uint64_t min(uint64_t a, uint64_t b) {
	return (a < b) ? a : b;
}

char *itoa(uint64_t value, char str[]) {
	int digit;
	int i = 0;

	if(value == 0) {
		str[i] = '0';
		str[++i] = '\0';
		return str;
	}
	while(value > 0){
		digit = value % 10;
		digit += '0';

		value /= 10;
		str[i] = digit;
		i++;
	}

	str[i] = '\0';
	reverse(str);
	return str;
}
