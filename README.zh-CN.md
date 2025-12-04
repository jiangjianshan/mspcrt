<div align="center">
  <h1>✨🚀 mspcrt 🚀✨</h1>
  <p>MSVC Posix C Runtime – 为 Windows 上的 MSVC 编译器提供更好的 POSIX 兼容性支持</p>
</div>

## 语言选择  
[English](README.md) | **简体中文**

## 项目简介

`mspcrt`（MSVC Posix C Runtime）是一个为 MSVC 及类 MSVC 编译器提供 POSIX 标准兼容运行时支持的库。它旨在补充 Windows UCRT 中缺失的 POSIX 标准函数与头文件，帮助开发者更轻松地在 Windows 平台上编译依赖 POSIX 标准的开源项目。

`mspcrt` 最初为 [msforge](https://github.com/jiangjianshan/msforge) 项目开发，用于简化依赖 POSIX 标准的开源库在 MSVC 下的编译过程。

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