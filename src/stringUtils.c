/**
 * \file stringUtils.c
*/
#include <stdlib.h>
#include <string.h>
#include "stringUtils.h"

#define UNDERLINE_SEQUENCE_LENGTH 9

char* cropStr(const char string[], int maxLength) {
    char* croppedString = (char*) malloc((maxLength + 3) * sizeof(char)); //Create the return pointer and allocate enough memory
    strncpy(croppedString, string, maxLength);  //Copy the input string into the output string (limited to maxLength)
    if (strlen(string) > maxLength) {           //If the input string is too long,
        croppedString[maxLength - 1] = '\0';    //put the terminating \0 in croppedString,
        strcat(croppedString, "…");             //and put dots at the end
    }
    else if (strlen(string) == maxLength) {
        croppedString[maxLength] = '\0'; //Put the terminating \0 in croppedString
    }
    return croppedString;
}

char* formatStr(char string[], int maxLength, TextPosition textPosition, Bool underline) {
    char* formattedString; //Create the return pointer
    char* croppedString = cropStr(string, maxLength); //Crop the input string if it's too long
    int additionalStrLength = 0, nbOfStartSpaces, nbOfEndSpaces, croppedStringLength = strlen(croppedString);
    if (croppedStringLength  < maxLength) { //Align the string if it's shorter than the maximum length
        formattedString = (char*) malloc((maxLength + 3 + UNDERLINE_SEQUENCE_LENGTH) * sizeof(char)); //Allocate memory for the return pointer
        switch (textPosition) { //Select the right number of spaces at the start and at the end depending on textPosition
            case TEXT_LEFT:
                nbOfStartSpaces = 0;
                nbOfEndSpaces = croppedStringLength;
                break;
            case TEXT_CENTER:
                nbOfStartSpaces = (maxLength - croppedStringLength)/2;
                nbOfEndSpaces = (maxLength + croppedStringLength)/2;
                break;
            case TEXT_RIGHT:
                nbOfStartSpaces = maxLength - croppedStringLength;
                nbOfEndSpaces = maxLength;
                break;
        }
        for(int i = 0; i < nbOfStartSpaces; i++) { //Put the right number of spaces at the start of formattedString
            formattedString[i] = ' ';
        }
        formattedString[nbOfStartSpaces] = '\0';    //Prepare formattedString for concatenation
        if (underline == TRUE) {                    //If underline mode,
            strcat(formattedString, "\033[4m");     //append opening underline sequence
            strcat(formattedString, croppedString); //Paste croppedString at the end of formattedString
            strcat(formattedString, "\033[24m");    //Append closing underline sequence
            additionalStrLength = UNDERLINE_SEQUENCE_LENGTH;
        }
        else {                                      //If not underline mode,
            strcat(formattedString, croppedString); //paste croppedString at the end of formattedString
        }
        free(croppedString); //CroppedString is not needed anymore, free it
        for(int i = nbOfEndSpaces + additionalStrLength; i < maxLength + additionalStrLength; i++) { //Put the right number of spaces at the end of formattedString
            formattedString[i] = ' ';
        }
        formattedString[maxLength + additionalStrLength] = '\0'; //Put the terminating \0
    }
    else {
        if (underline == TRUE) {                    //If underline mode,
            formattedString = (char*) malloc((maxLength + 3 + UNDERLINE_SEQUENCE_LENGTH) * sizeof(char)); //Allocate memory for the return pointer
            formattedString[0] = '\0';              //prepare formattedString for concatenation
            strcat(formattedString, "\033[4m");     //Append opening underline sequence
            strcat(formattedString, croppedString); //Paste croppedString at the end of formattedString
            strcat(formattedString, "\033[24m");    //Append closing underline sequence
            free(croppedString); //CroppedString is not needed anymore, free it
        }
        else {                                  //If not underline mode,
            formattedString = croppedString;    //formattedString is set to be the cropped string pointer
        }
    }
    return formattedString;
}