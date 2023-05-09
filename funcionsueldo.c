#include <stdio.h>
struct trabajador
{
    int cedula;
    char nombre[50];
    int departamento;
    int cargo;
    float sueldo;
    char f_ingreso[10];
};
int vectorindices[100];
int indicesueldo(float sueldolocal,struct trabajador vector[],int tam,int vectorindices[]);
float sueldolocal;

int indicesueldo(float sueldolocal,struct trabajador vector[],int tam,int vectorindices[]){
    int i, j=0;
    for (i=0;i<tam;i++){
        if (vector[i].sueldo=sueldolocal){
            vectorindices[j]=i;
            j++;
        }
    }
    return(j);
}
