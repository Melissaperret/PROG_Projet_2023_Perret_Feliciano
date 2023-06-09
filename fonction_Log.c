#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonctions.h"

// Fonction pour enregistrer les logs dans un fichier
void EcritureLogs(FILE* file, int compteurConversionBinaire, int compteurTrigonometrie)
{
	// Ouverture d'un deuxi�me fichier vide 
	FILE* file2 = fopen("Logs.txt", "w");
	if (file == NULL)
	{
		printf("Erreur lors de l'ouverture ou de la cr�ation du fichier de logs.\n");
		return;
	}

	// R��criture des deux premi�res lignes avec les compteurs
	fprintf(file2, "Compteur utilisation de fonction binaire : %02d\n", compteurConversionBinaire);
	fprintf(file2, "Compteur utilisation de fonction trigonom�trique : %02d\n", compteurTrigonometrie);

	char ch;				// D�claration d'une variable de type char pour stocker un caract�re � la fois
	rewind(file);			// Remet le curseur de lecture du fichier "file" au d�but
	while ((ch = fgetc(file)) != EOF)	//  tant que le caract�re lu � partir du fichier "file" n'est pas �gal � la valeur sp�ciale EOF(End Of File), la boucle continuera � s'ex�cuter.
	{
		fputc(ch, file2);	// �crit le caract�re lu dans le fichier "file2"
	}
	

	// Fermeture du fichier
	fclose(file2);

}

void EcrireDateHeure(FILE* file)
{
	// Obtention de la date et de l'heure actuelles
	time_t now;			// D�claration d'une variable de type time_t pour stocker le temps actuel
	time(&now);			// Obtention du temps actuel et stockage dans la variable "now"
	struct tm* timeinfo = localtime(&now);	// Convertit le temps actuel en une structure tm locale repr�sentant la date et l'heure


	// Formatage de la date et de l'heure
	char datetime[20];		 // D�claration d'un tableau de caract�res pour stocker la date et l'heure format�es
	strftime(datetime, sizeof(datetime), "%d.%m.%Y - %H:%M", timeinfo);	// Formatage de la date et de l'heure dans le tableau "datetime" selon le format sp�cifi�

	// �criture de la date et de l'heure actuelles
	fprintf(file, "%s\n", datetime);
}
