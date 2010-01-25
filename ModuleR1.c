/*
 *  ModuleR1.c
 *  
 *
 *  Created by Jared Crawford on 1/24/10.
 *  Copyright 2010 Jared Crawford. All rights reserved.
 *
 */

#include "ModuleR1.h"

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
}

void parseInput(char *userInput, char *functionName, char *functionParameters, int *numParameters){
	//lots of code
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
	ALLOC_STR(buffer, MAX_INPUT_SIZE, "");
	int bufSize = MAX_INPUT_SIZE;
	int error = sys_req(READ, TERMINAL, buffer, &bufSize);
	//!!!!!!!!!!!!!!!!!!
	//!!!MEMORY LEAK!!!!
	//!!!!!!!!!!!!!!!!!!
	//(but it's late, and I'm tired)
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
		}//etc
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
	return "Some help text for date";
}


void date(char *functionParameters, int *numParameters){
	//
}


char *versionHelpText(){
	return "Some help text for version";
}

void version(char *functionParameters, int *numParameters){
	
}


char *dirHelpText(){
	return "Some help text for dir";
}

void dir(char *functionParameters, int *numParameters){
	
}


char *exitHelpText(){
	return "Some help text for exit";
}


void exit(char *functionParameters, int *numParameters){
	//do we need this function?
}


int confirmExit(){
	printf("Are you sure you want to exit? (y/n) ");
	ALLOC_STR(confirmation, MAX_INPUT_SIZE, getUserInput());
	if (!strcmp("y",confirmation)) {
		return 1;
	}
	return 0;
}

