#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "pais.h"
#include <string.h>

/** \brief Parsea los datos los datos de los paises desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param listaPaises LinkedList*
 * \return int
 *
 */
int parser_CountryFromText(FILE* pFile , LinkedList* listaPaises)
{
    int totalcargados = 0;
    char* sNombre = (char*) malloc(sizeof(char) * 128);
    char* sId = (char*) malloc(sizeof(char) * 20);
    char* sRecuperados = (char*) malloc(sizeof(char) * 20);
    char* sInfectados = (char*) malloc(sizeof(char) * 20);
    char* sMuertos = (char*) malloc(sizeof(char) * 20);
    int esPrimeraLinea = 1;
    int id, recuperados, infectados, muertos;

    do
    {
        fscanf(pFile, "%[^,], %[^,], %[^,], %[^,], %[^,\n]\n", sId, sNombre, sRecuperados, sInfectados, sMuertos);
        if(!esPrimeraLinea)
        {
            sscanf(sId, "%d", &id);
            sscanf(sRecuperados, "%d", &recuperados);
            sscanf(sInfectados, "%d", &infectados);
            sscanf(sMuertos, "%d", &muertos);

            ll_add(listaPaises, pais_newParametros(id, sNombre, recuperados, infectados, muertos));
            totalcargados ++;
        }
        esPrimeraLinea = 0;
    }while(!feof(pFile));

    return totalcargados;
}

