#include <stdio.h>	// pour fopen, fprintf
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
	scanf_s("%d", &unite);							//la variable unite est utilisé pour choisir si on souhaite en degré ou radian l'angle alpha
	while ((getchar() != '\n') && (getchar() != EOF));

	while (unite < 0 || unite > 1)
	{
		printf("Veuillez rentrer une nouvelle valeur entre 0 ou 1 : ");
		scanf_s("%d", &unite);
		while ((getchar() != '\n') && (getchar() != EOF));
	}

	printf("\n");

	printf("Choisissez la valeur a calculer :\n");
	printf("0. Hypothenuse \n");
	printf("1. Abcisse \n");
	printf("2. Oppose \n");
	printf("Entrez le numero de votre choix selon le calcul souhaite : ");
	scanf_s("%d", &choix);
	while ((getchar() != '\n') && (getchar() != EOF));

	switch (choix)
	{
	case HYPOTHENUSE:
		printf("Entrez la valeur de l'abscisse : ");
		scanf_s("%lf", &(valeur->abscisse));
		while ((getchar() != '\n') && (getchar() != EOF));

		while (valeur->abscisse <= 0)
		{
			printf("Veuillez rentrer une nouvelle valeur pour l'abscisse : ");
			scanf_s("%lf", &(valeur->abscisse));
			while ((getchar() != '\n') && (getchar() != EOF));
		}

		printf("Entrez la valeur du cote oppose : ");
		scanf_s("%lf", &(valeur->coteOppose));
		while ((getchar() != '\n') && (getchar() != EOF));

		while (valeur->coteOppose <= 0)
		{
			printf("Veuillez rentrer une nouvelle valeur pour le cote oppose : ");
			scanf_s("%lf", &(valeur->coteOppose));
			while ((getchar() != '\n') && (getchar() != EOF));
		}

		valeur->hypotenuse = sqrt(pow(valeur->abscisse, 2) + pow(valeur->coteOppose, 2));  //Calcul pour trouver le côté opposé en utilisant le théorème de pythagore (le 2 est la puissance au carré) 
		break;

	case ABSCISSE:
		printf("Entrez la valeur du cote oppose : ");
		scanf_s("%lf", &(valeur->coteOppose));
		while ((getchar() != '\n') && (getchar() != EOF));

		while (valeur->coteOppose <= 0)
		{
			printf("Veuillez rentrer une nouvelle valeur pour le cote oppose : ");
			scanf_s("%lf", &(valeur->coteOppose));
			while ((getchar() != '\n') && (getchar() != EOF));
		}

		printf("Entrez la valeur de l'hypotenuse : ");
		scanf_s("%lf", &(valeur->hypotenuse));
		while ((getchar() != '\n') && (getchar() != EOF));

		while (valeur->hypotenuse <= valeur->coteOppose)
		{
			printf("Veuillez rentrer une nouvelle valeur d'hypothenuse : ");
			scanf_s("%lf", &(valeur->hypotenuse));
			while ((getchar() != '\n') && (getchar() != EOF));
		}


		valeur->abscisse = sqrt(pow(valeur->hypotenuse, 2) - pow(valeur->coteOppose, 2)); //Calcul pour trouver le côté opposé en utilisant le théorème de pythagore (le 2 est la puissance au carré)
		break;

	case OPPOSE:

		printf("Entrez la valeur de l'abscisse : ");
		scanf_s("%lf", &(valeur->abscisse));
		while ((getchar() != '\n') && (getchar() != EOF));

		while (valeur->abscisse <= 0)
		{
			printf("Veuillez rentrer une nouvelle valeur pour l'abscisse : ");
			scanf_s("%lf", &(valeur->abscisse));
			while ((getchar() != '\n') && (getchar() != EOF));
		}

		printf("Entrez la valeur de l'hypotenuse: ");
		scanf_s("%lf", &(valeur->hypotenuse));
		while ((getchar() != '\n') && (getchar() != EOF));

		while (valeur->hypotenuse <= valeur->abscisse)
		{
			printf("Veuillez rentrer une nouvelle valeur d'hypothenuse : ");
			scanf_s("%lf", &(valeur->hypotenuse));
			while ((getchar() != '\n') && (getchar() != EOF));
		}

		valeur->coteOppose = sqrt(pow(valeur->hypotenuse, 2) - pow(valeur->abscisse, 2));  //Calcul pour trouver le côté opposé en utilisant le théorème de pythagore (le 2 est la puissance au carré)
		break;

	default:
		printf("Choix invalide.\n");
		return;
	}

	// Calcul des valeurs trigonométriques
	valeur->sinus = valeur->coteOppose / valeur->hypotenuse;		//Cacul pour le sinus
	valeur->cosinus = valeur->abscisse / valeur->hypotenuse;		//Cacul pour le cosinus
	valeur->tangente = valeur->coteOppose / valeur->abscisse;		//Cacul pour la tangente

	switch (unite)
	{
	case DEGREE:
		valeur->degree = (int)round(asin(valeur->sinus) * 180 / M_PI);  //Calcul pour convertir la valeur en radian en degré
		break;

	case RADIAN:
		valeur->radian = asin(valeur->sinus);	//Calcul pour les radians
		break;
	default:
		break;
	}

	EcrireDateHeure(file);	//pour écrire l'heure exacte après que l'utilisateur ait rentré ses valeurs 

	// Obligé de faire ce switch pour avoir les valeurs avant les printf, si je les mets dans l'autre switch, ça ne fonctionne plus
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

	// Affichage des résultats
	printf("\nResultats:\n");
	printf("Abscisse: %.2f\n", valeur->abscisse);
	printf("Cote oppose: %.2f\n", valeur->coteOppose);
	printf("Hypotenuse: %.2f\n", valeur->hypotenuse);
	printf("Cosinus: %.2f\n", valeur->cosinus);
	printf("Sinus: %.2f\n", valeur->sinus);
	printf("Tangente: %.2f\n", valeur->tangente);

	//Ecrit dans le fichier les valeurs ci-dessus
	fprintf(file, "%.2g, %.2g, %.2g, %.2g, %.2g, %.2g, ", valeur->abscisse, valeur->coteOppose, valeur->hypotenuse, valeur->cosinus, valeur->sinus, valeur->tangente);
	
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