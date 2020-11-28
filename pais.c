#include "pais.h"
#include <stdlib.h>
#include <string.h>


/** \brief Crea un pais con los datos recividos y devuelve un puntero al mismo.
 *
 * \param id int
 * \param sNombre char*
 * \param recuperados int
 * \param infectados int
 * \param muertos int
 * \return ePais*
 *
 */
ePais* pais_newParametros(int id,char* sNombre,int recuperados,int infectados,int muertos)
{
    ePais* paisNuevo = (ePais*) malloc(sizeof(ePais));
    paisNuevo->id = id;
    paisNuevo->infectados = infectados;
    paisNuevo->muertos = muertos;
    paisNuevo->recuperados = recuperados;

    strcpy(paisNuevo->nombre, sNombre);

    return paisNuevo;
}

/** \brief Recibe un pais y checkea si se lo considera exitoso, devuelve 1 si es asi, 0 si no.
 *
 * \param pais void*
 * \return int
 *
 */
int p_filtroExitosos(void* pais)
{
    ePais* aux = (ePais*) pais;
    if(aux->muertos < 5)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/** \brief Recibe un pais y checkea si se lo considera en el horno, devuelve 1 si es asi, 0 si no.
 *
 * \param vPais void*
 * \return int
 *
 */
int p_filtroHorno(void* vPais)
{
    ePais* pais = (ePais*) vPais;

    if((pais->recuperados * 3) < pais->infectados)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/** \brief Compara paises recividos segun cant de infectados para realizar un ordenamiento.
 *
 * \param vPais1 void*
 * \param vPais2 void*
 * \return int
 *
 */
int p_compararPorInfectados(void* vPais1, void* vPais2)
{
    ePais* pais1 = (ePais*) vPais1;
    ePais* pais2 = (ePais*) vPais2;
    int retorno;

    if((pais1->infectados - pais2->infectados) > 0)
    {
        retorno = 1;
    }
    else
    {
        if(pais1->infectados - pais2->infectados == 0)
        {
            retorno = 0;
        }
        else
        {
            retorno = -1;
        }
    }

    return retorno;
}

/** \brief Compara paises recividos segun cant de muertos para realizar un ordenamiento.
 *
 * \param vPais1 void*
 * \param vPais2 void*
 * \return int
 *
 */
int p_compararPorMuertos(void* vPais1, void* vPais2)
{
    ePais* pais1 = (ePais*) vPais1;
    ePais* pais2 = (ePais*) vPais2;
    int retorno;

    if((pais1->muertos - pais2->muertos) > 0)
    {
        retorno = 1;
    }
    else
    {
        if(pais1->muertos - pais2->muertos == 0)
        {
            retorno = 0;
        }
        else
        {
            retorno = -1;
        }
    }

    return retorno;
}

/** \brief carga datos aleatorios en el pais recibido.
 *
 * \param vPais void*
 * \return void*
 *
 */
void* p_cargarDatosAleatorios(void* vPais)
{
    ePais* pais = (ePais*) vPais;
    if(pais != NULL)
    {
        pais->recuperados = rand()%(950 + 1)+50;
        pais->infectados = rand()%(1600 + 1)+400;
        pais->muertos = rand()%(49 + 1)+1;
    }

    return pais;
}
