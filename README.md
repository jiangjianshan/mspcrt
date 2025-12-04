<div align="center">
  <h1>✨🚀 mspcrt 🚀✨</h1>
  <p>MSVC Posix C Runtime – Providing better POSIX compatibility support for MSVC compiler on Windows</p>
</div>

## Language Selection
**English** | [简体中文](README.zh-CN.md)

## Project Introduction

`mspcrt` (MSVC Posix C Runtime) is a library that provides POSIX standard-compliant runtime support for MSVC and MSVC-like compilers. It aims to supplement the missing POSIX standard functions and header files in the Windows UCRT, helping developers more easily compile open-source projects that rely on POSIX standards on the Windows platform.

`mspcrt` was initially developed for the [msforge](https://github.com/jiangjianshan/msforge) project to simplify the compilation process of open-source libraries dependent on POSIX standards under MSVC.

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