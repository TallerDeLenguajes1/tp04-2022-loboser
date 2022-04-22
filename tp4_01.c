#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}typedef Tarea;

void cargarTareas(Tarea ** tareasPendientes, int cantTareas);
void realizarTareas(Tarea ** tareasPendientes, Tarea ** tareasRealizadas, int cantTareas);
void mostrarTareas(Tarea ** tareasPendientes, Tarea ** tareasRealizadas, int cantTareas);
Tarea BuscarTarea(Tarea ** tareasPendientes, Tarea ** tareasRealizadas, int cantTareas);


int main(){
    srand(time(NULL));

    int cantTareas;
    Tarea buscar;
    Tarea * tareasPendientes = NULL;
    Tarea * tareasRealizadas = NULL;

    printf("Cantidad de tareas a cargar: ");
    scanf("%d", &cantTareas);
    system("cls");

    cargarTareas(&tareasPendientes, cantTareas);
    realizarTareas(&tareasPendientes, &tareasRealizadas, cantTareas);
    mostrarTareas(&tareasPendientes, &tareasRealizadas, cantTareas);
    buscar = BuscarTarea(&tareasPendientes, &tareasRealizadas, cantTareas);

    printf("Tarea ID: %d \n", buscar.TareaID);
    printf("Descripcion: \"%s\"\n", buscar.Descripcion);
    printf("Duracion: %d\n\n", buscar.Duracion);
    system("pause");
    return 0;
}

void cargarTareas(Tarea ** tareasPendientes, int cantTareas){
    for (int i = 0; i < cantTareas; i++)
    {
        char descripcion[100];
        *(tareasPendientes + i) = (Tarea *)malloc(sizeof(Tarea));
        tareasPendientes[i]->TareaID = i+1;

        printf("Ingrese una descripcion para la tarea N %d\n", i+1);
        scanf("%s", &descripcion);
        system("cls");
        tareasPendientes[i]->Descripcion = (char*)malloc(sizeof(descripcion)*(strlen(descripcion)+1));
        strcpy(tareasPendientes[i]->Descripcion, descripcion);

        tareasPendientes[i]->Duracion = 10 + rand() % 100;
    }
}

void realizarTareas(Tarea ** tareasPendientes,Tarea ** tareasRealizadas, int cantTareas){
    int seRealizo;

    for (int i = 0; i < cantTareas; i++)
    {
        printf("Tarea Numero %d\n\n", tareasPendientes[i]->TareaID);
        printf("Descripcion: \"%s\"\n", tareasPendientes[i]->Descripcion);
        printf("Duracion: %d\n\n", tareasPendientes[i]->Duracion);

        printf("Esta tarea se realizo?\nSI = 1       NO = 0\n\n");
        scanf("%d", &seRealizo);

        if (seRealizo == 1)
        {
            *(tareasRealizadas + i) = *(tareasPendientes + i);
            *(tareasPendientes + i) = NULL;
        }else
        {
            *(tareasRealizadas + i) = NULL;
        }

        system("cls");
    }
}

void mostrarTareas(Tarea ** tareasPendientes, Tarea ** tareasRealizadas, int cantTareas){
    printf("|||||||||||||||||TAREAS REALIZADAS|||||||||||||||||\n\n");
    for (int i = 0; i < cantTareas; i++)
    {
        if (*(tareasRealizadas + i)!=NULL){
            printf("Tarea ID: %d \n", tareasRealizadas[i]->TareaID);
            printf("Descripcion: \"%s\"\n", tareasRealizadas[i]->Descripcion);
            printf("Duracion: %d\n\n", tareasRealizadas[i]->Duracion);
        }
    }
    printf("|||||||||||||||||TAREAS PENDIENTES|||||||||||||||||\n\n");
    for (int i = 0; i < cantTareas; i++)
    {
        if (*(tareasPendientes + i)!=NULL){
            printf("Tarea ID: %d \n", tareasPendientes[i]->TareaID);
		    printf("Descripcion: \"%s\"\n", tareasPendientes[i]->Descripcion);
		    printf("Duracion: %d\n\n", tareasPendientes[i]->Duracion);
        }
    }
    getchar();
    getchar();
}

Tarea BuscarTarea(Tarea ** tareasPendientes, Tarea ** tareasRealizadas, int cantTareas){
    char palabraClave[100];
    Tarea aux;
    aux.TareaID = 0;

    printf("Palabra clave para buscar\n\n");
    gets(palabraClave);

    for (int i = 0; i < cantTareas; i++)
    {
        if (strstr(tareasPendientes[i]->Descripcion, palabraClave))
        {
            return **(tareasPendientes + i);
        }
        else if (strstr(tareasRealizadas[i]->Descripcion, palabraClave))
        {
            return **(tareasRealizadas + i);
        }
    }
    return aux;
}