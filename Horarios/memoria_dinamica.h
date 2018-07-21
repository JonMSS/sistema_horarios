//Procedimiento que asigna memoria a una cadena.
//NOTA: es responsabilidad del programador considerar un espacio mas para incluir con "\0" el final de la cadena
//char **s: cadena
//int n: longitud de la cadena mas 1
void memoria_cadena(char **s, int n)
{
    *s=(char*)malloc(n*sizeof(char));
    if(*s==NULL)
    {
        printf("\nmemoria_cadena: error al asignar memoria\n");
        exit(-1);
    }
}

//Procedimiento que asigna memoria a un vector de enteros
//int **v: vector
//int n: longitud del vector
void memoria_vector_int(int **v, int n)
{
    *v=(int*)malloc(n*sizeof(int));
    if(*v==NULL)
    {
        printf("\nmemoria_vector_int: error al asignar memoria\n");
        exit(-1);
    }
}

//Procedimiento que asigna memoria a una matriz de enteros de nxm
//int ***A: puntero a matriz de nxm
//int n: numero de filas
//int m: numero de columnas
void memoria_matriz_int(int ***A, int n, int m)
{
    int i;
    *A=(int**)malloc(n*sizeof(int*));
    if(*A!=NULL)
    {
        for(i=0;i<n;i++)
        {
            (*A)[i]=(int*)malloc(m*sizeof(int));
        }
    }else
    {
        printf("\nmemoria_matriz_int: error al asignar memoria\n");
        exit(-1);
    }
}
