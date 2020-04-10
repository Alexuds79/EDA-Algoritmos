#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "cola.h"



int colaCreaVacia(Cola *c){
    if(c==NULL) return -1;
    
    c->fondo=NULL;
    c->frente=NULL;
    
    return 0;
}

int colaVacia(Cola *c){
    if(c==NULL) return -1;
    
    if(c->frente==NULL) return 1;
    return 0;
}

int colaInserta(tipoElemento elemento, Cola *c){
    if(c==NULL) return -1;
    
    tipoCelda *nuevo = malloc(sizeof(tipoCelda));
    nuevo->elemento = elemento;
    nuevo->sig=NULL;
    
    if(colaVacia(c)){
    	c->frente=nuevo;
    	c->fondo=nuevo;
    }
    else{
    	c->fondo->sig=nuevo;
    	c->fondo=nuevo;
    }
    
    return 0;
}

tipoElemento colaSuprime(Cola *c){
	if(c==NULL) return -1;
   
	tipoElemento valor;
	valor=c->frente->elemento;
	c->frente=c->frente->sig;
   
   return valor;
}













