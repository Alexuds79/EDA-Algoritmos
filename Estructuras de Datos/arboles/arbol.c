#include <stdlib.h>
#include <stdio.h>
#include "arbol.h"
#include "genArbol.h"
#include "cola.h"
#include "pila.h"


/* RESERVA DE MEMORIA PARA UN NUEVO NODO DE ARBOL BINARIO */

Arbol creaNodo(tipoInfo info){
	tipoNodo * nuevo;

	//   nuevo =(tipoNodo *)calloc(1, sizeof(tipoNodo));
	if ((nuevo =(tipoNodo *)malloc(sizeof(tipoNodo)))==NULL) return NULL;
	else{
		nuevo->info=info;
		nuevo->izq=NULL;
		nuevo->der=NULL;
		return nuevo;
	}
}


/* RECORRIDO EN AMPLITUD O POR NIVELES */


void amplitud(Arbol raiz){
	Cola c;
	tipoNodo *nodo;
	colaCreaVacia(&c);
	nodo = raiz;

	if (raiz!=NULL) colaInserta(nodo,&c);
	while (!colaVacia(&c)){
		nodo = (Arbol) colaSuprime(&c);
		printf(" %c ", nodo->info);
		if (nodo->izq!=NULL) colaInserta(nodo->izq,&c);
		if (nodo->der!=NULL) colaInserta(nodo->der,&c);
	}
}


/* RECORRIDOS EN PROFUNDIDAD "RECURSIVOS" */


void preOrden(Arbol raiz){
	if (raiz!=NULL){
		printf(" %c ",raiz->info);
		preOrden(raiz->izq);
		preOrden(raiz->der);
	}
}


void enOrden(Arbol raiz){
	if (raiz!=NULL){ enOrden(raiz->izq);
		printf(" %c ",raiz->info);
		enOrden(raiz->der);
	}
}


void postOrden(Arbol raiz){
	if (raiz!=NULL){
		postOrden(raiz->izq);
		postOrden(raiz->der);
		printf(" %c ",raiz->info);
	}
}


int altura(Arbol raiz){		// SOLO VALE POSTORDEN
	int hizq, hder;

	if(raiz==NULL) return -1;
	else{
		hizq=altura(raiz->izq);
		hder=altura(raiz->der);
		if(hizq>hder) return hizq+1;
		else return hder+1;
	}
}


int numNodos(Arbol raiz){	// VALE CUALQUIER ORDEN
	int izquierdo, derecho, numero;

	if(raiz==NULL) return 0;
	else{
		izquierdo=numNodos(raiz->izq);
		derecho=numNodos(raiz->der);
		numero=1+izquierdo+derecho;
		return numero;
	}
}


Arbol anula(Arbol raiz){	// SOLO VALE PREORDEN
	Arbol izquierdo, derecho;

	if(raiz==NULL) return NULL;
	else{
		izquierdo=anula(raiz->izq);
		derecho=anula(raiz->der);
		free(raiz);
		raiz=NULL;
		return raiz;
	}
}


int sustituye(Arbol raiz, tipoInfo x, tipoInfo y){	// VALE CUALQUIER ORDEN
	int sustituciones=0;

	if(raiz==NULL) return 0;
	else{
		sustituciones+=sustituye(raiz->izq,x,y);
		sustituciones+=sustituye(raiz->der,x,y);
		if(raiz->info==x){
			raiz->info=y;
			sustituciones+=1;
		}
		return sustituciones;
	}
}


int numNodosHoja(Arbol raiz){		// VALE CUALQUIER ORDEN
	if(raiz==NULL) return 0;
	else{
		if(altura(raiz) == 0) return 1 + numNodosHoja(raiz->izq) + numNodosHoja(raiz->der);
		else return numNodosHoja(raiz->izq) + numNodosHoja(raiz->der);
	}
	
	/*
	if(raiz != NULL){
		int izq = numNodosHoja(raiz->izq);
		int der = numNodosHoja(raiz->der);
		
		if(raiz->izq == NULL && raiz->der == NULL) return (1 + izq + der);
		else return 0;
	}
	
	else return 0;
	
	*/
}


int numNodosInternos(Arbol raiz){
	if(raiz==NULL) return 0;
	else{
		if(altura(raiz) > 0) return 1 + numNodosInternos(raiz->izq) + numNodosInternos(raiz->der);
		else return numNodosInternos(raiz->izq) + numNodosInternos(raiz->der);
	}
	
	/*
	if(raiz != NULL){
		int izq = numNodosInternos(raiz->izq);
		int der = numNodosInternos(raiz->der);
		
		if(raiz->izq != NULL || raiz->der != NULL) return (1 + izq + der);
		else return 0;
	}
	
	else return 0;
	
	*/
}


int numHijoUnico(Arbol raiz){
	if(raiz==NULL) return 0;
	else{
		if((raiz->izq==NULL && raiz->der!=NULL) || (raiz->izq!=NULL && raiz->der==NULL)) return 1 + numHijoUnico(raiz->izq) + numHijoUnico(raiz->der);
		else return numHijoUnico(raiz->izq) + numHijoUnico(raiz->der);
	}
}


Arbol buscarMax(Arbol raiz){
	Arbol izquierdo, derecho, max = raiz;

	if(raiz==NULL) return NULL;
	else{
		izquierdo = buscarMax(raiz->izq);
		derecho = buscarMax(raiz->der);
		if(izquierdo!=NULL && izquierdo->info > max->info) max = izquierdo;
		if(derecho!=NULL && derecho->info > max->info) max = derecho;
		return max;
	}
}


Arbol buscarMin(Arbol raiz){
	Arbol izquierdo, derecho, min = raiz;

	if(raiz==NULL) return NULL;
	else{
		izquierdo = buscarMin(raiz->izq);
		derecho = buscarMin(raiz->der);
		if(izquierdo!=NULL && izquierdo->info < min->info) min = izquierdo;
		if(derecho!=NULL && derecho->info < min->info) min = derecho;
		return min;
	}
}


int similares(Arbol r1,Arbol r2){
	if(r1==NULL && r2==NULL) return 1;
	else if(r1!=NULL && r2!=NULL) return similares(r1->izq,r2->izq) * similares(r1->der,r2->der);
	else return 0;
}


int equivalentes(Arbol r1,Arbol r2){
	if(r1==NULL && r2==NULL) return 1;
	else if(r1!=NULL && r2!=NULL){
		if(r1->info!=r2->info) return 0;
		else return equivalentes(r1->izq,r2->izq) * equivalentes(r1->der,r2->der);
	}
	else return 0;
}


Arbol especular(Arbol raiz){
	tipoNodo *temp;
	
	if(raiz!=NULL){
		if(raiz->izq != NULL && raiz->der != NULL){
			especular(raiz->izq);
			especular(raiz->der);
		
			temp = raiz->izq;
			raiz->izq = raiz->der;
			raiz->der = temp;
			
			return raiz;
		}
	}
}
