#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbolBB.h"


#ifdef EJERCICIO1
/******************************************************************
* Árboles Binarios de Búsqueda SIN CLAVES REPETIDAS		  *
* Se incluye un poco de código para mostrar la diferencia entre   *
* insertar (paso por referencia) y buscar                         * 
*******************************************************************/

int insertar(tipoArbolBB *raiz, tipoClave clave){
	tipoNodo *nuevo;
    
  	if(*raiz==NULL){
		nuevo = malloc(sizeof(tipoNodo));
		nuevo->clave = clave;
		nuevo->info = 1;
		nuevo->izq=NULL;
  		nuevo->der=NULL;
  		
		*raiz = nuevo;
  	}
	else if(clave < (*raiz)->clave) insertar(&((*raiz)->izq), clave);
	else if(clave > (*raiz)->clave) insertar(&((*raiz)->der), clave);
	else if(clave == (*raiz)->clave){
		(*raiz)->info++; /*No admito clave duplicada*/
	}
	
	return 0;
}

int buscar(tipoClave clave,tipoArbolBB raiz, tipoNodo **nodo){
	if (raiz==NULL) return 0;
	else if (clave < raiz->clave) buscar(clave, raiz->izq, nodo);
	else if (clave > raiz->clave) buscar(clave, raiz->der, nodo);
	else{
		*nodo=raiz;
		return (*nodo)->info;
	}
}

int eliminar(tipoArbolBB *raiz, tipoClave clave){
	tipoNodo *aux, *ant;

	if((*raiz) == NULL) return 0;
	else if(clave < (*raiz)->clave) return eliminar(&((*raiz)->izq), clave);
	else if(clave > (*raiz)->clave) return eliminar(&((*raiz)->der), clave);
	else if(clave == (*raiz)->clave){
		aux = *raiz;

		if(aux->der==NULL) *raiz = aux->izq;
		else if(aux->izq == NULL) *raiz = aux->der;
		else{
			ant = aux;
			aux=aux->izq;

			while(aux->der != NULL){
				ant = aux;
				aux = aux->der;
			}

			(*raiz)->clave = aux->clave;
			(*raiz)->info = aux->info;

			/*Eliminar aux*/			
			if(ant==*raiz) ant->izq = aux->izq;
			else ant->der = aux->izq;
			free(aux);
		}
	}
	
	return 1;
}

#endif

#ifdef EJERCICIO3
/******************************************************
* Árboles Binarios de Búsqueda CON CLAVES REPETIDAS   *
******************************************************/
int insertar(tipoArbolBB *raiz, tipoClave clave, tipoInfo info){
	tipoNodo *nuevo;
    
  	if(*raiz==NULL){
		nuevo = malloc(sizeof(tipoNodo));
		nuevo->clave = clave;
		strcpy(nuevo->info, info);
		nuevo->izq=NULL;
  		nuevo->der=NULL;
		
		*raiz = nuevo;
  	}
	else if(clave < (*raiz)->clave) insertar(&((*raiz)->izq), clave, info);
	else if(clave > (*raiz)->clave) insertar(&((*raiz)->der), clave, info);
	else if(clave == (*raiz)->clave){
		/*Clave duplicada*/
		nuevo = malloc(sizeof(tipoNodo));
		nuevo->clave = clave;
		strcpy(nuevo->info, info);
		nuevo->izq=NULL;
  		nuevo->der=NULL;
		
		nuevo->izq = (*raiz)->izq;
		(*raiz)->izq = nuevo;
	}
  
	return 0; 
}

int eliminar(tipoArbolBB *raiz, tipoClave clave){ /*Solo elimina una de las claves duplicadas. Hacer para todas*/
	tipoNodo *aux, *ant;

	if((*raiz) == NULL) return 0;
	else if(clave < (*raiz)->clave) return eliminar(&((*raiz)->izq), clave);
	else if(clave > (*raiz)->clave) return eliminar(&((*raiz)->der), clave);
	else if(clave == (*raiz)->clave){
		aux = *raiz;

		if(aux->der==NULL) *raiz = aux->izq;
		else if(aux->izq == NULL) *raiz = aux->der;
		else{
			ant = aux;
			aux=aux->izq;

			while(aux->der != NULL){
				ant = aux;
				aux = aux->der;
			}

			(*raiz)->clave = aux->clave;
			strcpy((*raiz)->info, aux->info);

			/*Eliminar aux*/			
			if(ant==*raiz) ant->izq = aux->izq;
			else ant->der = aux->izq;
			free(aux);
			
			return eliminar(raiz, clave)+1; //Eliminar todas las claves duplicadas (es lo unico que cambia)
		}
	}
	
	return 1;
}


int esBalanceado(tipoArbolBB *raiz){
	int hIzq, hDer;
	
	if(*raiz == NULL){
		return -1;
	}
	else{
		hIzq = esBalanceado(&((*raiz)->izq))+1; 
		hDer = esBalanceado(&((*raiz)->der))+1;
	}
	
	return hDer-hIzq;
}

#endif


/*****************************************************************************************
* Funciones GENERALES adaptadas a los dos ejercicios mediante DIRECTIVAS DE COMPILACIÓN  *
/*****************************************************************************************/
tipoNodo *creaNodo(tipoClave clave, tipoInfo info){
	tipoNodo * nuevo;
  
  	//nuevo =(tipoNodo *)calloc(1, sizeof(tipoNodo));
  
	if ((nuevo =(tipoNodo *)malloc(sizeof(tipoNodo)))==NULL) return NULL;
  	else{
		nuevo->clave = clave;
  	
		#ifdef EJERCICIO1
		nuevo->info=info;
  		#endif
  	
		#ifdef EJERCICIO3
		strcpy(nuevo->info,info);
  		#endif
  	
		nuevo->izq=NULL;
  		nuevo->der=NULL;
  
		return nuevo;
  	}
}

void preOrden(tipoArbolBB a){
	if(a){ 
  		#ifdef EJERCICIO1
		printf("%d %d \n", a->clave,a->info);
		#endif
  	
		#ifdef EJERCICIO3
		printf("%d %s \n", a->clave,a->info);
  		#endif
  	
		preOrden(a->izq);
  		preOrden(a->der);
  	}
} 

void enOrden(tipoArbolBB a){
	if(a){ 
		enOrden(a->izq);
   	
		#ifdef EJERCICIO1
		printf("%d %d \n", a->clave,a->info);
   		#endif
   	
		#ifdef EJERCICIO3
		printf("%d %s \n", a->clave,a->info);
   		#endif
    	
		enOrden(a->der);
  	}
}

void posOrden(tipoArbolBB a){
	if(a){
  		enOrden(a->izq);
  		enOrden(a->der);
   	
		#ifdef EJERCICIO1
		printf("%d %d \n", a->clave,a->info);
   		#endif
   	
		#ifdef EJERCICIO3
		printf("%d %s \n", a->clave,a->info);
   		#endif
  	}
}

