#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  int status;
  if(argint(0, &status) < 0)
    return -1;
  //Dejamos los bits bajos libres para la señal
  exit((status & 0xff) << 8); // Guardamos el estado de salida en los bits altos para que wait pueda recuperarlo
  return 0;  // not reached
}

int
sys_wait(void)
{
  int *status;
  //Comprobamos que el puntero este dentro del espacio de direcciones del proceso
  if(argptr(0, (void**)&status, sizeof(int*)) < 0)
    return -1;
  return wait(NULL);
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_date(void)
{
  struct rtcdate *d;

  /*
  a) lee el valor entero del n-ésimo argumento (ese entero es la dirección virtual que el proceso usuario pasó).
b) comprueba que esa dirección no es negativa y que la región [addr, addr+size) está dentro del espacio de direcciones de usuario del proceso (por ejemplo addr >= 0 && addr + size <= proc->sz).
c) si la comprobación falla retorna -1 (error).
d) si pasa la comprobación, escribe en *pp el valor del puntero (normalmente como char * o void *). Esa dirección será usada por el kernel para leer/escribir en la memoria del proceso.

En C: (void )&d toma la dirección de la variable d (que tiene tipo struct rtcdate), la convierte a tipo void* para ajustarse a la firma de argptr. Tras la llamada, d contiene la dirección (castada) que el usuario pasó y que ya ha sido validada por argptr.

Por qué no argint
argint extrae un argumento de tipo entero (int). Si usases argint para leer la dirección del buffer obtendrías un int con el valor de la dirección, pero no habría validación de que esa dirección sea accesible para el proceso (ni conversión segura a puntero). argptr realiza la validación necesaria para punteros (espacio y tamaño). */
  
  if(argptr(0,(void **)&d, sizeof(struct rtcdate))<0)
    return -1;

  cmostime(d);
  return 0;
}

//Ejercicio 1:
int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  
  if(n < 0){  //sbrk negativo
    if (growproc(n) < 0) //asignamos memoria para reducir el sbrk
      return -1;
  } else {  //sbrk positivo
    myproc()->sz += n; 
  }
  return addr; 
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int 
sys_getprio(void)
{
  int pid;
  
  if(argint(0, &pid) < 0)
    return -1;
  
  
  return getprio(pid);
}

int 
sys_setprio(void)
{
  int pid;
  unsigned int prio;
  
  if(argint(0, &pid) < 0)
    return -1;
  if(argint(1, (int*)&prio) < 0)
    return -1;
  if(prio >= NPRIO)
    return -1;
    
  return setprio(pid,prio);
}
