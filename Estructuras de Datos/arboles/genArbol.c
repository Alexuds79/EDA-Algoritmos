#include "genArbol.h"
#include<stdio.h>
#include "pila.h"

Arbol genArbol(char *exPostfija){
	Arbol a;
	Pila p;
	int i;
	char c;
	
	pilaCreaVacia(&p);
	c = exPostfija[0];
	i=0;
	
	while(c!='\0'){
		if(c==42 || c==43 || c==45 || c==47){ //* + - /
			a = creaNodo(c);
			a->der = pilaSuprime(&p);
			a->izq = pilaSuprime(&p);
			pilaInserta(a, &p);
		}
		else{
			a = creaNodo(c);
			pilaInserta(a, &p);
		}
	
		i++;
		c=exPostfija[i];
	}
	
	return pilaSuprime(&p);
}

int evaluar(Arbol a){ //POSTORDEN
	int izq, der;

	if(a==NULL){
		printf("Estoy en un nodo nulo\n");
		return 0;
	}
	else{ 
		izq = evaluar(a->izq);
		der = evaluar(a->der);
	
		printf("IZQ -> %d\t", izq);
		printf("DER -> %d\n", der);
			
		if(a->izq == NULL && a->der == NULL){ //Es un nodo hoja: es un numero
			printf("Estoy en el nodo con clave %d\n", a->info-48);
			return a->info-48;
		}
		else{ //Es un nodo interno: es un operador
			printf("Estoy en el nodo con clave %c\n", a->info);
			switch(a->info){
				case '+':
					return izq+der;
				break;
				
				case '-':
					return izq-der;
				break;
				
				case '*':
					return izq*der;
				break;
				
				case '/':
					return izq/der;
				break;
			}
		}
	}
}






























