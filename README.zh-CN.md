<div align="center">
  <h1>✨🚀 mspcrt 🚀✨</h1>
  <p>MSVC Posix C Runtime - 让 Windows 上的 MSVC 编译器更好地支持 POSIX 标准</p>
</div>

## 语言选择
[English](./README.md) | **简体中文** | [Español](./README.es.md) | [日本語](./README.ja.md)  
[한국어](./README.ko.md) | [Русский](./README.ru.md) | [Português](./README.pt-BR.md)

## 项目概述

尽管已有 [gnulib](https://www.gnu.org/software/gnulib/)、[mingw-w64](https://www.mingw-w64.org/) 和 [glibc](https://www.gnu.org/software/libc/) 等优秀开源项目部分或完整地实现了 POSIX 标准的头文件与函数，但我们依然创建了 `mspcrt`（MSVC Posix C Runtime），主要基于以下原因：

- **gnulib** 需要基于 Autotools 嵌入源码工程，不适用于非 Autotools 构建的项目。
- **MinGW-w64** 主要面向 MinGW 编译器，而 `mspcrt` 专为 MSVC 或类 MSVC 编译器设计。
- **glibc** 基于 GCC 构建，虽有旧版 [GnuWin](https://gnuwin32.sourceforge.net/) 已移植glibc到 Win32 平台，但新版移植缺失，且与 MSVC 存在兼容性冲突。
- Windows SDK 中的 [UCRT](https://learn.microsoft.com/en-us/cpp/porting/upgrade-your-code-to-the-universal-crt?view=msvc-170) 库仅实现了部分 POSIX 标准函数，存在不少缺失，导致许多开源项目在使用 MSVC 编译时面临挑战。

`mspcrt` 可视为 UCRT 库的补充项目，最初是为了在 [msforge](https://github.com/jiangjianshan/msforge) 项目中更轻松地编译依赖 POSIX 标准头文件的开源库而准备的。它旨在解决因 UCRT 缺失 某些POSIX 标准头文件或函数而导致的 MSVC 编译问题。

考虑到 Linux 与 Windows 在底层机制上存在差异，完全实现所有 POSIX 标准函数工作量巨大。因此，`mspcrt` 不会重复实现已有的优秀开源项目，例如：
- [getopt-2022-09-25](https://www.codeproject.com/articles/Full-getopt-Port-for-Unicode-and-Multibyte-Microso)（链接已失效）
- [dirent](https://github.com/tronkko/dirent)
- [dlfcn-win32](https://github.com/dlfcn-win32/dlfcn-win32)
- [winpthreads](https://github.com/mingw-w64/mingw-w64/tree/master/mingw-w64-libraries/winpthreads)

其中，`getopt` 作为第三方库已直接集成在 `mspcrt` 中；其他组件则在 [msforge](https://github.com/jiangjianshan/msforge) 中作为 `mspcrt` 的依赖库优先编译。

## 快速开始

```bash
git clone https://github.com/jiangjianshan/mspcrt
cd mspcrt
cmake -B build .
```

更推荐的方式是使用 `msforge` 来管理依赖和构建环境：

```bash
git clone https://github.com/jiangjianshan/msforge
cd msforge
# 编译 mspcrt 的依赖库（dirent、dlfcn-win32、winpthreads），然后编译 mspcrt
mpt mspcrt
```

## 实现策略

`mspcrt` 采用渐进式实现策略。每个 POSIX 头文件的添加与实现都需要谨慎评估，因为不完整的实现或宏定义与函数不匹配可能导致开源库编译错误。此外，部分开源库会自行提供跨平台实现，可能引发冲突。

因此，`mspcrt` 的初版仅实现 UCRT 缺失的部分 POSIX 头文件与函数，并已通过[msforge](https://github.com/jiangjianshan/msforge)近 355+ 个开源库的编译测试。随着 `msforge` 支持的开源库数量增加，`mspcrt` 将逐步补充缺失的 POSIX 组件。

我们的目标不是实现所有 POSIX 标准内容，而是专注于帮助 `msforge` 及其他项目在 Windows 平台上使用 MSVC 或类 MSVC 编译器成功编译更多符合 POSIX 标准的开源项目。

## 项目现状与路线图

### 当前进展
- ✅ 通过 355+ 开源库编译测试
- ✅ 与 dirent、dlfcn-win32、winpthreads 等项目的无缝集成
- 🔄 持续扩展 POSIX 函数覆盖范围

### 短期目标
- 增加更多 POSIX 系统调用的 Windows 实现
- 提升与 Linux 特定功能的兼容性
- 优化性能与内存使用

### 长期愿景
- 成为 Windows SDK 中 UCRT 库的完整 POSIX 兼容层补充（如果未来 UCRT 能像 glibc 那样完全支持 POSIX 标准，`mspcrt` 或许就可以功成身退了）
- 支持更多开源项目无需修改即可在 Windows 上编译
- 建立活跃的开发者社区

## 贡献指南

我们诚挚邀请开发者加入，共同完善 `mspcrt` 项目！您的任何贡献都是宝贵的。

### 如何参与贡献

#### 报告问题
如果您在使用过程中遇到任何问题，请通过 https://github.com/jiangjianshan/mspcrt/issues 提交详细的错误报告，包括：
- 使用的编译器版本和操作系统
- 重现问题的步骤
- 期望的行为和实际的行为
- 相关的错误信息或日志

#### 提交代码
1. **Fork 本仓库**并克隆到本地
2. 创建特性分支：`git checkout -b feature/amazing-feature`
3. 提交更改：`git commit -m 'Add some amazing feature'`
4. 推送到分支：`git push origin feature/amazing-feature`
5. 提交 Pull Request

#### 贡献类型
- **代码实现**：实现缺失的 POSIX 函数或头文件
- **测试用例**：添加编译测试或单元测试
- **文档完善**：改进文档或添加使用示例
- **性能优化**：优化现有实现的性能
- **跨平台适配**：增强不同 Windows 版本的兼容性

### 代码标准
- 保持与 MSVC 编译器的兼容性
- 添加适当的注释和文档
- 确保向后兼容性

## 许可证

本项目采用 MIT 许可证 - 详见 LICENSE 文件。

---

<div align="center">

✨ **让我们一起让Windows上的C/C++开发体验更美好！** ✨

</div>