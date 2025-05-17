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
  /*Estado de la denuncia*/
  char *estado;
  /*Descripcion del Caso*/
  char *descripcion;
  /*Si Imputado == NULL, no se ha identificado al imputado*/
  struct Imputado *imputado;
 }

/*Lista Simplemente enlazada*/
struct NodoDeclaraciones{
  char *declaracion;
  struct NodoDeclaraciones *sig;
}
/*Lista Circular Simplemente enlazada de imputados*/
struct NodoImputados{
  struct Imputado *imputado;
  struct NodoImputados *sig;
}

struct Imputado{
  /*Denuncia que se acuso al Imputado*/
  struct Denuncia *denuncia;
  /*Rut del imputado*/
  char *rut;
  /*Causa del cual se esta investigando al imputado*/
  char *causa;
  /*Medidas que se tomo para controlar al imputado*/
  char *medidasCautelares;
  /*Estado del caso del imputado*/
  int estado;
  /*Lista simplemente enlazada de declaraciones*/
  struct NodoDeclaraciones *declaraciones;
}


int main(){

  return 0;
}