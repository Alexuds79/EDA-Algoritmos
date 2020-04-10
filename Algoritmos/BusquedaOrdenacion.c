#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define NUM 10
#define LIM 1000

typedef struct tagnodo{ 
	int info;
	struct tagnodo *sig;
} nodo;

int bSecuencial(int * vector, int numElementos, int valor);
int bBinariaI(int * vector, int numElementos, int valor);
int bBinariaR(int * vector, int inicio,int fin, int valor);

int* ordenarBurbuja(int *vector, int numElementos);
int* burbujaE(int *vector, int numElementos);
int* ordenarSeleccion(int *vector, int numElementos);
int* ordenarInsercion(int *vector, int numElementos);
int* ordenarInsercionBin(int *vector, int numElementos);

void QuickSort(int *vector, int base, int tope);
void qsortE(int *vector, int base, int tope);
void qsortMed(int *vector, int base, int tope);
int colocar(int *vector, int base, int tope);
void MergeSort(int *vector, int base, int tope);
void fusion(int *vector, int base, int mitad, int tope);

void intercambiar (int *x, int *y);

void radixSort(nodo **lista,int numGrupos,int numCifras);
nodo * creaLista(int numElementos, int rango);
void verLista(nodo *lista);
void liberarLista(nodo *lista);



int main(int argc, char *argv){
	int i, numGrupos=10, numCifras=5;
	nodo *lista;
	int *vector;
	vector = (int *)malloc(NUM*sizeof(int));
	
	/*-----------------------------------------------------------*/
	printf("\nRADIXSORT | Lista original:\n");
	lista = creaLista(NUM, LIM);
	verLista(lista);
	
	printf("\n\nRADIXSORT | Lista ordenada:\n");
	radixSort(&lista, numGrupos, numCifras);
	verLista(lista);
	liberarLista(lista);
	printf("\n\n===================================================\n");
	
	/*-----------------------------------------------------------*/
	
	
	srand(time(NULL));
	for(i=0; i<NUM; i++){
		vector[i]=rand()%LIM;
	}
	
	printf("\nVECTOR ORIGINAL:\n");
	for(i=0; i<NUM; i++){
		printf("%5d", vector[i]);
	}
	printf("\n");
	
	/*ORDENACIÓN*/ /*Comentar todas menos el que se desea probar*/
	/*--------------------------------------------------------*/
	//ordenarBurbuja(vector, NUM);
	//burbujaE(vector, NUM);
	//ordenarSeleccion(vector, NUM);
	//ordenarInsercion(vector, NUM);
	//ordenarInsercionBin(vector, NUM);
	//QuickSort(vector, 0, NUM);
	//qsortE(vector, 0, NUM);
	//qsortMed(vector, 0, NUM);
	MergeSort(vector, 0, NUM);
	
	printf("\n\nVECTOR ORDENADO:\n");
	for(i=0; i<NUM; i++){
		printf("%5d", vector[i]);
	}
	printf("\n\n===================================================\n");
	/*--------------------------------------------------------*/
	
	/*BÚSQUEDA*/ /*Comentar todas menos la que se desee probar*/
	/*--------------------------------------------------------*/
	printf("\nBUSQUEDA:\n");
	srand(time(NULL));
	int pos;
	int valor = vector[rand()%NUM];
	//pos = bSecuencial(vector, NUM, valor);
	//pos = bBinariaI(vector, NUM, valor);
	pos = bBinariaR(vector, 0, NUM, valor);
	
	printf("| %15s | %15s |\n", "VALOR", "POSICION");
	printf("| %15d | %15d |\n", valor, pos);
	/*--------------------------------------------------------*/
	
	system("PAUSE");
	return 0;
	
}

int bSecuencial(int * vector, int numElementos, int valor){
	
	int i;
	//int posicion=-1;
	
	for(i=0; i<numElementos; i++){
		//if(vector[i] == valor) posicion=i;
		if(vector[i] == valor) return i;
	}
	
	//return posicion;
	return -1;
	
}

int bBinariaI(int * vector, int numElementos, int valor){
	
	int i=0, j=numElementos-1, k;
	
	while(i<j){
		k=(i+j)/2;
		if(valor<vector[k]) j=k-1;
		else if(valor>vector[k]) i=k+1;
		else i=j=k;
	}
	
	if(valor==vector[i]) return i;
	
	return -1;
	
}

int bBinariaR(int * vector, int inicio, int fin, int valor){
	int medio;
	
	if(inicio>fin){
		return -1;
	}
	else{
		medio=(inicio+fin)/2;
		if(valor<vector[medio]) fin=medio-1;
		else if(valor>vector[medio]) inicio=medio+1;
		else return medio;
	}
	
	return bBinariaR(vector,inicio,fin,valor);
	
}

int* burbujaE(int *vector, int numElementos){
	int i, j;
	int flag=1;
	
	for(i=0; i<numElementos && flag==1; i++){
		flag=0;
		for(j=0; j<numElementos-1-i; j++){
			if(vector[j]>vector[j+1]){
				intercambiar(&vector[j], &vector[j+1]);
				flag=1;
			}
		}
	}
	
	return vector;
}

int * ordenarBurbuja(int *vector , int numElementos){
	int i, j;
	
	for(i=0; i<numElementos-1; i++){	//BURBUJEA EL NÚMERO MÁS GRANDE HACIA LA PARTE INFERIOR
		for(j=0; j<numElementos-1-i; j++){
			if(vector[j+1]<vector[j]){
				intercambiar(&vector[j],&vector[j+1]);
			}
		}
	}
	
	/*for(i=0; i<numElementos-1; i++){	//BURBUJEA EL NÚMERO MÁS PEQUEÑO HACIA LA PARTE SUPERIOR
		contadorExterno++;
		for(j=numElementos-1; j>=i; j--){
			contadorInterno++;
			if(vector[j+1]<vector[j]){
				intercambiar(&vector[j],&vector[j+1]);
				contadorAuxiliar1++;
			}
		}
	}*/
	
	return vector;
	
}

void intercambiar (int *x, int *y){
	
	int temp;
	
	temp = *x;
	*x = *y;
	*y = temp;
	
}

int *ordenarSeleccion(int *vector, int numElementos){
	
	int i, j, posicionSeleccion, valorSeleccion;
	
	for(i=0; i<numElementos-1; i++){
		valorSeleccion=vector[i];
		posicionSeleccion=i;
		for(j=i+1; j<numElementos; j++){
			if(vector[j]<valorSeleccion){
				valorSeleccion=vector[j];
				posicionSeleccion=j;
			}
		}
		vector[posicionSeleccion]=vector[i];
		vector[i]=valorSeleccion;
	}
	
	return vector;
	
}

// INSERCIÓN NORMAL

int *ordenarInsercion(int *vector, int numElementos){
	
	int i, j, x;
	
	for(i=1; i<numElementos; i++){
		x=vector[i];
		j=i-1;
		while(j>=0 && vector[j]>x){
			vector[j+1]=vector[j];
			j=j-1;
		}
		vector[j+1]=x;
	}
	
	return vector;
	
}

// INSERCIÓN BINARIA

int *ordenarInsercionBin(int *vector, int numElementos){
	
	int i, j, aux, base, tope, mitad;
	
	for(i=1; i<numElementos; i++){
		aux=vector[i];
		base=0;
		tope=i-1;
		
		while(base<=tope){
			mitad=(base+tope)/2;
			if(aux<=vector[mitad]) tope=mitad-1;
			else base=mitad+1;
		}
		
		for(j=i-1; j>=base; j--){
			vector[j+1]=vector[j];
		}
		
		vector[base]=aux;
		
	}
	
	return vector;
	
}

void QuickSort(int *vector, int base, int tope){	
	int iP;
	
	if(base<tope){
		iP = colocar(vector,base,tope);
		QuickSort(vector,base,iP-1);
		QuickSort(vector,iP+1,tope);
	}
	
	return;
}

void qsortE(int *vector, int base, int tope){
	int iP;
	
	while(base<tope){
		iP=colocar(vector,base,tope);
		qsortE(vector, base, iP-1);
		base=iP+1;
	}
	
	return;
}

void qsortMed(int *vector, int base, int tope){
	int i=base;
	int j=tope;
	int iP=(base+tope)/2;
	int mitad = vector[iP];
	
	do{
		while(vector[i]<mitad) i++;
		while(vector[j]>mitad) j--;
		
		if(i<=j){
			intercambiar(&vector[i], &vector[j]);
			i++;
			j--;
		}
	}while(i<=j);
	
	if(base<j) qsortMed(vector, base, j);
	if(tope>i) qsortMed(vector, i, tope);
}

int colocar(int *vector, int base, int tope){
	
	int i, iP, pivote;
	
	iP=base;
	pivote=vector[base];
	
	for(i=base+1; i<=tope; i++){
		if(vector[i]<pivote){
			iP=iP+1;
			intercambiar(&vector[i],&vector[iP]);
		}
	}
	
	intercambiar(&vector[base],&vector[iP]);
	
	return iP;
	
}

void MergeSort(int *vector, int base, int tope){ 
    if (base < tope){ 
        int mitad = base+(tope-base)/2; 
        MergeSort(vector, base, mitad); 
        MergeSort(vector, mitad+1, tope); 
        fusion(vector, base, mitad, tope); 
    } 
}

void fusion(int *vector, int base, int mitad, int tope){ 
    int i, j, k; 
    int diml = mitad-base+1; 
    int dimr = tope-mitad; 
  
    int L[diml], R[dimr]; 
  
    for (i=0; i<diml; i++) L[i] = vector[base+i]; 
    for (j=0; j<dimr; j++) R[j] = vector[mitad+1+j]; 
  
    i = 0;
    j = 0; 
    k = base;
    
    while (i<diml && j<dimr){ 
        if (L[i]<=R[j]) vector[k++] = L[i++];  
        else vector[k++] = R[j++];
    } 
  
    while (i<diml) vector[k++] = L[i++]; 
	while (j<dimr) vector[k++] = R[j++];  
}

void radixSort(nodo **lista,int numGrupos,int numCifras){
	
	int i, k, anterior, pot10=1;
	nodo **grupos, **ultimos, *aux;

	grupos=malloc(numGrupos*sizeof(nodo*));
	ultimos=malloc(numGrupos*sizeof(nodo*));
	
	for(i=1; i<=numCifras; i++){
		
		// INICIALIZACIÓN DE GRUPOS
		
		for(k=0; k<numGrupos; k++){
			grupos[k]=NULL;
			ultimos[k]=NULL;
		}
		
		// FUNCIÓN DISTRIBUIR
		
		aux=*lista;
		
		while(aux!=NULL){
			k = (aux->info)%(pot10*10)/pot10;
			if(grupos[k]==NULL){
				grupos[k]=aux;
				ultimos[k]=aux;
			}
			else{
				ultimos[k]->sig=aux;
				ultimos[k]=aux;
			}
			aux=aux->sig;
		}
		
		*lista=NULL;
		
		//FUNCION CONCATENAR
		
		for(k=0; k<numGrupos; k++){
			if(grupos[k]!=NULL){
				if(*lista==NULL) *lista=grupos[k];
				else (ultimos[anterior])->sig=grupos[k];
				anterior=k;
			}	
		}
		
		(ultimos[anterior])->sig=NULL;
		pot10*=10;
		
	}
	
}

nodo *creaLista(int n, int rango){
	
	int i;
	nodo *lista=NULL, *aux, *anterior=NULL;
	
	for(i=0; i<n; i++){
		aux=malloc(sizeof(nodo));
		aux->info=rand()%rango;
		if(lista==NULL){
			lista=aux;
			lista->sig=NULL;
			anterior=aux;
		}
		else{
			anterior->sig=aux;
			anterior=aux;
		}
		aux->sig = NULL;
	}
	
	return lista;
	
}

void verLista(nodo *lista){
	nodo *aux;
	
	aux=lista;
	
	while(aux!=NULL){
		printf("%d ",aux->info);
		aux=aux->sig;
	}
	
}

void liberarLista(nodo *lista){
	
	nodo *aux, *borrar;
	
	aux=lista;
	
	while(aux!=NULL){
		borrar=aux;
		aux=aux->sig;
		free(borrar);
	}
	
}
