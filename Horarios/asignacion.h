#ifndef ASIGNACION_H
#define ASIGNACION_H

/*
* DESCRIPCION
* Funcion que devuelve el indice del primer elemento que encuentr mas pequeno mayor a cero
* ---------------------------------------------------------------------------------------
* DATOS
* int i: contador
* int menor: indice del primer elemento mas pequeno
* ---------------------------------------------------------------------------------------
*/
int menor(int a[], int n)
{
    int i=0, menor=-1;
    while(i<n)
    {
        if(a[i]>0)
        {
            if(menor==-1)
            {
                menor=i;
            }else if(a[menor]>a[i])
            {
                menor=i;
            }//if
        }//if
        i++;
    }//while
    return menor;
}

/*
* DESCRIPCION
* Procedimiento que asigna los cursos del trimestre a los profesores de tal menera
  que todos los profesores en P tengan la misma cantidad de cursos
* ---------------------------------------------------------------------------------------
* DATOS
* int n_pc[n_cursos]: vector de n_cursos (ver estructuras.h) elementos que contiene la cantidad de profesores que podrían impartir cada curso
* int gc[n_cursos]: vector de n_cursos (ver estructuras.h) elementos que contiene la cantidad de grupos por cada curso
* int p[m_prof]: vector de m_prof (ver estructuras.h) elementos que contiene la cantidad de cursos que se le van asignando a cada profesor
* ---------------------------------------------------------------------------------------
*/
void asig_prof_c()
{
    int i,j=0,k=0, l=0, gc[n_cursos], n_pc[n_cursos], p[m_prof], prof=-1,sum=0;
    inicializar_vector(p,m_prof,0); //inicializa el vector p con ceros
    for(i=0;i<n_cursos;i++) //se guarda la cantidad de grupos por curso
    {
        if(l==T[2][j]) //l llego al final del trimestre T[0][j], avanzamos al trimestre T[0][j+1]
        {
            j++; //avanza al siguiente trimestre
            l=0; //empieza con el primer elemento del siguiente trimestre
        }
        gc[i]=T[1][j]; //guarda la cantidad de grupos por cada curso
        l++;
    }//for
    printf("\nVector gc\n");
    imprimir_vector(gc,n_cursos);
    for(i=0;i<n_cursos;i++)//se guardan en n_pc[] la cantidad total de profesores que podrían impartir cada curso
    {
        for(j=0;j<m_prof;j++)
        {
            if(PC[j][i]==0)//cuenta los profesores candidatos para el curso i
                sum++;
        }
        if(sum<gc[i]) //para verificar que haya la suficiente cantidad de profesores para cada curso
        {
            printf("\nasig_prof_c: error el curso %d solo tiene %d profesores para impartirlo en %d grupos\n",C[0][i],sum,gc[i]);
            exit(-1);
        }
        n_pc[i]=sum; //se guarda el total de profesores candidatos para el curso i
        sum=0;
    }//for
    printf("\nvector n_pc\n");
    imprimir_vector(n_pc,n_cursos);
    printf("\nAsignando profesores a cursos...\n");
    while((i=menor(n_pc,n_cursos))!=-1)//buscamos el curso i-esimo con menos profesores candidatos
    {
        printf("\nAsignando para curso %d con %d profesores candidatos\n",C[0][i],n_pc[i]);
        n_pc[i]=-1; //deja de considerar el curso i-esimo ya que a continuacion se asignara al profesor o profesores
        for(j=0;j<gc[i];j++) //asigna profesores para el curso i para cada grupo
        {
            for(k=0;k<m_prof;k++) //se busca los profesores que pueden impartir el curso i-esimo
            {
                //si el profesor k-esimo es candidato para impartir el curso i-esimo
                if(PC[k][i]==0)
                {
                    //entonces se verifica que el profesor k-esimo sea el de menor cantidad de cursos asignados respecto a los demas profesores hasta el momento
                    if(p[k]==0) //si el profesor k-esimo tiene 0 cursos asignados, se le asigna el curso i
                    {
                        prof=k; //se guarda el profesor k en prof para que el profesor prof imparta el curso i
                        break; //termina la busqueda
                    }
                    if(prof==-1)// si el profesor k-esimo es el primero encontrado se guarda hasta encontrar uno con menor cantidad de cursos a impartir ya asignados
                    {
                        prof=k;
                    }else if(p[k]<p[prof]) //si encuentra uno profesor (k) con menor cantidad de cursos asignados que prof
                    {
                        prof=k;
                    }
                }//if
            }//for
            p[prof]+=1; //prof impatira un curso mas
            PC[prof][i]++;//el profesor prof impartira el curso i
            prof=-1;
        }//for
    }//while
}

/*
* DESCRIPCION
* Funcion que busca en la matriz PC (ver estructuras.h) uno de los profesores asignados al curso index_curso
* ---------------------------------------------------------------------------------------
*/
int buscar_asignacion_PC(int index_curso)
{
    int i;
    for(i=0;i<m_prof;i++)
    {
        if(PC[i][index_curso]==1)
        {
            printf("\nbuscar_asignacion_PC: curso=%d profesor=%d\n",index_curso,i);
            PC[i][index_curso]=2; //ya no se considera en la siguiente busqueda para el curso index_curso
            return i;
        }
    }
    return -1;
}

/*
* DESCRIPCION
* Metodo que restaura la matriz PC (ver estructuras.h) a su estado de solo asignacion profesor-curso
  (unos en lugar de 2)
  Nota: debe ser llamado después de terminar de buscar con la funcion buscar_asignacion_PC
* ---------------------------------------------------------------------------------------
*/
void restaurar_PC()
{
    int i,j;
    for(i=0;i<m_prof;i++)
    {
        for(j=0;j<n_cursos;j++)
        {
            if(PC[i][j]==2)
                PC[i][j]=1;
        }//for
    }//for
}

/*
* DESCRIPCION
* Metodo que obtiene la direccion de la matriz de disponibilidad D (ver estructuras.h)
  del profesor index_prof (es indice de profesor en la matriz P); devuelve la direccion de D
  con el apuntador ptr_D
* ---------------------------------------------------------------------------------------
* DATOS
* int_index_prof: indice de profesor en la matriz P (ver estructuras.h)
* struct profesor *primero: apuntador con la direccion del primer elemento de la cola de
  profesores
* int ***ptr: apuntador que asigna y devuelve la direccion de la matriz de disponibilidad D
*/
void obtener_D_prof(int index_prof, struct profesor *primero, int ***ptr_D)
{
    int i=0;
    if(primero==NULL)
    {
        printf("La lista se encuentra vacia\n");
    }else
    {
        while(primero!=NULL && i!=index_prof)
        {
            primero=primero->siguiente;
            i++;
        }
        *ptr_D=(primero->D);
    }
}

/*
* DESCRIPCION
* Funcion que devuelve el espacio disponible (para las matrices D y H) a partir de la fila (hora) i
  en la columna j (dia)
* ---------------------------------------------------------------------------------------
* Datos
* int **D: matriz de disponibilidad de algun profesor
* in **H: matriz de horario con se esta trabajando
* int i: hora desde la que se empieza a contar
* int j: dia
* int sum: suma para contar las horas disponibles en el dia j a partir de la hora i
*/
int espacio(int **D, int **H, int i, int j)
{
    int sum=0;
    while(i<6 && sum<4) //si sum es 4 hay espacio de sobra, no es necesario contar mas
    {
        if(D[i][j]==1 && H[i][j]==0) //disponible para el profesor y no hay curso asignado en esa hora
        {
            sum+=1;
        }else
            break;
        i++;
    }
    return sum;
}

/*
* DESCRIPCION
* Funcion que asigna los horarios para cada curso de cada grupo de cada trimestre,
  sujeta a las restricciones de
  - disponiblidad de los profesores en la matriz D, dias no disponibles y horas no
    disponibles por impartir otros cursos,
  - cursos en dias no consecutivos,
  - cursos con mas horas primero (se supone que los cursos ya estan
    ordenados ascendentemente respecto a las horas),
  - cantidad de horas maximas a asignar por dia son 3,
  - cantidad de horas minimas a asignar por dia son 2 (es deseable que sean 2 pero es posible asignar 1).
* CONSIDERACIONES IMPORTANTES
  - Al asignar se busca un espacio exacto para la cantidad de horas que se van a asignar,
    si se encuentra un espacio mas grande, se "flexibiliza" el dia, se busca otro dia
    que si tenga el espacio exacto y si no encuentra otro toma el "flexibilizado";
    para ésto se usa el vector control_horas.

* ---------------------------------------------------------------------------------------
* DATOS
* int d: contador de dias en el horario (dia=0,1,2,3 y 4)
* int i: contador para las horas en un determinado dia
* int t: contador de trimestres
* int l: contador de cursos por trimestre (l<T[2][t])
* int g: contador de grupos por trimestre
* int k_c: indice del curso C[0][k_c]
* int k_p: indice del profesor P[k_p]
* int k_c_aux: variable auxiliar para guardar el indice del primer curso correspondiente al trimestre t
  (necesario en caso de que un trimestre tenga más de un grupo)
* int horas: guarda la cantidad de horas totales (al inicio) para cada curso o la cantidad de horas de
  cada curso que faltan por asignar
* int horas_asig: cuenta las horas que se han asignado en un dia para un curso
* int tam_max: es la cantidad maxima (3 o 2) de horas que se pueden asignar por dia a cada curso
* int asigno: (0 o 1) indica con 1 que se ha asignado horas de un curso en un dia, 0 si no.
  Sirve para no asignar horas de un curso en dias consecutivos
* int contro_horas[5]: (0 o 1) lleva el control del espacio disponible en un dia para un curso, 1 indica si un dia
  tiene espacio mayor al necesario (<=4) que se puede considerar para asignar en caso de que los demas dias
  no tengan el espacio necesario exacto, es decir, flexibiliza el criterio de asignar en dias con espacio exacto
* int **D_aux: matriz auxiliar que contiene las restricciones de disponibilidad por dia y por horas del profesor k_p
* ---------------------------------------------------------------------------------------
*/
void asignar_horario()
{
    int i=0, d=0,t,l,g,k_c=0,k_p=0,k_c_aux, horas,horas_asig=0, tam_max,tam=0, asigno=0, control_horas[]={0,0,0,0,0},**D_aux;
    for(t=0;t<n_trim;t++)//asignamos para cada trimestre
    {
        k_c_aux=k_c;//se guarda el inicio del trimestre
        for(g=0;g<T[1][t];g++)//asignamos para cada grupo en cada trimestre
        {
            struct horario *nuevo;
            nuevo=(struct horario*)malloc(sizeof(struct horario)); //se crea nuevo horario
            memoria_matriz_int(&(nuevo->H),6,5); //se asigna memoria a la matriz de horario
            inicializar_matriz(nuevo->H,6,5,0); //se inicializa la matriz H con ceros
            nuevo->trimestre=t; //se guarda el indice del trimestre T[0][t]
            k_c=k_c_aux; //si hay más de un grupo, comenzamos en el inicio del conjunto de cursos para el trimestre t
            l=0;
            while(k_c<n_cursos && l<T[2][t])
            {
                printf("\nAsignando para CURSO: %d\n",k_c);
                horas=C[1][k_c]; //se guardan las horas que deben satisfacer el k_c-esimo curso
                k_p=buscar_asignacion_PC(k_c); //se busca qué profesor puede impartir el c-esimo curso
                printf("\nImpartira el profesor (indice): %d\n",k_p);
                obtener_D_prof(k_p,primero_p,&D_aux); //se obtiene la matriz de disponibilidad D del p-esimo profesor
                //se define la cantidad maxima de horas por dia (tam_max) en funcion de si las horas del curso son pares o impares
                if(horas%2==0)
                    tam_max=2;
                else
                    tam_max=3;
                printf("\nINICIO\n Matriz D de profesor: %d\n",k_p);
                imprimir_matriz(D_aux,6,5,0);
                printf("\nASIGNANDO...\n curso:%d, horas:%d, horas maximas por dia:%d\n",C[0][k_c],horas,tam_max);
                asigno=0;
                while(horas!=0)
                {
                    printf("\n inicio: d=%d\n",d);
                    if(d>4)//dia no debe pasarse del limite (H[6][5]) de columnas de H
                    {
                        d=0;
                        asigno=0;
                        printf("\n IF: reseteo de d\n");
                    }

                    if(D_aux[0][d]==-1) //el profesor no está disponible en el dia "dia"
                    {
                        d++;
                        asigno=0;
                        printf("\n IF: dia no disponible\n");
                        continue;
                    }
                    if(asigno==1) //avanza un dia si se asigno horas para no tener curso en dias consecutivos
                    {
                        asigno=0;
                        d++;
                        printf("\n IF: asignacion\n");
                        continue;
                    }
                    printf("\nESTADO\n dia: %d\n horas restantes por asignar: %d\n",d,horas);
                    //mientras aun no se hayan asignado el total de horas y mientras el maximo de horas por dia no se haya alcanzado
                    while(i<6 && horas_asig<tam_max && horas!=0)
                    {
                        tam=espacio(D_aux,nuevo->H,i,d); //espacio disponible el dia d a partir de la hora i
                        printf("\ntam_max=%d h=%d i=%d dia=%d tam=%d\n",tam_max,horas_asig,i,d,tam);
                        if(tam>tam_max && control_horas[d]==0 && tam<4)
                        {
                            printf("\nSalto, se flexibiliza el dia=%d espacio=%d tamaño necesario=%d\n",d,tam,tam_max-horas_asig);
                            control_horas[d]=1;
                            break;
                        }

                        if(((tam_max>=tam || control_horas[d]==1) && tam>1) || (tam==1 && horas==1) || tam>3)
                        {
                            while(horas_asig<tam && horas_asig<tam_max && horas_asig<horas)
                            {
                                nuevo->H[i][d]=C[0][k_c];
                                D_aux[i][d]=0;
                                i++;
                                horas_asig++;
                            }//while
                            horas-=horas_asig; // se restan las hora que ya se han asignado
                            asigno=1; //se asigno horario, se permite saltar un dia

                            printf("\nhoras_asig=%d\n",horas_asig);
                            printf("\nhoras=%d\n",horas);
                            printf("\nMatriz D de profesor: %d\n",k_p);
                            imprimir_matriz(D_aux,6,5,0);
                            printf("\n Estado del Horario \n");
                            imprimir_matriz(nuevo->H,6,5,1);
                        }else if(nuevo->H[i][d]==C[0][k_c] && asigno==0)//busca si ya se han asignado tam_max horas por día
                        {
                            printf("\n ya asignado en i=%d dia=%d\n",i,d);
                            horas_asig++;
                        }else if(horas_asig==2) //sirve para no dejar horas separadas en un dia j
                        {
                            break;
                        }//if
                        i++;
                    }//while
                    if(horas_asig==3) //solo permite un dia con 3 horas
                        tam_max=2;
                    i=0;
                    horas_asig=0;
                    d++;
                }//while
                inicializar_vector(control_horas,5,0);
                d=0;
                k_c++;
                l++;
            }//while
            insertar_horario_cola(nuevo);
        }//for
    }//for
    restaurar_PC();
}
#endif /* ASIGNACION_H */
