#pragma once
#ifndef LOCALCOM_H_INCLUDED
#define LOCALCOM_H_INCLUDED
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "InternalCommunicationLibrary.h"


void AITalk(int action, char *changable, LanguageModule *mainLM);
void changeIdentifier(LanguageCP aux, char *line, char identifiable[2], char *changable);
int UserInput(char *OTalk, LanguageModule *lm);
#endif