#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



function_n() {
	FILE* file;
	file = fopen("zvierata.txt", "r");
	
	typedef struct zoznam {
		char meno[50];
		char druh[30];
		char vyska[30];
		char vaha[30];
		char datum[20];
		char krmenie[20];
		char meno_osetrovatela[50];
		struct zoznam *link;
	}ZOZNAM;


	char buff[100];
	int n = 0; //pocet zvieracich zaznamov
	while (fgets(buff, sizeof(buff), file) != NULL) {
		if (strcmp(buff, "$$$\n") == 0) {
			n++;
		}
		
	}
	


	ZOZNAM *p_A = (ZOZNAM*)malloc(n * sizeof(ZOZNAM));
	//ZOZNAM A = (ZOZNAM*)malloc(n * sizeof(ZOZNAM));
	
	
	if (p_A == NULL) {
		printf("ERROR IN ALLOCATING MEMORY FOR A\n");
	}
	else {
		printf("MEMORY FOR A SUCCESFULLY ALLOCATED\n");
	}

	fseek(file, 0, SEEK_SET);
	for (int i = 0; i < n; i++) {
		fgets(buff, sizeof(buff), file);
		

		fgets(buff, sizeof(buff), file);
		strcpy(p_A[i].meno, buff);

		fgets(buff, sizeof(buff), file);
		strcpy(p_A[i].druh, buff);

		fgets(buff, sizeof(buff), file);
		strcpy(p_A[i].vyska, buff);

		fgets(buff, sizeof(buff), file);
		strcpy(p_A[i].vaha, buff);

		fgets(buff, sizeof(buff), file);
		strcpy(p_A[i].datum, buff);

		fgets(buff, sizeof(buff), file);
		strcpy(p_A[i].krmenie, buff);

		fgets(buff, sizeof(buff), file);
		strcpy(p_A[i].meno_osetrovatela, buff);

	}
	
	printf("%s", p_A[0].meno);
	
}


function_v() {

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
	while (scanf("%c", &input)) {
		if (input == 'n') {
			function_n();
		}
		if (input == 'v') {
			function_v();
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