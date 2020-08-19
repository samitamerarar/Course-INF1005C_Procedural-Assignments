////////////////////////////////////////////////////////////////////////////////
/// \file	 Exercice2.cpp
/// \author  Tamer Arar et Benjamin Heinen
/// \version Derni�re entr�e : 2016/06/14
/// \since   Cr�ation : 2016/06/08
///
/// Donne la somme, en d�cimal, d'un nombre en d�cimal et d'un nombre en hexad�cimal.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int ASCIINOMBRE = 48;
const int ASCIILETTRE = 97;


string lireEntree()
{
	string texte;
	getline(cin, texte);
	return texte;
}
void afficherTexte(const string& texte)
{
	cout.write(&texte[0], texte.size());
}

/**
* Transforme le texte d'un nombre d�cimal en un nombre entier.
*
* \param [in] valeur
*        Le texte d'un nombre d�cimal.
*
* \return la conversion du texte en un nombre entier.
*/
int dec2int(string valeur)
{
	int resultat = 0;
	for (int i = valeur.size()-1; i >= 0; i--)
		resultat += (valeur[i] - ASCIINOMBRE) * pow(10, valeur.size() - i - 1);
	return resultat;
}

/**
* Transforme le texte d'un nombre hexad�cimal en un nombre entier.

* \param [in] valeur
*        Le texte d'un nombre hexad�cimal.
*
* \return la conversion du texte en un nombre entier.
*/
int hex2int(string valeur)
{
	int resultat = 0;
	for (int i = valeur.size() - 1; i >= 0; i--)
	{
		if (isalpha(valeur[i]))
			resultat += (tolower(valeur[i]) - (ASCIILETTRE-10)) * pow(16, valeur.size() - i - 1);
		else if (isdigit(valeur[i]))
			resultat += ((valeur[i]) - ASCIINOMBRE) * pow(16, valeur.size() - i - 1);
	}
	return resultat;
}

/**
* Transforme un entier en une valeur texte d'un nombre d�cimal.

* \param [in] valeur
*        Un entier.
*
* \return la conversion de l'entier en une notation d�cimale textuelle.
*/
string int2dec(int valeur)
{
	string resultat = "";
	char caractere = ' ';
	int reste = 0;
	while (valeur != 0)
	{
		reste = valeur % 10;
			caractere = reste + ASCIINOMBRE;
		resultat += caractere;
		valeur /= 10;
	}
	std::reverse(resultat.begin(), resultat.end());
	return resultat;
}
int main()
{
	string decimal = "";
	string hexadecimal = "";
	string resultat = "";
	int somme = 0;
	afficherTexte("Entrer un nombre decimal: ");
	decimal = lireEntree(); 
	afficherTexte("Entrer un nombre hexadecimal: ");
	hexadecimal = lireEntree();
	somme = dec2int(decimal) + hex2int(hexadecimal);
	resultat = int2dec(somme);
	afficherTexte("La somme decimale est: ");
	afficherTexte(resultat + '\n');
}