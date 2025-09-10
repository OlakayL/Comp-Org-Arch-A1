#include <stdint.h>
#include <string.h>
#include <stdio.h>

void div_convert(uint32_t n, int base, char *out){
 
  char temp[65]; // Temporary buffer
  int pos = 0;
 
  // Handle zero case
  if (n == 0) {
    strcpy(out, "0");
    return;
  }
 
  // Extract digits from right to left
  while (n > 0) {
    int remainder = n % base;
    n = n / base;
 
  // Convert digit to character
    if (remainder < 10){
    temp[pos++] = '0' + remainder;
    }
  else{
    temp[pos++] = 'A' + (remainder- 10);
  }
  }
    
   // Reverse the result
    for (int i = 0; i < pos; i++) {
    out[i] = temp[pos - i - 1];
  }
    out[pos] = '\0';
}

void sub_convert(uint32_t n, int base, char *out) {
    char digits[] = "0123456789ABCDEF";
    char temp[65]; // Temporary buffer
    int pos = 0;

    // Handle zero case
    if (n == 0) {
        strcpy(out, "0");
        return;
    }

    // Find the highest power of base less than or equal to n
    int power = 1;
    while (power * base <= n && power * base > 0) {
        power *= base;
    }

    // Subtract powers from n
    while (power > 0) {
        int digit = n / power;
        temp[pos++] = digits[digit];
        n -= digit * power;
        power /= base;
    }

    temp[pos] = '\0';
    strcpy(out, temp);
}


void print_tables(uint32_t n, char*out){
   char bin[33], oct[12], hex[9];
   sprintf(out, "FORMATTED _OUTPUT");
 
  // Original number
  div_convert(n, 2, bin);
  div_convert(n, 8, oct);
  div_convert(n, 16, hex);
  printf("Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n",
  bin, oct, n, hex);
 
  // Left shift by 3
  uint32_t shifted = n << 3;
  div_convert(shifted, 2, bin);
  div_convert(shifted, 8, oct);
  div_convert(shifted, 16, hex);
  printf("Left Shift by 3: Binary=%s Octal=%s Decimal=%u Hex=%s\n",
  bin, oct, shifted, hex);
 
  // AND with 0xFF
  uint32_t masked = n & 0xFF;
  // ... similar pattern
  div_convert(masked, 2, bin);
  div_convert(masked, 8, oct);
  div_convert(masked, 16, hex);
  printf("AND with 0xFF: Binary=%s Octal=%s Decimal=%u Hex=%s\n",
  bin, oct, shifted, hex);
}
