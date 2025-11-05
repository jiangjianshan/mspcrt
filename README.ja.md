<div align="center">
  <h1>✨🚀 mspcrt 🚀✨</h1>
  <p>MSVC Posix C ランタイム - Windows上のMSVCコンパイラにおける、より優れたPOSIX標準サポート</p>
</div>

## 言語
[English](./README.md) | [简体中文](./README.zh-CN.md) | [Español](./README.es.md) | **日本語**  
[한국어](./README.ko.md) | [Русский](./README.ru.md) | [Português](./README.pt-BR.md)

## プロジェクト概要

[gnulib](https://www.gnu.org/software/gnulib/)、[mingw-w64](https://www.mingw-w64.org/)、[glibc](https://www.gnu.org/software/libc/) など、POSIX標準のヘッダーや関数を部分的または完全に実装する優れたオープンソースプロジェクトが存在しますが、それでも私たちが `mspcrt` (MSVC Posix C Runtime) を作成した主な理由は以下の通りです：

- **gnulib** は Autotools に基づいてソースコードプロジェクトに組み込む必要があり、Autotools を使用しないプロジェクトには適していません。
- **MinGW-w64** は主に MinGW コンパイラを対象としており、`mspcrt` は MSVC または MSVC 類似のコンパイラに特化して設計されています。
- **glibc** は GCC を中心に構築されています。古い [GnuWin](https://gnuwin32.sourceforge.net/) プロジェクトで glibc を Win32 プラットフォームに移植したものはありますが、新しい移植版はなく、MSVC との互換性の問題があります。
- Windows SDK の [UCRT](https://learn.microsoft.com/en-us/cpp/porting/upgrade-your-code-to-the-universal-crt?view=msvc-170) ライブラリは POSIX 標準関数の一部のみを実装しており、多くの関数が欠落しているため、多くのオープンソースプロジェクトを MSVC でコンパイルする際に課題が生じます。

`mspcrt` は UCRT ライブラリの補完プロジェクトと見なすことができます。このプロジェクトは、当初 [msforge](https://github.com/jiangjianshan/msforge) プロジェクト内で POSIX 標準ヘッダーに依存するオープンソースライブラリのコンパイルを容易にするために準備されました。UCRT に POSIX 標準ヘッダーや関数が欠落しているために発生する MSVC のコンパイル問題を解決することを目的としています。

Linux と Windows の根本的なメカニズムレベルの違いを考慮すると、すべての POSIX 標準関数を完全に実装することは非常に大規模な作業になります。そのため、`mspcrt` は既存の優れたオープンソースプロジェクトを再実装することはありません。例えば：
- [getopt-2022-09-25](https://www.codeproject.com/articles/Full-getopt-Port-for-Unicode-and-Multibyte-Microso) (リンクは無効のようです)
- [dirent](https://github.com/tronkko/dirent)
- [dlfcn-win32](https://github.com/dlfcn-win32/dlfcn-win32)
- [winpthreads](https://github.com/mingw-w64/mingw-w64/tree/master/mingw-w64-libraries/winpthreads)

これらの中でも、`getopt` はサードパーティライブラリとして `mspcrt` に直接統合されています。その他のコンポーネントは、[msforge](https://github.com/jiangjianshan/msforge) 内で `mspcrt` の依存関係としてコンパイルすることが優先されます。

## クイックスタート
```bash
git clone https://github.com/jiangjianshan/mspcrt
cd mspcrt
cmake -B build .
```

より推奨される方法は、`msforge` を使用して依存関係とビルド環境を管理することです：

```bash
git clone https://github.com/jiangjianshan/msforge
cd msforge
# mspcrtの依存ライブラリ（dirent, dlfcn-win32, winpthreads）をコンパイルし、その後mspcrtをコンパイル
mpt mspcrt
```

## 実装戦略

`mspcrt` は段階的な実装戦略を採用しています。各 POSIX ヘッダーの追加と実装には慎重な評価が必要です。なぜなら、不完全な実装やマクロ定義と関数の不一致は、オープンソースライブラリのコンパイルエラーを引き起こす可能性があるためです。さらに、一部のオープンソースライブラリは独自のクロスプラットフォーム実装を提供しているため、競合が発生する可能性があります。

したがって、`mspcrt` の初期バージョンでは、UCRT に欠落している POSIX ヘッダーと関数のみを実装しており、[msforge](https://github.com/jiangjianshan/msforge) の 355+ のオープンソースライブラリでのコンパイルテストに合格しています。`msforge` がサポートするオープンソースライブラリの数が増えるにつれて、`mspcrt` は欠落している POSIX コンポーネントを段階的に補充していきます。

私たちの目標は POSIX 標準全体を実装することではなく、`msforge` やその他のプロジェクトが、MSVC または MSVC 類似のコンパイラを使用して、Windows プラットフォーム上でより多くの POSIX 標準に準拠したオープンソースプロジェクトを正常にコンパイルできるように支援することに焦点を当てています。

## プロジェクト状況とロードマップ

### 現在の進捗状況
- ✅ 355+ のオープンソースライブラリでのコンパイルテストに合格
- ✅ dirent, dlfcn-win32, winpthreads などのプロジェクトとのシームレスな統合
- 🔄 POSIX 関数のカバレッジを継続的に拡大中

### 短期目標
- より多くの POSIX システムコールに対する Windows 実装の追加
- Linux 固有の機能との互換性の向上
- パフォーマンスとメモリ使用量の最適化

### 長期的なビジョン
- Windows SDK の UCRT ライブラリに対する完全な POSIX 互換レイヤーの補完となること（将来的に UCRT が glibc のように POSIX 標準を完全にサポートするようになれば、`mspcrt` は役目を終える可能性があります。）
- 変更を加えずにより多くのオープンソースプロジェクトが Windows でコンパイルできるようにサポート
- 活発な開発者コミュニティの構築

## 貢献について

私たちは、開発者の皆様が参加し、`mspcrt` プロジェクトの改善に協力してくださることを心からお待ちしています！皆様の貢献はどれも貴重なものです。

### 貢献の方法

#### 問題の報告
`mspcrt` の使用中に問題が発生した場合は、https://github.com/jiangjianshan/mspcrt/issues を通じて詳細なバグレポートを提出してください。以下の情報を含めてください：
- 使用したコンパイラのバージョンとオペレーティングシステム
- 問題を再現する手順
- 期待される動作と実際の動作
- 関連するエラーメッセージやログ

#### コードの提出
1. **このリポジトリを Fork** し、ローカルにクローンします。
2. 機能ブランチを作成: `git checkout -b feature/amazing-feature`
3. 変更をコミット: `git commit -m 'Add some amazing feature'`
4. ブランチにプッシュ: `git push origin feature/amazing-feature`
5. プルリクエストをオープン

#### 貢献の種類
- **コード実装**: 欠落している POSIX 関数やヘッダーの実装。
- **テストケース**: コンパイルテストや単体テストの追加。
- **ドキュメント改善**: ドキュメントの改善や使用例の追加。
- **パフォーマンス最適化**: 既存実装のパフォーマンス最適化。
- **クロスプラットフォーム適応**: 異なる Windows バージョン間での互換性向上。

### コーディング規約
- MSVC コンパイラとの互換性を維持すること。
- 適切なコメントとドキュメントを追加すること。
- 下位互換性を確保すること。

## ライセンス

このプロジェクトは MIT ライセンスの下でライセンスされています。詳細は LICENSE ファイルを参照してください。

---

<div align="center">

✨ **一緒に、Windows 上の C/C++ 開発体験をより良いものにしましょう！** ✨

</div>