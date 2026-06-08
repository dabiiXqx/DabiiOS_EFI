#include "utils.h"

void *kmemset(void *dest, int c, size_t n){
	unsigned char *ptr = (unsigned char *)dest;
	
	while(n--){
		*ptr++ = (unsigned char)c;
	}

	return dest;
}

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

char *itoa(int value, char str[]) {
	int digit;
	int i = 0;

	if(value == 0) {
		str[i] = '0';
		str[i++] = '\0';
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
