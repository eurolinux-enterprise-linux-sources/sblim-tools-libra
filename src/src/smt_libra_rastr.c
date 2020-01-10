 /*
 * rastr.c 
 *
 * (C) Copyright IBM Corp. 2005
 *
 * THIS FILE IS PROVIDED UNDER THE TERMS OF THE ECLIPSE PUBLIC LICENSE
 * ("AGREEMENT"). ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE
 * CONSTITUTES RECIPIENTS ACCEPTANCE OF THE AGREEMENT.
 *
 * You can obtain a current copy of the Eclipse Public License from
 * http://www.opensource.org/licenses/eclipse-1.0.php
 *
 * Author:  Glauber de Oliveira Costa <gocosta@br.ibm.com>
 *
 * Contributors: Tyrel Datwyler <tyreld@us.ibm.com>
 *
 * Description: Resource Access String utilities.
 *
 */ 
#include <stdlib.h>
#include <string.h>
#include <strings.h>

char *nonl(char *string){
  char *ptr;
  
  ptr = index(string,'\r');
  if (ptr)
    *ptr = '\0';
  ptr = index(string,'\n');
  if (ptr)
    *ptr = '\0';
  return string;
}


static char *__noquotes(char *str){
  char *ptr;
  while ( ((ptr = strpbrk(str,"\"'")) != NULL) && *str )
    strcpy(ptr,ptr+1);
  return str;
}

static char *__rstrip(char *str){
  char *ptr;
  
  ptr = nonl(str);
  
  ptr = index(str,'\0');
  while ((*(--ptr) == ' ') && *ptr)
    *ptr = '\0';
  
  return str;
}

static char *__lstrip(char *str){
  char *tmp = malloc(strlen(str) * sizeof(char));
  char *ptr = nonl(str);
  
  while ((*ptr == ' ') && *ptr)
    ptr = strcpy(tmp,ptr+1);  
  
  return ptr;
}

char *rstrip(char *string){
  char *str = strdup(string);
  return __rstrip(str);
}

char *lstrip(char *string){
  char *str = strdup(string);
  return __lstrip(str);
}

char *strip(char *string){
  char *str = strdup(string);
  return __lstrip(__rstrip(str));
}
char *noquotes(char *string){
  char *str = strdup(string);
  return __noquotes(str);
}

char *preproc(char *string){
  char *str = strdup(string);
  return __lstrip(__rstrip(__noquotes(str)));
  
}
