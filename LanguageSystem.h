#pragma once
#ifndef CHAT_H_INCLUDED
#define CHAT_H_INCLUDED

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INTRODUCTION 00
#define WELCOMEBACK  01
#define SMALLTALK 	 02
#define GOODBYE		   03
#define OPENPROGRAM  04
#define NOOPERATION  10
#define INVALIDACT   99

char languageFiles[2][300];

typedef struct LC* LanguageCP;
typedef struct{

	LanguageCP MainUserBranch; //The main user branch of the file
	LanguageCP user_lmw;	 // The last main branch word of the user 

	LanguageCP MainAIBranch; //The main AI branch of the cell
	LanguageCP ai_lmw;	 // The last main branch word of the AI 

}LanguageModule;

typedef struct LC {
	int action;
	int personality;
	char* word;
	LanguageCP nextWord;
}LanguageCell;

int ChatInicialization(LanguageModule *mainLM, PeMModule *mainPeM);
int checkString(int aux, char line[80], char *info);
void memoryChatHeadAllocation(LanguageModule *mainLM, int user, char* word, int size, int personality, int action);
void languageFileOpener(PeMModule *mainPeM, LanguageModule *mainLM, int *filesOpen, FILE *uLFile);

int UserInput(char *OTalk, LanguageModule *lm);
#endif