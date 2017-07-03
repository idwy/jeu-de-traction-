

#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

    #define TAILLE_BLOC         35 // Taille d'un bloc (carré) en pixels
    #define NB_BLOCS_LARGEUR    10
    #define NB_BLOCS_HAUTEUR    10
    #define TAILLE_OPTIONS      100
    #define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
    #define HAUTEUR_FENETRE     (TAILLE_BLOC * NB_BLOCS_HAUTEUR) + TAILLE_OPTIONS
    #define LEVELS              3

    enum {BLANC, NOIR, ROSE, BLEU, MAUVE};
    enum {HAUT, BAS, GAUCHE, DROITE};

#endif
