#include "types.h"
#include "user.h"
#include "stat.h"

void child_process(char ch, int Prioridad, int n_times, int sleep_time) {
    setprio(getpid(), Prioridad);
    for (int i = 0; i < n_times; i++) {
        printf(1, "%c ", ch);
        if(sleep_time >= 0) 
            sleep(sleep_time); // Los procesos normales duermen y ceden CPU
        
    }
    exit(0);
}

void ejecutaProcesos() {
    printf(1, "\nLanzando A, B, C (Prioridad 9) y * (Prioridad 5)...\n");
    
    // Procesos de baja prioridad (duermen mucho, dejan huecos)
    for (int i = 0; i < 3; i++) {
        if (fork() == 0) child_process('A' + i, 9, 70, 20);
    }
    if (fork() == 0) child_process('*', 5, 70, 20);

    printf(1, "Tienes 3 segundos. Escribe 'ls' AHORA!\n");
    
    // Tiempo para que uses la terminal
    sleep(200); 

    printf(1, "\n\n!!! LLEGAN X y Z (Prioridad 0) \n");
    printf(1, "La terminal deberia morir aqui.\n");

    // --- MONOPOLIZADORES ---
    // Prioridad 0, N_times 15, Sleep_time 0 
    if (fork() == 0) child_process('X', 0, 40, 1); 
    if (fork() == 0) child_process('Z', 0, 40, 1);


    // Esperar a todos
    for (int i = 0; i < 6; i++) wait(0);
    
    exit(0);
}

int main(int argc, char *argv[]) {
    // Truco para liberar la Shell inmediatamente
    int pid = fork();
    if (pid < 0) exit(0);

    if (pid > 0) { //Padre
        exit(0); // Matamos al padre para porder usar el shell
    } else {
        ejecutaProcesos(); // Dejamos el ejecutador de procesos trabajando en background
    }
    return 0;
}