#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct {
    int tareaID;
    char *descripcion;
    int duracion;
}typedef tarea;

void inicializar (tarea **vTarea, int n){
    for (int i=0; i<n; i++){
        vTarea[i]=NULL;
    }
}

void cargar_tareas (tarea **v, int n){

    for (int i=0; i<n; i++){

        v[i]=(tarea*)malloc(sizeof(tarea));
        v[i]->tareaID=i+1;
        printf("\n>>>>Tarea %d<<<<", i+1);

        char *aux = (char*)malloc(sizeof(char) * 100);
        printf("\nIngrese una descripcion de la tarea >> ");
        gets(aux);

        v[i]->descripcion = (char*)malloc((strlen(aux)+1) * sizeof(char));
        strcpy(v[i]->descripcion, aux);

        free(aux);

        v[i]->duracion = rand()%91 + 10;

    }
}

void mostrar_tareas (tarea *v){

        printf("\n\n----Tarea %d----", v->tareaID);
        printf("\nDescripcion: ");
        puts(v->descripcion);
        printf("Duracion: %d", v->duracion);
    
}

void tareas_realizadas (tarea **tareaPendiente, int n){

    int e, j=0;

    tarea **tareaRealizada= (tarea**) malloc(sizeof(tarea*) * n);

    inicializar(tareaRealizada, n);

    for (int i=0; i<n; i++){

        printf("\n\n\nRealizo la tarea? %d", tareaPendiente[i]->tareaID);
        printf("\nDescrieeepcion: ");
        puts(tareaPendiente[i]->descripcion);
        printf("\nDuracion: %d", tareaPendiente[i]->duracion);
        
        printf("\n\n1- SI\n2- NO\n>> ");
        scanf("%d", &e);
        while(e<1 || e>2){

            printf("\nDebe ingresar 1 para SI o 2 para NO");
            printf("\n1- SI\n2- NO\n>> ");
            scanf("%d", &e);

        }

        if(e==1){
            tareaRealizada[j]=(tarea*)malloc(sizeof(tarea));
            tareaRealizada[j] = tareaPendiente[i];
            tareaPendiente[i]=NULL;
        }
        j++;
        
    }


    printf("\n\n\t>>>>Tareas realizadas<<<<");
    for(int i=0; i<n; i++){

        if(tareaRealizada[i]!= NULL){
            mostrar_tareas(tareaRealizada[i]);
        }

        
    }

    printf("\n\n\t>>>>Tareas pendientes<<<<");
     for(int i=0; i<n; i++){

        if(tareaPendiente[i]!=NULL){
            mostrar_tareas(tareaPendiente[i]);    
        }
    }

    for(int i=0; i<n; i++){
        free(tareaRealizada[i]);
    }
    free(tareaRealizada);
}

tarea buscarTarea (tarea **v, int n){

     int id;

        fflush(stdin);
    
    printf("\nIngrese el ID (entre 1 y %d) de la tarea que desea buscar >> ", n);
    scanf("%d", &id);

    while(id < 1 || id > n){
        printf("\nDebe ingresar un ID valido");
        printf("\nIngrese el ID (entre 1 y %d) de la tarea que desea buscar >> ", n);
        scanf("%d", &id);
    }

    for(int i=0; i<n; i++){
        if(id== v[i]->tareaID){
            return *(v)[i];
        }
    }
}

int main(){

    int numTarea;
    tarea **vTarea;

    srand(time(NULL));

    printf("Ingrese cuantas tareas va a cargar >> ");
    scanf("%d", &numTarea);

    vTarea = (tarea**)malloc(sizeof(tarea*) * numTarea);

    fflush(stdin);

    inicializar(vTarea, numTarea);

    fflush(stdin);

    cargar_tareas(vTarea, numTarea);

    tareas_realizadas(vTarea, numTarea);

    printf("\n>>>>BUSQUEDA DE TAREA<<<<");

    tarea x = buscarTarea(vTarea, numTarea);
    
    printf("\nResultado de la busqueda: ");
    printf("\nID %d", x.tareaID);
    printf("Descripcion: ");
    puts(x.descripcion);
    printf("\nDuracion: %d", x.duracion);

    

    for(int i=0; i<numTarea; i++){
        free(vTarea[i]);
    }
    free(vTarea);

    getchar();
    return 0;
}
