#include "string.h"

int strcmp(char *string1, char *string2){
    while (*string1 == *string2) {
        if (*string1 == '\0') {
            return 0;
        }
        ++string1;
        ++string2;
    }
    return *string1 - *string2;
}

int strlen(char* string){
    int i = 0;
    while(string[i] != '\0'){
        i++;
    }
    return i;
}

char* strstr(char* haystack, char* needle) {
	const char * out = 0;
	const char * ptr;
	const char * acc;
	const char * p;
	int s = strlen(needle);
	for (ptr = haystack; *ptr != '\0'; ++ptr) {
		int accept = 0;
		out = ptr;
		p = ptr;
		for (acc = needle; (*acc != '\0') && (*p != '\0'); ++acc) {
			if (*p == *acc) {
				accept++;
				p++;
			} else {
				break;
			}
		}
		if (accept == s) {
			return (char*)out;
		}
	}
	return 0;
}

void* memcpy(void* dest, void* src, int count){
    unsigned char* destptr = (unsigned char*)dest;
    unsigned char* srcptr = (unsigned char*)src;
    for(int i = 0; i < count; i++){
        destptr[i] = srcptr[i];
    }
    return destptr;
}

void* memset(void* dest, int value, int count){
    unsigned char* destptr = (unsigned char*)dest;
    for(int i = 0; i < count; i++){
        destptr[i] = value;
    }
    return destptr;
}