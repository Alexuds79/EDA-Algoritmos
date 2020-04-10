#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "lista.h"

int creaVacia(Lista *l){
    if (l == NULL)
        return -2;
    else if (NULL == (l->raiz = l->ultimo = (tipoCelda *)malloc(sizeof(tipoCelda))))
        return -1;
    else {
        l->raiz->sig = NULL;
        return 0;
    }
}


int vacia(Lista *l){
    if (l == NULL || l->raiz == NULL) {
        return -1;
    }
    else if (l->raiz->sig == NULL)
        return 1;
    else
        return 0;
}

int destruye(Lista *l) {
    if (l == NULL || l->raiz == NULL) {
        return -1;
    }
    else if (l->raiz->sig != NULL){
        return -2;
    }
    else {
        free(l->raiz);
        l->raiz = l->ultimo = NULL;
        return 0;
    }
}


void imprime(Lista *l) {
    tipoCelda *aImprimir;
    int posicion;
    
    if (l == NULL || l->raiz == NULL) {
        return;
    }
    else {
        posicion = 1;
        aImprimir = l->raiz->sig;
        while (aImprimir != NULL) {
            printf("Valor: %d en posición: %d\n",aImprimir->elemento, posicion++);
            aImprimir = aImprimir->sig;
        }
        printf("%d valores en la lista\n",posicion-1);
    }
}

tipoPosicion anterior(tipoPosicion p, Lista *l) {
    tipoCelda *anterior;
    
    if (l == NULL || l->raiz == NULL || p == NULL) {
        return NULL;
    }
    else if (p == l->raiz){
        return l->raiz;
    }
    else {
        anterior = l->raiz;
        while (anterior->sig != p)
            anterior = anterior->sig;
        return anterior;
    }
}


tipoPosicion primero(Lista *l) {
   if(l==NULL || l->raiz==NULL) return NULL;
   else return l->raiz;
    
}



tipoPosicion fin(Lista *l) {
   if(l==NULL || l->raiz==NULL) return NULL;
   else return l->ultimo;
}




int inserta(tipoElemento x, tipoPosicion p, Lista *l) {
	if(l==NULL || l->raiz==NULL || p==NULL){
   		return -1;
   	}
   	else{
   		tipoPosicion nuevo; //tipoCelda *nuevo;
   		nuevo=malloc(sizeof(tipoCelda));
   			
   		if(nuevo==NULL) return -1;
   			
   		nuevo->elemento=x;
   		nuevo->sig=p->sig;
   		p->sig=nuevo;
   		
   		if(p==fin(l)) l->ultimo=nuevo;
   	}
   		
   	return 0;
}


int suprime (tipoPosicion p, Lista *l) {
	if(vacia(l) || p==NULL){
   		return -1;
   	}
   	else{
   		tipoPosicion aBorrar; //tipoCelda *aBorrar;
   		
   		if(p==fin(l)){ //Se decide por razones de implementación borrar el último elemento
   			p=anterior(fin(l), l);
   			
   		}
   		aBorrar=p->sig;
   		p->sig=aBorrar->sig;
   		if(p->sig==NULL) l->ultimo=p;
   		free(aBorrar);
   		
   	}
   		
   	return 0;
}



tipoPosicion siguiente(tipoPosicion p, Lista *l) {
	if(l==NULL || l->raiz==NULL || p==NULL){
   		return NULL;
   	}
   	else if(p==fin(l)){
   		return l->ultimo;
   	}
   	else{
   		return p->sig;
   	}
   		
   	return 0;
}




tipoPosicion localiza (tipoElemento x, Lista *l) {
	if(vacia(l)){
   		return NULL;
   	}
   	else{
   		tipoPosicion aux;
   		aux = l->raiz;
   		
   		while(aux->sig!=NULL && (aux->sig)->elemento!=x){
   			aux=aux->sig;
   		}
   		if(aux->sig==NULL) return l->ultimo;
   		else return aux->sig;
   	}
}



tipoElemento recupera(tipoPosicion p, Lista *l) {
	if(vacia(l) || p==NULL){
   		return -1;
   	}
   	else{
   		if(p==fin(l)) return p->elemento;
   		else return (p->sig)->elemento;
   	}  
}


int anula(Lista *l) {
	if(vacia(l)){
   		return -1;
   	}
   	else{
   		tipoPosicion aBorrar;
   		aBorrar=l->raiz;
   		while(aBorrar->sig!=NULL){
   			suprime(aBorrar, l);
   		}
   	} 
}
