#ifndef COLAS_H
#define COLAS_H
//FUNCIONES PARA COLAS

/*
* DESCRIPCION
* Procedimiento que crea un elemento de tipo struct horario y lo agrega a la cola
* ---------------------------------------------------------------------------------------
* DATOS
* struct horario *nuevo: puntero con la direccion del nuevo elemento para agragar a la cola
* struct horario *primero_h: apuntador al primer elemento de la cola definido en estructuras.h
* struct horario *ultimo_h: apuntador al ultimo elemento de la cola definido en estructuras.h
*/
void insertar_horario_cola(struct horario *nuevo)
{
    if(nuevo==NULL)
        exit(-1);

    nuevo->siguiente=NULL;
    if(primero_h==NULL) //si la cola no tiene elementos
    {
        primero_h=nuevo;
        ultimo_h=nuevo;
    }else
    {
        (ultimo_h)->siguiente=nuevo;
        ultimo_h=nuevo;
    }//if
}

/*
* DESCRIPCION
* Procedimiento que guarda las claves de los cursos y sus horas en la matriz C de 2xn_cursos desde la cola de cursos
* struct curso *primero: apuntador con la direccion del primer elemento de la cola de cursos
* ---------------------------------------------------------------------------------------
* DATOS
* int i: contador
* int trim_aux: guarda el trimestre de las
*/
void conjunto_cursos(struct curso *primero)
{
    int i=0;
    if(primero==NULL)
    {
        printf("\nconjunto_cursos: error la lista se encuentra vacia\n");
        exit(-1);
    }else
    {
        while(primero!=NULL && i<n_cursos)
        {
            C[0][i]=primero->clave;
            C[1][i]=primero->horas;
            primero=primero->siguiente;
            i++;
        }//while
    }//if
}

/*
* DESCRIPCION
* Procedimiento que guarda las claves de los profesores
* ---------------------------------------------------------------------------------------
* DATOS
* struct profesor *primero: apuntador con la direccion del primer elemento de la cola de profesores
* int i: contador
* int m_prof: cantidad de profesores, definida en estructuras.h
*/
void conjunto_profesores(struct profesor *primero)
{
    int i=0;
    if(primero==NULL)
    {
        printf("\nconjunto_profesores: error la lista se encuentra vacia\n");
        exit(-1);
    }else
    {
        while(primero!=NULL && i<m_prof)
        {
            P[i]=primero->clave;
            primero=primero->siguiente;
            i++;
        }//while
    }//if
}

/*
* DESCRIPCION
* Procedimiento que imprime todos los cursos que se encuentran en la cola de cursos
* ---------------------------------------------------------------------------------------
* DATOS
* struct curso *primero: apuntador con la direccion del primer elemento de la cola de cursos
*/
void imprimir_cursos(struct curso *primero)
{
    if(primero==NULL)
    {
        printf("\nimprimir_cursos: error la lista se encuentra vacia\n");
        exit(-1);
    }else
    {
        while(primero!=NULL)
        {
            printf("\n%d, %s, %d, %s, %d, %d\n",primero->trimestre, primero->nombre, primero->clave,primero->seriacion,primero->horas,primero->creditos);
            primero=primero->siguiente;
        }//while
    }//if
}

/*
* DESCRIPCION
* Procedimiento que imprime todos los profesores que se encuentran en la cola de profesores
* ---------------------------------------------------------------------------------------
* DATOS
* struct profesor *primero: apuntador con la direccion del primer elemento de la cola de profesores
*/
void imprimir_profesores(struct profesor *primero)
{
    int i,j;
    if(primero==NULL)
    {
        printf("\nimprimir_profesores: error la lista se encuentra vacia\n");
        exit(-1);
    }else
    {
        while(primero!=NULL)
        {
            printf("%s, %d, ",primero->nombre,primero->clave);
            for(i=0;i<6;i++)
            {
                for(j=0;j<5;j++)
                {
                    printf("%d ",primero->D[i][j]);
                }//for
                printf("\n");
            }//for
            printf("\n");
            primero=primero->siguiente;
        }//while
    }//if
}

/*
* DESCRIPCION
* Procedimiento que imprime todos los horarios que se encuentran en la cola de horarios
* ---------------------------------------------------------------------------------------
* DATOS
* struct horario *primero: apuntador con la direccion del primer elemento de la cola de horarios
*/
void imprimir_horarios(struct horario *primero)
{
    int i,j;
    if(primero==NULL)
    {
        printf("\nimprimir_horarios: error la lista se encuentra vacia\n");
        exit(-1);
    }else
    {
        while(primero!=NULL)
        {
            printf("\n Horario del trimestre %d \n",T[0][primero->trimestre]);
            printf("\n          L        M        M        J        V\n");
            for(i=0;i<6;i++)
            {
                printf("%02d:00-%02d:00  ", 8+i,9+i);
                for(j=0;j<5;j++)
                {
                    if(primero->H[i][j]==0)
                        printf("   -     ");
                    else
                        printf("%07d  ",primero->H[i][j]);
                }//for
                printf("\n");
            }//for
            printf("\n");
            primero=primero->siguiente;
        }//while
    }//if
}

/*
* DESCRIPCION
* Funcion que busca un curso en la cola de cursos,
  si no encuentra el curso con la clave "clave" devuelve -1, si lo encuentra pasa su direccion a c_aux
* ---------------------------------------------------------------------------------------
* DATOS
* int clave: clave del curso que se esta buscando
* struct curso *primero: apuntador con la direccion del primer elemento de la cola de cursos
* struct curso **c_aux: apuntador a apuntador que tendra la direccion del elemento que se busca en la cola
*/
int buscar_curso_cola(int clave, struct curso *primero, struct curso **c_aux)
{
    if(primero==NULL)
    {
        printf("buscar_curso: la lista se encuentra vacia\n");
    }else
    {
        while(primero!=NULL)
        {
            if(primero->clave==clave)
            {
                *c_aux=primero;
                return 0;
            }
            primero=primero->siguiente;
        }
    }
    return -1;
}

/*
* DESCRIPCION
* Funcion que busca un profesor en la cola de profesores,
  si no encuentra el curso con la clave "clave" devuelve -1, si lo encuentra pasa su direccion a p_aux
* ---------------------------------------------------------------------------------------
* DATOS
* int indice_profesor_cola: busca al profesor de acuerdo a su posicion en el vector P
* struct profesor *primero: apuntador con la direccion del primer elemento de la cola de cursos
* struct profesor **p_aux: apuntador a apuntador que tendra la direccion del elemento que se busca en la cola
*/
int buscar_profesor_cola(int indice_profesor, struct profesor *primero, struct profesor **p_aux)
{
    int i=0;
    if(primero==NULL)
    {
        printf("buscar_curso: la lista se encuentra vacia\n");
    }else
    {
        while(primero!=NULL)
        {
            if(i==indice_profesor)
            {
                *p_aux=primero;
                return 0;
            }
            i++;
            primero=primero->siguiente;
        }
    }
    return -1;
}
#endif /* MANIPULAR_ESTRUCTURAS_H */
