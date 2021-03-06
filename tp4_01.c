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
Tarea BusquedaPorID(Tarea ** tareasPendientes, Tarea ** tareasRealizadas, int cantTareas);
Tarea BusquedaPorPalabra(Tarea ** tareasPendientes, Tarea ** tareasRealizadas, int cantTareas);
void mostrarBusqueda(Tarea busqueda);


int main(){
    srand(time(NULL));

    int cantTareas;
    Tarea busqueda;
    Tarea * tareasPendientes = NULL;
    Tarea * tareasRealizadas = NULL;

    printf("Cantidad de tareas a cargar: ");
    scanf("%d", &cantTareas);
    fflush(stdin);
    system("cls");

    cargarTareas(&tareasPendientes, cantTareas);
    realizarTareas(&tareasPendientes, &tareasRealizadas, cantTareas);
    mostrarTareas(&tareasPendientes, &tareasRealizadas, cantTareas);

    busqueda = BusquedaPorID(&tareasPendientes, &tareasRealizadas, cantTareas);
    mostrarBusqueda(busqueda);

    busqueda = BusquedaPorPalabra(&tareasPendientes, &tareasRealizadas, cantTareas);
    mostrarBusqueda(busqueda);

    return 0;
}

void cargarTareas(Tarea ** tareasPendientes, int cantTareas){
    for (int i = 0; i < cantTareas; i++)
    {
        char descripcion[100];
        tareasPendientes[i] = (Tarea *)malloc(sizeof(Tarea));
        tareasPendientes[i]->TareaID = i+1;

        printf("Ingrese una descripcion para la tarea N %d\n", i+1);
        scanf("%s", &descripcion);
        fflush(stdin);
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
        tareasRealizadas[i] = NULL;
        printf("Tarea Numero %d\n\n", tareasPendientes[i]->TareaID);
        printf("Descripcion: \"%s\"\n", tareasPendientes[i]->Descripcion);
        printf("Duracion: %d\n\n", tareasPendientes[i]->Duracion);

        printf("Esta tarea se realizo?\nSI = 1       NO = 0\n\n");
        scanf("%d", &seRealizo);
        fflush(stdin);
        system("cls");

        if (seRealizo == 1)
        {
            tareasRealizadas[i] = tareasPendientes[i];
            tareasPendientes[i] = NULL;
        }
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
    system("pause");
    system("cls");
}

Tarea BusquedaPorID(Tarea ** tareasPendientes, Tarea ** tareasRealizadas, int cantTareas){
    int ID;
    Tarea aux;
    aux.TareaID = 0;

    printf("ID de la tarea a buscar: ");
    scanf("%d",&ID);
    fflush(stdin);
    system("cls");

    for (int i = 0; i < cantTareas; i++)
    {
        if (tareasPendientes[i]->TareaID == ID)
        {
            return **(tareasPendientes + i);
        }
        else if(tareasRealizadas[i]->TareaID == ID)
        {
            return **(tareasRealizadas + i);
        }
    }
    return aux;
}

Tarea BusquedaPorPalabra(Tarea ** tareasPendientes, Tarea ** tareasRealizadas, int cantTareas){
    char palabraClave[100];
    Tarea aux;
    aux.TareaID = 0;

    printf("Palabra clave para buscar\n\n");
    gets(palabraClave);
    system("cls");

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

void mostrarBusqueda(Tarea busqueda){
    printf("Tarea Numero %d\n\n", busqueda.TareaID);
    printf("Descripcion: \"%s\"\n", busqueda.Descripcion);
    printf("Duracion: %d\n\n", busqueda.Duracion);

    system("pause");
    system("cls");
}
