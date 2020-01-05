#include <stdlib.h>
#include <stdio.h>
#include "LanguageSystem.h"
#include "LocalCommunications.h"

int main()
{
	int error, action;
	char UserName[100];
	char input[1000];
	LanguageModule mainLM;
	FILE *systemLanguage;
	systemLanguage = fopen("Language/EN-US.lang", "r"); //It's the main language file, verify if the file is in the correct folder.
	error = languageIncialization(&mainLM, systemLanguage);
	
	if (error == NOLANGFILE)
	{
		printf("Error getting files, please check the language folder or contact the programmer\n");
		printf("Exited with code %d\n", NOLANGFILE);
		system("pause");
		return NOLANGFILE;
	}
	printf("Digit your username: ");
	fgets(&UserName[0], sizeof(UserName), stdin);
	UserName[strcspn(UserName, "\n")] = 0; //Removing the /n at the end of the scanf

	AITalk(INTRODUCTION, &UserName, &mainLM);
	while (1)
	{
		error = -1;
		fgets(&input[0], sizeof(input), stdin);
		input[strcspn(input, "\n")] = 0; //Removing the /n.. it's necessary
		action = UserInput(&input[0], &mainLM);
		AITalk(action, UserName, &mainLM);

		if (action == GOODBYE)
		{
			break;
		}
	}
	system("pause");
	return 0;
}