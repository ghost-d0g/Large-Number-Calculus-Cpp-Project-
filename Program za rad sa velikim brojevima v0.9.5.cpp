/* ---------------------------------------------------------------------------------------------- */
/* PROGRAM ZA RAD SA VELIKIM BROJEVIMA KOJI SU DATI PREKO NIZOVA CIFARA                           */
/* AUTOR: Nikola Vukicevic                                                                        */
/* NOVEMBAR 2016.                                                                                 */
/* ---------------------------------------------------------------------------------------------- */

#include <iostream>
#include <cstdio>

using namespace std;

int DONJA_GRANICA = 0, DUZINA_NIZA = 0, MAX_DUZINA_OPERANDA = 5000;


int poredjenje(int a[], int n_a, int b[], int n_b) // return: 0 - prvi je veci; 1 - drugi je veci; 2 - isti su
{
	int i, pom_a[DUZINA_NIZA], pom_b[DUZINA_NIZA];

	for(i=0; i<DUZINA_NIZA; i++) pom_a[i] = pom_b[i] = 0;
	for(i = 0; i < n_a; i++) pom_a[DUZINA_NIZA - n_a + i] = a[DUZINA_NIZA - n_a + i];
	for(i = 0; i < n_b; i++) pom_b[DUZINA_NIZA - n_b + i] = b[DUZINA_NIZA - n_b + i];


	for(i=0; i<DUZINA_NIZA; i++) // Ovde ne trazimo prvu cifru koja se poklapa, gledamo sve (malo bezveze ... donekle ....
	{						// .... ali, prilicno ok u ovoj situaciji
		if(pom_a[i] > pom_b[i])
			return 0;

		if(pom_b[i] > pom_a[i])
			return 1;
	}

	return 2; // Brojevi su isti; ako se do ovde funkcija ne vrati u pozivajucu funkciju,
			  // to znaci da brojevi stvarno jesu isti
}

void sabiranje(int *a, int n_a, int *b, int n_b, int *c, int n_c)
{
	int i, prenos = 0, pom_a[DUZINA_NIZA], pom_b[DUZINA_NIZA], pom_c[DUZINA_NIZA];

	for(i = 0; i < DUZINA_NIZA; i++) pom_a[i] = pom_b[i] = pom_c[i] = 0;
	for(i = 0; i < n_a; i++) pom_a[DUZINA_NIZA - n_a + i] = a[DUZINA_NIZA - n_a + i];
	for(i = 0; i < n_b; i++) pom_b[DUZINA_NIZA - n_b + i] = b[DUZINA_NIZA - n_b + i];

	for(i = DUZINA_NIZA - 1; i >= DONJA_GRANICA; i--)
	{
		pom_c[i] = (pom_a[i] + pom_b[i] + prenos) % 10;
		prenos   = (pom_a[i] + pom_b[i] + prenos) / 10;
	}

	for(i = 0; i < n_c; i++) *(c + DUZINA_NIZA - n_c + i) = pom_c[DUZINA_NIZA - n_c + i];
}

void oduzimanje(int *a, int n_a, int *b, int n_b, int *c, int n_c)
{
	int i, komplement, prenos = 0, pom_a[DUZINA_NIZA], pom_b[DUZINA_NIZA], pom_c[DUZINA_NIZA];

	for(i = 0; i<DUZINA_NIZA; i++) pom_a[i] = pom_b[i] = pom_c[i] = 0;
	for(i = 0; i < n_a; i++) pom_a[DUZINA_NIZA - n_a + i] = a[DUZINA_NIZA - n_a + i];
	for(i = 0; i < n_b; i++) pom_b[DUZINA_NIZA - n_b + i] = b[DUZINA_NIZA - n_b + i];

	for(i = DUZINA_NIZA - 1; i >= DONJA_GRANICA; i--)
	{
		komplement = 10 - pom_b[i];
		pom_c[i]   =   (pom_a[i] + komplement - prenos) % 10;
		prenos     = !((pom_a[i] + komplement - prenos) / 10);
	}

	for(i = 0; i<DUZINA_NIZA; i++) *(c + i) = pom_c[i];
}

int indeksPrveCifre(int *a, int n)
{
	for(int i=0; i<n; i++)
		if(*(a+i) != 0)
			return i;

	return n - 1;
}

void mnozenje(int a[], int n_a, int b[], int n_b, int *c, int n_c)
{
	int i, brojac_b, pocetak_b = 0, pom_a[DUZINA_NIZA], pom_b[DUZINA_NIZA], pom_c[DUZINA_NIZA],
	    pomocni[DUZINA_NIZA];

	for(i = 0; i<DUZINA_NIZA; i++) pom_a[i] = pom_b[i] = pom_c[i] = pomocni[i] = 0;
	for(i = 0; i < n_a; i++) pom_a[DUZINA_NIZA - n_a + i] = a[DUZINA_NIZA - n_a + i];
	for(i = 0; i < n_b; i++) pom_b[DUZINA_NIZA - n_b + i] = b[DUZINA_NIZA - n_b + i];

	while(pom_b[pocetak_b] == 0) pocetak_b++;

	for(brojac_b = pocetak_b; brojac_b < DUZINA_NIZA; brojac_b++)
	{
		for(i = 0; i < DUZINA_NIZA; i++) pomocni[i] = 0;

		for(i = 0; i < pom_b[brojac_b]; i++)
			sabiranje(pom_a, DUZINA_NIZA, pomocni, DUZINA_NIZA, pomocni, DUZINA_NIZA);

		int korekcija = DUZINA_NIZA - brojac_b - 1; // Broj nula za dopisivanje

		for(i = korekcija; i < DUZINA_NIZA; i++) pomocni[i - korekcija] = pomocni[i];
		for(i = DUZINA_NIZA - korekcija; i < DUZINA_NIZA; i++) pomocni[i] = 0;

		sabiranje(pom_c, DUZINA_NIZA, pomocni, DUZINA_NIZA, pom_c, DUZINA_NIZA);
	}

	for(i = 0; i < DUZINA_NIZA; i++) *(c + i) = pom_c[i];
}

int djm(int a[], int n_a, int b[], int n_b)
{
	int i, pom_a[DUZINA_NIZA], pom_b[DUZINA_NIZA], kolicnik = 0;

	for(i = 0; i<DUZINA_NIZA; i++) pom_a[i] = pom_b[i] = 0;
	for(i = 0; i < n_a; i++) pom_a[DUZINA_NIZA - n_a + i] = a[DUZINA_NIZA - n_a + i];
	for(i = 0; i < n_b; i++) pom_b[DUZINA_NIZA - n_b + i] = b[DUZINA_NIZA - n_b + i];

	while(poredjenje(pom_a, DUZINA_NIZA, pom_b, DUZINA_NIZA) != 1)
	{
		oduzimanje(pom_a, DUZINA_NIZA, pom_b, DUZINA_NIZA, pom_a, DUZINA_NIZA);
		kolicnik++;
	}

	return kolicnik;
}

void mnozenje_brzinsko(int *a, int n, int indeks, int *c)
{
	int i, prenos = 0, proizvod;

	for(i = DUZINA_NIZA - 1; i >= 0; --i)
	{
		proizvod = a[i] * n + prenos;
		*(c + i) = proizvod % 10;
		prenos   = proizvod / 10;
	}

	while(prenos)
	{
		*(c + indeks) = prenos % 10;
		prenos /= 10;
		--indeks;
	}
}

void deljenje(int a[], int n_a, int b[], int n_b, int *k, int n_k, int *o, int n_o)
{
	int i, brojac_a = 0, pom_a[DUZINA_NIZA], pom_b[DUZINA_NIZA], pom_k[DUZINA_NIZA], radni[DUZINA_NIZA],
						 umnozak[DUZINA_NIZA], mnozilac[DUZINA_NIZA];

	for(i = 0; i < DUZINA_NIZA; i++) pom_a[i] = pom_b[i] = pom_k[i] = radni[i] = umnozak[i] = mnozilac[i] = 0;
	for(i = 0; i < n_a; i++) pom_a[DUZINA_NIZA - n_a + i] = a[DUZINA_NIZA - n_a + i];
	for(i = 0; i < n_b; i++) pom_b[DUZINA_NIZA - n_b + i] = b[DUZINA_NIZA - n_b + i];

	while(pom_a[brojac_a] == 0) brojac_a++;

	while(brojac_a < DUZINA_NIZA)
	{
		while(poredjenje(radni, DUZINA_NIZA, pom_b, DUZINA_NIZA) == 1)
		{
			if(brojac_a == DUZINA_NIZA) break;

			for(i=1; i<DUZINA_NIZA; i++)
				radni[i-1] = radni[i];

			radni[DUZINA_NIZA - 1] = pom_a[brojac_a];

			for(i=1; i<DUZINA_NIZA; i++)
				pom_k[i-1] = pom_k[i];

			pom_k[DUZINA_NIZA - 1] = 0;

			brojac_a++;
		}

		pom_k[DUZINA_NIZA - 1] = mnozilac[DUZINA_NIZA - 1] = djm(radni, DUZINA_NIZA, pom_b, DUZINA_NIZA);
		mnozenje_brzinsko(pom_b, mnozilac[DUZINA_NIZA - 1], DUZINA_NIZA - indeksPrveCifre(pom_b, DUZINA_NIZA), umnozak);
		//mnozenje(mnozilac, DUZINA_NIZA, pom_b, n_b, umnozak, DUZINA_NIZA);
		oduzimanje(radni, DUZINA_NIZA, umnozak, DUZINA_NIZA, radni, DUZINA_NIZA);
	}

	for(i = 0; i < DUZINA_NIZA; i++) k[i] = pom_k[i];
	for(i = 0; i < DUZINA_NIZA; i++) o[i] = radni[i];
}

int mnozenje_brzinsko(int *a, int n, int indeks)
{
	int i, prenos = 0, proizvod;

	for(i = 0; i < indeks; i++)
	{
		proizvod = a[i] * n + prenos;
		a[i]     = proizvod % 10;
		prenos   = proizvod / 10;
	}

	while(prenos)
	{
		a[indeks] = prenos % 10;
		prenos   /= 10;
		indeks++;
	}

	return indeks;
}

void faktorijel_brzinski(int n)
{
	if(n > 50000)
	{
		printf("\nUneli ste broj koji je veci od 50000, sto program trenutno ne podrzava!");
		return;
	}

	int i, duzina = 250000, pom_c[duzina], indeks = 1;

	pom_c[0] = 1;

	for(i = 1; i < duzina; i++) pom_c[i] = 0;

	for(i = 2; i<= n; i++)
		indeks = mnozenje_brzinsko(pom_c, i, indeks);

	FILE *f = fopen("rezultat.txt", "w");

	fprintf(f, "Uneti broj: %d\n", n);
	fprintf(f, "Broj cifara u rezultatu: %d\n\n", indeks);
	fprintf(f, "Faktorijel(%d) = \n\n", n);

	for(i = indeks - 1; i >= 0; i--)
			fprintf(f, "%d", pom_c[i]);
		fprintf(f, "\n");

	printf("\nRezultat je izracunat i smesten u fajl \"rezultat.txt\".");

	fclose(f);
}

void odredjivanje_duzine_nizova(string ime, string *s1, string *s2)
{
	char znak = '0';
	int i, n1, n2;
	string string1 = "", string2 = "";
	FILE *f = fopen(ime.c_str() , "r");

	while(znak == '0') fscanf(f, "%c", &znak);

    string1 += znak;

    while(znak != '\n')
    {
    	fscanf(f, "%c", &znak);
    	if(znak >= 48 && znak <= 57) string1 += znak;
	}

    n1 = string1.length();

	fscanf(f, "%c", &znak);

	while(znak == '0') fscanf(f, "%c", &znak);

	string2 += znak;

	while(znak != '\n')
    {
    	fscanf(f, "%c", &znak);
    	if(znak >= 48 && znak <= 57) string2 += znak;
	}

    n2 = string2.length();

	DUZINA_NIZA = n1 + n2;

    fclose(f);

    *s1 = string1; *s2 = string2;
}


void ucitavanje(string ime, string s1, int *a, int *n_a, string s2, int *b, int *n_b)
{
	int i;

    *n_a = s1.length();

	for(i = 0; i < *n_a; i++)
    	a[DUZINA_NIZA - *n_a + i] = s1.at(i) - 48;

    printf("\nPrvi broj ucitan korektno.");
    printf("\nBroj cifara prvog broja: %d\n", *n_a);

    *n_b = s2.length();

    for(i = 0; i < *n_b; i++)
    	b[DUZINA_NIZA - *n_b + i] = s2.at(i) - 48;

    printf("\nDrugi broj ucitan korektno.");
    printf("\nBroj cifara drugog broja: %d\n\n\n", *n_b);

}

void pisanje_u_fajl(char znak, string ime, int a[], int n_a, int b[], int n_b, int r1[], int n_r1, int r2[], int n_r2, int najduzi, int n)
{
	FILE *f = fopen(ime.c_str(), "w");
	int i;

	if(znak == '5')
	{
		fprintf(f, "Faktorijel(%d) = \n\n", n);
		i = 0;
		while(!r1[i]) i++;

		for(; i < DUZINA_NIZA; i++)
			fprintf(f, "%d", r1[i]);
		fprintf(f, "\n");
		fclose(f);
		return;
	}

	fprintf(f, " ");
    for(i = 0; i < najduzi - n_a; i++) fprintf(f, " ");
    for(i = 0; i < n_a; i++) fprintf(f, "%d", a[DUZINA_NIZA - n_a + i]);
    fprintf(f, "\n");
    switch(znak)
    {
    	case '1' : fprintf(f, "+"); break;
    	case '2' : fprintf(f, "-"); break;
    	case '3' : fprintf(f, "*"); break;
    	case '4' : fprintf(f, "/"); break;
    	default: break;
	}


    for(i = 0; i < najduzi - n_b; i++) fprintf(f, " ");
    for(i = 0; i < n_b; i++) fprintf(f, "%d", b[DUZINA_NIZA - n_b + i]);
    fprintf(f, "\n");
    for(i = 0; i <= najduzi; i++) fprintf(f, "-");
    fprintf(f, "\n=");
    for(i = 0; i < najduzi - n_r1; i++) fprintf(f, " ");
    for(i = 0; i < n_r1; i++) fprintf(f, "%d", r1[DUZINA_NIZA - n_r1 + i]);
   	fprintf(f, "\n");

	if(znak == '4')
	{
		fprintf(f, "\n");
		fprintf(f, "OSTATAK:\n ");
   		for(i = 0; i < najduzi - n_r2; i++) fprintf(f, " ");
		for(i = 0; i < n_r2; i++) fprintf(f, "%d", r2[DUZINA_NIZA - n_r2 + i]);
   		fprintf(f, "\n");
	}

    fclose(f);
}

int main()
{
    char znak;
	int i, j, k, n, br_cifara1, br_cifara2, br_cifaraR, br_cifaraO, najduzi_broj;
	string broj1_string = "", broj2_string = "";

	odredjivanje_duzine_nizova("operandi.txt", &broj1_string, &broj2_string);

	int	broj1[DUZINA_NIZA], broj2[DUZINA_NIZA], rezultat[DUZINA_NIZA], rezultat2[DUZINA_NIZA];

	printf("////////////////////////////////////////////////////////////\n");
    printf("// OPERACIJE SA VELIKIM BROJEVIMA:                        //\n");
    printf("////////////////////////////////////////////////////////////\n");

    ///////////////////////////////////////////////////////////////////////////////////////
    // Ucitavanje operanada:
    ///////////////////////////////////////////////////////////////////////////////////////

	for(i = 0; i < DUZINA_NIZA; i++) broj1[i] = broj2[i] = rezultat[i] = rezultat2[i] = 0;
    ucitavanje("operandi.txt", broj1_string, broj1, &br_cifara1, broj2_string, broj2, &br_cifara2);
    najduzi_broj = br_cifara1 * (br_cifara1 >= br_cifara2) + br_cifara2 * (br_cifara2 > br_cifara1);
    DONJA_GRANICA = DUZINA_NIZA - br_cifara1 - br_cifara2 - 10;
    if(DONJA_GRANICA < 0) DONJA_GRANICA = 0;

    if (najduzi_broj > MAX_DUZINA_OPERANDA)
    {
    	printf("Iako su operandi ucetani korektno, bar jedan od dva ucitana operanda\nima vise od %d cifara, sto program trenutno ne podrzava!", MAX_DUZINA_OPERANDA);
    	printf("\n\nPrekida se izvrsavanje programa.");
    	return 0;
	}

    ///////////////////////////////////////////////////////////////////////////////////////
    // Izvrsavanje operacija:
    ///////////////////////////////////////////////////////////////////////////////////////

    printf("Izaberite operaciju:\n");
    printf("1. Sabiranje\n2. Oduzimanje\n3. Mnozenje\n4. Deljenje\n5. Faktorijel\n\nIZBOR: ");


    scanf("%c", &znak);

	///////////////////////////////////////////////////////////////////////////////////////
    // Komande za brzo biranje operacija (testiranje brzine programa i sl).
    ///////////////////////////////////////////////////////////////////////////////////////

	//    znak = '1';
	//    znak = '2';
	//    znak = '3';
	//    znak = '4';
	//    znak = '5';

	switch(znak)
	{
		case '1' : sabiranje(broj1, br_cifara1, broj2, br_cifara2, rezultat, DUZINA_NIZA); break;
		case '2' : oduzimanje(broj1, br_cifara1, broj2, br_cifara2, rezultat, DUZINA_NIZA); break;
		case '3' : mnozenje(broj1, br_cifara1, broj2, br_cifara2, rezultat, DUZINA_NIZA); break;
		case '4' : deljenje(broj1, br_cifara1, broj2, br_cifara2, rezultat, DUZINA_NIZA, rezultat2, DUZINA_NIZA); break;
		//case '5' : printf("\nUnesite broj ciji faktorijel zelite da izracunate: "); n = 10000; faktorijel_brzinski(n); return 0;
		case '5' : printf("\nUnesite broj ciji faktorijel zelite da izracunate: "); scanf("%d", &n); faktorijel_brzinski(n); return 0;
		//case '5' : printf("\nUnesite broj ciji faktorijel zelite da izracunate: "); n=30000; faktorijel_brzinski(n); return 0;
		default: printf("Pogresno unet znak za operaciju!\n\nPrekida se izvrsavanje programa."); return 0;
	}

	br_cifaraR = DUZINA_NIZA - indeksPrveCifre(rezultat, DUZINA_NIZA);
	printf("\n\nBroj cifara u rezultatu: %d\n", br_cifaraR);
	najduzi_broj = br_cifaraR * (br_cifaraR >= najduzi_broj) + najduzi_broj * (najduzi_broj > br_cifaraR);

	br_cifaraO = DUZINA_NIZA - indeksPrveCifre(rezultat2, DUZINA_NIZA);
	if(znak == '4') printf("Broj cifara u ostatku: %d\n", br_cifaraO);
	najduzi_broj = br_cifaraO * (br_cifaraO >= najduzi_broj) + najduzi_broj * (najduzi_broj > br_cifaraO);

	////////////////////////////////////////////
	// Pisanje u fajl:
	////////////////////////////////////////////

	pisanje_u_fajl(znak, "rezultat.txt", broj1, br_cifara1, broj2, br_cifara2, rezultat, br_cifaraR, rezultat2, br_cifaraO, najduzi_broj, n);

    printf("\nRezultat je izracunat i smesten u fajl \"rezultat.txt\".");
}

