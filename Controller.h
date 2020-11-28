#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED
#include "pais.h"

int controller_loadFromText(char* path , LinkedList* listaPaises);
int controller_ListarPaises(LinkedList* listaPaises);
int controller_saveAsText(char* path , LinkedList* listaPaises);
void controller_filtrarPaisesExitosos(LinkedList* listaPaises);
void controller_filtrarPaisesEnHorno(LinkedList* listaPaises);
void controller_pedirNombreArchivo(char* nombre);
void controller_mostrarPais(ePais* auxPais);

#endif // CONTROLLER_H_INCLUDED
