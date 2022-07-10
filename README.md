Clang Tidy 介绍
===================

目录
---

- [介绍](#介绍)
- [安装](#安装)
- [静态检查](#静态检查)
- [自动重构代码](#自动重构代码)
- [参考](#参考)

介绍
---

clang-tidy 是一个基于 clang 的 C++“linter”工具。 

它的目的是提供一个可扩展的框架，用于诊断和修复典型的编程错误，如样式违规、接口滥用或可以通过静态分析推断的错误。 

clang-tidy 是模块化的，并为编写新检查提供了方便的接口。

通常，我们使用 clang-tidy 来完成以下两件事情，

- 静态检查
- 自动重构代码

安装
---

linux 中安装比较简单，我们以 Ubuntu 为例。

```bash
sudo apt-get install clang-tidy
```

静态检查
------

### 使用命令行

基本的用法如下，

```bash
clang-tidy test.cpp -- -Imy_project/include -DMY_DEFINES ...
```

像这样执行它，该工具将打印一堆警告和注释（如果适用），与 Clang/GCC 提供诊断的方式完全相同。

### 查看可用的检查器

```bash
clang-tidy --list-checks -checks='*' | grep "modernize"
```

自动重构代码
----------

C++11 添加了大量新的 C++ 语言特性，这些特性迄今为止仍未得到充分利用。 最直观的肯定是 auto、override、Lambda 表达式、基于范围的 for、统一初始化语法，等等。 

虽然 C++11 现在已经有好几年了，但仍然有很多代码库没有使用任何新的语言特性，让开发人员移植代码可能是一项令人厌烦的工作 . LLVM 编译器基础设施项目中的 Clang-Tidy 以可以自动重构您的源代码，以便它使用新的语言特性。

### 重构单一文件

```c++
struct Base {
    virtual void reimplementMe(int a) {}
};
struct Derived : public Base  {
    virtual void reimplementMe(int a) {}
};
```

执行以下命令，可以执行 override 检查，

```bash
clang-tidy -checks='modernize-use-override' modernize-use-override.cpp -- -std=c++11
```

可能输出如下提示，

```bash
1 warning generated.
/home/code/clang-tidy/tutorial/checks/modernize/modernize-use-override.cpp:5:18: warning: prefer using 'override' or (rarely) 'final' instead of 'virtual' [modernize-use-override]
    virtual void reimplementMe(int a) {}
    ~~~~~~~~     ^
                                      override
```

它注意到 Derived::reimplementMe(int) 覆盖了一个基类方法，但缺少覆盖说明符！ 现在我们可以手动添加它或者只是让工具通过传递 -fix 来为我们完成它！


```bash
clang-tidy -checks='modernize-use-override' modernize-use-override.cpp -fix -- -std=c++11
```

我们发现 clang-tidy 帮我加上了 override 修饰符

```
diff --git a/checks/modernize/modernize-use-override.cpp b/checks/modernize/modernize-use-override.cpp
index e30edaa..49bd0c3 100644
--- a/checks/modernize/modernize-use-override.cpp
+++ b/checks/modernize/modernize-use-override.cpp
@@ -2,5 +2,5 @@ struct Base {
     virtual void reimplementMe(int a) {}
 };
 struct Derived : public Base  {
-    virtual void reimplementMe(int a) {}
+    void reimplementMe(int a) override {}
 };
 ```

### 重构整个工程

如果你有一个更复杂的项目设置，有很多文件，都带有自定义编译标志，会发生什么？ Clang-tidy 总是对单个文件，或者更确切地说，翻译单元进行操作。 

我们可以帮助该工具为我们在项目中编译的每个翻译单元找出正确的编译标志。 运行它最方便的方法是使用编译命令数据库。 

我们可以使用 CMake 自动生成一个，一旦 compile_commands.json 就位并且 clang-tidy 的工作版本在 PATH 中，就可以使用 run-clang-tidy.py 脚本分析整个代码库（通常作为 安装）。 

#### 生成编译数据库

```bash
cd refactor/project/cmake-based-project
mkdir build
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
```

#### 启动脚本

```
run-clang-tidy
```

这将会根据编译命令数据库来分析代码，如果要对整个项目重构，可以执行以下命令，

```bash
run-clang-tidy -header-filter='.*' -checks='-*,modernize-use-override' -fix
```

#### 添加其他检查器

```bash
run-clang-tidy -header-filter='.*' -checks='-*,modernize-use-nullptr' -fix
```


参考
---

* [clang-tidy-documentation](https://clang.llvm.org/extra/clang-tidy/)