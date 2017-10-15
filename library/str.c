#include <malloc.h>
#include <strings.h>
#include "str.h"


// konstanta STR_LEN_INC udava, na kolik bytu provedeme pocatecni alokaci pameti
// pokud nacitame retezec znak po znaku, pamet se postupne bude alkokovat na
// nasobky tohoto cisla

#define STR_LEN_INC 8
#define STR_ERROR   1
#define STR_SUCCESS 0

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
