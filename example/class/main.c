#include <stdio.h>
#include "myclass.h"

int main(void) {
    MyClass *mc = myclass_init(0);
    printf("mc = %d\n", mc->get());
    mc->set(1);
    printf("mc = %d\n", mc->get());
    myclass_free(&mc);
}
