 /*
 * conf.c 
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
 * Description: Functionality to handle the basic configuration file 
 * for the Resource Access layer
 *
 */ 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "smt_libra_conf.h"
#include "smt_libra_rastr.h"



void free_conf(struct conf *cf){

  struct conf *p = cf;
		
  while (cf && cf->key && cf->value){
    free(cf->key);
    free(cf->value);
    cf++;
  }
  free(p);
}

/*
static char *__path(struct conf *c,const char *name,char *conf,char *dfl){

  char *dir;
  char *base;
  char *ptr;
  
  dir = get_conf(c,conf);
  if (!dir)
    dir = strdup(dfl);
  
  base = (char *)malloc(strlen(dir)+strlen(name)+2);
  strncpy(base,dir,strlen(dir)+1);
  
  ptr = strchr(base,'\n');
  if (ptr)
    *ptr = '/';
  else
    strcat(base,"/");
  strcat(base,name);
  
  return base;
}
*/
/*
char *script_path(const char *name){
	return __path(name,SCRIPTS,SCRIPTPATH);
}

char *plugin_path(const char *name){
	return __path(name,PLUGINS,PLUGINSPATH);
}
*/

char *script_path(struct conf *conf, const char *name){

  char *scriptdir;
  char *script;
  char *ptr;
  
  scriptdir = get_conf(conf,SCRIPTS);
  if (!scriptdir)
    scriptdir = strdup(SCRIPTPATH);
  
  script = (char *)malloc(strlen(scriptdir)+strlen(name)+2);
  strncpy(script,scriptdir,strlen(scriptdir)+1);
  free(scriptdir);
  
  ptr = strchr(script,'\n');
  if (ptr)
    *ptr = '/';
  else
    strcat(script,"/");
  strcat(script,name);
  
  return script;
}

int write_conf(const char *file, const struct conf *conf) {
  FILE *f = NULL;
  char *line;
  int ret = 0;
  
  f = fopen(file, "w");
  if (!f)
    return -1;

  line = (char *)malloc(sizeof(char) * LINE);

  while (conf && conf->key && conf->value) {
    snprintf(line, LINE, "%s = %s\n", conf->key, conf->value);
    if (fputs(line, f) == EOF) {
      ret = -1;
      break;
    }
    conf++;
  }

  fclose(f);

  return ret;
}

struct conf *read_conf(const char *file, const char *default_file){

  FILE *f = NULL;
  int count = 0;
  char *line, *lineptr;
  struct conf *conf;
  
  if (!default_file){
    errno = -EINVAL;
    return NULL;
  }
  
  f = fopen(file,"r");
  if (!f)
    f = fopen(default_file,"r");
  if (!f)
    return NULL;
  
  conf = malloc(sizeof(struct conf));
  count = 0;
  lineptr = (char *)malloc(LINE*sizeof(char));
  line = lineptr;
  
  while (!feof(f)){
    if (!fgets(line,LINE,f)) break;
    if ((!line) || (*line == '\n') || (*line == '#'))
      continue;
    conf = realloc(conf,(count+2)*sizeof(struct conf)); 
    conf[count].key = preproc(strsep(&line,"="));
    if (line)
      conf[count].value = preproc(line);
    else{
      free(conf[count].key);
      break;
    }
    count++;
    line = lineptr;
  }	 
  conf[count].key = NULL;
  conf[count].value = NULL;
  
  free(lineptr);
  fclose(f);
  
  return conf;
  
}

struct conf *set_conf(struct conf **c, const char *key, const char *value) {
  struct conf *conf = *c;
  int i = 0;

  while (conf && conf->key && strcmp(conf->key, key)) {
    conf++;
    i++;
  }

  if (conf && conf->key) {
    free(conf->value);
    conf->value = strdup(value);
  } else {
    *c = (struct conf *)realloc(*c, (i+2) * sizeof(struct conf));
    conf = *c;
    
    conf[i].key = strdup(key);
    conf[i].value = strdup(value);

    conf[i+1].key = NULL;
    conf[i+1].value = NULL;
  }

  return *c;
}

char *get_conf(struct conf *c,const char *key){
	
  char *ret;
  
  if (!c)
    return NULL;
  
  while (c && c->key && c->value){
    if (!strcmp(c->key,key)){
      ret = strdup(c->value);
      return ret;
    }
    c++;
  } 	
  return NULL;
}


