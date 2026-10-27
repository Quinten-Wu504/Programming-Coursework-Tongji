# Coursework Checker

Read configuration and student records, check submissions, perform cross-checks, and access coursework data through MariaDB.

Requires MariaDB Connector/C, a configured database, configuration files, and submission files.

## Build

Compile these source files together, with paths relative to this directory:

- `../common/class_aat.cpp`
- `../common/class_crt.cpp`
- `../common/common_database_tools.cpp`
- `../common/common_string_process.cpp`
- `class_cross_check_list.cpp`
- `class_dbcfg.cpp`
- `class_stuinfo.cpp`
- `hw_check.cpp`
- `hw_check_action.cpp`
