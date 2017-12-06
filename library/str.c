///////////////////////////////////////////////////////////////////////////////////
//
//	@Project 			IFJ 2017
//
//  @Authors
//  Kristýna Jandová  	xjando04
//  Vilém Faigel		xfaige00
//  Nikola Timková		xtimko01
//	Bc. Václav Doležal	xdolez76
//
//	@File				str.h
//	@Description
//
///////////////////////////////////////////////////////////////////////////////////

#include "str.h"

/*
*	@function strInit
*	@param string *s
*	@description Funkce vytvori novy retezec
*/
int strInit(string *s) {
   if ((s->str = (char*) malloc(STR_LEN_INC)) == NULL)
      return STR_ERROR;
   s->str[0]    = '\0';
   s->length    = 0;
   s->allocSize	= STR_LEN_INC;
   return STR_SUCCESS;
}


/*
*	@function strInit
*	@param string *s
*	@description Funkce vytvori novy retezec
*/
string strChars(char * str) {
   string s;
   s.str       = str;
   s.length    = strlen(str);
   s.allocSize = s.length + 1;
   return s;
}


/*
*	@function strFree
*	@param string *s
*	@description Funkce uvolni retezec z pameti
*/
void strFree(string *s) {
   free(s->str);
}


/*
*	@function strClear
*	@param string *s
*	@description funkce vymaze obsah retezce
*/
void strClear(string *s) {
   s->str[0] = '\0';
   s->length = 0;
}


/*
*	@function strAddChar
*	@param string *s1
*	@param char c
*	@description prida na konec retezce jeden znak
*/
int strAddChar(string *s1, char c) {
   if (s1->length + 1 >= s1->allocSize)
   {
      // pamet nestaci, je potreba provest realokaci
      if ((s1->str = (char*) realloc(s1->str, s1->length + STR_LEN_INC)) == NULL)
         return STR_ERROR;
      s1->allocSize = s1->length + STR_LEN_INC;
   }
   s1->str[s1->length] = c;
   s1->length++;
   s1->str[s1->length] = '\0';
   return STR_SUCCESS;
}


/*
*	@function strCopyString
*	@param string *s1
*	@param string *s2
*	@description prekopiruje retezec s2 do s1
*/
int strCopyString(string *s1, string *s2) {
   int newLength = s2->length;
   if (newLength >= s1->allocSize) {
      // pamet nestaci, je potreba provest realokaci
      if ((s1->str = (char*) realloc(s1->str, newLength + 1)) == NULL)
         return STR_ERROR;
      s1->allocSize = newLength + 1;
   }
   strcpy(s1->str, s2->str);
   s1->length = newLength;
   return STR_SUCCESS;
}


/*
*	@function strCmpString
*	@param string *s1
*	@param string *s2
*	@description porovna oba retezce a vrati vysledek
*/
int strCmpString(string *s1, string *s2) {
   return strcmp(s1->str, s2->str);
}


/*
*	@function strCmpConstStr
*	@param string *s1
*	@param string *s2
*	@description porovna nas retezec s konstantnim retezcem
*/
int strCmpConstStr(string *s1, char* s2) {
   return strcmp(s1->str, s2);
}
/*
*	@function strCmpConstStr
*	@param string *s1
*	@param string *s2
*	@description porovna nas retezec s konstantnim retezcem - case insensitive
*/
int strCmpConstStrI(string *s1, char* s2) {
   return strcasecmp(s1->str, s2);
}


/*
*	@function *strGetStr
*	@param string *s
*	@description vrati textovou cast retezce
*/
char *strGetStr(string *s) {
   return s->str;
}


/*
*	@function strGetLength
*	@param string *s
*	@description vrati delku daneho retezce
*/
int strGetLength(string *s) {
   return s->length;
}


/*
*	@function strUpper
*	@param string *s
*	@description Hlavičkuje znaky
*/
string strUpper(string *s) {
    char *str = s->str;
    while (*str) {
        *str = toupper((unsigned char) *str);
        str++;
    }
    return *s;
}

/*
*	@function strPrintf
*	@param char* format
*	@param arguments
*	@description Vytvori string z printf
*/
string strPrintf(char* format,...) {
    char * buffer;
    size_t size;

    va_list args;
    va_start (args, format);

    size   = vsnprintf(NULL, 0, format, args) + 1;
    buffer = (char *) malloc(size);

    vsnprintf(buffer, size, format, args);

    va_end (args);

    return strChars(buffer);
}

/*
*	@function strConcat
*	@param string *s1
*	@param string *s2
*	@description spoji retezce do s
*/
int strConcat(string * s, string * s1, string * s2) {
    int newLength = s1->length + s2->length;

    int allocSize = newLength + STR_LEN_INC - (newLength % STR_LEN_INC);

    char * str = malloc(allocSize);

    snprintf(str, allocSize, "%s%s", s1->str, s2->str);

    s->str       = str;
    s->allocSize = allocSize;
    s->length    = newLength+1;

    return 1;
}

