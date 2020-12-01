#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996) // strcmpi() mi hádzalo warning

typedef struct zoznam { // zoznam --> nazov struktury
	char meno[50];
	char druh[30];
	int vyska;
	double vaha;
	long long datum;
	long long krmenie;
	char meno_osetrovatela[50];
	struct zoznam* dalsi;
}ZOZNAM;  // TYP (nieČo ako int, float)

// VYTVORENIE ZOZNAMOV
ZOZNAM* function_n(ZOZNAM* t) {
	
	if (t != NULL) { // AK UŽ EXISTOVAL SPÁJANÝ ZOZNAM
		printf("Zoznam uz bol alokovany!\n");
		while (t != NULL) {
			ZOZNAM* temp;
			temp = t;
			t = t->dalsi;
			free(temp);
		}
		printf("Prebehla dealokacia!\n\n");
	}
	
	
	FILE* file;
	file = fopen("zvierata.txt", "r");
	
	
	if (file == NULL) {// AK SA NEPODARIL OTVORIŤ SUBOR
		printf(" Zaznamy neboli nacitane\n");
		exit(1);
	}


	fseek(file, 0, SEEK_SET);
	char buff[100];
	int n = 0;				// pocet zaznamov zvierat
	
	while (fgets(buff, sizeof(buff), file) != NULL) {//pokiaľ tam nieje prázdny riadok
		if (strcmp(buff, "$$$\n") == 0) {	// ak narazíme na $$$ tak ide novy zaznam , čiže pripocitam 1 k aktualnemu poctu zaznamov (n)
			n++;
		}
	}

	ZOZNAM* p = NULL, *p_new = NULL;		//pomocne premenné
	fseek(file, 0, SEEK_SET);
	
	for (int i = 0; i < n; i++) {				// precházdam n-krát ( n = počet záznamov)
		
		p_new = (ZOZNAM*)malloc(sizeof(ZOZNAM));	// vytvorím si zoznam a nižšie doňho vkladám hodnoty
		
		fgets(buff, sizeof(buff), file);
		fgets(buff, sizeof(buff), file);
		buff[strlen(buff) - 1] = '\0';
		strcpy(p_new->meno, buff);

		fgets(buff, sizeof(buff), file);
		buff[strlen(buff) - 1] = '\0';
		strcpy(p_new->druh, buff);

		fgets(buff, sizeof(buff), file);
		buff[strlen(buff) - 1] = '\0';
		p_new->vyska = atoi(buff);

		fgets(buff, sizeof(buff), file);
		buff[strlen(buff) - 1] = '\0';
		p_new->vaha = atof(buff);
		

		fgets(buff, sizeof(buff), file);
		buff[strlen(buff) - 1] = '\0';
		p_new->datum = atoll(buff);

		fgets(buff, sizeof(buff), file);
		buff[strlen(buff) - 1] = '\0';
		p_new->krmenie = atoll(buff);

		fgets(buff, sizeof(buff), file);
		buff[strlen(buff) - 1] = '\0';
		strcpy(p_new->meno_osetrovatela, buff);
		
		if (t == NULL) {			//Ak moj zoznam je prázdny
			p_new->dalsi = NULL; // nastav dalsi na NULL
			t = p_new;		
		}
		else {		//Ak nieje prázdny 
			p = t;						// p bude t
			while (p->dalsi != NULL) {	// pokiaľ nieje p.dalsi NULL tak sa posuvaj v zozname dalej a dalej az kym prides na koniec
				p = p->dalsi;
 			}
			p_new->dalsi = NULL;  //p_new->dalsi nastav na NULL , čiže to bude posledný záznam
			p->dalsi = p_new;		// p mi teraz ukazuje na koniec záznamu a nanho napojim dalsi zoznam p_new
				
		}
	}
	printf("Nacitalo sa %d zaznamov\n", n);
	puts("");
	fclose(file);
	return t;

	
}		


// VYPIS DANÝCH ZOZNAMOV
function_v(ZOZNAM* t) {
	ZOZNAM* p = NULL;
	p = t;
	int i = 1;
	while (p != NULL) {
		printf("%d.\n", i);
		printf("Meno: %s\n", p->meno);
		printf("Druh: %s\n", p->druh);
		printf("Vyska: %d\n", p->vyska);
		printf("Vaha: %g\n", p->vaha);
		printf("Datum: %lld\n", p->datum);
		printf("Krmenie: %lld\n", p->krmenie);
		printf("Meno osetrovatela: %s\n", p->meno_osetrovatela);
		puts("");
		p = p->dalsi;
		i++;
	}
	return;
}


// PRIDANIE UDAJU V ZOZNAME NA DANÉ MIESTO
ZOZNAM* function_p(ZOZNAM* t) {
	int c1;										//pozicia noveho zaznamu
	printf("Pozicia noveho zaznamu : ");
	scanf("%d", &c1);		
	getchar();
	ZOZNAM* p_new;								//vytvorim si pomocnú premennú typu ZOZNAM
	p_new = (ZOZNAM*)malloc(sizeof(ZOZNAM));	

	//VKLADAM DO p_new hodnoty
	printf("Meno: ");
	fgets(p_new->meno, sizeof(p_new->meno), stdin);
	p_new->meno[strlen(p_new->meno) - 1] = '\0';
	
	printf("Druh: ");
	fgets(p_new->druh, sizeof(p_new->druh), stdin);
	p_new->druh[strlen(p_new->druh) - 1] = '\0';
	
	printf("Vyska: ");
	scanf("%d", &p_new->vyska);
	
	printf("Vaha: ");
	scanf("%lf", &p_new->vaha);
	
	printf("Datum: ");
	scanf("%lld", &p_new->datum);
	
	printf("Datum Krmenia: ");
	scanf("%lld", &p_new->krmenie);
	
	printf("Meno osetrovatela: ");
	getchar();
	fgets(p_new->meno_osetrovatela, sizeof(p_new->meno_osetrovatela), stdin);
	p_new->meno_osetrovatela[strlen(p_new->meno_osetrovatela)- 1] = '\0';

	

	ZOZNAM* p;

	ZOZNAM* temp=NULL ,* pred=NULL;
	p = t; // p bude moj zoznam ktorý už bol vytovrený v n
	int pozicie = 1, ano = 0;
	
	while (p!=NULL) {			// prechádzaj spájaným zoznamom až dokým niesi na konci
		if (c1 == 1) {					// ak c1=1 , čiže chcem vložiž nový zoznam na 1 pozíciu
			temp = p;					// uložím si celý zoznam do temp
			p_new->dalsi = temp;		// za p_new napojim moj zoznam
			p = p_new;					// a naspäť do p si uložím p_new ( ktorý začína s záznamom ktorý som pridal a za nim su napojene ostatne zaznamy
			return p;
			
		}
		if (pozicie == c1 && c1 != 1) {		// Ak chcem niekde do stredu zoznamu uložiť nový záznam
			temp = pred->dalsi;				// temp bude pred->dalsi
			pred->dalsi = p_new;
			p_new->dalsi = temp;
			return t;
		}
		pozicie++;							// pozicia v zozname sa mi navýši .
		pred = p;							// pred uchová záznam ktorý je pred p
		p = p->dalsi;						// posuniem sa na dalsi záznam

	}
	p_new->dalsi = NULL;			// Ak bolo c1 > ako pocet záznamov tak program dôojde až sem, p_new->dalsi nastavý na NULL,lebo ten záznam bude posledný
	pred->dalsi = p_new;			// Aktuálne p = NULL, pred->dalsi mi ukazuje na p, čiže pred->dalsi mi bude ukazovat na nový záznam. takže som to napojil 
	return t;

}


// ZMAZANIE ZÁZNAMU PODĽA MENA
ZOZNAM *function_z(ZOZNAM* t) {
	printf("Nacitaj meno zvierata: ");
	char meno_z[51];	
	ZOZNAM* p=NULL,*p_pred =NULL;
	p = t;
	
	fgets(meno_z, sizeof(meno_z), stdin);			// načíta meno zvierata na odstranenie
	meno_z[strlen(meno_z) - 1] = '\0';

	
	
	while (strcmpi(p->meno, meno_z) != 0) {			// pokiaľ sa nerovná 
	
		p_pred = p;				// p_pred ukazuje na záznam pred p
		p = p->dalsi;			// posun sa v zozname o 1 dalej 
		
		if (p == NULL) {						// Ak presiel vsetkymi menami a ani jedno sa nerovnalo
			printf("MENO NIEJE V ZOZNAME!\n");
				return t;
		}
	}

	if (t == p) {   // Odstraňujem prvý záznam
		t = t->dalsi;	// posuň sa o 1 záznam dopredu 
		free(p);		// vymaž prvý záznam
	}
	else {			//Odstaňujem iný než prvý
		p_pred->dalsi = p->dalsi;	//p_pred->dalsi mi ukazuje na na p->dalsi čiže jeden prvok vynechal 
		free(p); // uvolním to celé 
	}

	printf("Zviera s menom %s bolo vymazane\n",meno_z);
	

	return t ;
}


// VYPIS ZÁZNAMOV DO URČITÉHO DÁTUMU KRMENIA
function_h(ZOZNAM* t) {
	if (t == NULL) {
		printf("Nemas nacitany subor zvierata.txt\n");
		return;
	}
	long long datumkrmenia;
	printf("Nacitaj datum krmenia : ");
	scanf("%lld", &datumkrmenia);
	getchar();
	
	
	ZOZNAM* p = NULL;
	p = t;
	int nenakrmene=0;		// premenná pre zistenie či nejaký zviera nebolo nakrmene
	int poradie=1;			// premenná na očíslovanie
	while (p != NULL) {
		if (datumkrmenia>= p->krmenie) { // Ak zadany datum je ostro väčší ako datum zvierata tak zviera nebolo nakrmene...
			printf("%d.\n", poradie);
			printf("Meno: %s\n", p->meno);
			printf("Druh: %s\n", p->druh);
			printf("Vyska: %d\n", p->vyska);
			printf("Vaha: %g\n", p->vaha);
			printf("Datum: %lld\n", p->datum);
			printf("Krmenie: %lld\n", p->krmenie);
			printf("Meno osetrovatela: %s\n", p->meno_osetrovatela);
			puts("");
			nenakrmene++;	// inkrementujem pocet zvierat ktore neobli nakrmnene
		}
		p = p->dalsi; // posun sa v zozname o 1
		poradie++;//premenná na očíslovanie
	}
	if (nenakrmene == 0) {// Ak všetky zvierata boli nakrmene
		printf("Vsetky zvierata boli k datumu %lld nakrmene\n", datumkrmenia);
	}
}


// ZMENA ÚDAJU KRMENIA
ZOZNAM* function_a(ZOZNAM* t) {
	char meno_zvierata[51];
	long long input_krmenie;
	
	ZOZNAM* p;
	printf("Meno: ");
	fgets(meno_zvierata, sizeof(meno_zvierata), stdin);
	meno_zvierata[strlen(meno_zvierata) - 1] = '\0';

	printf("Novy datum krmenia: ");
	scanf("%lld", &input_krmenie); // novy datum krmenia
	getchar();

	p = t;

	while (strcmp(meno_zvierata, p->meno) != 0) {   //pokial nepridem na dané meno zvierata v zozname
		p = p->dalsi;		//posun sa o 1 v zozname
		if (p == NULL) {					// ak už prešiel celým zoznamom tak také meno sa nenchadzalo v zozname		
			printf("MENO NIEJE V ZOZNAME!\n");
			return t;
		}
	}

	p->krmenie = input_krmenie;   // zmena udaju na p->kremnie na hodnotu v input_krmenie
	printf("Zviera s menom %s bolo naposledy nakrmene dna %lld\n", meno_zvierata, input_krmenie);
	return t;
}



int main() {
	char input;
	ZOZNAM* zvierata = NULL;
	printf("n - prikaz na nacitanie zaznamov zo suboru\n");
	printf("v - prikaz na vypis celeho spajaneho zoznamu\n");
	printf("p - prikaz na pridanie do spajaneho zoznamu\n");
	printf("z - prikaz na zmazanie zaznamov podla mena zvierata\n");
	printf("h - prikaz na vyhladanie a vypis poloziek podla datumu krmenia\n");
	printf("a - prikaz na zmenu datumu krmenia\n");
	printf("k - priaz na ukončenie programu\n");
	while (scanf("%c",&input)) {
		puts("");
		getchar();
		
	
		if (input == 'n') {
			zvierata = function_n(zvierata);
		}
		if (input == 'v') {
			function_v(zvierata);
		}
		if (input == 'p') {
			zvierata = function_p(zvierata);
		}
		if (input == 'z') {
			zvierata = function_z(zvierata);
		}
		if (input == 'h') {
			function_h(zvierata);
		}
		if (input == 'a') {
			zvierata = function_a(zvierata);
		}
		if (input == 'k') {
			while (zvierata != NULL){
				ZOZNAM* temp;
				temp = zvierata;
				zvierata = zvierata->dalsi;
				free(temp);
			}
			exit(1);
					
			
		}
	}
}
