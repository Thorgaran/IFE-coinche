#ifndef STRINGUTILS_H
#define STRINGUTILS_H
#include "core.h"

/** 
 * \fn char* cropStr(const char string[], int maxLength)
 * @param string[]: the string to crop
 * @param maxLength: the maximum length the string can be without cropping
 * @return croppedString*: pointer to the first char of the cropped string. Must be freed eventually!
 * 
 * Takes a string and returns a cropped version of it with dots at the end if it exceeds a given length
*/
char* cropStr(const char string[], int maxLength);

/** 
 * \fn formatStr(char string[], int maxLength, TextPosition textPosition, Bool underline)
 * @param string[]: the string to center
 * @param maxLength: the maximum length of the space the centered string will be displayed in
 * @param textPosition: text alignement within the string (left, center, right)
 * @param underline: TRUE if the text sould be underlined, FALSE otherwise
 * @return formattedString*: pointer to the first char of the centered string. Must be freed eventually!
 * 
 * Takes a string and returns a fixed length, text-aligned version of it, cropped and or underlined if needed
*/
char* formatStr(char string[], int maxLength, TextPosition textPosition, Bool underline);

#endif // STRINGUTILS_H
