#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "pais.h"

int mostrarOpcionesYObtenerSeleccion()
{
    int seleccion;
    int seleccionEsCorrecta = 0;

    while(!seleccionEsCorrecta)
    {

        system("cls");
        printf("Por favor seleccione una opcion y presione la tecla enter: \n\n");
        printf("1. Cargar archivo de paises\n");
        printf("2. Mostrar paises.\n");
        printf("3. Cargar estadisticas al azar. \n");
        printf("4. Generar archivo de paises exitosos. \n");
        printf("5. Generar archivo de paises en el horno. \n");
        printf("6. Ordenar paises por nivel de infeccion. \n");
        printf("7. Mostrar al pais mas castigado. \n");
        printf("8. Salir \n");


        fflush(stdin);

        scanf("%i" , &seleccion );

        if(seleccion < 9 && seleccion > 0)
        {
            seleccionEsCorrecta = 1;
        }
    }

    return seleccion;



}

int main()
{
    int option = 0;
    char* nombreArchivo = (char*) malloc(sizeof(char) * 128);
    srand (time(NULL));
    int paisesCargados = 0;

    LinkedList* listaPaises = ll_newLinkedList();
    do{
        option = mostrarOpcionesYObtenerSeleccion();
        if(!paisesCargados && option != 1)
        {
            printf("\n\nAun no han sido cargados los paises!");
            system("pause");
        }
        switch(option)
        {
            case 1:
                controller_pedirNombreArchivo(nombreArchivo);
                paisesCargados = controller_loadFromText(nombreArchivo, listaPaises);
                break;
            case 2:
                if(paisesCargados)
                {
                    controller_ListarPaises(listaPaises);
                }
                break;
            case 3:
                if(paisesCargados)
                {
                    listaPaises = ll_map(listaPaises, p_cargarDatosAleatorios);
                }
                break;
            case 4:
                if(paisesCargados){
                controller_filtrarPaisesExitosos(listaPaises);
                }
                break;
            case 5:
                if(paisesCargados){
                controller_filtrarPaisesEnHorno(listaPaises);
                }
                break;
            case 6:
                if(paisesCargados){
                ll_sort(listaPaises, p_compararPorInfectados, 0);
                controller_ListarPaises(listaPaises);
                }
                break;
            case 7:
                if(paisesCargados){
                ll_sort(listaPaises, p_compararPorMuertos, 0);
                printf("Pais con mas muertos: \n\n");
                printf("ID\t NOMBRE\t\t RECUPERADOS\t INFECTADOS\t MUERTOS\t\n");
                printf("--------------------------------------------------------------------\n\n");
                controller_mostrarPais(ll_get(listaPaises, 0));
                system("pause");
                }
                break;
            case 8:
                break;

        }
    }while(option != 8);
    return 0;
}
