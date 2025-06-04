Lecture 15
---
# Compiler Infrastructure LLVM/Clang

## Lecture

Slides: [PDF](slides_14.pdf), [PPTX](slides_14.pptx)

Notes: [PDF](nodes_14.pdf)

#### Outline

* LLVM Project: history and architecture
* LLVM IR
* Clang: parser and static analysis tool
* Clang Static Analyzer and its symbolic execution engine
* Clang Extra Tools: Clang-Tidy

## Workshop

#### Outline

* Compiling/Installing LLVM
* Compiling C/C++ programs to executables and LLVM IR
* Exploring C/C++ programs with Clang (tokens, AST, call graph, CFG, exploded graph)
* Running Clang Static Analyzer
* Exploring Clang Static Analyzer and Clang-Tidy checks

#### Installing Clang

Clang is already installed in Mac OS. In Linux, it can be installed using the following command:

```bash
sudo apt install clang
```

#### Building Clang (optional, takes a long time)

For studying Clang source code, making experiments, and using features available to developers,
it is recommended to clone its sources from GitHub and build them.
_Warning: this may take several hours depending on your computer._

##### Cloning project from GitHub and checking our LLVM 20 (latest release):

```bash
git clone git@github.com:llvm/llvm-project.git
git checkout llvm-20
```

##### Installing visualization packages

Graphs that visualize internal data structures of a compiler
are described in the [DOT](https://en.wikipedia.org/wiki/DOT_%28graph_description_language%29)
format and rendered to an image with the help of the
[Graphviz](https://en.wikipedia.org/wiki/Graphviz) tool.

First, install the required visualization tools: 

```bash
sudo apt install graphviz
sudo apt install gv
sudo apt install xdot
sudo apt install python3-distutils-extra
```

Second, install the [Ninja](https://en.wikipedia.org/wiki/Ninja_%28build_system%29) build system.
It solves the same task as GNU Make, but it has better performance
(automatically generated scripts that efficiently parallelize build tasks). 

```bash
apt install python3-distutils-extra
```

Third, build and install LLVM compiler infrastructure (this is a debug build with
some optimizations that reduce build time and size of the files).
That is interesting, we build a debug version of Clang 20, with installed version of Clang 18.

```bash
cd /home/andrewt/Documents/src/llvm-project/
mkdir build
cd build
env CC=`which clang` CXX=`which clang++` cmake \
  -DCMAKE_BUILD_TYPE=Debug \
  -GNinja \
  -DLLVM_ENABLE_PROJECTS='clang;clang-tools-extra' \
  -DLLVM_TARGETS_TO_BUILD="X86" \
  -DBUILD_SHARED_LIBS=ON \
  -DLLVM_OPTIMIZED_TABLEGEN=ON \
  -DLLVM_USE_SPLIT_DWARF=ON \
  -DCMAKE_INSTALL_PREFIX=/home/andrewt/Programs/llvm/ \
  ../llvm
ninja install
export PATH=/home/andrewt/Programs/llvm/bin:$PATH
```

#### Build Hello World and viewing build phases

Build and run the [hello.c](hello.c) program:
```bash
clang hello.c -o hello
./hello 
Hello!
```
Build and see the list of build phases:
```bash
clang hello.c -o hello -ccc-print-phases
            +- 0: input, "hello.c", c
         +- 1: preprocessor, {0}, cpp-output
      +- 2: compiler, {1}, ir
   +- 3: backend, {2}, assembler
+- 4: assembler, {3}, object
5: linker, {4}, image
```

* [test.c](
  https://github.com/andrewt0301/static-analysis-course/tree/main/docs/lectures/14/examples/test.c)



##### Exploring `test.c`:

1. Dump tokens:
   ```bash
   clang -cc1 -dump-tokens test.c
   ```

2. Dump and view AST:
   ```bash
   clang -cc1 -ast-dump test.c
   clang -cc1 -ast-view test.c
   ```

3. Dump and view call graph:
   ```bash
   clang -cc1 -analyze -analyzer-checker="debug.DumpCallGraph" test.c
   clang -cc1 -analyze -analyzer-checker="debug.ViewCallGraph" test.c
   ```

4. View CFG and Exploded Graph:
   ```bash
   clang -cc1 -analyze -analyzer-checker="debug.ViewCFG" test.c
   clang -cc1 -analyze -analyzer-checker="debug.ViewExplodedGraph" test.c
   ```

## References

* [LLVM](https://en.wikipedia.org/wiki/LLVM) (Wikipedia)
* [Clang](https://en.wikipedia.org/wiki/Clang) (Wikipedia)
* [LLVM Web Site](https://llvm.org/)
* [LLVM Project](https://github.com/llvm/llvm-project) (GitHub)
* [Clang Static Analyzer - A Checker Developer's Guide](
  https://github.com/haoNoQ/clang-analyzer-guide/releases/download/v0.1/clang-analyzer-guide-v0.1.pdf)
* [[LLVM]](../../books.md#tool-books) Chapters 2, 3, 4, 5, 9, 10
* [LLVM Language Reference Manual](https://llvm.org/docs/LangRef.html)
