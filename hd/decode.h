#ifndef DECODE_GUARD
#define DECODE_GUARD

#define TAILLE_ENTETE   54

    int main_finding(char *argv[]);
    int get_taille_message(FILE* IMG);
    char lecture_1_octet(FILE *IMG);

#endif