#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork basarisiz");
        return 1;
    }

    if (pid == 0) {
        // Child process
        FILE *file = fopen("deneme.txt", "r"); // deneme.txt dosyasinin var olup olmadigi kontrol ediliyor

        if (file == NULL) {
            // Dosya bulunamazsa, abort() ile çikis yapilacak
            perror("File bulunamadi");
            abort();
        } else {
            // Dosya basariyla açilirsa, düzgün bir sekilde çikis yapilacak
            printf("File basariyla acildi!\n");
            fclose(file);
            exit(0);
        }
    } else {
        // Parent process
        int status;
        wait(&status); // Child process'in bitmesi bekleniyor

        if (WIFSIGNALED(status)) {
            // Child bir sinyal ile sonlandi
            printf("Child sinyal ile sonlandi %d\n", WTERMSIG(status));
        } else if (WIFEXITED(status)) {
            // Child normal bir sekilde sonlandi
            printf("Child normal sonlandi %d\n", WEXITSTATUS(status));
        } else {
            printf("Child normal sonlanamadi\n");
        }
    }

    return 0;
}
