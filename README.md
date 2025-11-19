<div align="center">
  <h1>✨🚀 mspcrt 🚀✨</h1>
  <p>MSVC Posix C Runtime – Providing better POSIX compatibility support for MSVC compiler on Windows</p>
</div>

## Language Selection
**English** | [简体中文](README.zh-CN.md)

## Project Introduction

`mspcrt` (MSVC Posix C Runtime) is a library that provides POSIX standard-compliant runtime support for MSVC and MSVC-like compilers. It aims to supplement the missing POSIX standard functions and header files in the Windows UCRT, helping developers more easily compile open-source projects that rely on POSIX standards on the Windows platform.

Although excellent projects like [gnulib](https://www.gnu.org/software/gnulib/), [mingw-w64](https://www.mingw-w64.org/) already provide similar functionalities, `mspcrt` focuses specifically on the MSVC environment, addressing the following practical issues:

- **gnulib** relies on Autotools and is not suitable for non-Autotools projects.
- **MinGW-w64** primarily targets the GCC compiler family and has compatibility issues with MSVC.
- **UCRT** only implements a subset of POSIX functions, making it still difficult to compile many open-source libraries under MSVC.

`mspcrt` was initially developed for the [msforge](https://github.com/jiangjianshan/msforge) project to simplify the compilation process of open-source libraries dependent on POSIX standards under MSVC.

## Design Principles

We adhere to the following principles to ensure the practicality and quality of the port:

- **Functional Completeness**: Implementations should provide functionality substantially equivalent to the POSIX standard, avoiding incomplete stub implementations.
- **Native Efficiency**: Implementations should be based on native Windows APIs (e.g., Win32, NTAPI), avoiding inefficient user-mode emulation.
- **Addressing Pain Points**: Prioritize implementing functionalities commonly used in cross-platform development, such as file operations, threads, networking, etc.

`mspcrt` does not reinvent the wheel but reuses or adapts existing excellent implementations, for example:

- [dirent](https://github.com/tronkko/dirent)
- [dlfcn-win32](https://github.com/dlfcn-win32/dlfcn-win32)
- [winpthreads](https://github.com/mingw-w64/mingw-w64/tree/master/mingw-w64-libraries/winpthreads)
- [gnulib](https://www.gnu.org/software/gnulib/) (some modules are used after adaptation and modification)
- [mingw-w64-crt](https://github.com/mingw-w64/mingw-w64/tree/master/mingw-w64-crt) (some files are used after adaptation and modification)

## Implementation Strategy

We adopt a progressive implementation strategy, carefully evaluating the introduction of each POSIX header file. Incomplete implementations or macro definition conflicts can cause compilation errors, especially for headers like `unistd.h` and `sys/types.h`, which are often implemented independently in various open-source libraries, leading to issues like symbol redefinition or missing definitions.

For instance, the definition of `ssize_t`, if protected only by macro guards, might cause inconsistent definitions across different libraries. Therefore, we strive to strike a balance between compatibility and stability.

## Quick Start

### Direct Build

```bash
git clone https://github.com/jiangjianshan/mspcrt
cd mspcrt
cmake -B build .
cmake --build build
```

### Using msforge (Recommended)

If you use [msforge](https://github.com/jiangjianshan/msforge) to manage dependencies and the build environment, you can execute the following commands:

```bash
git clone https://github.com/jiangjianshan/msforge
cd msforge
mpt mspcrt
```

## Contributing Guide

We welcome all forms of contributions, whether it's code, tests, documentation, or issue feedback.

### Reporting Issues

Please provide the following information in the [Issues](https://github.com/jiangjianshan/mspcrt/issues):

- Compiler version and operating system
- Steps to reproduce
- Expected vs. actual behavior
- Error logs or screenshots

### Submitting Code

1. Fork this repository and clone it locally.
2. Create a feature branch: `git checkout -b feat/your-feature`.
3. Commit your changes: `git commit -m "Add your feature"`.
4. Push the branch: `git push origin feat/your-feature`.
5. Submit a Pull Request.

### Contribution Types

- **Implement Missing Features**: Add unimplemented POSIX functions or header files.
- **Write Tests**: Add compilation tests or unit tests.
- **Improve Documentation**: Enhance documentation or add usage examples.
- **Performance Optimization**: Improve the efficiency and stability of existing implementations.

### Code Standards

- Maintain compatibility with the MSVC compiler.
- Code should be well-commented and structurally clear.
- Ensure backward compatibility; avoid breaking changes.

## License

This project is released under the MIT License. See the [LICENSE](LICENSE) file for details.