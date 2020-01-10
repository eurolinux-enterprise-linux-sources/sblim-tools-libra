 /*
 * execscripts.h 
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
 * Description: header file for the scripts layer 
 *
 */ 

#ifndef _SMT_LIBRA_EXECSCRIPTS_H_
#define _SMT_LIBRA_EXECSCRIPTS_H_

#ifdef __cplusplus
extern "C" {
#endif 

int execScript(const char *);
int execScript1(const char *, const char *);
int execScript2(const char *, const char *, const char *);
int execScript3(const char *, const char *, const char *, const char *);
int execScript4(const char *, const char *, const char *, const char *, const char *);
  
void *readData(const char *script,  void *(*func)(int));
void *readData1(const char *script, const char *par1, void *(*func)(int));
void *readData3(const char *script, const char *par1, const char *par2, const char *par3, void *(*func)(int));

int writeData(const char *script, void (*func)(int));
int writeData1(const char *script, const char *par1, void (*func)(int));
#ifdef __cplusplus
}
#endif

#endif 
