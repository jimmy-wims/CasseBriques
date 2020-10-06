#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

struct brique
{
	int posx;
	int posy;
	int posw;
	int posh;
	int vie;
	SDL_Surface *brique;
	SDL_Texture *texturebrique;
}brique;
void AfficheBrique(SDL_Renderer *renderer,SDL_Rect DestBrique,struct brique tabbrique[])	//gere l'affichage des briques
{
	int i,j,retour,n=0;
	retour=DestBrique.y;
	for(i=0;i<=3;i++) //création du mur de brique
    {
    	for(j=0;j<=15;j++)
    	{
    		if(tabbrique[n].vie>=1)		//affiche la brique si la vie=1
    		{
    			SDL_RenderCopy(renderer,tabbrique[n].texturebrique, NULL, &DestBrique);
    		}
    		DestBrique.x=DestBrique.x+40;
    		n=n+1;
    	}
    	DestBrique.x=0;
    	DestBrique.y=DestBrique.y+27;
    	n=n+1;
   	}
   	DestBrique.x=0;
    DestBrique.y=retour;
}
int main(int argc,char* argv[])
{
	int jouer=1,largeur=640,hauteur=500,i,j,retour,mouvBalle=0,gauche=0,monter=1,n=0,score=0,toucher=0,niveau=1,gagne=1,compteur=0,max=0;
	struct brique tabbrique[64]; //creation d'un tableau permettant de gerer l'affichage des briques
	FILE* fichier = NULL;
	int lettre[64];
	FILE *niv;
	const Uint8 *bouger = SDL_GetKeyboardState(NULL);
	SDL_Event event;
	SDL_Rect DestBrique;
	SDL_Rect SrcRaquette;
	SDL_Rect DestRaquette;
	SDL_Rect SrcBalle;
	SDL_Rect DestBalle;
	SDL_Rect DestScore;
	SDL_Renderer *renderer;
	DestBrique.x=0;	  //coordonnée de la premiere brique
	DestBrique.y=0;
	DestBrique.w=39;
	DestBrique.h=25;
	SrcRaquette.x=299;		//coordonnée de la zone de l'image raquette.jpg desiré
	SrcRaquette.y=289;
	SrcRaquette.w=203;
	SrcRaquette.h=22;
	DestRaquette.w=120;		//coordonnée de la raquette
	DestRaquette.x=(largeur/2)-(DestRaquette.w/2);
	DestRaquette.y=hauteur-50;
	DestRaquette.h=15;
	SrcBalle.x=263;	 		//coordonnée de la zone de l'image balle.jpg desiré
	SrcBalle.y=175;
	SrcBalle.w=207;
	SrcBalle.h=209;
	DestBalle.h=25;			//coordonnée de la balle
	DestBalle.w=25;
	DestBalle.x=DestRaquette.x+((DestRaquette.w/2)-(DestBalle.w/2));
	DestBalle.y=DestRaquette.y-(DestBalle.h+1);
	DestScore.x=50;
	DestScore.y=300;
	DestScore.w=40;
	DestScore.h=40;
	DestBalle.x=DestRaquette.x+((DestRaquette.w/2)-(DestBalle.w/2));
	DestBalle.y=DestRaquette.y-(DestBalle.h+1);
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *fenetre = SDL_CreateWindow("casse brique", 100, 100, largeur, hauteur, SDL_WINDOW_OPENGL); 	//création de la fenetre
	renderer=SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_SOFTWARE);
	IMG_Init(IMG_INIT_JPG);
	SDL_Surface *fond=IMG_Load("fond.jpg");
	if(!fond) {
		printf("IMG_Load: %s\n", IMG_GetError());
	}
	SDL_Texture *texturefond = SDL_CreateTextureFromSurface(renderer, fond);	//crée la texture du fond
	if (texturefond == NULL) {
    fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
    exit(1);
    }
     SDL_Surface *raquette=IMG_Load("raquette.jpg");
	if(!raquette) {
		printf("IMG_Load: %s\n", IMG_GetError());
	}
	SDL_Texture *textureraquette= SDL_CreateTextureFromSurface(renderer, raquette);		//crée la texture de la raquette
	if (textureraquette == NULL) {
    fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
    exit(1);
    }
     SDL_Surface *balle=IMG_Load("balle.jpg");
	if(!balle) {
		printf("IMG_Load: %s\n", IMG_GetError());
	}
	SDL_Texture *textureballe = SDL_CreateTextureFromSurface(renderer, balle);	//crée la texture de la balle
	if (textureballe == NULL) {
    fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
    exit(1);
    }
    IMG_Quit();
    SDL_WaitEvent(&event);
    while(jouer!=0)  //mise en place du jeu
    {
    	if(gagne==1)
    	{
    		n=0;
    		if(niveau==1)
    		{
    			fichier = fopen("niveau1", "r"); //on ouvre le fichier niveau1
    		}
    		else
    		{
    			if(niveau==2)
    			{
    				fichier = fopen("niveau2", "r");//on ouvre le fichier niveau2
    			}
    			else
    			{
    				fichier = fopen("niveau3", "r");//on ouvre le fichier niveau3
    			}
    		}
    			if (fichier != NULL)
    			{
    				do
    				{
    					lettre[compteur]= fgetc(fichier); // On lit le caractère
    					compteur=compteur+1;
    				}
    				while (lettre[compteur] != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
    				fclose(fichier);
    				compteur=0;
    				retour=DestBrique.y;
    			}
    				for(i=0;i<=3;i++) //création du mur de brique
    				{
    					for(j=0;j<=15;j++)
    					{
    						tabbrique[n].posx=DestBrique.x;
    						tabbrique[n].posy=DestBrique.y;
    						tabbrique[n].posw=DestBrique.x+39;
    						tabbrique[n].posh=DestBrique.y+27;
    						DestBrique.x=DestBrique.x+40;
    						if(lettre[n]=='x')		//si le caractere est un y,cela crée une brique orange
    						{
    							tabbrique[n].vie=1;
    							tabbrique[n].brique=IMG_Load("brique.png");
    							tabbrique[n].texturebrique = SDL_CreateTextureFromSurface(renderer, tabbrique[n].brique);
    							max=max+1;
    						}
    						else
    						{
    							if(lettre[n]=='y')		//si le caractere est un y,cela crée une brique bleu
    							{
    								tabbrique[n].brique=IMG_Load("briquebleu.png");
    								tabbrique[n].texturebrique= SDL_CreateTextureFromSurface(renderer, tabbrique[n].brique);
    								tabbrique[n].vie=2;
    								max=max+1;
    							}
    							else
    							{
    								tabbrique[n].vie=0;		//si le caractere est un espace cela met la vie a zero et donc ne l'affiche pas
    							}
    						}
    						n=n+1;
    					}
    					DestBrique.x=0;
						DestBrique.y=DestBrique.y+28;
						n=n+1;
				}
				DestBrique.x=0;
				DestBrique.y=retour;
				gagne=0;
    		}
    	while(SDL_PollEvent(&event))
    	{
    		if(event.type==SDL_QUIT)
    		{
    			jouer = 0;
    		}
    			if(bouger[SDL_SCANCODE_RIGHT]) // Flèche droite/la raquette va a droite
    			{
    					if(DestRaquette.x+DestRaquette.w<=largeur)
    					{
    						DestRaquette.x=DestRaquette.x+30;
    						 if(mouvBalle==0)
    						 {
    						 	 DestBalle.x=DestBalle.x+30;
    						 }
    					}
    					break;
    			}
    			if(bouger[SDL_SCANCODE_LEFT]) // Flèche gauche/la raquette va a gauche
    			{
    					if(DestRaquette.x>=0)
    					{
    						DestRaquette.x=DestRaquette.x-30;
    						if(mouvBalle==0)
    						 {
    						 	 DestBalle.x=DestBalle.x-30;
    						 }
    					}
    					break;
    			}
    			if(bouger[SDL_SCANCODE_SPACE])	//la barre espace lance la balle
    			{
    					mouvBalle=1;
    					break;
            	}
            	if(bouger[SDL_SCANCODE_ESCAPE])		//si la touche echap est est presse cela quitte le jeu
    			{
    					jouer=0;
    					break;
            	}
           break;
        }
        if(mouvBalle==1)
    	{
    		if(DestBalle.x+DestBalle.w>=largeur)	//si la balle touche le bord droit la balle part a gauche
    		{
    			gauche=1;
    		}
    		if(DestBalle.x<=1)		//si la balle touche le bord gauche la balle part a droite
    		{
    			gauche=0;
    		}
    		if(gauche==0)		//la balle va vers la droite
    		{
    			DestBalle.x=DestBalle.x+1;
    		}
    		if(gauche==1)		//la balle va vers la gauche
    		{
    		 	DestBalle.x=DestBalle.x-1;
    		}
    		if(DestBalle.y<=1)	//la balle va vers le bas
    		{
    			monter=0;
    		}
    		if(DestBalle.y>=hauteur)	//si la  balle quitte l'ecran cela ferme le jeu
    		{
    			jouer=0;
    		}
    		if(monter==1)	//la balle va vers le haut
    		{
    			DestBalle.y=DestBalle.y-1;
    		}
    		if(monter!=1)//la balle va vers le bas
    		{
    			DestBalle.y=DestBalle.y+1;
    		}
    		if(((DestBalle.x>=DestRaquette.x)&&(DestBalle.x<=DestRaquette.x+DestRaquette.w))&&((DestBalle.y+DestBalle.h>=DestRaquette.y)&&((DestBalle.y+DestBalle.h<=DestRaquette.y+DestRaquette.h))))
    		{
    			monter=1;
    		}
    	}
    	for(i=0;i<=66;i++)
    	{
    		if(tabbrique[i].vie>=1)		//regarde si la balle touche une brique
    		{
    			if((((DestBalle.y>=tabbrique[i].posy)&&(DestBalle.y<=tabbrique[i].posh))||((DestBalle.y+DestBalle.h>=tabbrique[i].posy)&&(DestBalle.y+DestBalle.h<=tabbrique[i].posh)))&&((DestBalle.x>=tabbrique[i].posx)&&(DestBalle.x<=tabbrique[i].posw)))
    			{
    				toucher=1;
				}
				if((((DestBalle.y>=tabbrique[i].posy)&&(DestBalle.y<=tabbrique[i].posh))||((DestBalle.y+DestBalle.h>=tabbrique[i].posy)&&(DestBalle.y+DestBalle.h<=tabbrique[i].posh)))&&(((DestBalle.x+DestBalle.w)>=tabbrique[i].posx)&&((DestBalle.x+DestBalle.w)<=tabbrique[i].posw)))
				{
					toucher=1;
				}
				if((((DestBalle.x>=tabbrique[i].posx)&&(DestBalle.x<=tabbrique[i].posw))||(((DestBalle.x+DestBalle.w)>=tabbrique[i].posx)&&((DestBalle.x+DestBalle.w)<=tabbrique[i].posw)))&&((DestBalle.y>=tabbrique[i].posy)&&(DestBalle.y<=tabbrique[i].posh)))
				{
					toucher=1;
				}
				if((((DestBalle.x>=tabbrique[i].posx)&&(DestBalle.x<=tabbrique[i].posw))||(((DestBalle.x+DestBalle.w)>=tabbrique[i].posx)&&((DestBalle.x+DestBalle.w)<=tabbrique[i].posw)))&&(((DestBalle.y+DestBalle.h)>=tabbrique[i].posy)&&((DestBalle.y+DestBalle.h)<=tabbrique[i].posh)))
				{
					toucher=1;
				}
				if(toucher==1)
				{
					tabbrique[i].vie=tabbrique[i].vie-1;
					DestBalle.y=DestBalle.y+1;
					monter=0;
					if(tabbrique[i].vie==0)
					{
						score=score+1;		//augmentation du score quand la brique se casse
					}
					toucher=0;
					if(gauche==1)
					{
						DestBalle.x=DestBalle.x-2;
					}
					else
					{
						DestBalle.x=DestBalle.x+2;
					}
				}
			}
    	}
    	if(score==max)
    	{
    		printf("Bravo!!!");
    		if(niveau==3)	//fin du jeu
    		{
    		jouer=0;
    		}
    		else
    		{		//remise a zero du jeu avec le niveau suivant
    			niveau=niveau+1;
    			gagne=1;
    			score=0;
    			max=0;
    			DestBalle.y=DestRaquette.y-(DestBalle.h+1);
    			DestBalle.x=DestRaquette.x+((DestRaquette.w/2)-(DestBalle.w/2));
    			mouvBalle=0;
    			monter=1;
    		}
    	}
    		SDL_RenderCopy(renderer,texturefond, NULL, NULL);
    		SDL_RenderCopy(renderer,textureballe,&SrcBalle, &DestBalle);
    		SDL_RenderCopy(renderer,textureraquette, &SrcRaquette, &DestRaquette);
    		AfficheBrique(renderer,DestBrique,tabbrique);
    		SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(fenetre);
   	SDL_DestroyRenderer(renderer);
   	SDL_DestroyTexture(texturefond);
   	SDL_Quit();
    return EXIT_SUCCESS;
}
