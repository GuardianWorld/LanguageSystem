#pragma once
#ifndef LBaseLibrary_H_INCLUDED
#define LBaseLibrary_H_INCLUDED
//----------------------------------------------------//
//                                                    //
//	This file just serves as a basis to the rest of   //
//  the language program. Think of it as a Library.   //
//  It hosts the main defines/constants, and the      //
//  structs necessary for the working of it.          //
//                        Emanuel//GuardianWorld 2019 //
//----------------------------------------------------//



//----------------------------------------------------//
//                                                    //
//	Bellow are the defines, used for easy writing and //
//  memorization of the actions defined for the       //
//  library program.                                  //
//                                                    //
//----------------------------------------------------//

//Communication Defines/Constants 
//Before making any changes to the numbers of the constants, verify if the aiAmmountText is set to a higher number than the max number here.
#define INTRODUCTION 00
#define WELCOMEBACK  01
#define GREETINGS	 02
#define AFFIRMATION  03
#define NEGATION	 04
#define GOODBYE		 29
#define INVALIDACT	 99

//Errors
#define NORMAL		 00
#define NOLANGFILE   90
#define NOPATH		 92

//----------------------------------------------------//
//                                                    //
//	Bellow are the structs, used for the storage of   //
//  variables/text in the program's memory.           //
//  It uses linked lists to achieve this without      //
//  static allocation                                 //
//                                                    //
//----------------------------------------------------//


typedef struct LC* LanguageCP; //This is the pointer to the linked Cell, aka: The main body of the list. Each phrase/word is stored in a Cell.
typedef struct {


	int aiAmmountText[100]; //Stores the ammount of words into an action, it's the only static list, and needs to be adjusted if the ammount of actions passes the number 100.
	//The area above is used for random Program phrases.
	LanguageCP MainUserBranch; //The main user branch of the file
	LanguageCP user_lmw;	 // The last main branch word of the user

	LanguageCP MainAIBranch; //The main AI branch of the cell
	LanguageCP ai_lmw;	 // The last main branch word of the AI

}LanguageModule; //This struct stores the pointers/Main language Cells for the User, and the Program (nammed AI) 

typedef struct LC { //This is the main cell, each cell is made of:
	int action; //An action, defined on this library as a #Define
	char* word; //A word/phrase, that is allocated dynamically to help preserve space.
	LanguageCP nextWord; //The pointer to the next cell, used for running the list and getting all the options.

}LanguageCell;

#endif
