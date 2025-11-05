<div align="center">
  <h1>✨🚀 mspcrt 🚀✨</h1>
  <p>MSVC Posix C Runtime - Mejor compatibilidad con el estándar POSIX para el compilador MSVC en Windows</p>
</div>

## Idioma
English | [简体中文](./README.zh-CN.md) | **Español** | [日本語](./README.ja.md)  
[한국어](./README.ko.md) | [Русский](./README.ru.md) | [Português](./README.pt-BR.md)

## Resumen del Proyecto

Aunque existen excelentes proyectos de código abierto como [gnulib](https://www.gnu.org/software/gnulib/), [mingw-w64](https://www.mingw-w64.org/) y [glibc](https://www.gnu.org/software/libc/) que implementan parcial o totalmente los encabezados y funciones del estándar POSIX, aún así creamos `mspcrt` (MSVC Posix C Runtime), principalmente por las siguientes razones:

- **gnulib** requiere integrarse en el proyecto de código fuente basado en Autotools, lo cual no es adecuado para proyectos que no utilizan Autotools para la construcción.
- **MinGW-w64** se dirige principalmente al compilador MinGW, mientras que `mspcrt` está diseñado específicamente para compiladores MSVC o similares a MSVC.
- **glibc** está construido alrededor de GCC. Aunque existe un proyecto antiguo [GnuWin](https://gnuwin32.sourceforge.net/) que portó glibc a la plataforma Win32, faltan ports más nuevos y existen conflictos de compatibilidad con MSVC.
- La biblioteca [UCRT](https://learn.microsoft.com/en-us/cpp/porting/upgrade-your-code-to-the-universal-crt?view=msvc-170) en el SDK de Windows solo implementa un subconjunto de las funciones estándar POSIX, faltando muchas, lo que causa desafíos al compilar muchos proyectos de código abierto con MSVC.

`mspcrt` puede considerarse un proyecto complementario a la biblioteca UCRT. Inicialmente se preparó para facilitar la compilación de bibliotecas de código abierto que dependen de encabezados estándar POSIX dentro del proyecto [msforge](https://github.com/jiangjianshan/msforge). Su objetivo es resolver problemas de compilación con MSVC causados por la falta de encabezados o funciones estándar POSIX en UCRT.

Considerando las diferencias fundamentales entre Linux y Windows a nivel de mecanismos subyacentes, implementar completamente todas las funciones estándar POSIX sería una tarea masiva. Por lo tanto, `mspcrt` no reimplementará proyectos de código abierto excelentes existentes, tales como:
- [getopt-2022-09-25](https://www.codeproject.com/articles/Full-getopt-Port-for-Unicode-and-Multibyte-Microso) (El enlace parece inactivo)
- [dirent](https://github.com/tronkko/dirent)
- [dlfcn-win32](https://github.com/dlfcn-win32/dlfcn-win32)
- [winpthreads](https://github.com/mingw-w64/mingw-w64/tree/master/mingw-w64-libraries/winpthreads)

Entre estos, `getopt` se ha integrado directamente en `mspcrt` como una biblioteca de terceros; otros componentes se priorizan para su compilación como dependencias de `mspcrt` dentro de [msforge](https://github.com/jiangjianshan/msforge).

## Inicio Rápido
```bash
git clone https://github.com/jiangjianshan/mspcrt
cd mspcrt
cmake -B build .
```

Un enfoque más recomendado es usar `msforge` para gestionar las dependencias y el entorno de construcción:

```bash
git clone https://github.com/jiangjianshan/msforge
cd msforge
# Compilar las bibliotecas dependientes de mspcrt (dirent, dlfcn-win32, winpthreads), luego compilar mspcrt
mpt mspcrt
```

## Estrategia de Implementación

`mspcrt` adopta una estrategia de implementación incremental. La adición e implementación de cada encabezado POSIX requiere una evaluación cuidadosa porque implementaciones incompletas o desajustes entre definiciones de macros y funciones pueden provocar errores de compilación en bibliotecas de código abierto. Además, algunas bibliotecas de código abierto proporcionan sus propias implementaciones multiplataforma, lo que podría causar conflictos.

Por lo tanto, la versión inicial de `mspcrt` solo implementa los encabezados y funciones POSIX que faltan en UCRT y ha pasado las pruebas de compilación con casi 355+ bibliotecas de código abierto en [msforge](https://github.com/jiangjianshan/msforge). A medida que aumenta el número de bibliotecas de código abierto compatibles con `msforge`, `mspcrt` complementará gradualmente los componentes POSIX faltantes.

Nuestro objetivo no es implementar todo el estándar POSIX, sino centrarnos en ayudar a `msforge` y otros proyectos a compilar exitosamente más proyectos de código abierto compatibles con el estándar POSIX en la plataforma Windows utilizando compiladores MSVC o similares a MSVC.

## Estado del Proyecto y Hoja de Ruta

### Progreso Actual
- ✅ Pasadas las pruebas de compilación con 355+ bibliotecas de código abierto
- ✅ Integración perfecta con proyectos como dirent, dlfcn-win32, winpthreads
- 🔄 Expansión continua de la cobertura de funciones POSIX

### Objetivos a Corto Plazo
- Añadir implementaciones para Windows de más llamadas al sistema POSIX
- Mejorar la compatibilidad con características específicas de Linux
- Optimizar el rendimiento y el uso de memoria

### Visión a Largo Plazo
- Convertirse en una capa de compatibilidad POSIX completa que complemente a la biblioteca UCRT en el SDK de Windows (Si UCRT llegara a admitir completamente el estándar POSIX como glibc en el futuro, `mspcrt` podría retirarse).
- Apoyar a más proyectos de código abierto para que se compilen en Windows sin modificaciones
- Construir una comunidad activa de desarrolladores

## Contribuciones

Invitamos sinceramente a los desarrolladores a unirse y ayudar a mejorar el proyecto `mspcrt`. Cualquier contribución que hagas es valiosa.

### Cómo Contribuir

#### Reportar Problemas
Si encuentras algún problema mientras usas `mspcrt`, por favor envía un reporte de error detallado a través de https://github.com/jiangjianshan/mspcrt/issues, incluyendo:
- Versión del compilador y sistema operativo utilizado
- Pasos para reproducir el problema
- Comportamiento esperado y comportamiento real
- Mensajes de error o registros relevantes

#### Enviar Código
1. **Haz un fork de este repositorio** y clónalo localmente.
2. Crea una rama de características: `git checkout -b feature/amazing-feature`
3. Confirma tus cambios: `git commit -m 'Add some amazing feature'`
4. Sube los cambios a la rama: `git push origin feature/amazing-feature`
5. Abre una Solicitud de Extracción (Pull Request)

#### Tipos de Contribuciones
- **Implementación de Código**: Implementar funciones o encabezados POSIX faltantes.
- **Casos de Prueba**: Añadir pruebas de compilación o pruebas unitarias.
- **Mejora de Documentación**: Mejorar la documentación o añadir ejemplos de uso.
- **Optimización de Rendimiento**: Optimizar el rendimiento de las implementaciones existentes.
- **Adaptación Multiplataforma**: Mejorar la compatibilidad entre diferentes versiones de Windows.

### Estándares de Codificación
- Mantener la compatibilidad con el compilador MSVC.
- Añadir comentarios y documentación apropiados.
- Garantizar la compatibilidad con versiones anteriores.

## Licencia

Este proyecto está licenciado bajo la Licencia MIT - consulta el archivo LICENSE para más detalles.

---

<div align="center">
  
✨ **¡Hagamos juntos que la experiencia de desarrollo en C/C++ en Windows sea mejor!** ✨

</div>