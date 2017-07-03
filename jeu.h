

#ifndef DEF_JEU
#define DEF_JEU

    void jouer(SDL_Surface* ecran, joueur *user); //Pour jouer :P
    void mapp(int carte[][NB_BLOCS_HAUTEUR], int a ,int b, SDL_Surface* ecran, int niveau, int B );          //Modifier la carte apres un deplacement
    void succes (int carte[][NB_BLOCS_HAUTEUR],int a ,int b , SDL_Surface* ecran, int niveau);               //Modifier la carte en cas de succes
    void footer (SDL_Surface *ecran, unsigned int r, unsigned int g, unsigned int b);
    void gameover (SDL_Surface *ecran);
    void info(SDL_Surface *ecran, joueur *user);                                                            //Afficher les infos du joueur
    void help (SDL_Surface *ecran, joueur *user);                                                            //Propose une solution pour le joueur

#endif
