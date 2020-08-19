////////////////////////////////////////////////////////////////////////////////
///    \file exo5.cpp
///  \author Tamer Arar et Benjamin Heinen
/// \version Dernière entrée : 2016/05/10
///   \since Création : 2016/05/10
///
/// Mise en page d'une facture et création d'un fichier texte.
////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
	string nom = "";
	int nbProduit = 0;
	float prixProduit = 0;
	double resultat = 0;
	double montantHT = 0;
	double taxe = 0;
	double montantTotalHT = 0;
	double taxeTotal = 0;
	string nomProduit = "";
	ifstream entree("ventes.txt");
	ofstream sortie("recapitulatif.txt");

	entree >> nom;
	entree >> nomProduit;
	entree >> nbProduit;
	entree >> prixProduit;
	montantHT = prixProduit*nbProduit;
	montantTotalHT += montantHT;
	taxe = montantHT * 0.1; 
	taxeTotal += taxe;

	cout << "Nom du Client : " << nom << endl << endl;
	cout << "nomProduit : " << nomProduit << " Quantite : " << nbProduit << " Prix : " << prixProduit << " Montant HT : " << montantHT << " Taxe : " << taxe << endl;

	entree >> nomProduit;
	entree >> nbProduit;
	entree >> prixProduit;
	montantHT = prixProduit*nbProduit;
	montantTotalHT += montantHT;
	taxe = montantHT * 0.1;
	taxeTotal += taxe;

	cout << "nomProduit : " << nomProduit << " Quantite : " << nbProduit << " Prix : " << prixProduit << " Montant HT : " << montantHT << " Taxe : " << taxe << endl;
	resultat += (nbProduit * prixProduit);
	entree >> nomProduit;
	entree >> nbProduit;
	entree >> prixProduit;
	montantHT = prixProduit*nbProduit;
	montantTotalHT += montantHT;
	taxe = montantHT * 0.1;
	taxeTotal += taxe;


	cout << "nomProduit : " << nomProduit << " Quantite : " << nbProduit << " Prix : " << prixProduit << " Montant HT : " << montantHT << " Taxe : " << taxe << endl << endl;

	resultat = montantTotalHT + taxeTotal;
	cout << setw(40) << "Total  : " << resultat << endl;

	sortie << nom << " " << resultat << " " << taxeTotal << endl;

	entree.close();
	sortie.close();
	system("PAUSE");
	return 0;
}