#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../hd/decode.h"

int main_finding(char *argv[]){

    char* img = argv[2];

    /* Ouverture de l'image */

    FILE* IMG = fopen(img, "rb");

    if(IMG == NULL){
        printf("[ERR] Image source introuvable, probleme d'ouverture\n");
        return 11;
    }

    int taille_message = get_taille_message(IMG);

    printf("[DEBUG - TEMPO] taille du message : %d\n", taille_message);

    return 0;
}

int get_taille_message(FILE* IMG){

    /* Positionnement du curseur */
    fseek(IMG, TAILLE_ENTETE, SEEK_SET);
    char chiffre_lu[2];
    chiffre_lu[1] = '\0';
    int nombre = 0; /* TODO: Penser a securiser ce buffer */

    /* Lecture chiffre par chiffre */
    chiffre_lu[0] = lecture_1_octet(IMG);
    while( chiffre_lu[0] != ';')
    {

        nombre = nombre * 10 + atoi(chiffre_lu);
        chiffre_lu[0] = lecture_1_octet(IMG);
    }
    return nombre;
}

char lecture_1_octet(FILE *IMG){

    unsigned char byte_read = 0;
    char total = 0;
    int i;

    /* Lecture des 8 octets d'image et recuperation du dernier bit */
    for (i = 0; i<8; i++){
        total *=2;
        fread(&byte_read, 1, 1, IMG);
        if(byte_read % 2 == 1)
        {
            total +=1;
        }
    }
    return total;

}
