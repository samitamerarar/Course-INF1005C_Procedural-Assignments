////////////////////////////////////////////////////////////////////////////////
///    \file exo4.cpp
///  \author Tamer Arar et Benjamin Heinen
/// \version Dernière entrée : 2016/05/10
///   \since Création : 2016/05/10
///
/// Calcul d'un angle entre un vecteur A et un vecteur B.
////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <cmath>
using namespace std;


int main()
{
	const long double PI = 3.141592653589793238L;
	double composanteAx = 0;
	double composanteAy = 0;
	double composanteBx = 0;
	double composanteBy = 0;
	double cosVecteur = 0;
	double angleVecteur = 0;
	
	cout << "Veuillez entrer les composantes x et y du premier vecteur A : " << endl;
	cin >> composanteAx;
	cin >> composanteAy;

	cout << "Veuillez entrer les composantes x et y du deuxieme vecteur B : " << endl;
	cin >> composanteBx;
	cin >> composanteBy;
	
	cosVecteur = composanteAx*composanteBx + composanteBy * composanteAy;
	cosVecteur /= sqrt(pow(composanteAx, 2) + pow(composanteAy, 2)) * sqrt(pow(composanteBx, 2) + pow(composanteBy, 2));

	angleVecteur = acos(cosVecteur) * 180/PI;

	cout << "L'angle entre les vecteurs (" << composanteAx << ", " << composanteAy << ")" << "et (" << composanteBx << ", " << composanteBy << ")" << " est de " << angleVecteur << " degres." << endl;
	
	system("PAUSE");
	return  0;
}