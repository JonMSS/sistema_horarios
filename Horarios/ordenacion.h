/*
* DESCRIPCION
* Procedimiento que ordena la matriz C en orden descendente respecto a las horas de
  cada curso mediante el algoritmo shell
* ---------------------------------------------------------------------------------------
* DATOS
* int **A: matriz de 2xn para ordenar pespecto a la 2da fila
* int intervalo: define el tamano de las particiones
* int n: igual a n_cursos
* int i,j,k: contadores
* int aux_c, aux_h: auxiliares para intercambiar los valores en la matriz C
* ---------------------------------------------------------------------------------------
*/
void shell_cursos(int **A, int n)
{
    int intervalo, i,j,k, aux_c, aux_h;
    intervalo=n/2;
    while(intervalo>0)
    {
        for(i=intervalo;i<n;i++)
        {
            j=i-intervalo; //contador en extremo izquierdo de la particion
            while(j>=0)
            {
                k=j+intervalo; //contador en extremo derecho de la particion
                if(A[1][j]>=A[1][k]) //si es mayor el elemento del extremo izquierdo respecto al del derecho, se pasa al siguiente elemento
                {
                    j=-1;
                }else //de los contrario, se intercambian
                {
                    aux_c=A[0][j];
                    aux_h=A[1][j];

                    A[0][j]=A[0][k];
                    A[1][j]=A[1][k];

                    A[0][k]=aux_c;
                    A[1][k]=aux_h;
                    j-=intervalo;
                }//if
            }//while
        }//for
        intervalo=intervalo/2;
    }//while
}

/*
* DESCRIPCION
* Procedimiento que extrae los cursos de cada trimestre guardados en la matriz C para
  ordenarlos (usando shell_cursos) respecto a la cantidad de horas que tienen
* ---------------------------------------------------------------------------------------
* DATOS
* int **aux: es una matrix auxiliar que guarda los datos de los cursos de un determinado trimestre
* int n_trim: cantidad de trimestres, definida en estructuras.h
* int T: matriz de 3xn_trim, con informacion de los trimestres, definida en estructuras.h
* int i: contador de trimestres (<n_trim)
* int j: contador de cursos (<n_cursos)
* int k: contador de cursos (k<=j<n_cursos)
* ---------------------------------------------------------------------------------------
*/
void ordenar_cursos()
{
    int **aux,i,j=0,k=0,l;
    for(i=0;i<n_trim;i++) //recorremos los trimestres
    {
        memoria_matriz_int(&aux,2,T[2][i]); //le damos a aux el tamaño para guardar los cursos del trimestre i-esimo
        k=j; //respaldamos el indice del primer elemento del trimestre i-esimo en la matriz C
        l=0;
        while(j<n_cursos && l<T[2][i]) //copiamos en aux los cursos y sus horas del trimestre i-esimo desde la matriz C
        {
            aux[0][l]=C[0][j];
            aux[1][l]=C[1][j];
            j++;
            l++;
        }//while
        shell_cursos(aux,T[2][i]); //ordena los cursos del trimestre i-esimo
        l=0;
        //if(k!=0)
            //aux[0][l]=-aux[0][l];
        while(k<n_cursos && l<T[2][i]) //copiamos en C los cursos y sus horas del trimestre i-esimo, ordenanos, desde aux
        {
            C[0][k]=aux[0][l];
            C[1][k]=aux[1][l];
            k++;
            l++;
        }//while
        free(aux);
    }//for
}
