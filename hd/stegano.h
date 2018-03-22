#ifndef STENO_GUARD
#define STENO_GUARD

#define TAILLE_ENTETE   54

    /* Fonction principale */
    int main_hiding(int argc, char *argv[]);
    /* Fonction d'ecriture de message */
    void run_hide_mess(char* message, FILE* IMG_SRC, FILE* IMG_DEST);
    /* Fonction d'ecriture pour un bit du message */
    void hiding(unsigned char byte_message, int byte_number, unsigned char byte_img, unsigned char* byte_dest);
    /* Ecriture des entetes */
    void ecriture_header(FILE* IMG_SRC, FILE* IMG_DEST);
    /* Ecriture de la fin de l'image source */
    void ecrire_reste(FILE* IMG_SRC, FILE* IMG_DEST);
    /* Verification de la taille du message */
    int verification_taille(char* message, FILE* IMG_SRC);
    /* Enrichissement du message avec la taile */
    char* enrichir_taille(char* message_user);
    
#endif
