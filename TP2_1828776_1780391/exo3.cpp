////////////////////////////////////////////////////////////////////////////////
///    \file exo3.cpp
///  \author Tamer Arar et Benjamin Heinen
/// \version Dernière entrée : 2016/05/10
///   \since Création : 2016/05/10
///
/// Comparaison entre sin(x) et sa valeur approximative des 3 premiers termes de sa suite.
////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

int main()
{
	int nombreAleatoire = 0;
	double resultatSin = 0;
	double serieSin = 0;
	double difference = 0;
	srand(time(nullptr));
	nombreAleatoire = rand()%2;
	
	resultatSin = sin(nombreAleatoire);
	serieSin = (pow(nombreAleatoire, 3) / 6) + (pow(nombreAleatoire, 5) / 120) - (pow(nombreAleatoire, 7), 5040);
	difference = abs(resultatSin - nombreAleatoire);
	cout << "pour x = " << nombreAleatoire << " la difference entre les trois premiers termes de la suite du sinus et la fonction sinus est : " << difference << endl;

	system("PAUSE");
	return 0;


}
