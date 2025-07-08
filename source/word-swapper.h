#include <libc.h>
#include <stdio.h>
#include <assert.h>

#define exFile       "wordlist.txt"

void zero(uint8_t*, uint16_t);
int create_wsFile(uint8_t*, uint8_t*);
int word_replacer(uint8_t*, uint8_t*, uint8_t*);
int ws_program(int, char**);
int main(int, char**);