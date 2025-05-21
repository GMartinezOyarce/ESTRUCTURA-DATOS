#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000 /*ESTOS NOMBRES CREO QUE HAY QUE CAMBIARLOS*/
#define MIN 14

struct JuicioOral {
  /*Si sentencia == 0 es Condenatoria
   *Si sentencia == 1 es Absolutoria*/
  int sentencia;
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
  /*Si Tipo Prueba == 0 es un informe Pericial
   * Si Tipo Prueba == 1 es una grabacion
   * Si Tipo Prueba == 2 es un documento
   * Si Tipo Prueba == 3 es una prueba fisica
   */
  int tipoDePrueba;
  char descripcionPrueba[MAX];
  char fecha[MIN];
};

/*Lista Simplemente Enlazada*/
struct NodoPruebas {
  struct Prueba *prueba;
  struct NodoPruebas *sig;
};


struct Resolucion {
  /*Si Tipo Resolucion == 0 es Sentencia
   * si Tipo Resolucion == 1 es Autorizacion para diligencias
   * si Tipo Resolucion == 2 es una medida Cautelar
   * si tipo Resolucion == 3 es un sobreseimiento
   */
  int tipoResolucion;;

  /*Si origen == 0 la resolucion fue emitida por el Juez de Garantia
   * Si origen == 1 la resolucion fue emitida por el tribunal de Juicio Oral
   */
  int origenResolucion;
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
   *Si Origen Diligencia == 0 lo pidio El fiscal
   *Si origen == 1 lo pidio la victima,
   *Si origen == 2 lo pidioel imputado
   */
  int OrigenDiligencia;

  /*Ejemplos: allanamientos, intercepciones Telefonicas, citaciones,
   * toma de declaraciones a victimas, testigos o imputados, peritajes,
   * inspecciones, medidas de proteccion a victimas o testigos
   *
   * Ya que son demaciados tipos no podemos usar int
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
  /*Si urgencia == 1, es urgencia baja
   * Si urgencia == 2, es urgencia media
   * Si urgencia == 3, es urgencia Alta
   */
  int urgencia;
  /*
   * Si impacto == 1, es de bajo impacto para la investigacion
   * Si impacto == 2 es de medio impacto para la investigacion
   * Si impacto == 3 es de alto impacto para la investigacion
   */
  int impacto;
};

/*Lista Simplemente enlazada*/
struct NodoDiligencias {
  struct Diligencia *diligencia;
  struct NodoDiligencias *sig;
};

struct Declaracion {
  char rut[MIN];
  /*Si declaracion == 0 es una declaracion de la victima
   *Si declaracion == 1 es una declaracion de un testigo
   *Si declaracion == 2 es una declaracion de un imputado
   */
  int origenDeclaracion;
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
  /*Tipo de causa por la que de esta demandando
   * si causa == 0 es un crimen (Infraccion grave)
   * si causa == 1 es un delito simple (Ejemplo:Hurto, estafa)
   * si causa == 2 es una falta (Ejemplo: Infracciones de transito)
   */
  int causa;
  /*Medidas que se tomo para controlar al imputado,
   * como prision preventiva o arraigo
   */
  char medidasCautelares[MAX];


};


struct CarpetaInvestigativa {
  char ruc[MIN];
  /*Posibles Estados de Carpeta:
   *Si estado == 0 En investigacion
   *Si estado == 1 Juicio Oral
   *Si estado == 2 Archivada
   *Si estado == 3 Cerrada
   */
  int estadoCarpeta;
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
  struct CarpetaInvestigativa*carpetaInvestigativa;
  struct arbolCarpetas *izq, *der;
};


struct Denuncia{
  /* RUC Para identificar la denuncia*/
  char ruc[MIN];
  /* Rut del denunciante*/
  char denunciante[MIN];
  /*Si origen Denunciante == 0 denuncio una victima
   * Si origen Denunciante == 1 denuncio un testigo
   * Si origen Denunciante == 2 denuncio un tercero
   * Si origen Denunciante == 3 denuncio Carabineros
   * Si origen Denunciante == 4 denuncio PDI
   */
  int origenDenunciante;
  /*Fecha en la que se hizo la denuncia*/
  char fecha[MIN];

  /*Tipo de causa por la que de esta demandando
   * si causa == 0 es un crimen (Infraccion grave)
   * si causa == 1 es un delito simple (Ejemplo:Hurto, estafa)
   * si causa == 2 es una falta (Ejemplo: Infracciones de transito)
   */
  int causa;
  /*Posibles Estados de Denuncia:
  *Si estado == 0 En investigacion
  *Si estado == 1 Juicio Oral
  *Si estado == 2 Archivada
  *Si estado == 3 Cerrada
  */
  int estadoDenuncia;
  /*Descripcion del Caso*/
  char descripcion[MAX];


 };

struct NodoDenuncias {
  struct Denuncia *denuncia;
  struct NodoDenuncias *sig;
};


struct Peticion {
  char ruc[MIN];
  char rut[MIN];

  /*Quien pidio la peticion
   Si origen == 0 la Victima o su abogado hizo la peticion
   Si origen == 1 el imputado o su abogado hizo la peticion*/
  int origenPeticion;

  /*Tipos de solicitudes:
   * Si tipo Solicitud == 0, es para revicion de la carpeta
   * Si tipo Solicitud == 1, es para solicitar diligencias adicionales
   */
  int tipoSolicitud;

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
  struct arbolCarpetas *carpetas;
};

/*Struct principal con un arreglo fiscales de tamaño TamFiscal*/
struct MinisterioPublico {
  struct Fiscal **fiscales;
  int tamFiscal;
};
/*-----------------------FUNCIONES DE DENUNCIAS----------------------------*/
void agregarDenuncia(){
}



/*-----------------------FUNCIONES DE MENUS----------------------------*/
void limpiarPantalla() {
  int i;
  for(i=0;i<20;i++) printf("\n");
}
struct CarpetaInvestigativa* BUSCARCARPETA(struct arbolCarpetas *raiz, char *ruc) {
  if (raiz == NULL) return NULL;

  int cmp = strcmp(ruc, raiz->carpetaInvestigativa->ruc);
  if (cmp == 0) return raiz->carpetaInvestigativa;
  if (cmp < 0) return BUSCARCARPETA(raiz->izq, ruc);
  return BUSCARCARPETA(raiz->der, ruc);
}

/* Limpiar el buffer de entrada después de un scanf()*/
void limpiarBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

/* Esperar a que el usuario presione Enter*/
void esperarEnter() {
  printf("\nPresione Enter para continuar...\n");
  limpiarBuffer(); /* Consume el '\n' previo si existe*/
  getchar(); /* Espera a que el usuario presione Enter*/
}

/*Función para buscar una denuncia por RUC en la lista de denuncias del fiscal*/
struct Denuncia* BUSCARDENUNCIA(struct Fiscal *fiscal, char *ruc) {
  struct NodoDenuncias *actual = fiscal->Denuncias;
  while (actual != NULL) {
    if (strcmp(actual->denuncia->ruc, ruc) == 0) {
      return actual->denuncia;
    }
    actual = actual->sig;
  }
  return NULL;
}
/*---------------------FUNCIONES SOBRE CARPETAS----------------*/

/*---------------------FUNCION CREAR CARPETA


/* Función para crear una nueva carpeta investigativa*/
void CrearCarpeta(struct Fiscal *fiscal) {
    char rucBusqueda[MIN];
    struct Denuncia *denunciaEncontrada = NULL;
    struct CarpetaInvestigativa *nuevaCarpeta = NULL;
    struct arbolCarpetas *actual = NULL;
    struct arbolCarpetas *nuevoNodo = NULL;
    int opcion;

    /* Paso 1: Buscar la denuncia por RUC*/
    do {
        limpiarPantalla();
        printf("---------------CREAR CARPETA INVESTIGATIVA-------------------\n");
        printf("Ingrese el RUC de la denuncia asociada (formato: 123456789-2025): ");
        fgets(rucBusqueda, MIN, stdin);
        rucBusqueda[strcspn(rucBusqueda, "\n")] = 0;

        denunciaEncontrada = BUSCARDENUNCIA(fiscal, rucBusqueda);

        if (denunciaEncontrada == NULL) {
            printf("\nNo se encontro ninguna denuncia con el RUC %s\n", rucBusqueda);
            printf("1. Intentar nuevamente\n");
            printf("2. Volver al menu anterior\n");
            printf("Seleccione una opcion: ");


            scanf("%d", &opcion);
            limpiarBuffer();


            if (opcion == 2) {
                return; // Salir de la función si el usuario elige volver
            }
        }
    } while (denunciaEncontrada == NULL);

    limpiarPantalla();

    /* Paso 2: Crear la nueva carpeta investigativa*/
    nuevaCarpeta = (struct CarpetaInvestigativa*)malloc(sizeof(struct CarpetaInvestigativa));

    /* Copiar el RUC de la denuncia*/
    strcpy(nuevaCarpeta->ruc, denunciaEncontrada->ruc);

    /* Asignar la denuncia encontrada*/
    nuevaCarpeta->denuncia = denunciaEncontrada;

    /* Inicializar otros campos*/
    nuevaCarpeta->declaraciones = NULL;
    nuevaCarpeta->pruebas = NULL;
    nuevaCarpeta->diligencias = NULL;
    nuevaCarpeta->resoluciones = NULL;
    nuevaCarpeta->imputado = NULL;
    nuevaCarpeta-> estadoCarpeta = 0;


    /* Paso 3: Insertar la carpeta en el árbol*/
    if (fiscal -> carpetas == NULL) {
        // Crear el árbol si no existe
        fiscal -> carpetas = (struct arbolCarpetas*)malloc(sizeof(struct arbolCarpetas));
        fiscal -> carpetas -> carpetaInvestigativa = nuevaCarpeta;
        fiscal -> carpetas -> izq = NULL;
        fiscal -> carpetas -> der = NULL;
    }
    else {
        /* Insertar en el árbol binario ordenado por RUC*/
        actual = fiscal -> carpetas;
        nuevoNodo = (struct arbolCarpetas*)malloc(sizeof(struct arbolCarpetas));
        nuevoNodo->carpetaInvestigativa = nuevaCarpeta;
        nuevoNodo->izq = NULL;
        nuevoNodo->der = NULL;

        while (actual != NULL) {
            if (strcmp(nuevaCarpeta->ruc, actual->carpetaInvestigativa->ruc) < 0) {
                if (actual->izq == NULL) {
                    actual->izq = nuevoNodo;
                    break;
                } else {
                    actual = actual->izq;
                }
            } else {
                if (actual->der == NULL) {
                    actual->der = nuevoNodo;
                    break;
                } else {
                    actual = actual->der;
                }
            }
        }
    }

    printf("\n¡Carpeta investigativa creada con exito!\n");
    printf("Presione Enter para continuar...");
    getchar();
}


/*-----------------------------FUNCION AGREGAR DECLARACION------------------*/

void agregarDeclaracion(struct Fiscal *fiscal) {
  struct Declaracion *nuevo = NULL;
  struct NodoDeclaraciones *nodo = NULL;
  struct NodoDeclaraciones *rec = NULL;
  struct CarpetaInvestigativa *carpeta = NULL;
  char rucCarpeta[14];

  limpiarPantalla();
  getchar();

  if (fiscal -> carpetas == NULL) {
    printf("No hay carpetas a las que pueda agregarle una Declaracion");
    esperarEnter();
    return;
  }

  nuevo = (struct Declaracion*)malloc(sizeof(struct Declaracion));
  nodo = (struct NodoDeclaraciones*)malloc(sizeof(struct NodoDeclaraciones));

  printf("Ingrese el RUC de su Carpeta\n");
  fgets(rucCarpeta, MIN, stdin);
  rucCarpeta[strcspn(rucCarpeta, "\n")] = 0;

  carpeta = BUSCARCARPETA(fiscal-> carpetas, rucCarpeta);
  if (carpeta == NULL) {
    printf("No se ENCONTRO LA CARPETA");
    esperarEnter();
    return;
  }

  printf("Ingrese RUT del declarante: ");
  fgets(nuevo -> rut, 14, stdin);
  nuevo-> rut[strcspn(nuevo -> rut, "\n")] = 0;

  printf("Ingrese origen (0: Víctima, 1: Testigo, 2: Imputado): ");
  scanf("%d", &nuevo->origenDeclaracion);
  limpiarBuffer();

  printf("Ingrese declaración: ");
  fgets(nuevo->declaracion, MAX, stdin);
  nuevo-> declaracion[strcspn(nuevo-> declaracion, "\n")] = 0;

  printf("Ingrese fecha (dd/mm/aaaa): ");
  fgets(nuevo->fecha, 14, stdin);
  nuevo-> fecha[strcspn(nuevo-> fecha, "\n")] = 0;

  nodo->declaracion = nuevo;
  nodo->sig = NULL;

  if (carpeta->declaraciones == NULL) {
    carpeta->declaraciones = nodo;
  } else {
    rec = carpeta->declaraciones;
    while (rec->sig != NULL) {
      rec = rec->sig;
    }
    rec->sig = nodo;
  }
  printf("Declaración agregada con éxito\n");
  esperarEnter();
}
/*-------------------------FUNCION AGREGAR  DILIGENCIAS-----------------*/
void agregarDiligencia(struct Fiscal *fiscal) {
  struct Diligencia *nueva;
  struct NodoDiligencias *nodo;
  struct CarpetaInvestigativa *carpeta;
  struct NodoDiligencias *rec= NULL;
  char rucCarpeta[14];



  nueva = (struct Diligencia*)malloc(sizeof(struct Diligencia));
  nodo = (struct NodoDiligencias*)malloc(sizeof(struct NodoDiligencias));

  limpiarPantalla();

  printf("Ingrese el RUC de su Carpeta");
  fgets(rucCarpeta, MIN, stdin);
  rucCarpeta[strcspn(rucCarpeta, "\n")] = 0;

  carpeta = BUSCARCARPETA(fiscal-> carpetas, rucCarpeta);
  if (carpeta == NULL) {
    printf("No se ENCONTRO LA CARPETA");
    esperarEnter();
    return;
  }

  printf("Ingrese origen (0: Fiscal, 1: Víctima, 2: Imputado): ");
  scanf("%d", &nueva->OrigenDiligencia);
  limpiarBuffer();

  printf("Ingrese tipo de diligencia: ");
  fgets(nueva->tipoDiligencia, MAX, stdin);
  nueva->tipoDiligencia[strcspn(nueva->tipoDiligencia, "\n")] = 0;

  printf("Ingrese descripción: ");
  fgets(nueva->descripcionDiligencia, MAX, stdin);
  nueva->descripcionDiligencia[strcspn(nueva->descripcionDiligencia, "\n")] = 0;

  printf("Ingrese fecha (dd/mm/aaaa): ");
  scanf("%s", nueva->fechaDiligencia);
  limpiarBuffer();

  printf("Ingrese decisión (1: Aprobada, 0: Rechazada): ");
  scanf("%d", &nueva->decicion);
  limpiarBuffer();

  printf("Ingrese urgencia (1: Baja, 2: Media, 3: Alta): ");
  scanf("%d", &nueva->urgencia);
  limpiarBuffer();

  printf("Ingrese impacto (1: Bajo, 2: Medio, 3: Alto): ");
  scanf("%d", &nueva->impacto);
  limpiarBuffer();

  nodo->diligencia = nueva;
  nodo->sig = NULL;

  if (carpeta->diligencias == NULL) {
    carpeta->diligencias = nodo;
  } else {
    rec = carpeta->diligencias;
    while (rec->sig != NULL) {
      rec = rec->sig;
    }
    rec->sig = nodo;
  }

  printf("\nDiligencia agregada correctamente.\n");
  esperarEnter();
}

/*---------FUNCION AGREGAR RESOLUCION----------------*/
void agregarResolucion(struct Fiscal *fiscal) {
  struct NodoResoluciones *nodo;
  struct NodoResoluciones *rec;
  struct Resolucion *nuevaResolucion;
  struct CarpetaInvestigativa *carpeta;
  char rucCarpeta[14];

  printf("Ingrese el RUC de la carpteta a la que desea agregar una Resolucion");
  fgets(rucCarpeta, MIN, stdin);
  rucCarpeta[strcspn(rucCarpeta, "\n")] = 0;

  carpeta = BUSCARCARPETA(fiscal-> carpetas, rucCarpeta);
  if (carpeta == NULL) {
    printf("CARPETA NO ENCONTRADA.");
    esperarEnter();
    return;
  }

  nodo = (struct NodoResoluciones*)malloc(sizeof(struct NodoResoluciones));
  nuevaResolucion = (struct Resolucion*)malloc(sizeof(struct Resolucion));
  limpiarPantalla();


  printf("/nÏngrese el tipo de resolución:/n ");
  printf("0. Sentencia/n");
  printf("1. Autorizacion para Diligancias/n");
  printf("2. Medida Cautelar/n");
  printf("3. Sobreseimiento/n");
  scanf("%d", &nuevaResolucion->tipoResolucion);
  limpiarBuffer();

  /*Si origen == 0 la resolucion fue emitida por el Juez de Garantia
   * Si origen == 1 la resolucion fue emitida por el tribunal de Juicio Oral
   */
  printf("Ingrese el Origen de la Resolucion/n");
  printf("0. Resolución emitida por Juez de Garantía/n");
  printf("1. Resolución emitida por Tribunal De jucio Oral/n");
  scanf("%d", &nuevaResolucion-> origenResolucion);
  limpiarBuffer();

  printf("Ingrese la Descripcion de su Resolucion/n");
  fgets(nuevaResolucion->descripcion, MAX, stdin);
  nuevaResolucion->descripcion[strcspn(nuevaResolucion->descripcion, "\n")] = 0;

  printf("Ingrese la Fecha de su Resolucion/n");
  fgets(nuevaResolucion->fecha, MAX, stdin);
  nuevaResolucion->fecha[strcspn(nuevaResolucion->fecha, "\n")] = 0;

  nodo->resolucion = nuevaResolucion;
  nodo->sig = NULL;

  if (carpeta->resoluciones == NULL) {
    carpeta->resoluciones = nodo;
  } else {
    rec = carpeta->resoluciones;
    while (rec->sig != NULL) {
      rec = rec->sig;
    }
    rec->sig = nodo;
  }
  printf("Resolución agregada Correctamente");
  esperarEnter();
}
/*-------------------------FUNCION AGREGAR IMPUTADO-----------------------------------------*/
void agregarImputado(struct Fiscal *fiscal) {
  struct Imputado *nuevoImputado;
  struct CarpetaInvestigativa *carpeta;
  char rucCarpeta[MIN];
  limpiarPantalla();

  printf("Ingrese el RUC de su Imputado");
  fgets(rucCarpeta, MIN, stdin);
  rucCarpeta[strcspn(rucCarpeta, "\n")] = 0;

  carpeta = BUSCARCARPETA(fiscal->carpetas, rucCarpeta);
  if (carpeta == NULL) {
    printf("CARPETA NO ENCONTRADA.\n");
    esperarEnter();
    return;
  }

  limpiarPantalla();

  nuevoImputado = (struct Imputado*)malloc(sizeof(struct Imputado));

  printf("Ingrese el RUT del imputado(123456789-8)/n");
  fgets(nuevoImputado-> rut, MIN, stdin);
  nuevoImputado->rut[strcspn(nuevoImputado->rut, "\n")] = 0;

  printf("Ingrese la Causa (Solamente un numero)/n");
  printf("0. Crimen (Infraccion grave)/n");
  printf("1. Delito Simple (Ejemplo: Hurto, estafa)");
  printf("2. Falta (Ejemplo: Infracciones de transito)");
  scanf("%d", nuevoImputado-> causa);
  limpiarBuffer();

  printf("Ingrese las Medidas Cautelares (MAX 1000 caracteres)");
  fgets(nuevoImputado->medidasCautelares, MAX, stdin);
  nuevoImputado->medidasCautelares[strcspn(nuevoImputado-> medidasCautelares, "\n")] = 0;

  carpeta -> imputado = nuevoImputado;

  printf("Imputado Agregar Correctamente.");
  esperarEnter();
}

/*--------------------FUNCION AGREGAR PRUEBA----------------------*/
void agregarPrueba(struct Fiscal *fiscal) {
  struct Prueba *nuevaPrueba;
  struct NodoPruebas *nuevoNodo;
  struct NodoPruebas *rec;
  struct CarpetaInvestigativa *carpeta;
  char rucCarpeta[MAX];
  char enter[1];

  limpiarPantalla();

  printf("Ingrese el RUC de su Imputado ");
  fgets(rucCarpeta, MIN, stdin);
  rucCarpeta[strcspn(rucCarpeta, "\n")] = 0;

  carpeta = BUSCARCARPETA(fiscal->carpetas, rucCarpeta);
  if (carpeta == NULL) {
    printf("CARPETA NO ENCONTRADA.\n");
    esperarEnter();
    return;
  }
  nuevaPrueba = (struct Prueba*)malloc(sizeof(struct Prueba));
  nuevoNodo = (struct NodoPruebas*)malloc(sizeof(struct NodoPruebas));

  printf("Ingrese tipo de prueba (0: Informe, 1: Grabación, 2: Documento, 3: Física): ");
  scanf("%d", &nuevaPrueba->tipoDePrueba);
  limpiarBuffer();

  printf("Ingrese descripción: ");
  fgets(nuevaPrueba->descripcionPrueba, MAX, stdin);
  nuevaPrueba->descripcionPrueba[strcspn(nuevaPrueba->descripcionPrueba, "\n")] = 0;

  printf("Ingrese fecha (dd/mm/aaaa): ");
  scanf("%s", nuevaPrueba->fecha);
  limpiarBuffer();

  nuevoNodo->prueba = nuevaPrueba;
  nuevoNodo->sig = NULL;

  if (carpeta->pruebas == NULL) {
    carpeta->pruebas = nuevoNodo;
  } else {
    rec = carpeta->pruebas;
    while (rec->sig != NULL) {
      rec = rec->sig;
    }
    rec->sig = nuevoNodo;
  }

  printf("La prueba se asigno correctamente");
  esperarEnter();

}
void listarCarpetasRecursivo(struct arbolCarpetas *raiz) {
  struct CarpetaInvestigativa *carpeta;

  /*CASOS BASE*/
  if (raiz == NULL) {
    return;
  }
  /*SE RECORRE DE MANERA IN-ORDER*/
  /*se recorre la parte izquierda de la raiz*/
  listarCarpetasRecursivo(raiz-> izq);
  carpeta = raiz -> carpetaInvestigativa;
  printf("--------------------------------------------------\n");
  printf("RUC: %s\n", carpeta->ruc);
  printf("Estado: ");
  switch (carpeta->estadoCarpeta) {
    case 0: printf("En investigación\n"); break;
    case 1: printf("Juicio Oral\n"); break;
    case 2: printf("Archivada\n"); break;
    case 3: printf("Cerrada\n"); break;
    default: printf("Desconocido\n"); break;
  }
  printf("Descripción Estado: %s\n", carpeta->descripcionEstadoCarpeta);
  if (carpeta->imputado)
    printf("RUT Imputado: %s\n", carpeta->imputado->rut);
  else
    printf("Sin imputado asignado\n");

  // 3. Recorre subárbol derecho
  listarCarpetasRecursivo(raiz->der);
}


void listarCarpetas(struct Fiscal *fiscal) {
  limpiarPantalla();
  printf("=============== LISTADO DE CARPETAS =============");
  if (fiscal-> carpetas == NULL) {
    printf("NO HAY CARPETAS REGISTRADAS");
    return;
  }
  /*el listar Carpetas solo se puede hacer recursivo*/
  listarCarpetasRecursivo(fiscal-> carpetas);

  esperarEnter();
}
/*-------------------------*/

/*----------Funciones MenuCarpeta---------*/

/*--------Función recorrerRut--------*/

void recorrerBuscarRUT(struct arbolCarpetas *nodoArbol, char *rutBuscado) {
  if (nodoArbol == NULL) {
      return;
  }
  recorrerBuscarRUT(nodoArbol->izq, rutBuscado);

  if(nodoArbol->carpetaInvestigativa->imputado != NULL){
    struct Imputado *imputado = nodoArbol->carpetaInvestigativa->imputado;
    if (strcmp(imputado->rut, rutBuscado) == 0) {
      printf("\n--- Imputado Encontrado ---\n");
      printf("RUT: %s\n", imputado->rut);
      printf("Causa: %s\n", imputado->causa);
      printf("Medidas cautelares: %s\n", imputado->medidasCautelares);
      printf("RUC de la carpeta: %s\n", nodoArbol->carpetaInvestigativa->ruc);
    }
  }
  recorrerBuscarRUT(nodoArbol->der, rutBuscado);
}

void buscarImputadoPorRut(struct Fiscal *fiscal){
  char rut[MIN];

  if(fiscal->carpetas == NULL) {
    printf("No hay carpetas registradas.\n");
    return;
  }
  limpiarPantalla();
  printf("=== BUSCAR IMPUTADO POR RUT ===\n");
  printf("Ingrese el RUT del imputado: ");
  fgets(rut, MIN, stdin);
  rut[strcspn(rut, "\n")]= 0;  /*saltar linea de posible espacio*/
  recorrerBuscarRUT(fiscal->carpetas, rut);
}

void mostrarTodosLosImputados(struct arbolCarpetas *nodoArbol){
  if(nodoArbol == NULL) {
    return;
  }

  mostrarTodosLosImputados(nodoArbol->izq);
  struct Imputado *imputado = nodoArbol->carpetaInvestigativa->imputado;
  if(imputado != NULL){
    printf("\n--- IMPUTADO ---\n");
    printf("RUT: %s\n", imputado->rut);
    printf("Causa: %s\n", imputado->causa);
    printf("Medidas Cautelares: %s\n", imputado->medidasCautelares);
    printf("RUC Carpeta: %s\n", nodoArbol->carpetaInvestigativa->ruc);
  }
  mostrarTodosLosImputados(nodoArbol->der);
}

void mostrarTodosImputados(struct Fiscal *fiscal){
  if (fiscal->carpetas == NULL) {
    printf("No hay carpetas registradas.\n");
    return;
  }

  limpiarPantalla();
  printf("=== LISTADO DE IMPUTADOS DEL FISCAL ===\n");
  mostrarTodosLosImputados(fiscal->carpetas);
}



/*-----------------------------------------------------------------------*/
void menuDenuncias() {
  int opcion;
  limpiarPantalla();
  do {
    printf("\n--- Gestión de Denuncias ---\n");
    printf("1. Agregar Denuncia\n");
    printf("2. Buscar Denuncia por RUC\n");
    printf("3. Buscar Denuncia por ESTADO");
    printf("4. Modificar Denuncia\n");
    printf("5. Eliminar Denuncia\n");
    printf("6. Listar Todas las Denuncias\n");
    printf("0. Volver al Menú Principal\n");
    printf("Seleccione una opción: ");
    scanf("%d", &opcion);

    switch(opcion) {
      case 1: /* función agregar denuncia */ break;
      case 2: /* función buscar denuncia RUC */ break;
      case 3: /* funcion buscar denuncia Estado*/ break;
      case 4: /* función modificar denuncia */ break;
      case 5: /* función eliminar denuncia */ break;
      case 6: /* función listar denuncias */ break;
      case 0: break;
      default: printf("Opción inválida.\n");
    }
  } while(opcion != 0);
}

void menuCarpetas(struct Fiscal *fiscal) {
  int opcion;
  limpiarPantalla();
  getchar();

  do {
    printf("\n === Gestion de Carpetas investigativas.\n");
    printf("1. Crear nueva Carpeta Investigativa.\n");
    printf("2. Buscar Carpeta Investigativa por RUC.\n");
    printf("3. Modificar Estado de Carpeta.\n");
    printf("4. Agregar declaración a Carpeta.\n");
    printf("5. Agregar diligencia a Carpeta.\n");
    printf("6. Agregar resolucion a Carpeta.\n");
    printf("7. Agregar imputado a Carpeta;\n");
    printf("8. Agregar Pruebas a Carpeta.\n");
    printf("9. listar todas las Carpetas\n");
    printf("0. Volver al Menu Principal\n");

    scanf("%d", &opcion);

    switch(opcion) {
      case 1: CrearCarpeta(fiscal); break;
      case 2: /*funcion MODIFICAR carpeta RUC */ break;
      case 3: /*funcion MODIFICAR estado Carpeta*/ break;
      case 4: agregarDeclaracion(fiscal); break;
      case 5: agregarDiligencia(fiscal); break;
      case 6: agregarResolucion(fiscal); break;
      case 7: agregarImputado(fiscal); break;
      case 8: agregarPrueba(fiscal); break;
      case 9: listarCarpetas(fiscal); break;
      case 0: /*volver al menu principal*/ break;
      default: printf("Opcion Invalida. Intente Denuevo"); break;
    }
  }while (opcion != 0);
}

void menuImputados(struct Fiscal *fiscal){
  int opcion;
  do {
    printf("\n--- Gestión de Imputados---\n");
    printf("1. Agregar Imputado a una Carpeta Investigativa\n");
    printf("2. Modificar Imputado\n");
    printf("3. Agregar Declaraciones\n");
    printf("4. Buscar Imputado por RUT o Causa\n");
    printf("5. Listar Todos los imputados del Fiscal\n");
    printf("0. Volver al Menú Principal\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);

    switch(opcion) {
      case 1: agregarImputado(fiscal); break;
      case 2: /* función modificautadorImp */ break;
      case 3: agregarDeclaracion(fiscal); break;
      case 4: buscarImputadoPorRut(fiscal); break;
      case 5: mostrarTodosImputados(fiscal); break;
      case 0: break;
      default: printf("Opción inválida.\n");
    }
  }while(opcion != 0);
}

void menuDiligencias(){
  int opcion;
  do{
    printf("--- Gestión de Diligencias ---\n");
    printf("1. Agregar diligencias\n");
    printf("2. Asignar prioridad a Diligencia\n");
    printf("3. Ver diligencias pendientes por carpeta\n");
    printf("4. Ver diligencias ordenadas por Prioridad\n");
    printf("0. Volver al Menú Principal\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);

    switch(opcion) {
      case 1: /* función agregar diligencias */ break;
      case 2: /* función para asignar prioridad a diligencia dependiendo urgencia o impacto */ break;
      case 3: /* función para ver diligencias pendientes */ break;
      case 4: /* función para ver diligencias ordenadas por prioridad dependiendo urgencia o impacto */ break;
      case 0: break;
      default: printf("Opciónnn inválida.\n");
    }
  }while(opcion != 0);
}

void menuCausas() {
  int opcion;
  do {
    printf("\n--- Gestión de Causas ---\n");
    printf("1. Agregar Causa\n");
    printf("2. Buscar Causa por Imputado\n");
    printf("3. Buscar Causa por Denuncia\n");
    printf("4. Modificar Estado de la Causa\n");
    printf("5. Listar Todas las Causas\n");
    printf("0. Volver al Menú Principal\n");
    printf("Seleccione una opción: ");
    scanf("%d", &opcion);

    switch(opcion) {
      case 1: /* función agregar causa */ break;
      case 2: /* función buscar causa imputado */ break;
      case 3: /* función buscar causa denuncia */ break;
      case 4: /* función modificar causa */ break;
      case 5: /* función listar causa */ break;
      case 0: return ;
      default: printf("Opción inválida.\n");
    }
  } while(opcion != 0);
}

void menuSentenciasResoluciones() {
  int opcion;
  do {
    printf("\n--- Gestión de Sentencias y Resoluciones ---\n");
    printf("1. Agregar Sentencia\n");
    printf("2. Agregar Resolucion\n");
    printf("3. Buscar Resolución por Causa\n");
    printf("4. Buscar Resolución por Imputado\n");
    printf("5. Buscar Resolución por Tipo de Resolución\n");
    printf("6. Listar Todas las Sentencias\n");
    printf("7. Listar Todas las Resoluciones\n");
    printf("0. Volver al Menú Principal\n");
    printf("Seleccione una opción: ");
    scanf("%d", &opcion);

    switch(opcion) {
      case 1: /* función agregar sentencia */ break;
      case 2: /* función agregar resolucion */ break;
      case 3: /* función buscar resolución por causa */ break;
      case 4: /* función buscar resolución por imputado */ break;
      case 5: /* función buscar resolución por tipo */ break;
      case 6: /* función listar todas las sentencias */ break;
      case 7: /* función listar todas las resoluciones */ break;
      case 0: return ;
      default: printf("Opción inválida.\n");
    }
  } while(opcion != 0);
}


void mostrarMenuPrincipal(struct Fiscal *fiscal) {
  int opcion;
  limpiarPantalla();
  do {
    printf("\n=== SISTEMA DE GESTION PENAL - MINISTERIO PUBLICO ===\n");
    printf("1. Registrar / Consultar Denuncias\n");
    printf("2. Gestionar Carpetas Investigativas\n");
    printf("3. Administrar Imputados\n");
    printf("4. Seguimiento de Diligencias\n");
    printf("5. Controlar Estado de Causas\n");
    printf("6. Gestionar Sentencias y Resoluciones\n");
    printf("7. Generar Reportes\n");
    printf("0. Salir\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);

    switch(opcion) {
      case 1: menuDenuncias(); break;
      case 2: menuCarpetas(fiscal); break;
      case 3: menuImputados(fiscal); break;
      case 4: menuDiligencias(); break;
      case 5: menuCausas(); break;
      case 6: menuSentenciasResoluciones(); break;
      case 7: /*generarReportes()*/; break;
      case 0: return ;
      default: printf("Opción inválida. Intente nuevamente.\n");
    }
  } while(opcion != 0);
}

/*PARA DATOS DE PRUEBA*/

void inicializarDatosPrueba(struct MinisterioPublico *mp) {
    /* Declarar todas las variables al inicio del bloque */
    struct Fiscal* fiscal;
    struct Denuncia* denuncia;
    struct NodoDenuncias* nodoDenuncia;
    struct CarpetaInvestigativa* carpeta;
    struct Imputado* imputado;
    struct Declaracion* decl;
    struct NodoDeclaraciones* nodoDecl;
    struct Diligencia* dil;
    struct NodoDiligencias* nodoDil;
    struct Resolucion* res;
    struct NodoResoluciones* nodoRes;
    struct arbolCarpetas* arbol;

    /* Inicializar Ministerio Público */
    mp->tamFiscal = 1;
    mp->fiscales = (struct Fiscal**)malloc(sizeof(struct Fiscal*) * 1);

    /* Crear fiscal */
    fiscal = (struct Fiscal*)malloc(sizeof(struct Fiscal));
    strcpy(fiscal->rut, "12345678-9");
    strcpy(fiscal->contrasenia, "pass123");
    fiscal->Peticiones = NULL;
    fiscal->Juicios = NULL;
    fiscal->carpetas = NULL;

    /* Crear denuncia */
    denuncia = (struct Denuncia*)malloc(sizeof(struct Denuncia));
    strcpy(denuncia->ruc, "123456789-2024");
    strcpy(denuncia->denunciante, "98765432-1");
    denuncia->origenDenunciante = 0;
    strcpy(denuncia->fecha, "01/01/2024");
    denuncia->causa = 1;
    denuncia->estadoDenuncia = 0;
    strcpy(denuncia->descripcion, "Robo de computador en oficina");

    /* Enlazar denuncia */
    nodoDenuncia = (struct NodoDenuncias*)malloc(sizeof(struct NodoDenuncias));
    nodoDenuncia->denuncia = denuncia;
    nodoDenuncia->sig = NULL;
    fiscal->Denuncias = nodoDenuncia;

    /* Crear carpeta */
    carpeta = (struct CarpetaInvestigativa*)malloc(sizeof(struct CarpetaInvestigativa));
    strcpy(carpeta->ruc, "123456789-2024");
    carpeta->estadoCarpeta = 0;
    strcpy(carpeta->descripcionEstadoCarpeta, "En investigacion inicial");
    carpeta->denuncia = denuncia;
    carpeta->declaraciones = NULL;
    carpeta->pruebas = NULL;
    carpeta->diligencias = NULL;
    carpeta->resoluciones = NULL;

    /* Crear imputado */
    imputado = (struct Imputado*)malloc(sizeof(struct Imputado));
    strcpy(imputado->rut, "19283746-5");
    imputado->causa = 1;
    strcpy(imputado->medidasCautelares, "Arraigo nacional");
    carpeta->imputado = imputado;

    /* Crear declaracion */
    decl = (struct Declaracion*)malloc(sizeof(struct Declaracion));
    strcpy(decl->rut, "11223344-5");
    decl->origenDeclaracion = 1;
    strcpy(decl->declaracion, "Vi al sospechoso en el lugar de los hechos");
    strcpy(decl->fecha, "02/01/2024");

    nodoDecl = (struct NodoDeclaraciones*)malloc(sizeof(struct NodoDeclaraciones));
    nodoDecl->declaracion = decl;
    nodoDecl->sig = NULL;
    carpeta->declaraciones = nodoDecl;

    /* Crear diligencia */
    dil = (struct Diligencia*)malloc(sizeof(struct Diligencia));
    dil->OrigenDiligencia = 0;
    strcpy(dil->tipoDiligencia, "Allanamiento");
    strcpy(dil->descripcionDiligencia, "Allanamiento domicilio sospechoso");
    strcpy(dil->fechaDiligencia, "03/01/2024");
    dil->decicion = 1;
    dil->urgencia = 3;
    dil->impacto = 3;

    nodoDil = (struct NodoDiligencias*)malloc(sizeof(struct NodoDiligencias));
    nodoDil->diligencia = dil;
    nodoDil->sig = NULL;
    carpeta->diligencias = nodoDil;

    /* Crear resolucion */
    res = (struct Resolucion*)malloc(sizeof(struct Resolucion));
    res->tipoResolucion = 1;
    res->origenResolucion = 0;
    strcpy(res->descripcion, "Autorizacion para allanamiento");
    strcpy(res->fecha, "02/01/2024");

    nodoRes = (struct NodoResoluciones*)malloc(sizeof(struct NodoResoluciones));
    nodoRes->resolucion = res;
    nodoRes->sig = NULL;
    carpeta->resoluciones = nodoRes;

    /* Configurar arbol */
    arbol = (struct arbolCarpetas*)malloc(sizeof(struct arbolCarpetas));
    arbol->carpetaInvestigativa = carpeta;
    arbol->izq = NULL;
    arbol->der = NULL;
    fiscal->carpetas = arbol;

    /* Asignar fiscal */
    mp->fiscales[0] = fiscal;
}
int main(){
  struct MinisterioPublico ministerioPublico;
  inicializarDatosPrueba(&ministerioPublico);
  mostrarMenuPrincipal(ministerioPublico.fiscales[0]);

  return 0;
}