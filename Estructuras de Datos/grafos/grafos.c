#include <stdio.h>
#include <stdlib.h>
#include "cola.h"
#include "grafos.h"
#include "monticulo.h"
#include "conjuntos.h"

/*EJERCICIO 4. Grafos no dirigidos*/
int esConexo(tipoGrafo *grafo){
	Monticulo m;
	particion C;
	pArco p;
	int i, numAristasAceptadas=0;
	tipoConjunto U,V;
	tipoElementoM x;
	
	if(grafo == NULL) return 0;
	iniciar(grafo);
	
	crea(C);
	iniciaMonticulo(&m);
	
	//Construir monticulo de aristas
	for(i=1; i<=grafo->orden; i++){
		p = grafo->directorio[i].lista;
		while(p!=NULL){
			x.clave = p->peso;
			x.origen = i;
			x.destino = p->v;
			x.informacion = 0;
			
			insertar(x, &m);
			p=p->sig;
		}
	}
	
	i=0;
	while(numAristasAceptadas < grafo->orden-1 && i<=MAXIMO_C){
		eliminarMinimo(&m, &x);
		U = buscar(x.origen, C);
		V = buscar(x.destino, C);
		if(U != V){
			unir(U, V, C);
			x.informacion=1;
			numAristasAceptadas++;
		}
		i++;
	}
	
	verParticion(C);
	
	if(numAristasAceptadas == grafo->orden-1) return 1;
	else return 0;
}

tipoGrafo* prim1(tipoGrafo *grafo){
	int vIni = 1, i, j, v, w;
	pArco p;
	
	if(grafo==NULL) return NULL;
	iniciar(grafo);
	
	grafo->directorio[vIni].peso=0;
	//grafo->directorio[vIni].anterior = 0; <<ya lo puso iniciar>>
	
	for(i=1; i<=grafo->orden; i++){
		v=0;
		for(j=1; j<=grafo->orden; j++){
			if(!grafo->directorio[j].alcanzado && (v==0 || grafo->directorio[j].peso < grafo->directorio[v].peso)){
				v = j;
			}
		}
		
		grafo->directorio[v].alcanzado = 1;
		
		p = grafo->directorio[v].lista;
		while(p!=NULL){
			w = p->v;
			
			if(!grafo->directorio[w].alcanzado){
				if(grafo->directorio[w].peso > p->peso){
					grafo->directorio[w].peso = p->peso;
					grafo->directorio[w].anterior = v;
				}
			}
			
			p = p->sig;
		}
	}
	
	liberarListas(grafo);
	
	/*************** CREACION LISTA ADYACENCIA *******************/
	//Insertar anteriores
	for(i=1; i<=grafo->orden; i++){
		p = (arco *)calloc(1, sizeof(arco));
		p->v = grafo->directorio[i].anterior;
		p->peso = grafo->directorio[i].peso;
		if(p->v != 0) grafo->directorio[i].lista = p;
	}
	
	//Insertar el actual en la lista del anterior
	int vAnterior;
	pArco aux;
	for(i=1; i<=grafo->orden; i++){
		vAnterior = grafo->directorio[i].anterior;
		p = (arco *)calloc(1, sizeof(arco));
		p->v = i;
		p->peso = grafo->directorio[i].peso;
		
		if(grafo->directorio[vAnterior].lista == NULL) grafo->directorio[vAnterior].lista = p;
		else{
			aux = grafo->directorio[vAnterior].lista;
			grafo->directorio[vAnterior].lista = p;
			grafo->directorio[vAnterior].lista->sig = aux;
		}
	}
	/*****************************************************/
	
	return grafo;
}

tipoGrafo* prim2(tipoGrafo *grafo){
	int i, v, w;
	pArco p;
	Monticulo m;
	tipoElementoM x, minimo;
	int vInicio=1;
	
	if(grafo==NULL) return NULL;
	iniciar(grafo);
	
	grafo->directorio[vInicio].peso= 0;
	//grafo->directorio[vInicio].anterior = 0; <<ya lo puso iniciar>>
	
	iniciaMonticulo(&m);
	x.clave = 0;
	x.informacion = vInicio;
	insertar(x, &m);
	
	while(!vacioMonticulo(m)){
		eliminarMinimo(&m, &x);
		
		if(!grafo->directorio[x.informacion].alcanzado){
			v = x.informacion;
			grafo->directorio[v].alcanzado = 1;
			
			p = grafo->directorio[v].lista;
			while(p!=NULL){
				w = p->v;
				
				if(!grafo->directorio[w].alcanzado){
					if(grafo->directorio[w].peso > p->peso){
						grafo->directorio[w].peso = p->peso;
						grafo->directorio[w].anterior = v;
						x.clave = grafo->directorio[w].peso;
						x.informacion = w;
						insertar(x, &m);
					}
				}
				
				p=p->sig;
			}
		}
	}
	
	liberarListas(grafo);
	
	/*************** CREACION LISTA ADYACENCIA *******************/
	//Insertar anteriores
	for(i=1; i<=grafo->orden; i++){
		p = (arco *)calloc(1, sizeof(arco));
		p->v = grafo->directorio[i].anterior;
		p->peso = grafo->directorio[i].peso;
		if(p->v != 0) grafo->directorio[i].lista = p;
	}
	
	//Insertar el actual en la lista del anterior
	int vAnterior;
	pArco aux;
	for(i=1; i<=grafo->orden; i++){
		vAnterior = grafo->directorio[i].anterior;
		p = (arco *)calloc(1, sizeof(arco));
		p->v = i;
		p->peso = grafo->directorio[i].peso;
		
		if(grafo->directorio[vAnterior].lista == NULL) grafo->directorio[vAnterior].lista = p;
		else{
			aux = grafo->directorio[vAnterior].lista;
			grafo->directorio[vAnterior].lista = p;
			grafo->directorio[vAnterior].lista->sig = aux;
		}
	}
	/*****************************************************/
	
	return grafo;
}

tipoGrafo* kruskal(tipoGrafo *grafo){
	Monticulo m;
	particion C;
	pArco p;
	int i, j, numAristasAceptadas=0;
	tipoConjunto U,V;
	tipoElementoM x;
	
	tipoGrafo *arbolExp;
	arbolExp = (tipoGrafo *)calloc(1, sizeof(tipoGrafo));
	arbolExp->orden = ORDEN;
	iniciar(arbolExp);
	
	if(grafo == NULL) return NULL;
	iniciar(grafo);
	
	crea(C);
	iniciaMonticulo(&m);
	
	//Construir monticulo de aristas
	for(i=1; i<=grafo->orden; i++){
		p = grafo->directorio[i].lista;
		while(p!=NULL){
			x.clave = p->peso;
			x.origen = i;
			x.destino = p->v;
			x.informacion = 0;
			
			insertar(x, &m);
			p=p->sig;
		}
	}
	
	while(numAristasAceptadas < grafo->orden-1){
		eliminarMinimo(&m, &x);
		U = buscar(x.origen, C);
		V = buscar(x.destino, C);
		if(U != V){
			unir(U, V, C);
			numAristasAceptadas++;
			x.informacion=1;
			
			/*************** CREACION LISTA ADYACENCIA *******************/
			pArco aux;
			
			p = (arco *)calloc(1, sizeof(arco));
			p->v = x.origen;
			p->peso = x.clave;
			if(arbolExp->directorio[x.origen].lista == NULL) arbolExp->directorio[x.destino].lista = p;
			else{
				aux = arbolExp->directorio[x.destino].lista;
				arbolExp->directorio[x.destino].lista = p;
				arbolExp->directorio[x.destino].lista->sig = aux;
			}
			
			p = (arco *)calloc(1, sizeof(arco));
			p->v = x.destino;
			p->peso = x.clave;
			
			if(arbolExp->directorio[x.origen].lista == NULL) arbolExp->directorio[x.origen].lista = p;
			else{
				aux = arbolExp->directorio[x.origen].lista;
				arbolExp->directorio[x.origen].lista = p;
				arbolExp->directorio[x.origen].lista->sig = aux;
			}
			/*****************************************************/
		}
	}
	
	return arbolExp;
}

/*EJERCICIO 3. Grafos dirigidos*/
void caminos1(int vInicio, tipoGrafo *g){
	int i, distActual, w;
	pArco p;
	
	if(g==NULL) return;
	
	iniciar(g);
	g->directorio[vInicio].distancia = 0;
	//g->directorio[vInicio].anterior = 0; //no hace falta, iniciar ya lo pone a 0
	
	for(distActual=0; distActual<g->orden; distActual++){ //ojo!
		for(i=1; i<=g->orden; i++){
			if(!g->directorio[i].alcanzado && g->directorio[i].distancia == distActual){
				g->directorio[i].alcanzado = 1;
				
				p = g->directorio[i].lista;
				while(p!=NULL){
					w = p->v;
					
					if(g->directorio[w].distancia == INF){
						g->directorio[w].distancia = g->directorio[i].distancia+1;
						g->directorio[w].anterior = i;
					}
					
					p = p->sig;
				}
			}
		}
	}
}

void caminos2(int vInicio, tipoGrafo *g){
	int i, w;
	Cola c;
	pArco p;
	
	if(g==NULL) return;
	
	iniciar(g);
	g->directorio[vInicio].distancia = 0;
	//g->directorio[vInicio].anterior = 0 <<iniciar ya lo había puesto a 0>>
	
	colaCreaVacia(&c);
	colaInserta(vInicio, &c);
	
	while(!colaVacia(&c)){
		i = colaSuprime(&c);
		g->directorio[i].alcanzado = 1; //No hace falta
		
		p = g->directorio[i].lista; 
		
		while(p!=NULL){
			w = p->v;
			
			if(g->directorio[w].distancia == INF){
				g->directorio[w].distancia = g->directorio[i].distancia + 1;
				g->directorio[w].anterior = i;
				colaInserta(w, &c);
			}
			
			p = p->sig;
		}
	}
}

void dijkstra1(int vInicio, tipoGrafo *g){
	int i, j, v, w;
	pArco p;
	
	if(g==NULL) return;
	
	iniciar(g);
	g->directorio[vInicio].distancia = 0;
	//g->directorio[vInicio].anterior = 0 <<iniciar ya lo puso a 0>>
	
	for(i=1; i<=g->orden; i++){
		v = 0;
		for(j=1; j<=g->orden; j++){
			if(!g->directorio[j].alcanzado && (v==0 || g->directorio[j].distancia < g->directorio[v].distancia)){
				v=j;
			}
		}
		g->directorio[v].alcanzado = 1;
		
		p = g->directorio[v].lista;
		while(p!=NULL){
			w = p->v;
						
			if(!g->directorio[w].alcanzado){
				if(g->directorio[v].distancia + p->peso < g->directorio[w].distancia){
					g->directorio[w].distancia = g->directorio[v].distancia + p->peso;
					g->directorio[w].anterior = v;
				}
			}
			
			p = p->sig;
		}
	}

}

void dijkstra2(int vInicio, tipoGrafo *g){
	int i, v, w;
	pArco p;
	Monticulo m;
	tipoElementoM x, minimo;
	
	if(g==NULL) return;
	iniciar(g);
	
	g->directorio[vInicio].distancia = 0;
	//g->directorio[vInicio].anterior = 0; <<ya lo puso iniciar>>
	
	iniciaMonticulo(&m);
	x.clave = 0;
	x.informacion = vInicio;
	insertar(x, &m);
	
	while(!vacioMonticulo(m)){
		eliminarMinimo(&m, &x);
		
		if(!g->directorio[x.informacion].alcanzado){
			v = x.informacion;
			g->directorio[v].alcanzado = 1;
			
			p = g->directorio[v].lista;
			while(p!=NULL){
				w = p->v;
				
				if(!g->directorio[w].alcanzado){
					if(g->directorio[v].distancia + p->peso < g->directorio[w].distancia){
						g->directorio[w].distancia = g->directorio[v].distancia + p->peso;
						g->directorio[w].anterior = v;
						x.clave = g->directorio[w].distancia;
						x.informacion = w;
						insertar(x, &m);
					}
				}
				
				p=p->sig;
			}
		}
	}
}

int costeyTrayectoria(int vIni, int vFin, tipoGrafo *g){
	int v, i=1, j;
	int recorrido[g->orden];
	
	//Obligatorio haber aplicado Dijkstra antes
	for(j=0; j<g->orden; j++) recorrido[j] = -1; 
	
	v = vFin;
	recorrido[0] = v;
	
	while(v!=vIni && v!=0){
		v = g->directorio[v].anterior;
		recorrido[i++] = v;
	}
	
	if(v!=0){
		for(j=g->orden-1; j>=0; j--){
			if(recorrido[j] == -1) continue;
			printf("%d ", recorrido[j]);
		}
	}
	
	return g->directorio[vFin].distancia;

}

//Obligatorio haber aplicado Dijkstra antes
int costeyTrayectoriaRec(int vIni, int vFin, tipoGrafo *g){
	
	if(g->directorio[vFin].distancia == INF) return INF;
	else{
		if(vFin!=0){
			costeyTrayectoriaRec(vIni, g->directorio[vFin].anterior, g); //costeyTrayectoria(vIni, g->directorio[vFin].anterior, g);
			printf("%d ", vFin);
			return g->directorio[vFin].distancia;
		}
		else return 0;
	}
}

void todosCaminosMin(int vIni, tipoGrafo *g){
	int i, distancia;
	
	dijkstra1(vIni, g);
	
	for(i=1; i<=g->orden; i++){
		distancia = costeyTrayectoriaRec(vIni, i, g);
		if (distancia!=INF) printf("Camino de coste %d \n", distancia);	
		else printf("No existe camino de %d a %d \n",vIni,i);
	}
}

/*EJERCICIO 2*/
int ordenTop1(tipoGrafo *grafo){
	int i, j, flag=0;
	pArco p;
	int v, w;
	
	if(grafo==NULL) return -1;
	iniciar(grafo);
	
	for(j=1; j<=grafo->orden; j++){
		flag=0;
		/*** Buscar vertice OrdenTop = 0 ***/
		for(i=1; i<=grafo->orden; i++){
			if(grafo->directorio[i].gradoEntrada == 0 && !grafo->directorio[i].alcanzado){
				flag = 1;
				grafo->directorio[i].alcanzado=1;
				v = i;
				break;
			}
		}
		
		if(flag==0) return -1; //hay un ciclo!!!
		/**********************************/
		
		grafo->directorio[i].ordenTop = j;
		p = grafo->directorio[v].lista;
		
		while(p!=NULL){
			w = p->v;
			grafo->directorio[w].gradoEntrada -= 1;
			p=p->sig;
		}
	}
}

int ordenTop2(tipoGrafo *grafo){
	int i;
	Cola c;
	int v, w;
	pArco p;
	int orden=1;
	
	if(grafo == NULL) return -1;
	
	colaCreaVacia(&c);
	iniciar(grafo);
	
	for(i=1; i<=grafo->orden; i++){
		if(grafo->directorio[i].gradoEntrada == 0) colaInserta(i, &c);
	}
	
	if(colaVacia(&c)) return -1; //Hay un ciclo!!!
	
	while(!colaVacia(&c)){
		v = colaSuprime(&c);
		grafo->directorio[v].ordenTop = orden++;
		
		p = grafo->directorio[v].lista;
		while(p!=NULL){
			w = p->v;
			grafo->directorio[w].gradoEntrada -= 1;
			if(grafo->directorio[w].gradoEntrada == 0) colaInserta(w, &c);
			p = p->sig;
		}
	}
	
	if(orden != grafo->orden+1) return -1; //Hay un ciclo!!!
}

void liberarListas(tipoGrafo *g){
	int i;
	pArco aBorrar, p;
	
	if(g==NULL) return;
	
	for(i=1; i<=g->orden; i++){
		p = g->directorio[i].lista;
	
		while(p!=NULL){
			aBorrar = p;
			p = p->sig;
			free(aBorrar);
		}
		g->directorio[i].lista = NULL;
	}
}

/*EJERCICIO 1*/
void iniciar(tipoGrafo *g){
	int i, j;
	pArco p;
	
	if(g==NULL) return;
	
	for(i=1; i<=g->orden; i++){
		g->directorio[i].alcanzado = 0;
	  	g->directorio[i].gradoEntrada = 0;
	  	g->directorio[i].ordenTop = 0;
	  	g->directorio[i].distancia = INF;
	  	g->directorio[i].peso = INF;
	  	g->directorio[i].anterior = 0;
	  	
   		for(j=1; j<=g->orden; j++){
   			p = g->directorio[j].lista;
	   		while (p != NULL){
	       			if(p->v == i) g->directorio[i].gradoEntrada += 1;		
	       			p = p->sig;
	       		}
       		}
   	}
}

void profundidadMejorado(int v_inicio, tipoGrafo * grafo){
	int w, i;
  	pArco  p;
  	
  	if(grafo==NULL) return;
  
  	printf("%d ", v_inicio);
  
  	grafo->directorio[v_inicio].alcanzado = 1;
  	p = grafo->directorio[v_inicio].lista;
  
  	while (p!=NULL){
  		w = p->v;
    
    		if (!grafo->directorio[w].alcanzado) profundidadMejorado(w, grafo);
    		p = p->sig;
  	}
  	
  	for(i=1; i<=grafo->orden; i++){
  		if(!grafo->directorio[i].alcanzado) profundidadMejorado(i, grafo);
  	}
}

// Recorrido en PROFUNDIDAD de un grafo. ¡CUIDADO! Depende del vertice inicial y del tipo de grafo
void profundidad(int v_inicio, tipoGrafo * grafo){
	int w;
  	pArco  p;
  	
  	if(grafo==NULL) return;
  
  	printf("%d ",v_inicio);
  
  	grafo->directorio[v_inicio].alcanzado=1;
  	p = grafo->directorio[v_inicio].lista;
  
  	while (p!=NULL){
  		w=p->v;
    
    		if (!grafo->directorio[w].alcanzado) profundidad(w,grafo);
    		p = p->sig;
  	}
}


//Recorrido en AMPLITUD de un grafo. ¡CUIDADO! Depende del vertice inicial y del tipo de grafo
void amplitud(int v_inicio, tipoGrafo *grafo){
	int w, i;
  	pArco  p;
  	Cola c;
  	
  	if(grafo==NULL) return;

  	colaCreaVacia(&c);
  	colaInserta(v_inicio, &c);
  	
  	while (!colaVacia(&c)){
		w =colaSuprime(&c);
        
        	if (!grafo->directorio[w].alcanzado){
			printf("%d ",w);
	        	grafo->directorio[w].alcanzado=1;
        		p =grafo->directorio[w].lista;
        		
 			while (p!=NULL){
				w = p->v;
				colaInserta(w,&c);
				p = p->sig;
			}
		}
  	}
  	
  	//Amplitud mejorado (no venía en la versión original)
  	for(i=1; i<=grafo->orden; i++){
  		if(!grafo->directorio[i].alcanzado) amplitud(i, grafo);
  	}	  
}


//Función auxiliar para ver el contenido de la estructura que representa un grafo en memoria
void verGrafo(tipoGrafo *g){
	int i;
   	pArco p;
   	
   	if(g==NULL) return;

   	printf("\nGrafo  (Orden %d)\n\n", g->orden);
   	printf("       alc gEnt oTop dist peso ant \n");
   	printf("     +----+----+----+----+----+----+\n");

   	for(i=1;i<=g->orden;i++){
   		printf("  %2d | %2d | %2d | %2d |", i, g->directorio[i].alcanzado, g->directorio[i].gradoEntrada, g->directorio[i].ordenTop);
       
       		if (g->directorio[i].distancia == INF) printf("  * |");
       		else printf(" %2d |", g->directorio[i].distancia);
       
       		if (g->directorio[i].peso == INF) printf("  * |");
       		else printf(" %2d |", g->directorio[i].peso);
       
       		printf(" %2d |",g->directorio[i].anterior);
      		p = g->directorio[i].lista;
      		
       		while (p != NULL){
       			//printf(" ->%2d", p->v);	// Grafos no ponderados
           		printf(" ->%2d, %2d", p->v, p->peso); // Grafos ponderados
           		p = p->sig;
       		}
       		
       		printf("\n");
   	}
   
	printf("     +----+----+----+----+----+----+\n\n");
}



