////////////////////////////////////////////////////////////////////////////////
///    \file exo1.cpp
///  \author Tamer Arar et Benjamin Heinen
/// \version Dernière entrée : 2016/05/17
///   \since Création : 2016/05/16
///
/// Determine si un nombre est premier.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

using namespace std;

int main()
{
	int nombre = 0;	
	int diviseur = 3;
	bool nombrePremierTrouver = true;
	cout << "Entrez un nombre : ";
	cin >> nombre;
	if (nombre % 2 == 1)
	{	
		if (sqrt(nombre) > 3)
		{
			while (diviseur < sqrt(nombre))
			{
				if (nombre % diviseur == 0)
					nombrePremierTrouver = false;
				diviseur += 2;
			}
		}
		if (nombrePremierTrouver)
			cout << "ce nombre est premier" << endl;
		else
			cout << "Ce nombre n'est pas premier" << endl ;
	}
	else 
	{
		if (nombre != 2)
			cout << "Ce nombre n'est pas premier car il est divisible par 2" << endl;
	}
	system("PAUSE");
	return 0;
}