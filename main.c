//GitHub URL: https://github.com/OlakayL/Comp-Org-Arch-A1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "conversions.h"

int main (void){
  FILE *file = fopen("a1_test_file.txt", "r");
  if (file == NULL) {
  printf("Error: Could not open file\n");
  return 1;
  }
  char line[256];
  int test_number = 1;
  int total_tests = 0;
  int passed_tests = 0;
  
    while (fgets(line, sizeof(line), file)) {
        // Skip comments and empty lines
        if (line[0] == '#' || line[0] == '\n') continue;

        char func[32], expected[128], output[128];
        unsigned long in1, in2;

	 // Case: 4 items (func in1 in2 expected)
        if (sscanf(line, "%31s %lu %lu %127s", func, &in1, &in2, expected) == 4) {
            if (strcmp(func, "div_convert") == 0) {
                div_convert(in1, in2, output);
            } else if (strcmp(func, "sub_convert") == 0) {
                sub_convert(in1, in2, output);
            }
	    int pass = strcmp(expected, output) == 0;
            printf("Test %d: %s(%lu, %lu)-> Expected: \"%s\", Got: \"%s\" [%s]\n",
                   test_number, func, in1, in2,
                   expected, output,
                   strcmp(expected, output) == 0 ? "PASS" : "FAIL");
	    
	    total_tests++;
            if (pass) passed_tests++;
        }
        // Case: 3 items (func in1 expected)
        else if (sscanf(line, "%31s %lu %127s", func, &in1, expected) == 3) {
            if (strcmp(func, "print_tables") == 0) {
	      print_tables(in1, output); // assume you change print_tables to accept buffer
	        int pass = strcmp(expected, output) == 0;
                printf("Test %d: %s(%lu)-> [FORMATTED OUTPUT CHECK] [%s]\n",
                        test_number, func, in1,
                       strcmp(expected, output) == 0 ? "PASS" : "FAIL");

		total_tests++;
		if (pass) passed_tests++;
            }
        }

        test_number++;
    }

  fclose(file);
  printf("\nSummary: %d/%d tests passed\n", passed_tests, total_tests);
  return 0;
}
