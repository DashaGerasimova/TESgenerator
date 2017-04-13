#include "stdafx.h"
#define largest 50

void copyFileLine (FILE *,FILE *,int);
int randomFileLineNumber(FILE *);

struct PathAndMessage {
	const char* path;
	const char* message;
};

const PathAndMessage g_traits[] = {
	{ "resources/races.txt", "Раса:" },
	{ "resources/weapon.txt", "Любимое оружие:" },
	{ "resources/personality.txt","Происхождение:" },
	{ "resources/sp.txt", "Семейное положение:" },
	{ "resources/Age.txt", "Возраст:" },
	{ "resources/religion.txt", "Религия:" }
};

enum TraitType {
	TT_RACE,
	TT_WEAPON,
	TT_PERSONALITY,
	TT_MARITALSTATUS,
	TT_AGE,
	TT_RELIGION
};

const PathAndMessage g_classes[] = {
	{ "resources/war.txt", "воин" },
	{ "resources/mage.txt", "маг" },
	{ "resources/thif.txt", "вор" }
};

enum ClassType {
	CT_WARRIOR,
	CT_MAG
};

void processTrait (TraitType tt);

void processPathAndMessage (PathAndMessage* pam) {
	FILE* inputFile = fopen (pam->path, "r");

	if (inputFile == NULL) {
		MessageBox(NULL,L"Невозможно открыть файлы",L"Ошибка",MB_OK);
		return 1;
	}
		
	printf("\n%s", pam->message);
	fputs(pam->message, outputFile);
	copyFileLine(inputFile, outputFile, randomFileLineNumber(inputFile));
	fclose(inputFile);
}



int main() {
	setlocale(LC_CTYPE, ".1251");
	int ran,randc;
	FILE *inputFile = NULL,*outputFile = NULL;
	int itraits=0,iclasses=0; 
	//char *fuck[10];

	printf ("Авторы:Александр Дак, Даша ПеКа\nГенератор для игры TES:\n -------------------");

	// primary initialization	

	srand(time(NULL));

	while (1) {
		if ((outputFile=fopen ("randomfile.txt","wb"))==NULL) {
			MessageBox(NULL,L"Невозможно открыть файлы",L"Ошибка",MB_OK);
		
			return 1;
		}

		
		// races
		processPathAndMessage(g_traits[i++]);
		
		// classes

		printf ("Класс:");
		fputs("Класс:", outputFile);
		randc = rand() % 3;
		
		switch (randc) {
		case 0:
			printf("воин\n");
			fputs("воин\n", outputFile);
			
			processPathAndMessage(g_classes[ii++]);

			break;
		
		case 1:
			printf ("маг\n");
			fputs("маг\n",outputFile);
			
			if ((inputFile=fopen("resources/mage.txt","rb"))==NULL){
				MessageBox(NULL,L"Невозможно открыть файлы",L"Ошибка",MB_OK);
				return 1;
			}
			
			printf ("Роль:");
			fputs("\nРоль:",outputFile);
    		copyFileLine(inputFile, outputFile, randomFileLineNumber(inputFile));
			fclose(inputFile);

			break;

		default:
			printf ("вор\n");
			fputs("вор\n",outputFile);
			
			if ((inputFile=fopen("resources/thif.txt","rb"))==NULL){ // thief
				MessageBox(NULL,L"Невозможно открыть файлы",L"Ошибка",MB_OK);
				return 1;
			}
			
			printf ("Роль:");
			fputs("\nРоль:",outputFile);
    		copyFileLine(inputFile, outputFile, randomFileLineNumber(inputFile));
			fclose(inputFile);
		}		
		
		// weapons

		if ((inputFile=fopen("resources/weapon.txt","rb"))==NULL){
			MessageBox(NULL,L"Невозможно открыть файлы",L"Ошибка",MB_OK);
			return 1;
		}
		ran= randomFileLineNumber(inputFile);
		printf ("Любимое оружие:");
		fputs("Любимое оружие:",outputFile);
		copyFileLine (inputFile,outputFile,ran);
		//работа с оружием
		fclose (inputFile);

		if ((inputFile=fopen("resources/personality.txt","rb"))==NULL){
			MessageBox(NULL,L"Невозможно открыть файлы",L"Ошибка",MB_OK);
			return 1;
		}
		ran= randomFileLineNumber(inputFile);
		printf ("Происхождение:");
		fputs("Происхождение:",outputFile);
		copyFileLine (inputFile,outputFile,ran);
		//работа с происхождением
		fclose (inputFile);

		if ((inputFile=fopen("resources/sp.txt","rb"))==NULL){
			MessageBox(NULL,L"Невозможно открыть файлы",L"Ошибка",MB_OK);
			return 1;
		}
		ran= randomFileLineNumber(inputFile);
		printf ("Семейное положение:");
		fputs("семейное положение:",outputFile);
		copyFileLine (inputFile,outputFile,ran);
		// работа с сп

		if ((inputFile=fopen("resources/Age.txt","rb"))==NULL){
			MessageBox(NULL,L"Невозможно открыть файлы",L"Ошибка",MB_OK);
			return 1;
		}
		ran= randomFileLineNumber(inputFile);
		printf ("Возраст:");
		fputs("Возраст:",outputFile);
		copyFileLine (inputFile,outputFile,ran);
		// работа с возрастом
		fclose (inputFile);

		if ((inputFile=fopen("resources/religion.txt","rb"))==NULL){
			MessageBox(NULL,L"Невозможно открыть файлы",L"Ошибка",MB_OK);
			return 1;
		}
		ran= randomFileLineNumber(inputFile);
		printf ("Религия:");
		fputs("Религия:",outputFile);
		copyFileLine (inputFile,outputFile,ran);
		//Работа с религией

		printf ("--------------------\n");
		printf("Repeat? Yes==1\n");

		int w;
		scanf("%d",&w);
		if (w!=1)
			break;
	}

	fclose (inputFile);
	fclose (outputFile);
	return 0;
}

void copyFileLine (FILE *input, FILE *output, int lineNumber) {
	char buf[largest];
	
	rewind(input);
	
	for (int i=0; i<=lineNumber; ++i) {
		fgets(buf,largest,input);
	}
	
	fputs(buf,output);
	
	// debug info
	puts(buf);
}

//Выбор произвольной строки в файле
int randomFileLineNumber (FILE *f){
	int i=0;
	char buf [largest];
	rewind(f);
	
	while (fgets(buf,largest,f)!=NULL)
		++i;
//	printf ("%d\n",i);
	
	
	return rand() % i;
}