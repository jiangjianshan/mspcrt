<div align="center">
  <h1>✨🚀 mspcrt 🚀✨</h1>
  <p>MSVC Posix C 런타임 - Windows의 MSVC 컴파일러가 POSIX 표준을 더 잘 지원하도록</p>
</div>

## 언어 선택
[English](./README.md) | [简体中文](./README.zh-CN.md) | [Español](./README.es.md) | [日本語](./README.ja.md)  
**한국어** | [Русский](./README.ru.md) | [Português](./README.pt-BR.md)

## 프로젝트 개요

[gnulib](https://www.gnu.org/software/gnulib/), [mingw-w64](https://www.mingw-w64.org/), [glibc](https://www.gnu.org/software/libc/)와 같은 훌륭한 오픈소스 프로젝트들이 POSIX 표준 헤더 파일과 함수들을 부분적 또는 완전히 구현했음에도 불구하고, 우리는 `mspcrt`(MSVC Posix C Runtime)를 만들었습니다. 주된 이유는 다음과 같습니다:

- **gnulib**는 Autotools에 기반하여 소스 코드 프로젝트에 내장되어야 하며, Autotools를 사용하지 않는 프로젝트에는 적합하지 않습니다.
- **MinGW-w64**는 주로 MinGW 컴파일러를 대상으로 하는 반면, `mspcrt`는 MSVC 또는 MSVC 유사 컴파일러를 위해 특별히 설계되었습니다.
- **glibc**는 GCC 기반으로 빌드됩니다. 구버전 [GnuWin](https://gnuwin32.sourceforge.net/)이 glibc를 Win32 플랫폼으로 이식했지만, 새로운 버전의 이식은 부재하고 MSVC와의 호환성 충돌이 있습니다.
- Windows SDK의 [UCRT](https://learn.microsoft.com/en-us/cpp/porting/upgrade-your-code-to-the-universal-crt?view=msvc-170) 라이브러리는 POSIX 표준 함수의 일부만 구현하여 많은 부분이 누락되어 있어, 많은 오픈소스 프로젝트가 MSVC로 컴파일할 때 어려움에 직면하게 합니다.

`mspcrt`는 UCRT 라이브러리의 보완 프로젝트로 볼 수 있으며,最初는 [msforge](https://github.com/jiangjianshan/msforge) 프로젝트에서 POSIX 표준 헤더 파일에 의존하는 오픈소스 라이브러리들을 더 쉽게 컴파일하기 위해 준비되었습니다. 이는 UCRT가 특정 POSIX 표준 헤더 파일이나 함수를 누락시켜 발생하는 MSVC 컴파일 문제를 해결하는 것을 목표로 합니다.

Linux와 Windows의 근본적인 메커니즘 차이를 고려할 때, 모든 POSIX 표준 함수를 완전히 구현하는 것은 엄청난 작업량이 필요합니다. 따라서 `mspcrt`는 기존의 훌륭한 오픈소스 프로젝트를 반복 구현하지 않습니다. 예를 들어:
- [getopt-2022-09-25](https://www.codeproject.com/articles/Full-getopt-Port-for-Unicode-and-Multibyte-Microso) (링크失效)
- [dirent](https://github.com/tronkko/dirent)
- [dlfcn-win32](https://github.com/dlfcn-win32/dlfcn-win32)
- [winpthreads](https://github.com/mingw-w64/mingw-w64/tree/master/mingw-w64-libraries/winpthreads)

이 중 `getopt`는 서드파티 라이브러리로 `mspcrt`에 직접 통합되었습니다. 다른 구성 요소들은 [msforge](https://github.com/jiangjianshan/msforge)에서 `mspcrt`의 의존 라이브러리로 우선 컴파일됩니다.

## 빠른 시작
```bash
git clone https://github.com/jiangjianshan/mspcrt
cd mspcrt
cmake -B build .
```

의존성 및 빌드 환경 관리를 위해 `msforge`를 사용하는 것을 더 권장합니다:

```bash
git clone https://github.com/jiangjianshan/msforge
cd msforge
# mspcrt의 의존 라이브러리(dirent, dlfcn-win32, winpthreads) 컴파일 후 mspcrt 컴파일
mpt mspcrt
```

## 구현 전략

`mspcrt`는 점진적인 구현 전략을 채택합니다. 각 POSIX 헤더 파일의 추가와 구현은 신중하게 평가되어야 합니다. 불완전한 구현이나 매크로 정의와 함수의 불일치는 오픈소스 라이브러리 컴파일 오류를 유발할 수 있기 때문입니다. 또한, 일부 오픈소스 라이브러리는 자체적인 크로스 플랫폼 구현을 제공하여 충돌을 일으킬 수 있습니다.

따라서 `mspcrt`의 초기 버전은 UCRT에서 누락된 일부 POSIX 헤더 파일과 함수만 구현하며, 이미 [msforge](https://github.com/jiangjianshan/msforge)의 약 355개 이상의 오픈소스 라이브러리 컴파일 테스트를 통과했습니다. `msforge`가 지원하는 오픈소스 라이브러리 수가 증가함에 따라, `mspcrt`는 점차 누락된 POSIX 구성 요소들을 보완해 나갈 것입니다.

우리의 목표는 모든 POSIX 표준 내용을 구현하는 것이 아니라, `msforge` 및 다른 프로젝트가 Windows 플랫폼에서 MSVC 또는 MSVC 유사 컴파일러를 사용하여 POSIX 표준을 준수하는 더 많은 오픈소스 프로젝트들을 성공적으로 컴파일할 수 있도록 돕는 데 중점을 둡니다.

## 프로젝트 현황 및 로드맵

### 현재 진행 상황
- ✅ 355+ 오픈소스 라이브러리 컴파일 테스트 통과
- ✅ dirent, dlfcn-win32, winpthreads 등과의 원활한 통합
- 🔄 POSIX 함수 커버리지 지속적 확장

### 단기 목표
- 더 많은 POSIX 시스템 호출의 Windows 구현 추가
- Linux 특정 기능과의 호환성 향상
- 성능 및 메모리 사용 최적화

### 장기 비전
- Windows SDK의 UCRT 라이브러리에 대한 완전한 POSIX 호환 레이어 보완이 되는 것 (만약 미래에 UCRT가 glibc처럼 POSIX 표준을 완전히 지원하게 된다면, `mspcrt`는 그 임무를 다하게 될 수도 있습니다)
- 더 많은 오픈소스 프로젝트가 수정 없이 Windows에서 컴파일될 수 있도록 지원
- 활발한 개발자 커뮤니티 구축

## 기여 가이드

개발자 여러분의 참여를 진심으로 환영하며, 함께 `mspcrt` 프로젝트를 완성해 나갑시다! 여러분의 어떤 기여도 소중합니다.

### 기여 방법

#### 문제 보고
사용 중 문제가 발생하면 https://github.com/jiangjianshan/mspcrt/issues 에 상세한 버그 리포트를 제출해 주세요. 포함 내용:
- 사용 중인 컴파일러 버전 및 운영체제
- 문제 재현 단계
- 기대 행동과 실제 행동
- 관련 오류 메시지 또는 로그

#### 코드 제출
1. **본 저장소를 Fork**하고 로컬에 클론합니다.
2. 기능 브랜치 생성: `git checkout -b feature/amazing-feature`
3. 변경 사항 커밋: `git commit -m 'Add some amazing feature'`
4. 브랜치에 푸시: `git push origin feature/amazing-feature`
5. Pull Request 제출

#### 기여 유형
- **코드 구현**: 누락된 POSIX 함수 또는 헤더 파일 구현
- **테스트 케이스**: 컴파일 테스트 또는 단위 테스트 추가
- **문서 개선**: 문서 개선 또는 사용 예제 추가
- **성능 최적화**: 기존 구현 성능 최적화
- **크로스 플랫폼 적응**: 다양한 Windows 버전 간 호환성 강화

### 코드 표준
- MSVC 컴파일러와의 호환성 유지
- 적절한 주석 및 문서 추가
- 하위 호환성 보장

## 라이선스

이 프로젝트는 MIT 라이선스를 따릅니다. 자세한 내용은 LICENSE 파일을 참조하세요.

---

<div align="center">

✨ **함께 Windows에서의 C/C++ 개발 경험을 더욱 즐겁게 만들어요!** ✨

</div>