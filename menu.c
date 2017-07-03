#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <string.h>
#include <SDL/SDL_ttf.h>
#include <ctype.h>

#include "menu.h"


void auth(SDL_Surface *ecran)
{
    joueur *user = NULL;
    SDL_Surface *trait = NULL, *texte_psd = NULL, *texte_mdp = NULL;
    SDL_Rect positionP, positionM;
    SDL_Event event;
    int choice, ecrire = 1, test;
    int continuer = 1;
    char *tmp;
    char pseudo[50] = "", mdp[25] = "", __mdp[25] = "";
    int length_psd = 0, length_mdp = 0;

    choice = choix (ecran);
    __mdp[0] = '\0';
    if (choice != -1)
    {
        auth_creer (ecran);
        trait = construire_trait(ecran, 60, 128, 1, 22);
    }
    if (choice == -1) continuer = 0;
    SDL_Flip(ecran);

    TTF_Font *police = NULL;
    police = TTF_OpenFont("CL.ttf", 25);
    SDL_Color blanche = {0 , 0 , 0};

    positionP.x = 60;
    positionP.y = 125;
    positionM.x = 60;
    positionM.y = 200;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        //intialiser tout
                        pseudo[0] = '\0';
                        mdp[0] = '\0';
                        __mdp[0] = '\0';
                        length_psd = 0;
                        length_mdp = 0;
                        texte_psd = NULL;
                        texte_mdp = NULL;
                        ecrire = 1;
                        //Retour à la 1ere page
                        choice = choix (ecran);
                        if (choice == -1)   continuer = 0;
                        else                auth_creer (ecran);
                        SDL_Flip(ecran);
                        break;

                    case SDLK_RETURN: // Demande à jouer

                        if (choice == 1)
                        {
                            user = creerJoueur(pseudo, mdp);
                            test = charger(user);
                            if (test == -1)
                                fail_msg (ecran, "Pseudo ou Mot de passe vide !");
                            else
                            {
                                if (test == 0)
                                    fail_msg (ecran, "Pseudo ou Mot de passe incorrect !");
                                else
                                {
                                    if (test == 1)
                                        {jouer(ecran, user);}
                                }
                            }
                        }
                        if (choice == 0)
                        {
                            user = creerJoueur(pseudo, mdp);
                            test = creer(user);
                            if (test == -1)
                                fail_msg (ecran, "Pseudo ou Mot de passe vide !");
                            else
                            {
                                if (test == 0)
                                    fail_msg (ecran, "Pseudo existe déjà !");
                                else
                                {
                                    if (test == 1)
                                        fail_msg(ecran, "Compte créé avec succes !");
                                }
                            }
                        }
                        //intialiser tout
                        pseudo[0] = '\0';
                        mdp[0] = '\0';
                        __mdp[0] = '\0';
                        length_psd = 0;
                        length_mdp = 0;
                        texte_psd = NULL;
                        texte_mdp = NULL;
                        ecrire = 1;
                        //Retour à la 1ere page
                        choice = choix (ecran);
                        if (choice == -1)   continuer = 0;
                        else                auth_creer (ecran);
                        SDL_Flip(ecran);
                        break;

                    case SDLK_KP_ENTER:
                        if (choice == 1)
                        {
                            user = creerJoueur(pseudo, mdp);
                            test = charger(user);
                            if (test == -1)
                                fail_msg (ecran, "Pseudo ou Mot de passe vide !");
                            else
                            {
                                if (test == 0)
                                    fail_msg (ecran, "Pseudo ou Mot de passe incorrect !");
                                else
                                {
                                    if (test == 1)
                                        jouer(ecran, user);
                                }
                            }
                        }
                        if (choice == 0)
                        {
                            user = creerJoueur(pseudo, mdp);
                            test = creer(user);
                            if (test == -1)
                                fail_msg (ecran, "Pseudo ou Mot de passe vide !");
                            else
                            {
                                if (test == 0)
                                    fail_msg (ecran, "Pseudo existe déjà !");
                                else
                                {
                                    if (test == 1)
                                        fail_msg(ecran, "Compte créé avec succes !");
                                }
                            }
                        }
                        //intialiser tout
                        pseudo[0] = '\0';
                        mdp[0] = '\0';
                        __mdp[0] = '\0';
                        length_psd = 0;
                        length_mdp = 0;
                        texte_psd = NULL;
                        texte_mdp = NULL;
                        ecrire = 1;
                        //Retour à la 1ere page
                        choice = choix (ecran);
                        if (choice == -1)   continuer = 0;
                        else                auth_creer (ecran);
                        SDL_Flip(ecran);
                        break;

                    case SDLK_TAB:
                        if (ecrire == 1)
                        {
                            detruire_trait(ecran, trait, 60, 128);
                            trait = construire_trait(ecran, 60, 198, 1, 22);
                            ecrire = 0;
                        }
                        else
                        {
                            detruire_trait(ecran, trait, 60, 198);
                            trait = construire_trait(ecran, 60, 128, 1, 22);
                            ecrire = 1;
                        }
                        break;

                    case SDLK_BACKSPACE:
                        if (ecrire == 1)
                        {
                            if (length_psd > 0)
                            {
                                auth_creer(ecran);
                                pseudo[length_psd-1] = '\0';
                                texte_psd = TTF_RenderText_Blended(police, pseudo, blanche);
                                SDL_BlitSurface(texte_psd, NULL, ecran, &positionP);
                                SDL_BlitSurface(texte_mdp, NULL, ecran, &positionM);
                                SDL_Flip(ecran);
                                length_psd = length_psd - 1;
                            }
                        }
                        else
                        {
                            if (length_mdp > 0)
                            {
                                auth_creer(ecran);
                                mdp[length_mdp-1] = '\0';
                                __mdp[length_mdp-1] = '\0';
                                texte_mdp = TTF_RenderText_Blended(police, __mdp, blanche);
                                SDL_BlitSurface(texte_mdp, NULL, ecran, &positionM);
                                SDL_BlitSurface(texte_psd, NULL, ecran, &positionP);
                                SDL_Flip(ecran);
                                length_mdp = length_mdp - 1;
                            }
                        }
                        break;

                    default:
                        tmp = SDL_GetKeyName(event.key.keysym.sym);
                        int b = (int) tmp[0];
                        if ( ( (b >= 97 && b <= 122) || (b >= 65 && b <= 90 || (b >= 48 && b <= 57) ) ) && strlen(tmp)==1 )
                        {
                            if (ecrire == 1)
                            {
                                auth_creer(ecran);
                                strcat(pseudo, SDL_GetKeyName(event.key.keysym.sym));
                                texte_psd = TTF_RenderText_Blended(police, pseudo, blanche);
                                SDL_BlitSurface(texte_psd, NULL, ecran, &positionP);
                                SDL_BlitSurface(texte_mdp, NULL, ecran, &positionM);
                                SDL_Flip(ecran);
                                length_psd = length_psd + 1;
                            }
                            else
                            {
                                auth_creer(ecran);
                                strcat(mdp, SDL_GetKeyName(event.key.keysym.sym));
                                strcat(__mdp, "*");
                                texte_mdp = TTF_RenderText_Blended(police, __mdp, blanche);
                                SDL_BlitSurface(texte_mdp, NULL, ecran, &positionM);
                                SDL_BlitSurface(texte_psd, NULL, ecran, &positionP);
                                SDL_Flip(ecran);
                                length_mdp = length_mdp + 1;
                            }
                        }
                        break;
                }
                break;
            default:
                break;
        }
    }
    TTF_CloseFont(police);
    SDL_FreeSurface(trait);
    SDL_FreeSurface(texte_psd);
    SDL_FreeSurface(texte_mdp);
}

void auth_creer (SDL_Surface *ecran)
{
    SDL_Surface *pseudo = NULL, *PWD = NULL, *wallpaper = NULL;
    SDL_Rect position;

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    position.x = 0;
    position.y = 0;
    wallpaper = SDL_LoadBMP("images/auth.bmp");
    SDL_BlitSurface(wallpaper,NULL,ecran,&position);
    //footer
    footer(ecran, 0, 0, 0);

    //pseudo
    position.x = 20;
    position.y = 95;
    TTF_Font *policeP = NULL;
    policeP = TTF_OpenFont("uni.ttf", 20);
    TTF_SetFontStyle(policeP, TTF_STYLE_UNDERLINE);
    SDL_Color couleurN = {0 , 0 , 0};
    pseudo = TTF_RenderText_Blended(policeP, "Votre Pseudo :", couleurN);
    SDL_BlitSurface(pseudo, NULL, ecran, &position);

    //password
    position.x = 20;
    position.y = 160;
    TTF_Font *policeM = NULL;
    policeM = TTF_OpenFont("uni.ttf", 20);
    TTF_SetFontStyle(policeM, TTF_STYLE_UNDERLINE);
    PWD = TTF_RenderText_Blended(policeM, "Mot de Passe :", couleurN);
    SDL_BlitSurface(PWD, NULL, ecran, &position);

    SDL_Flip(ecran);
    TTF_CloseFont(policeM);
    TTF_CloseFont(policeP);
    SDL_FreeSurface(wallpaper);
}

int choix (SDL_Surface *ecran)
{
    SDL_Surface *authSurface = NULL, *creerSurface = NULL, *premiers = NULL, *wallpaper = NULL;
    SDL_Rect position, positionA, positionC, position10;
    SDL_Event event;
    int continuer = 1;
    int choice;

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

    //wallpaper
    position.x = 0;
    position.y = 0;
    wallpaper = SDL_LoadBMP("images/walll.bmp");
    SDL_BlitSurface(wallpaper, NULL, ecran, &position);
    SDL_Flip(ecran);

    //footer
    footer(ecran, 0, 0, 0);

    //Surface d'authentification
    positionA.x = 35;
    positionA.y = 170;
    TTF_Font *policeA = NULL;
    policeA = TTF_OpenFont("uni.ttf", 13);
    SDL_Color couleurN = {0 , 0 , 0};
    authSurface = TTF_RenderText_Blended(policeA, "S'authentifier!", couleurN);
    SDL_BlitSurface(authSurface, NULL, ecran, &positionA);

    //Surface de nouveau compte
    positionC.x = 210;
    positionC.y = 170;
    creerSurface = TTF_RenderText_Blended(policeA, "Créer compte !", couleurN);
    SDL_BlitSurface(creerSurface, NULL, ecran, &positionC);

    //Surface de 10 premiers scores
    position10.x = 105;
    position10.y = 305;
    premiers = TTF_RenderText_Blended(policeA, "10 Premiers scores!", couleurN);
    SDL_BlitSurface(premiers, NULL, ecran, &position10);

    SDL_Flip(ecran);

    while (continuer)
    {
        SDL_WaitEvent(&event);

        switch(event.type)
        {

            case SDL_QUIT:
                continuer = 0;
                choice = -1;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    continuer = 0;
                    choice = -1;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if ( (event.button.x >= positionA.x && event.button.y >= positionA.y) && (event.button.x <= (positionA.x + authSurface->w) && event.button.y <= (positionA.y + authSurface->h) ) )
                    {
                        choice = 1;
                        continuer = 0;
                    }
                    else
                    {
                        if ( (event.button.x >= positionC.x && event.button.y >= positionC.y) && (event.button.x <= (positionC.x + creerSurface->w) && event.button.y <= (positionC.y + creerSurface->h) ) )
                        {
                            choice = 0;
                            continuer = 0;
                        }
                        else
                        {
                            if ( (event.button.x >= position10.x && event.button.y >= position10.y) && (event.button.x <= (position10.x + premiers->w) && event.button.y <= (position10.y + premiers->h) ) )
                            {
                                choice = premiersScores(ecran);
                                continuer = 0;
                            }
                        }
                    }
                }
                break;
            default:
                break;
        }
    }
    TTF_CloseFont(policeA);
    SDL_FreeSurface(premiers);
    SDL_FreeSurface(authSurface);
    SDL_FreeSurface(creerSurface);
    SDL_FreeSurface(wallpaper);
    return choice;
}

SDL_Surface *construire_trait(SDL_Surface *ecran, int X, int Y, int W, int H)
{
    SDL_Surface *trait = NULL;
    SDL_Rect position;
    position.x = X;
    position.y = Y;
    trait = SDL_CreateRGBSurface(SDL_SWSURFACE, W, H, 32, 0, 0, 0, 0);
    SDL_FillRect(trait, NULL, SDL_MapRGB(ecran->format, 40, 180, 255));
    SDL_BlitSurface(trait, NULL, ecran, &position);
    SDL_Flip(ecran);
    return trait;
}

void detruire_trait(SDL_Surface *ecran, SDL_Surface *trait, int X, int Y)
{
    SDL_Rect position;
    position.x = X;
    position.y = Y;
    SDL_FillRect(trait, NULL, SDL_MapRGB(ecran->format, 168, 186, 203));
    SDL_BlitSurface(trait, NULL, ecran, &position);
    SDL_Flip(ecran);
}

void fail_msg (SDL_Surface *ecran, char *message)
{
    SDL_Surface *msg = NULL, *wallpaper = NULL;
    SDL_Rect position;
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    position.x = 0;
    position.y = 0;
    wallpaper = SDL_LoadBMP("images/wallpaper.bmp");
    SDL_BlitSurface(wallpaper,NULL,ecran,&position);
    //footer
    footer(ecran, 50, 50, 50);
    //Fail Message
    position.x = 20;
    position.y = 130;
    TTF_Font *police = NULL;
    police = TTF_OpenFont("CL.ttf", 22);
    SDL_Color couleurN = {0 , 0 , 0};
    msg = TTF_RenderText_Blended(police, message, couleurN);
    SDL_BlitSurface(msg, NULL, ecran, &position);
    SDL_Flip(ecran);
    TTF_CloseFont(police);
    SDL_Delay(2000);
    SDL_FreeSurface(wallpaper);
}

int premiersScores (SDL_Surface *ecran)
{
    SDL_Surface *meilleur = NULL, *wallpaper = NULL, *level1 = NULL, *level2 = NULL, *level3;
    joueur *user = NULL;
    SDL_Rect position;
    char *score;
    char score1[6], score2[6], score3[6];
    FILE *fichier = NULL;
    SDL_Event event, eventC;
    int continuer = 1;
    int niveau;

    fichier = fopen("scores.txt", "r");
    if (fichier == NULL)
    {
        fprintf(stderr,"Ouverture impossible");
        exit(1);
    }
    else
    {
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        position.x = 0;
        position.y = 0;
        wallpaper = SDL_LoadBMP("images/scores.bmp");
        SDL_BlitSurface(wallpaper,NULL,ecran,&position);
        //Footer
        footer(ecran, 250, 230, 30);
        user = (joueur*) malloc(sizeof(joueur));
        TTF_Font *police = NULL;
        police = TTF_OpenFont("uni.ttf", 15);
        SDL_Color couleur = {250 , 230 , 30};
        position.x = 150;
        position.y = 100;
        level1 = TTF_RenderText_Blended(police, "Level 1", couleur);
        SDL_BlitSurface(level1, NULL, ecran, &position);
        position.y += 50;
        level2 = TTF_RenderText_Blended(police, "Level 2", couleur);
        SDL_BlitSurface(level2, NULL, ecran, &position);
        position.y += 50;
        level3 = TTF_RenderText_Blended(police, "Level 3", couleur);
        SDL_BlitSurface(level3, NULL, ecran, &position);
        SDL_Flip(ecran);
        while (continuer)
        {
            SDL_WaitEvent(&eventC);
            switch(eventC.type)
            {
                case SDL_KEYDOWN:
                    if (eventC.key.keysym.sym == SDLK_ESCAPE)
                    {
                        continuer = 0;
                        //break;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (eventC.button.button == SDL_BUTTON_LEFT)
                    {
                        if ( (eventC.button.x >= 150 && eventC.button.y >= 100) && (eventC.button.x <= (150 + level1->w) && eventC.button.y <= (100 + level1->h) ) )
                        {
                            niveau = 1;
                            continuer = 0;
                        }
                        else
                        {
                            if ( (eventC.button.x >= 150 && eventC.button.y >= 150) && (eventC.button.x <= (150 + level2->w) && eventC.button.y <= (150 + level2->h) ) )
                            {
                                niveau = 2;
                                continuer = 0;
                            }
                            else
                            {
                                if ( (eventC.button.x >= 150 && eventC.button.y >= 200) && (eventC.button.x <= (150 + level3->w) && eventC.button.y <= (200 + level3->h) ) )
                                {
                                    niveau = 3;
                                    continuer = 0;
                                }
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        meilleurs(niveau);

        position.x = 0;
        position.y = 0;
        wallpaper = SDL_LoadBMP("images/scores.bmp");
        SDL_BlitSurface(wallpaper,NULL,ecran,&position);
        footer(ecran, 250, 230, 30);

        position.x = 30;
        position.y = 50;
        while (feof(fichier) == 0)
        {
            score[0] = '\0';
            fscanf(fichier,"%s %s %d %s %s %s %d %d\n", user->pseudo, user->mdp, &(user->level), score1, score2, score3, &(user->X), &(user->Y) );
            strcat(score, user->pseudo);
            strcat(score, " - Score : ");
            if (niveau == 1)
                strcat(score, score1);
            if (niveau == 2)
                strcat(score, score2);
            if (niveau == 3)
                strcat(score, score3);

            meilleur = TTF_RenderText_Blended(police, score, couleur);//exit (0);
            SDL_BlitSurface(meilleur, NULL, ecran, &position);
            SDL_Flip(ecran);

            position.y += 25;
            SDL_Delay(30);
        }
        continuer = 1;
        while (continuer)
        {
            SDL_WaitEvent(&event);

            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                return choix(ecran);
            }
        }
        TTF_CloseFont(police);
        SDL_FreeSurface(meilleur);
        SDL_FreeSurface(wallpaper);
    }
}
