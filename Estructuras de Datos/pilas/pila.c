#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "pila.h"



int pilaCreaVacia(Pila *p){
	if(p==NULL) return -1;
	*p=NULL;
	
	return 0;
}

int pilaVacia(Pila *p){
	if(p==NULL) return -1;
    if(*p==NULL) return 1;
    else return 0;
}

int pilaInserta(tipoElemento elemento, Pila *p){
	if(p==NULL) return -1;
	
	tipoCelda *nuevo;
	nuevo = malloc(sizeof(tipoCelda));
	
	nuevo->elemento = elemento;
	nuevo->sig=*p;
	*p=nuevo;
	
	return 0;
}

tipoElemento pilaSuprime(Pila *p){
	if(p==NULL) return -1;
    tipoElemento valor;
    
    if(pilaVacia(p)) return -1;
    else{
    	valor = (*p)->elemento;
    	(*p)=(*p)->sig;
    	return valor; 
    }
    
}
