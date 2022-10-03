#include "myclass.h"
#include "../../closures.h"
#include <stdlib.h>

typedef struct {
    MyClass pub;
    int data;
} MyClass_private;

static int get(void);
static void set(int data);

MyClass *myclass_init(int data) {
    MyClass_private *mc = malloc(sizeof(MyClass_private));
    if (!mc) goto err0;

    mc->pub.get = clsr_capture(get, mc);
    if (!mc->pub.get) goto err1;

    mc->pub.set = clsr_capture(set, mc);
    if (!mc->pub.set) goto err2;

    mc->pub.set(data);
    return (MyClass *) mc;

err2:
    clsr_release((void **) &mc->pub.get);
err1:
    free(mc);
err0:
    return NULL;
}

void myclass_free(MyClass **hmc) {
    MyClass_private *mc = (MyClass_private *) *hmc;
    clsr_release((void **) &mc->pub.get);
    clsr_release((void **) &mc->pub.set);
    free(mc);
    *hmc = NULL;
}

int get(void) {
    MyClass_private *mc = CLSR_DATA;
    return mc->data;
}

void set(int data) {
    MyClass_private *mc = CLSR_DATA;
    mc->data = data;
}
