////////////////////////////////////////////////////////////////////////////////
///    \file exo3.cpp
///  \author Tamer Arar et Benjamin Heinen
/// \version Dernière entrée : 2016/05/17
///   \since Création : 2016/05/16
///
/// Hauteur atteinte d'une balle selon le nombre de rebonds et de la hauteur initiale.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

using namespace std;

int main()
{
	const double GRAVITE = 9.81;
	int i = 0;
	double hauteur = 0;
	double vitesseAvantRebond = 0;
	double vitesseApresRebond = 0;
	int nbRebond = 0;
	float coefRebond = 0;
	do{
		cout << "Veuillez entrer la hauteur initiale (en m) a laquelle se trouve la balle : " << endl;
		cin >> hauteur;
	} while (hauteur <=0);
	do{
		cout << "Veuillez entrer le nombre de rebonds : " << endl;
		cin >> nbRebond;
	} while (nbRebond <=0);
	do{
		cout << "Veuillez entrer le coefficient de rebond : " << endl;
		cin >> coefRebond;
	} while (coefRebond<0 || coefRebond>1);
	while (i < nbRebond){
		vitesseAvantRebond = (sqrt(2 * GRAVITE*hauteur));
		vitesseApresRebond = (coefRebond*vitesseAvantRebond);
		hauteur = pow(vitesseApresRebond, 2) / (2 * GRAVITE);
		i++;
	}
	cout << "La hauteur est de : " << hauteur << " m" << endl;
	system("PAUSE");
	return 0;
}
