#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this = (LinkedList*) malloc(sizeof(LinkedList));

    if(this== NULL)
    {
        return NULL;
    }

    this->pFirstNode = NULL;
    this->size = 0;

    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this == NULL)
    {
        return returnAux;
    }
    returnAux = this->size;

    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    int listLength = ll_len(this);

    if(this == NULL || nodeIndex < 0 || nodeIndex >= listLength)
    {
        return NULL;
    }

    Node* auxNode = this->pFirstNode;

    for(int i = 0 ; i < nodeIndex; i++ )
    {
        auxNode = auxNode->pNextNode;
    }

    return auxNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    int listLength = ll_len(this);
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->pElement = pElement;
    newNode->pNextNode = NULL;

    if(this == NULL || nodeIndex > (listLength) || nodeIndex < 0 )
    {
        return returnAux;
    }

    returnAux = 0;
    Node* auxNode = this->pFirstNode;
    Node* prevNode = NULL;
    this->size = (this->size + 1);

    for(int i = 0; i < nodeIndex; i++)
    {
        prevNode = auxNode;
        auxNode = auxNode->pNextNode;
    }

    if(nodeIndex == 0)
    {
        this->pFirstNode = newNode;
        newNode->pNextNode = auxNode;
    }
    else
    {
        prevNode->pNextNode = newNode;
        newNode->pNextNode = auxNode;
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    return addNode(this, ll_len(this), pElement);
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    if(getNode(this, index) != NULL )
    {
        return getNode(this, index)->pElement;
    }
    else
    {
        return NULL;
    }

}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {
        Node* auxNode = getNode(this, index);

        if(auxNode != NULL)
        {
            auxNode->pElement = pElement;
            returnAux = 0;
        }
    }

    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    if(this != NULL && index >= 0 && index < ll_len(this))
    {
        Node* nodoARemover = getNode(this, index);

        if(index == 0)
        {
            this->pFirstNode = nodoARemover->pNextNode;
        }
        else
        {
            getNode(this, index - 1)->pNextNode = nodoARemover->pNextNode;
        }
        free(nodoARemover);
        this->size--;
        returnAux = 0;
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    if(this == NULL)
    {
        return returnAux;
    }

    returnAux = 0;

    Node* auxNode = this->pFirstNode;
    Node* nodoABorrar = auxNode;

    while(auxNode != NULL)
    {
        auxNode = auxNode->pNextNode;
        free(nodoABorrar);
        nodoABorrar = auxNode;
    }

    this->size = 0;
    this->pFirstNode = NULL;


    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this == NULL)
    {
        return returnAux;
    }
    returnAux = 0;

    ll_clear(this);

    free(this);

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this == NULL)
    {
        return returnAux;
    }

    int encontrado  = 0;
    int i = 0;
    void * auxElement;

    while(!encontrado && i < ll_len(this))
    {
        auxElement = ll_get(this, i);
        if(auxElement == pElement)
        {
            encontrado = 1;
            returnAux = i;
        }
        i++;
    }

    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
        if(ll_len(this) > 0)
        {
            returnAux = 0;
        }
        else
        {
            if(ll_len(this) == 0)
            {
                returnAux = 1;
            }
        }
    }


    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    if(this == NULL || index > ll_len(this) || index < 0)
    {
        return returnAux;
    }
    returnAux = addNode(this, index, pElement);

    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    Node* nodoAnterior = NULL;
    if(index > 0)
    {
        nodoAnterior = getNode(this, index - 1);
    }
    Node* nodoARemover = getNode(this, index);

    if( (nodoARemover != NULL && nodoAnterior != NULL) || (nodoARemover != NULL && index == 0) )
    {
        if(index == 0)
        {
            this->pFirstNode = nodoARemover->pNextNode;
        }
        else
        {
            nodoAnterior->pNextNode = nodoARemover->pNextNode;
        }
        this->size = (this->size - 1);
        returnAux = nodoARemover->pElement;
    }

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this == NULL)
    {
        return returnAux;
    }

    int index = ll_indexOf(this, pElement);

    if(pElement == NULL)
    {
        return 0;
    }

    if(index >= 0)
    {
        returnAux = 1;
    }
    else
    {
        returnAux = 0;
    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    if(this == NULL || this2 == NULL)
    {
        return returnAux;
    }
    int estanContenidos = 1;

    Node* auxNode = this2->pFirstNode;
    while(estanContenidos && auxNode != NULL)
    {
        if(!ll_contains(this, auxNode->pElement) )
        {
            estanContenidos = 0;
        }
        auxNode = auxNode->pNextNode;
    }
    returnAux = estanContenidos;

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{

    if(this == NULL || from < 0 || from > ll_len(this) - 1 || from > to || to > ll_len(this))
    {
        return NULL;
    }
    LinkedList* cloneArray = ll_newLinkedList();

    void* pElementAux;

    for(int i = from; i < to; i++)
    {
        pElementAux = ll_get(this, i);
        ll_add(cloneArray, pElementAux);
    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    if(this == NULL)
    {
        return cloneArray;
    }

    cloneArray = ll_subList(this, 0 , ll_len(this));



    return cloneArray;
}

void ll_swapWithNext(LinkedList* this, int index)
{
    if(index >= 0 && index < ll_len(this) - 1 && this != NULL)
    {
        void* auxElement1 = ll_get(this, index);
        void* auxElement2 = ll_get(this, index + 1);

        ll_set(this , index, auxElement2);
        ll_set(this, index + 1, auxElement1);
    }

}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    if(this == NULL || pFunc == NULL || (order != 1 && order != 0) )
    {
        return returnAux;
    }

    returnAux = 0;
    int ordenada = 0;
    int compareValue;
    int largo = ll_len(this);
    if(largo > 1)
    {
        while(!ordenada)
        {
            ordenada = 1;
            for(int j = 0; j < largo - 1; j++)
            {
                compareValue = pFunc(ll_get(this, j), ll_get(this, j + 1));
                if(compareValue == 1 && order)
                {
                    ll_swapWithNext(this, j);
                    ordenada = 0;
                }
                else
                {
                    if(compareValue == -1 && !order)
                    {
                        ll_swapWithNext(this, j);
                        ordenada = 0;
                    }
                }
            }
        }
    }
    return returnAux;
}

/** \brief Crea una nueva lista con los elementos que cumplan la condicion recibida como funcion.
 *
 * \param element void*
 * \return LinkedList* ll_filter(LinkedList* lista, int
 *
 */
LinkedList* ll_filter(LinkedList* lista, int (*pFunc)(void* element))
{
    if(lista != NULL && pFunc != NULL)
    {
        LinkedList* listaFiltrada = ll_newLinkedList();
        int largo = ll_len(lista);
        for(int i = 0; i < largo; i++)
        {
            if(pFunc(ll_get(lista, i)))
            {
                ll_add(listaFiltrada, ll_get(lista, i));
            }
        }

        return listaFiltrada;

    }
    else
    {
        return NULL;
    }
}

/** \brief Crea una nueva lista con los paises de la primera con datos ya cargados y borra la lista en blanco recibida.
 *
 * \param listaEnBlanco LinkedList*
 * \param (*pFunc void*
 * \return LinkedList*
 *
 */
LinkedList* ll_map(LinkedList* listaEnBlanco, void* (*pFunc) (void* element))
{
    LinkedList* listaCargada = ll_newLinkedList();
    int largo = ll_len(listaEnBlanco);
    for(int i = 0; i < largo ; i++)
    {
        ll_add(listaCargada, pFunc(ll_get(listaEnBlanco, i)));
    }

    ll_deleteLinkedList(listaEnBlanco);

    return listaCargada;
}
