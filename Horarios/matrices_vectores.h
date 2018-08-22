//FUNCIONES PARA VECTORES Y MATRICES DE ENTEROS

/*
* DESCRIPCION
* Procedimiento que iniciliza con un valor a una matriz A de enteros de tamano nxm
* ---------------------------------------------------------------------------------------
*/
void inicializar_matriz(int **A, int n, int m, int a)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            A[i][j]=a;
        }
    }
}

/*
* DESCRIPCION
* Procedimiento que iniciliza con un valor a un vector v de enteros de tamano n
* ---------------------------------------------------------------------------------------
* DATOS
*/
void inicializar_vector(int *v, int n, int a)
{
    int i;
    for(i=0;i<n;i++)
    {
        v[i]=a;
    }
}

/*
* DESCRIPCION
* Procedimiento que busca en un vector de enteros de tamano n el valor a
* ---------------------------------------------------------------------------------------
*/
int buscar_en_vector(int *v, int n, int a)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(a==v[i])
            return i;
    }
    return -1;
}

/*
* DESCRIPCION
* Procemiento que imprime el contenido de una matriz A de enteros de tamano nxm en dos
  formas:
  1: formato para imprimir horarios
  distinto de 1: formato general
* ---------------------------------------------------------------------------------------
*/
void imprimir_matriz(int **A, int n, int m, int formato)
{
    int i,j;
    printf("\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            if(formato==1)
            {
                printf("%07d  ",A[i][j]);
            }else
            {
                printf("%d  ",A[i][j]);
            }
        }
        printf("\n");
    }
}

/*
* DESCRIPCION
* Procedimiento que imprime el contenido de un vector v de enteros de tamano n
* ---------------------------------------------------------------------------------------
*/
void imprimir_vector(int *v, int n)
{
    int i;
    printf("\n");
    for(i=0;i<n;i++)
    {
        printf("%d,  ",v[i]);
    }
    printf("\n");
}
