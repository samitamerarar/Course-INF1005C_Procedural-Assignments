////////////////////////////////////////////////////////////////////////////////
///    \file exo5.cpp
///  \author Tamer Arar et Benjamin Heinen
/// \version Dernière entrée : 2016/05/17
///   \since Création : 2016/05/16
///
/// Classer une serie d'entiers en affichant d'abord les pairs et, ensuite les impairs.
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

using namespace std;
int main()
{
	int i = 0;
	int j = 0;
	int tableau[10];
	int tableauFinal[10];
	while (i < 10)
	{
		cout << "veuillez entrer une valeur du tableau"<<endl;
		cin >> tableau[i];
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (tableau[i] % 2 == 0)
		{
			tableauFinal[j] = tableau[i];
			j++;
		}
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (tableau[i] % 2 == 1)
		{
			tableauFinal[j] = tableau[i];
			j++;
		}
		i++;
	}
	cout << "{";
	i = 0;
	while (i < 10)
	{
		cout << tableauFinal[i];
		if (i < 9)
			cout << ", ";
		i++;
	}
	cout << "}"<<endl;

	system("PAUSE");
	return 0;
}