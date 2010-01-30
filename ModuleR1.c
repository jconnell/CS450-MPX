/*
 *  ModuleR1.c
 *  
 *
 *  Created by Jared Crawford on 1/24/10.
 *  Copyright 2010 Jared Crawford. All rights reserved.
 *
 */

 /*Anthony's GitHub test run code mod*/

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
	ALLOC_STR(prompt, MAX_PROMPT_SIZE, "/");
	int exitFlag = 0;
	
	//reuse these params in the do loop
	ALLOC_STR(userInput, MAX_INPUT_SIZE, "");
	ALLOC_STR(functionName, MAX_PARAM_SIZE, "");
	ALLOC_STR(functionParameters, MAX_INPUT_SIZE, "");
	int numParameters;
	int invalidParamNum;
	
	
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

void parseInput(char *userInput, char *functionName, char *functionParameters, int *numParameters){

	/*It's mostly done. *numParameters doesn't quite work. All the prints and so forth are just debugging code.
		Also, I still need to add a check for parameters that are too long.*/

	int curPos = 0;
	int i = 0;
	int paramCounter = 0;
	int inputLength = strlen(userInput);
	printf("%d\n", inputLength);
	
	//Handles leading spaces before command
	while (*userInput == ' ') {
			userInput++;
	}
	
	//Loop to find functionName and store it in array
	while ((*userInput != '\0') && (*userInput != ' ')) {
		*functionName = *userInput;
		printf("%c", *functionName);
		functionName++;
		userInput++;
		curPos++;
	}
	
	//Fills rest of functionName with spaces
	for (i=curPos; curPos < MAX_PARAM_SIZE; curPos++) {
		*functionName = ' ';
		functionName++;
	}
	
	curPos = 0;
	
	printf("\n");
	
	//Loop to find functionParameters and store them in array
	while (*userInput != '\0') {
		//Removes extra spaces in between params
		while (*userInput == ' ') {
			userInput++;
		}
		while ((*userInput != ' ') && (*userInput != '\0')) {
			*functionParameters = *userInput;
			printf("%c", *functionParameters);
			userInput++;
			functionParameters++;
			curPos++;
		}
		curPos++;
		
		//Fills up array between params with spaces
		for (i=curPos; curPos < MAX_PARAM_SIZE; curPos++) {
			*functionParameters = ' ';
			printf("%c", *functionParameters);
			functionParameters++;
		}
		
		curPos = 0;
		
		paramCounter++;
	}
	
	printf("\n%d", curPos);
	printf("\n%d\n", paramCounter);
	*numParameters = paramCounter;
	printf("%d", numParameters);
	printf("\n");
}


int invalidParameter(char *functionName, char *functionParameters, int *numParameters){
	return 0;
}

void callFunction(char *functionName, char *functionParameters, int *numParameters){
	if (!strcmp(functionName, "help")) {
		//execute help
		help(functionParameters);
	}
	else if(!strcmp(functionName, "dir") {
		
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
	Type \"help <command>\" to learn more";
	
}

//if param != valid functionName, display genericHelpText
void help(char *functionName){
	//set up the string to store the help text
	ALLOC_STR(helpText, MAX_HELP_SIZE, "");
	
	//make sure there is a param to check help against
	if (numParameters > 0) {
		if (!strcmp("dir",functionName[0])) {
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
	/*take a look at the dateHelpText to see what format I suggested...if you want to change how the user
	enters a date to change the system date, please also change the help text!*/
}


char *versionHelpText(){
	return "Enter 'version' as a command to display the current MPX version as well as the last modification date.\n";
}

void version(char *functionParameters, int *numParameters){
	/*once you decide what to output here besides version number and last modification date (authors, current date, etc.)
	I'll change the versionHelpText accordingly.*/
}


char *dirHelpText(){
	return "Enter 'dir' as a command to display all the files present in your current directory, including executable .MPX files.\n";
}

void dir(char *functionParameters, int *numParameters){
	/*be sure to create fake files to test this function! :) */
}


char *exitHelpText(){
	return "Enter 'exit' as a command to terminate the current MPX session.  Upon execution, the system will prompt the user "
	+ "to confirm the session termination.\n";
}


void exit(char *functionParameters, int *numParameters){
	//do we need this function?
	/*doesn't look like it*/
}


int confirmExit(){
	printf("Are you sure you want to exit? (y/n) ");
	ALLOC_STR(confirmation, MAX_INPUT_SIZE, getUserInput());
	if (!strcmp("y",confirmation)) {
		return 1;
	}
	return 0;
}

