# Clsr

Clsr is a hacked-up single header C library that brings the semantics (but not syntax) of [closures](https://en.wikipedia.org/wiki/Closure_\(computer_programming\)) into C. It employs a special-purpose just-in-time assembler to capture your userdata and hard-code it into runtime-generated functions.

Applications do not need any special knowledge to invoke closures. They are represented as bare function pointers, compatible with your platform's ABI. If you want, you can pass closures unmodified as callbacks to C libraries. If you've ever tried to funnel extra state into a callback, then you can think of this library as the vastly friendlier thread-safe alternative to pass-by-global-variable.

## Directory Structure

- [clsr.h](clsr.h): The code
- [doc/](doc): Documentation
- [example/](example): Example code
- [LICENSE](LICENSE): MIT License
- [readme.md](readme.md): You are here!
