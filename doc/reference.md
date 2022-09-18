# Reference Documentation

Function `clsr_capture`:
---
```c
void *clsr_capture(void *fn, void *data);
```
Initializes a closure.

*fn* must be a function pointer of any type, cast to `void *`. *fn* must use the standard calling convention for your platform.

*clsr_capture* returns a function pointer of the same type as *fn*. The returned closure wraps *fn*, but invokes *fn* in such a way that the special variable CLSR_DATA initially holds the value of *data*. Note that CLSR_DATA may be clobbered by external function calls; see below.

*clsr_capture* may fail and set errno for any of the reasons specified for the routine *mmap*. On failure, NULL is returned.

Function `clsr_release`:
---
```c
int clsr_release(void **pclsr);
```
Frees the resources associated with a function pointer previously returned by *clsr_capture*, pointed to by *pclsr*.

*clsr_release* may fail and set errno for any of the reasons specified for the routine *munmap*. If this happens, then -1 is returned; otherwise, `*pclsr` is set to NULL, and 0 is returned.

Variable `CLSR_DATA`:
---
```c
void *CLSR_DATA;  // With additional magic properties
```
When referenced by a function wrapped by a closure created with *clsr_capture*, holds the value of the *data* argument to the call to *clsr_capture* that created the closure. CLSR_DATA is thread-local.

Warning: *CLSR_DATA may be clobbered by a call to any function in a translation unit that does not include closure.h.* Therefore, functions that want to read CLSR_DATA should first save its value to a local variable as soon as possible.

Macro `CLSR_IMPLEMENTATION`:
---
```c
// undefined
```
If this macro is defined before including closure.h, then the library's functions are defined by the header. When used this way, closure.h must be the first header included.
