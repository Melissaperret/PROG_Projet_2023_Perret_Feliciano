#include <stdio.h>
#include "fonctions.h"

// Fonction pour convertir une valeur r�elle en binaire
void ConversionBinaire(FILE* file)
{
	float valUtilisateur;
	choixModeDigits modes;
	int nbDigits, valEntiere, i, tbResteModulo[10], bit;

	printf("Entrez une valeur : ");
	scanf_s("%f", &valUtilisateur);


	printf("Selectionnez le mode d'affichage :\n");
	printf("0. Mode normal\n");
	printf("1. Mode 8 digits\n");
	printf("2. Mode 16 digits\n");
	printf("3. Mode 32 digits\n");
	printf("Selectionnez le mode :");
	scanf_s("%d", &modes);

	EcrireDateHeure(file);			//pour �crire l'heure exacte apr�s que l'utilisateur ait rentr� ses valeurs 
	fprintf(file, "%.2g / ", valUtilisateur);

	valEntiere = (int)valUtilisateur;		// Partie enti�re de la valeur
	float valFractionnaire = valUtilisateur - valEntiere; // Partie d�cimale de la valeur

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
		nbDigits = 1;
		break;
	}
	printf("\n");

	// Conversion de la partie enti�re en binaire
	// Dans les modes 8, 16, 32, les valeurs flottantes sont arrondis vers le bas 
	if (nbDigits != 0)
	{
		if (nbDigits > 1)
		{
			if (valEntiere == valUtilisateur)
			{
				printf("Partie binaire : 0b ");
				fprintf(file, "0b");
				for (i = nbDigits - 1; i >= 0; i--) // boucle en d�cr�mentation pour aller du msb au lsb et donc afficher les bits via le printf dans le bon ordre
				{
					// 10111 >> 1 = 01011
					//        01011 
					//      & 00001
					//        00001        
					bit = (valEntiere >> i) & 1;	// on utilise un d�calage vers la droite de i bits, ainsi qu'un masque, pour r�cup�rer la valeur du i �me bit (0 ou 1), 
					printf("%d", bit);
					fprintf(file, "%d", bit);
				}
			}
			else
			{
				printf("Impossible de convertir une valeur flottante dans ce mode");
			}
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
			// 23 en d�cimal
			// 23 / 2 = 2*11 + 1
			// 11 = 2*5 + 1
			// 5 = 2*2 + 1
			// 2 = 2*1 + 0
			// 1 = 2*0 + 1
			// 0 => on s'arr�te
			// Donc 23 en binnaire �a donne 10111 (les restes en remontant)

			printf("Partie binaire : 0b ");
			fprintf(file, "0b");
			for (i = 0; valEntiere > 0; i++)
			{
				tbResteModulo[i] = valEntiere % 2; // on calcule les restes via un module 2, et on stock les r�sultats dans le tableau 
				valEntiere = valEntiere / 2; // on divise la valeur par deux pour passer � l'�tape suivante
			}

			// boucle en d�cr�mentation pour r�cup�rer les restes du dernier au premier
			// i-1 pour commencer en r�cup�rant le dernier reste stock� (-1 car i � �t� incr�ment� par la boucle for pr�c�dente apr�s sa derni�re it�ration)
			for (i = i - 1; i >= 0; i--)
			{
				printf("%d", tbResteModulo[i]);
				fprintf(file, "%d", tbResteModulo[i]);
			}

			//partie apr�s la virgule
			if (valFractionnaire != 0.0) // Note: valFractionnaire est comprise entre ]-1, +1[
			{
				printf(".");
				fprintf(file, ".");
				for (i = 0; i < 3; i++) // "se limiter � 3 digits apr�s le 0" (�nonc�)
				{
					valFractionnaire *= 2;			// Multiplie la partie fractionnaire par 2
					bit = (int)valFractionnaire;	// Convertit la partie enti�re de valFractionnaire en un bit
					valFractionnaire -= bit;		// Soustrait la partie enti�re de valFractionnaire pour obtenir la nouvelle partie fractionnaire
					bit = bit & 1;					// Assure que le bit est soit 0 ou 1

					printf("%d", bit);				// Affiche le bit sur la console
					fprintf(file, "%d", bit);		// �crit le bit dans le fichier
				}
			}
		}
	}
	fprintf(file, "\n");
	printf("\n\n");
}