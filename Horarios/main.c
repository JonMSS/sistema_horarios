#include <stdio.h>
#include <stdlib.h>
#include "archivos_csv.h"
#include "colas.h"
#include "ordenacion.h"
#include "asignacion.h"

int main()
{
    int i;
    leer_rutas();
    printf("\n\nIntroduzca la cantidad de trimestres que desea programar\n");
    scanf("%d",&n_trim);
    memoria_matriz_int(&T,3,n_trim);

    printf("\nIntroduzca a continuación los trimestres\n");
    for(i=0;i<n_trim;i++)
    {
        printf("\nTrimestre: ");
        scanf("%d",&T[0][i]);
        printf("¿Cuantos grupos se programaran con materias de este trimestre? ");
        scanf("%d",&T[1][i]);
    }

    //Lectura de cursos desde el archivo csv
    printf("\nBuscando cursos...\n");
    for(i=0;i<n_trim;i++)
    {
        abrir_archivo(ruta_cursos_csv,"r");
        printf("\nAgregando cursos del trimestre %d\n",T[0][i]);
        insertar_curso_cola(T[0][i]);
        T[2][i]=n_cursos;//cursos por trimestre
        printf("\nNumero de cursos del trimestre %d: %d\n",T[0][i],T[2][i]);
        cerrar_archivo();
    }
    printf("\nCursos\n");
    imprimir_cursos(primero_c);

    //Lectura de profesores desde el archivo csv
    printf("\n\nProfesores\n");
    abrir_archivo(ruta_profesores_csv,"r");
    insertar_profesor_cola();
    cerrar_archivo();
    imprimir_profesores(primero_p);

    //Creacion de los arreglos C y P
    printf("\n\nConjunto de cursos (matriz C)\n\n");
    memoria_matriz_int(&C,2,n_cursos);
    conjunto_cursos(primero_c);
    ordenar_cursos();
    printf("\nCursos ordenados\n");
    for(i=0;i<n_cursos;i++)
    {
        printf("\n%d %d, ",C[0][i],C[1][i]);
    }

    printf("\n\nConjunto de profesores P\n\n");
    memoria_vector_int(&P, m_prof);
    conjunto_profesores(primero_p);
    imprimir_vector(P,m_prof);

    printf("\n\nLeyendo los cursos que cada profesor puede impartir\n");
    memoria_matriz_int(&PC,m_prof,n_cursos);
    inicializar_matriz(PC,m_prof,n_cursos,-1);
    abrir_archivo(ruta_prof_cursos_csv,"r");
    leer_prof_cursos_csv();
    cerrar_archivo();
    imprimir_matriz(PC,m_prof,n_cursos,0);

    printf("\nASIGNACION DE PROFESORES\n");
    asig_prof_c();
    imprimir_matriz(PC,m_prof,n_cursos,0);
    printf("\n pc_ij=-1: profesor i-esimo no puede impartir curso j-esimo\n");
    printf("\n pc_ij=0: profesor i-esimo es candidato para impartir curso j-esimo\n");
    printf("\n pc_ij=1: profesor i-esimo impartira curso j-esimo\n");

    printf("\nASIGNACION DE HORARIOS FINAL\n");
    asignar_horario();
    imprimir_horarios(primero_h);
    crear_horario_csv(primero_h);
    return 0;
}
