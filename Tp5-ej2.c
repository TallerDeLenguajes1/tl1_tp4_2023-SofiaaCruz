#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

typedef struct Tarea{
    int tareaID;
    char *descripcion;
    int duracion;
} tarea;

typedef struct Nodo{
    tarea t;
    struct Nodo *sig;
} nodo;

nodo *crear_lista_vacia();

tarea cargar_tarea(int id);

nodo *crear_Nodo(tarea Ntarea);

void insertar_nodo(nodo **lista, nodo *nuevoNodo);

void mostrar_tareas(nodo *tarea);

void mostrar_lista (nodo *lista);

void mover_tarea(nodo **lista1, nodo **lista2, int id);

nodo *busqueda_ID (nodo **lista1, int id);

nodo *busqueda_palabra (nodo **lista1,  char *palabra);

void eliminar_tarea(int valor, nodo **lista);

void mostrar_datos (nodo *lista);

void liberar_memoria(nodo ** lista);

/****FUNCION PRINCIPAL****/

int main(){

    int resp, id=1, IDbusq, op, eliminar, auxID;
    nodo *pendiente, *realizada, *tareasEnProceso, *busq, *todasT;
    pendiente = crear_lista_vacia();
    realizada = crear_lista_vacia();
    tareasEnProceso = crear_lista_vacia();

    do{
        printf("\n\n>>>>MENU<<<<");
        printf("\nElija una opcion");
        printf("\n1- Agregar tarea");
        printf("\n2- Modificar lista de tarea");
        printf("\n3- Mostrar tareas ");
        printf("\n4- Buscar tarea");
        printf("\n0- Salir");
        printf("\n>> ");
        scanf("%d", &op);

        fflush(stdin);

        switch (op){
        case 1 :
                do{

                    insertar_nodo(&pendiente, crear_Nodo(cargar_tarea(id)));

                    insertar_nodo(&todasT, crear_Nodo(pendiente->t));

                    printf("\nDesea cargar otra tarea?\n1-SI\n2-NO\n>> ");
                    scanf("%d", &resp);
                    fflush(stdin);

                    id++;

                }while(resp != 2);
            break;
        case 2:
                printf("\n\nMODIFICAR TAREAS");
                int r;
                int eleccion;
                int mover;
                int aux;

                do{ 
                    
                    printf("\n\nTareas en proceso");
                    mostrar_lista(tareasEnProceso);
                    
                    printf("\n\nTareas pendientes");
                    mostrar_lista(pendiente);   
                    
                    printf("\n\nTareas realizadas");
                    mostrar_lista(realizada);    
                    
                    printf("\n\nDonde se encuentra la tarea que desea seleccionar\n1-Proceso\n2-Pendientes\n3-Realizadas\n>> ");
                    scanf("%d", &eleccion);
                    printf("\n\nIngrese el ID de la tarea que elije\n>> ");
                    scanf("%d", &auxID);
                    printf("\nSeleccione que desea hacer con esa tarea\n1-Mover\n2-Eliminar\n0-Nada\n>> ");
                    scanf("%d", &r);

                    switch (r){
                        case 1:
                            switch(eleccion){
                                case 1:
                                    printf("\nDesea mover la tarea a\n1-Pendiente\n2-Realizada\n>> ");
                                    scanf("%d", &mover);
                                    if(mover == 1){
                                        mover_tarea(&tareasEnProceso, &pendiente, auxID);
                                    }
                                    else{
                                        mover_tarea(&tareasEnProceso, &realizada, auxID);
                                    }
                                break;
                                case 2:
                                    printf("\nDesea mover la tarea a\n1-Proceso\n2-Realizada\n>> ");
                                    scanf("%d", &mover);
                                    if(mover == 1){
                                        mover_tarea(&pendiente, &tareasEnProceso, auxID);
                                    }
                                    else{
                                        mover_tarea(&pendiente, &realizada, auxID);
                                    }
                                break;
                                case 3:
                                    printf("\nDesea mover la tarea a\n1-Proceso\n2-Pendiente\n>> ");
                                    scanf("%d", &mover);
                                    if(mover == 1){
                                        mover_tarea(&realizada, &tareasEnProceso, auxID);
                                    }
                                    else{
                                        mover_tarea(&realizada, &pendiente, auxID);
                                    }
                                break;
                            }
                        break;
                        case 2:
                            switch(eleccion){
                                case 1:
                                    eliminar_tarea(id, &tareasEnProceso);
                                break;
                                case 2:
                                    eliminar_tarea( auxID, &pendiente);
                                break;
                                case 3:
                                    eliminar_tarea(auxID, &realizada);
                                break;
                            }
                        break;
                    }

                    printf("\n\nDesea modificar otra tarea\n1-Si\n2-No\n>> ");
                    scanf("%d", &aux);

                    fflush(stdin);

                }while(aux != 2);

                if(aux == 2){
                    printf("\nDatos de tareas en proceso");
                    mostrar_datos(tareasEnProceso);
                    printf("\nDatos de tareas pendientes");
                    mostrar_datos(pendiente);
                    printf("\nDatos de tareas realizadas");
                    mostrar_datos(realizada);
                }
                               
            break;
        case 3: 
                printf("\n\nMOSTRAR TAREAS");
                int m;
                do{
                    do{
                        printf("\nDesea ver:\n\t1-TAREAS PENDIENTES\n\t2-TAREAS EN PROCESO\n\t3-TAREAS REALIZADAS\n\t0-NINGUNA\n\t>> ");
                        scanf("%d", &m);
                    }while(m >= 5);
                

                    switch(m){
                        case 1:
                            if(pendiente){
                                printf("\n\n----TAREAS PENDIENTES----");
                                while(pendiente != NULL){
                                    mostrar_tareas(pendiente);
                                    pendiente = pendiente->sig;

                                }
                            }
                            else{
                                printf("\nYa se ralizaron todas las tareas o estan en proceso");
                            }
                            getchar();
                        break;
                        case 2:
                            if(tareasEnProceso){
                                while(tareasEnProceso != NULL){

                                    printf("\n----TAREAS EN PROCESO----");
                                    mostrar_tareas(tareasEnProceso);
                                    tareasEnProceso = tareasEnProceso->sig;

                                }
                            }
                            else{
                                printf("\nNo marco ninguna tarea como en proceso o ya se realizaron todas");
                            }
                            getchar();
                        break;
                        case 3:
                            if(realizada){
                                printf("\n----TAREAS REALIZADAS----");
                                while(realizada != NULL){

                                    mostrar_tareas(realizada);
                                    realizada = realizada->sig;

                                }
                            }
                            else{
                                printf("\nNo marco ninguna tarea como realizada o estan en proceso");
                            }
                            getchar();
                        break;
                    }
                
                }while (m != 0);
            break;
        case 4:
                printf("\n\nBUSQUEDA DE TAREAS");
                int b;

                do{    
                    do{
                        printf("\n\n\tDesea buscar una tarea por:\n\t1-ID\n\t2-PALABRA CLAVE\n\t0-NINGUNA");
                        scanf("%d", &b);
                    }while(b>2);

                    switch (b){
                    case 1:
                        printf("\n\n----BUSQUEDA DE TAREA POR ID----");
                        fflush(stdin);
                        printf("\n\nIngrese el ID de la tarea que desea buscar: >> ");
                        scanf("%d", &IDbusq);
                        
                        busq = busqueda_ID(&todasT, IDbusq);
                    break;
                    case 2:
                        printf("\n\n----BUSQUEDA DE TAREA POR PALABRA CLAVE----");

                        char *auxP = (char*) malloc(sizeof(char) * 100);
                        fflush(stdin);

                        printf("\nIngrese la palabra clave: ");
                        gets(auxP);
                        char *palabra = (char*) malloc(sizeof(char) * (strlen(auxP) + 1));
                        strcpy(palabra, auxP);

                        free(auxP);
                        fflush(stdin);
                        busq = busqueda_palabra(&todasT, palabra);
                    break;
                    }

                    if(busq!=NULL && b != 0){
                        printf("\nResultado de la busqueda");
                        mostrar_tareas(busq);
                    }     
                    else{
                        printf("\nNo se encontro coincidencia");
                    }
                    
                }while(b != 0);
                
            break;
        }

    }while(op != 0);
    
    liberar_memoria(&pendiente);
    liberar_memoria(&tareasEnProceso);
    liberar_memoria(&realizada);
    liberar_memoria(&todasT);

    //mostrar_tareas(pendiente);

    getchar();
    return 0;
}

/****FUNCIONES SECUNDARIAS****/

nodo *crear_lista_vacia(){
    return NULL;
}

tarea cargar_tarea(int id){
    
    tarea tareaNueva;

        printf("\n\nTAREA %d", id);
        tareaNueva.tareaID = id;

        char *auxDes = (char*) malloc(sizeof(char));
        printf("\nIngrese una descripcion: ");
        gets(auxDes);
        tareaNueva.descripcion = (char*) malloc(sizeof(char) * (strlen(auxDes) + 1));
        strcpy(tareaNueva.descripcion, auxDes);

        tareaNueva.duracion = rand()%91 + 10;

        return tareaNueva;
}

nodo *crear_Nodo(tarea Ntarea){
    nodo *nuevoNodo = (nodo*) malloc(sizeof(nodo));
    nuevoNodo->t = Ntarea;
    nuevoNodo->sig = NULL;
    return nuevoNodo;

}

void insertar_nodo(nodo **lista, nodo *nuevoNodo){
    nuevoNodo->sig = *lista;
    *lista = nuevoNodo;
}

void mostrar_tareas(nodo *tarea){

    nodo *aux;
    aux = tarea;
    printf("\n\nTAREA %d", aux->t.tareaID);
    printf("\nDescripcion: ");
    puts(aux->t.descripcion);
    printf("Duracion: %d", aux->t.duracion);

}

void mostrar_lista (nodo *lista){
    nodo *aux = lista;

    while (aux != NULL){
        mostrar_tareas(aux);
        aux = aux->sig;
    }
}

void mover_tarea(nodo **lista1, nodo **lista2, int id){

    nodo *actual = *lista1;// para recorrer la lista 'pendiente'
    nodo *anterior = NULL; //guarda la direccion del nodo anterior a aux

    while(actual){

        if(actual->t.tareaID == id){

            if(!anterior){ //cuando es el primer nodo de la lista
                
                insertar_nodo(lista2, crear_Nodo(actual->t));//inserta el nodo actual a la lista de tareas realizadas
                *lista1 = (*lista1)->sig;//actualiza la cabecera para que apunte al nodo siguiente
                actual = *lista1;// avanza al siguiente nodo

            }
            else{//cuando no es el primer nodo de la lista
                insertar_nodo(lista2, crear_Nodo(actual->t));
                anterior->sig = actual->sig;//el nodo siguiente del auxiliar anterior apunta al nodo siguiente del nodo actual 
                actual = anterior->sig;//avanza al siguiente nodo de la lista de tareas
            }
        }
        else{
            anterior = actual;//apunta al nodo actual
            actual = actual->sig;//avanza al siguiente nodo
        }
    }
}

nodo *busqueda_ID (nodo **lista1, int id){

    nodo *aux1 = *lista1;

    while(aux1){
        
        if (aux1->t.tareaID == id){
            return  aux1;
        }

        aux1 = aux1->sig;
    }
    
    return NULL;
}

nodo *busqueda_palabra (nodo **lista1, char *palabra){
    
    nodo *aux1 = *lista1;

    while(aux1){

        if(strstr(strlwr(aux1->t.descripcion), strlwr(palabra))){
    
            return aux1;
        }
        aux1 = aux1->sig;
    }

    return NULL;
}

void eliminar_tarea (int valor, nodo **lista) {
    nodo *actual = *lista;
    nodo *anterior = NULL;

    while (actual != NULL && actual->t.tareaID != valor) {
        anterior = actual;
        actual = actual->sig;
    }
    
    if (actual != NULL) {
        if (anterior == NULL) {
            *lista = actual->sig;
        }
        else {
            anterior->sig = actual->sig;
        }
        free(actual);
    }
}

void mostrar_datos (nodo *lista){
    nodo *aux = lista;
    int totalT = 0, totalD = 0;

    while (aux != NULL){
        totalT++;
        totalD += aux->t.duracion;
        aux = aux->sig;
    }

    printf("\nEl total de tareas es: %d", totalT);
    printf("\nLa suma de la duracion de todas las tareas es: %d", totalD);

}

void liberar_memoria(nodo ** lista)
{
	nodo *aux;
	
	while (*lista)
	{
		free((*lista)->t.descripcion);
		aux = *lista;
		*lista = (*lista)->sig;
		free(aux);
	}
}
