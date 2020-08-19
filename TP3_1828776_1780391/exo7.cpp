////////////////////////////////////////////////////////////////////////////////
///    \file exo7.cpp
///  \author Tamer Arar et Benjamin Heinen
/// \version Dernière entrée : 2016/05/17
///   \since Création : 2016/05/16
///
/// Determiner le nombre de lignes, les espaces et les voyelles dans un fichier.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	string nomFichier = "";
	string contenu = "";
	int nombreLigne = 0;
	int nombreVoyelle = 0;
	int nombreEspace = 0;
	int i = 0;
	cout << "Veuillez entrer le nom de votre fichier" << endl;
	cin >> nomFichier;

	ifstream entree(nomFichier);
	if (!ws(entree).fail())
	{
		while (!entree.eof())
		{
			i = 0;
			nombreLigne++;
			getline(entree, contenu);
			while (i < contenu.size())
			{
				if (char(tolower(contenu[i])) == 'a' || char(tolower(contenu[i])) == 'e' ||
					char(tolower(contenu[i])) == 'i' || char(tolower(contenu[i])) == 'o' ||
					char(tolower(contenu[i])) == 'u' || char(tolower(contenu[i])) == 'y')
					nombreVoyelle++;

				if (contenu[i] == ' ')
					nombreEspace++;
				i++;
			}
		}
		cout << "Il y a " << nombreEspace << "espace, " << nombreLigne << " lignes, et " << nombreVoyelle << " voyelles" << endl;
	}
	else
		cout << "Impossible de lire le fichier. Verifiez qu'il existe bien." << endl;

	system("PAUSE");
	return 0;
}