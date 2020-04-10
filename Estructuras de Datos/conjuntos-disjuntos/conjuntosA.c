#include "conjuntos.h"
#include <stdio.h>

/// Incluir aqui las funciones que implementan las tres operaciones básicas 
/// en la representación de CONJUNTOS DISJUNTOS mediante ÁRBOLES
/// ......................................................................

void crea(particion C){
	tipoConjunto i;
	
	//UNION POR ALTURA
	for(i=0; i<MAXIMO_C; i++) C[i] = 0; //Altura inicial = 0
	
	//UNION POR TAMANIO
	//for(i=0; i<MAXIMO_C; i++) C[i] = -1; //Tamanio inicial = 1
	
	//PRIMERA SOLUCION
	/*for(i=0; i<MAXIMO_C; i++) C[i] = i;*/
}

tipoElemento buscar(tipoElemento x, particion C){
	//COMPRESION DE CAMINOS
	if(C[x] <= 0) return x;
	else{
		C[x] = buscar(C[x], C);
		return C[x];
	}
	
	//UNION POR ALTURA
	/*if(C[x] <= 0) return x;
	else buscar(C[x], C);*/
	
	//UNION POR TAMANIO
	/*if(C[x] < 0) return x;
	else buscar(C[x], C);*/
	
	//PRIMERA SOLUCION
	/*if(C[x] == x) return x;
	else buscar(C[x], C);*/
}

void unir(tipoElemento x, tipoElemento y, particion C){
	//UNION POR ALTURA --> d) Hay que cambiar la Union(11,6) a U(6,11)
	if(C[x] > C[y]){
		C[x] = y;
	}
	else if(C[x] == C[y]){
		C[x]--;
		C[y] = x;
	}
	else{
		C[y] = x;
	}
	
	//UNION POR TAMANIO
	/*if(C[x] > C[y]){
		C[y] += C[x];
		C[x] = y;
	}
	else{
		C[x] += C[y];
		C[y] = x;
	}*/
	
	//PRIMERA SOLUCION
	//C[y] = x;
}


//
// Función auxiliar para ver contenido de Partición 
//
void verParticion(particion C){
	int i;
    	printf("\n");
    
    	for (i =0;i<MAXIMO_C;i++) printf("|%2d",C[i]);
    	printf("| contenido  vector\n");
    
    	for (i =0;i<MAXIMO_C;i++) printf("---");
    	printf("\n");
    
    	for (i =0;i<MAXIMO_C;i++) printf(" %2d",i);
    	printf("  índices vector\n\n");
}
