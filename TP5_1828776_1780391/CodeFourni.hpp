////////////////////////////////////////////////////////////////////////////////
/// \file    CodeFourni.hpp
/// \author  Charles Hosson
/// \version Dernière entrée : 2015/11/06
/// \since   Création : 2015/10/11
///
/// Le code fourni aux élèves est constitué des structures d'enregistrement
/// et de fonctions utilitaires faisant le traitement d'image.
////////////////////////////////////////////////////////////////////////////////

#pragma once


#pragma region "Inclusions" //{

#include <ciso646>
#include <cstddef>
#include <cstdint>


using namespace std;

#pragma endregion //}




#pragma region "Déclarations" //{

#pragma region "Macros" //{

#if defined(__GNUC__) || defined(__clang__)
	#define PACKED_STRUCT(declaration) \
	declaration  __attribute__((__packed__))
#elif defined(_MSC_VER)
	#define PACKED_STRUCT(declaration) \
	__pragma(pack(push, foo, 1)) declaration __pragma(pack(pop, foo))
#else
	#error Compiler not supported.
#endif

#pragma endregion //}


#pragma region "Constantes" //{

static const unsigned ALIGNEMENT_PIXELS = 4;

static const unsigned BMP_ID = 0x4D42; // "BM"
static const unsigned COMPRESSION_BI_RGB = 0; // Pas de compression
static const unsigned RESOLUTION_IMPRESSION = 2835; // 72 DPI

#pragma endregion //}


#pragma region "Structures d'enregistrement" //{

/**
 * \struct Point
 * \brief  Un point en 2D
 * 
 * Un point avec des coordonnées en X et Y, en pixels.
 */
struct Point
{
	unsigned x;
	unsigned y;
};


/**
 * \struct Rectangle
 * \brief  Un rectangle.
 * 
 * Un rectangle est représenté par deux points, dont chacun possède des
 * coordonnées en X et en Y. Le premier point est le coin bas-gauche et l'autre
 * est le coin haut-droit.
 */
struct Rectangle
{
	Point coin1;
	Point coin2;
};


/**
 * \struct Pixel
 * \brief  Enregistrement qui représente un pixel RGB24.
 * 
 * Un pixel RGB24 possède les trois couleurs rouge, vert et bleu, dont
 * l'ordre dans la mémoire est BGR. Chaque couleur est représentée par un
 * entier non-signé à 8 bits.
 */
struct Pixel
{
	uint8_t b;
	uint8_t g;
	uint8_t r;
};


/**
 * \struct Image
 * \brief  Enregistrement représentant une image.
 * 
 * Une image possède à la base une largeur, une hauteur et une séquence de
 * pixels.
 * <p>
 * Il est important de noter que les pixels sont organisés en un tableau de
 * lignes. La première dimension représente le numéro de ligne et la deuxième
 * dimension représente le numéro de colonne. Les coordonnées des pixels sont
 * donc en (Y,X), <b>PAS EN (X,Y)</b>.
 */
struct Image
{
	unsigned largeur;
	unsigned hauteur;
	Pixel**  pixels;
};


/**
 * \struct EnteteBmp
 * \brief  Entête BMP d'un bitmap.
 * 
 * L'entête BMP d'une image bitmap vient en premier dans le fichier et le
 * format est toujours le même. Elle contient de l'information générale sur
 * le fichier d'image.
 */
PACKED_STRUCT(
struct EnteteBmp
{
	uint16_t id;
	uint32_t tailleFichier;
	uint16_t inutilise[2];
	uint32_t positionTableau;
});


/**
 * \struct EnteteDib
 * \brief  Entête DIB d'un bitmap.
 * 
 * L'entête DIB d'une image bitmap vient après l'entête BMP dans le fichier
 * et il existe beaucoup de formats différents. Elle contient de
 * l'information détaillée sur l'image et définit le format de pixel.
 * <p>
 * Dans ce TD, nous utilisons le format BITMAPINFOHEADER avec des pixels
 * RGB24.
 */
PACKED_STRUCT(
struct EnteteDib
{
	uint32_t tailleEntete;
	int32_t  largeurImage;
	int32_t  hauteurImage;
	uint16_t nbPlansCouleur;
	uint16_t bpp;
	uint32_t compression;
	uint32_t tailleTableau;
	int32_t  resolutionImpression[2];
	uint32_t nbPalettes;
	uint32_t nbCouleursImportantes;
});

#pragma endregion //}


#pragma region "Globaux" //{

void convertirNoirEtBlanc ( Image& );

bool estRectangleValide ( const Rectangle& );

bool estZoneValide ( const Image&, const Rectangle& );

EnteteBmp construireBmpVide ( );

EnteteDib construireDibVide ( );

unsigned calculerTaillePadding ( const Image& );

unsigned calculerTailleTableau ( const Image& );

EnteteBmp construireEnteteBmp ( const Image& );

EnteteDib construireEnteteDib ( const Image& );

void tracerLigneHorizontale ( Image&, Pixel, const Point[2], unsigned );

void tracerLigneVerticale ( Image&, Pixel, const Point[2], unsigned );

void dessinerCarre ( Image&, Pixel, const Point&, unsigned );

void tracerContourRectangle ( Image&, Pixel, const Rectangle&, unsigned );

#pragma endregion //}

#pragma endregion //}

