#include <stdio.h>
#include <stdlib.h>

struct Denuncia{
  /* RUC Para identificar la denuncia*/
  char *ruc;
  /* Rut del denunciante*/
  char *denunciante;
  /*Quien hizo la denuncia*/
  char *origenDenunciante;
  /*Fecha en la que se hizo la denuncia*/
  char *fecha;
  /*Si la denuncia sigue en proceso o ya termino,
*   0 = Terminado  1 = Sigue vigente*/
  int estado;
  /*Descripcion del Caso*/
  char *descripcion;
}

int main(){

  return 0;
}