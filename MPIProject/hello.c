#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <string.h>

#define SHM_SIZE 1024
#define SEM_NAME "/semaphore_example"

int main(int argc, char *argv[]) {

	// girilen proses sayısı 2'den az ise haberlesme olamayacagi icin koyulan condition.
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <num_processes>\n", argv[0]);
        exit(1);
    }

    int num_processes = atoi(argv[1]);

    int shm_fd;
    char *shared_memory;
    sem_t *sem;

    // Paylaşımlı bellek oluşturma ve açma
    shm_fd = shm_open("shared_memory", O_CREAT | O_RDWR, 0666);
    if (shm_fd < 0) {
        perror("shm_open");
        exit(1);
    }
    // paylasimli bellegin boyutunu ayarla.
    ftruncate(shm_fd, SHM_SIZE);
    shared_memory = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_memory == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Semafor oluşturma ve açma
    sem = sem_open(SEM_NAME, O_CREAT, 0644, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    pid_t pids[num_processes]; //surec id'lerini tut.
    for (int i = 0; i < num_processes; i++) {
        if ((pids[i] = fork()) == 0) { // cocuk proses olustur.
            char message[SHM_SIZE];
            if (i % 2 == 0) { // Cift numaralı surecler
                snprintf(message, sizeof(message), "Message from process %d", i + 1);
                // Mesaj gönderme
                sem_wait(sem);
                strcpy(shared_memory, message);
                sem_post(sem);
                
                // Mesaj alma
                sem_wait(sem);
                printf("Process %d received message: %s\n", i, shared_memory);
                sem_post(sem);
            } else { // Tek numaralı surecler
                // Mesaj alma
                snprintf(message, sizeof(message), "Message from process %d", i - 1);
                
                // Mesaj gönderme
                sem_wait(sem);
                strcpy(shared_memory, message);
                sem_post(sem);
                
                sem_wait(sem);
                printf("Process %d received message: %s\n", i, shared_memory);
                sem_post(sem);
                
            }
		// Ana surec, cocuk sureclerin tamamlanmasini bekler.
            exit(0);
        }
    }
	
    for (int i = 0; i < num_processes; i++) {
    	// ana surec, cocuk sureclerin tamamlanmasini bekler.
        wait(NULL);
    }

    // Temizlik işlemleri
    sem_close(sem); // semaforu kapat.
    sem_unlink(SEM_NAME); // semaforu sistemden sil.
    munmap(shared_memory, SHM_SIZE); // paylasimli bellegi bellekten cikar.
    shm_unlink("shared_memory"); // paylasimli bellek nesnesini sistemden sil.

    return 0;
}

