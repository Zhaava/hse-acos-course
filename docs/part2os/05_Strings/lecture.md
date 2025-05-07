Lecture 5
---

# Dynamic Memory Allocation

## Lecture

Slides ([PDF](OS_Lecture_05.pdf), [PPTX](OS_Lecture_05.pptx)).

#### Outline

* Heap management and dynamic memory allocation
* `malloc` package
* Internal and external fragmentation
* Implicit and explicit lists, segregated lists, sorting blocks by size
* Headers and footers
* Placement policies
* Splitting and coalescing

#### Example

Simple `malloc` [implementation](memory/malloc.c) based on an implicit list and the first-fit policy.

Try using it to allocate memory for various programs. For example:
```cpp
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::string s = "Hello World!";
  std::cout << s << std::endl;
  std::vector<int> v(20, 0);
  int *pp = new int[10];
  delete pp;
  std::string text = "This is some random very long text!";
  return 0;
}
```
```bash
make runcpp
gcc -Wall -g -shared -fpic -o libmalloc.so malloc.c
g++ test.cpp -o testcpp
LD_PRELOAD="./libmalloc.so" ./testcpp
malloc(73728)
malloc is initialized
start=0x56f5dd354000
end=  0x56f5dd355000
head= 0x56f5dd354008
malloc(73728) = 0x56f5dd354008
malloc(1024)
malloc(1024) = 0x56f5dd366010
Hello World!
malloc(80)
malloc(80) = 0x56f5dd366418
malloc(40)
malloc(40) = 0x56f5dd366470
free(0x56f5dd366470)
malloc(36)
malloc(36) = 0x56f5dd366470
free(0x56f5dd366470)
free(0x56f5dd366418)
```

## Workshop

Workshop on strings in C language is [here](strings/workshop.md).

See the __Homework__ in the workshop materials.

# References

* Dynamic Memory Allocation. Section 9.9 in [[CSPP]](../../books.md)
* Interlude: Memory API. Chapter 14 in [[COMET]](../../books.md)
* Free-Space Management. Chapter 17 in [[COMET]](../../books.md)
* Memory Allocation. Chapter 7 in [[TLPI]](../../books.md)
* [C dynamic memory allocation](https://en.wikipedia.org/wiki/C_dynamic_memory_allocation) (Wikipedia)
* [Malloc tutorial](https://danluu.com/malloc-tutorial/)
* [Memory Allocators](https://github.com/mtrebi/memory-allocators)
* [jemalloc](https://jemalloc.net/) (example of malloc implementation)
