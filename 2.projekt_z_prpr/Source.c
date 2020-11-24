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
	scanf("%d", &c1);
	
	char meno[50];
	char druh[30];
	int vyska;
	double vaha;
	long long datum;
	long long krmenie;
	char meno_osetrovatela[50];

	printf("Meno: ");
	getchar();
	fgets(meno, sizeof(meno), stdin);
	printf("Druh: ");
	getchar();
	fgets(druh, sizeof(druh), stdin);
	printf("Vyska: ");
	scanf("%d", &vyska);
	printf("Vaha: ");
	scanf("%g", &vaha);
	printf("Datum: ");
	scanf("%lld", &datum);
	printf("Datum Krmenia: ");
	scanf("%lld", &krmenie);
	printf("Meno osetrovatela: ");
	getchar();
	fgets(meno_osetrovatela, sizeof(meno_osetrovatela), stdin);

	
	ZOZNAM* p;
	p = t;
	int pozicie = 0;
	while (p!=NULL) {
		p = p->dalsi;
		pozicie++;
		if (pozicie == c1) {

		}
	}
	printf("pozicie : %d\n", pozicie);
	
	if (c1 >= pozicie+1) { // PRIDAM NA KONIEC ZOZNAMU
		

	}





	return t;
}


// ZMAZANIE ZÁZNAMU PODĽA MENA
ZOZNAM *function_z(ZOZNAM* t) {
	printf("Nacitaj meno zvierata: ");
	char meno_z[51];
	ZOZNAM* p=NULL,*p_pred =NULL;
	p = t;
	getchar();
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
	getchar();
	fgets(meno_zvierata, sizeof(meno_zvierata), stdin);
	meno_zvierata[strlen(meno_zvierata) - 1] = '\0';

	printf("Novy datum krmenia: ");
	scanf("%lld", &input_krmenie);
	

	p = t;

	while (strcmp(meno_zvierata, p->meno) != 0) {   //pokial nepridem na dané meno zvierata v zozname
		p = p->dalsi;								//postupujem na dalsi zoznam
	}
	p->krmenie = input_krmenie;   // zmena udaju na p->kremnie na hodnotu v input_krmenie
	printf("Zviera s menom %s bolo naposledy nakrmene dna %lld\n", meno_zvierata, input_krmenie);

	return t;
}



int main() {
	char input;
	ZOZNAM* zvierata = NULL;

	while (scanf("%c", &input)) {
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
