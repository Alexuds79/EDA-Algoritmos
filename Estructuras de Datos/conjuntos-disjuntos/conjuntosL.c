#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conjuntos.h"

/// Incluir aqui las funciones que implementan las tres operaciones básicas 
/// en la representación de CONJUNTOS DISJUNTOS mediante LISTAS
/// ......................................................................

void crea(particion C){
	int i;
	
	for(i=0; i<MAXIMO; i++){
		tipoCelda *nuevo = malloc(sizeof(tipoCelda));
		nuevo->sig = NULL;
		nuevo->elemento = i;
		
		C[i].primero = C[i].ultimo = nuevo;
	}
}

tipoElemento buscar(tipoElemento x, particion C){
	int i;
	
	for(i=0; i<MAXIMO; i++){
		tipoCelda *aux;
		aux = C[i].primero;
		
		while(aux != NULL){
			if(aux->elemento == x) return i;
			aux = aux->sig;
		}
	}
	
	return -1;

}

void unir(tipoElemento x, tipoElemento y, particion C){
	tipoElemento repX = buscar(x, C);
	tipoElemento repY = buscar(y, C);
	
	if(repX != -1 && repY != -1){
		C[repX].ultimo->sig = C[repY].primero;
		C[repX].ultimo = C[repY].ultimo;
		C[repY].primero = C[repY].ultimo = NULL;
	}
}

//
// Funciones auxiliares para ver contenido de Partición y Clase de Equivalencia
//


void verParticion(particion C){
	int i;
   	tipoCelda *aux;
    	
    	for (i =0;i<MAXIMO;i++) {
        	aux = C[i].primero;
        
        	if(aux!=NULL)  printf("\nClase equivalencia representante %d: ",i);
        
        	while(aux!=NULL){
        		printf("%d ",aux->elemento);
         		aux=aux->sig;
        	}
    	}
}

void verClaseEquivalencia(tipoElemento x,particion C){
	int representante;
  	tipoCelda *aux;
  
    	representante = buscar(x,C);
    	printf("\nClase de Equivalencia de %d cuyo representante es %d: ", x,representante);
    	
    	aux = C[representante].primero;
    	while (aux){
    		printf(" %d ",aux->elemento);
          	aux=aux->sig;
        }
        
    	printf("\n\n");
}


