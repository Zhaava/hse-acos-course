//
// trace(format, ...) - macro for printing debug messages
//
#ifdef NDEBUG
  #define trace(format, ...)
#else
  #include <stdio.h>
  #define trace(format, ...) do {                                  \
    char buff[64];                                                 \
    int len = snprintf(buff, sizeof(buff), format, ##__VA_ARGS__); \
    write(STDOUT_FILENO, buff, len);                               \
  } while (0)
#endif
