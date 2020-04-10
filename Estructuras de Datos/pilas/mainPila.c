#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

int main(int argc, char *argv[]){
	Pila pila;
	char c1, c2;
	//char cadena[] = {"[{(4+56*7)}]"};
	int i=0;
	char cadena[100];
	
	printf("Ingrese una operacion aritmetica: ");
	scanf("%s", cadena);
	
	pilaCreaVacia(&pila);	
	c1 = cadena[0];
	
	while(c1!='\0'){
		if(c1!='[' && c1!='{' && c1!='(' && c1!=']' && c1!='}' && c1!=')'){
			c1 = cadena[++i];
			continue;
		}
		else if(c1=='[' || c1=='{' || c1=='('){
			pilaInserta(c1, &pila);
		}
		else{
			if(pilaVacia(&pila)){
				printf("Secuencia ilegal\n");
				return -1;
			}
			else{
				c2=pilaSuprime(&pila);
				if( (c2 == '[' && c1!= ']') && (c2 == '{' && c1!= '}') && (c2 == '(' && c1!= ')')){
					printf("Secuencia ilegal\n");
					return -1;
				}
			}
		}
		c1 = cadena[++i];
	}
	
	if(!pilaVacia(&pila)){
		printf("Secuencia ilegal\n");
		return -1;
	}
	else printf("Secuencia legal\n");
	
	return 0;
}
