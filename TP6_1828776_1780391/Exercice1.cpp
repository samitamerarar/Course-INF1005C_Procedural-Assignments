////////////////////////////////////////////////////////////////////////////////
/// \file	 Exercice1.cpp
/// \author  Tamer Arar et Benjamin Heinen
/// \version Dernière entrée : 2016/06/14
/// \since   Création : 2016/06/08
///
/// Classe, efface et affiche des films selon les Acteurs ou la collection.
////////////////////////////////////////////////////////////////////////////////

#pragma region "Includes"//{
#define _CRT_SECURE_NO_WARNINGS // On permet d'utiliser les fonctions de copies de chaînes qui sont considérées non sécuritaires.
#include <iostream>
#include <fstream>
#include <string>
#include <cwchar>
#include <limits>
#include <algorithm>
#include <cstdint>
using namespace std;

#include "debogageMemoire.hpp"
#include "unicode.hpp"        
#include "structures.hpp"      

#pragma endregion//}

typedef uint8_t UInt8;
typedef uint16_t UInt16;

#pragma region "Fonctions de base pour lire le fichier binaire"//{

UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
wstring lireWstring(istream& fichier)
{
	wstring texte;
	texte.resize(lireUint16(fichier));
	fichier.read((char*)&texte[0], sizeof(texte[0]) * texte.length());
	return texte;
}

#pragma endregion//}

/**
* Ajoute un film existant à une collection.

* \param [in] film
*        un pointeur vers un film existant.
* \param [in] collection
*        l'adresse d'une collection de films.
*
*/

void ajouterFilm(Film* film, Collection& collection)
{
	Film** temporaire;
	if (collection.nFilms >= collection.capaciteFilms)
	{
		if (collection.capaciteFilms == 0)
		{
			collection.capaciteFilms = 1;
			collection.films = new Film*[collection.capaciteFilms];
		}
		else
		{
			collection.capaciteFilms *= 2;
			temporaire = new Film*[collection.capaciteFilms];
			for (int i = 0; i < collection.nFilms; i++)
			{
				temporaire[i] = new Film;
				temporaire[i] = collection.films[i];
			}
			delete collection.films;
			collection.films = temporaire;
		}
		
	}
	collection.films[collection.nFilms] = film;
	collection.nFilms++;
}

/**
* Compte un maximum d'acteurs dans une collection
*
* \param [in] collection
*        Une collection de films.
*
* \return un nombre maximal d'acteurs.
*/
int compterMaxActeur(Collection collection)
{
	int nActeur = 0;
	for (int i = 0; i < collection.nFilms; i++)
	{
		nActeur += collection.films[i]->nActeurs;
	}
	return nActeur;
}

/**
* Préciser dans quel film joue un acteur.
*
* \param [in] fichier
*        Une collection de films.
* \param [in] acteur
*        Un acteur.
*
*/
void acteurJoueDans(Acteur* acteur, Collection collection)
{
	Collection collectionJoueDans = {};
	for (int i = 0; i < collection.nFilms; i++)
	{
		for (int j = 0; j < collection.films[i]->nActeurs; j++)
			if (collection.films[i]->acteurs[j] == acteur)
				ajouterFilm(collection.films[i], collectionJoueDans);
	}
	acteur->joueDans = collectionJoueDans;
}

/**
* Préciser les films d'une collection dans lesquels les acteurs jouent.
*
* \param [in] collection
*        Une collection de films.
*
*/
void remplirCollectionJoueDans(Collection collection)
{
	Acteur** acteurs;
	int nActeur = 0;
	bool acteurTrouve = false;
	int nActeursMax = compterMaxActeur(collection);
	acteurs = new Acteur*[nActeursMax];
	for (int i = 0; i < collection.nFilms; i++)
	{
		for (int j = 0; j < collection.films[i]->nActeurs; j++)
		{
			for (int k = 0; k < nActeur; k++)
			{
				if (acteurs[k] == collection.films[i]->acteurs[j])
					acteurTrouve = true;
			}
			if (!acteurTrouve == true)
			{
				acteurJoueDans(collection.films[i]->acteurs[j], collection);
				acteurs[nActeur++] = collection.films[i]->acteurs[j];
			}
			acteurTrouve = false;
		}
	}
}



/**
* Retire un film existant d'une collection.

* \param [in] film
*        un pointeur vers un film existant.
* \param [in] collection
*        l'adresse d'une collection de films.
*
*/

void supprimerFilm(Film* film, Collection& collection)
{
	for (int i = 0; i < collection.nFilms; i++)
	{
		if (collection.films[i] == film)
		{
			for (int j = i + 1; j < collection.nFilms; j++)
				collection.films[j - 1] = collection.films[j];
			collection.films[collection.nFilms - 1] = nullptr;
			collection.nFilms--;
		}
	}
}

/**
* Recherche et retrouve un Acteur parmis une collection de films.
*
* \param [in] nom
*        Le nom de l'Acteur.
* \param [in] collection
*        Une collection de films.
*
* \return vers un acteur existant ou un acteur vide.
*/

Acteur *trouverActeur(wstring nom, Collection collection)
{
	Acteur* acteur;
	bool trouve = false;
	for (int i = 0; i < collection.nFilms && trouve == false; i++)
	{
		for (int j = 0; j < (*collection.films[i]).nActeurs && trouve == false; j++)
		{
			if (collection.films[i][0].acteurs[j][0].nom == nom)
			{
				acteur = collection.films[i][0].acteurs[j];
				trouve = true;
			}
		}
	}
	if (trouve == false)
		acteur = nullptr;
	return acteur;
}

/**
* Alloue une capacité nécessaire pour les Acteurs pour pouvoir ensuite créer une collection.
*
* \param [in] fichier
*        Le fichier duquel on retrouve les informations des Acteurs.
* \param [in] collection
*        Une collection de films.
*
* \return un nouvel acteur.
*/

Acteur* lireActeur(istream& fichier, Collection collection)
{
	Acteur* acteur = new Acteur;
	Acteur* acteurRetour;
	acteur->nom				= lireWstring(fichier);
	acteur->anneeNaissance = lireUint16(fichier);
	acteur->sexe = lireUint8(fichier);
	acteurRetour = trouverActeur(acteur->nom, collection);
	if (acteurRetour == nullptr)
 		 acteurRetour = acteur;
	return acteurRetour; 
}

/**
* Alloue une capacité nécessaire pour les films pour pouvoir ensuite créer une collection.
*
* \param [in] fichier
*        Le fichier duquel on retrouve les informations de films.
* \param [in] collection
*        Une collection de films.
*
* \return un nouveau film.
*/

Film* lireFilm(istream& fichier, Collection collection)
{
	Film* film = new Film;
	film->titre       = lireWstring(fichier);
	film->realisateur = lireWstring(fichier);
	film->anneeSortie = lireUint16(fichier);
	film->recette = lireUint16(fichier);
	film->nActeurs = lireUint8(fichier);
	(film->acteurs) = new Acteur *[film->nActeurs];		
	for (int i = 0; i < film->nActeurs; i++)
		film->acteurs[i] = new Acteur;
	for (int i = 0; i < film->nActeurs; i++) {
		film->acteurs[i] = lireActeur(fichier, collection); 
	}
	return film;
}

/**
* Crée une collection de films à partir d'un fichier.
*
* \param [in] nomFichier
*        Le nom du fichier où se retrouvent les informations des films et des Acteurs.
*
* \return une nouvelle collection de films et de leurs Acteurs.
*/

Collection creerListe(string nomFichier)
{
	ifstream fic(nomFichier, ios::binary);
	fic.exceptions(ios::failbit);

	int nFilms = lireUint16(fic);
	
	Collection collection = {};
	collection.films = new Film *[nFilms];
	for (int i = 0; i < nFilms; i++)
	{
		collection.films[i] = new Film;
	}
	collection.capaciteFilms = nFilms;

	for (int i = 0; i < nFilms; i++) {
		ajouterFilm(lireFilm(fic, collection), collection); 
	
	}
	remplirCollectionJoueDans(collection);
	return collection; 
}

/**
* Détruit un film choisis et désalloue la mémoire lié à ce film, ainsi de celle de ses acteurs.
*
* \param [in] film
*        Le film à détruire.
* \param [in] collection
*        L'adresse d'une collection de films.
*
*/

void detruireFilm(Film *film, Collection &collection)
{
	Acteur** acteurs = film[0].acteurs;
	supprimerFilm(film, collection);
	bool acteurTrouve = false;
	for (int k = 0; k < film[0].nActeurs; k++)
	{
		for (int i = 0; i < collection.nFilms; i++)
		{
			for (int j = 0; j < collection.films[i][0].nActeurs; j++)
			{
				if (collection.films[i][0].acteurs[j] == acteurs[k])
					acteurTrouve = true;
			}
		}
		if (acteurTrouve == false)
		{
			delete acteurs[k];
			acteurs[k] = 0;
			acteurTrouve = true;
		}
	}
	delete film;
	film = 0;
}

/**
* Détruit une collection de films choisis et, donc, désalloue la mémoire lié à tous ses films, ainsi de celle de ses acteurs.
*
* \param [in] collection
*        L'adresse d'une collection de films.
*
*/

void detruireCollection(Collection *collection)
{
	int nFilms = collection->nFilms;
	for (int i = 0; i < nFilms; i++)
		detruireFilm(collection[0].films[0], *collection);
	delete collection;
	collection = 0;
}

/**
* Prend en paramètre un acteur et affiche ses informations.
*
* \param [in] acteur
*        Un acteur choisis.
*
*/

void afficherActeur(const Acteur& acteur)
{
	wcout << "nom : " << acteur.nom << endl << "annee Naissance : " << acteur.anneeNaissance << endl << "sexe : " << acteur.sexe << endl;
}

/**
* Affiche un film, ses acteurs et tous ses caractéristiques.
*
* \param [in] film
*        Contient les données du film en question.
*
*/

void afficherFilm(Film film)
{
	wcout << "titre : " << film.titre << endl
		<< "realisateur : " << film.realisateur << endl
		<< "annee de sortie : " << film.anneeSortie << endl
		<< "recette : " << film.recette << endl
		<< "nombre d'acteurs : " << film.nActeurs << endl;
	for (int i = 0; i < film.nActeurs; i++)
		afficherActeur(film.acteurs[i][0]);
}

/**
* Affiche une collection de films avec tous leurs caractéristiques.
*
* \param [in] collection
*        Contient les données du la collection en question.
*
*/

void afficherCollectionDeFilms(Collection collection)
{
	for (int i = 0; i < collection.nFilms; i++)
	{
		afficherFilm(collection.films[i][0]);
	}
}

/**
* Afficher, selon l'Acteur choisis, tous les films dans lesquels il joue dedans.
*
* \param [in] nom
*        Le fichier duquel on retrouve les informations de films.
* \param [in] collection
*        Une collection de films.
*
*/

void afficherFilmAvecActeur(wstring nom, Collection collection)
{
	Acteur* acteur = trouverActeur(nom, collection);
 	afficherCollectionDeFilms(acteur->joueDans);
}
void exempleAffichageUnicode()
{
	// Exemples de chaînes C non Unicode:
	static const char texteNonUnicode[] = "Un texte pas Unicode permet l'affichage des caractères Latin-1, àâéèêïùç...\n";
	wcout << "Une chaine de 'char' est considérée en Latin-1 (pas Unicode):" << endl
		<< texteNonUnicode << endl;
	
	static const wchar_t texteUnicode[] = L"Russe: Добрый день\nGrec: Γεια σας\nTeintes de gris: ░▒▓█\n";
	wcout << L"Une chaine de 'wchar_t' est Unicode et permet les caractères plus spéciaux ♪♫:" << endl
		<< texteUnicode << endl;
	
	// Exemple de string (pas Unicode) et wstring (Unicode):
	static const string stringNonUnicode = "Une string avec caractères Latin-1.";
	static const wstring stringUnicode = L"Une string Unicode ░▒▓█♪♫.";
	wcout << stringNonUnicode << endl // Nous avons fourni une fonction qui permet d'afficher des 'string' sur wcout.
		<< stringUnicode << endl;
}

int main()
{
	Collection* collection = new Collection;
	wstring nom = L"Benedict Cumberbatch";
	initDebogageMemoire(); // Affichera dans la "Sortie" de VisualStudio les fuites de mémoire.
	initUnicode(); // Permet d'afficher des caractères Unicode (pas seulement les accents latin).
	Acteur* acteur;
	exempleAffichageUnicode(); 
	
	static const wstring LIGNE_DE_SEPARATION = L"\n════════════════════════════════════════\n";

	*collection = creerListe("films.bin"); 

	wcout << LIGNE_DE_SEPARATION << L"Le premier film de la liste est:" << endl;
	afficherFilm(collection->films[0][0]);
	wcout << LIGNE_DE_SEPARATION << L"Les films sont:" << endl;
	afficherCollectionDeFilms(*collection);
	acteur = trouverActeur(nom, *collection);
	acteur->anneeNaissance = 1976;
	wcout << LIGNE_DE_SEPARATION << L"Liste des films où Benedict Cumberbatch joue sont:" << endl;
	afficherFilmAvecActeur(nom, *collection);
	detruireFilm(collection->films[0], *collection);
	wcout << LIGNE_DE_SEPARATION << L"Les films sont maintenant:" << endl;
	afficherFilm(collection->films[0][0]);
	detruireCollection(collection);
}
