#include <stdio.h>
#include <stdlib.h>
#include "jeu.h"
#include <SDL/SDL.h>
#include "constantes.h"
#include <time.h>
#include <string.h>


void jouer(SDL_Surface* ecran, joueur *user)
{
    int done = 1;
    int continuer = 1;
    int carte[10][10] = {0};
    int a, b ;
    int xD[LEVELS] = {7 , 5 , 8}, yD[LEVELS] = {2 , 3 , 8};
    SDL_Event event;
    /*int tempsActuel = 0;
    SDL_Surface *temps = NULL;
    char *TMPS[20];*/

    while (done)
    {
        continuer = 1;

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));// Effacement de l'écran
        a = user->X;
        b = user->Y;
        mapp(carte, a, b, ecran, user->level, 1); //Afficher la map avec la derniere position du joueur
        info(ecran, user);
        /*tempsActuel = SDL_GetTicks();
        sprintf(TMPS, "Temps : %d", compteur);
        TTF_Font *police = NULL;
        police = TTF_OpenFont("uni.ttf",15);
        SDL_Color couleurBlanche = {255,255,255};
        SDL_Rect position;
        position.x =
        temps = TTF_RenderText_Blended(police, TMPS, couleurBlanche);*/
        SDL_Flip(ecran);

        while (continuer)
        {
            SDL_WaitEvent(&event);
            switch(event.type)
            {
                case SDL_QUIT:
                    sauvegarder(user);
                    continuer = 0;
                    done = 0;
                    break;

                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            sauvegarder(user);
                            continuer = 0;
                            done = 0;
                            break;

                        case SDLK_r: //For RESET
                            user->X = xD[user->level - 1];
                            user->Y = yD[user->level - 1];
                            jouer(ecran, user);
                            continuer = 0;
                            break;

                        case SDLK_h: //For HELP
                            user->score[user->level - 1] += 10;
                            help(ecran, user);
                            break;

                        case SDLK_UP: //MOVE UP

                            if ( carte[a][b-1] != NOIR )
                                user->score[user->level - 1] += 5;
                            while (carte[a][b-1] != NOIR  && carte[a][b-1] != ROSE)
                            {
                                mapp(carte, a , b-1 , ecran, user->level, 1);
                                info(ecran, user);
                                b--;
                                SDL_Flip(ecran);
                                SDL_Delay(30);
                            }
                            if (user->Y != b)
                                user->Y = b;
                            if (carte[a][b-1] == ROSE) //Le cas de succes
                            {
                                succes(carte, a, b-1, ecran, user->level);
                                SDL_Flip(ecran);
                                continuer = 0;
                                SDL_Delay(500);

                                user->Y = yD[user->level];
                                user->X = xD[user->level];
                                user->level++;
                                sauvegarder(user);
                            }
                            break;

                        case SDLK_DOWN:

                            if ( carte[a][b+1] != NOIR )
                                user->score[user->level - 1] += 5;
                            while (carte[a][b+1] != NOIR  && carte[a][b+1] != ROSE)
                            {
                                mapp(carte, a , b+1 , ecran, user->level, 1);
                                info(ecran, user);
                                b++;
                                SDL_Flip(ecran);
                                SDL_Delay(30);
                            }
                            if (user->Y != b)
                                user->Y = b;
                            if (carte[a][b+1] == ROSE)
                            {
                                succes(carte, a, b+1, ecran, user->level);
                                SDL_Flip(ecran);
                                continuer = 0;
                                SDL_Delay(500);

                                user->Y = yD[user->level];
                                user->X = xD[user->level];
                                user->level++;
                                sauvegarder(user);
                            }
                            break;

                        case SDLK_RIGHT:

                            if ( carte[a+1][b] != NOIR )
                                user->score[user->level - 1] += 5;
                            while (carte[a+1][b] != NOIR  && carte[a+1][b] != ROSE)
                            {
                                mapp(carte, a+1 , b , ecran, user->level, 1);
                                info(ecran, user);
                                a++;
                                SDL_Flip(ecran);
                                SDL_Delay(30);
                            }
                            if (user->X != a)
                                user->X = a;
                            if (carte[a+1][b] == ROSE)
                            {
                                succes(carte, a+1, b, ecran, user->level);
                                SDL_Flip(ecran);
                                continuer = 0;
                                SDL_Delay(500);

                                user->Y = yD[user->level];
                                user->X = xD[user->level];
                                user->level++;
                                sauvegarder(user);
                            }
                            break;

                        case SDLK_LEFT:

                            if ( carte[a-1][b] != NOIR )
                                user->score[user->level - 1] += 5;
                            while (carte[a-1][b] != NOIR  && carte[a-1][b] != ROSE)
                            {
                                mapp(carte, a-1 , b , ecran, user->level, 1);
                                info(ecran, user);
                                a--;
                                SDL_Flip(ecran);
                                SDL_Delay(30);
                            }
                            if (user->X != a)
                                user->X = a;
                            if (carte[a-1][b] == ROSE)
                            {
                                succes(carte, a-1, b, ecran, user->level);
                                SDL_Flip(ecran);
                                continuer = 0;
                                SDL_Delay(500);

                                user->Y = yD[user->level];
                                user->X = xD[user->level];
                                user->level++;
                                sauvegarder(user);
                            }
                            break;

                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
            SDL_Flip(ecran);
        }

        if (user->level > LEVELS)
        {
            strcpy(user->mdp,"***");
            sauvegarder(user);
            done = 0;
            gameover(ecran);
        }
    }

}

void mapp(int carte[][NB_BLOCS_HAUTEUR],int a ,int b , SDL_Surface* ecran, int niveau, int B )
{
    SDL_Surface *bleu = NULL, *noir = NULL, *rose = NULL, *blanc = NULL, *wallpaper = NULL;
    int i,j;
    SDL_Rect position;
    FILE *fichier = NULL;

    position.x = 0;
    position.y = 0;
    wallpaper = SDL_LoadBMP("images/wallpaper.bmp");
    SDL_BlitSurface(wallpaper,NULL,ecran,&position);

    if (B == 1)
        bleu = SDL_LoadBMP("images/bleu3.bmp");
    if (B == 0)
        bleu = SDL_LoadBMP("images/Sbleu.bmp");

    noir = SDL_LoadBMP("images/noir4.bmp");
    blanc = SDL_LoadBMP("images/blanc1.bmp");
    rose = SDL_LoadBMP("images/rose1.bmp");
    if (niveau == 1)
        fichier = fopen("map1.txt","r");
    if (niveau == 2)
        fichier = fopen("map2.txt","r");
    if (niveau == 3)
        fichier = fopen("map3.txt","r");

        /*for (i = 0 ; i < 10 ; i++)
        {
            for (j = 0 ; j < 10 ; j++)
            {

                if (i == 0 || i == 9 || j == 0 || j == 9)     //NOIR
                    carte[i][j] = NOIR;

                else
                {
                    if ( (i == 1 && j == 3) || (i == 1 && j == 4) || (i == 1 && j == 7)
                      || (i == 3 && j == 1) || (i == 3 && j == 7)
                      || (i == 4 && j == 2)
                      || (i == 5 && j == 5) || (i == 5 && j == 7)
                      || (i == 6 && j == 2) || (i == 6 && j == 6)
                      || (i == 7 && j == 7)
                      || (i == 8 && j == 1) || (i == 8 && j == 5) )  //NOIR
                        carte[i][j] = NOIR;

                    else
                    {   if (i == a && j == b) //BLEU
                            carte[i][j] = BLEU;
                        else
                        {
                            if (i == 5 && j == 3)  //ROSE
                                carte[i][j] = ROSE;

                            else  //BLANC
                                carte[i][j] = BLANC;
                        }
                    }
                }
            }
        }*/
    for (i=0 ; i<10 ; i++)
    {
        for(j=0 ; j < 10 ; j++)
        {
            fscanf(fichier, "%d,", &carte[j][i]);
        }
    }
    carte[a][b] = BLEU;

    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            position.x = i * TAILLE_BLOC;
            position.y = j * TAILLE_BLOC;

            switch(carte[i][j])
            {
                case NOIR:
                    SDL_BlitSurface(noir, NULL, ecran, &position);
                    break;
                case BLANC:
                    SDL_BlitSurface(blanc, NULL, ecran, &position);
                    break;
                case ROSE:
                    SDL_BlitSurface(rose, NULL, ecran, &position);
                    break;
                case BLEU:
                    SDL_BlitSurface(bleu, NULL, ecran, &position);
                    break;
                default:
                    break;
            }
        }
    }
}

void succes (int carte[][NB_BLOCS_HAUTEUR],int a ,int b , SDL_Surface* ecran, int niveau)
{
    int i = 0, j = 0;
    SDL_Rect position;
    SDL_Surface *mauve = NULL, *noir = NULL, *blanc = NULL;
    FILE *fichier = NULL;

    noir = SDL_LoadBMP("images/noir4.bmp");
    blanc = SDL_LoadBMP("images/blanc1.bmp");
    mauve = SDL_LoadBMP("images/mauve3.bmp");

    /*if (niveau == 1)
    {
        for (i = 0 ; i < 10 ; i++)
        {
            for (j = 0 ; j < 10 ; j++)
            {
                if (i == 0 || i == 9 || j == 0 || j == 9)   //NOIR
                    carte[i][j] = NOIR;

                else
                {
                    if ( (i == 1 && j == 3) || (i == 1 && j == 4) || (i == 1 && j == 7)
                      || (i == 3 && j == 1) || (i == 3 && j == 7)
                      || (i == 4 && j == 2)
                      || (i == 5 && j == 5) || (i == 5 && j == 7)
                      || (i == 6 && j == 2) || (i == 6 && j == 6)
                      || (i == 7 && j == 7)
                      || (i == 8 && j == 1) || (i == 8 && j == 5) )    //NOIR
                        carte[i][j] = NOIR;

                    else
                    {
                        if (i == 5 && j == 3)    //MAUVE
                            carte[i][j] = MAUVE;

                        else    //BLANC
                            carte[i][j] = BLANC;
                    }
                }
            }
        }
    }
    if (niveau == 2)
    {
        for (i = 0 ; i < 10 ; i++)
        {
            for (j = 0 ; j < 10 ; j++)
            {

                if (i == 0 || i == 9 || j == 0 || j == 9)     //NOIR
                    carte[i][j] = NOIR;

                else
                {
                    if ( (i == 2 && j == 3)
                      || (i == 3 && j == 5) || (i == 3 && j == 7)
                      || (i == 4 && j == 8)
                      || (i == 6 && j == 3) || (i == 6 && j == 8)
                      || (i == 7 && j == 4)
                      || (i == 8 && j == 2) || (i == 8 && j == 6) )  //NOIR
                        carte[i][j] = NOIR;

                    else
                    {
                        if (i == 7 && j == 2)  //MAUVE
                            carte[i][j] = MAUVE;

                        else  //BLANC
                            carte[i][j] = BLANC;
                    }
                }
            }
        }
    }*/
    if (niveau == 1)
        fichier = fopen("map1.txt","r");
    if (niveau == 2)
        fichier = fopen("map2.txt","r");
    if (niveau == 3)
        fichier = fopen("map3.txt","r");

    for (i=0 ; i<10 ; i++)
    {
        for(j=0 ; j < 10 ; j++)
        {
            fscanf(fichier, "%d,", &carte[j][i]);
        }
    }

    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            position.x = i * TAILLE_BLOC;
            position.y = j * TAILLE_BLOC;

            switch(carte[i][j])
            {
                case NOIR:
                    SDL_BlitSurface(noir, NULL, ecran, &position);
                    break;
                case BLANC:
                    SDL_BlitSurface(blanc, NULL, ecran, &position);
                    break;
                case ROSE:
                    SDL_BlitSurface(mauve, NULL, ecran, &position);
                    break;
                default:
                    break;
            }
        }
    }
}

void footer(SDL_Surface *ecran, unsigned int r, unsigned int g, unsigned int b)
{
    SDL_Surface *title = NULL;
    SDL_Rect position;
    position.x = 7;
    position.y = 360;
    TTF_Font *policeF = NULL;
    policeF = TTF_OpenFont("urban.otf", 45);
    SDL_Color couleur = {r , g , b};
    title = TTF_RenderText_Blended(policeF, "Jeu  de  Traction", couleur);
    SDL_BlitSurface(title, NULL, ecran, &position);
    SDL_Flip(ecran);
    TTF_CloseFont(policeF);
    SDL_FreeSurface(title);
}

void gameover (SDL_Surface *ecran)
{
    SDL_Surface *wallpaper = NULL;
    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    wallpaper = SDL_LoadBMP("images/gameover.bmp");
    SDL_BlitSurface(wallpaper, NULL, ecran, &position);
    footer(ecran, 120, 120, 120);
    SDL_Delay(3000);
    SDL_FreeSurface(wallpaper);
}

void info(SDL_Surface *ecran, joueur *user)
{
    SDL_Surface *pseudo = NULL, *score = NULL, *level = NULL, *touches = NULL, *help = NULL;
    SDL_Rect position;
    char PSD[60], SCR[50], LVL[10];
    char scoreActuel[10], levelActuel[5];
    int x = user->level;
    PSD[0] = '\0';
    SCR[0] = '\0';
    LVL[0] = '\0';

    sprintf(scoreActuel, "%d", user->score[x-1]); //pour convertir un int en string
    sprintf(levelActuel, "%d", user->level);

    strcat(PSD, "Pseudo : ");
    strcat(PSD, user->pseudo);
    strcat(SCR, "Score : ");
    strcat(SCR, scoreActuel);
    strcat(LVL, "Level ");
    strcat(LVL, levelActuel);

    //Footer
    footer(ecran, 150, 150, 150);

    //pseudo
    position.x = 7;
    position.y = 400;
    TTF_Font *policeP = NULL;
    policeP = TTF_OpenFont("CL.ttf", 16);
    TTF_SetFontStyle(policeP, TTF_STYLE_BOLD);
    SDL_Color couleur = {0 , 0 , 0};
    pseudo = TTF_RenderText_Blended(policeP, PSD, couleur);
    SDL_BlitSurface(pseudo, NULL, ecran, &position);

    //score
    position.x = 7;
    position.y = 420;
    TTF_Font *policeS = NULL;
    policeS = TTF_OpenFont("CL.ttf", 14);
    score = TTF_RenderText_Blended(policeS, SCR, couleur);
    SDL_BlitSurface(score, NULL, ecran, &position);

    //touches
    position.x = 200;
    position.y = 435;
    TTF_Font *policeT = NULL;
    policeT = TTF_OpenFont("Timeless.ttf", 13);
    touches = TTF_RenderText_Blended(policeT, "Esc : [EXIT] , R : [RESET]", couleur);
    SDL_BlitSurface(touches, NULL, ecran, &position);

    //level
    position.x = 250;
    position.y = 400;
    TTF_Font *policeL = NULL;
    policeL = TTF_OpenFont("CL.ttf", 30);
    couleur = {0 , 0 , 255};
    level = TTF_RenderText_Blended(policeL, LVL, couleur);
    SDL_BlitSurface(level, NULL, ecran, &position);

    //Help
    position.x = 7;
    position.y = 435;
    couleur = {100 , 50 , 255};
    help = TTF_RenderText_Blended(policeS, "H : [ HELP ] ", couleur);
    SDL_BlitSurface(help, NULL, ecran, &position);

    SDL_Flip(ecran);

    TTF_CloseFont(policeL);
    TTF_CloseFont(policeT);
    TTF_CloseFont(policeS);
    TTF_CloseFont(policeP);

    SDL_FreeSurface(help);
    SDL_FreeSurface(score);
    SDL_FreeSurface(level);
    SDL_FreeSurface(touches);
    SDL_FreeSurface(pseudo);
}

void help (SDL_Surface *ecran, joueur *user)
{
    int carte[10][10];
    int x, y, i = 0, j = 0;
    int *a, *b;
    int ta, tb;

    if (user->level == 1)
    {
        ta = 8;
        tb = 7;
        a = (int*) malloc(ta * sizeof(int));
        b = (int*) malloc(tb * sizeof(int));
        a[0]=7 ; a[1]=8 ; a[2]=2 ; a[3]=1 ; a[4]=3 ; a[5]=1 ; a[6]=4 ; a[7]=5;
        b[0]=2 ; b[1]=4 ; b[2]=1 ; b[3]=2 ; b[4]=6 ; b[5]=5 ; b[6]=3 ;
    }
    if (user->level == 2)
    {
        ta = 7;
        tb = 7;
        a = (int*) malloc(ta * sizeof(int));
        b = (int*) malloc(tb * sizeof(int));
        a[0]=5 ; a[1]=3 ; a[2]=6 ; a[3]=8 ; a[4]=7 ; a[5]=8 ; a[6]=7 ;
        b[0]=3 ; b[1]=4 ; b[2]=7 ; b[3]=8 ; b[4]=5 ; b[5]=3 ; b[6]=2 ;
    }
    if (user->level == 3)
    {
        ta = 6;
        tb = 5;
        a = (int*) malloc(ta * sizeof(int));
        b = (int*) malloc(tb * sizeof(int));
        a[0]=8 ; a[1]=1 ; a[2]=6 ; a[3]=5 ; a[4]=1 ; a[5]=4 ;
        b[0]=8 ; b[1]=7 ; b[2]=2 ; b[3]=5 ; b[4]=3 ;
    }

    x = a[i];
    y = b[j];

    mapp(carte, a[i] , b[j] , ecran, user->level, 0);
    info(ecran, user);
    SDL_Flip(ecran);
    SDL_Delay(200);

    while (j < tb-1)
    {
        x = a[i];
        i++;
        if(x < a[i])
        {
            for( ; x<a[i] ; x++)
            {
                mapp(carte, x , y , ecran, user->level, 0);
                info(ecran, user);
                SDL_Flip(ecran);
                SDL_Delay(200);
            }
        }
        else
        {
            for( ; x>a[i] ; x--)
            {
                mapp(carte, x , y , ecran, user->level, 0);
                info(ecran, user);
                SDL_Flip(ecran);
                SDL_Delay(200);
            }
        }
        y = b[j];
        j++;
        if(y < b[i])
        {
            for( ; y<b[i] ; y++)
            {
                mapp(carte, x , y , ecran, user->level, 0);
                info(ecran, user);
                SDL_Flip(ecran);
                SDL_Delay(200);
            }
        }
        else
        {
            for( ; y>b[i] ; y--)
            {
                mapp(carte, x , y , ecran, user->level, 0);
                info(ecran, user);
                SDL_Flip(ecran);
                SDL_Delay(200);
            }
        }
    }
    if (i < ta-1)
    {
        x = a[i];
        i++;
        for( ; x<a[i] ; x++)
        {
            mapp(carte, x , y , ecran, user->level, 0);
            info(ecran, user);
            SDL_Flip(ecran);
            SDL_Delay(200);
        }
    }
    mapp (carte, user->X, user->Y, ecran, user->level, 1);
    info(ecran, user);
}

