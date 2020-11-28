#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "pais.h"
#include "LinkedList.h"
#include <string.h>


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param listaPaises LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* listaPaises)
{
    FILE* archivo = fopen(path, "r");
    if(archivo != NULL)
    {
        parser_CountryFromText(archivo , listaPaises);
        return 1;
    }
    else
    {
        printf("No se encontro un archivo con ese nombre.\n");
        system("pause");
        return 0;
    }

}


/** \brief Imprime un pais por pantalla
 *
 * \param auxPais ePais*
 * \return void
 *
 */
void controller_mostrarPais(ePais* auxPais)
{
    printf("%i\t%s\t\t\t\t%i\t%i\t%i\n",auxPais->id, auxPais->nombre, auxPais->recuperados, auxPais->infectados, auxPais->muertos);
}

/** \brief Lista todos los paises de la lista
 *
 * \param path char*
 * \param listaPaises LinkedList*
 * \return int
 *
 */
int controller_ListarPaises(LinkedList* listaPaises)
{
    if(listaPaises != NULL)
    {
        int i = 0;
        int largo = ll_len(listaPaises);
        ePais* auxPais;
        printf("ID\t NOMBRE\t\t\t RECUPERADOS\t INFECTADOS\t MUERTOS\t\n");
        printf("--------------------------------------------------------------------\n\n");
        while(i < largo)
        {
            auxPais = (ePais*) ll_get(listaPaises, i);
            controller_mostrarPais(auxPais);
            i++;
        }
        system("pause");
        return 1;
    }
    else
    {
        return 0;
    }
}


/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param listaPaises LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* listaPaises)
{
    FILE* pArchivo;
    ePais* auxPais;
    int largoId, largoRecuperados, largoInfectados, largoMuertos;

    if((pArchivo = fopen(path, "w"))== NULL)
    {
        return 0;
    }
    int largo = ll_len(listaPaises);

    for(int i = 0; i < largo; i++)
    {
        auxPais = ll_get(listaPaises, i);

        largoId = snprintf(NULL, 0, "%d", auxPais->id);
        char* sId = (char*)malloc(largoId + 1);
        snprintf(sId, largoId + 1, "%i", auxPais->id );

        largoRecuperados = snprintf(NULL, 0, "%d", auxPais->recuperados);
        char* sRecuperados = (char*)malloc(largoRecuperados + 1);
        snprintf(sRecuperados, largoRecuperados + 1, "%i", auxPais->recuperados );

        largoInfectados = snprintf(NULL, 0, "%d", auxPais->infectados);
        char* sInfectados = (char*)malloc(largoInfectados + 1);
        snprintf(sInfectados, largoInfectados + 1, "%i", auxPais->infectados );

        largoMuertos = snprintf(NULL, 0, "%d", auxPais->muertos);
        char* sMuertos = (char*)malloc(largoMuertos + 1);
        snprintf(sMuertos, largoMuertos + 1, "%i", auxPais->muertos);

        fwrite(sId, sizeof(char), largoId, pArchivo);
        fwrite(",", sizeof(char), 1, pArchivo);
        fwrite(auxPais->nombre, sizeof(char), strlen(auxPais->nombre), pArchivo);
        fwrite(",", sizeof(char), 1, pArchivo);
        fwrite(sRecuperados, sizeof(char), largoRecuperados, pArchivo);
        fwrite(",", sizeof(char), 1, pArchivo);
        fwrite(sInfectados, sizeof(char), largoInfectados, pArchivo);
        fwrite(",", sizeof(char), 1, pArchivo);
        fwrite(sMuertos, sizeof(char), largoMuertos, pArchivo);
        fwrite("\n", sizeof(char), 1, pArchivo);
    }

    fclose(pArchivo);

    return 1;
}

/** \brief Muestra los paises que cumplan con la condicion de ser "Exitosos"
 *
 * \param listaPaises LinkedList*
 * \return void
 *
 */
void controller_filtrarPaisesExitosos(LinkedList* listaPaises)
{
    LinkedList* listaFiltrada = ll_filter(listaPaises, p_filtroExitosos);
    controller_ListarPaises(listaFiltrada);
    controller_saveAsText("PaisesExitosos.csv", listaFiltrada );
}

/** \brief Muestra los paises que cumplan con la condicion de estar en el "Horno"
 *
 * \param listaPaises LinkedList*
 * \return void
 *
 */
void controller_filtrarPaisesEnHorno(LinkedList* listaPaises)
{
    LinkedList* listaFiltrada = ll_filter(listaPaises, p_filtroHorno);
    controller_ListarPaises(listaFiltrada);
    controller_saveAsText("PaisesEnElHorno.csv", ll_filter(listaPaises, p_filtroHorno));
}

/** \brief Pide el nombre del archivo para cargar los paises.
 *
 * \param nombre char*
 * \return void
 *
 */
void controller_pedirNombreArchivo(char* nombre)
{
    printf("Por favor ingrese el nombre del archivo con los paises: \n\n");
    fflush(stdin);
    gets(nombre);
}


