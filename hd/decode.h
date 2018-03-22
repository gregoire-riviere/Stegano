#ifndef DECODE_GUARD
#define DECODE_GUARD

#define TAILLE_ENTETE   54

    /* fonction principale de dechiffrement */
    int main_finding(char *argv[]);
    /* lecture de la taille du message */
    int get_taille_message(FILE* IMG);
    /* fonction tres utile : lecture d'un octet de message en lisant 8 octets d'image */
    char lecture_1_octet(FILE *IMG);
    /* lecture du corps du message */
    char* get_message(FILE* IMG, int taille);

#endif
