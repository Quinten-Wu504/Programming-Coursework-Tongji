# Programming Coursework

C/C++ assignments from Advanced Programming and Object-Oriented Programming at Tongji University, by [Jinxuan Wu(Quinten)](https://github.com/Quinten-Wu504).

Topics include pointers, memory management, data structures, file processing, operator overloading, inheritance, and polymorphism.

## Exercises

- [Student Grade Sorting](exercises/%E6%88%90%E7%BB%A9%E6%8E%92%E5%BA%8F/README.md)
- [Dou Dizhu Card Dealing](exercises/%E6%96%97%E5%9C%B0%E4%B8%BB%E5%8F%91%E7%89%8C/README.md)
- [Out-of-Bounds Memory Experiments](exercises/%E5%85%B3%E4%BA%8E%E5%8A%A8%E6%80%81%E5%86%85%E5%AD%98%E7%94%B3%E8%AF%B7%E5%90%8E%E8%B6%8A%E7%95%8C%E8%AE%BF%E9%97%AE%E7%9A%84%E6%B7%B1%E5%BA%A6%E8%AE%A8%E8%AE%BA/README.md)
- [Basic TString Class](exercises/%E7%AE%80%E5%8D%95%E7%9A%84TString%E7%B1%BB/README.md)
- [Matrix Addition](exercises/%E7%9F%A9%E9%98%B5%E5%8A%A0%E6%B3%95/README.md)
- [Linked Lists](exercises/%E9%93%BE%E8%A1%A8/README.md)
- [Linked List Reallocation](exercises/%E9%93%BE%E8%A1%A8%E4%BA%8C%E6%AC%A1%E7%94%B3%E8%AF%B7/README.md)
- [Ping Argument Parsing](exercises/%E6%A8%A1%E6%8B%9Fping%E7%9A%84%E5%8F%82%E6%95%B0%E8%A7%A3%E6%9E%90/README.md)
- [Numerical Integration](exercises/%E6%B1%82%E5%AE%9A%E7%A7%AF%E5%88%86/README.md)
- [Shape Areas](exercises/%E6%B1%82%E9%9D%A2%E7%A7%AF/README.md)
- [Pointer Experiments](exercises/%E8%B6%A3%E5%91%B3%E6%8C%87%E9%92%88%E5%88%86%E6%9E%90/README.md)
- [Array References](exercises/%E6%95%B0%E7%BB%84%E7%9A%84%E5%BC%95%E7%94%A8/README.md)
- [Generic Sequential List](exercises/%E9%A1%BA%E5%BA%8F%E8%A1%A8-6%E5%90%881/README.md)
- [Random Student Selection](exercises/%E9%9A%8F%E6%9C%BA%E6%8A%BD%E5%8F%96/README.md)
- [Conditional Compilation](exercises/%E6%9D%A1%E4%BB%B6%E7%BC%96%E8%AF%91/README.md)
- [Bitwise Switches](exercises/%E4%BD%8D%E8%BF%90%E7%AE%97%E6%A8%A1%E6%8B%9F%E5%A4%9A%E5%BC%80%E5%85%B3/README.md)
- [File and Hex Conversion](exercises/%E6%96%87%E4%BB%B6%E4%B8%8Ehex%E6%A0%BC%E5%BC%8F%E4%BA%92%E8%BD%AC/README.md)
- [Student Grade Statistics](exercises/%E5%AD%A6%E7%94%9F%E5%B9%B3%E5%9D%87%E5%88%86%EF%BC%88%E4%BA%8C%E7%BB%B4%E6%95%B0%E7%BB%84%EF%BC%89/README.md)
- [Month Names](exercises/%E6%9C%88%E4%BB%BD%E6%89%93%E5%8D%B0/README.md)
- [Similarity Tool Argument Parsing](exercises/%E4%BD%9C%E4%B8%9A%E7%9B%B8%E4%BC%BC%E5%BA%A6%E5%8C%B9%E9%85%8D%E5%8F%82%E6%95%B0%E8%A7%A3%E6%9E%90/README.md)
- [BMP Image Reader](exercises/bmp%E5%9B%BE%E5%83%8F%E8%AF%BB%E5%8F%96/README.md)
- [Date Class](exercises/Data%E7%B1%BB/README.md)
- [DateTime Class](exercises/DateTime%E7%B1%BB/README.md)
- [Hello World](exercises/HelloWorld/README.md)
- [Student and Teacher Conversions](exercises/Student%E4%B8%8ETeacher%E4%BA%92%E8%BD%AC/README.md)
- [C and C++ Experiments](exercises/TEST_HOMEWORK/README.md)
- [TString Class](exercises/TString%E7%B1%BB/README.md)
- [TStringAdv Class](exercises/TStringAdv%E7%B1%BB/README.md)
- [Line Ending Conversion](exercises/Windows-Linux%E6%96%87%E4%BB%B6%E6%A0%BC%E5%BC%8F%E6%B5%8B%E8%AF%95%E5%8F%8A%E4%BA%92%E8%BD%AC/README.md)

## Projects

[BigHW](projects/BigHW/README.md) includes Tower of Hanoi, PopStar, Tetris, HDC drawing, BMP subtitles, text comparison, and database-backed coursework tools.

## Build

Build each exercise independently. Compile implementation files with their corresponding entry point; keep programs with different main functions separate.

Most source files use GBK/CP936. For GCC, use `-finput-charset=GBK -fexec-charset=GBK`; for MSVC, use `/source-charset:.936 /execution-charset:.936`. For example, from the month-name source directory:

```sh
g++ -std=c++11 -finput-charset=GBK -fexec-charset=GBK 12-b3.cpp -o month
```

Windows console and graphics programs require the Windows SDK. Project-specific inputs and dependencies are listed in their READMEs.
