<div align="center">
  <h1>✨🚀 mspcrt 🚀✨</h1>
  <p>MSVC Posix C Runtime - Better POSIX standard support for the MSVC compiler on Windows</p>
</div>

## Language
**English** | [简体中文](./README.zh-CN.md) | [Español](./README.es.md) | [日本語](./README.ja.md)  
[한국어](./README.ko.md) | [Русский](./README.ru.md) | [Português](./README.pt-BR.md)

## Project Overview

Although there are excellent open-source projects like [gnulib](https://www.gnu.org/software/gnulib/), [mingw-w64](https://www.mingw-w64.org/), and [glibc](https://www.gnu.org/software/libc/) that partially or fully implement POSIX standard headers and functions, we still created `mspcrt` (MSVC Posix C Runtime), primarily for the following reasons:

- **gnulib** requires embedding into the source code project based on Autotools, which is not suitable for projects not using Autotools for building.
- **MinGW-w64** primarily targets the MinGW compiler, while `mspcrt` is specifically designed for the MSVC or MSVC-like compilers.
- **glibc** is built around GCC. Although there is an old [GnuWin](https://gnuwin32.sourceforge.net/) project that ported glibc to the Win32 platform, newer ports are missing, and there are compatibility conflicts with MSVC.
- The [UCRT](https://learn.microsoft.com/en-us/cpp/porting/upgrade-your-code-to-the-universal-crt?view=msvc-170) library in the Windows SDK only implements a subset of the POSIX standard functions, with many missing, causing challenges when compiling many open-source projects with MSVC.

`mspcrt` can be considered a supplementary project to the UCRT library. It was initially prepared to facilitate easier compilation of open-source libraries that depend on POSIX standard headers within the [msforge](https://github.com/jiangjianshan/msforge) project. It aims to resolve MSVC compilation issues caused by missing POSIX standard headers or functions in UCRT.

Considering the fundamental differences between Linux and Windows at the underlying mechanism level, fully implementing all POSIX standard functions would be a massive undertaking. Therefore, `mspcrt` will not re-implement existing excellent open-source projects, such as:
- [getopt-2022-09-25](https://www.codeproject.com/articles/Full-getopt-Port-for-Unicode-and-Multibyte-Microso) (Link appears inactive)
- [dirent](https://github.com/tronkko/dirent)
- [dlfcn-win32](https://github.com/dlfcn-win32/dlfcn-win32)
- [winpthreads](https://github.com/mingw-w64/mingw-w64/tree/master/mingw-w64-libraries/winpthreads)

Among these, `getopt` has been directly integrated into `mspcrt` as a third-party library; other components are prioritized for compilation as dependencies of `mspcrt` within [msforge](https://github.com/jiangjianshan/msforge).

## Quick Start
```bash
git clone https://github.com/jiangjianshan/mspcrt
cd mspcrt
cmake -B build .
```

A more recommended approach is to use `msforge` to manage dependencies and the build environment:

```bash
git clone https://github.com/jiangjianshan/msforge
cd msforge
# Compile mspcrt's dependency libraries (dirent, dlfcn-win32, winpthreads), then compile mspcrt
mpt mspcrt
```

## Implementation Strategy

`mspcrt` adopts an incremental implementation strategy. The addition and implementation of each POSIX header require careful evaluation because incomplete implementations or mismatches between macro definitions and functions can lead to compilation errors in open-source libraries. Furthermore, some open-source libraries provide their own cross-platform implementations, which might cause conflicts.

Therefore, the initial version of `mspcrt` only implements the POSIX headers and functions missing from UCRT and has passed compilation tests with nearly 355+ open-source libraries in [msforge](https://github.com/jiangjianshan/msforge). As the number of open-source libraries supported by `msforge` increases, `mspcrt` will gradually supplement the missing POSIX components.

Our goal is not to implement the entire POSIX standard but to focus on helping `msforge` and other projects successfully compile more POSIX-standard-compliant open-source projects on the Windows platform using MSVC or MSVC-like compilers.

## Project Status & Roadmap

### Current Progress
- ✅ Passed compilation tests with 355+ open-source libraries
- ✅ Seamless integration with projects like dirent, dlfcn-win32, winpthreads
- 🔄🔄 Continuously expanding POSIX function coverage

### Short-term Goals
- Add Windows implementations for more POSIX system calls
- Improve compatibility with Linux-specific features
- Optimize performance and memory usage

### Long-term Vision
- Become a complete POSIX compatibility layer supplement to the UCRT library in the Windows SDK (If UCRT were to fully support the POSIX standard like glibc in the future, `mspcrt` could potentially retire.)
- Support more open-source projects compiling on Windows without modifications
- Build an active developer community

## Contributing

We sincerely invite developers to join and help improve the `mspcrt` project! Any contribution you make is valuable.

### How to Contribute

#### Reporting Issues
If you encounter any issues while using `mspcrt`, please submit a detailed bug report via https://github.com/jiangjianshan/mspcrt/issues, including:
- Compiler version and operating system used
- Steps to reproduce the issue
- Expected behavior and actual behavior
- Relevant error messages or logs

#### Submitting Code
1. **Fork this repository** and clone it locally.
2. Create a feature branch: `git checkout -b feature/amazing-feature`
3. Commit your changes: `git commit -m 'Add some amazing feature'`
4. Push to the branch: `git push origin feature/amazing-feature`
5. Open a Pull Request

#### Types of Contributions
- **Code Implementation**: Implement missing POSIX functions or headers.
- **Test Cases**: Add compilation tests or unit tests.
- **Documentation Improvement**: Improve documentation or add usage examples.
- **Performance Optimization**: Optimize the performance of existing implementations.
- **Cross-platform Adaptation**: Enhance compatibility across different Windows versions.

### Coding Standards
- Maintain compatibility with the MSVC compiler.
- Add appropriate comments and documentation.
- Ensure backward compatibility.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

---

<div align="center">
  
✨ **Let's make the C/C++ development experience on Windows better together!** ✨

</div>