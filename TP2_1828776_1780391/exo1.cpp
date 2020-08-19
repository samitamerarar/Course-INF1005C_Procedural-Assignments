////////////////////////////////////////////////////////////////////////////////
///    \file exo1.cpp
///  \author Tamer Arar et Benjamin Heinen
/// \version Derni�re entr�e : 2016/05/10
///   \since Cr�ation : 2016/05/10
///
/// Les param�tres d'un cercle et sa diff�rence de surface avec un hexagone.
////////////////////////////////////////////////////////////////////////////////


#include <iostream>
using namespace std;

int main()
{
	const long double PI = 3.141592653589793238L;
	float rayon = 0;
	float diametre = 0;
	float circonference = 0;
	float aire = 0;
	float differenceSurface = 0;
	float surfaceHexagone = 0;


	cout << "Saisir le rayon du cercle : ";
	cin >> rayon;

	diametre = rayon * 2;
	circonference = 2 * PI * rayon;
	aire = PI * rayon *rayon;
	surfaceHexagone = 2 * sqrt(3) * (rayon*rayon);
	differenceSurface = surfaceHexagone - aire;

	cout << "pour un cercle de rayon : " << rayon << " cm" << endl
		<< "diametre = " << diametre << " cm" << endl
		<< "circonference = " << circonference << " cm" << endl
		<< "aire = " << aire << " cm2" << endl
		<< "La difference de surface entre l'hexagone et le cercle est " << differenceSurface << " cm2" << endl;
	system("PAUSE");
	return 0;
	
}

