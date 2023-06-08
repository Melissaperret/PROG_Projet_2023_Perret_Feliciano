#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions.h"

#define MAX_MESSAGE_LENGTH 100					// Définir la longueur maximale du message

// Fonction pour enregistrer les logs dans un fichier
void Ecriturelogs(FILE* file, int compteurConversionBinaire, int compteurTrigonometrie)
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



	char ch;
	rewind(file);
	while ((ch = fgetc(file)) != EOF)
		fputc(ch, file2);

	// Fermeture du fichier
	fclose(file2);

}


void EcrireDateHeure(FILE* file)
{
	// Obtention de la date et de l'heure actuelles
	time_t now;
	time(&now);
	struct tm* timeinfo = localtime(&now);

	// Formatage de la date et de l'heure
	char datetime[20];
	strftime(datetime, sizeof(datetime), "%d.%m.%Y - %H:%M", timeinfo);

	// Écriture de la date et de l'heure actuelles
	fprintf(file, "%s\n", datetime);
}
