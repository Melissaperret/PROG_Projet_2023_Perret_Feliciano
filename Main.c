// Canevas Projet_Prog 
// Auteur :  M.Perret et C.Feliciano

// Suppression avertissement C4996
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> // pour fopen, fprintf
#include <stdlib.h>
#include <time.h>
#include "fonctions.h"

// ouvre le fichier au début du main, passe le pointeur à fonctions de calcul, 

int main()
{

	FILE* file = fopen("TempLogs.txt", "w+");
	if (file == NULL)
	{
		printf("Erreur lors de l'ouverture ou de la création du fichier de logs.\n");
		return;
	}


	valeurTriangle valeurs;
	uniteAngle unite = 0;
	choixDuMode choixModes = 0;
	int compteurConversionBinaire = 0;			//Mettre dans le fichier fonction binaire
	int compteurTrigonometrie = 0;				//Mettre dans le fichier fonction trigo

	while (1)
	{
		printf("Veuillez choisir votre mode :\n");
		printf("0. Conversion binaire\n");
		printf("1. Trigonometrie\n");
		printf("2. Quitter\n");
		printf("Entrez le numero de votre choix : ");

		scanf("%d", &choixModes);
		while ((getchar() != '\n') && (getchar() != EOF));

		switch (choixModes)
		{
		case CONVERSION:
			ConversionBinaire(file);
			compteurConversionBinaire++;
			break;
		case TRIGONOMETRIE:
			printf("\n");
			CalculTriangleRectangle(file, &valeurs, unite);
			compteurTrigonometrie++;
			break;
		case QUITTER:
			Ecriturelogs(file, compteurConversionBinaire, compteurTrigonometrie);
			fclose(file);
			remove("TempLogs.txt");
			exit(0);		//permet de quitter le programme 
		default:
			printf("ERREUR, veuillez choisir entre 0 et 1:\n\n");
		}
	}
	return 0;
}
