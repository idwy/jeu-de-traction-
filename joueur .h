

#ifndef DEF_JOUEUR
#define DEF_JOUEUR

    typedef struct _joueur
    {
        char pseudo[50];
        char mdp[25];
        int level;
        int score[LEVELS];
        int X,Y;
    }joueur;

    joueur *creerJoueur (char *pseudo, char *mdp);      //Permet d'initialiser un joueur
    int creer (joueur *user);                         //Permet de creer un nouveau joueur et de l'enregistrer dans le fichier
    int charger(joueur *user);                        //Permet de charger la partie avec la derniere position du joueur
    void sauvegarder(joueur *user);                  //Permet de sauvegarder la derniere position lorsque le joueur quitte le jeu sans arriver au bloc rose
    void meilleurs (int niveau);                     // Permet de stocker les 10 premiers scores dans un fichier

#endif
