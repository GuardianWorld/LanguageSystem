/*
MIT License

Copyright (c) 2019 Emanuel Ruella

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
© 2019 GitHub, Inc.
*/

#include "LanguageSystem.h"

int ChatInicialization(LanguageModule *mainLM)
{
	printf("System: Loading Language Files and setting language, this could take a while.\n");
	strcpy(languageFiles[0], "Language/EN-US.txt");
	strcpy(languageFiles[1], "Language/PT-BR.txt");
	FILE *mainLanguage;
	FILE *secondaryLanguage;
	int fileOpened = 0;
	int x;
	for (x = 0; x < 100; x++)
	{
		mainLM->aiAmmountText[x] = 0;
	}

	//Initialize the Head;
	memoryChatHeadAllocation(mainLM, -1, "Initializing", 0,-1);
	mainLanguage = fopen(languageFiles[0], "r");
	if (mainLanguage == NULL)
	{
		printf("System: Could not find/open %s language file\n", languageFiles[0]);
	}
	else
	{
		fileOpened++;
		languageFileOpener(mainLM, &fileOpened, mainLanguage);
	}

	fclose(mainLanguage);
	secondaryLanguage = fopen(languageFiles[1], "r");
	if (secondaryLanguage == NULL)
	{
		printf("System: Could not find/open %s language file\n", languageFiles[1]);
	}
	else
	{
		fileOpened++;
		languageFileOpener(mainLM, &fileOpened, secondaryLanguage);
	}

	if (fileOpened == 2)
	{
		return 0;
	}
	else if (fileOpened == 1)
	{
		return 1;
	}
	else
	{
		printf("CRITICAL ERROR, please check your installation, or your files.\n");
		return -1;
	}
	fclose(secondaryLanguage);

}

void languageFileOpener(LanguageModule *mainLM, int *filesOpen, FILE *uLFile)
{
	int aux, x, z;
	char line[80];
	char auxline[80];

	//Sets the temporary variables for the chat;
	int user = -1, action = NORMAL, size = 0;
	char info[80];

	while (fgets(line, sizeof line, uLFile) != NULL)
	{
		for (aux = 0; aux < sizeof line; aux++)
		{
			if (auxline[aux] == '\0')
			{
				break;
			}
			info[aux] = '\0';
			auxline[aux] = '\0';
		}
		x = 0;
		//printf("%s\n", line);
		for (aux = 0; aux < sizeof line; aux++)
		{
			auxline[x] = line[aux];
			if (line[aux] == '\0' || line[aux] == '\n' || line[aux] == '/' || line[aux] == '\r')
			{
				break;
			}
			else if (strcmp(auxline, "[SOA]") == 0 || strcmp(auxline, "[EOA]") == 0)
			{
				break;
			}
			else if (strcmp(auxline, "User: ") == 0)
			{
				z = 0;
				aux++;
				size = checkString(aux, line, &info[0]);
				user = atoi(info);
			}
			else if (strcmp(auxline, "Action: ") == 0)
			{
				z = 0;
				aux++;

				size = checkString(aux, line, &info[0]);
				action = atoi(info);
			}
			else if (strcmp(auxline, "I: ") == 0)
			{
				aux++;
				size = checkString(aux, line, &info[0]);
				if (user == 1)
				{
					mainLM->aiAmmountText[action]++;
				}
				memoryChatHeadAllocation(mainLM, user, &info[0], size, action);
			}
			x++;
		}

	}
	*filesOpen++;
}

int checkString(int aux, char line[80], char *info)
{
	int z = 0;
	int size = 0;
	while (1)
	{
		if (line[aux + z] == '\n' || line[aux + z] == '\0' || line[aux + z] == '\r')
		{
			return size;
		}
		else
		{
			size += 1;
			info[z] = line[aux + z];
			//printf("==%c==\n", line[aux + z]);
		}
		z++;
	}
}

void memoryChatHeadAllocation(LanguageModule *mainLM, int user, char* word, int size, int action)
{
	LanguageCP aux;

	if (user == -1)
	{
		mainLM->MainUserBranch = (LanguageCP)malloc(sizeof(LanguageCell));
		mainLM->MainUserBranch->word = (char*)malloc(sizeof(int));
		mainLM->MainUserBranch->nextWord = NULL;
		mainLM->user_lmw = mainLM->MainUserBranch; //Sets the last Main Word allocated;
		mainLM->MainAIBranch = (LanguageCP)malloc(sizeof(LanguageCell));
		mainLM->MainAIBranch->word = (char*)malloc(sizeof(int));
		mainLM->MainUserBranch->nextWord = NULL;
		mainLM->ai_lmw = mainLM->MainAIBranch; //Sets the last Main Word allocated;
		//mainLM->MainLanguageFileOrigin[0] = "EN-US";
	}
	else if (user == 0)
	{
		aux = mainLM->user_lmw;
		aux->nextWord = (LanguageCP)malloc(sizeof(LanguageCell));
		aux = aux->nextWord;
		aux->word = (char*)malloc(size);
		strcpy(aux->word, word);
		aux->action = action;
		aux->nextWord = NULL;
		mainLM->user_lmw = aux;
		//printf("%s\n", aux->word);
	}
	else if (user == 1)
	{
		aux = mainLM->ai_lmw;
		aux->nextWord = (LanguageCP)malloc(sizeof(LanguageCell));
		aux = aux->nextWord;
		aux->word = (char*)malloc(size);
		aux->action = action;
		strcpy(aux->word, word);
		aux->nextWord = NULL;
		mainLM->ai_lmw = aux;
		//printf("%s\n", word);*/
	}
}

int UserInput(char *OTalk, LanguageModule *lm)
{
	LanguageCP aux;
	aux = lm->MainUserBranch;
	while (1)
	{
		//printf("\t=%s=\n", aux->word);
		if (aux->nextWord == NULL)
		{
			break;
		}
		aux = aux->nextWord;
		if (strcmp(OTalk, "forcedbye") == 0)
		{
			return GOODBYE;
		}
		if (strcmp(OTalk, aux->word) == 0)
		{
			return aux->action;
		}
	}
	return INVALIDACT;
}
