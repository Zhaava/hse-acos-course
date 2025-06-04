![SiFive HiFive Unleashed](images/hifive-unleashed-logo.png)

# Welcome to Computer Architecture and Operating Systems

This site contains materials for the "Computer Architecture and Operating Systems".
For information on course administration (grades, deadlines, etc.), please refer to the university website.

* __DSBA__:
  [wiki](http://wiki.cs.hse.ru/ACOS_DSBA_2024/25) and
  [syllabus](https://www.hse.ru/edu/courses/476614465)
* __COMPDS/EAD/VSN__:
  [wiki](http://wiki.cs.hse.ru/ACOS_COMPDS_2024/2025) and
  [syllabus](https://www.hse.ru/edu/courses/476614465)

## Course Motivation

This course is taught to second-year students who major in computer science.
The goal of the course is to give an introduction to how operating systems and hardware work under the hood,
which is essential for general computer science literacy.
This knowledge will help better understand the performance of software systems and create more efficient solutions.
The practical part will give some experience in working with system software such as Unix-based operating systems,
compilers, build tools, emulators, virtual machines, and so on. 

## Course Description

The course consists of two logical parts.
The first part is given in __module 3__ and is dedicated to computer architecture and assembly language programming.
This part is based on the [RISC-V](https://en.wikipedia.org/wiki/RISC-V) instruction set architecture
and its assembly language.
The second part is given in __module 4__ and covers foundations of operating system organisation and system programming.
The main tools for this part are the [Linux](https://en.wikipedia.org/wiki/Linux) operating system and
the [C programming language](https://en.wikipedia.org/wiki/C_%28programming_language%29).

__Calendar plan by weeks can be found [here](calendar_2025.md).__

### Computer Architecture and Assembly Language

1. [Introduction. Course motivation. Historical perspective.](part1ca/01_Introduction/lecture.md)
1. [Data types. Byte ordering. Integer formats.](part1ca/02_DataTypes/lecture.md)
1. [Computer organization. Microprocessor. RISC and RISC-V. Assembly language.](part1ca/03_CPU/lecture.md)
1. [RISC-V instructions. Instruction formats.](part1ca/04_Instructions/lecture.md)
1. [Pseudo instructions, macros, and includes. Conditions, loops, loads, and stores.](part1ca/05_MacrosBranchesArrays/lecture.md)
1. [Subroutines. Call stack. Calling conventions.](part1ca/06_CallStack/lecture.md)
1. [Floating-point format. IEEE 754. Floating-point instructions.](part1ca/07_FP/lecture.md)
1. [Memory and caches.](part1ca/08_Caches/lecture.md)
1. [Virtual memory.](part1ca/09_VM/lecture.md)
1. [Processor and pipeline.](part1ca/10_Pipeline/lecture.md)
1. [Exceptions and interrupts.](part1ca/11_Exceptions/lecture.md)
1. [Input/Output](part1ca/12_MMIO/lecture.md).
1. [Instruction-level parallelism: Multiple issue and out-of-order execution.](part1ca/13_MultiIssue/lecture.md)
1. [Thread-level parallelism.](part1ca/14_TLP/lecture.md)
1. [Optimizations.](part1ca/15_Optimize/lecture.md)

All homeworks for "Computer Architecture and Assembly Language"
are [here](part1ca/Tasks/homeworks.md).

Final test for Computer Architecture is [here](part1ca/final_tests.md).

### Operating Systems and System Programming

1. [Operating system architecture. Linux.](part2os/01_OS_Architecture/lecture.md)
1. [C programming language.](part2os/02_C/lecture.md)
1. [System calls.](part2os/03_SystemCalls/lecture.md)
1. [Executable file format. Linking and loading.](part2os/04_Linking/lecture.md)
1. [Dynamic memory allocation and string handling.](part2os/05_Strings/lecture.md)
1. [Processes and threads.](part2os/06_Processes/lecture.md)
1. [I/O and files.](part2os/07_Synch/lecture.md)
1. [Synchronization.](part2os/08_IPC/lecture.md)
1. [Inter-process communication.](part2os/09_IPC/lecture.md)
1. [Users, groups, and permissions.](part2os/10_Permissions/lecture.md)
1. [Virtual Machines.](part2os/11_VM/lecture.md)
1. [Networking.](part2os/12_Networking/lecture.md)
1. [Sockets.](part2os/13_Sockets/lecture.md)
1. [High-level Languages and Operating System.](part2os/14_Python/lecture.md)

Final test for Operating Systems is [here](part2os/final_tests.md).

### Additional Chapters

1. [Domain-specific architectures. Tensor Processing Unit.](part1ca/16_TPU/lecture.md)
2. [Compiler infrastructure Clang/LLVM](part2os/15_Clang/lecture.md)

## Exam

Exam questions are [here](exam_latest.md).

## Grading System

Information on the grading system for the course is [here](grades.md).

## Related Materials

* Textbooks used in this course are [here](books.md).
* Software used in this course can be found [here](software.md).
* Similar courses by other universities can be found [here](courses.md).
* Other useful links are [here](links.md).

## Feedback

If you have any questions or suggestions related to the course content, please feel free to submit
an [issue](https://github.com/andrewt0301/hse-acos-course/issues)
or contact the course [author](https://github.com/andrewt0301). 
If you like the course, you are welcome to star it in
[GitHub](https://github.com/andrewt0301/hse-acos-course).
