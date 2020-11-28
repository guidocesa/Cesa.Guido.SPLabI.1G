#ifndef PAIS_H_INCLUDED
#define PAIS_H_INCLUDED

typedef struct
{
    int id;
    char nombre[128];
    int recuperados;
    int infectados;
    int muertos;
}ePais;

ePais* pais_newParametros(int id,char* sNombre,int recuperados,int infectados,int muertos);
int p_filtroExitosos(void* pais);
int p_filtroHorno(void* pais);
int p_compararPorInfectados(void* vPais1, void* vPais2);
int p_compararPorMuertos(void* vPais1, void* vPais2);
void* p_cargarDatosAleatorios(void* vPais);


#endif // PAIS_H_INCLUDED
