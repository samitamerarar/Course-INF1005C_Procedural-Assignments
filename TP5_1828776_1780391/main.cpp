////////////////////////////////////////////////////////////////////////////////
/// \file    main.cpp
/// \author  Tamer Arar et Benjamin Heinen
/// \version Dernière entrée : 2016/06/07
/// \since   Création : 2016/06/01
///
/// Interaction entre le code qui permet l'extraction des images et l'utilisateur.
////////////////////////////////////////////////////////////////////////////////


#pragma region "Inclusions" //{

#include <ciso646>
#include <cstddef>
#include <cstdint>

#include <iomanip>
#include <iostream>
#include <string>

#include "CodeDemande.hpp"
#include "CodeFourni.hpp"


using namespace std;

#pragma endregion //}




void testerPartie1 ( );

void testerPartie2 ( );

string construireNomFichierResultat ( const string&, const string& );




int main ( )
{
	cout.setf(ios::boolalpha);
	
	cout << "---- PARTIE 1 ----" << "\n";
	
	testerPartie1();
	
	cout << "\n";
	
	cout << "---- PARTIE 2 ----" << "\n";
	
	testerPartie2();
	
	cout << "\n";
	
	return 0;
}




/**
 * Effectue des opérations pour tester les fonctions de la partie 1.
 * <p>
 * Le fichier "resultat_partie_1.bmp" devrait correspondre à
 * "flight_line_generator" en noir et blanc.
 */
void
testerPartie1
( )
{
	const unsigned LARGEUR_GENERATEUR = 100;
	const unsigned HAUTEUR_GENERATEUR = 110;
	const string nomFichierGenerateur = "flight_line_generator.bmp";
	const string nomFichierPartie1 = "resultat_partie_1.bmp";
	
	Pixel tamponMemoire[HAUTEUR_GENERATEUR][LARGEUR_GENERATEUR];
	Pixel* tamponPixels[HAUTEUR_GENERATEUR];
	for ( unsigned i = 0; i < HAUTEUR_GENERATEUR; i++ )
		tamponPixels[i] = tamponMemoire[i];
	
	// Voici une image de 100x110 déjà allouée pour vous aider à tester vos
	// fonctions sans faire d'allocation dynamique.
	Image imagePartie1 = {LARGEUR_GENERATEUR, HAUTEUR_GENERATEUR,
	                      tamponPixels};
	
	fstream fichierGenerateur(nomFichierGenerateur, ios::in | ios::binary);
	if ( fichierGenerateur.fail() ) {
		cout << "ERREUR: " << nomFichierGenerateur << " introuvable." << "\n";
		return;
	}
	
	bool ok;
	
	EnteteDib dibGenerateur = lireEnteteFichier(fichierGenerateur);
	
	ok = dibGenerateur.largeurImage == LARGEUR_GENERATEUR and
	     dibGenerateur.hauteurImage == HAUTEUR_GENERATEUR and
	     dibGenerateur.tailleTableau == calculerTailleTableau(imagePartie1);
	cout << "Contenu du DIB OK : " << ok << "\n";
	
	lireDonneesImage(fichierGenerateur, imagePartie1);
	int a = 1;
	convertirNoirEtBlanc(imagePartie1);
	
	ecrireImage(nomFichierPartie1, imagePartie1, ok);
	cout << "Ecriture OK : " << ok << "\n";
}


/**
 * Effectue des opérations pour tester les fonctions de la partie 1.
 * <p>
 * Demande en boucle, jusqu'à l'entrée d'une certaine commande, des coordonnées
 * de rectangle à l'utilisateur, marque ces zones dans "resultat_partie_2.bmp"
 * et les extraits dans des fichiers individuels.
 */
void
testerPartie2
( )
{
	const unsigned EPAISSEUR_TRAIT = 3;
	
	const string commandeFin = "quit";
	const Pixel noir = {0x00, 0x00, 0x00};
	
	const string nomFichierOriginal = "flight_line.bmp";
	const string nomFichierPartie2 = "resultat_partie_2.bmp";
	bool ok;

	fstream fichier;
	string nomFichier = "";
	Rectangle zoneExtraire;
	Image image = lireImage(nomFichierOriginal, ok);
	Image imageExtraite = { 0, 0, 0 };
	if (ok == true)
	{
		cout << "le fichier s'est bien ouvert" << endl;
		cout << "Entrez \"" << commandeFin << "\" "
			<< "comme nom d'image pour quitter." << "\n\n";
		do {
			cout << "quel est le nom de votre image ? " << endl;
			cin >> nomFichier;
			if (nomFichier != commandeFin)
			{
				nomFichier = construireNomFichierResultat(nomFichierPartie2, nomFichier);

				cout << "coin inferieur a extraire ? (x, y)" << endl;
				cin >> zoneExtraire.coin1.x >> zoneExtraire.coin1.y;
				cout << "coin superieur a extraire ? (x, y)" << endl;
				cin >> zoneExtraire.coin2.x >> zoneExtraire.coin2.y;
				imageExtraite = extraireRectangle(image, zoneExtraire);
				ecrireImage(nomFichier, imageExtraite, ok);
				if (ok == true)
					cout << "Succes ecriture" << endl;
				else
					cout << "echec ecriture" << endl;
				tracerContourRectangle(image, noir, zoneExtraire, EPAISSEUR_TRAIT);
				ecrireImage(nomFichierPartie2, image, ok);
			}
		} while (nomFichier != commandeFin);

		desallouerImage(image);
		desallouerImage(imageExtraite);
	}
	else
		cout << "erreur de lecture" << endl;
}


/**
 * Construit le nom du fichier pour les résultats d'extraction de la partie 2.
 * 
 * \param [in] nomFichierPartie2
 * \param [in] nomImageExtraite
 * 
 * \return Le nom du fichier généré.
 */
string
construireNomFichierResultat
( const string& nomFichierPartie2, const string& nomImageExtraite )
{
	size_t positionDernierPoint = nomFichierPartie2.rfind('.');
	string extension = nomFichierPartie2.substr(positionDernierPoint);
	size_t longueur = nomFichierPartie2.size() - extension.length();
	
	return nomFichierPartie2.substr(0, longueur) + "_" +
	       nomImageExtraite + extension;
}

