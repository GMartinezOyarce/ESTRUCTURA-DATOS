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
  /*Razon por la que se esta denunciando*/
  char *causa;
  /*Estado de la denuncia
   * * En investigacion, cerrada, en juicio o archivada
   */
  char *estado;
  /*Descripcion del Caso*/
  char *descripcion;

  /*Si Imputado == NULL, no se ha identificado al posible responsable,
   * una vez se apruebe la investigacion, el posible responsable pasa a ser imputado
   */
  int *rutPosibleResponsable;

 };

/*Lista Simplemente enlazada*/
struct NodoDeclaraciones{
  char *declaracion;
  struct NodoDeclaraciones *sig;
};
/*Lista Circular Simplemente enlazada de imputados*/
struct NodoImputados{
  struct Imputado *datosImputado;
  struct NodoImputados *sig;
};



struct Imputado{
  /*Denuncia que se acuso al Imputado*/
  char *ruc;
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
};

struct Peticion {
  char *ruc;
  char *rut;
  /*Quien pidio la peticion (Victima, abogados, pdi, carabineros u otros)*/
  char *origenPeticion;
  char *tipoSolicitud;
  char *descripcionSolicitud;
  /*Si aprobacion == 0, la peticion todavia no se ha revisado
   * Si aprobacion == 1, la peticion se ha aprobado
   * si aprobacion == -1, la peticion se ha rechazado
   */
  int aprobacion;
};
/*Lista Simple con nodo Fantasma*/
struct NodoPeticiones {
  struct Peticion *peticion;
  struct NodoPeticiones *sig;
};



struct Fiscal {
  int rut;
  char *contrasenia;
  /*Lista simplemente enlazada con nodo fantasma*/
  struct NodoPeticiones *Peticiones;
  /*lista simplemente enlazada, Posiblemente se cambie a circular doblemente enlazada,
   * porque en este caso solo se agregan denuncias, no se eliminan
   */
  struct NodoDenuncias *Denuncias;
  /*lista simplemente enlazada juicios*/
  struct NodoJuicioOral *Juicios;
  /*arbol binario con carpetas de investigacion*/
  struct ArbolCarpetas *carpetas;
};

/*Struct principal con un arreglo fiscales de tamaño TamFiscal*/
struct MinisterioPublico {
  struct Fiscal **fiscales;
  int tamFiscal;
};

int main(){

  return 0;
}