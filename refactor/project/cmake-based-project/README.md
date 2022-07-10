Refactoring a Complete Project
===============================================

Contents
--------

- [Introduction](#introduction)
- [Getting Started](#getting-started)
	- [Usage](#usage)
- [References](#references)

Introduction
------------

Getting Started
---------------

### Generating Compile Database

``` bash
mkdir build
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
```

### Run Clang-Tidy

``` bash
run-clang-tidy
``` 

References
----------

* [modernize-avoid-c-arrays](https://releases.llvm.org/11.0.1/tools/clang/tools/extra/docs/clang-tidy/checks/modernize-avoid-c-arrays.html#modernize-avoid-c-arrays)
* [modernize-use-override](https://releases.llvm.org/9.0.1/tools/clang/tools/extra/docs/clang-tidy/checks/modernize-use-override.html)
