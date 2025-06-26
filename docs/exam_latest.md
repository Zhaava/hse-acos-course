Exam Questions
---

## Exam Rules

* The exam is oral: 40 minutes for a preparation and 10 minutes for an answer.
* No materials are allowed except for [RISC-V Greencard](
  https://github.com/andrewt0301/hse-acos-course/raw/master/related/greencard-20181213.pdf).
* Exam tickets include 3 questions:
  1. theoretical question on CA;
  2. theoretical question on OS;
  3. programming task (solved on a sheet of paper).

### Grading

__Grade = 0.3 * Theory_CA + 0.3 * Theory_OS + 0.4 * Programming__

### Hint

An answer to each question is expected to take ~3 minutes.
Theoretical questions contain a number of points (subquestions).
For many of them, a simple answer (1 sentence) is enough.
The exam checks your overall understanding of the main concepts.

## Questions

Python script to pick questions at random is [here](exam/exam_random.py).

### Computer Architecture

Printed version is [here](exam/exam_ca_print.pdf).

1. Computer architecture.
   * What main parts do modern computers include?
   * Explain the stored program concept and how a computer executes a program.
   * What is computer architecture? What is computer micro-architecture?
   * What instruction set architectures do you know?
   * What are performance challenges of modern computers?

1. Integer data formats and operations.
   * What is a byte and what is a machine word? What is byte ordering (which ones do you know)?
   * Describe unsigned integer format and 2's complement signed integer format.
   * How unsigned and signed values are converted to decimal numbers?
   * How unsigned values are converted to signed and vice versa?
   * What is the difference between integer sign- and zero-extension?
   * What is the difference between arithmetical and logical shift?

1. Floating-point format.
   * Why floating-point format is needed? Name the standard that covers it.
   * Explain the floating-point format (sign, exponent, fraction). Describe single and double precision.
   * What is implicit `1.` in fraction?  Why exponents are biased (and what is bias)?
   * Explain how the following value types are encoded: zero, normalized number, denormalized number, infinity, NaN.
   * What are floating-point overflow and underflow?
   * How does addition of two floating-point numbers works (the main steps)? 
   * How floating-point format is supported in RISC-V (registers, main instructions)?

1. ISA and assembler language.
   * What is instruction set architecture (ISA)?
   * Give definitions and examples of the following ISA types: RISC, CISC, and VLIW.
   * What are machine code, assembly language, and assembler? What tool converts machine code to assembly language?
   * Describe of the structure of an assembly program (when in text) and its memory layout (when in machine code).
   * Describe main assembly directives (`.text`, `.data`, `.align`, `.space`, etc.). What else do you know?

1. RISC-V.
   * Brief history and advantages of the RISC-V ISA. Design principles of RISC-V.
   * List main RISC-V registers and main instruction types with examples.
   * What is program counter (PC)? What RISC-V instruction can be used to read its value?
   * Briefly describe 6 types of RISC-V instruction encodings (R-type, I-type, etc.).
   * Explain immediate addressing, register addressing, base addressing, and PC-relative addressing.  

1. RISC-V assembly programming.
   * Give a definition of a register. What is the difference between registers and memory?
   * How you you swap values of two registers without using a temporary registers?
   * Give an example of a logic and arithmetical shift instruction. Explain the differences.
   * What load and store instructions do you know? Explain the difference between the `lh` and `lhu` instructions.
   * What control-transfer instructions do you know?
   * Explain the idea of pseudoinstructions. Give examples of RISC-V pseudoinstructions.
   * Explain the idea of macros. When would you use macros? How to reuse macros defined in other `.s` files? 

1. Functions and stack.
   * What is a function? What are caller and callee?
   * How functions are implemented in assembly language? Describe what exception are performed by a function call.
   * Explain the idea of return address and jump-and-link instructions?
   * What are stack, stack pointer, stack (function) frame, and frame pointer? What is stored in the stack?
   * Explain the idea of caller- and callee-saved registers (give examples of such registers).

1. Interrupts and exceptions.
   * What is an interrupt and what is an exception? What RISC-V exceptions do you know?
   * What is the role of Control and Status Registers (CSRs) in handling exceptions?
   * What system instructions do you know?
   * What happens when an exception occurs (how the CPU handles the event)?
   * What is an exception handler? What actions does it perform? How does the CPU know how to call a handler?
   * What is a system call and how does it work?

1. Memory-mapped I/O (MMIO).
   * How I/O devices are connected to CPU and managed (control, data, and status signals)?
   * Explain the idea of Memory-Mapped I/O (MMIO).
   * Explain the idea of Direct Memory Access (DMA).
   * Explain difference between Interrupt-Driven I/O and Polling?
   * What is a device driver?

1. Pipelining.
   * List the 5 stages and give brief descriptions for them.
   * What pipeline hazards are? List the types of hazards and the ways to prevent them (with brief definitions).
   * Give an example of a hazard situation and how it can be handled.
   * What is branch prediction is needed for? How does it work?

1. Caches.
   * Describe how caching mechanism works (block, index, tag, valid bit, dirty bit).
   * Give the definition of associativity (direct-mapped, set associative, fully associative).
   * What is the difference between write-through and write-back?
   * What is replacement policy (what type of policy do you know)?
   * How many cache levels are typical for modern processors?
   * What problem can caches create for multicore processors?

1. Virtual Memory.
   * What is virtual memory (vs. physical memory)?
   * How does address translation work?
   * What is a page table and what information does it contain?
   * What is TLB and why is it needed? That is a TLB miss and how is it handled?
   * What is a page fault?
   * How does memory protection work?

1. Thread-level parallelism.
   * Why do we need thread-level parallelism? What are the challenges of parallel programming?
   * What is Amdahl’s Law?
   * Briefly describe how multi-threading works with: hardware multithreading (hyperthreading), multicore, multiprocessors.
   * What are context and context switch?
   * What is memory coherency problem?

1. Multiple issue processor. Data-level parallelism. Domain-specific architectures.
   * Explain the ide of multiple issues and superscalar microprocessors.
   * How do static multiple issue and dynamic multiple issue work? What is speculation?
   * What are SISD, SIMD, MISD, and MIMD?
   * Summarize the idea of SIMD. How does it help improve performance? Give examples of the SIMD approach in modern computers.
   * Why do we need domain-specific processors? Main principles of modern DSAs. Give an example of a DSA processor.

1. Optimizations.
   * Goal of optimizations? Algorithmic optimizations vs. compiler optimizations (advantages and limitations)?
   * How to assess performance?
   * What optimizations do you know?
   * How does the loop unrolling optimisation work (how it improves performance)?

### Operating Systems

Printed version is [here](exam/exam_os_print.pdf).

1. Operating system architecture.
   * What are main tasks solved by an operating systems (services)?
   * What is operating system kernel?
   * Explain differences between monolithic and microkernel model of OS kernel. What models are used in Linux/MacOS/Windows?
   * Explain the idea of _kernel_ and _user_ modes of a processor.
   * What is a system call and how is it implemented?

1. C programming language. GNU C Library (glibc).
   * C language: brief history, what tasks it solves, advantages over assembly language.
   * What data types are supported in C? What is a pointer? How does `sizeof` work?
   * How to assign and how to dereference a pointer? How does address arithmetic work?
   * What is _glibc_ (GNU C Library) and what tasks does it solve?
   * How are strings are represented in C? What functions to manipulate with strings do you know?
   * Explain the main idea of pattern-matching and regular expressions.

1. Executable and Linkable Format (ELF).
   * What is ELF? What kings of ELF object files do you know? What is their purpose?
   * What data do ELF object files contain?
   * Explain the idea of symbols and symbol table. What kinds of symbols do you know?
   * What happens when several object files are linked together (explain the idea of symbol resolution and relocation)?
   * What does it mean strong and weak symbol? Explain symbol resolution rules.
   * Explain the idea of position-independent code (PIC).

1. Compiling/linking/loading. Static and dynamic libraries.
   * List the compiler stages (steps to turn a C source file to an executable file).
   * What is done at the linking stage? What is the meaning of `static` and `extern` keywords?
   * Explain the idea of static and shared libraries.
   * Explain the idea of run-time loading of shared libraries. What are the advantages of shared libraries?
   * Explain the idea of library interpositioning (compile time, link lime, load/run time). 
   * What tasks are solved with the help of Make files? What are _target_, _source_, and _recipe_ in a Make file?

1. Memory management.
   * Memory layout of a program: What memory segments do you know? What purposes do they serve?
   * What ways to allocate memory do you know?
   * How dynamic memory allocation via `malloc`/`free` is implemented (using what data structures)?
   * Give definitions of payload, fragmentation, and placement strategies.
   * What is the purpose of the `sbrk` system call? 

1. Filesystems. Linux folder structure.
   * What Linux file types do you know?
   * Explain the purpose of the following Linux folders: `/home`, `/bin`, `/sbin`, `/usr`, `/proc`, `/dev`, `/media`. 
   * What is Virtual File Systems (VFS) and what functions does it provide?
   * What are the parts of a Linux disk?
   * What is _inode_? What data does it contain?
   * What is a link? How to create it (what utility tool to use)? What is the difference between hard and symbol links?

1. System calls / system utilities / Shell (Bash).
   * Explain connection between system calls, system utilities and Bash.
   * What is Bash and what tasks does solves?
   * How to get a manual on Linux system utilities and system calls?
   * How (using what special symbols) to access command-line arguments in Bash?
   * What is the role of exit code in a program (e.g. `0` vs. `-1`)? Who exit code can be checked in Bash scripts? 
   * Name Linux utilities that solve these tasks:
      - print current directory;
      - change current directory;
      - print the list of files/folders in the current directory;
      - create new folder;
      - copy file/folder;
      - remove file/folder;
      - move/rename file/folder;
      - print full path to a utility file (e.g. full path to `gcc`).
    * What Bash commands are used to read user input to a variable and to print variable values?

1. File input/output. Pipes and redirection.
   * What system calls are used to read/write data from/to files?
   * What _glibc_ (C Standard Library) function to work with files do you know? Their advantages over system calls?
   * What is a file descriptor? What is descriptor table? What is open file table?
   * List three standard streams of a Linux process and their descriptors.
   * How to redirect process I/O from a terminal to a file?
   * How to connect I/O of two processes?
   * What is a pipe? What system calls are used to manage pipes? 

1. Processes.
   * What is a process? What parts does it contains (its layout in memory)?
   * List the states of the process and describe how it changes states.
   * What is Process Control Block (PCB)? What information does it contain?
   * Explain how CPU switches between processes (context switch).
   * Explain the main idea of short-term, long-term, and medium-term schedulers. What is process swapping?
   * Describe the idea of process creation with system calls `fork` and `exec`. What is the role of system call `wait`?
   * How to see the list of running processes in Linux (what system utilities do you know)?

1. Threads and synchronization.
   * Give a definition of a thread. Explain the difference between a process and a thread.
   * Explain the main idea of consumer-producer problem.
   * Explain the idea of critical section and mutual exclusion.
   * How thread synchronization is supported in hardware?
   * List system calls that are used to manage threads in Linux (pthreads).
   * Explain the main idea of mutexes and conditional variables (pthreads).
   * What is a deadlock?

1. Permissions.
   * What are main attributes of a Linux user and group?
   * What access rights do you know? What permission groups do you know? How to view file permissions (what utility tool to use)? 
   * How to change file permissions (what utility tool to use)? E.g. add write permission to _group_, remove read permission from _other_.
   * Explain the `setuid`/`setguid` permissions.
   * Explain the sticky bit permission.

1. Inter-process communications: signals.
   * Give a definition of a signal. What signals to you know (name and purpose)?
   * How to send a signal to a process (system call and utility tool)?
   * How to set up a custom handler for a signal? It is possible to do this for all signals?
   * Explain the idea of foreground and background processes. How to run a background process?
   * How to switch a process from foreground to background and vice versa?

1. Inter-process communications: message queues, memory mapping, shared memory.
   * Explain the main idea of two models of inter-process communication: shared memory and messages.
   * Describe main features of POSIX message queues. What system calls are used to manage POSIX message queues?
   * How subscribe to get a notification (a signal) when a message is available in the queue?
   * Explain the idea of mapping file into memory? What system call is used for this?
   * Describe main idea of POSIX shared memory. That system calls are used to manage it?

1. Network. Sockets and TCP/IP.
   * Explain the concept of a client-server application.
   * Explain the idea of a network protocol. What is a network packet and what information does it contain?
   * What protocols does the TCP/IP family include?
   * What is MAC address? What is IP address? How domain name (e.g. `www.hse.ru`) is converted to an IP address?
   * Explain the difference between TCP and UDP. What advantages and disadvantages do they have?
   * What is socket? What system calls are done by the client and the server to establish a communication.
   * What is a port? Give examples of network protocols you know and ports they use.  

## Programming

You need to write code in RISC-V assembly on a sheet of paper. You must be able to explain it.

White a function that takes two arguments:
* the pointer to an array of 32-bit integers (`a0`);
* the number of elements in the array (`a1`).

What the function should do is specified in your variant (the list of tasks is not published).

__NOTE__: When implementing a function be careful about callee-saved registers:
(1) do not modify them at all or (2) save them to the stack and then restore.

### Example Variant

The function computes the distance between the smallest and
the largest element in the array and returns it in (`a0`).

### Example Solution

See the `func` function in [this](exam.asm) file.

