# LanguageSystem
A small language system i made for use with a private project. How to use bellow!

![Showcase](/Test.png)


ps: The Communication system is a prototype of what you can do with the language system. It's as basic as it will get.

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
  
  The MemoryLanguageHeadAllocation will get the Language Module, and all the variables got on the checkstring + LanguageFileOpener and allocate on memory the words.
  
  The user input will get the user input and check if it coincides to any allocated word. If it is equal, it return it's action to the main function.



Final considerations:
 
  This is the first version of this module, it does the work right, and it's simple enough to help most people. You can modify it to change user interface/language interface, and removing the Random Effect will help you do it. 
  
  The real meat here is the code that Fetch the language file and stores in memory, the communications user->Program and Program->User are there just for demonstration purposes. You are free to use it anyway you want.
