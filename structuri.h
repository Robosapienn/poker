#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constante.h"

// cartile de joc au doua componente, valoarea si culoarea.
struct carte
{
	int culoare;
	int valoare;
};

// in texas hold 'em fiecare jucator are doua carti in mana.
struct mana_jucator
{
	struct carte carti[2];
};

/*
* -in texas hold 'em exista 10 combinatii, de la
* cea mai mare carte la chinta roiala(cea mai buna
* combinatie).
* -fiecare jucator o sa aiba doua carti in mana
* si rangul combinatiei pe care o va face ulterior.
* -in final o sa compar rangul combinatiilor fiecarui
* jucator si o sa decid cine a castigat.
*/
struct jucator
{
	struct mana_jucator mana;
	int valori[VALORI];
	int culori[CULORI];
	int culoare_chinta;
	int rang_combinatie[COMBINATII];
	int rang_maximal;
};

/*
*-am creat pachetul de carti din care o sa
*se imparta cartile catre jucatori si pe masa
*de joc.
*-stochez numarul de carti impartite
*in variabila de tip intreg carti_impartite.
*/
struct pachet_de_carti
{
	struct carte carti_de_impartit[NR_CARTI];
	int carti_impartite;
};
