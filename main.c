#include <stdio.h>
#include <stdlib.h>
#include "stegano.h"

int main(int argc, char *argv[])
{

/* Verification des arguments */
    if(argc < 4){
        printf("[ERR] Nombre d'arguments invalide");
        return 10;
    }

    char* message = argv[1];
    char* img_src = argv[2];
    char* img_dest = argv[3];

/* Ouverture de l'image source */
    FILE* IMG_SRC = fopen(img_src, "rb");

    if(IMG_SRC == NULL){
        printf("[ERR] Image source introuvable, probleme d'ouverture");
        return 11;
    }

/* Ouverture de l'image de destination */
    FILE* IMG_DEST = fopen(img_dest, "wb+");

/* Lancement */
    run_hide_mess(message, IMG_SRC, IMG_DEST);

/* Fermeture de l'image */

    fclose(IMG_SRC);
    fclose(IMG_DEST);
    return 0;
}
