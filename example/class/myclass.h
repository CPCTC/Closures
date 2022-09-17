#pragma once

// Public interface of MyClass
typedef struct {
    int (*get)(void);
    void (*set)(int data);
} MyClass;

// Constructor
MyClass *myclass_init(int data);

// Destructor
void myclass_free(MyClass **mc);
