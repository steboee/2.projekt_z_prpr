#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

typedef struct zoznam{ // zoznam --> nazov struktury
	char meno[50];
	char druh[30];
	int vyska;
	float vaha;
	long long datum;
	long long krmenie;
	char meno_osetrovatela[50];
	struct zoznam* dalsi;
}ZOZNAM;  // TYP (nie»o ako int, float)



void uvolni(ZOZNAM* p_zaciatok)
{
	ZOZNAM* p_akt = p_zaciatok;
	while (p_zaciatok != NULL)
	{
		p_akt = p_zaciatok;
		p_zaciatok = p_zaciatok->dalsi;
		
	}
}

function_n(ZOZNAM **p_zac) {
	FILE* file;
	file = fopen("zvierata.txt", "r");
	if (file == NULL) {
		printf(" Zaznamy neboli nacitane\n");
		exit(1);
	}
	
	

	char buff[100];
	int pocet_zaznamov = 0; //pocet zvieracich zaznamov
	while (fgets(buff, sizeof(buff), file) != NULL) {
		if (strcmp(buff, "$$$\n") == 0) {
			pocet_zaznamov++;
		}
	}
	ZOZNAM* p_A = NULL;
	if (*p_zac == NULL) {
		printf("NEBOL VYTVORENY\n");
		p_A = (ZOZNAM*)malloc(pocet_zaznamov * sizeof(ZOZNAM));
	}
	else {
		uvolni(p_zac);
		return;
	}
	
	

	if (p_A == NULL) {
		printf("ERROR IN ALLOCATING MEMORY FOR A\n");
	}
	else {
		printf("MEMORY FOR A SUCCESFULLY ALLOCATED\n");
	}

	fseek(file, 0, SEEK_SET);
	for (int i = 0; i < 2; i++) {
		fgets(buff, sizeof(buff), file);
		

		fgets(buff, sizeof(buff), file);
		buff[strlen(buff) - 1] = '\0';
		strcpy(p_A[i].meno, buff);

		fgets(buff, sizeof(buff), file);
		buff[strlen(buff)-1] = '\0';
		strcpy(p_A[i].druh, buff);

		fgets(buff, sizeof(buff), file);
		buff[strlen(buff) - 1] = '\0';
		p_A[i].vyska = atoi(buff);

		fgets(buff, sizeof(buff), file);
		buff[strlen(buff) - 1] = '\0';
		p_A[i].vaha = atof(buff);

		fgets(buff, sizeof(buff), file);
		buff[strlen(buff) - 1] = '\0';
		p_A[i].datum = atoll(buff);
	
		fgets(buff, sizeof(buff), file);
		buff[strlen(buff) - 1] = '\0';
		p_A[i].krmenie = atoll(buff);

		fgets(buff, sizeof(buff), file);
		buff[strlen(buff) - 1] = '\0';
		strcpy(p_A[i].meno_osetrovatela, buff);
		
		p_A[i].dalsi = (*p_zac);
		(*p_zac) = p_A;
	}
	printf("Nacitalo sa <%d> zaznamov", pocet_zaznamov);
	for (int i = 0; i < 2; i++) {
		puts("");
		printf("Meno : %s\n", p_A[i].meno);
		printf("Druh : %s\n", p_A[i].druh);
		printf("Vyska : %d\n", p_A[i].vyska);
		printf("Vaha : %g\n", p_A[i].vaha);
		printf("datum : %lld\n", p_A[i].datum);
		printf("krmenie : %lld\n", p_A[i].krmenie);
		printf("osetrovatel : %s\n", p_A[i].meno_osetrovatela);
	}
	fclose(file);
}


function_v(ZOZNAM *p_A) {

	if (p_A == NULL) {
		return;
	}
	for (int i = 0; i < 2; i++) {
		puts("");
		printf("Meno : %s\n", p_A[i].meno);
		printf("Druh : %s\n", p_A[i].druh);
		printf("Vyska : %d\n", p_A[i].vyska);
		printf("Vaha : %g\n", p_A[i].vaha);
		printf("datum : %lld\n", p_A[i].datum);
		printf("krmenie : %lld\n", p_A[i].krmenie);
		printf("osetrovatel : %s\n", p_A[i].meno_osetrovatela);
	}
}

function_p() {

}

function_z() {

}

function_h() {

}

function_a() {

}


int main() {
	char input;
	ZOZNAM *zvierata = NULL;
	
	while (scanf("%c", &input)) {
		if (input == 'n') {
			function_n(&zvierata);
		}
		if (input == 'v') {
			function_v(zvierata);
		}
		if (input == 'p') {
			function_p();
		}
		if (input == 'z') {
			function_h();
		}
		if (input == 'h') {
			function_h();
		}
		if (input == 'a') {
			function_a();
		}
		if (input == 'k') {
			exit(1);
		}
	}
}*/
typedef struct zoznam { // zoznam --> nazov struktury
	char meno[50];
	char druh[30];
	int vyska;
	float vaha;
	long long datum;
	long long krmenie;
	char meno_osetrovatela[50];
	struct zoznam* dalsi;
}ZOZNAM;  // TYP (nie»o ako int, float)



void function_n(ZOZNAM**a,int *pocet) {
	FILE* file;
	file = fopen("zvierata.txt", "r");
	if (file == NULL) {
		printf(" Zaznamy neboli nacitane\n");
		exit(1);
	}
	fseek(file, 0, SEEK_SET);
	char buff[100];
	int n = 0;
	pocet = 0;
		while (fgets(buff, sizeof(buff), file) != NULL) {
			if (strcmp(buff, "$$$\n") == 0) {
				pocet++;
				n++;
			}
		}
	
	
	

	
	ZOZNAM*my = malloc(n*sizeof(ZOZNAM));

	fseek(file, 0, SEEK_SET);
	for (int i = 0; i < n; i++) {
		fgets(buff, sizeof(buff), file);


		fgets(buff, sizeof(buff), file);
		buff[strlen(buff) - 1] = '\0';
		strcpy(my[i].meno, buff);

		fgets(buff, sizeof(buff), file);
		buff[strlen(buff) - 1] = '\0';
		strcpy(my[i].druh, buff);

		fgets(buff, sizeof(buff), file);
		buff[strlen(buff) - 1] = '\0';
		my[i].vyska = atoi(buff);

		fgets(buff, sizeof(buff), file);
		buff[strlen(buff) - 1] = '\0';
		my[i].vaha = atof(buff);

		fgets(buff, sizeof(buff), file);
		buff[strlen(buff) - 1] = '\0';
		my[i].datum = atoll(buff);

		fgets(buff, sizeof(buff), file);
		buff[strlen(buff) - 1] = '\0';
		my[i].krmenie = atoll(buff);

		fgets(buff, sizeof(buff), file);
		buff[strlen(buff) - 1] = '\0';
		strcpy(my[i].meno_osetrovatela, buff);

		my[i].dalsi = (*a);
		(*a) = my;
	}
	
	return;
}

void function_v(ZOZNAM*a,int pocet) {
	for (int i = 0; i < pocet; i++) {
		puts("");
		printf("Meno : %s\n", a[i].meno);
		printf("Druh : %s\n", a[i].druh);
		printf("Vyska : %d\n", a[i].vyska);
		printf("Vaha : %g\n", a[i].vaha);
		printf("datum : %lld\n", a[i].datum);
		printf("krmenie : %lld\n", a[i].krmenie);
		printf("osetrovatel : %s\n", a[i].meno_osetrovatela);
	}
}

void function_h(ZOZNAM* a,int pocet) {
	printf("Nacitaj datum krmenia: ");
	long long datumkrmenia;
	scanf("%lld", &datumkrmenia);
	for (int i = 0; i < pocet; i++) {
		if (datumkrmenia == a[i].krmenie) {
			printf("Meno : %s\n", a[i].meno);
			printf("Druh : %s\n", a[i].druh);
			printf("Vyska : %d\n", a[i].vyska);
			printf("Vaha : %g\n", a[i].vaha);
			printf("datum : %lld\n", a[i].datum);
			printf("krmenie : %lld\n", a[i].krmenie);
			printf("osetrovatel : %s\n", a[i].meno_osetrovatela);
		}
	}
}
int main()
{
	char input;
	ZOZNAM *zvierata = NULL;
	int pocet = 0;

	while (scanf("%c", &input)) {
		printf("%d",pocet);
		if (input == 'n') {
			function_n(&zvierata,&pocet);
		}
		if (input == 'v') {
			function_v(zvierata,pocet);
		}
		if (input == 'h') {
			function_h(zvierata,pocet);
		}
		if (input == 'k') {
			printf("KONIEC!\n");
			exit(1);
			
		}
	}
}