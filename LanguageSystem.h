#ifndef LSystem_H_INCLUDED
#define LSystem_H_INCLUDED
#pragma once
//#include "Chat.h"
#include "InternalCommunicationLibrary.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int languageIncialization(LanguageModule *mainLM, FILE *mainLanguage);
int checkString(int aux, char line[1000], char *info);
void memoryLanguageHeadAllocation(LanguageModule *mainLM, int user, char* word, int size, int action);
void languageFileOpener(LanguageModule *mainLM, FILE *uLFile);

#endif