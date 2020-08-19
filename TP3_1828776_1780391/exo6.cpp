////////////////////////////////////////////////////////////////////////////////
///    \file exo6.cpp
///  \author Tamer Arar et Benjamin Heinen
/// \version Dernière entrée : 2016/05/17
///   \since Création : 2016/05/16
///
/// Determiner le min d'une ligne qui est aussi le max d'une colonne sur une matrice donnee.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
	int matrice[4][4];
	int elementLigneMin = 13;
	int elementColonneMax = 5;
	bool trouve = false;
	
	srand(time(nullptr));


	for (int i = 0; i < 4; i++){    
		for (int j = 0; j < 4; j++){
			matrice[i][j] = (rand() % 7) + 6;
			if (matrice[i][j] < 10)
				cout << " ";
			cout << matrice[i][j] << " " ;
		}
		cout << endl;
	}

	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++){ 
			if (matrice[i][j] < elementLigneMin)
			{
				elementLigneMin = matrice[i][j];
			}
		}
		for (int j = 0; j < 4; j++)
		{	
			if (matrice[i][j] == elementLigneMin)
			{
				for (int k = 0; k < 4; k++) 
				{
					if (matrice[k][j] > elementColonneMax)
					{
						elementColonneMax = matrice[k][j];
					}
				}
				if (matrice[i][j] == elementColonneMax)
				{
					cout << "min-max trouve a la position (" << i + 1 << "," << j + 1 << ") avec la valeur " << matrice[i][j] << endl;
					trouve = true;
				}
			}
			elementColonneMax = 5;
		}
		elementLigneMin = 13;
		
	}
	if (!trouve)
		cout << "Aucun min-max n'a ete trouve" << endl;
	system("PAUSE");
	return 0;
}