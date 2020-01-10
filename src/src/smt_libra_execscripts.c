 /*
 * execscript.c 
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
 * Description: This file contains the the basic scripting interface used in
 * the various resource access layers for the providers in the sblim project.
 * 
 */ 

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "smt_libra_execscripts.h"

/*
static int __execScript(const char *script){

  if (!script)
    return -EINVAL;
  fprintf(stderr, "%s\n", script);
  execlp(script,script,NULL);
  perror(sys_errlist[errno]);

  return errno;
}
*/

static int __execScript1(const char *script, const char *par1){
 
  if ((!script) || (!par1))
    return -EINVAL;
  
  fprintf(stderr, "%s\n", script);
  execlp(script,script,par1,NULL);
  perror(sys_errlist[errno]);

  return errno;
}


static int __execScript2(const char *script, const char *par1,const char *par2){

  if ((!script) || (!par1) || (!par2))
    return -EINVAL;
  fprintf(stderr, "%s\n", script);
  execlp(script,script,par1,par2,NULL);
  perror(sys_errlist[errno]);

  return(errno);
}


static int __execScript3(const char *script, const char *par1,const char *par2,
		                                     const char *par3){
  if ((!script) || (!par1) || (!par2) || (!par3))
    return -EINVAL;
  
  fprintf(stderr, "%s\n", script);
  execlp(script,script,par1,par2,par3,NULL);
  perror(sys_errlist[errno]);

  return errno;
}


static int __execScript4(const char *script, const char *par1,const char *par2,
		                   const char *par3, const char *par4){
  if ((!script) || (!par1) || (!par2) || (!par3) || (!par4))
    return -EINVAL;  
  
  fprintf(stderr, "%s\n", script);
  execlp(script,script,par1,par2,par3,par4,NULL);
  perror(sys_errlist[errno]);

  return errno;
}


int execScript(const char *script){
  int status;
  pid_t pid;
  
  if (!script)
    return -EINVAL;
  
  pid = fork();
  if (pid){
    waitpid(pid,&status,0);
    return -WEXITSTATUS(status);
  }
  else{
    fprintf(stderr, "exec: %s\n", script);
    execlp(script,script,NULL);
    perror(sys_errlist[errno]);

    exit(errno);
  }
  return 0;
}


int execScript1(const char *script, const char *par1){
  int status;
  pid_t pid;
  
  if ((!script) || (!par1))
    return -EINVAL;
  
  pid = fork();
  if (pid){
    waitpid(pid,&status,0);
    return -WEXITSTATUS(status);
  }
  else{
    fprintf(stderr, "exec: %s %s\n", script, par1);
    execlp(script,script,par1,NULL);
    perror(sys_errlist[errno]);

    exit(errno);
  }
  return 0;
}


int execScript2(const char *script, const char *par1,const char *par2){

  int status;
  pid_t pid;
  
  if ((!script) || (!par1) || (!par2))
    return -EINVAL;

  pid = fork();
  if (pid){
    waitpid(pid,&status,0);
    return -WEXITSTATUS(status);
  }
  else{
    fprintf(stderr, "exed %s %s %s\n", script, par1, par2);
    execlp(script,script,par1,par2,NULL);
    perror(sys_errlist[errno]);

    exit(errno);
  }
  return 0;
}


int execScript3(const char *script, const char *par1,const char *par2,
		                                     const char *par3){
  int status;
  pid_t pid;
  
  if ((!script) || (!par1) || (!par2) || (!par3))
    return -EINVAL;
  
  
  pid = fork();
  if (pid){
    waitpid(pid,&status,0);
    return -WEXITSTATUS(status);
  }
  else{
    fprintf(stderr, "exec %s %s %s %s\n", script, par1, par2, par3);
    execlp(script,script,par1,par2,par3,NULL);
    perror(sys_errlist[errno]);
    exit(errno);
  }
  return 0;
}


int execScript4(const char *script, const char *par1,const char *par2,
		                   const char *par3, const char *par4){
  int status;
  pid_t pid;
  
  if ((!script) || (!par1) || (!par2) || (!par3) || (!par4))
    return -EINVAL;
  
  pid = fork();
  if (pid){
    waitpid(pid,&status,0);
    return -WEXITSTATUS(status);
  }
  else{
    fprintf(stderr, "exec: %s %s %s %s %s\n", script, par1, par2, par3, par4);
    execlp(script,script,par1,par2,par3,par4,NULL);
    perror(sys_errlist[errno]);

    exit(errno);
  }
  return 0;
}


void *readData(const char *script,  void *(*func)(int) ){

  int status,fd[2];
  char *pipefd;
  void *data;
  pid_t pid;

  pipe(fd);
  asprintf(&pipefd,"%d",fd[1]);
  
  pid = fork();
  if(pid){
    data = func(fd[0]);
    waitpid(pid,&status,0);
    close(fd[1]);
    close(fd[0]);
  }else{
    __execScript1(script,pipefd);
    free(pipefd);
    perror(sys_errlist[errno]);

    close(fd[0]);
    close(fd[1]);
    exit(errno);
  }

  free(pipefd);
  if (status) return NULL;

  return (void*) data;
}


void *readData1(const char *script, const char *par1,void *(*func)(int)){

  int status,fd[2];
  char *pipefd;
  void *data;
  pid_t pid;

  pipe(fd);
  asprintf(&pipefd,"%d",fd[1]);
  
  pid = fork();
  if(pid){
    data = func(fd[0]);
    waitpid(pid,&status,0);
    close(fd[1]);
    close(fd[0]);
  }else{
    __execScript2(script,par1,pipefd);
    free(pipefd);
    perror(sys_errlist[errno]);

    close(fd[0]);
    close(fd[1]);
    exit(errno);
  }

  free(pipefd);
  if (status) return NULL;

  return (void*) data;

}


void *readData2(const char *script, const char *par1, const char *par2,
		                                    void *(*func)(int)){
  int status,fd[2];
  char *pipefd;
  void *data;
  pid_t pid;

  pipe(fd);
  asprintf(&pipefd,"%d",fd[1]);
  
  pid = fork();
  if(pid){
    data = func(fd[0]);
    waitpid(pid,&status,0);
    close(fd[1]);
    close(fd[0]);
  }else{
    __execScript3(script,par1,par2,pipefd);
    free(pipefd);
    perror(sys_errlist[errno]);

    close(fd[0]);
    close(fd[1]);
    exit(errno);
  }

  free(pipefd);
  if (status) return NULL;

  return (void*) data;
}


void *readData3(const char *script, const char *par1,const char *par2,
		                    const char *par3, void *(*func)(int)){
  int status,fd[2];
  char *pipefd;
  void *data;
  pid_t pid;

  pipe(fd);
  asprintf(&pipefd,"%d",fd[1]);
  
  pid = fork();
  if(pid){
    data = func(fd[0]);
    waitpid(pid,&status,0);
    close(fd[1]);
    close(fd[0]);
  }else{
    __execScript4(script,par1,par2,par3,pipefd);
    free(pipefd);
    perror(sys_errlist[errno]);

    close(fd[0]);
    close(fd[1]);
    exit(errno);
  }

  free(pipefd);
  if (status) return NULL;

  return (void*) data;
}


int writeData(const char *script, void (*func)(int) ){

  int status,fd[2];
  char *pipefd;
  pid_t pid;

  pipe(fd);
  asprintf(&pipefd,"%d",fd[0]);

  pid = fork();
  if(pid){
    func(fd[1]);
    waitpid(pid,&status,0);
    close(fd[1]);
    close(fd[0]);
  }else{
    __execScript1(script,pipefd);
    perror(sys_errlist[errno]);

    close(fd[1]);
    close(fd[0]);
    exit(errno);
  }

  free(pipefd);
  return status;
}


int writeData1(const char *script, const char *par1,void (*func)(int) ){
  
  int status,fd[2];
  char *pipefd;
  pid_t pid;

  pipe(fd);
  asprintf(&pipefd,"%d",fd[0]);

  pid = fork();
  if(pid){
    func(fd[1]);
    waitpid(pid,&status,0);
    close(fd[1]);
    close(fd[0]);
  }else{
    __execScript2(script,par1,pipefd);
    perror(sys_errlist[errno]);

    close(fd[1]);
    close(fd[0]);
    exit(errno);
  }
  
  free(pipefd);
  return status;
}
