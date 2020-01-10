 /*
 * conf.h 
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
 * Description: Header file for the configuration utilities 
 *
 */ 

#ifndef _SMT_LIBRA_CONF_H_
#define _SMT_LIBRA_CONF_H_

#ifdef __cplusplus
extern "C" {
#endif 

#define LINE 1024
#define SCRIPTS "scriptdir"
#define SCRIPTPATH "./scripts/"

#define PLUGINS "pluginsdir"
#define PLUGINSPATH "./plugins/"

	
struct conf{
	char *key;
	char *value;
};

int write_conf(const char *, const struct conf *);
struct conf *read_conf(const char *,const char *);
struct conf *set_conf(struct conf **, const char *, const char *);
char *get_conf(struct conf *,const char *);
char *script_path(struct conf *,const char *);
char *plugin_path(const char *);
void free_conf(struct conf *cf);

#ifdef __cplusplus
}
#endif

#endif 
