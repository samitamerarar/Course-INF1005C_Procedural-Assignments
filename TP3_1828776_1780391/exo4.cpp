////////////////////////////////////////////////////////////////////////////////
///    \file exo4.cpp
///  \author Tamer Arar et Benjamin Heinen
/// \version Dernière entrée : 2016/05/17
///   \since Création : 2016/05/16
///
/// Calculer une valeur rapprocher de la constante PI.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;
int main()
{
	const double PI_THEORIQUE = 3.141593;
	double differencePi = 0;
	double pi = 0;
	double valeurX = 0;
	double valeurY = 0;
	double nbIteration = 0;
	double nbIterationValide = 0;
	int i = 0;
	do{
		cout << "Veuillez entrer le nombre d'iterations souhaite : " << endl;
		cin >> nbIteration;
	} while (nbIteration <= 0);
	srand(time(nullptr));
	while (i < nbIteration){
		valeurX = (2* ((float)rand()) / RAND_MAX) -1;
		valeurY = (2 * ((float)rand()) / RAND_MAX) - 1;
		if (pow(valeurX, 2) + pow(valeurY, 2) < 1)
			nbIterationValide++;
		i++;
	}
	pi = ((nbIterationValide / nbIteration) * 4.0);
	cout << "la valeur de pi est de : " << pi << endl;
	differencePi = abs(pi - PI_THEORIQUE);
	cout << setprecision(6);
	cout << "La difference entre notre pi et sa valeur reel est de : " << differencePi<<endl;
	system("PAUSE");
	return 0;
}