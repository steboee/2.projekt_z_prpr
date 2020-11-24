#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	while (p->dalsi != NULL) {
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

ZOZNAM* function_z(ZOZNAM* t) {

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
		if (input == 'z') {
			zvierata = function_z(zvierata);
		}
	}
}
