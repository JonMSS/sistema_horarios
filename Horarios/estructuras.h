#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H
int **C=NULL; //Matriz de cursos de 2xn_cursos; c_0,i son las claves de los cursos y c_1,i son las horas de cada curso
int *P=NULL; //Vector de profesores de longitud m_prof
int **info_trim=NULL; //Matriz de 3xn_trim con informacion de cada trimestre; info_trim[0][i]: trimestres, info_trim[1][i]: grupos por trimestre, info_trim[2][i]: cantidad de cursos por trimestre
int **PC=NULL; //Matriz con la asignacion de profesores a cursos, -1 significa sin asignacion, 0 que es candidato a impartir el curso y 1 que impartira el curso

int n_cursos=0; //cantidad de cursos
int m_prof=0; //cantidad de profesores
int n_trim=0; //cantidad de trimestres

char *ruta_cursos_csv; //cadena con la ruta (para leer) del archivo csv que contiene los datos de los cursos
char *ruta_profesores_csv; //cadena con la ruta (para leer) del archivo csv que contiene los datos de los profesores
char *ruta_prof_cursos_csv; //cadena con la ruta (para leer) del archivo csv que contiene los datos de asignacion de profesor-curso
char *ruta_horario_csv; //cadena con la ruta para guardar archivo csv que contiene los datos de la version preliminar del horario


struct curso
{
    int clave;
    char *nombre;
    int horas; // horas practicas mas horas teoricas
    int creditos;
    char *seriacion;
    int trimestre;
    struct curso *siguiente;
}*primero_c=NULL, *ultimo_c=NULL;

struct profesor
{
    int clave; //no. economico
    char *nombre;
    int **D; //matriz de disponibilidad de tamano numero de horas por dias (5), 1 si esta disponible, -1 no disponible un dia, 0 no disponible
    struct profesor *siguiente;
}*primero_p=NULL, *ultimo_p=NULL;

struct horario
{
    int trimestre; //indice del trimestre en la matriz info_trim
    int **H; //matriz de horarios de tamano numero de horas por dias (5)
    struct horario *siguiente;
}*primero_h=NULL, *ultimo_h=NULL;

#endif /* ESTRUCTURAS_H */
