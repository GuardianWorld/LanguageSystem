# LanguageSystem
A small language system i made for use with a private project. How to use bellow!

(test.png)

How to use the LanguageSystem Module?

--  On the libraries, there is some prototypes of variables, as well as some structures.

On the first structure, LanguageCell:

--  It has the action used, defined the the #defines above, they are used for doing certains things in the program. If you are making a Bank Program, one input from the user could call a WELCOMEBACK message, that will recognize it and display on the screen something. 

--  There is a word, that is a char pointer, this place you will allocate the size for fitting the word in your Language File. 

--  There is also a nextWord LanguageCell Pointer there, that will point to the next word in a dinamically allocated list.
The second structure LanguageModule:

--  This is the main module you will use, and should be active all the time, initialized on the main function, this only has pointers for the LanguageCells, the first one is a pointer for the "Head" of the list, and the second one to the last word. The other Two are for the second user, in this case by name, the program itself.

The Variables:

  The languageInicialization is the only one you will call in your main for taking from the Language File and Initializing it. It takes a pointer to the LanguageModule you created on the main function.
  
  The LanguageFileOpener will open a file specified on ChatInicialization, and open it. It will open in this case two files. One main and other sub-language.
  
  The checkString will do the job of getting everything you need checked before passing.
  
  The MemoryChatHeadAllocation will get the Language Module, and all the variables got on the checkstring + LanguageFileOpener and allocate on memory the words.
  
  The user input will get the user input and check if it coincides to any allocated word. If it is equal, it return it's action to the main function.
