

#ifndef DEF_MENU
#define DEF_MENU

    void auth (SDL_Surface *ecran);                                                                         // Fonction principale
    void auth_creer (SDL_Surface *ecran);                                                                 // Afficher le formulaire d'authentification ou d'inscription
    int choix (SDL_Surface *ecran);                                                                        // Donne le choix à l'utilisateur de choisir Authentification/Inscription/10 premiers scores
    SDL_Surface *construire_trait (SDL_Surface *ecran, int X, int Y, int W, int H);
    void detruire_trait (SDL_Surface *ecran, SDL_Surface *trait, int X, int Y);
    void fail_msg (SDL_Surface *ecran, char *msg);
    int premiersScores (SDL_Surface *ecran);

#endif
