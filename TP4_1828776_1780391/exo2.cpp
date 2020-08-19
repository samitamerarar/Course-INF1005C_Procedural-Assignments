////////////////////////////////////////////////////////////////////////////////
///    \file exo2.cpp
///  \author Tamer Arar et Benjamin Heinen
/// \version Dernière entrée : 2016/05/28
///   \since Création : 2016/05/25
///
/// Bibliothèque de tableaux de nombres entiers.
////////////////////////////////////////////////////////////////////////////////

#include <utility>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

const int NB_MAX_TABLEAU_COLONNE = 8;
const int TAILLE = 5;
const int TAILLE_TABLEAU_B = 8;


struct Nombres{
	int nbNombreSuperieur;
	int nbNombreEgaux;
	int nbNombreInferieur;
};
/**
*  Retourne une valeur aleatoire comprise entre un minimum et un maximum.
*  \param       minimum			Valeur minimale de l'intervale.
*  \param       maximum			Valeur maximale de l'intervale.
*  \return  valeurAleatoire		Valeur aleatoire comprise dans l'intervale.
*/
int valeurAleatoire(int minimum, int maximum)	
{
	int valeurAleatoire = 0;
	valeurAleatoire = rand() % (maximum + 1 - minimum) + minimum;
	return valeurAleatoire;
}
/**
*  Initie un tableau a une dimension de valeurs aleatoires comprises entre 2 bornes predefinies.
*  \param       minimum					Valeur minimale de l'intervale.
*  \param       maximum					Valeur maximale de l'intervale.
*  \param       tableau					Tableau a une dimension.
*  \param       taille					Nombre de colonnes que peux prendre le tableau.
*/
void tableauAleatoire(int minimum, int maximum, int tableau[], int taille)
{
	int i = 0;
	while (i < taille)
		tableau[i++] = valeurAleatoire(minimum, maximum);
}
/**
*  Initie un tableau a deux dimensions de valeurs aleatoires comprises entre 2 bornes predefinies.
*  \param	    tableau								Tableau a deux dimensions.
*  \param       minimum								Valeur minimale de l'intervale.
*  \param       maximum								Valeur maximale de l'intervale.
*  \param       nbLigne								Nombre de lignes que peux prendre le tableau.
*/
void tableauDeuxDimensionsAleatoire(int tableau[][NB_MAX_TABLEAU_COLONNE], int minimum, int maximum, int nbLigne)
{
	for (int i = 0; i < nbLigne; i++)
	{
		for (int j = 0; j < NB_MAX_TABLEAU_COLONNE; j++)
		{
			tableau[i][j] = valeurAleatoire(minimum, maximum);
		}
	}
}
/**
*  Compare un nombre choisis avec les données d'un tableau a deux dimensions.
*  \param       nombre							Valeur du nombre choisis a comparer.
*  \param       ligne							Nombre de lignes que contiendrais le tableau.
*  \param       tableau							Tableau a deux dimensions.
*  \return		nombres							Retourne la structure contenant le nombre de nombres inferieurs,egaux et superieurs au nombre saisit.
*/
Nombres trouverNombre(int nombre, int ligne, int tableau[][NB_MAX_TABLEAU_COLONNE])
{
	int i = 0;
	int j = 0;
	Nombres nombres;
	int nbPetitNombre = 0;
	int nbNombreEgaux = 0;
	int nbGrandNombre = 0;
	while (i < ligne)
	{
		while (j < NB_MAX_TABLEAU_COLONNE)
		{
			if (tableau[i][j] < nombre)
				nbPetitNombre++;
			else if (tableau[i][j] == nombre)
				nbNombreEgaux++;
			else
				nbGrandNombre++;
			j++;
		}
		j = 0;
		i++;
	}
	nombres.nbNombreInferieur = nbPetitNombre;
	nombres.nbNombreEgaux = nbNombreEgaux;
	nombres.nbNombreSuperieur = nbGrandNombre;
	return nombres;
}
/**
*  Verifie si un tableau A est inclut dans un tableau B à la position p si Bp+i = Ai pour tout indice i de A.
*  \param       tableauA				Premier tableau a une dimension.
*  \param       tailleA					Nombre de lignes que prend le premier tableau.
*  \param		tableauB				Deuxieme tableau a une dimension.
*  \param       tailleB					Nombre de lignes que prend le deuxieme tableau.
*  \return		indice					Retourne la valeur de i indice du tableau A de l'equation Bp+i = Ai où p est la position.
*/
int AIncluDansB(int tableauA[], int tailleA, int tableauB[], int tailleB)
{
	int indice = 0;
	bool trouve = true;
	bool succes = false;
	for (int i = 0; i < tailleB; i++)
	{
		for (int j = 0; j < tailleA; j++)
		{
			if (tableauB[i + j] != tableauA[j])
			{
				trouve = false;
			}
		}
		if (trouve == true)
		{
			indice = i;
			succes = true;
		}
		trouve = true;
	}
	if (!succes)
		indice = -1;
	return indice;
}
int main()
{
	int maximum = 0;
	int minimum = 0;
	int nombre = 0;
	int indice = 0;
	int tableau1[TAILLE];
	int tableau2[TAILLE][8];
	int tableauB[TAILLE_TABLEAU_B];
	Nombres nombres;
	srand(time(0));
	cout << "Veuillez entrer un minimum " << endl;
	cin >> minimum;
	cout << "Veuillez entrer un maximum " << endl;
	cin >> maximum;
	cout << "Un nombre aleatoire compris entre les deux bornes serait : " << valeurAleatoire(minimum, maximum) << endl << endl;
	tableauAleatoire(minimum, maximum, tableau1, TAILLE);
	cout << "tableau A " << " " << endl;
	for (int i = 0; i < TAILLE; i++)
		cout << tableau1[i] << " ";
	cout << endl << endl;
	tableauAleatoire(minimum, maximum, tableauB, TAILLE_TABLEAU_B);
	cout << "tableau B " << " " << endl;
	for (int i = 0; i < TAILLE_TABLEAU_B; i++)
		cout << tableauB[i] << " ";
	cout << endl << endl;
	tableauDeuxDimensionsAleatoire(tableau2, minimum, maximum, TAILLE);
	cout << "tableau a 2 dimensions : " << endl << endl;
	for (int i = 0; i < TAILLE; i++){
		for (int j = 0; j < 8; j++)
			cout << tableau2[i][j] << " ";
		cout << endl;
	}
	cout << "Veuillez choisir le nombre a comparer" << endl;
	cin >> nombre;
	nombres = trouverNombre(nombre, TAILLE, tableau2);
	cout << "Il y a " << nombres.nbNombreSuperieur << " nombres superieurs a " << nombre << endl;
	cout << "Il y a " << nombres.nbNombreInferieur << " nombres inferieurs a " << nombre << endl;
	cout << "Il y a " << nombres.nbNombreEgaux << " nombres egaux a " << nombre << endl;
	indice = AIncluDansB(tableau1, TAILLE, tableauB, TAILLE_TABLEAU_B);
	if (indice != -1)
		cout << "Le tableau A est inclut dans le tableau B a partir de l'indice " << indice << endl;
	else
		cout << "Le tableau A n'est pas inclut dans le tableau B" << endl;
	return 0;
}