# BigHW Projects

C++ projects covering console games, graphics, command-line tools, configuration files, and databases.

## Projects

- [Tower of Hanoi](90-01-b1/README.md): Solve and visualize Tower of Hanoi using recursion, state tracking, and menu-driven console displays.
- [PopStar](90-01-b2/README.md): Generate a grid of stars, select connected groups to remove, update the board, and calculate scores using numeric and console-graphics views.
- [Tetris](90-02-b1/README.md): Implement piece generation, rotation, movement, collision detection, line clearing, scoring, and levels in a console game.
- [HDC Drawing](90-02-b2/README.md): Draw mathematical graphics and cartoon characters using Windows HDC, with a drawing test harness.
- [BMP Subtitles](bmp_subtitles/README.md): Render text onto BMP images using command-line options, bitmap processing, and character glyph data.
- [Coursework Checker](hw_check/README.md): Read configuration and student records, check submissions, perform cross-checks, and access coursework data through MariaDB.
- [Ping-Style CLI](my_ping/README.md): Demonstrate ping-style option declarations, parsing, and validation using the shared argument-analysis class.
- [Argument Parser Tests](test_args_analyse_tools/README.md): Exercise option types, constraints, and parsing results for the argument-analysis class in common/class_aat.cpp.
- [MariaDB Demo](test_mariadb/README.md): Connect to MariaDB and run queries using the C API.
- [Configuration Reader Tests](test_readcfg/README.md): Read configuration groups and values using class_crt and the shared argument parser.
- [Console Toolkit Tests](test-cct/README.md): Exercise Windows console cursor positioning, colors, and interactive display functions.
- [Text Comparison](txt_compare/README.md): Compare two text files using configurable command-line options and shared string-processing utilities.
- [Shared Implementations](common/README.md): Shared implementations for argument parsing, configuration files, strings, console and HDC drawing, mathematics, and database access.
- [Shared Headers](include/README.md): Declarations for the shared classes, console interfaces, and utility functions implemented in common.

## Build

Build each application separately using the source list in its README. Preserve the relative paths to `common` and `include`.

Console and graphics projects require Windows and the Windows SDK; GDI drawing uses the Gdi32 and User32 libraries. Database projects require MariaDB Connector/C with matching headers and libraries.
