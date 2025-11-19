<div align="center">
  <h1>✨🚀 mspcrt 🚀✨</h1>
  <p>MSVC Posix C Runtime – 为 Windows 上的 MSVC 编译器提供更好的 POSIX 兼容性支持</p>
</div>

## 语言选择  
[English](README.md) | **简体中文**

## 项目简介

`mspcrt`（MSVC Posix C Runtime）是一个为 MSVC 及类 MSVC 编译器提供 POSIX 标准兼容运行时支持的库。它旨在补充 Windows UCRT 中缺失的 POSIX 标准函数与头文件，帮助开发者更轻松地在 Windows 平台上编译依赖 POSIX 标准的开源项目。

尽管已有 [gnulib](https://www.gnu.org/software/gnulib/)、[mingw-w64](https://www.mingw-w64.org/) 等优秀项目提供类似功能，但 `mspcrt` 专注于 MSVC 环境，解决以下实际问题：

- **gnulib** 依赖 Autotools，不适合非 Autotools 项目。
- **MinGW-w64** 主要面向 GCC 系编译器，与 MSVC 存在兼容性问题。
- **UCRT** 仅实现了部分 POSIX 函数，许多开源库在 MSVC 下编译仍面临困难。

`mspcrt` 最初为 [msforge](https://github.com/jiangjianshan/msforge) 项目开发，用于简化依赖 POSIX 标准的开源库在 MSVC 下的编译过程。

## 设计原则

我们遵循以下原则，确保移植的实用性与质量：

- **功能完整**：实现应提供与 POSIX 标准实质等同的功能，避免残缺的存根实现。
- **原生高效**：基于 Windows 原生 API（如 Win32、NTAPI）实现，避免低效的用户态模拟。
- **解决痛点**：优先实现跨平台开发中常用的功能，如文件操作、线程、网络等。

`mspcrt` 不会重复造轮子，而是复用或适配已有的优秀实现，例如：

- [dirent](https://github.com/tronkko/dirent)
- [dlfcn-win32](https://github.com/dlfcn-win32/dlfcn-win32)
- [winpthreads](https://github.com/mingw-w64/mingw-w64/tree/master/mingw-w64-libraries/winpthreads)
- [gnulib](https://www.gnu.org/software/gnulib/)（部分模块经适配修改后使用）
- [mingw-w64-crt](https://github.com/mingw-w64/mingw-w64/tree/master/mingw-w64-crt)（部分文件经适配修改后使用）

## 实现策略

我们采用渐进式实现策略，谨慎评估每个 POSIX 头文件的引入。不完整的实现或宏定义冲突可能导致编译错误，尤其像 `unistd.h`、`sys/types.h` 这类在多个开源库中自行实现的头文件，容易引发符号重复定义或缺失问题。

例如，`ssize_t` 的定义若仅依赖宏开关保护，可能在不同库之间造成定义不一致。因此，我们力求在兼容性和稳定性之间取得平衡。

## 快速开始

### 直接构建

```bash
git clone https://github.com/jiangjianshan/mspcrt
cd mspcrt
cmake -B build .
cmake --build build
```

### 使用 msforge（推荐）

如果你使用 [msforge](https://github.com/jiangjianshan/msforge) 管理依赖和构建环境，可执行以下命令：

```bash
git clone https://github.com/jiangjianshan/msforge
cd msforge
mpt mspcrt
```

## 贡献指南

我们欢迎任何形式的贡献，无论是代码、测试、文档还是问题反馈。

### 报告问题

请在 [Issues](https://github.com/jiangjianshan/mspcrt/issues) 中提供以下信息：

- 编译器版本与操作系统
- 重现步骤
- 期望与实际行为
- 错误日志或截图

### 提交代码

1. Fork 本仓库并克隆到本地；
2. 创建功能分支：`git checkout -b feat/your-feature`；
3. 提交更改：`git commit -m "Add your feature"`；
4. 推送分支：`git push origin feat/your-feature`；
5. 提交 Pull Request。

### 贡献类型

- **实现缺失功能**：补充未实现的 POSIX 函数或头文件；
- **编写测试**：添加编译测试或单元测试；
- **完善文档**：改进说明文档或添加使用示例；
- **性能优化**：提升现有实现的效率与稳定性。

### 代码标准

- 保持与 MSVC 编译器的兼容性；
- 代码注释清晰，结构易懂；
- 确保向后兼容，避免破坏性变更。

## 许可证

本项目基于 MIT 许可证发布，详见 [LICENSE](LICENSE) 文件。