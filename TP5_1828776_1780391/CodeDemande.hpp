////////////////////////////////////////////////////////////////////////////////
/// \file    CodeDemande.hpp
/// \author  Tamer Arar et Benjamin Heinen
/// \version Dernière entrée : 2016/06/07
/// \since   Création : 2016/06/01
///
/// Prototypes des implementations du code demandé permettant l'extraction d'images.
////////////////////////////////////////////////////////////////////////////////

#pragma once


#pragma region "Inclusions" //{

#include <ciso646>
#include <cstddef>
#include <cstdint>

#include <fstream>
#include <string>

#include "CodeFourni.hpp"


using namespace std;

#pragma endregion //}




#pragma region "Déclarations" //{

#pragma region "Globaux" //{

EnteteDib lireEnteteFichier ( fstream& );

void lireDonneesImage ( fstream&, Image& );

void ecrireDonneesImage ( fstream&, const Image& );

void ecrireImage ( const string&, const Image&, bool& );

Image allouerImage ( unsigned, unsigned );

void desallouerImage ( Image& );

Image copierImage ( const Image& );

Image lireImage ( const string&, bool& );

Image extraireRectangle ( const Image&, const Rectangle& );

#pragma endregion //}

#pragma endregion //}

