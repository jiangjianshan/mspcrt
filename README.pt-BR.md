<div align="center">
  <h1>✨🚀 mspcrt 🚀✨</h1>
  <p>MSVC Posix C Runtime - Melhor suporte ao padrão POSIX para o compilador MSVC no Windows</p>
</div>

## Idioma
[English](./README.md) | [简体中文](./README.zh-CN.md) | [Español](./README.es.md) | [日本語](./README.ja.md)  
[한국어](./README.ko.md) | [Русский](./README.ru.md) | **Português**

## Visão Geral do Projeto

Embora existam projetos de código aberto excelentes como [gnulib](https://www.gnu.org/software/gnulib/), [mingw-w64](https://www.mingw-w64.org/) e [glibc](https://www.gnu.org/software/libc/) que implementam parcial ou totalmente cabeçalhos e funções do padrão POSIX, nós ainda criamos o `mspcrt` (MSVC Posix C Runtime), principalmente pelas seguintes razões:

- **gnulib** requer ser incorporado ao projeto de código fonte com base no Autotools, o que não é adequado para projetos que não usam Autotools para construção.
- **MinGW-w64** tem como foco principal o compilador MinGW, enquanto o `mspcrt` é especificamente projetado para compiladores MSVC ou similares ao MSVC.
- **glibc** é construído em torno do GCC. Embora exista um projeto antigo [GnuWin](https://gnuwin32.sourceforge.net/) que portou a glibc para a plataforma Win32, faltam portes mais recentes e há conflitos de compatibilidade com o MSVC.
- A biblioteca [UCRT](https://learn.microsoft.com/en-us/cpp/porting/upgrade-your-code-to-the-universal-crt?view=msvc-170) no Windows SDK implementa apenas um subconjunto das funções padrão POSIX, com muitas faltantes, causando desafios ao compilar muitos projetos de código aberto com o MSVC.

O `mspcrt` pode ser considerado um projeto complementar à biblioteca UCRT. Ele foi inicialmente preparado para facilitar a compilação de bibliotecas de código aberto que dependem de cabeçalhos padrão POSIX dentro do projeto [msforge](https://github.com/jiangjianshan/msforge). Visa resolver problemas de compilação no MSVC causados pela falta de cabeçalhos ou funções padrão POSIX na UCRT.

Considerando as diferenças fundamentais entre Linux e Windows no nível de mecanismo subjacente, implementar totalmente todas as funções padrão POSIX seria um trabalho massivo. Portanto, o `mspcrt` não irá reimplementar projetos de código aberto excelentes existentes, tais como:
- [getopt-2022-09-25](https://www.codeproject.com/articles/Full-getopt-Port-for-Unicode-and-Multibyte-Microso) (Link parece inativo)
- [dirent](https://github.com/tronkko/dirent)
- [dlfcn-win32](https://github.com/dlfcn-win32/dlfcn-win32)
- [winpthreads](https://github.com/mingw-w64/mingw-w64/tree/master/mingw-w64-libraries/winpthreads)

Entre esses, o `getopt` foi integrado diretamente ao `mspcrt` como uma biblioteca de terceiros; outros componentes são priorizados para compilação como dependências do `mspcrt` dentro do [msforge](https://github.com/jiangjianshan/msforge).

## Início Rápido
```bash
git clone https://github.com/jiangjianshan/mspcrt
cd mspcrt
cmake -B build .
```

Uma abordagem mais recomendada é usar o `msforge` para gerenciar dependências e o ambiente de construção:

```bash
git clone https://github.com/jiangjianshan/msforge
cd msforge
# Compilar as bibliotecas de dependência do mspcrt (dirent, dlfcn-win32, winpthreads), depois compilar o mspcrt
mpt mspcrt
```

## Estratégia de Implementação

O `mspcrt` adota uma estratégia de implementação incremental. A adição e implementação de cada cabeçalho POSIX requer uma avaliação cuidadosa porque implementações incompletas ou incompatibilidades entre definições de macro e funções podem levar a erros de compilação em bibliotecas de código aberto. Além disso, algumas bibliotecas de código aberto fornecem suas próprias implementações multiplataforma, o que pode causar conflitos.

Portanto, a versão inicial do `mspcrt` implementa apenas os cabeçalhos e funções POSIX faltantes na UCRT e passou por testes de compilação com quase 355+ bibliotecas de código aberto no [msforge](https://github.com/jiangjianshan/msforge). À medida que o número de bibliotecas de código aberto suportadas pelo `msforge` aumenta, o `mspcrt` irá gradualmente complementar os componentes POSIX faltantes.

Nosso objetivo não é implementar todo o padrão POSIX, mas focar em ajudar o `msforge` e outros projetos a compilar com sucesso mais projetos de código aberto compatíveis com o padrão POSIX na plataforma Windows usando compiladores MSVC ou similares ao MSVC.

## Status do Projeto & Roteiro

### Progresso Atual
- ✅ Testes de compilação aprovados com 355+ bibliotecas de código aberto
- ✅ Integração perfeita com projetos como dirent, dlfcn-win32, winpthreads
- 🔄 Expandindo continuamente a cobertura de funções POSIX

### Metas de Curto Prazo
- Adicionar implementações Windows para mais chamadas de sistema POSIX
- Melhorar a compatibilidade com recursos específicos do Linux
- Otimizar desempenho e uso de memória

### Visão de Longo Prazo
- Tornar-se uma camada de compatibilidade POSIX completa complementar à biblioteca UCRT no Windows SDK (Se a UCRT viesse a suportar totalmente o padrão POSIX como a glibc no futuro, o `mspcrt` poderia potencialmente ser aposentado.)
- Suportar mais projetos de código aberto compilando no Windows sem modificações
- Construir uma comunidade ativa de desenvolvedores

## Contribuindo

Convidamos sinceramente desenvolvedores a se juntarem e ajudarem a melhorar o projeto `mspcrt`! Qualquer contribuição que você fizer é valiosa.

### Como Contribuir

#### Reportando Problemas
Se você encontrar qualquer problema ao usar o `mspcrt`, por favor, envie um relatório de bug detalhado via https://github.com/jiangjianshan/mspcrt/issues, incluindo:
- Versão do compilador e sistema operacional utilizado
- Passos para reproduzir o problema
- Comportamento esperado e comportamento real
- Mensagens de erro ou logs relevantes

#### Enviando Código
1. **Faça um fork deste repositório** e clone-o localmente.
2. Crie um branch de funcionalidade: `git checkout -b feature/incrivel-funcionalidade`
3. Commit suas alterações: `git commit -m 'Adiciona uma funcionalidade incrível'`
4. Push para o branch: `git push origin feature/incrivel-funcionalidade`
5. Abra um Pull Request

#### Tipos de Contribuições
- **Implementação de Código**: Implementar funções ou cabeçalhos POSIX faltantes.
- **Casos de Teste**: Adicionar testes de compilação ou testes unitários.
- **Melhoria de Documentação**: Melhorar a documentação ou adicionar exemplos de uso.
- **Otimização de Performance**: Otimizar o desempenho de implementações existentes.
- **Adaptação Multiplataforma**: Melhorar a compatibilidade entre diferentes versões do Windows.

### Padrões de Codificação
- Manter a compatibilidade com o compilador MSVC.
- Adicionar comentários e documentação apropriados.
- Garantir a compatibilidade com versões anteriores.

## Licença

Este projeto está licenciado sob a Licença MIT - veja o arquivo LICENSE para detalhes.

---

<div align="center">
  
✨ **Vamos tornar a experiência de desenvolvimento C/C++ no Windows melhor juntos!** ✨

</div>