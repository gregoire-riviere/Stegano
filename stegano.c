#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "steno.h"

void run_hide_mess(char* message, FILE* IMG_SRC, FILE* IMG_DEST){

/*  Octets de lecture
    byte_img : octet lu dans l'image source
    byte_mess : octet a ecrire du message
    byte_dest : resultat à ecrire dans l'image de destination */

    unsigned char byte_img = 0;
    unsigned char byte_dest = 0;

/* Indices de deplacement */

    int indice_octet = 0;
    int indice_bit=0;

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

}

void hiding(unsigned char byte_message, int byte_number, unsigned char byte_img, unsigned char* byte_dest){

/* Selection du bit */
    int bit_to_write = ((byte_message >> byte_number) & 0x01);
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

void ecriture_header(FILE* IMG_SRC, FILE* IMG_DEST){

    unsigned char entete[TAILLE_ENTETE];
    
    fread(entete, 1, TAILLE_ENTETE, IMG_SRC);
    fwrite(entete, 1, TAILLE_ENTETE, IMG_DEST);

}

void ecrire_reste(FILE* IMG_SRC, FILE* IMG_DEST){

    unsigned char byte = 0;
    while(fread(&byte, 1, 1, IMG_SRC) != 0){
        fwrite(&byte, 1, 1, IMG_DEST);
    }

}
