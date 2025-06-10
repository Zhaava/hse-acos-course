# Контрольная Работа: Операционные Системы (Модуль 4)

__Ссылка на форму для отправки ответов [здесь](https://forms.gle/R1GwrvgQNsTotrhj9).__

Формула оценки:

__Оценка = 0.4 * Теория + 0.6 * Задача__

## Часть 1. Теоретические Вопросы

Answer the theoretical questions in a few sentences (1-2 paragraphs for a question).

Use __your own words__.
Copy-paste from external sources and other students will result in 100% penalty.

1. Memory management.
   * Memory layout of a program: What memory segments do you know? What purposes do they serve?
   * What ways to allocate memory do you know?
   * How dynamic memory allocation via `malloc`/`free` is implemented (using what data structures)?
   * Give definitions of payload, fragmentation (internal and external), and placement strategies.
   * What is the purpose of the `sbrk` system call? 

1. Processes.
   * What is a process? What parts does it contains (its layout in memory)?
   * List the states of a process and describe how it changes states.
   * What is Process Control Block (`PCB`)? What information does it contain?
   * Describe the idea of process creation with system calls `fork` and `exec`. What is the role of system call `wait`?
   * How to see the list of running processes in Linux (what system utilities do you know)?
     What Linux system folder does contain information about running processes?

1. Permissions.
   * What access rights do you know? What permission groups do you know?
   * How to view and how to change file permissions (what utility tools to use)? How to change file ownership?
   * Give definitions of hard and soft links, explain the differences between them. How to create links?
   * Explain the `setuid`/`setguid` permissions.
   * Study the text below. What can you say about `file1`, `file2`, `file3`, and `file4`?
   
   ```bash
   (base) andrewt@ThinkPad-T490s:~/Documents/src/hse/temp$ ls -li
   total 36
   35140286 drwxrwxr-x 2 acos   acos  4096 Jun 17 09:03 file1
   35140287 -rwxrwsr-x 2 myuser acos 15776 Jun 17 09:01 file2
   35140288 lrwxrwxrwx 1 acos   acos     5 Jun 17 09:03 file3 -> file1
   35140287 -rwxrwsr-x 2 myuser acos 15776 Jun 17 09:01 file4
   ```

## Часть 2. Задача По Программированию

Write a program in C that does the following:

* Calculates the value of the specified function `f(x)` in the range from `argv[1]` to `argv[2]` with step `argv[3]`.
* Writes pairs `x, f(x)` into text file `output.csv` ([CSV](https://en.wikipedia.org/wiki/Comma-separated_values) format).  
* The function to be calculated has the following format:
  ``` 
  f(x) = f0(f1(x), f2(x), f3(x), f4(x))
  ```
  , where:
    * `x` is the function argument;
    * `f0`-`f4` are functions that are individual according to the variant.

### Example of Function (you need your variant, see below)

_Note_: the `^` symbol means "power".

    f0(a, b, c, d) = (a - b + c - d) / 2
    f1(x) = 2*x^3 - 4*x^2 + 3*x + 1
    f2(x) = sin(5*x)*4 + 3
    f3(x) = 1 / (1 + e^(-7*x))
    f4(x) = 2^x + 5

### Requirements and Grades

* ___4 Points___:
  make all calculations and write to file in a __parent__ process;
  provide a Makefile to build the program;
* ___5 Points___:
  write to a file using output redirection (redirect the standard output
  to the file using [dup2](https://man7.org/linux/man-pages/man2/dup.2.html));
* ___6 Points___:
  make all calculations and write to the file in a __child__ process
  (use [fork](https://man7.org/linux/man-pages/man2/fork.2.html));
* ___8 Points___:
  execute the __f0__ function for the entire value range in a __child__ process
  and send the resulting values to the parent process using
  a [pipe](https://man7.org/linux/man-pages/man2/pipe.2.html);
* ___10 Points___:
  execute __f0__ in the __parent__ process and __f1__-__f4__ in separate __child__ processes;
  return the calculated values of __f1__-__f4__ to __f0__ using a pipe (you will need 4 pipes).

### Hints

* Function `f0` have the following  structure:
  ```c
  double f0(double a, double b, double c, double d) {
      return <math expr>;
  }
  ```
* Functions `f1`-`f4` have the following  structure:
  ```c
  double f1(double x) {
      return <math expr>;
  }
  ```
* Command-line arguments (strings) can be converted to `double` using the [atof](
  https://man7.org/linux/man-pages/man3/atof.3.html) function.
* Mathematical functions (such as `sin`, `cos`, `pow`, `exp` etc.) and constants (`M_E`) are in the [math.h](
  https://man7.org/linux/man-pages/man0/math.h.0p.html) library.
  The program must be linked with the library: use the `-lm` GCC flag.
* To write to a file, [open](https://man7.org/linux/man-pages/man2/open.2.html) the file and redirect the standard output
  (`STDOUT_FILENO`) to this file with the [dup2](https://man7.org/linux/man-pages/man2/dup.2.html) system call.
  When you do this, you will be able to use `printf` to print to the file. If you do this in the parent process,
  redirection will work in both processes (parent and child).
* Sending data from child to parent using a pipe: see example in the [manual](
  https://man7.org/linux/man-pages/man2/pipe.2.html).
  * _Child_: `f(x)` is calculated for a range of values and results (`x` and `f(x)`) are written (`write(pfd[1], &x, sizeof(x))`) to the pipe;
  * _Parent_: results (`x` and `f(x)`) are read (`read(pfd[0], &x, sizeof(x))`) from the pipe in a loop and printed.
 
### Варианты

Выберите __свой номер варианта__ согласно своему номеру в группе. Списки групп здесь:

* [КНАД 231](https://github.com/andrewt0301/hse-acos-course/blob/master/docs/software/ejudge/compds_231.csv)
* [КНАД 232](https://github.com/andrewt0301/hse-acos-course/blob/master/docs/software/ejudge/compds_232.csv)
* [ЭАД 231](https://github.com/andrewt0301/hse-acos-course/blob/master/docs/software/ejudge/ead_231.csv)
* [ЭАД 232](https://github.com/andrewt0301/hse-acos-course/blob/master/docs/software/ejudge/ead_232.csv)
* [ЭАД 233](https://github.com/andrewt0301/hse-acos-course/blob/master/docs/software/ejudge/ead_233.csv)
* [ВСН 231/232](https://github.com/andrewt0301/hse-acos-course/blob/master/docs/software/ejudge/vsn_231.csv)

Варианты для групп:

* [КНАД1](variants_2025_compds231.md)
* [КНАД2](variants_2025_compds232.md)
* [ЭАД1](variants_2025_ead231.md)
* [ЭАД2](variants_2025_ead232.md)
* [ЭАД3](variants_2025_ead233.md)
* [ВСН](variants_2025_vsn231.md)

_Замечание_: символ `^` означает возведение в степень.
