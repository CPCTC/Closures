Portability
---
x86_64 Linux is supported. 64-bit Windows support is plausable, but not yet implemented. Other 64-bit POSIX systems that support MAP_ANON and use the System V AMD64 ABI will most likely work as well. x86 systems are unsupported.

Gcc is the only supported compiler. Clang does not support the required gcc extensions.

Usage
---
This is a single-header C library. To use it in your project, submodule (or copy-paste) closures.h into your project's repo. Then, `#include "closures.h"`.

The library's routines are defined in closures.h, but only when the macro CLSR_IMPLEMENTATION is defined before including the header. You must do this in exactly one translation unit, and closures.h must be the first header included into that unit.

Caveats
---
CLSR_DATA is implemented as a *global register variable*, a gcc extension. It's a way of telling the compiler to keep a certain CPU register reserved. This restricts what the compiler can do and will impact the performance of complicated functions. The reserving behavior comes with the declaration of CLSR_DATA, so this impacts any code in a translation unit that includes closures.h. However, for many users this may not cause a signifigant slowdown. If this matters to you, then move as much code as you can out of translation units that include closures.h.

The register used, `%r11`, is a volatile register in both the System V and Microsoft calling conventions. That means that callers can expect to find the register clobbered when a callee returns. This is why it is important to read CLSR_DATA as soon as possible in your wrapped functions.

Defining a global register variable in a volatile register causes gcc to issue a warning. So far, I can't find a way to turn this specific warning off. We are stuck with it for now.
