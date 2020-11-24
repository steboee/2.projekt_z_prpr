#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996) // strcmpi() mi hádzalo warning

typedef struct zoznam { // zoznam --> nazov struktury
	char meno[50];
	char druh[30];
	int vyska;
	float vaha;
	long long datum;
	long long krmenie;
	char meno_osetrovatela[50];
	struct zoznam* dalsi;
}ZOZNAM;  // TYP (nieČo ako int, float)


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

	
}


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

	printf("pozicia: %d\n", poc);
	

	return t ;
}


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
		if (input == 'z') {
			zvierata = function_z(zvierata);
		}
		if (input == 'h') {
			function_h(zvierata);
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
