#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct zoznam{ // zoznam --> nazov struktury
	char meno[50];
	char druh[30];
	int vyska;
	float vaha;
	long long datum;
	long long krmenie;
	char meno_osetrovatela[50];
	struct zoznam* link;
}ZOZNAM;  // TYP (nie»o ako int, float)









function_n(ZOZNAM* p_A) {
	FILE* file;
	file = fopen("zvierata.txt", "r");
	if (file == NULL) {
		printf(" Zaznamy neboli nacitane\n");
		exit(1);
	}
	


	char buff[100];
	int n = 0; //pocet zvieracich zaznamov
	while (fgets(buff, sizeof(buff), file) != NULL) {
		if (strcmp(buff, "$$$\n") == 0) {
			n++;
		}
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
	}
}


function_v(ZOZNAM* p_A) {


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
	ZOZNAM *a = (ZOZNAM*)malloc(2 * sizeof(ZOZNAM));
	while (scanf("%c", &input)) {
		if (input == 'n') {
			function_n(&a);
		}
		if (input == 'v') {
			function_v(&a);
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
}