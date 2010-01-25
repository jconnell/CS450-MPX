/*
 *  ModuleR1.h
 *  
 *
 *  Created by Jared Crawford on 1/24/10.
 *  Copyright 2010 Jared Crawford. All rights reserved.
 *
 */


#pragma mark User Interaction

//If something goes in here, make sure to either cleanup in cleanUpGlobals() or document why not
void initGlobals();

void displayWelcomeMessage();

void commandHandler();

void displayExitMessage();

void cleanUpGlobals();

//pass last three function parameters as reference
void parseInput(char *userInput, char *functionName, char *functionParameters, int *numParameters);

//returns 0 if function and parameters are valid, else returns index of invalid parameter
//return 1 is function name, params are numbered 2 to numParameters+1
int invalidParameter(char *functionName, char *functionParameters, int *numParameters);

//maps functionName to a function call
void callFunction(char *functionName, char *functionParameters, int *numParameters);

#pragma mark Convenience Methods

//a wrapper for sys_req
char *getUserInput();


#pragma mark help

//available function list
char *genericHelpText();

//if param != valid functionName, display genericHelpText
void help(char *functionName);

#pragma mark date

char *dateHelpText();

//if numParameters = 0, get date
//else, set date
void date(char *functionParameters, int *numParameters);

#pragma mark version

char *versionHelpText();

void version(char *functionParameters, int *numParameters);

#pragma mark dir

char *dirHelpText();

void dir(char *functionParameters, int *numParameters);

#pragma mark exit

char *exitHelpText();

//do we need this function?
void exit(char *functionParameters, int *numParameters);

//returns 1 for exit, 0 for cancel
int confirmExit();

