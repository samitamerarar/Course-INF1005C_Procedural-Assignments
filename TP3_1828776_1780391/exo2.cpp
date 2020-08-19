////////////////////////////////////////////////////////////////////////////////
///    \file exo2.cpp
///  \author Tamer Arar et Benjamin Heinen
/// \version Dernière entrée : 2016/05/17
///   \since Création : 2016/05/16
///
/// Nombre de mois necessaire au remboursement d'une dette.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

using namespace std;

int main()
{
	float argent = 0;
	float taux = 0;
	float montantRembourse = 0;
	double montant = 0;
	double montantRembourseTotal = 0;
	int nbMois = 0;
	do {
		cout << "Combien d'argent voulez vous emprunter ?" << endl;
		cin >> argent;
	} while (argent <= 0);
	do {
		cout << "quelle est la somme qui sera rembourse chaque mois ?" << endl;
		cin >> montantRembourse;
	} while (montantRembourse <= 0);
	do {
		cout << "Quel est le taux d'interet ?" << endl;
		cin >> taux;
	} while (taux < 0 || taux > 100.00);
	montant = argent;
	while (montantRembourseTotal < montant)
	{
		if (nbMois % 12 == 0)
			montant += argent * (taux / 100);
		montantRembourseTotal += montantRembourse;
		nbMois++;
			
	}
	cout << "Il faut " << nbMois << " mois pour rembourser le montant indique" << endl;

	system("PAUSE");
	return 0;
}