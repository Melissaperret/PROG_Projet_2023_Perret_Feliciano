#pragma once
#ifndef FONCTIONS
#define FONCTIONS

typedef enum { DEGREE, RADIAN } uniteAngle;
typedef enum { HYPOTHENUSE, ABSCISSE, OPPOSE } choixCase;
typedef enum { CONVERSION, TRIGONOMETRIE, QUITTER } choixDuMode;
typedef enum { RIEN, HUITBITS, SEIZEBITS, TRENTEDEUXBITS } choixModeDigits;

typedef struct
{
	double abscisse;
	double coteOppose;
	double hypotenuse;
	double sinus;
	double cosinus;
	double tangente;
	union angleUnite
	{
		int degree;
		double radian;
	};
}valeurTriangle;

void ConversionBinaire(FILE* file);
void CalculTriangleRectangle(FILE* file, valeurTriangle* valeur, uniteAngle unite);
void EcritureLogs(FILE* file, int compteurConversionBinaire, int compteurTrigonometrie);
void EcrireDateHeure(FILE* file);

#endif // !FONCTION_CONVERSION

