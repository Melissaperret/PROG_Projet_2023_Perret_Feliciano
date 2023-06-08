#include <stdio.h>	// pour fopen, fprintf
//#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include "fonctions.h"

void CalculTriangleRectangle(FILE* file, valeurTriangle* valeur, uniteAngle unite)    //pointe sur la structure valeurTriangle 
{
	choixCase choix;

	// Demande de l'unité de l'angle
	printf("Choisissez l'unite de l'angle:\n");
	printf("0. Degree\n");
	printf("1. Radian\n");
	printf("Entrez le numero de l'unite: ");
	scanf("%d", &unite);
	while ((getchar() != '\n') && (getchar() != EOF));

	while (unite < 0 || unite > 1)
	{
		printf("Veuillez rentrer une nouvelle valeur entre 0 ou 1 : ");
		scanf("%d", &unite);
		while ((getchar() != '\n') && (getchar() != EOF));
	}

	printf("\n");

	printf("Choisissez la valeur a calculer :\n");
	printf("0. Hypothenuse \n");
	printf("1. Abcisse \n");
	printf("2. Oppose \n");
	printf("Entrez le numero de votre choix selon le calcul souhaite : ");
	scanf("%d", &choix);
	while ((getchar() != '\n') && (getchar() != EOF));

	switch (choix)
	{
	case HYPOTHENUSE:
		printf("Entrez la valeur de l'abscisse: ");
		scanf("%lf", &(valeur->abscisse));
		while ((getchar() != '\n') && (getchar() != EOF));

		while (valeur->abscisse <= 0)
		{
			printf("Veuillez rentrer une nouvelle valeur pour l'abscisse ");
			scanf("%lf", &(valeur->abscisse));
			while ((getchar() != '\n') && (getchar() != EOF));
		}

		printf("Entrez la valeur du cote oppose: ");
		scanf("%lf", &(valeur->coteOppose));
		while ((getchar() != '\n') && (getchar() != EOF));

		while (valeur->coteOppose <= 0)
		{
			printf("Veuillez rentrer une nouvelle valeur pour le cote oppose : ");
			scanf("%lf", &(valeur->coteOppose));
			while ((getchar() != '\n') && (getchar() != EOF));
		}

		valeur->hypotenuse = sqrt(pow(valeur->abscisse, 2) + pow(valeur->coteOppose, 2));  //le 2 est pour la puissance au carré 
		break;

	case ABSCISSE:
		printf("Entrez la valeur du cote oppose: ");
		scanf("%lf", &(valeur->coteOppose));
		while ((getchar() != '\n') && (getchar() != EOF));

		while (valeur->coteOppose <= 0)
		{
			printf("Veuillez rentrer une nouvelle valeur pour le cote oppose : ");
			scanf("%lf", &(valeur->coteOppose));
			while ((getchar() != '\n') && (getchar() != EOF));
		}

		printf("Entrez la valeur de l'hypotenuse: ");
		scanf("%lf", &(valeur->hypotenuse));
		while ((getchar() != '\n') && (getchar() != EOF));

		while (valeur->hypotenuse <= valeur->coteOppose)
		{
			printf("Veuillez rentrer une nouvelle valeur d'hypothenuse : ");
			scanf("%lf", &(valeur->hypotenuse));
			while ((getchar() != '\n') && (getchar() != EOF));
		}


		valeur->abscisse = sqrt(pow(valeur->hypotenuse, 2) - pow(valeur->coteOppose, 2)); //le 2 est pour la puissance au carré 
		break;

	case OPPOSE:

		printf("Entrez la valeur de l'abscisse: ");
		scanf("%lf", &(valeur->abscisse));
		while ((getchar() != '\n') && (getchar() != EOF));

		while (valeur->abscisse <= 0)
		{
			printf("Veuillez rentrer une nouvelle valeur pour l'abscisse ");
			scanf("%lf", &(valeur->abscisse));
			while ((getchar() != '\n') && (getchar() != EOF));
		}

		printf("Entrez la valeur de l'hypotenuse: ");
		scanf("%lf", &(valeur->hypotenuse));
		while ((getchar() != '\n') && (getchar() != EOF));

		while (valeur->hypotenuse <= valeur->abscisse)
		{
			printf("Veuillez rentrer une nouvelle valeur d'hypothenuse : ");
			scanf("%lf", &(valeur->hypotenuse));
			while ((getchar() != '\n') && (getchar() != EOF));
		}

		valeur->coteOppose = sqrt(pow(valeur->hypotenuse, 2) - pow(valeur->abscisse, 2));
		break;

	default:
		printf("Choix invalide.\n");
		return;
	}

	// Calcul des valeurs trigonométriques
	valeur->sinus = valeur->coteOppose / valeur->hypotenuse;
	valeur->cosinus = valeur->abscisse / valeur->hypotenuse;
	valeur->tangente = valeur->coteOppose / valeur->abscisse;

	switch (unite)
	{
	case DEGREE:
		valeur->degree = (int)round(asin(valeur->sinus) * 180 / M_PI);
		break;

	case RADIAN:
		valeur->radian = asin(valeur->sinus);
		break;
	}

	EcrireDateHeure(file);			//pour écrire l'heure exacte après que l'utilisateur ait rentré ses valeurs 

	switch (choix)
	{
	case HYPOTHENUSE:
		fprintf(file, "%.2g, %.2g / ", valeur->abscisse, valeur->coteOppose);
		break;
	case ABSCISSE:
		fprintf(file, "%.2g, %.2g / ", valeur->coteOppose, valeur->hypotenuse);
		break;
	case OPPOSE:
		fprintf(file, "%.2g, %.2g / ", valeur->abscisse, valeur->hypotenuse);
		break;
	default:
		break;
	}
	fprintf(file, "%.2g, %.2g, %.2g, %.2g, %.2g, %.2g, ", valeur->abscisse, valeur->coteOppose, valeur->hypotenuse, valeur->cosinus, valeur->sinus, valeur->tangente);

	// Affichage des résultats
	printf("\nResultats:\n");
	printf("Abscisse: %.2f\n", valeur->abscisse);
	printf("Cote oppose: %.2f\n", valeur->coteOppose);
	printf("Hypotenuse: %.2f\n", valeur->hypotenuse);
	printf("Cosinus: %.2f\n", valeur->cosinus);
	printf("Sinus: %.2f\n", valeur->sinus);
	printf("Tangente: %.2f\n", valeur->tangente);

	if (unite == DEGREE)
	{
		printf("Angle: %d degres\n\n\n", valeur->degree);
		fprintf(file, "%d", valeur->degree);

	}
	else
	{
		printf("Angle: %.2f radians\n\n\n", valeur->radian);
		fprintf(file, "%.2g", valeur->radian);
	}
	fprintf(file, "\n");
}