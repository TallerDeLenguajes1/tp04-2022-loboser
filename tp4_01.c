#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}typedef Tarea;

void cargarTareas(Tarea * tareasPendientes, int cantTareas);
void realizarTareas(Tarea * tareasPendientes, Tarea * tareasRealizadas, int cantTareas);
void mostrarTareas(Tarea * tareasPendientes, Tarea * tareasRealizadas, int cantTareas);

int main(){
    srand(time(NULL));

    int cantTareas;

    printf("Cantidad de tareas a cargar: ");
    scanf("%d",&cantTareas);
    system("cls");

    Tarea * tareasPendientes = (Tarea *) malloc(sizeof(Tarea)*cantTareas);
    Tarea * tareasRealizadas = (Tarea *) malloc(sizeof(Tarea)*cantTareas);

    cargarTareas(tareasPendientes, cantTareas);
    realizarTareas(tareasPendientes, tareasRealizadas, cantTareas);
    mostrarTareas(tareasPendientes, tareasRealizadas, cantTareas);


    return 0;
}

void cargarTareas(Tarea * tareasPendientes, int cantTareas){
    for (int i = 0; i < cantTareas; i++)
    {
        char descripcion[100];

        (tareasPendientes + i)->TareaID = i+1;

        printf("Ingrese una descripcion para la tarea N %d\n", i+1);
        scanf("%s",&descripcion);
        system("cls");
        (tareasPendientes + i)->Descripcion = (char*)malloc(sizeof(descripcion)*(strlen(descripcion)+1));
        strcpy((tareasPendientes + i)->Descripcion,descripcion);

        (tareasPendientes + i)->Duracion = 10 + rand() % 100;
    }
}

void realizarTareas(Tarea * tareasPendientes,Tarea * tareasRealizadas, int cantTareas){
    int seRealizo;
    int indexAux;
    for (int i = 0; i < cantTareas; i++)
    {
        printf("Tarea Numero %d\n\n", (tareasPendientes + i)->TareaID);
        printf("Descripcion: %s\n", (tareasPendientes + i)->Descripcion);
        printf("Duracion: %d\n\n", (tareasPendientes + i)->Duracion);

        printf("¿Esta tarea se realizo?\nSI = 1       NO = 0");
        scanf("%d", &seRealizo);

        if (seRealizo == 1)
        {
            *(tareasRealizadas + indexAux) = *(tareasPendientes + i);
            (tareasPendientes + i)->TareaID = 0;
            indexAux++;
        }
        system("cls");
    }
}

void mostrarTareas(Tarea * tareasPendientes, Tarea * tareasRealizadas, int cantTareas){
    printf("|||||||||||||||||TAREAS REALIZADAS|||||||||||||||||\n\n");
    for (int i = 0; i < cantTareas; i++)
    {
        printf("Tarea ID: %d \n", (tareasRealizadas + i)->TareaID);
		printf("Descripcion: \"%s\"\n", (tareasRealizadas + i)->Descripcion);
		printf("Duracion: %d\n\n", (tareasRealizadas + i)->Duracion);
    }
    printf("|||||||||||||||||TAREAS PENDIENTES|||||||||||||||||\n\n");
    for (int i = 0; i < cantTareas; i++)
    {
        if ((tareasRealizadas + i)->TareaID != 0){
            printf("Tarea ID: %d \n", (tareasRealizadas + i)->TareaID);
		    printf("Descripcion: \"%s\"\n", (tareasRealizadas + i)->Descripcion);
		    printf("Duracion: %d\n\n", (tareasRealizadas + i)->Duracion);
        }
    }  
}

