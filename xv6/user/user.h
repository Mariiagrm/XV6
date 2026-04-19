
#include <stdint.h>
/* macros para interpretar status devuelto por wait(NULL) */
#define WIFEXITED(status)  ( (((status) & 0x7f) == 0) ) //Comprueba si el proceso terminó normalmente
#define WEXITSTATUS(status) ( (((status) & 0xff00) >> 8) ) //Obtiene el código de salida del proceso
#define WIFSIGNALED(status) ( (((status) & 0x7f) != 0) ) //Comprueba si el proceso terminó debido a una señal

/* macro específico de xv6 para recuperar el número de trap real
   (el kernel devuelve trap+1, por eso restamos 1) */
#define WEXITTRAP(status)   ( (((status) & 0x7f) - 1) ) 
struct stat;
struct rtcdate;

// system calls
extern int fork(void);
extern int exit(int i) __attribute__((noreturn)); /*Toma un entero como codigo de salida*/
extern int wait(int* i);    /*Toma un puntero */
extern int pipe(int*);
extern int write(int, const void*, int);
extern int read(int, void*, int);
extern int close(int);
extern int kill(int);
extern int exec(char*, char**);
extern int open(const char*, int);
extern int mknod(const char*, short, short);
extern int unlink(const char*);
extern int fstat(int fd, struct stat*);
extern int link(const char*, const char*);
extern int mkdir(const char*);
extern int chdir(const char*);
extern int dup(int);
extern int getpid(void);
extern char* sbrk(int);
extern int sleep(int);
extern int uptime(void);
extern int date(struct rtcdate*);
extern int dup2(int oldfd, int newfd);
extern int getprio(int pid);
extern int setprio(int pid, unsigned int prio);

// ulib.c
extern int stat(const char*, struct stat*);
extern char* strcpy(char*, const char*);
extern void *memmove(void*, const void*, int);
extern char* strchr(const char*, char c);
extern int strcmp(const char*, const char*);
extern void printf(int, const char*, ...);
extern char* gets(char*, int max);
extern uint32_t strlen(const char*);
extern void* memset(void*, int, uint32_t);
extern void* malloc(uint32_t);
extern void free(void*);
extern int atoi(const char*);
