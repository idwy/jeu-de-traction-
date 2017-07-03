#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string.h>

#include "constantes.h"

#include "joueur.c"
#include "jeu.c"
#include "menu.c"

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *menu = NULL;

    SDL_Init(SDL_INIT_VIDEO);

    if (TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetIcon(SDL_LoadBMP("images/mauve3.bmp"), NULL); // L'icône doit être chargée avant SDL_SetVideoMode
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Jeu de Traction", NULL);

    auth(ecran);

    SDL_FreeSurface(menu);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
