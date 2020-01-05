#include "LanguageSystem.h"

int languageIncialization(LanguageModule *mainLM, FILE *mainLanguage)
{
	memoryLanguageHeadAllocation(mainLM, -1, "Initializing", 0, -1);

	int x;
	for (x = 0; x < 100; x++)
	{
		mainLM->aiAmmountText[x] = 0;
	}
	if (mainLanguage == NULL)
	{
		return NOLANGFILE;
		//printf("System: Could not find/open %s language file\n", languageFiles[0]);
	}
	else
	{
		languageFileOpener(mainLM, mainLanguage);
	}
	fclose(mainLanguage);
	return NORMAL;
}

void memoryLanguageHeadAllocation(LanguageModule *mainLM, int user, char* word, int size, int action)
{
	LanguageCP aux;
	if (user == -1 && size == 0)
	{
		mainLM->MainUserBranch = (LanguageCP)malloc(sizeof(LanguageCell));
		mainLM->MainUserBranch->word = NULL;
		mainLM->MainUserBranch->nextWord = NULL;
		mainLM->user_lmw = mainLM->MainUserBranch; //Sets the last Main Word allocated;
		mainLM->MainAIBranch = (LanguageCP)malloc(sizeof(LanguageCell));
		mainLM->MainAIBranch->word = NULL;
		mainLM->MainAIBranch->nextWord = NULL;
		mainLM->ai_lmw = mainLM->MainAIBranch; //Sets the last Main Word allocated;
		//mainLM->MainLanguageFileOrigin[0] = "EN-US";
	}
	else if (user == 0)
	{
		aux = mainLM->user_lmw;
		aux->nextWord = (LanguageCP)malloc(sizeof(LanguageCell));
		aux = aux->nextWord;
		aux->word = (char*)malloc(size + 1);
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
		aux->word = (char*)malloc(size + 1);
		aux->action = action;
		strcpy(aux->word, word);
		aux->nextWord = NULL;
		mainLM->ai_lmw = aux;
		//printf("%s\n", word);
	}
}

void languageFileOpener(LanguageModule *mainLM, FILE *uLFile)
{
	int aux, x, z;
	//char *line;
	char line[1000];
	char auxline[1000];

	//Sets the temporary variables for the chat;
	int user = -1, action = NORMAL, size = 0;
	char info[1000];

	memset(auxline, '\0', sizeof(auxline));
	while (fgets(line, sizeof line, uLFile) != NULL)
	{
		memset(auxline, '\0', sizeof(auxline));
		memset(info, '\0', sizeof(info));
		x = 0;
		//printf("%s\n", line);
		for (aux = 0; aux < sizeof line; aux++)
		{
			auxline[x] = line[aux];
			if (line[aux] == '\0' || line[aux] == '\n' || line[aux] == '/' || line[aux] == '\r')
			{
				if (line[aux] == '/')
				{
					if (line[aux + 1] == '/')
					{
						break;
					}
					if (line[aux + 1] == '*')
					{
						return;
					}
				}
				else
				{
					break;
				}
				//break;
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
				if (size > 0)
				{
					//printf("DEBUG: %s\n", info);
					memoryLanguageHeadAllocation(mainLM, user, &info[0], size, action);
				}
			}
			x++;
		}

	}
}

int checkString(int aux, char line[1000], char *info)
{
	int z = 0;
	int size = 0;
	while (1)
	{
		if (line[aux + z] == '%')
		{
			if (line[aux + z + 1] == 's' || line[aux + z + 1] == 'd')
			{
				return -1;
			}
		}
		if (line[aux + z] == '\n' || line[aux + z] == '\0' || line[aux + z] == '\r')
		{
			//printf("==%s==\n", line);
			return size;
		}
		else
		{
			size += 1;
			info[z] = line[aux + z];
			//printf("==%s==\n", line);
		}
		z++;
	}
}
