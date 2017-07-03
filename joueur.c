#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "joueur.h"

/*
    ActualTime = SDL_GetTicks();           //Pour avoir le nombre de milisecondes ecoules depuis le lancement de la SDL
    if ((ActualTime - LastTime >= 1000)&&(GameOver!=1)) // Si 1000 ms au moins se sont écoulées
    {
        ResultFlag=CheckResult(TabCases);
        LastTime = ActualTime;
        TimeNow++;
    }
*/
joueur *creerJoueur (char *pseudo, char *mdp)
{
    joueur *user;
    int i;
    user = (joueur*) malloc(sizeof(joueur));
    strcpy(user->pseudo, pseudo);
    strcpy(user->mdp, mdp);
    user->level = 1;
    for (i = 0 ; i < LEVELS ; i++)
        user->score[i] = 0;
    user->X = 7;
    user->Y = 2;

    return user;
}

int creer (joueur *user)
{
    joueur *tmp = NULL;
    FILE *fichier;
    if (strcmp(user->pseudo, "") != 0 && strcmp(user->mdp, "") != 0)
    {
        fichier = fopen("joueurs.txt","r");
        tmp = (joueur*) malloc(sizeof(joueur));
        if (fichier== NULL)
        {
            fprintf(stderr,"Ouverture en ecriture impossible");
            return 2;
        }
        else
        {
                while(fscanf(fichier,"%s %s %d %d %d %d %d %d\n", tmp->pseudo, tmp->mdp, &(tmp->level), &(tmp->score[0]), &(tmp->score[1]), &(tmp->score[2]), &(tmp->X), &(tmp->Y) ) != EOF)
                {
                    if (strcmp(user->pseudo, tmp->pseudo) == 0 )
                        return 0;
                }
                fichier = fopen("joueurs.txt","a");
                fprintf(fichier,"%s %s %d %d %d %d %d %d\n",user->pseudo,user->mdp,user->level,user->score[0],user->score[1],user->score[2],user->X,user->Y);
                fclose(fichier);
                return 1;
        }
    }
    else
        return -1;
}

int charger (joueur *user)
{
    joueur *tmp = NULL;
    FILE *fichier;
    int i;
    if (strcmp(user->pseudo, "") != 0 && strcmp(user->mdp, "") != 0)
    {
        fichier = fopen("joueurs.txt","r");
        tmp = (joueur*) malloc(sizeof(joueur));
        if(fichier != NULL)
        {
            while(fscanf(fichier,"%s %s %d %d %d %d %d %d\n", tmp->pseudo, tmp->mdp, &(tmp->level), &(tmp->score[0]), &(tmp->score[1]), &(tmp->score[2]), &(tmp->X), &(tmp->Y) ) != EOF)
            {
                if (strcmp(user->pseudo, tmp->pseudo) == 0 && strcmp(user->mdp, tmp->mdp) == 0)
                {
                    strcpy(user->pseudo, tmp->pseudo);
                    strcpy(user->mdp, tmp->mdp);
                    user->level = tmp->level;
                    for (i = 0 ; i < LEVELS ; i++)
                        user->score[i] = tmp->score[i];
                    user->X = tmp->X;
                    user->Y = tmp->Y;

                    return 1;
                }
            }
            return 0;
        }
        else
        {
            return 2;
        }
    }
    else
        return -1;
}

void sauvegarder(joueur *user)
{
    joueur *liste = NULL;
    FILE *fichier, *tmp;
    int i = 0;

    fichier = fopen("joueurs.txt","r+");
    tmp = fopen("tmp.txt","w+");

    if (fichier == NULL || tmp == NULL)
    {
        fprintf(stderr,"Ouverture impossible");
        exit(1);
    }
    else
    {
        liste = (joueur*) malloc(sizeof(joueur));

        while(feof(fichier) == 0)
        {
            fscanf(fichier,"%s %s %d %d %d %d %d %d\n", liste->pseudo, liste->mdp, &(liste->level), &(liste->score[0]), &(liste->score[1]), &(liste->score[2]), &(liste->X), &(liste->Y) );
            if ( strcmp(liste->pseudo, user->pseudo) == 0 )
            {
                for(i=0;i<LEVELS;i++)
                {
                    liste->score[i] = user->score[i];
                }
                liste->level = user->level;
                strcpy(liste->mdp,user->mdp);
                liste->X     = user->X;
                liste->Y     = user->Y;
            }
            fprintf(tmp,"%s %s %d %d %d %d %d %d\n",liste->pseudo,liste->mdp,liste->level,liste->score[0],liste->score[1],liste->score[2],liste->X,liste->Y);
        }
        rewind(fichier);
        rewind(tmp);
        while (feof(tmp) == 0)
        {
            fscanf(tmp,"%s %s %d %d %d %d %d %d\n", liste->pseudo, liste->mdp, &(liste->level), &(liste->score[0]), &(liste->score[1]), &(liste->score[2]), &(liste->X), &(liste->Y) );
            fprintf(fichier,"%s %s %d %d %d %d %d %d\n", liste->pseudo, liste->mdp, liste->level, liste->score[0], liste->score[1], liste->score[2], liste->X, liste->Y);
        }
    }
    fclose(fichier);
    fclose(tmp);
}

void meilleurs (int niveau)
{
    joueur *liste = NULL;
    FILE *fichier, *scores;
    int i = 0, perfect, cpt = 0, x, y;
    if (niveau == 1)
    {
        perfect = 13;
        x = 5;
        y = 3;
    }
    if (niveau == 2)
    {
        perfect = 12;
        x = 7;
        y = 2;
    }
    if (niveau == 3)
    {
        perfect = 9;
        x = 4;
        y = 3;
    }

    fichier = fopen("joueurs.txt","r");
    scores = fopen("scores.txt","w");

    if (fichier == NULL || scores == NULL)
    {
        fprintf(stderr,"Ouverture impossible");
        exit(1);
    }
    else
    {
        liste = (joueur*) malloc(sizeof(joueur));

        while(feof(fichier) == 0 && cpt < 10)
        {
            fscanf(fichier,"%s %s %d %d %d %d %d %d\n", liste->pseudo, liste->mdp, &liste->level, &(liste->score[0]), &(liste->score[1]), &(liste->score[2]), &(liste->X), &(liste->Y) );

            if ( liste->level > niveau && cpt < 10)
                cpt++;
        }
         //Savoir le nombre de personnes qui ont déjà fini le jeu s'ils sont < 10

        while(i < cpt && i < 10)
        {
            rewind(fichier);
            while (feof(fichier) == 0)
            {
                fscanf(fichier,"%s %s %d %d %d %d %d %d\n", liste->pseudo, liste->mdp, &liste->level, &(liste->score[0]), &(liste->score[1]), &(liste->score[2]), &(liste->X), &(liste->Y) );
                if (liste->level > niveau && liste->score[niveau-1] == perfect && i < 10)
                {
                    fprintf(scores,"%s %s %d %d %d %d %d %d\n",liste->pseudo,liste->mdp,liste->level,liste->score[0],liste->score[1],liste->score[2],liste->X,liste->Y);
                    i++;
                }
            }
            perfect++;
        }
    }
    fclose(scores);
    fclose(fichier);
}
