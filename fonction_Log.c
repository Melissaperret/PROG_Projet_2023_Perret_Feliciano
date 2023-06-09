#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions.h"

// Fonction pour enregistrer les logs dans un fichier
void EcritureLogs(FILE* file, int compteurConversionBinaire, int compteurTrigonometrie)
{
	// Ouverture d'un deuxième fichier vide 
	FILE* file2 = fopen("Logs.txt", "w");
	if (file == NULL)
	{
		printf("Erreur lors de l'ouverture ou de la création du fichier de logs.\n");
		return;
	}

	// Réécriture des deux premières lignes avec les compteurs
	fprintf(file2, "Compteur utilisation de fonction binaire : %02d\n", compteurConversionBinaire);
	fprintf(file2, "Compteur utilisation de fonction trigonométrique : %02d\n", compteurTrigonometrie);

	char ch;				// Déclaration d'une variable de type char pour stocker un caractère à la fois
	rewind(file);			// Remet le curseur de lecture du fichier "file" au début
	while ((ch = fgetc(file)) != EOF)	//  tant que le caractère lu à partir du fichier "file" n'est pas égal à la valeur spéciale EOF(End Of File), la boucle continuera à s'exécuter.
	{
		fputc(ch, file2);	// Écrit le caractère lu dans le fichier "file2"
	}
	

	// Fermeture du fichier
	fclose(file2);

}

void EcrireDateHeure(FILE* file)
{
	// Obtention de la date et de l'heure actuelles
	time_t now;			// Déclaration d'une variable de type time_t pour stocker le temps actuel
	time(&now);			// Obtention du temps actuel et stockage dans la variable "now"
	struct tm* timeinfo = localtime(&now);	// Convertit le temps actuel en une structure tm locale représentant la date et l'heure


	// Formatage de la date et de l'heure
	char datetime[20];		 // Déclaration d'un tableau de caractères pour stocker la date et l'heure formatées
	strftime(datetime, sizeof(datetime), "%d.%m.%Y - %H:%M", timeinfo);	// Formatage de la date et de l'heure dans le tableau "datetime" selon le format spécifié

	// Écriture de la date et de l'heure actuelles
	fprintf(file, "%s\n", datetime);
}
