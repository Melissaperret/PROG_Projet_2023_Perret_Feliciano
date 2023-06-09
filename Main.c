// Canevas Projet_Prog 
// Auteur :  M.Perret et C.Feliciano


#include <stdio.h>	 // pour fopen, fprintf
#include <stdlib.h>  //pour exit(0)
#include <time.h>
#include "fonctions.h"

int main()
{
	FILE* file = fopen("TempLogs.txt", "w+");		//Cr�e le fichier + Ouverture, le w+ permet la lecture et l'�criture 
	if (file == NULL)
	{
		printf("Erreur lors de l'ouverture ou de la cr�ation du fichier de logs.\n");
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

		scanf_s("%d", &choixModes);
		while ((getchar() != '\n') && (getchar() != EOF));

		switch (choixModes)
		{
		case CONVERSION:
			ConversionBinaire(file);
			compteurConversionBinaire++; // Incr�mente le compteur de conversions binaires
			break;
		case TRIGONOMETRIE:
			printf("\n");
			CalculTriangleRectangle(file, &valeurs, unite);
			compteurTrigonometrie++;     // Incr�mente le compteur de la fonction trigonom�trique
			break;
		case QUITTER:
			EcritureLogs(file, compteurConversionBinaire, compteurTrigonometrie);  // Appelle la fonction Ecriturelogs pour enregistrer les compteurs dans le fichier
			fclose(file);
			remove("TempLogs.txt");			//On supprime le fichier TempLogs
			exit(0);						//permet de quitter le programme 
		default:
			printf("ERREUR, veuillez choisir entre 0, 1 et 2:\n\n");
		}
	}
	return 0;
}
