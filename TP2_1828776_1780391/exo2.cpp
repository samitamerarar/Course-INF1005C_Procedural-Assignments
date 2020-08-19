////////////////////////////////////////////////////////////////////////////////
///    \file exo2.cpp
///  \author Tamer Arar et Benjamin Heinen
/// \version Dernière entrée : 2016/05/10
///   \since Création : 2016/05/10
///
/// Souhaiter la bienvenue à quelqu'un à un certain cours.
////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <string>
using namespace std;

int main()
{ 
	string nom = "";
	string sigle = "";
	string bonjour = "Bonjour ";
	string bienvenue = ", bienvenue au cours ";
	string poly = " de Poly.";

	cout << "Veuillez entrer votre nom." << endl;
	cin >> nom;
	cout << "Veuillez entrer le sigle du cours." <<endl;
	cin >> sigle;

	cout << bonjour << nom << bienvenue << sigle << poly << endl;
	system("PAUSE");
	return 0;
}