#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void eliminar(struct trabajador lista[maximo], int *dimension){
    //VARIABLES
    int cedula,indice,tam,dd,mm,aa,motivo,salida=0,i;
    struct trabajador temporal;
    int confirmacion;
    FILE *ext;
    tam=*dimension;
    do{
        cedula=validar_ced("a buscar: (Solo numeros)"); //LEER CEDULA
        indice=busqueda_cedula(lista,tam,cedula); //BUSCAR CEDULA EN EL VECTOR DE REGISTROS
        if(indice==-1){
            printf("La CI indicada no esta asociada a ningun trabajador de la empresa.\n");
        }else{
            printf("---DATOS DEL TRABAJADOR:\n");
            escribirtrabajador(lista[indice]); //ESCRIBIR DATOS DEL TRABAJADOR
            do{
                printf("Esta seguro de eliminar este trabajador? (Si=1/No=0)\n"); //PEDIR CONFIRMACION
                scanf("%i", &confirmacion);
            }while(confirmacion!=1 && confirmacion!=0);

            if(confirmacion==1){
                borrar_registro(lista,indice,&tam, &temporal); //BORRAR REGISTRO EN EL VECTOR Y RETORNARLO EN EL REGISTRO "temporal"
                agregar_archivo("extrabajadores.txt", ext, temporal); //AGREGAR REGISTRO "temporal" AL ARCHIVO DE EXTRABAJADORES
                do{
                    printf("Ingrese el motivo de eliminacion:\n");
                    for(i=0;i<sizeof(motivos)/sizeof(motivos[0]);i++){
                        printf("%i: %s\n", i+1, motivos[i]);
                    }
                    scanf("%i", &motivo); //PREGUNTAR MOTIVO DE LA ELIMINACION
                }while(motivo<1 || motivo>5);
                //LEER FECHA DE ELIMINACION
                verificacionfecha(&dd,&mm,&aa,"despido");
                //AGREGAR A EXTRABAJADORES.TXT
                ext=fopen("extrabajadores.txt", "a");
                fprintf(ext," %s %i/%i/%i", motivos[motivo-1], dd,mm,aa); //ESCRIBIR MOTIVO Y FECHA
                fclose(ext);
                actualizar_archivo("trabajadores.in",ext,lista,tam);
                printf("Trabajador eliminado correctamente\n");
                printf("El trabajador eliminado ha sido agregado al archivo extrabajadores.txt\n");
            }
            *dimension=tam;
        }
        do{
            printf("Desea eliminar otro trabajador? (1=Si / 0=No)");
            scanf("%i", &salida);
        }while(salida!=1 && salida!=0);
    }while(salida==1);
}

//LECTURA Y VALIDACION DE CEDULA
int validar_ced(char mensaje[]){
    int lectura;
    do{
        printf("Ingrese la cedula %s\n", mensaje);
        scanf("%i", &lectura);
    } while(lectura<1);
    return lectura;
}

/*DEVOLVER EL INDICE DEL REGISTRO CON LA CEDULA CONSULTADA
    -VECTOR ES EL ARREGLO DE REGISTROS CON LOS DATOS DE TODOS LOS TRABAJADORES
    -DIM_ARREGLO ES LA DIMENCION DEL ARREGLO DE REGISTROS
    -DATO ES LA CEDULA A BUSCAR
*/
int busqueda_cedula(struct trabajador arreglo[maximo],int dim_arreglo, int dato){
    int i=0,band=0,posicion=-1;
    while(band==0 && i<dim_arreglo){
        if(arreglo[i].cedula==dato){
            band=1;
            posicion=i;
        }
        i++;
    }
    return posicion;
}

//Función para mostrar por pantalla datos de un trabajador dado un registro con datos particulares
void escribirtrabajador(struct trabajador registro){
    printf("\nNombre: %s\n", registro.nombre);
    printf("Fecha de ingreso: %s\n", registro.f_ingreso);
    printf("C%cdula de identidad: %d\n", 130, registro.cedula);
    printf("Departamento: %s\n", departamentos[registro.departamento-1]);
    printf("Cargo: %s\n", cargos[registro.cargo-1]);
    printf("Sueldo: $%f\n", registro.sueldo);
}

//Recolecta y desplazamiento de casillas en el vector de registros
void borrar_registro(struct trabajador vector[], int indice, int *dimension, struct trabajador *borrado){
    int i,dim=*dimension;
    //Guardar trabajador a eliminar
    *borrado=vector[indice];
    //borrar trabajador del vector
    if(indice!=dim-1){
        for(i=indice; i<*dimension; i++){
            vector[i]=vector[i+1];
        }
    }
   //Reducción de la dimensión por uno
   *dimension = *dimension - 1;
}

void agregar_archivo(char nombre_archivo[], FILE *archivo, struct trabajador t){
    int cant=0;
    archivo= fopen(nombre_archivo, "r"); //ABRIR ARCHIVO
    //VERIFICAR SI EXISTE EL ARCHIVO
    if(archivo==NULL){
        cant=1;
    }else{
        fclose(archivo);
    }
    //AGREGAR REGISTRO AL ARCHIVO
    archivo= fopen(nombre_archivo, "a"); //ABRIR ARCHIVO
    if(cant!=1){
        fprintf(archivo, "\n%i %s %s %s %s %f", t.cedula, t.nombre, departamentos[t.departamento-1], cargos[t.cargo-1], t.f_ingreso,t.sueldo);
    }else{
        fprintf(archivo, "%i %s %s %s %s %f", t.cedula, t.nombre, departamentos[t.departamento-1], cargos[t.cargo-1], t.f_ingreso,t.sueldo);
    }
    fclose(archivo);
}

void actualizar_archivo(char nombre_archivo[], FILE *archivo, struct trabajador arreglo[], int dimension_arreglo){
    int i=0;
    archivo= fopen(nombre_archivo, "w"); //ABRIR ARCHIVO
    //ESCRIBIR PRIMERA LINEA
    if(dimension_arreglo!=0){
        fprintf(archivo, "%i %s %s %s %s %f", arreglo[i].cedula, arreglo[i].nombre, departamentos[arreglo[i].departamento-1], cargos[arreglo[i].cargo-1], arreglo[i].f_ingreso,arreglo[i].sueldo);

    }

    for(i=1;i<dimension_arreglo;i++){
        //ESCRIBIR EL RESTO DE LINEAS
        fprintf(archivo, "\n%i %s %s %s %s %f", arreglo[i].cedula, arreglo[i].nombre, departamentos[arreglo[i].departamento-1], cargos[arreglo[i].cargo-1], arreglo[i].f_ingreso,arreglo[i].sueldo);
    }

    fclose(archivo); //CERRAR ARCHIVO
}