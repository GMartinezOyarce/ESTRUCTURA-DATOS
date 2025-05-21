#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000
#define MIN 14

struct JuicioOral {
  /*Si la sentencia fue Condenatoria o Absolutoria*/
  char sentencia[MAX];
  char descripcionSentencia[MAX];

  /*si tipoDeJuicio == 0, es un juicio publico
   * si tipodeJuicio == 1, es un juicio privado
   */
  int tipoDeJuicio;

  struct CarpetaInvestigativa *investigacion;
};

/*Lista Simplemente Enlazada*/
struct NodoJuicioOral {
  struct JuicioOral *juicio;
  struct NodoJuicioOral *sig;
};

struct Prueba {
  char tipoDePrueba[MAX];
  char descripcionPrueba[MAX];
  char fecha[MIN];
};

/*Lista Simplemente Enlazada*/
struct NodoPruebas {
  struct Prueba *prueba;
  struct NodoPruebas *sig;
};


struct Resolucion {
  /*EJ: ordenes de detencion, medidas cautelares,
   *autorizacion para diligencias invasivas,
   *asignacion de abogado para imputado*/
  char tipoResolucion[MAX];
  char descripcion[MAX];
  char fecha[MIN];

};

/*Lista simple Circular*/
struct NodoResoluciones {
  struct Resolucion *resolucion;
  struct NodoResoluciones *sig;
};

struct Diligencia {
  /*La persona que pidio la diligencia
   * El fiscal, la victima, el imputado, un abogado, carabineros o PDI
   */
  char OrigenDiligencia[MAX];

  /*Ejemplos: allanamientos, intercepciones Telefonicas, citaciones,
   * toma de declaraciones a victimas, testigos o imputados, peritajes,
   * inspecciones, medidas de proteccion a victimas o testigos
   */
  char tipoDiligencia[MAX];

  char descripcionDiligencia[MAX];

  char fechaDiligencia[MIN];

  /*Si quien pide la diligencia no es el fiscal,
   * la diligencia queda como rechazada pero igualmente se guarda
   * dentro de la carpeta investigativa
   * si declaracion == 1, aprobada
   * si declaracion == 0, rechazada
   */
  int decicion;
};

/*Lista Simplemente enlazada*/
struct NodoDiligencias {
  struct Diligencia *diligencia;
  struct NodoDiligencias *sig;
};

struct Declaracion {
  char *rut;
  /*Quien hizo la declaracion, testigo, victima,
   * carabineros, pdi o un tercero
   */
  char origenDeclaracion[MAX];
  char declaracion[MAX];
  char fecha[MIN];
};

/*Lista Simplemente enlazada*/
struct NodoDeclaraciones{
  struct Declaracion *declaracion;
  struct NodoDeclaraciones *sig;
};

struct Imputado{
  /*Rut del imputado*/
  char rut[MIN];
  /*Causa del cual se esta investigando al imputado*/
  char causa[MAX];
  /*Medidas que se tomo para controlar al imputado,
   * como prision preventiva o arraigo
   */
  char medidasCautelares[MAX];


};


struct CarpetaInvestigativa {
  char ruc[MIN];
  /*Posibles Estados de Carpeta:
   * En investigacion , Archivada, Sobreseimiento(Temporal o Permanente)
   * Juicio Oral, Cumplimiento de Sentensia, suspencion Condicional, Acuerdo reparatorio
   */
  char estadoCarpeta[MAX];
  /*Si se hace un sobresimiento, un acuerdo reparatorio, escribir aca la desripcion de la decision*/
  char descripcionEstadoCarpeta[MAX];
  struct Denuncia *denuncia;
  struct Imputado *imputado;
  /*Lista Simplemente enlazada*/
  struct NodoDeclaraciones *declaraciones;
  /*Lista Simplemente enlazada*/
  struct NodoPruebas *pruebas;
  /*Lista Simplemente enlazada*/
  struct NodoDiligencias *diligencias;
  /*Lista Circular*/
  struct NodoResoluciones *resoluciones;
};

/*Arbol binario de carpetas investigativas*/
struct arbolCarpetas {
  struct CarpetaInvestigativa *carpetaInvestigativa;
  struct CarpetaInvestigativa *izq, *der;
};


struct Denuncia{
  /* RUC Para identificar la denuncia*/
  char ruc[MIN];
  /* Rut del denunciante*/
  char denunciante[MAX];
  /*Quien hizo la denuncia*/
  char origenDenunciante[MAX];
  /*Fecha en la que se hizo la denuncia*/
  char fecha[MIN];
  /*Razon por la que se esta denunciando*/
  char *causa;
  /*Estado de la denuncia
   * * En investigacion, cerrada, en juicio o archivada
   */
  char estado[MAX];
  /*Descripcion del Caso*/
  char descripcion[MAX];

  /*Si Imputado == NULL, no se ha identificado al posible responsable,
   * una vez se apruebe la investigacion, el posible responsable pasa a ser imputado
   */
  char rutPosibleResponsable;

 };



struct Peticion {
  char *ruc;
  char *rut;

  /*Quien pidio la peticion (Victima, abogados, pdi, carabineros u otros)*/
  char *origenPeticion;

  /*Tipos de solicitudes:
   * Agregar, borrar o modificar Denuncia
   * Agregar, borrar o modificar Diligencias
   * Agregar o modificar Imputado
   * Agregar Diligencias Judiciales
   * Agregar Pruebas
   * Agregar Declaraciones
   *
   */
  char *tipoSolicitud;

  char descripcionSolicitud[MAX];

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
  char rut[MIN];
  char contrasenia[MAX];
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

/*-----------------------MENUS----------------------------*/
void limpiarPantalla() {
  int i;
  for(i=0;i<20;i++) printf("\n");
}

void menuDenuncias() {
  int opcion;
  do {
    printf("\n--- Gestión de Denuncias ---\n");
    printf("1. Agregar Denuncia\n");
    printf("2. Buscar Denuncia por RUC\n");
    printf("3. Modificar Denuncia\n");
    printf("4. Eliminar Denuncia\n");
    printf("5. Listar Todas las Denuncias\n");
    printf("0. Volver al Menú Principal\n");
    printf("Seleccione una opción: ");
    scanf("%d", &opcion);

    switch(opcion) {
      case 1: /* función agregar denuncia */ break;
      case 2: /* función buscar denuncia */ break;
      case 3: /* función modificar denuncia */ break;
      case 4: /* función eliminar denuncia */ break;
      case 5: /* función listar denuncias */ break;
      case 0: break;
      default: printf("Opción inválida.\n");
    }
  } while(opcion != 0);
}


void mostrarMenuPrincipal() {
  int opcion;
  do {
    printf("\n=== SISTEMA DE GESTIÓN PENAL - MINISTERIO PÚBLICO ===\n");
    printf("1. Registrar / Consultar Denuncias\n");
    printf("2. Gestionar Carpetas Investigativas\n");
    printf("3. Administrar Imputados\n");
    printf("4. Seguimiento de Diligencias\n");
    printf("5. Controlar Estado de Causas\n");
    printf("6. Gestionar Sentencias y Resoluciones\n");
    printf("7. Generar Reportes\n");
    printf("0. Salir\n");
    printf("Seleccione una opción: ");
    scanf("%d", &opcion);

    switch(opcion) {
      case 1: menuDenuncias(); break;
      case 2: /*menuCarpetas()*/; break;
      case 3: /*menuImputados()*/; break;
      case 4: /*menuDiligencias()*/; break;
      case 5: /*menuCausas()*/; break;
      case 6: /*menuSentencias()*/; break;
      case 7: /*generarReportes()*/; break;
      case 0: return ; break;
      default: printf("Opción inválida. Intente nuevamente.\n");
    }
  } while(opcion != 0);
}

int main(){

  return 0;
}