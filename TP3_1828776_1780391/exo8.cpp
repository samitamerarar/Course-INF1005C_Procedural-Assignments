////////////////////////////////////////////////////////////////////////////////
///    \file exo8.cpp
///  \author Tamer Arar et Benjamin Heinen
/// \version Dernière entrée : 2016/05/17
///   \since Création : 2016/05/16
///
/// Determiner le grade final des etudiants selon leurs notes a partir d'un fichier.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	const int NBMATRICULE = 10;
	ifstream entree("matricules.txt");
	ofstream sortie("grade.txt");
	int i = 0;
	int j = 0;
	string matricule[NBMATRICULE];
	int tableauDecroissantParIdentifiant = 0;
	int note[NBMATRICULE];
	int temporaireNote = 0;
	string temporaireMatricule = "";
	while (i < NBMATRICULE)
	{
		entree >> matricule[i];
		entree >> note[i];
		if (i != 0)
		{
			j = i;
			while (j > 0)
			{
				if (note[j] > note[j - 1])
				{
					temporaireNote = note[j - 1];
					note[j - 1] = note[j];
					note[j] = temporaireNote;
					temporaireMatricule = matricule[j - 1];
					matricule[j - 1] = matricule[j];
					matricule[j] = temporaireMatricule;
				}
				j--;
			}
				
		}
		i++;
		
	}
	sortie << matricule[0] << " " << 'A' << endl;
	for (int k = 1; k < 4;k++)
		sortie << matricule[k] << " " << 'B' << endl;
	for (int k = 4; k < 7; k++)
		sortie << matricule[k] << " " << 'C' << endl;
	for (int k = 7; k < NBMATRICULE; k++)
	{
		if (note[k] >= 10)
			sortie << matricule[k] << " " << 'D' << endl;
		else
			sortie << matricule[k] << " " << "echec" << endl;
	}
	entree.close();
	sortie.close();
	return 0;
}