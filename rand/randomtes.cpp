#include "stdafx.h"

// макросы обычно прописываются большими буквами, это тоже типичный coding convention
#define MAX_LINE_LENGTH 100

struct PathAndMessage {
	const char* path;
	const char* message;
};

const PathAndMessage g_traits[] = {
	{ "resources/races.txt", "Раса" },
	{ "resources/weapon.txt", "Любимое оружие" },
	{ "resources/personality.txt","Происхождение" },
	{ "resources/sp.txt", "Семейное положение" },
	{ "resources/Age.txt", "Возраст" },
	{ "resources/religion.txt", "Религия" },
	{ "resources/characters.txt", "Характер"}
};

enum TraitType {
	TT_RACE, 
	TT_WEAPON,
	TT_PERSONALITY,
	TT_MARITALSTATUS,
	TT_AGE,
	TT_RELIGION,
	TT_CHARACTER,
	
	TT_COUNT
};

const PathAndMessage g_classes[] = {
	{ "resources/war.txt", "Класс: воин\nРоль" },
	{ "resources/mage.txt", "Класс: маг\nРоль" },
	{ "resources/thif.txt", "Класс: вор\nРоль" }
};

enum ClassType {
	CT_WARRIOR,
	CT_MAGE,
	CT_THIEF,

	CT_COUNT
};

void processPathAndMessage (const PathAndMessage* pam, FILE* outputFile);


int main() {
	setlocale(LC_CTYPE, ".1251");
	FILE* outputFile = NULL;

	// primary initialization
	
	{
		srand(time(NULL));
	}

	if ((outputFile = fopen("randomfile.txt","w")) == NULL) {
		MessageBox(NULL, L"Невозможно открыть файлы", L"Ошибка", MB_OK);
		
		return 1;
	}
	
	while (1) {
		// classes

		printf ("Авторы:Александр Дак, Даша ПеКа\nГенератор для игры TES:\n -------------------\n");

		{
			ClassType ct = ClassType(((unsigned int)rand()) % CT_COUNT);

			processPathAndMessage(&g_classes[ct], outputFile);
		}
		
		// traits
		{
			for (int i = 0; i < TT_COUNT; ++i) { 
				processPathAndMessage(&g_traits[i], outputFile); 
			}
		}

		//repeat
		printf ("--------------------\n");
		printf("Repeat? (y/n)\n");
		
		int c = 0;
		
		do {
			c = getchar();
		} while (c != 'y' && c != 'n');
		
		if (c == 'n') {
			break;
		} else {
			fprintf (outputFile,"\n\n");
		}
		system("cls");
	}

	fclose (outputFile);
	return 0;
}

// ---------------------------------------------------------------------------------------------------- //

//Выбор произвольной строки в файле
void randomFileLine (FILE *f, OUT char* lineBuffer) {
	unsigned int randomLineNumber = 0;
 
	rewind(f);
	
	while (fgets(lineBuffer, MAX_LINE_LENGTH, f) !=NULL) {
		++randomLineNumber;
	}

	randomLineNumber = (unsigned int)rand() % randomLineNumber;

	rewind(f);
	
	for (int i = 0; i <= randomLineNumber; ++i) {
		fgets(lineBuffer, MAX_LINE_LENGTH, f);
	}

	int lastSymbolIndex = strlen(lineBuffer) - 1;
	
	if (lineBuffer[lastSymbolIndex] == '\n') {
			
		lineBuffer[lastSymbolIndex] = '\0';
	}
}

// ---------------------------------------------------------------------------------------------------- //

void processPathAndMessage (const PathAndMessage* pam, FILE* outputFile) {
	FILE* inputFile = fopen (pam->path, "r");

	if (inputFile == NULL) {
		MessageBox(NULL, L"Невозможно открыть файлы", L"Ошибка", MB_OK);
		
		return;
	}

	char lineBuffer[MAX_LINE_LENGTH + 1] = {0};
	randomFileLine(inputFile, lineBuffer);
	fclose(inputFile); 

	FILE* outputFiles[2] = { outputFile, stdout };
	
	for (int i = 0; i < 2; ++i) {
		
		fprintf(outputFiles[i], "%s: %s\n", pam->message, lineBuffer);
	}
}