//FUNCIONES PARA VECTORES Y MATRICES

/*
* DESCRIPCION
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
