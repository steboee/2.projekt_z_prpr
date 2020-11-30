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
	if (t != NULL) {
		printf("Bolo Alokovane!\n");
		return t;
	}
	FILE* file;
	file = fopen("zvierata.txt", "r");
	if (file == NULL) {
		printf(" Zaznamy neboli nacitane\n");
		exit(1);
	}
	fseek(file, 0, SEEK_SET);
	char buff[100];
	int n = 0;
	
	while (fgets(buff, sizeof(buff), file) != NULL) {
		if (strcmp(buff, "$$$\n") == 0) {
			n++;
		}
	}
	ZOZNAM* p = NULL, *p_new = NULL;
	fseek(file, 0, SEEK_SET);
	for (int i = 0; i < n; i++) {
		
		p_new = (ZOZNAM*)malloc(sizeof(ZOZNAM));
		
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
		if (t == NULL) {
			p_new->dalsi = NULL;
			t = p_new;
		}
		else {
			p = t;
			while (p->dalsi != NULL) {
				p = p->dalsi;
 			}
			p_new->dalsi = p->dalsi;
			p->dalsi = p_new;

		}
	}
	printf("Nacitalo sa %d zaznamov\n", n);
	puts("");
	fclose(file);
	return t;

	
}		//VYTV


// VYPIS DANÝCH ZOZNAMOV
function_v(ZOZNAM* t) {
	ZOZNAM* p = NULL;
	p = t;
	while (p != NULL) {
		printf("Meno: %s\n", p->meno);
		printf("Druh: %s\n", p->druh);
		printf("Vyska: %d\n", p->vyska);
		printf("Vaha: %g\n", p->vaha);
		printf("Datum: %lld\n", p->datum);
		printf("Krmenie: %lld\n", p->krmenie);
		printf("Meno osetrovatela: %s\n", p->meno_osetrovatela);
		puts("");
		p = p->dalsi;
	}
}


// PRIDANIE UDAJU V ZOZNAME NA DANÉ MIESTO
ZOZNAM* function_p(ZOZNAM* t) {
	int c1;
	printf("Pozicia noveho zaznamu : ");
	scanf("%d", &c1);
	getchar();
	ZOZNAM* p_new;
	p_new = (ZOZNAM*)malloc(sizeof(ZOZNAM));


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
	p = t;
	int pozicie = 1, ano = 0;
	while (p->dalsi!=NULL) {
		if (c1 == 1) {
			temp = p;
			p = p_new;
			p_new->dalsi = temp;
			p = p_new;
			return p;
			
		}
		if (pozicie == c1 && c1 != 1) {
			temp = pred->dalsi;
			pred->dalsi = p_new;
			p_new->dalsi = temp;
			return t;
		}
		pozicie++;
		pred = p;
		p = p->dalsi;

	}
	p_new->dalsi = NULL;
	p->dalsi = p_new;
	return t;
	
	printf("pozicie : %d\n", pozicie);

}


// ZMAZANIE ZÁZNAMU PODĽA MENA
ZOZNAM *function_z(ZOZNAM* t) {
	printf("Nacitaj meno zvierata: ");
	char meno_z[51];
	ZOZNAM* p=NULL,*p_pred =NULL;
	p = t;
	
	fgets(meno_z, sizeof(meno_z), stdin);
	meno_z[strlen(meno_z) - 1] = '\0';

	int poc = 1;
	int a;
	while (a = strcmpi(p->meno, meno_z) != 0) {
	
		p_pred = p;
		p = p->dalsi;
		poc++;
		if (p == NULL) {						// Ak presiel vsetkymi menami a ani jedno sa nerovnalo
			printf("MENO NIEJE V ZOZNAME!\n");
				return t;
		}
	}

	if (t == p) {
		t = t->dalsi;
		free(p);
	}
	else {
		p_pred->dalsi = p->dalsi;
		free(p);
	}

	printf("Zviera s menom %s bolo vymazane\n",meno_z);
	

	return t ;
}


// VYPIS ZÁZNAMOV DO URČITÉHO DÁTUMU KRMENIA
function_h(ZOZNAM* t) {
	long long datumkrmenia;
	printf("Nacitaj datum krmenia : ");
	scanf("%lld", &datumkrmenia);
	getchar();
	
	ZOZNAM* p = NULL;
	p = t;
	int poradie=1;
	while (p != NULL) {
		if (datumkrmenia>= p->krmenie) {
			printf("%d.\n", poradie);
			printf("Meno: %s\n", p->meno);
			printf("Druh: %s\n", p->druh);
			printf("Vyska: %d\n", p->vyska);
			printf("Vaha: %g\n", p->vaha);
			printf("Datum: %lld\n", p->datum);
			printf("Krmenie: %lld\n", p->krmenie);
			printf("Meno osetrovatela: %s\n", p->meno_osetrovatela);
			puts("");
			
		}
		p = p->dalsi;
		poradie++;
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
	scanf("%lld", &input_krmenie);
	getchar();

	p = t;

	while (strcmp(meno_zvierata, p->meno) != 0) {   //pokial nepridem na dané meno zvierata v zozname
		p = p->dalsi;		
		if (p == NULL) {						
			printf("MENO NIEJE V ZOZNAME!\n");
			
			return t;
		}
	}
	p->krmenie = input_krmenie;   // zmena udaju na p->kremnie na hodnotu v input_krmenie
	printf("Zviera s menom %s bolo naposledy nakrmene dna %lld\n", meno_zvierata, input_krmenie);
	return t;
}



int main() {
	char input=NULL;
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
			printf("koniec\n");
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
