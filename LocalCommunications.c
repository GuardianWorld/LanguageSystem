#pragma once
#include "LocalCommunications.h"

void AITalk(int action,char *changable, LanguageModule *mainLM)
{
	LanguageCP aux;
	aux = mainLM->MainAIBranch;
	if (aux->nextWord != NULL)
	{
		aux = aux->nextWord;
	}
	srand((unsigned int)time(NULL));
	int x;
	int h = 0;
	int find = 0;
	char buffer[5000];
	bool foundSomething = false;
	x = mainLM->aiAmmountText[action];
	//printf("%d\n", x);
	if (x != 0) { h = 1 + rand() % x; }

	while (1)
	{
		if (action == aux->action)
		{
			find++;
		}
		if (find == h && h != 0)
		{
			changeIdentifier(aux, &buffer[0], "&s", changable);
			printf("-%s-\n", buffer);
			foundSomething = true;
			break;
		}
		if (aux->nextWord == NULL)
		{
			break;
		}
		else
		{
			aux = aux->nextWord;
		}
	}
	if (foundSomething == false)
	{
		char conversion[2];
		conversion[0] = action + '0';
		conversion[1] = '\0';
		if (action == INTRODUCTION)
		{
			printf("-Hello %s, i hope we get to work together for a long time!-\n", changable);
		}
		else if (action == WELCOMEBACK)
		{
			printf("-Hello there!-\n");
		}
		else if (action == GOODBYE)
		{
			printf("-GoodBye!-\n");
		}
		else if (action == INVALIDACT)
		{
			printf("-I did not understand what you mean-\n");
		}
	}

	return;
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
		if (strcmp(OTalk, aux->word) == 0) //Problema na alocação
		{
			return aux->action;
		}
	}
	return INVALIDACT;
}

void changeIdentifier(LanguageCP aux, char *line, char identifiable[2], char *changable)
{
	unsigned int z = 0, j = 0, size = 0, size1 = 0, maxSize, anotherOne = 0;
	char * pch;
	char auxchar[2000];
	char auxchar2[2000];
	if (changable != NULL)
	{
		size = strlen(changable);
	}
	else
	{
		size = 0;
	}
	size1 = strlen(aux->word);
	pch = strchr(aux->word, '&');
	while (pch != NULL)
	{
		anotherOne++;
		pch = strchr(pch + 1, '&'); //If find another, repeat.
	}
	maxSize = size1 + (anotherOne * (size - 2));
	if (maxSize > 2000)
	{
		return;
	}

	//printf("\nLine: \n=%s=\n", dynamicLine);

	memset(line, '\0', maxSize); //Set the line to \0.
	strcpy(line, aux->word);
	//printf("\nLine: =%s=\n", line);
	// void append(char *line, char *s, char *t, PeMModule *PeM, int firstSize, int secondSize, int sizemiddle)
	pch = strchr(line, '&');

	while (pch != NULL)
	{
		z = pch - line;
		memset(auxchar, '\0', maxSize); //Set the line to \0.
		memset(auxchar2, '\0', maxSize); //Set the line to \0.
		strncpy(&auxchar[0], line, z); //Copies the first half of the string (before the actual &)
		strcpy(&auxchar2[0], pch + 2); //Copies the second half of the string after the &
		memset(line, '\0', maxSize); //Set the line to \0.
		strncat(line, auxchar, z); //Concatenate the line plus the first half
		if (z != size - 1)
		{
			/*if (line[z + 1] == 'u')
			{
				//strcat(line, PeM->memory[5]); //Concatenate the line plus the name
			}
			else if (line[z + 1] == 's')
			{

			}*/
		}
		if (changable != NULL)
		{
			strcat(line, changable); //Concatenate the line plus the extra
		}
		strncat(line, auxchar2, size1); //Concatenate the line plus the rest

		pch = strchr(pch + 1, '&'); //If find another, repeat.
		//For now, it only covers the &u, later i wanna it to cover the &d and &s identifiers. not much different, only diferent place in memory (just need to check first);
	}

	//line = dynamicLine;
	return;
}