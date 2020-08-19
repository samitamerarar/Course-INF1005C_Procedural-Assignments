#include <utility>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream> 
#include <clocale>

using namespace std;

const int NB_ANNEE = 15;
const int NB_MAX_PILOTE = 6;
const int NB_MAX_CONSTRUCTEUR = 2;

struct Pilote {
	string nom;
	string pays;
	int nbCourse;
	int nbVictoire;
	int anneeChampions[NB_ANNEE];
	int nbAnnee;
	string constructeurs[NB_MAX_CONSTRUCTEUR];
	int nbConstructeur;
};

struct ListePilote{
	Pilote pilotes[NB_MAX_PILOTE];
	int nbPilote;
};

/**
*	Lit le fichier et le stock dans une liste
*  \return  La liste de pilote \p liste.
*/
ListePilote lireFichier()
{
	Pilote pilotes[NB_MAX_PILOTE];
	ListePilote liste;
	int i = 0;
	int j = 0;
	int k = 0;
	string chaine = "";
	stringstream entier;
	ifstream entree("champions.txt");
	liste.nbPilote = 0;
	
	if (ws(entree).fail())
	{
		return liste;
	}
	else
	{
		while (getline(entree, chaine))
		{
			switch (i)
			{
			case 0:  liste.pilotes[j].nom = chaine;
					liste.nbPilote++;
					break;
				case 1:  liste.pilotes[j].pays = chaine.substr(0, chaine.find(';'));
					liste.pilotes[j].nbCourse = atoi(chaine.substr(chaine.find(';') + 1, chaine.find(' ')).c_str());
					liste.pilotes[j].nbVictoire = atoi(chaine.substr(chaine.find(' '), 3).c_str());
						break; 
				case 2:
					entier << chaine;
					while (entier >> liste.pilotes[j].anneeChampions[k++]);
					liste.pilotes[j].nbAnnee = k - 1;
					break;
				case 3 : 
					while (chaine.find(';') != string::npos)
					{
						liste.pilotes[j].constructeurs[k] = chaine.substr(0, chaine.find(';'));
						chaine.erase(0, chaine.find(';')+1);
						k++;
					}
					liste.pilotes[j].nbConstructeur = k;
					i = -1;
					j++;
					break;
			}
			i++;
			k = 0;
			entier.clear();
		}
		entree.close();
		return liste;
	}
}


/**
*	Afficher la liste des champions
*  \param       liste   La liste des champions
*/

void afficherListeChampions(ListePilote liste)
{
	int i = 0;
	int j = 0;
	while (i < liste.nbPilote)
	{
		cout << "nom : " << liste.pilotes[i].nom << endl
			<< "pays : " << liste.pilotes[i].pays << endl
			<< "Nombre de courses : " << liste.pilotes[i].nbCourse << endl
			<< "Nombre de victoires : " << liste.pilotes[i].nbVictoire << endl;
		if (liste.pilotes[i].nbAnnee > 0)
		{
			cout << "A ete champion du monde en : ";
			while (j < liste.pilotes[i].nbAnnee)
				cout << liste.pilotes[i].anneeChampions[j++] << ", ";
			cout << endl;
			j = 0;
		}
		else
			cout << "Il n'a jamais été champion du monde"<<endl;
		cout << "Les constructeurs sont : ";
		while (j < liste.pilotes[i].nbConstructeur)
			cout << liste.pilotes[i].constructeurs[j++] << ", ";
		cout << endl<<endl<<endl;
		i++;
		j = 0;
	}
}


/**
*	Recuperer la liste des pilotes d'un pays ainsi que le nombre de victoire de ce pays
*  \param       pilotes			La liste des pilotes
*  \param       pays			Le pays que dont l'on souhaite recuperer les informations
*  \param       nbVictoire		Le nombre de victoire du pays
*  \return  La liste de pilote \p liste.
*  \return  le nombre de victoire \p nbVictoire.
*/
ListePilote listePilotesPays(Pilote pilotes[], string pays, int& nbVictoire)
{
	ListePilote liste;
	int i = 0;
	int j = 0;
	int nbVictoirePays = 0;
	liste.nbPilote = 0;
	while (i < 6)
	{
		if (pilotes[i].pays == pays)
		{
			liste.pilotes[j] = pilotes[i];
			nbVictoirePays += pilotes[i].nbVictoire;
			j++;
			liste.nbPilote++;
		}
		i++;
	}
	nbVictoire = nbVictoirePays;
	return liste;
}

/**
*	Recuperer le meilleur pilote de la liste de pilote fourni
*  \param       liste			La liste des pilotes
*  \return  Le meilleur pilote \p pilote.
*/

Pilote meilleurPilote(ListePilote liste)
{
	int i = 0;
	Pilote pilote= liste.pilotes[i++];
	while (i < liste.nbPilote)
	{
		if (pilote.nbVictoire < liste.pilotes[i].nbVictoire)
			pilote = liste.pilotes[i];
		i++;
	}
	return pilote;
}

int main()
{
	setlocale(LC_ALL, "");
	int choix = 0;
	Pilote pilote[NB_MAX_PILOTE];
	ListePilote liste = lireFichier();
	int nbVictoire = 0;
	string pays = "";
	if (liste.nbPilote != 0)
	{
		do{
			cout << "Que voulez vous faire : " << endl
				<< "1 : Afficher la liste des champions " << endl
				<< "2 : Afficher la liste de pilotes par pays" << endl
				<< "3 : Afficher le meilleur pilote" << endl;
			cin >> choix;
		} while (choix < 1 || choix > 3);

		switch (choix){
		case 1: afficherListeChampions(liste);
			break;
		case 2: cout << "Veuillez ecrire un pays" << endl;
			cin >> pays;
			cout << endl;
			liste = listePilotesPays(liste.pilotes, pays, nbVictoire);
			cout << "Le pays a " << nbVictoire << " victoires" << endl;
			afficherListeChampions(liste);
			break;
		case 3:
			cout << "Le meilleur pilote est " << meilleurPilote(liste).nom << endl;
			break;
		}
	}
	else
		cout << "Le fichier ne c'est pas chargé correctement ou est vide" << endl;
	return 0;
}