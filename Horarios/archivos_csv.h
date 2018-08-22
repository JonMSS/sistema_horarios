#include <stdio.h>
#include <string.h>
#include <math.h>
#include "memoria_dinamica.h"
#include "estructuras.h"
#include "matrices_vectores.h"
#include "colas.h"
#include "asignacion.h"

//FILE* f: apuntador global a archivo, sirve para manipular varios archivos
//por lo que se debe cerrar el archivo antes de usarlo para abrir otro
FILE* f;

/*
* VARIABLES Y ESTRUCTURAS DEFINIDAS EN estructuras.h
* struct curso
* struct profesor
* int **C
* int *P
* int **T
* int **PC
* int n_cursos
* int m_prof
* int n_trim
* char *ruta_cursos_csv
* char *ruta_profesores_csv
* char *ruta_prof_cursos_csv
* char *ruta_horario_csv
* struct curso *primero_c
* struct curso *ultimo_c
*/

/*
* DESCRIPCION
* Procedimiento que abre el archivo al que apunta FILE *f
* ---------------------------------------------------------------------------------------
* DATOS
* char ruta_archivo: cadena con la ruta del archivo csv que se desea abrir
* char *modo: sirve para elegir la forma en la que se lee el archivo (r, w, a, r+, w+...)
* ---------------------------------------------------------------------------------------
*/
void abrir_archivo(char *ruta_archivo, char *modo)
{
    f=fopen(ruta_archivo, modo);
    if(f==NULL)
    {
        printf("abrir_archivo: error al abrir el archivo %s\n",ruta_archivo);
        exit(-1);
    }
}

/*
* DESCRIPCION
* Procedimiento que cierra el archivo al que apunta FILE *f
* ---------------------------------------------------------------------------------------
*/
void cerrar_archivo()
{
    fclose(f);
}

/*
* DESCRIPCION
* Funcion que calcula y devuelve el tamano de la cadena mas 1 perteneciente a una linea
  del archivo al que apunta FILE *archivo
* ---------------------------------------------------------------------------------------
* DATOS
* int i: contador de cantidad de caracteres que se deben leer en una linea del archivo
* char c: para guardar el caracter que se esta leyendo en el archivo
* fpos_t posicion: guarda la posicion en el archivo
* ---------------------------------------------------------------------------------------
*/
int tamano_cadena_leer(FILE* archivo)
{
    int i=0;
    char c;
    fpos_t posicion;
    fgetpos(archivo,&posicion); //obtenemos la posicion inicial
    do //continua mientras c es distinto a salto de linea o final del archivo
    {
        c=getc(archivo);
        i++;
    }while(c!=10 && c!=-1);
    fsetpos(archivo,&posicion); //regresamos a la posicion inicial
    if(c==-1) //se llego al final del archivo
        return -1;
    return i;
}

/*
* DESCRIPCION
* Funcion que lee una linea completa del archivo al que apunta FILE *f
  y lo guarda en la cadena a la que apunta char **s
* ---------------------------------------------------------------------------------------
* DATOS
* char **s: apuntador a la cadena de tamano n donde se guardara una linea del archivo *f
* int n: tamano de la cadena s
* ---------------------------------------------------------------------------------------
*/
int leer_cadena_archivo(char **s, FILE *f)
{
    int n; //tamano de la cadena s
    if(f==NULL)
    {
        printf("leer_cadena_archivo: error al abrir el archivo\n");
        exit(-1);
    }
    n=tamano_cadena_leer(f); //se obtiene el tamano mas 1 de la cadena que se desea leer
    if(n==-1) //si es EOF devuelve -1
        return -1;
    memoria_cadena(&(*s),n); //asignamos memoria a la cadena s de tamano n)
    fgets(*s,n,f); //leemos y guardamos la linea del archivo en la cadena s
    getc(f); //no guardo el salto de linea en *s
    return 0;
}

/*
* DESCRIPCION
* Procedimiento que lee desde el archivo rutas_archivo (esta dentro del proyecto)
  las rutas de los archivos csv que contienen los datos de los cursos, profesores y
  la asignacion de los profesores a cursos
* ---------------------------------------------------------------------------------------
*/
void leer_rutas()
{
    int error=0;
    printf("\nVariables de rutas a archivos (ver archivo rutas_archivos)\n");
    abrir_archivo("rutas_csv","r");
    error=leer_cadena_archivo(&ruta_cursos_csv,f);
    printf("\nruta_cursos_csv: %s",ruta_cursos_csv);
    error=leer_cadena_archivo(&ruta_profesores_csv,f);
    printf("\nruta_profesores_csv: %s",ruta_profesores_csv);
    error=leer_cadena_archivo(&ruta_prof_cursos_csv,f);
    printf("\nruta_prof_cursos_csv: %s",ruta_prof_cursos_csv);
    error=leer_cadena_archivo(&ruta_horario_csv,f);
    printf("\nruta_horario_csv: %s\n",ruta_horario_csv);
    if(error==-1)
    {
        printf("\nleer_rutas: error al leer las rutas de los archivos");
        exit(-1);
    }
    cerrar_archivo();
}

/*
* DESCRIPCION
* Funcion que lee los cursos de un trimestre determinado en el archivo csv *f y los guarda en una
  estructura curso
* NOTA IMPORTANTE: se asume que los cursos en el archivo csv de cursos estan ordenados
  ascendentemente respecto al trimestre
* ---------------------------------------------------------------------------------------
* DATOS
* struct curso *c: apuntador a tipo struct curso donde se guardaran los datos del curso
  leido desde el archivo .csv
* int trim: trimestre de los cursos que se guardaran y planificaran
* char *s: cadena de tamano n perteneciente a una linea del archivo csv (*f)
* char *ptr: puntero a subcadena de s delimitada por ","
* ---------------------------------------------------------------------------------------
*/
int leer_curso_csv(struct curso *c, int trim)
{
    char *ptr=NULL,*s=NULL;
    do
    {
        if(s!=NULL) //liberar memoria solo si se le ha asignado anteriormente
            free(s);
        if(leer_cadena_archivo(&s,f)==-1) //se llego al final del archivo
            return -1;
        ptr=strtok(s,","); //devuelve subcadena de s hasta encontrar ","
        if(atoi(ptr)>trim) //se han leido todos los cursos del trimestre trim
            return -1;
    }while(atoi(ptr)!=trim);
    c->trimestre=atoi(ptr); //se guarda el trimestre
    printf("\n\nCurso del trimestre: %d\n",c->trimestre);

    ptr=strtok(NULL,","); //devuelve subcadena de s hasta encontrar ","
    memoria_cadena(&(c->nombre),strlen(ptr)+1); //se asigna memoria para el nombre del trimestre
    strcpy(c->nombre,ptr);
    printf("\nNombre: %s\n",c->nombre);

    ptr=strtok(NULL,","); //devuelve subcadena de s hasta encontrar ","
    c->clave=atoi(ptr); //se guarda la clave del curso
    printf("\nClave: %d\n",c->clave);

    ptr=strtok(NULL,","); //devuelve subcadena de s hasta encontrar ","
    memoria_cadena(&(c->seriacion),strlen(ptr)+1); //se asigna memoria para la seriacion del curso
    strcpy(c->seriacion,ptr);
    printf("\nSeriacion: %s\n",c->seriacion);

    ptr=strtok(NULL,","); //devuelve subcadena de s hasta encontrar ","
    c->horas=atoi(ptr);
    printf("\nCantidad de horas (practicas mas teoricas) p: %d\n",c->horas);

    ptr=strtok(NULL,","); //devuelve subcadena de s hasta encontrar ","
    c->creditos=atoi(ptr);
    printf("\nCreditos: %d\n",c->creditos);

    free(s);
    n_cursos++; //sumamos un curso mas al total (n_cursos es variable global en estructuras.h)
    return 0;
}

/*
* DESCRIPCION
* Procedimiento que crea un elemento de tipo struct curso de determinado trimestre y lo agrega a la cola
* NOTA IMPORTANTE: se asume que los cursos en el archivo csv estan ordenados (ascendentemente) y agrupados
  por trimestre
* ---------------------------------------------------------------------------------------
* DATOS
* int trimestre: trimestre del curso que se desea agregar a la cola
* ---------------------------------------------------------------------------------------
*/
void insertar_curso_cola(int trimestre)
{
    while(1)
    {
        struct curso *nuevo;
        nuevo=(struct curso*)malloc(sizeof(struct curso));
        if(nuevo==NULL)
            exit(-1);
        if(leer_curso_csv(nuevo,trimestre)==-1) //se llego al final del archivo csv o se ha terminado de leer todos los cursos del trimestre
        {
            free(nuevo);
            break;
        }else
        {
            nuevo->siguiente=NULL;
            if(primero_c==NULL) //si la cola no tiene elementos
            {
                primero_c=nuevo;
                ultimo_c=nuevo;
            }else
            {
                (ultimo_c)->siguiente=nuevo;
                ultimo_c=nuevo;
            }//if
        }//if
    }//while
}

/*
* DESCRIPCION
* Funcion que lee los profesores en el archivo csv de profesores que apunta FILE *f y los
  guarda en una estructura profesor
* ---------------------------------------------------------------------------------------
* DATOS
* struct curso *p: apuntador a tipo struct profesor donde se guardaran los datos del profesor
  leido desde el archivo .csv
* char *s: cadena de tamano n perteneciente a una linea del archivo csv
* char *ptr: puntero a subcadena de s delimitada por ","
* int i,j: contadores
* ---------------------------------------------------------------------------------------
*/
int leer_profesor_csv(struct profesor *p)
{
    char *ptr,*s=NULL;
    int i,j;

    if(leer_cadena_archivo(&s,f)==-1) //se llego al final del archivo
        return -1;

    ptr=strtok(s,","); //devuelve subcadena de s hasta encontrar ","
    p->clave=atoi(ptr); //se guarda la clave del profesor (no. economico)

    ptr=strtok(NULL,","); //devuelve subcadena de s hasta encontrar ","
    memoria_cadena(&(p->nombre),strlen(ptr)+1); //se asigna memoria para el nombre del profesor
    strcpy(p->nombre,ptr);

    memoria_matriz_int(&(p->D),6,5); //asignamos memoria a la matriz D (disponibilidad de horario)
    inicializar_matriz(p->D,6,5,1); //hasta aqui en todas las horas del horario, el profesor esta disponible (se iniciliza con 1 a la matriz D)
    for(i=0;i<5;i++)
    {
        ptr=strtok(NULL,","); //devuelve subcadena de s hasta encontrar ","
        if(atoi(ptr)==0) //si encontramos un dia de no disponibilidad
        {
            for(j=0;j<6;j++)
            {
                p->D[j][i]=-1;//indicamos que todo el dia i-esimo no puede impartir cursos
            }//for
        }//if
    }//for

    free(s);
    m_prof++; //sumamos un profesor mas al total (n_prof es variable global en estructuras.h)
    return 0;
}

/*
* DESCRIPCION
* Procedimiento que crea un elemento de tipo struct profesor y lo agrega a la cola
* ---------------------------------------------------------------------------------------
*/
void insertar_profesor_cola()
{
    while(1)
    {
        struct profesor *nuevo;
        nuevo=(struct profesor*)malloc(sizeof(struct profesor));
        if(nuevo==NULL)
            exit(-1);
        if(leer_profesor_csv(nuevo)==-1)
        {
            free(nuevo);
            break;
        }else
        {
            nuevo->siguiente=NULL;
            if(primero_p==NULL) //si la cola no tiene elementos
            {
                primero_p=nuevo;
                ultimo_p=nuevo;
            }else
            {
                (ultimo_p)->siguiente=nuevo;
                ultimo_p=nuevo;
            }//if
        }//if
    }//while
}

/*
* DESCRIPCION
* Procedimiento que lee los cursos que pueden impartir cada profesor
* ---------------------------------------------------------------------------------------
* DATOS
* char *s: cadena de tamano n perteneciente a una linea del archivo csv (*f)
* char *ptr: puntero a subcadena de s delimitada por ","
* int p: clave de profesor
* int c: clave de curso
* int i_p: indice del profesor p en el vector P (ver estructuras.h)
* int j_c: indice del curso c en la matriz C (ver estructuras.h)
* ---------------------------------------------------------------------------------------
*/
void leer_prof_cursos_csv()
{
    char *ptr, *s;
    int i_p,j_c, p, c;
    while(leer_cadena_archivo(&s,f)!=-1)//leer hasta el fin del archivo
    {
        ptr=strtok(s,","); //devuelve subcadena de s hasta encontrar ","
        p=atoi(ptr); //lee la clave del profesor
        printf("Profesor (clave): %d\n",p);

        i_p=buscar_en_vector(&P[0],m_prof,p); //busca al profesor p en el vector P (en estructuras.h) y devuelve su posicion i_p
        if(i_p==-1) //no se encontro el profesor p (i-esimo) en P
        {
                printf("\nleer_prof_cursosCSV: advertencia, el profesor %d no se encuentra en la lista de profesores actual\n",c);
                free(s); //liberamos la memoria asignada a s
                continue;
        }//if
        while((ptr=strtok(NULL,","))!=NULL)//leemos la lista de cursos que puede impartir el profesor p
        {
            c=atoi(ptr); //se guarda el curso
            printf("Curso : %d\n",c);
            j_c=buscar_en_vector(&C[0][0],n_cursos,c); //se busca el curso en la fila 0 de la matriz C
            if(j_c==-1) //no se encontro el curso en C aux_c
            {
                printf("\nleer_prof_cursosCSV:: advertencia, el curso %d asociado al profesor %d no se encuentra en la lista de cursos actual\n",c, p);
                continue;
            }//if
            PC[i_p][j_c]=0; //indicamos con 0 que el profesor i-esimo puede impartir (es candidato) el j-esimo curso
        }//while
        free(s);
    }//while
}

/*
* DESCRIPCION
* Funcion que convierte el indice que corresponde a las horas en la matriz H (horario) a horas de 8:00 a 14:00
*/
int indice_to_horas(int indice_hora)
{
    return indice_hora+8;
}

/*
* DESCRIPCION
* Procedimiento que da formato de horas hh:mm (cadena)
* ---------------------------------------------------------------------------------------
* DATOS
* int hora_i: hora
* char hora_s[6]: cadena con hora_i en formato de hora
* ---------------------------------------------------------------------------------------
*/
void formato_hora(int hora_i, char hora_s[6])
{
    strcpy(hora_s,"");
    sprintf(hora_s,"%02d:00",hora_i);
}

/*
* DESCRIPCION
* Procemiento que asigna a la cadena horario de longitud 60
  el horario completo de la semana de un curso guardado en
  la matriz de horarios H (ver estructuras.h)
* ---------------------------------------------------------------------------------------
* DATOS
* ind d: contador para los dias de la semana
* int h: cotador para las horas por dia
* int inicio: indica el comienzo en horas de la imparticion de un curso
* int fin: indice el final en horas de la imparticion de un curso
* int hora[6]: guarda la cadena de una hora con formato hh:mm
* ---------------------------------------------------------------------------------------
*/
void horario_curso(char horario[60], int clave_curso, int **H)
{
    int d,h,inicio=-1,fin;
    char hora[6];
    strcpy(horario,"");
    for(d=0;d<5;d++)
    {
        for(h=0;h<6;h++)
        {
            if(H[h][d]==clave_curso && inicio==-1) //es el comienzo de la imparticion del curso
            {
                inicio=h;
            }else if(H[h][d]==clave_curso) //es el final de la imparticion del curso
            {
                fin=h;
            }else if(inicio!=-1) //no se encontro asignacion del curso en el dia d
            {
                break;
            }//if
        }//for
        if(d!=0)
            strcat(horario,",");
        if(inicio!=-1)
        {
            formato_hora(indice_to_horas(inicio),hora);
            strcat(horario,hora);
            strcat(horario,"-");
            formato_hora(indice_to_horas(fin),hora);
            strcat(horario,hora);
        }else //no hay horas asignadas en el dia d
        {
            strcat(horario,"-");
        }//if
        inicio=-1;
    }//for
}

/*
* DESCRIPCION
* Metodo que crear el archivo horario.csv usando los horarios ya asignados
* ---------------------------------------------------------------------------------------
* DATOS
* int i_c: indice del curso C[0][i_c] (para matriz C ver estructuras.h)
* int i_p: indce del profesor P[i_p] (para matriz P ver estructuras.h)
* int k: contador auxiliar para i_c, guarda el inicio para cada trimestre en C
* int trim_aux: variable auxiliar para guardar un trimestre anterior al actual
* char horario[60]: cadena para el horario de toda la semana de un curso
* struct curso *curso: apuntador al curso (C[0][i_c]) actual
  (necesario para descargar todos los datos del curso en el archivo .csv del horario)
* struct profesor *prof: apuntador al profesor (P[i_p]) que imparte el curso C[0][i_c]
* ---------------------------------------------------------------------------------------
*/
void crear_horario_csv(struct horario *prim_h)
{
    int i_c=0,i_p,k,l,trim_aux=-1;
    char horario[60];
    struct curso *curso=NULL;
    struct profesor *prof=NULL;
    char head_t[]="NOMBRE DEL CURSO,CLAVE,GRUPO,CUPO,PROFESOR,No. ECON,L,M,M,J,V,HORAS,CREDITOS,SERIACION";
    abrir_archivo(ruta_horario_csv,"w+"); //abrimos/creamos el archivo horario.csv en la ruta ruta_horario_csv (cadena en estructuras.h)
    if(prim_h==NULL)
    {
        printf("\ncrear_horario_csv: error la lista se encuentra vacia\n");
        exit(-1);
    }else
    {
        while(prim_h!=NULL)
        {
            fprintf(f,"%d\n",T[0][prim_h->trimestre]);
            fprintf(f,"%s\n",head_t);
            if(trim_aux==prim_h->trimestre)
                i_c=k;
            k=i_c; //si hay más de un grupo, comenzamos en el inicio del conjunto de cursos para el trimestre prim_h->trimestre
            l=0;
            while(i_c<n_cursos && l<T[2][prim_h->trimestre])
            {
                buscar_curso_cola(C[0][i_c],primero_c,&curso);
                i_p=buscar_asignacion_PC(i_c);
                buscar_profesor_cola(i_p,primero_p,&prof);
                horario_curso(horario,C[0][i_c],(prim_h->H));
                fprintf(f,"%s,%d, , ,%s,%d,%s,%d,%d,%s\n",curso->nombre,curso->clave,prof->nombre,prof->clave, horario,curso->horas,curso->creditos,curso->seriacion);
                l++;
                i_c++;
            }//while
            trim_aux=prim_h->trimestre;
            prim_h=prim_h->siguiente;
        }//while
    }//if
    cerrar_archivo();
}
