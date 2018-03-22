#include <stdio.h>
#include <stdlib.h>
#include "../hd/stegano.h"
#include "../hd/decode.h"

int main(int argc, char *argv[])
{

/* Verification des arguments */
    if(argc < 3){
        printf("[ERR] Nombre d'arguments invalide\n");
        return 10;
    }

    char action = argv[1][0];

    if( action == 'h' ){
    /* Lancement de l'ecriture du message */

        return main_hiding(argc, argv);

    }
    else if( action == 'f' ){
    /* Lancement du dechiffrement */

        return main_finding(argv);

    }else{
        printf("[ERR] Action inconnue\n");
        return 12;
    }
}
