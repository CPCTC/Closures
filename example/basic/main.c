#include "../../closures.h"
#include <stdio.h>

void print_val(void);

int main(void) {
    // My program's data
    int four = 4;
    int two = 2;

    // Invokes 'print_val' in an environment where CLSR_DATA is '&four'.
    void (*print_four)(void) = clsr_capture(print_val, &four);
    print_four();

    // And again, where CLSR_DATA is '&two':
    void (*print_two)(void) = clsr_capture(print_val, &two);
    print_two();

    // When you're done, you must free your closures:
    clsr_release((void **) &print_four);
    clsr_release((void **) &print_two);

    return 0;
}

void print_val(void) {
    int *data = CLSR_DATA;      // Access the captured data
    // Important: Most function calls will clobber CLSR_DATA.
    // See the documentation for full details.
    printf("Data = %d\n", *data);
}
