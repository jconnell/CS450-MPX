/*
 *  ModuleR1.c
 *  
 *
 *  Created by Jared Crawford on 1/24/10.
 *  Copyright 2010 Jared Crawford. All rights reserved.
 *
 */
 
 
	//NOTE: be sure to change the version, modification date, and modifier in version() every time you commit!
	//ALSO: my friend who took this last semester said a major problem they found was that
	//Turbo C required them to define their variables before they do anything else in each function,
	//so make sure you define all variables before doing anything else (including allocating strings)

//Our Code
#include "ModuleR1.h"

//Provided Code
#include "mpx_supt.h"

//C Libraries
#include <string.h>


#ifndef DEBUG

	#define DEBUG 0
	
	#define VERSION_NUM 1.0

	#define MAX_INPUT_SIZE 80
	#define MAX_PARAM_SIZE 20
	#define MAX_HELP_SIZE 500
	#define MAX_VER_SIZE 500
	#define MAX_FILENAME_SIZE 10
	#define MAX_PROMPT_SIZE 10

	#define ALLOC_STR(NAME,SIZE,CONTENTS) char NAME[SIZE] = (char*)sys_alloc_mem(sizeof(char)*SIZE); \
		strncpy(NAME, CONTENTS, SIZE)
	
#endif

//////////////////////////
//Put any globals here
//Consult team first
//Don't forget to init and cleanUp

char userInputBuffer[MAX_INPUT_SIZE];


//////////////////////////




int main(){
	initGlobals();
	displayWelcomeMessage();
	commandHandler();
	displayExitMessage();
	cleanUpGlobals();
}


void initGlobals(){
	int sysInitResult = sys_init(MODULE_R1);
	userInputBuffer = (char*)sys_alloc_mem(sizeof(char)*MAX_INPUT_SIZE);
}

void displayWelcomeMessage(){
	printf("Hola\n");
}


void commandHandler(){
	int numParameters;
	int invalidParamNum;
	int exitFlag = 0;
	ALLOC_STR(prompt, MAX_PROMPT_SIZE, "/");
	
	//reuse these params in the do loop
	ALLOC_STR(userInput, MAX_INPUT_SIZE, "");
	ALLOC_STR(functionName, MAX_PARAM_SIZE, "");
	ALLOC_STR(functionParameters, MAX_INPUT_SIZE, "");
	
	
	
	do {
		printf("%s", prompt);
		strncpy(userInput, getUserInput(), MAX_INPUT_SIZE);
		parseInput(userInput, &functionName[0], &functionParameters[0], &numParameters);
		invalidParamNum = invalidParameters(&functionName[0], &functionParameters[0], &numParameters)
		if (!strcmp("exit", functionName)) {
			exitFlag = confirmExit();
		}
		else if (!invalidParamNum) {
			callFunction(&functionName[0], &functionParameters[0], &numParameters);
		}
		else {
			//display error message for invalidParamNum
		}
		
	} while (!exitFlag);
	
	sys_free_mem(prompt);
	sys_free_mem(userInput);
	sys_free_mem(functionName);
	sys_free_mem(functionParameters);
	
}

void displayExitMessage(){
	printf("Adiós\n");
}

void cleanUpGlobals(){
	sys_exit();
	sys_free_mem(userInputBuffer);
}

int parseInput(char *userInput, char *functionName, char *functionParameters, int *numParameters){
	
	//Still can't figure out how to get the number of parameters into memory, but if someone figures it out, it'll take like two lines and I'll put it in.
	//Added error checking for too many params and commands/params that are too long
	//I changed the function to return integers (0 for success, 1 for error). I was too afraid to start playing with other people's code,
	//this will need to be changed when you use parseInput.
	//Other than writing numParameters to memory, this function is done.
	
	int curPos = 0;
	int i = 0;
	int paramCounter = 0;
	int maxParamsAllowed = (MAX_INPUT_SIZE/MAX_PARAM_SIZE) - 1;	//Determines how many params are allowed AS LONG AS THE MAX COMMAND AND MAX PARAM SIZES ARE THE SAME
	
	while (*userInput == ' ') {
			userInput++;
	}
	
	//Loop to find functionName and store it in array
	while ((*userInput != '\0') && (*userInput != ' ')) {
		*functionName = *userInput;
		functionName++;
		userInput++;
		curPos++;
		if ((curPos >= MAX_PARAM_SIZE) && (*userInput != ' ') && (*userInput != '\0')) {	//Checks to make sure that commands are less than MAX_PARAM_SIZE
			printf("\nERROR: Commands must be no more than %d characters.\n", MAX_PARAM_SIZE);
			return 1;
		}
	}
	
	//Fills rest of functionName with spaces
	for (i=curPos; curPos < MAX_PARAM_SIZE; curPos++) {
		*functionName = ' ';
		functionName++;
	}
	
	curPos = 0;
	
	//Removes spaces between command and first parameter
	while (*userInput == ' ') {
			userInput++;
	}
	
	//Loop to find functionParameters and store them in array
	while (*userInput != '\0') {
		
		if (paramCounter >= maxParamsAllowed) {
			printf("\nERROR: There can be no more than %d parameters.", maxParamsAllowed);
			return 1;
		}
		
		while ((*userInput != '\0') && (*userInput != ' ')) {
			*functionParameters = *userInput;
			userInput++;
			functionParameters++;
			curPos++;
			if ((curPos >= MAX_PARAM_SIZE) && (*userInput != ' ') && (*userInput != '\0')) {	//Checks to make sure that params are less than MAX_PARAM_SIZE
				printf("\nERROR: Parameters must be no more than %d characters.\n", MAX_PARAM_SIZE);
				return 1;
			}
			
		}
		
		
		for (i=curPos; curPos < MAX_PARAM_SIZE; curPos++) {
				*functionParameters = ' ';
				functionParameters++;
		}
		
		curPos = 0;
		paramCounter++;
		
		//Removes spaces between parameters
		while (*userInput == ' ') {
			userInput++;
		}
		
	}
	
	printf("%d\n", paramCounter);	//FOR DEBUGGING PURPOSES
	//*numParameters = paramCounter;
	//printf("%d", numParameters);
	//printf("\n");
	return 0;
	
}


int invalidParameter(char *functionName, char *functionParameters, int *numParameters){
	return 0;
}

void callFunction(char *functionName, char *functionParameters, int *numParameters){
	//set up string for version text since all the version function does is print text
	ALLOC_STR(verText, MAX_VER_SIZE, "");
	
	if (!strcmp(functionName, "help")) {
		//execute help
		help(functionParameters, numParameters);
	}
	else if(!strcmp(functionName, "dir") {
		
	}
	else if(!strcmp(functionName, "version") {
		//call version
		strncpy(verText, version(), MAX_VER_SIZE);
	}

}


char *getUserInput(){
	int bufSize = MAX_INPUT_SIZE;
	int error = sys_req(READ, TERMINAL, userInputBuffer, &bufSize);
	if (error) {
		return NULL;
	}
	return userInputBuffer;
}

char *genericHelpText(){
	return "Available commands are:\n\
	\tdir\n\
	\texit\n\
	\tversion\n\
	\tdate\n\
	\n\
	Type \"help <command>\" to learn more.\n";
	
}

//if param != valid functionName, display genericHelpText
//1/31 added functionParameters and numParameters to params passed to help function since they're used below
//also removed functionName param since it wouldn't be used here (I don't think)
void help(char *functionParameters, int *numParameters){
	//set up the string to store the help text
	ALLOC_STR(helpText, MAX_HELP_SIZE, "");
	
	//make sure there is a param to check help against
	if (numParameters > 0) {
		if (!strcmp("dir",functionParameters[0])) {
			strncpy(helpText, dirHelpText(), MAX_HELP_SIZE);
		}
		else if(!strcmp("exit",functionParameters[0])){
			strncpy(helpText, exitHelpText(), MAX_HELP_SIZE);
		}
		else if(!strcmp("date",functionParameters[0])){
			strncpy(helpText, dateHelpText(), MAX_HELP_SIZE);
		}
		else if(!strcmp("version",functionParameters[0])){
			strncpy(helpText, versionHelpText(), MAX_HELP_SIZE);
		}
		else {
			strncpy(helpText, genericHelpText(), MAX_HELP_SIZE);
		}
	}
	else {
		strncpy(helpText, genericHelpText(), MAX_HELP_SIZE);
	}
	
	printf("%s", helpText);
	sys_free_mem(helpText);
}

char *dateHelpText(){
	return "To view the current system date, simply enter 'date' as a command.  To change the system date, "
	+ "enter 'date <DD/MM/YYYY>' as a command using a valid date (for example, 02/30/2010 is not a valid date, but "
	+ "02/28/2010 is valid). The system will automatically check to see if the date you entered is valid "
	+ "and you will be informed as to whether or not the system date was changed.\n";
}


void date(char *functionParameters, int *numParameters){
	//take a look at the dateHelpText to see what format I suggested...if you want to change how the user
	//enters a date to change the system date, please also change the help text!
}


char *versionHelpText(){
	return "Enter 'version' as a command to display the following content: \n\
		\tCurrent MPX version\n\
		\tGroup Members\n\
		\tLast modification date.\n";
}

char *version(){
	//be sure to change the version, modification date, and modifier every time you commit!
	return "CS450 MPX Operating System Project\n\
			\tCurrent Version: 1.5\n\
			\n\
			\tGroup 6:\n\
			\tChris Blosser\n\
			\tJon Connell\n\
			\tJared Crawford\n\
			\tAnthony Palma\n\
			\n\
			\tLast Modification Date: 1/31/10 by Anthony\n";
}

char *dirHelpText(){
	return "Enter 'dir' as a command to display all the files present in your current directory, including executable .MPX files.\n";
}

void dir(char *functionParameters, int *numParameters){
	//be sure to create fake files to test this function! :)
}


char *exitHelpText(){
	return "Enter 'exit' as a command to terminate the current MPX session.  Upon execution, the system will prompt the user "
	+ "to confirm the session termination.\n";
}


//void exit(char *functionParameters, int *numParameters){
	//do we need this function?
	//doesn't look like it
//}


int confirmExit(){
	ALLOC_STR(confirmation, MAX_INPUT_SIZE, getUserInput());
	printf("Are you sure you want to exit? (y/n) ");
	if (!strcmp("y",confirmation)) {
		return 1;
	}
	return 0;
}

