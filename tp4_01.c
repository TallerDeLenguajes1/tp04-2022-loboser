#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}typedef TTarea;

struct Nodo{
    TTarea T;
    struct Nodo * Siguiente;
}typedef TNodo;


void cargarTareas(TNodo ** tareasPendientes, int cantTareas);
void realizarTareas(TNodo ** tareasPendientes, TNodo ** tareasRealizadas, int cantTareas);
void mostrarTareas(TNodo ** tareasPendientes, TNodo ** tareasRealizadas);
TNodo BusquedaPorID(TNodo * tareasPendientes, TNodo * tareasRealizadas, int cantTareas);
TNodo BusquedaPorPalabra(TNodo * tareasPendientes, TNodo * tareasRealizadas, int cantTareas);
void mostrarBusqueda(TNodo busqueda);

int main(){
    srand(time(NULL));

    int cantTareas;
    TNodo busqueda;

    TNodo * tareasPendientes = NULL; //start
    TNodo * tareasRealizadas = NULL; //start

    printf("Cantidad de tareas a cargar: ");
    scanf("%d", &cantTareas);
    fflush(stdin);
    system("cls");

    cargarTareas(&tareasPendientes, cantTareas);
    realizarTareas(&tareasPendientes, &tareasRealizadas, cantTareas);
    mostrarTareas(&tareasPendientes, &tareasRealizadas);

    busqueda = BusquedaPorID(tareasPendientes, tareasRealizadas, cantTareas);
    mostrarBusqueda(busqueda);

    busqueda = BusquedaPorPalabra(tareasPendientes, tareasRealizadas, cantTareas);
    mostrarBusqueda(busqueda);

    return 0;
}

void cargarTareas(TNodo ** tareasPendientes, int cantTareas){
    for (int i = 0; i < cantTareas; i++)
    {
        TNodo * nodoTarea = (TNodo *)malloc(sizeof(TNodo));
        char descripcion[100];
        nodoTarea->T.TareaID = i+1;

        printf("Ingrese una descripcion para la tarea N %d\n", i+1);
        scanf("%s", &descripcion);
        fflush(stdin);
        system("cls");

        nodoTarea->T.Descripcion = (char*)malloc(sizeof(descripcion)*(strlen(descripcion)+1));
        strcpy(nodoTarea->T.Descripcion, descripcion);

        nodoTarea->T.Duracion = 10 + rand() % 100;
        nodoTarea->Siguiente = NULL;

        if (i != 0)
        {
            nodoTarea->Siguiente = *tareasPendientes;
        }

        *tareasPendientes = nodoTarea;
    }
}

void realizarTareas(TNodo ** tareasPendientes,TNodo ** tareasRealizadas, int cantTareas){
    int seRealizo;

    TNodo * aux = *tareasPendientes;
    TNodo * auxAnterior = NULL;

    for (int i = 0; i < cantTareas; i++)
    {
        printf("Tarea Numero %d\n\n", aux->T.TareaID);
        printf("Descripcion: \"%s\"\n", aux->T.Descripcion);
        printf("Duracion: %d\n\n", aux->T.Duracion);

        printf("Esta tarea se realizo?\nSI = 1       NO = 0\n\n");
        scanf("%d", &seRealizo);
        fflush(stdin);
        system("cls");

        if (seRealizo == 1)
        {
            if (auxAnterior == NULL)
            {
                auxAnterior = aux->Siguiente;
                aux->Siguiente = *tareasRealizadas;
                *tareasRealizadas = aux;

                *tareasPendientes = auxAnterior;
                aux = *tareasPendientes;
                
                auxAnterior = NULL;
            }
            else
            {
                auxAnterior->Siguiente = aux->Siguiente;
                aux->Siguiente = *tareasRealizadas;
                *tareasRealizadas = aux;
                aux = auxAnterior->Siguiente;
            }    
        }else{
            auxAnterior = aux;
            aux = aux->Siguiente;
        }
    }
}

void mostrarTareas(TNodo ** tareasPendientes, TNodo ** tareasRealizadas){
    TNodo * auxPendientes = *tareasPendientes;
    TNodo * auxRealizadas = *tareasRealizadas;

    printf("|||||||||||||||||TAREAS REALIZADAS|||||||||||||||||\n\n");
    while (auxRealizadas)
    {
        printf("Tarea ID: %d \n", auxRealizadas->T.TareaID);
        printf("Descripcion: \"%s\"\n", auxRealizadas->T.Descripcion);
        printf("Duracion: %d\n\n", auxRealizadas->T.Duracion);
        auxRealizadas = auxRealizadas->Siguiente;
    }
    printf("|||||||||||||||||TAREAS PENDIENTES|||||||||||||||||\n\n");
    while (auxPendientes)
    {
        printf("Tarea ID: %d \n", auxPendientes->T.TareaID);
		printf("Descripcion: \"%s\"\n", auxPendientes->T.Descripcion);
		printf("Duracion: %d\n\n", auxPendientes->T.Duracion);
        auxPendientes = auxPendientes->Siguiente;
    }
    system("pause");
    system("cls");
}

TNodo BusquedaPorID(TNodo * tareasPendientes, TNodo * tareasRealizadas, int cantTareas){
    int ID;
    TNodo * auxPendientes = tareasPendientes;
    TNodo * auxRealizadas = tareasRealizadas;
    TNodo aux;
    aux.T.TareaID = 0;

    printf("ID de la tarea a buscar: ");
    scanf("%d",&ID);
    fflush(stdin);
    system("cls");

    for (int i = 0; i < cantTareas; i++)
    {
        if (auxPendientes->T.TareaID == ID)
        {
            return *(auxPendientes);
        }
        else if(auxRealizadas->T.TareaID == ID)
        {
            return *(auxRealizadas);
        }
        auxPendientes = auxPendientes->Siguiente;
        auxRealizadas = auxRealizadas->Siguiente;
    }
    return aux;
}

TNodo BusquedaPorPalabra(TNodo * tareasPendientes, TNodo * tareasRealizadas, int cantTareas){
    char palabraClave[100];
    TNodo * auxPendientes = tareasPendientes;
    TNodo * auxRealizadas = tareasRealizadas;
    TNodo aux;
    aux.T.TareaID = 0;

    printf("Palabra clave para buscar: ");
    gets(palabraClave);
    fflush(stdin);
    system("cls");

    for (int i = 0; i < cantTareas; i++)
    {
        if (strstr(auxPendientes->T.Descripcion, palabraClave))
        {
            return *(auxPendientes);
        }
        else if(strstr(auxRealizadas->T.Descripcion, palabraClave))
        {
            return *(auxRealizadas);
        }
        auxPendientes = auxPendientes->Siguiente;
        auxRealizadas = auxRealizadas->Siguiente;
    }
    return aux;
}

void mostrarBusqueda(TNodo busqueda){
    if (busqueda.T.TareaID != 0)
    {
        printf("Tarea Numero %d\n\n", busqueda.T.TareaID);
        printf("Descripcion: \"%s\"\n", busqueda.T.Descripcion);
        printf("Duracion: %d\n\n", busqueda.T.Duracion);
    }
    else{
        printf("No se encontro esa tarea!\n\n");
    }
    system("pause");
    system("cls");
}