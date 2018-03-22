#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../hd/stegano.h"

int main_hiding(int argc, char *argv[]){

    if(argc < 5){
        printf("[ERR] Nombre d'arguments invalide\n");
        return 10;
    }

    char* message = argv[2];
    char* img_src = argv[3];
    char* img_dest = argv[4];

    FILE* IMG_SRC = fopen(img_src, "rb");

    if(IMG_SRC == NULL){
        printf("[ERR] Image source introuvable, probleme d'ouverture\n");
        return 11;
    }

    /* Ouverture de l'image de destination */
    FILE* IMG_DEST = fopen(img_dest, "wb+");

    if(IMG_DEST == NULL){
        printf("[ERR] Impossible de creer l'image de destination. Verifiez que vous disposez des droits.\n");
        return 11;
    }

    /* Lancement */
    run_hide_mess(message, IMG_SRC, IMG_DEST);

    /* Fermeture de l'image */

    fclose(IMG_SRC);
    fclose(IMG_DEST);

    return 0;

}

void run_hide_mess(char* message_user, FILE* IMG_SRC, FILE* IMG_DEST){

/*  Octets de lecture
    byte_img : octet lu dans l'image source
    byte_mess : octet a ecrire du message
    byte_dest : resultat à ecrire dans l'image de destination */

    unsigned char byte_img = 0;
    unsigned char byte_dest = 0;

/* Indices de deplacement */

    int indice_octet = 0;
    int indice_bit=0;

/* Ajout de la taille du message */
    char* message = NULL;
    message = enrichir_taille(message_user);

    if(message == NULL){
        printf("[ERR] Erreur d'enrichissement avec la taille\n");
    }

/* Verification de la longueur du message */

    if(verification_taille(message, IMG_SRC) == 0){
        printf("[ERR] Le message est trop long ou l'image trop petite\n");
        return;
    }

/* Skip des headers */

    ecriture_header(IMG_SRC, IMG_DEST);

/*///////////////////
* Boucle principale /
///////////////////*/

    while(fread( &byte_img, 1, 1, IMG_SRC) != 0 && indice_octet < strlen(message))
    {

/* Ecriture du message */

        hiding(message[indice_octet], indice_bit, byte_img, &byte_dest);
        fwrite(&byte_dest, 1, 1, IMG_DEST);
        byte_dest = 0;

/* On se deplace dans le message (bit a bit) */

        indice_bit ++;
        if(indice_bit == 8){
            indice_bit = 0;
            indice_octet ++;
        }

    }

    if(indice_octet >= strlen(message)){
        fwrite(&byte_dest, 1, 1, IMG_DEST);
        ecrire_reste(IMG_SRC, IMG_DEST);
    }

    free(message);
    printf("Message ecrit avec succes!\n\n");
}

/* Fonction d'ecriture */

void hiding(unsigned char byte_message, int byte_number, unsigned char byte_img, unsigned char* byte_dest){

/* Selection du bit */
    int bit_to_write = ((byte_message >> (7-byte_number)) & 0x01);
    int last_bit_img = 0;

/* Ecriture du bit */
    if(bit_to_write == 1){ /* cas du bit a 1 */
        *byte_dest = byte_img | bit_to_write;
    }
    else{ /* cas du bit a 0 */
        last_bit_img = byte_img  & 0x01;
        if(last_bit_img == 1){
            *byte_dest = byte_img - 1;
        }
        else{/* Sinon : le bit est deja a zero */
            *byte_dest = byte_img;
        }

    }
}

/* Ecriture des entetes */

void ecriture_header(FILE* IMG_SRC, FILE* IMG_DEST){

    unsigned char entete[TAILLE_ENTETE];

    fread(entete, 1, TAILLE_ENTETE, IMG_SRC);
    fwrite(entete, 1, TAILLE_ENTETE, IMG_DEST);

}

/* Ecritures des parties unused de l'image */

void ecrire_reste(FILE* IMG_SRC, FILE* IMG_DEST){

    unsigned char byte = 0;
    while(fread(&byte, 1, 1, IMG_SRC) != 0){
        fwrite(&byte, 1, 1, IMG_DEST);
    }

}

int verification_taille(char* message, FILE* IMG_SRC){

    int taille_reelle;

    fseek(IMG_SRC, 0L, SEEK_END);
    taille_reelle = ftell(IMG_SRC) - TAILLE_ENTETE;
    rewind(IMG_SRC);

    if(strlen(message)*8 > taille_reelle){
        return 0;
    }else{
        return 1;
    }

}

char* enrichir_taille(char* message_user){

    /* Ecriture de la taille */
    char taille_mess_txt[50];
    sprintf(taille_mess_txt, "%d", strlen(message_user));

    /* Taille du message = taille message user + nombre de chiffres de sa taille + 1 pour le separateur + 1 pour le \0 */
    char* message = NULL;
    message = malloc(sizeof(char) * (strlen(message_user) + strlen(taille_mess_txt) + 2));

    if(message == NULL){
        return NULL;
    }

    /* Assemblage du message */
    strcpy(message, taille_mess_txt);
    strcat(message, ";");
    strcat(message, message_user);

    return message;

}
