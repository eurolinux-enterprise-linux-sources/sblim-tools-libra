 /*
 * monitors.c 
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
 * Contributors:
 *
 * Description: This file offers the simple functionality for checking for
 * changes in a given file. Over the other libraries that do the same, like fam 
 * and gamin, it has the advantage of simplicity (we only code what we need), and
 * NO EXTERNAL LINKING but libc. The disadvantages are obviously coding that again.
 *
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include "smt_libra_monitors.h"

struct monitor *init_monitor(int max){

  struct monitor *m = (struct monitor *)malloc(sizeof(struct monitor));
  if (!m)
    return NULL;
  m->nentries = 0;
  m->maxentries = max;
  m->entries =  (struct entry *)calloc(m->maxentries + 1,sizeof(struct entry));
  if (!m->entries){
    free(m);
    return NULL;
  }
  return m;
}
void destroy_monitor(struct monitor *m){
	
  int i;
  for (i = 0; i < m->nentries; i++)
    free(m->entries[i].filename);
  free(m->entries);
  free(m);
}

struct entry *add_entry(struct monitor *m,char *filename){
	
	if (m->nentries >= m->maxentries){
		m->maxentries += 10;
		m->entries = (struct entry *)realloc(m->entries,(m->maxentries +1)*sizeof(struct entry));
	}
	m->entries[m->nentries].filename  =  strdup(filename);
	return m->entries+(m->nentries++);

}	
struct entry *find_entry(struct monitor *m, char *filename){
	struct entry *e = m->entries;

	for (; e && e->filename; e++)
		if (!strcmp(e->filename,filename))
			return e;

	return NULL;
}


void del_entry(struct monitor *m,struct entry *e){
	memmove(e,e+1,sizeof(struct entry));
	m->nentries++;
}

void touch_entry(struct monitor *m,char *filename){
	/* like the touch command, but does not create anything 
	 * in any situation. Use it if there is a need to avoid 
	 * a re-read of the files in a situation in wich we are
	 * sure it will happen but don't want it. i.e. after a 
	 * write from our side */

	struct entry *e = find_entry(m,filename);
	struct stat st;
	int ret;
	
	if (!e)
			return;
	ret = stat(filename,&st);
	if (ret) /* maybe the file has been deleted. Ok, don't do 
							anything, wait a explicit unregister */
		return;
	memcpy(&e->st,&st,sizeof(struct stat));
}
	
	
int has_changes(struct monitor *m, const char *filename){
	/* -1 means an error ocurred in stat
			0 means the file has changed
			1 means the file has not changed
  */

	struct entry *e = find_entry(m,(char *)filename);
	struct stat st;
	int ret = 1;
	if (!e)
		return -ENOENT;
	ret = stat(filename,&st);
	if (ret)
	  return ret;
	if (memcmp(&st.st_mtime,&e->st.st_mtime,sizeof(time_t))){
	  ret = 0;
	  memcpy(&m->entries->st.st_mtime,&st.st_mtime,sizeof(time_t));
	}
	else{
		ret = 1;
	}
	return ret;

}		
		

int check_events(struct monitor *m){

	int i;

	for (i = 0; i < m->nentries; i++)
		if (!has_changes(m,m->entries[i].filename)){
			return 0;
		}
	
	return 1;

}


	
int monitor_file(struct monitor *m,char *file){
	struct entry *e = find_entry(m,file);
	struct stat st;
	int ret = 0;

	if (e)
		return ret;

	ret = stat(file,&st);
	if (ret)
		return ret;

	e = add_entry(m,file);
	
	memcpy(&e->st,&st,sizeof(struct stat));	
	return ret;
}
int unmonitor_file(struct monitor *m, char *file){
	struct entry *e = find_entry(m,file);
	if (e){
		del_entry(m,e);
	}
	return 0;
}

/*int main(int argc, char *argv[]){

	mon = init_monitor(50);
	if (!mon)
		return 1;
	//monitor_file("/home/glauber/sources/teste.c");

	for(;;);
	return 0;
}*/
//PROTOTYPES

/*DNSZONE *zones = NULL;

DNSZONE *getZones(){

	char *conffile;
	int i;
	if (!zones){
		init_entries();
		init_monitor();
		conffile = get_conf("bindconf");
		if (!conffile)
			conffile = strdup(BINDCONF);
			zones = getZones();
			monitor_file(conffile);
		}
		for (i = 0; (zones+i) && zones[i].zoneName; i++){
			if (zones[i].zoneFile)
				monitor_file(zones[i].zoneFile);
		}
	}
		return zones;
}*/
