Lecture 7
---

# I/O and Files

## Lecture

Slides ([PDF](OS_Lecture_07.pdf), [PPTX](OS_Lecture_07.pptx)).

#### Outline

* Files and folders in Linux
* Directory hierarchy in Linux
* Virtual file system and basics of Ext4
* System calls for working with files and folders
* Standard I/0, file descriptors and redirection
* Function of C standard library (libc) for working with I/0

#### Examples

Copying `stdin` to `stdout`, one byte at a time:
```c
#include <unistd.h>
int main(void) {
    char c;
    while(read(STDIN_FILENO, &c, 1) != 0)
    write(STDOUT_FILENO, &c, 1);
    return 0;
}
```

Accessing file metadata:
```c
#include <sys/stat.h>
#include <stdio.h>

int main (int argc, char **argv) {
    struct stat st;
    char *type, *readok;
    stat(argv[1], &st);
    if (S_ISREG(st.st_mode)) /* Determine file type */
        type = "regular";
    else if (S_ISDIR(st.st_mode))
        type = "directory";
    else
        type = "other";
    if ((st.st_mode & S_IRUSR)) /* Check read access */
        readok = "yes";
    else
        readok = "no";
    printf("type: %s, read: %s\n", type, readok);
    return 0;
}
```

Reading a directory to get the list of files (`ls`-like program):
```c
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
int main(int argc, char *argv[]) {
    DIR *directory;
    struct dirent *de;
    const char *dir_name = argv[1];
    if (!(directory = opendir(dir_name))) {
        perror("Failed to open directory");
        return 1;
    }
    while ((de = readdir(directory))) {
        printf("Found file: %s\n", de->d_name);
    }
    closedir(directory);
    return 0;
}
```

Buffering provided by the standard C library:
```
#include <stdio.h>
int main() {
    printf("h");
    printf("e");
    printf("l");
    printf("l");
    printf("o");
    printf("\n");
    fflush(stdout);
    return 0;
}
```

`strace` utility shows that many `printf` calls result in a single system call `write`:
```
strace -e trace=write  ./hello 
write(1, "hello\n", 6hello
)                  = 6
+++ exited with 0 +++
```

## Workshop

[Workshop: Shell Scripts](../06_Processes/bash.md) 

## Homework

__TODO__

# References

* [Filesystem Hierarchy Standard](https://en.wikipedia.org/wiki/Filesystem_Hierarchy_Standard) (Wikipedia)
* [Overview of the Linux Virtual File System](https://docs.kernel.org/filesystems/vfs.html)
* [Inode](https://en.wikipedia.org/wiki/Inode) (Wikipedia)
* [ext4 Data Structures and Algorithms](https://www.kernel.org/doc/html/latest/filesystems/ext4/index.html)
* Oracle Linux Blog. Understanding Ext4 Disk Layout.
  [Part 1](https://blogs.oracle.com/linux/post/understanding-ext4-disk-layout-part-1) and
  [Part 2](https://blogs.oracle.com/linux/post/understanding-ext4-disk-layout-part-2)
