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

void tareas_realizadas(nodo **pendiente, nodo **realizada);

nodo *busqueda_ID (nodo **lista1, nodo **lista2, int id);

nodo *busqueda_palabra (nodo **lista1, nodo **lista2, char *palabra);

void liberar_memoria(nodo ** lista);

/****FUNCION PRINCIPAL****/

int main(){

    int resp, id=1, IDbusq, op;
    nodo *pendiente, *realizada, *busq;
    pendiente = crear_lista_vacia();
    realizada = crear_lista_vacia();

    do{
        printf("\n\n>>>>MENU<<<<");
        printf("\nElija una opcion");
        printf("\n1- Agregar tarea");
        printf("\n2- Marcar tareas realizadas");
        printf("\n3- Mostrar tareas pendientes");
        printf("\n4- Mostrar tareas realizadas");
        printf("\n5- Buscar tarea por ID");
        printf("\n6- Buscar tarea por palabra clave");
        printf("\n7- Salir");
        printf("\n>> ");
        scanf("%d", &op);

        fflush(stdin);

        switch (op){
        case 1 :
                do{

                    insertar_nodo(&pendiente, crear_Nodo(cargar_tarea(id)));

                    printf("\nDesea cargar otra tarea?\n1-SI\n2-NO\n>> ");
                    scanf("%d", &resp);
                    fflush(stdin);

                    id++;

                }while(resp != 2);
            break;
        case 2:
                printf("\n\nCONTROL DE TAREAS REALIZADAS");
                tareas_realizadas(&pendiente, &realizada);
            break;
        case 3:
                if(pendiente){
                    while(pendiente != NULL){

                        printf("\n\n----TAREAS PENDIENTES----");
                        mostrar_tareas(pendiente);
                        pendiente = pendiente->sig;

                    }
                }
                else{
                    printf("\nYa se ralizaron todas las tareas");
                }
                getchar();
            break;
        case 4:
                if(realizada){
                    while(realizada != NULL){

                        printf("\n----TAREAS REALIZADAS----");
                        mostrar_tareas(realizada);
                        realizada = realizada->sig;

                    }
                }
                else{
                    printf("\nNo marco ninguna tarea como realizada");
                }
                getchar();
            break;
        case 5:
                printf("\n\n----BUSQUEDA DE TAREA POR ID----");
                fflush(stdin);
                printf("\n\nIngrese el ID de la tarea que desea buscar: >> ");
                scanf("%d", &IDbusq);
                

                busq = busqueda_ID(&pendiente, &realizada, IDbusq);
            break;
        case 6:
                printf("\n\n----BUSQUEDA DE TAREA POR PALABRA CLAVE----");

                char *auxP = (char*) malloc(sizeof(char) * 100);
                fflush(stdin);

                printf("\nIngrese la palabra clave: ");
                gets(auxP);
                char *palabra = (char*) malloc(sizeof(char) * (strlen(auxP) + 1));
                strcpy(palabra, auxP);

                free(auxP);
                fflush(stdin);
                busq = busqueda_palabra(&pendiente, &realizada, palabra);
        }
                if(op == 5 || op == 6){
                if(busq!=NULL){
                    printf("\nResultado de la busqueda");
                    mostrar_tareas(busq);
                    getchar();
                }     
                else{
                    printf("\nNo se encontro coincidencia");
                    getchar();
                }
            }

    }while(op != 7);
    
    liberar_memoria(&pendiente);
    liberar_memoria(&realizada);

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

void tareas_realizadas(nodo **pendiente, nodo **realizada){

     int respuesta;
    nodo *actual = *pendiente;// para recorrer la lista 'pendiente'
    nodo *anterior = NULL; //guarda la direccion del nodo anterior a aux

    while(actual){

        mostrar_tareas(actual);

        do{   
            printf("\nRealizo esta tarea?\n1-SI \n2-NO \n>> ");
            scanf("%d", &respuesta);
        } while (respuesta != 1 && respuesta!=2);

        if(respuesta == 1){

            if(!anterior){ //cuando es el primer nodo de la lista
                
                insertar_nodo(realizada, crear_Nodo(actual->t));//inserta el nodo actual a la lista de tareas realizadas
                *pendiente = (*pendiente)->sig;//actualiza la cabecera para que apunte al nodo siguiente
                actual = *pendiente;// avanza al siguiente nodo

            }
            else{//cuando no es el primer nodo de la lista
                insertar_nodo(realizada, crear_Nodo(actual->t));
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

nodo *busqueda_ID (nodo **lista1, nodo **lista2, int id){

    nodo *aux1 = *lista1;
    nodo *aux2 = *lista2;

    while(aux1){
        
        if (aux1->t.tareaID == id){
            return  aux1;
        }

        aux1 = aux1->sig;
    }
    while (aux2){
        if(aux2->t.tareaID == id){
            return aux2;
        }
        aux2 = aux2->sig;
    }
    
    return NULL;
}

nodo *busqueda_palabra (nodo **lista1, nodo **lista2, char *palabra){
    
    nodo *aux1 = *lista1;
    nodo *aux2 = *lista2;

    while(aux1){

        if(strstr(strlwr(aux1->t.descripcion), strlwr(palabra))){
    
            return aux1;
        }
        aux1 = aux1->sig;
    }
    while(aux2){

        if(strstr(strlwr(aux2->t.descripcion), strlwr(palabra))){
    
            return aux2;
        }
        aux2 = aux2->sig;
    }

    return NULL;
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