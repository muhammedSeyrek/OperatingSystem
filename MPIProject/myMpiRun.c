#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHM_SIZE 1024

// mesaj gonderen MPI fonksiyonu.
void send_message(char *message, int dest) {
    MPI_Send(message, SHM_SIZE, MPI_CHAR, dest, 0, MPI_COMM_WORLD);
}

// mesaj alan MPI fonksiyonu.
void receive_message(char *message, int source) {
    MPI_Recv(message, SHM_SIZE, MPI_CHAR, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

int main(int argc, char *argv[]) {
    // Baslatilir.
    MPI_Init(&argc, &argv);

    int npes, myRank;
    // su anki calisan program
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    // suan calisan toplam program.
    MPI_Comm_size(MPI_COMM_WORLD, &npes);

    char message[SHM_SIZE]; // gonderilen mesaj. 
    char received_message[SHM_SIZE]; // alinan mesaj.
      
    
    if (myRank % 2 == 0){
   	// mesaj yazilir. snprintf fonksiyonuna boyutu ile birlikte mesaj gonderilir.
        snprintf(message, sizeof(message), "Bu mesaj %d. prosese... (Bu mesaj %d. prosesten gelmistir.)", myRank, myRank + 1);
        send_message(message, myRank + 1); // MPI fonksiyonu bir araci fonksiyon ile cagrilir. Mesaj gonderme.
        printf("%d. Proses'ten mesaj: %s\n", myRank + 1, message); // Gonderilen mesaj.
        receive_message(received_message, myRank + 1); // MPI fonksiyonu ile gelen mesaj alinir. Mesaj alma.
        printf("%d. Proses'ten alinan mesaj: %s\n", myRank + 1, received_message); // Gelen
    } 
    else{
    	//yukaridaki mantik uygulanir.
        snprintf(message, sizeof(message), "Bu mesaj %d. prosese... (Bu mesaj %d. prosesten gelmistir.)", myRank, myRank - 1);
        send_message(message, myRank - 1);
        printf("%d. Proses'ten mesaj: %s\n", myRank - 1, message);
        receive_message(received_message, myRank - 1);
        printf("%d. Proses'ten alinan mesaj: %s\n", myRank - 1, received_message);
    }
	// mpi sonlandir.
    MPI_Finalize();
    return 0;
}
