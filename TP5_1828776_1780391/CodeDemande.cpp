////////////////////////////////////////////////////////////////////////////////
/// \file    CodeDemande.cpp
/// \author  Tamer Arar et Benjamin Heinen
/// \version Dernière entrée : 2016/06/07
/// \since   Création : 2016/06/01
///
/// Extraire des plus petites images à partir des images des cibles.
////////////////////////////////////////////////////////////////////////////////


#pragma region "Inclusions" //{

#include <ciso646>
#include <cstddef>
#include <cstdint>

#include <fstream>
#include <string>
#include <cmath>
#include "CodeFourni.hpp"

#include "CodeDemande.hpp"


using namespace std;

#pragma endregion //}



const int LARGEUR_IMAGE = 100;
const int HAUTEUR_IMAGE = 100;
#pragma region "Globaux" //{

#pragma region "Fonctions" //{

/**
* Lit l'entete du fichier image Bitmap.
*
* \param [in] fichier
*        le fichier a lire.
*
* \return l'entete lu.
*/
EnteteDib lireEnteteFichier(fstream& fichier)
{
	// TODO: Lire l'entête DIB du fichier donné.
	EnteteDib enteteDib;
	EnteteBmp enteteBmp;
	fichier.read((char*)&enteteBmp, sizeof(enteteBmp));
	fichier.read((char*)&enteteDib, sizeof(enteteDib));
	return enteteDib;
}

/**
* Lit les pixels d'une image dans un fichier de format Bitmap.
*
* \param [in] fichier
*        Le fichier à lire.
* \param [in] image
*        l'image a traiter.
*
*/
void lireDonneesImage(fstream& fichier, Image& image) 
{
	int padding = calculerTaillePadding(image);
	if (padding % 4 != 0)
		padding += (4 - (padding % 4));

	// TODO: Se positionner au début du tableau de pixels dans le fichier.
	fichier.seekp(sizeof(EnteteDib) + sizeof(EnteteBmp), ios::beg);

	// TODO: Pour chaque ligne de l'image, lire la ligne et sauter le padding.
	for (int i = image.hauteur-1; i >= 0; i--)
	{
		for (int j = 0; j < image.largeur; j++)
			fichier.read((char*)&image.pixels[i][j], sizeof(image.pixels[i][j]));
		fichier.seekp(padding, ios::cur);
	}
}

/**
* Ecrit dans un fichier, contentant des entêtes, une image.
*
* \param [in] fichier
*        Le fichier à écrire.
* \param [in] image
*        l'image a traiter.
*
*/
void ecrireDonneesImage(fstream& fichier, const Image& image)
{
	// TODO: Se positionner au début du tableau de pixels dans le fichier (après
	//       les entêtes).
	fichier.seekp(sizeof(EnteteBmp) + sizeof(EnteteDib), ios::beg);


	// TODO: Pour chaque ligne de l'image, écrire la ligne puis écrire des bytes
	//       à zéro pour le padding.
	for (int i = image.hauteur-1; i >= 0; i--)
	{
		for (int j = 0; j < image.largeur; j++)
			fichier.write((char*)&image.pixels[i][j], sizeof(image.pixels[i][j]));
			fichier.write("0", calculerTaillePadding(image));
	}

}

/**
* Creer un fichier Bitmap à l'aide d'une image.
*
* \param [in] fichier
*        Le fichier à écrire.
* \param [in] image
*        l'image a traiter.
* \param [out] ok
*        Condition booléenne; ouverture réussite du fichier ou non.
*
*/
void ecrireImage(const string& nomFichier, const Image& image, bool& ok)
{
	// TODO: Ouvrir un fichier en écriture binaire.
	fstream fichierEcrire(nomFichier, ios::binary | ios::out);

	if (fichierEcrire.fail())
		ok = 0;
	else {
		// Si l'ouverture n'a pas échouée :
		ok = 1;
		// TODO: Construire les entêtes à partir de l'image.
		EnteteBmp resultatBmp = construireEnteteBmp(image);
		EnteteDib resultatDib = construireEnteteDib(image);
		// TODO: Écrire les entêtes dans le fichier.
		fichierEcrire.write((char*)&resultatBmp, sizeof(resultatBmp));
		fichierEcrire.write((char*)&resultatDib, sizeof(resultatDib));

		// TODO: Écrire les données (pixels) de l'image dans le fichier.
		ecrireDonneesImage(fichierEcrire, image);
	}
}

/**
* Allocation de pixels pour une image.
*
* \param [in] largeur
*        Le nombre de pixels en largeur de l'image alloués.
* \param [in] hauteur
*        Le nombre de pixels en hauteur de l'image alloués.
*
* \return une image allouée ou vide.
*/
Image
allouerImage
( unsigned largeur, unsigned hauteur )
{	
	// Si la largeur ET la hauteur ne sont pas nulles :
		// TODO: Affecter les dimensions à l'image.
		
		// TODO: Allouer un tableau dynamique de pixels pour l'image.
		//       On veut Image::hauteur de lignes qui ont chacune
		//       Image::largeur de pixels.
	Image image;
	Pixel pixel = { 0, 0, 0 };
	if (largeur != 0 && hauteur != 0)
	{
		image.hauteur = hauteur;
		image.largeur = largeur;
		image.pixels = new Pixel* [hauteur];
		for (int ligne = 0; ligne < hauteur; ligne++)
		{
			image.pixels[ligne] = new Pixel[largeur];
			for (int colonne = 0; colonne < largeur; colonne++)
			{
				image.pixels[ligne][colonne] = pixel;
			}
		}
	}
	return image;
}

/**
* Désallocation de pixels pour une image.
*
* \param [in] image
*        L'image a désalloué.
*
*/
void
desallouerImage
( Image& image )
{
	// Si le tableau dynamique de l'image n'est pas nul :
		// TODO: Désallouer le tableau 2D.
	if (image.largeur != 0 && image.hauteur != 0 && image.pixels != 0)
	{
		for (int ligne = 0; ligne < image.hauteur; ligne++)
			delete[] image.pixels[ligne];
		delete[] image.pixels;
		image.pixels = 0;
	}
}

/**
* Copie les pixels d'une image.
*
* \param [in] image
*        l'image a copier.
*
* \return La copie de l'image.
*/
Image
copierImage
( const Image& image )
{
	// TODO: Allouer une image de la même taille que celle donnée.
	Image copie = allouerImage(image.largeur, image.hauteur);
	// TODO: Copier tous les pixels.
	copie.pixels = image.pixels;
	return copie;
}

/**
* Lit une image a partir d'un fichier Bitmap.
*
* \param [in] nomFichier
*        Le nom du fichier contenant l'image.
* \param [out] ok
*        Fonction booléenne : vrai si l'image a été lue.
*
* \return les données de l'image obtenue.
*/
Image
lireImage
( const string& nomFichier, bool& ok )
{
	// TODO: Ouvrir le fichier en lecture binaire.
	// Si l'ouverture n'a pas échouée :
	// TODO: Lire l'entête DIB.
	// TODO: Allouer une image selon le contenu du DIB.
	// TODO: Lire les pixels du fichier.

	fstream fichier(nomFichier, ios::in | ios::binary);
	EnteteDib enteteDib;
	Image image = { 0, 0, 0 };
	if (!fichier.fail())
	{
		enteteDib = lireEnteteFichier(fichier);
		image = allouerImage(enteteDib.largeurImage, enteteDib.hauteurImage);
		lireDonneesImage(fichier, image);
		ok = true;
	}
	else
		ok = false;
	return image;
}

/**
* Extraire une petite image d'une plus grande image.
*
* \param [in] image
*        Les données de la grande image.
* \param [in] zone
*        Zone rectangulaire (petite image) extraite de l'image.
*
* \return les données de l'image extraite.
*/
Image
extraireRectangle
( const Image& image, const Rectangle& zone )
{
	// Si la zone demandée est valide :
		// TODO: Allouer une image de la taille de la zone à extraire.
		
		// TODO: Copier les pixels de la zone.
	int largeurZone = 0;
	int hauteurZone = 0;
	Image zoneImage;
	if (estZoneValide(image, zone))
	{
		largeurZone = zone.coin2.x - zone.coin1.x;
		hauteurZone = zone.coin2.y - zone.coin1.y;
		zoneImage = allouerImage(largeurZone, hauteurZone);
		for (int i = zone.coin2.y-1; i >= zone.coin1.y; i--)
		{
			for (int j = zone.coin1.x; j < zone.coin2.x; j++)
				zoneImage.pixels[i - zone.coin1.y][j - zone.coin1.x] = image.pixels[i][j];
		}
	}
	return zoneImage;
}

#pragma endregion //}

#pragma endregion //}

