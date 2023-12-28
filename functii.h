#include "structuri.h"
#include <windows.h>
#include <conio.h>

// prototipez functiile pe care le voi folosi.
void afisare_meniu();
void start_joc();
struct carte imparte_carte(int);
void imparte_maini();
void afisare_maini();
void cautare_castigator();
void setare_valori();
void mesaj(const char*, float);

// fac o functie de sortare pt a face debugging mai usor
void sortare();
// functie de debugging/ afisare date
void debug();

/*
* stochez combinatiile de carti, valorile si culorile
* intr-un sir de caractere constant pentru
* ca nu vreau ca acestea sa se schimbe.
*/
const char culori_carti[CULORI][LUNGIME_CHAR] = { "inima neagra", "inima rosie", "romb", "trefla" };
const char valori_carti[VALORI][LUNGIME_CHAR] = { "2 ", "3 ", "4 ", "5 ", "6 ", "7 ", "8 ", "9 ", "10 ", "J ", "Q ", "K ", "A " };
const char combinatii_carti[COMBINATII][LUNGIME_CHAR] = { "carte mare", "pereche", "doua perechi", "trei de un fel", "chinta", "culoare", "full house", "careu", "chinta de culoare", "chinta roiala" };

// declar variabile globale ca sa nu ma complic cu pointeri
int nr_jucatori;
struct pachet_de_carti pachet_de_carti;
// sa zicem ca la masa de poker sunt doar 6 scaune
struct jucator nume[NR_MAX_JUCATORI];
/*
* creez variabila care o sa stocheze cartile
* puse pe masa de catre dealer
*/
struct carte carti_pe_masa[NR_CARTI_MASA];
int carte_pe_masa = 0;

void afisare_meniu()
{
	// am folost un site ca sa generez titlul jocului sub forma ASCII
	printf("\033[0;31m");
	mesaj("    _____  _____ __ ___  _____  _____ \n", 0.75);
	mesaj("   /  _  \\/  _  \\|  |  //   __\\/  _  \\\n", 0.75);
	mesaj("   \\   __/|  |  ||  _ < |   __||  _  <\n", 0.75);
	mesaj("    |__|  \\_____/|__|__\\\\_____/\\__|\\_/\n", 0.75);
	mesaj("     _____ ___ ___   __ __  _____  _____ ___ ___   _____  _____  ____  _____  _____  _____  _____  __ __ \n", 0.5);
	mesaj("    /  _  \\\\  |  /  /  |  \\/  _  \\/  _  \\\\  |  /  /  _  \\/  _  \\/    \\/  _  \\/  _  \\/  ___>/     \\/  |  \\\n", 0.5);
	mesaj("    |  _  < |   |   |  _  ||  _  ||  _  < |   |   |   __/|  _  |\\-  -/|  _  <|  _  ||___  ||  |--||  |  |\n", 0.5);
	mesaj("    \\_____/ \\___/   \\__|__/\\__|__/\\__|\\_/ \\___/   \\__/   \\__|__/ |__| \\__|\\_/\\__|__/<_____/\\_____/\\_____/\n", 0.5);
	printf("\n");
	printf("\033[0m");
}

void start_joc()
{
	int optiune;
	srand(time(NULL));
	afisare_meniu();
	mesaj("introduceti numarul jucatorilor de la masa(MINIM 2 JUCATORI, MAXIM 6 JUCATORI):", 15);
	scanf("%d", &nr_jucatori);
	Beep(600, 300);
	getchar();
	while (nr_jucatori < 2 || nr_jucatori > NR_MAX_JUCATORI)
	{
		mesaj("numarul introdus este invalid! introduceti un alt numar:", 15);
		scanf("%d", &nr_jucatori);
		Beep(600, 300);
		getchar();
	}
	mesaj("0.iesire din joc.\n", 15);
	mesaj("1.incepe runda.\n", 15);
	mesaj("2.incepe un nou joc.\n", 15);
	mesaj("selectati o optiune:", 15);
	scanf("%d", &optiune);
	Beep(600, 300);
	getchar();
	// bucla repetitiva pentru joc
	while (1)
	{
		system("cls");
		afisare_meniu();
		switch (optiune)
		{
		case 0:
			exit(0);
			break;
		case 1:
			mesaj("dealerul imparte cartile...\n", 15);
			Sleep(2500);
			cautare_castigator();
			break;
		case 2:
			mesaj("introduceti numarul jucatorilor de la masa(MINIM 2 JUCATORI, MAXIM 6 JUCATORI):", 25);
			Beep(600, 300);
			scanf("%d", &nr_jucatori);
			getchar();
			while (nr_jucatori < 2 || nr_jucatori > NR_MAX_JUCATORI)
			{
				mesaj("numarul introdus este invalid! introduceti un alt numar:", 15);
				scanf("%d", &nr_jucatori);
				getchar();
			}
			mesaj("0.iesire din joc.\n", 15);
			mesaj("1.incepe runda.\n", 15);
			mesaj("2.incepe un nou joc.\n", 15);
			mesaj("selectati o optiune:", 15);
			scanf("%d", &optiune);
			Beep(600, 300);
			getchar();
			system("cls");
			afisare_meniu();
			cautare_castigator();
			break;
		default:
			mesaj("optiunea selectata nu este valida!\n", 15);
			break;
		}
		mesaj("0.iesire din joc.\n", 15);
		mesaj("1.incepe runda.\n", 15);
		mesaj("2.incepe un nou joc.\n", 15);
		mesaj("selectati o optiune:", 15);
		scanf("%d", &optiune);
		Beep(600, 300);
	}
}

struct carte imparte_carte(int optiune)
{
	int contor, impartita;
	struct carte carte;
	while (1)
	{
		carte.culoare = rand() % CULORI;
		carte.valoare = rand() % VALORI;
		impartita = 1;
		if (optiune == 1)
		{
			// verific daca cartea a fost impartita deja la jucator
			for (contor = 0; contor < pachet_de_carti.carti_impartite && impartita == 1; contor++)
			{
				if (pachet_de_carti.carti_de_impartit[contor].culoare == carte.culoare &&
					pachet_de_carti.carti_de_impartit[contor].valoare == carte.valoare)
					impartita = 0;
			}
			/*
			* daca cartea nu a fost impartita cresc contorul
			* de carti impartite si o pun in pachetul cu carti
			* impartite, apoi o returnez ca valoare.
			*/
			if (impartita == 1)
			{
				pachet_de_carti.carti_de_impartit[pachet_de_carti.carti_impartite] = carte;
				pachet_de_carti.carti_impartite++;
				return carte;
			}
		}
		else if (optiune == 2)
		{
			/*
			 * verific daca cartea a fost impartita deja pe masa
			 * si daca cartea de pe masa a fost impartita la unul
			 * dintre jucatori.
			*/
			for (contor = 0; contor < pachet_de_carti.carti_impartite && impartita == 1; contor++)
			{
				if (pachet_de_carti.carti_de_impartit[contor].culoare == carte.culoare &&
					pachet_de_carti.carti_de_impartit[contor].valoare == carte.valoare)
					impartita = 0;
			}
			/*
			* daca cartea nu a fost impartita cresc contorul
			* de carti impartite si o pun in pachetul cu carti
			* impartite, apoi o returnez ca valoare.
			*/
			if (impartita == 1)
			{
				pachet_de_carti.carti_de_impartit[pachet_de_carti.carti_impartite] = carte;
				carti_pe_masa[carte_pe_masa] = carte;
				carte_pe_masa++;
				pachet_de_carti.carti_impartite++;
				return carte;
			}
		}
	}
}

void imparte_maini()
{
	int carte, jucator, optiune;
	/*
	* -iterez prin fiecare jucator si impart cartile
	* -variabila optiune o folosesc pentru functia
	* imparte carte, pentru optiune == 1 o sa
	* impart cartea la jucator, pentru optiunea 2
	* o sa impart cartea pe masa.
	*/
	optiune = 1;
	for (jucator = 0; jucator < nr_jucatori; jucator++)
		for (carte = 0; carte < 2; carte++)
			nume[jucator].mana.carti[carte] = imparte_carte(optiune);
	optiune = 2;
	for (carte = 0; carte < NR_CARTI_MASA; carte++)
		carti_pe_masa[carte] = imparte_carte(optiune);
}

void afisare_maini()
{
	int jucator, carte;
	int index_valoare, index_culoare;
	// afisez cartile jucatorilor
	for (jucator = 0; jucator < nr_jucatori; jucator++)
	{
		printf("jucatorul %d are ", jucator + 1);
		for (carte = 0; carte < 2; carte++)
		{
			index_culoare = nume[jucator].mana.carti[carte].culoare;
			index_valoare = nume[jucator].mana.carti[carte].valoare;
			if (carte == 0)
				printf("%s%s, ", valori_carti[index_valoare], culori_carti[index_culoare]);
			else
				printf("%s%s", valori_carti[index_valoare], culori_carti[index_culoare]);
		}
		printf("\n");
	}
	// afisez cartile puse de catre dealer pe masa
	printf("dealarul a impartit cartile:\n");
	for (carte = 0; carte < NR_CARTI_MASA; carte++)
	{
		index_culoare = carti_pe_masa[carte].culoare;
		index_valoare = carti_pe_masa[carte].valoare;
		if (carte < NR_CARTI_MASA - 1)
			printf("%s%s, ", valori_carti[index_valoare], culori_carti[index_culoare]);
		else
			printf("%s%s\n", valori_carti[index_valoare], culori_carti[index_culoare]);
	}
	/*
	* debugging pentru cand imi afisa carti cu aceeasi valoare si aceeasi culoare --> rezolvat
	printf("\n");
	int contor;
	for (contor = 0; contor < pachet_de_carti.carti_impartite; contor++)
	{
		printf("%s de %s\n", valori_carti[pachet_de_carti.carti_de_impartit[contor].valoare], culori_carti[pachet_de_carti.carti_de_impartit[contor].culoare]);
	}
	printf("\n");
	*/
}

void cautare_castigator()
{
	setare_valori();
	imparte_maini();
	sortare();
	afisare_maini();
	int jucator, valori_masa, valoare;
	/*
	* initializez vectorii de frecventa pentru
	* valori respectiv culori, acestia ma vor
	* ajuta sa gasesc foarte usor diferite
	* tipuri de combinatii.
	*/
	for (jucator = 0; jucator < nr_jucatori; jucator++)
	{
		nume[jucator].culori[nume[jucator].mana.carti[0].culoare]++;
		nume[jucator].valori[nume[jucator].mana.carti[0].valoare]++;
		nume[jucator].culori[nume[jucator].mana.carti[1].culoare]++;
		nume[jucator].valori[nume[jucator].mana.carti[1].valoare]++;
		for (valori_masa = 0; valori_masa < NR_CARTI_MASA; valori_masa++)
		{
			nume[jucator].culori[carti_pe_masa[valori_masa].culoare]++;
			nume[jucator].valori[carti_pe_masa[valori_masa].valoare]++;
		}
	}

	// verific daca exista o pereche, doua perechi, trei de un fel si patru de un fel
	for (jucator = 0; jucator < nr_jucatori; jucator++)
	{
		for (valoare = 0; valoare < VALORI; valoare++)
		{
			// o pereche sau doua perechi
			if (nume[jucator].valori[valoare] == 2)
			{
				if (nume[jucator].rang_maximal < 2)
				{
					nume[jucator].rang_combinatie[1]++;
					nume[jucator].rang_maximal = 1;
				}
				if (nume[jucator].rang_combinatie[1] >= 2 && nume[jucator].rang_maximal < 2)
				{
					nume[jucator].rang_combinatie[2] = 1;
					nume[jucator].rang_maximal = 2;
				}
			}
			// trei de un fel
			if (nume[jucator].valori[valoare] == 3 && nume[jucator].rang_maximal < 3)
			{
				nume[jucator].rang_combinatie[3] = 1;
				nume[jucator].rang_maximal = 3;
			}
			// patru de un fel
			if (nume[jucator].valori[valoare] == 4)
			{
				nume[jucator].rang_combinatie[7] = 1;
				nume[jucator].rang_maximal = 7;
			}
		}
	}

	// verific daca exista chinta
	int consecutiv;
	for (jucator = 0; jucator < nr_jucatori; jucator++)
	{
		consecutiv = 0;
		for (valoare = 0; valoare < VALORI && consecutiv != 5; valoare++)
		{
			if (nume[jucator].valori[valoare] != 0)
				consecutiv++;
			else
				consecutiv = 0;
		}
		if (consecutiv == 5)
		{
			nume[jucator].rang_combinatie[4] = 1;
			nume[jucator].rang_maximal = 4;
		}
	}

	// verific daca exista culoare
	int culoare;
	for (jucator = 0; jucator < nr_jucatori; jucator++)
		for (culoare = 0; culoare < CULORI; culoare++)
			if (nume[jucator].culori[culoare] == 5)
			{
				// printf("CULORI JUCATOR{%d}: %d ", jucator, nume[jucator].culori[culoare]);
				nume[jucator].rang_combinatie[5] = 1;
				nume[jucator].rang_maximal = 5;
				nume[jucator].culoare_chinta = culoare;
			}

	// verific daca exista full house
	for (jucator = 0; jucator < nr_jucatori; jucator++)
		if (nume[jucator].rang_combinatie[1] >= 1 && nume[jucator].rang_combinatie[3] == 1)
		{
			nume[jucator].rang_combinatie[6] = 1;
			nume[jucator].rang_maximal = 6;
		}

	// verific daca exista chinta de culoare
	for (jucator = 0; jucator < nr_jucatori; jucator++)
		if (nume[jucator].rang_combinatie[5] == 1)
		{
			// -daca rangul al combinatiei a 5-a este diferit de 0 atunci exista culoare
			// -mai trebuie sa verific daca cartile care formeaza culoarea sunt si crescatoare
			consecutiv = 0;
			for (valoare = 0; valoare < VALORI && consecutiv != 5; valoare++)
			{
				if (nume[jucator].valori[valoare] != 0)
				{
					if (carti_pe_masa[consecutiv].culoare == nume[jucator].culoare_chinta && carti_pe_masa[consecutiv].valoare == valoare)
						consecutiv++;
					else if (nume[jucator].mana.carti[0].valoare == valoare && nume[jucator].mana.carti[0].culoare == culoare)
						consecutiv++;
					else if (nume[jucator].mana.carti[1].valoare == valoare && nume[jucator].mana.carti[1].culoare == culoare)
						consecutiv++;
				}
				else
					consecutiv = 0;
			}
			if (consecutiv == 5)
			{
				nume[jucator].rang_combinatie[8] = 1;
				nume[jucator].rang_maximal = 8;
			}
		}

	// verific daca exista chinta roiala
	for (jucator = 0; jucator < nr_jucatori; jucator++)
	{
		consecutiv = 0;
		if (nume[jucator].rang_combinatie[8] == 1)
		{
			/*
			* -practic chinta roiala este o chinta de culoare
			* dar cu cele mai mari carti 10, J, R, K si A.
			* -verific doar ultimele 5 valori.
			*/
			for (valoare = VALORI - 1; valoare >= 8; valoare--)
			{
				if (nume[jucator].valori[valoare] >= 1)
					consecutiv++;
			}
			if (consecutiv == 5)
			{
				nume[jucator].rang_combinatie[9] = 1;
				nume[jucator].rang_maximal = 9;
			}
		}
	}

	// gasesc castigatorul
	int castigator = 1, aux = 0;
	for (jucator = 0; jucator < nr_jucatori; jucator++)
	{
		if (nume[jucator].rang_maximal > aux)
		{
			castigator = jucator + 1;
			aux = nume[jucator].rang_maximal;
		}
		else if (nume[jucator].rang_maximal == aux)
		{
			// aici verific pentru jucatorii care au rangurile la fel
			// printf("activat\n");
			if (nume[jucator].mana.carti[1].valoare > nume[jucator - 1].mana.carti[1].valoare)
				castigator = jucator + 1;
			else if (nume[jucator].mana.carti[1].valoare < nume[jucator - 1].mana.carti[1].valoare)
				castigator = jucator;
			else
			{
				if (nume[jucator].mana.carti[0].valoare > nume[jucator - 1].mana.carti[0].valoare)
					castigator = jucator + 1;
				else if (nume[jucator].mana.carti[0].valoare < nume[jucator - 1].mana.carti[0].valoare)
					castigator = jucator;
				else
					castigator = -1;
			}
		}
	}

	// debugging
	// debug()
	mesaj("\n\n~~~~~", 15);
	if (castigator == -1)
		mesaj("Ceva nu e ok ba...", 25);
	else
		printf("Jucatorul %d a castigat avand %s!!!", castigator, combinatii_carti[nume[castigator - 1].rang_maximal]);
	mesaj("~~~~~\n\n\n", 15);
}

void setare_valori()
{
	int jucator, combinatie, culori, valori, carte;
	// am initializat toti vectorii 0
	pachet_de_carti.carti_impartite = 0;
	carte_pe_masa = 0;
	for (carte = 0; carte < NR_CARTI; carte++)
	{
		pachet_de_carti.carti_de_impartit[carte].culoare = 0;
		pachet_de_carti.carti_de_impartit[carte].valoare = 0;
	}
	for (carte = 0; carte < NR_CARTI_MASA; carte++)
	{
		carti_pe_masa[carte].culoare = 0;
		carti_pe_masa[carte].valoare = 0;
	}
	// initializez vectorii de combinatii si variabilele de rang maximal la fiecare jucator
	for (jucator = 0; jucator < nr_jucatori; jucator++)
		for (combinatie = 0; combinatie < COMBINATII; combinatie++)
			nume[jucator].rang_combinatie[combinatie] = 0;
	for (jucator = 0; jucator < nr_jucatori; jucator++)
	{
		// toti jucatorii o sa aiba combinatia de carte mare(cea mai slaba)
		nume[jucator].rang_combinatie[0] = 1;
		nume[jucator].rang_maximal = 0;
		for (culori = 0; culori < CULORI; culori++)
		{
			nume[jucator].culori[culori] = 0;
			nume[jucator].culoare_chinta = -1;
		}
		for (valori = 0; valori < VALORI; valori++)
			nume[jucator].valori[valori] = 0;
	}
}

void sortare()
{
	// aceasta functie face mai usoara vizualizarea cartilor si ajuta la gasirea chintei roiale
	int i, j, jucator;
	struct carte aux;
	for (jucator = 0; jucator < nr_jucatori; jucator++)
	{
		// sortez cartile de pe masa
		for (i = 0; i < NR_CARTI_MASA; i++)
		{
			for (j = i + 1; j < NR_CARTI_MASA; j++)
			{
				if (carti_pe_masa[i].valoare > carti_pe_masa[j].valoare)
				{
					aux = carti_pe_masa[j];
					carti_pe_masa[j] = carti_pe_masa[i];
					carti_pe_masa[i] = aux;

				}
			}
		}
		// sortez cartile jucatorului
		for (i = 0; i < 2; i++)
		{
			for (j = i + 1; j < 2; j++)
			{
				if (nume[jucator].mana.carti[i].valoare > nume[jucator].mana.carti[j].valoare)
				{
					aux = nume[jucator].mana.carti[j];
					nume[jucator].mana.carti[j] = nume[jucator].mana.carti[i];
					nume[jucator].mana.carti[i] = aux;
				}
			}
		}
	}
}

void debug()
{
	// functie de debugging
	int jucator, culoare, valoare;
	for (jucator = 0; jucator < nr_jucatori; jucator++)
	{
		printf("jucatorul %d \n", jucator + 1);
		printf("inima neagra | inima rosie | romb | trefla\n");
		for (culoare = 0; culoare < CULORI; culoare++)
			printf("%d ", nume[jucator].culori[culoare]);
		printf("\n");
		printf("2 3 4 5 6 7 8 9  10 J R K A\n");
		for (valoare = 0; valoare < VALORI; valoare++)
			printf("%d ", nume[jucator].valori[valoare]);
		printf("\n");
	}
}

void mesaj(const char* sir, float timp)
{
	if (sir == NULL)
		return;
	while (*sir)
	{
		printf("%c", *sir++);
		Sleep(timp);
	}
	Sleep(timp + 50);
}
