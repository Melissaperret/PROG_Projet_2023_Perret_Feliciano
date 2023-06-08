#include <stdio.h>
#include <math.h>
#include "fonctions.h"

// Fonction pour convertir une valeur réelle en binaire
void ConversionBinaire(FILE* file)
{
	float valUtilisateur;
	choixModeDigits modes;
	int nbDigits, valEntiere, i, tbResteModulo[10], bit;

	printf("Entrez une valeur  : ");
	scanf("%f", &valUtilisateur);


	printf("Selectionnez le mode d'affichage :\n");
	printf("0. Mode normal\n");
	printf("1. Mode 8 digits\n");
	printf("2. Mode 16 digits\n");
	printf("3. Mode 32 digits\n");
	printf("Selectionnez le mode :");
	scanf("%d", &modes);

	EcrireDateHeure(file);			//pour écrire l'heure exacte après que l'utilisateur ait rentré ses valeurs 
	fprintf(file, "%.2g / ", valUtilisateur);

	valEntiere = valUtilisateur;		// Partie entière de la valeur
	float valFractionnaire = valUtilisateur - valEntiere; // Partie décimale de la valeur

	switch (modes)
	{
	case RIEN:
		nbDigits = 0;
		break;
	case HUITBITS:
		nbDigits = 8;
		break;
	case SEIZEBITS:
		nbDigits = 16;
		break;
	case TRENTEDEUXBITS:
		nbDigits = 32;
		break;
	default:
		printf("Mode invalide. \n ");
		return 1;
	}
	printf("\n");

	// Conversion de la partie entière en binaire
	// Dans les modes 8, 16, 32, les valeurs flottantes sont arrondis vers le bas 
	if (nbDigits != 0)
	{
		printf("Partie entiere : 0b ");
		fprintf(file, "0b");
		for (i = nbDigits - 1; i >= 0; i--) // boucle en décrémentation pour aller du msb au lsb et donc afficher les bits via le printf dans le bon ordre
		{
			// 10111 >> 1 = 01011
			//		01011 
			//	  &	00001
			//		00001		

			bit = (valEntiere >> i) & 1; // on utilise un décalage vers la droite de i bits, ainsi qu'un masque, pour récupérer la valeur du i ème bit (0 ou 1), 
			printf("%d", bit);
			fprintf(file, "%d", bit);
		}
	}
	else
	{
		if (valEntiere < 0)
		{
			printf("Impossible dans ce mode \n");
		}
		else
		{
			// 23 en décimal
			// 23 / 2 = 2*11 + 1
			// 11 = 2*5 + 1
			// 5 = 2*2 + 1
			// 2 = 2*1 + 0
			// 1 = 2*0 + 1
			// 0 => on s'arrête
			// Donc 23 en binnaire ça donne 10111 (les restes en remontant)

			printf("Partie entiere : 0b ");
			fprintf(file, "0b");
			for (i = 0; valEntiere > 0; i++)
			{
				tbResteModulo[i] = valEntiere % 2; // on calcule les restes via un module 2, et on stock les résultats dans le tableau 
				valEntiere = valEntiere / 2; // on divise la valeur par deux pour passer à l'étape suivante
			}

			// boucle en décrémentation pour récupérer les restes du dernier au premier
			// i-1 pour commencer en récupérant le dernier reste stocké (-1 car i à été incrémenté par la boucle for précédente après sa dernière itération)
			for (i = i - 1; i >= 0; i--)
			{
				printf("%d", tbResteModulo[i]);
				fprintf(file, "%d", tbResteModulo[i]);
			}

			//partie après la virgule
			if (valFractionnaire != 0.0) // Note: valFractionnaire est comprise entre ]-1, +1[
			{
				printf(".");
				for (i = 0; i < 3; i++) // "se limiter à 3 digits après le 0" (énoncé)
				{
					valFractionnaire *= 2;
					bit = (int)valFractionnaire;
					valFractionnaire -= bit;
					bit = bit & 1; // Assure que le bit est soit 0 ou 1

					printf("%d", bit);
					fprintf(file, "%d", bit);
				}
			}
		}
	}
	fprintf(file, "\n");
	printf("\n\n");
}