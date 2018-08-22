#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

/*
* int **C: matriz de cursos de 2xn_cursos; C[0][i] son las claves de los cursos y C[1][i] son las horas de cada curso
* int *P: vector de profesores (solo claves) de longitud m_prof
* int **T: matriz de 3xn_trim con informacion de cada trimestre; T[0][i]: trimestres,
  T[1][i]: informacion de grupos por trimestre, T[2][i]: cantidad de cursos por trimestre
* int **PC: matriz con la asignacion de profesores a cursos, -1 significa sin asignacion, 0 que es
  candidato a impartir el curso y 1 que impartira el curso.
* int n_cursos: variable para contar la cantidad total de cursos
* int m_prof: variable para contar la cantidad total de profesores
* int n_trim: variable para contar la cantidad total de trimestres que se planificaran
* char *ruta_cursos_csv: cadena con la ruta (para leer) del archivo csv que contiene los datos de los cursos
* char *ruta_profesores_csv: cadena con la ruta (para leer) del archivo csv que contiene los datos de los profesores
* char *ruta_prof_cursos_csv; //cadena con la ruta (para leer) del archivo csv que contiene los datos de asignacion de
  profesor-curso
* char *ruta_horario_csv: cadena con la ruta para guardar archivo csv que contiene los datos de la version preliminar
  del horario
* struct curso *primero_c: apuntador al primer elemento de la cola
* struct curso *ultimo_c: apuntador al ultimo elemento de la cola
*/
int **C=NULL;
int *P=NULL;
int **T=NULL;
int **PC=NULL;

int n_cursos=0;
int m_prof=0;
int n_trim=0;

char *ruta_cursos_csv;
char *ruta_profesores_csv;
char *ruta_prof_cursos_csv;
char *ruta_horario_csv;

/*
* DESCRIPCION
* Estructura que guarda los datos de cada curso
* ---------------------------------------------------------------------------------------
* DATOS
* int clave: clave numerica asignada a cada curso
* char *nombre: cadena con el nombre del curso
* int horas: horas que se deben impartir para cada curso (horas practicas mas horas teoricas)
* int creditos: creditos que tiene el curso
* char *seriacion: dependencia contros cursos en el plan de estudios
* int trimestre: trimestre al que pertence el curso
* struct curso *siguiente: apuntador al siguiente curso para crear la cola
*/
struct curso
{
    int clave;
    char *nombre;
    int horas;
    int creditos;
    char *seriacion;
    int trimestre;
    struct curso *siguiente;
}*primero_c=NULL, *ultimo_c=NULL;

/*
* DESCRIPCION
* Estructura que guarda los datos de cada profesor
* ---------------------------------------------------------------------------------------
* DATOS
* int clave: clave numerica asignada a cada profesor
* char *nombre: cadena con el nombre del profesor
* int *D: matriz de disponibilidad de tamano numero de horas por numero de dias (5). La matriz
  es 1 si el profesor esta disponible, -1 no esta disponible un dia completo (se asigna -1 a todo ese dia),
  0 no disponible
* struct profesor *siguiente: apuntador al siguiente profesor para crear la cola
*/
struct profesor
{
    int clave;
    char *nombre;
    int **D;
    struct profesor *siguiente;
}*primero_p=NULL, *ultimo_p=NULL;

/*
* DESCRIPCION
* Estructura que guarda los horarios para grupo de cada trimestre
* ---------------------------------------------------------------------------------------
* DATOS
* int trimestre: indice del trimestre al que pertence el horario y que se hace referencia en la matriz T
* int **H: matriz de horarios de tamano numero de horas por numero de dias (5). En la matriz 0 no hay curso
  asignado y distinto de cero (sera la clave de un curso) hay un curos asignado
* struct horario *siguiente: apuntador al siguiente horario para crear la cola
*/
struct horario
{
    int trimestre;
    int **H;
    struct horario *siguiente;
}*primero_h=NULL, *ultimo_h=NULL;

#endif /* ESTRUCTURAS_H */
