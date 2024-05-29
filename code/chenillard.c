#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdint.h> //include pour uint32
#include <sys/mman.h> //include pour mmap

#define LED_PATH "/sys/class/leds/"

// Définir le nombre de LEDs à utiliser
#define NUM_LEDS 10

int main() {
    FILE *leds[NUM_LEDS];
    char led_file[NUM_LEDS][50];

    // Créer le chemin d'accès pour chaque LED
    for (int i = 1; i < NUM_LEDS; i++) {
        sprintf(led_file[i], "%s%s%d/brightness", LED_PATH, "fpga_led", i);
        // Ouvrir le fichier pour écriture
        leds[i] = fopen(led_file[i], "w");
		printf(led_file[i]);
		printf("/n");
        if (leds[i] == NULL) {
            perror("Erreur lors de l'ouverture du fichier de la LED");
            exit(EXIT_FAILURE);
        }
    }

    // Faire clignoter les LEDs en boucle
    while (1) {
        // Allumer toutes les LEDs
        for (int i = 1; i < NUM_LEDS; i++) {
            fprintf(leds[i], "1");
            fflush(leds[i]);
            usleep(5000); // Attendre 0.5 seconde
        }

        // Éteindre toutes les LEDs
        for (int i = 1; i < NUM_LEDS; i++) {
            fprintf(leds[i], "0");
            fflush(leds[i]);
            usleep(5000); // Attendre 0.5 seconde
        }
    }

    // Fermer les fichiers LED
    for (int i = 1; i < NUM_LEDS; i++) {
        fclose(leds[i]);
    }

    return 0;
}