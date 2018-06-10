/*
    Autores:
        Luis Andres Fernandez Calderon
        Jurguen Romero
        Fecha de inicio:
                16/05/2016
        Fecha de final:
                10/06/2016
*/
//Librerias a utilizar
#include <iostream>
#include "fstream"// para trabajar con archivos
#include <String>
#include <string.h>
#include <time.h>
#include<stdio.h>
#include <string>
#include <sstream>
#include<cstdlib>
#include<stdlib.h>

//Variables globales y prototipos
void MenuPrincipal();
void MenuGrafo();

using namespace std;

//Esta es la estructura que se encarga de representar las ciudades del grafo
struct Vertice{
        string nombre;
        struct Arcos*primeroCaminos;
        struct Vertice*sig;
        bool bandera=false;
        Vertice(string name){
            nombre=name;
            sig=NULL;
            primeroCaminos=NULL;
                            }
              }*primeroCiudades;
//Esta es la estructura que se encarga de representar los caminos del grafo
struct Arcos{
        int distancia;
        struct Vertice*destino;
        struct Arcos*sig;
        //Destino de X ciudad
            };
//Esta es la estructura de Arbol binario que se encarga de representar las encomiendas
struct ArbolBinario{
        int id;
        int peso;
        int direccion;//Apunta hacia el numro de registro en el archivo encomiendas
        char  descripcion[20];
        //Puntero hacia el archivo clientes
        char destino[20];
        struct ArbolBinario*izq;
        struct ArbolBinario*der;
        ArbolBinario(int identi,int weight,char descri[20],char destiny[20],int direct){
                id=identi;
                peso=weight;
                strcpy(descripcion,descri);
                strcpy(destino,destiny);
                direccion=direct;
                der=NULL;
                izq=NULL;
                                                                             }
                   }*primeroEncomiendas;
//Insertar de forma ordenada en un arbol binario
void insertarArbol_ordenado(int identi,int weight,char description[20],char destiny[20],int direct){
    struct ArbolBinario*nn=new ArbolBinario(identi,weight,description,destiny,direct);
    if (primeroEncomiendas==NULL){
        primeroEncomiendas=nn;
                                 }
    else{
        struct ArbolBinario*temp=primeroEncomiendas;
        while(true){
            if (temp->id>identi){
                if (temp->izq==NULL){
                    temp->izq=nn;
                    break;
                                     }
                else{
                    temp=temp->izq;
                    }
                               }
            else if(temp->id<identi){
                if(temp->der==NULL){
                    temp->der=nn;
                    break;
                                   }
                else{
                    temp=temp->der;
                    }
                                   }
            else{
                break;
                }
                  }
         }
                                                                                                }
//ImprimirEnPreOrden raiz izq der
void imprimir_pre(struct ArbolBinario*roble){
    if (roble==NULL){
        return;
                    }
    printf("%-10i%-10i%-22s%-22s%-10i\n",roble->id,roble->peso,roble->descripcion,roble->destino,roble->direccion);
    imprimir_pre(roble->izq);
    imprimir_pre(roble->der);
                                            }
//ImprimirEnOrden izq raiz der
void imprimir_Enorden(struct ArbolBinario*roble){
    if (roble==NULL){
        return;
                    }
    imprimir_Enorden(roble->izq);
    printf("%-10i%-10i%-22s%-22s%-10i\n",roble->id,roble->peso,roble->descripcion,roble->destino,roble->direccion);
    imprimir_Enorden(roble->der);
                                               }
//Esta es la estructura de el archivo clientes
struct ArchivoClientes{
            int cedula;
            char nombre[20];
            char direccion[20];
            int primeraEncomienda;//dependiendo puede ser long
                      }clientes;

//Esta es la estructura de el archivo encomiendas
struct ArchivoEncomiendas{
        int id;
        int peso;
        char descripcion[20];
        char destino[20];
        int  sig;
                         }encomiendas;
//inicializa los archivos al empezar el programa
fstream fp1("ArchivoClientes.txt", ios::in | ios::out|ios::binary|ios::trunc);
fstream fp2("ArchivoEncomiendas.txt", ios::in | ios::out|ios::binary|ios::trunc);

//inserta en archivo clientes
void escribirArchivoClientes(struct ArchivoClientes clientes){
	fp1.write(reinterpret_cast<char *> (&clientes), sizeof(clientes));

                                                            }
//inserta en el archivo encomiendas
void escribirArchivoEncomiendas(struct ArchivoEncomiendas encomiendas){
    fp2.write(reinterpret_cast<char *>(&encomiendas), sizeof(encomiendas));
                                                                      }
//inserta encomiendas
void insertarEncomiendas(int id, int peso, char descripcion[20],char destino[20],int sig){
    encomiendas.id=id;
    encomiendas.peso=peso;
    strcpy(encomiendas.descripcion,descripcion);
    strcpy(encomiendas.destino,destino);
    encomiendas.sig=sig;
    insertarArbol_ordenado(id,peso,descripcion,destino,sig);
    escribirArchivoEncomiendas(encomiendas);
                                                                                         }
//Esta funcion se encarga de insertar los clientes
void insertarClientes(int ced, char name[20],char ditect[20],int primera){
    	clientes.cedula =ced;
        strcpy(clientes.nombre,name);
        strcpy(clientes.direccion ,ditect);
        clientes.primeraEncomienda=primera;
        escribirArchivoClientes(clientes);
                                                                         }
//Se encarga de buscar en el grafo las ciudades
struct Vertice*buscarCiudad(string ciudad){
	struct Vertice*search=primeroCiudades;
	while(search!=NULL){
		if(search->nombre==ciudad){
			return search;
		                          }
		else{
			search=search->sig;
		    }
	                   }
	return NULL;
                                            };
//Esta funcion se encarga de insertar una ciudad en el grafo
void InsertarCiudades(string name){
        if(buscarCiudad(name)!=NULL){
            cout<<"Esta ciudad ya existe"<<endl;
                                    }
        else{
            struct Vertice*nn=new Vertice(name);
            nn->sig=primeroCiudades;
            primeroCiudades=nn;
            }
                                  }
//Esta funcion se encarga de imprimir las ciudades disponibles en el grafo
void ImprimirCiudades(){
        struct Vertice*temp=primeroCiudades;
        cout<<"Ciudades del grafo"<<endl;
        while(temp!=NULL){
            cout<<"Nombre:"<<temp->nombre<<endl;
             temp=temp->sig;
                         }
                        }
//Esta funcion se encarga de borrar las ciudades del grafo
void BorrarCiudades(string ciudad){
        struct Vertice*temCI=buscarCiudad(ciudad);
        if(temCI==NULL){
            cout<<"Datos inconsistentes"<<endl;
                       }
        else{
            struct Vertice*temp=primeroCiudades;
            struct Vertice*aux=NULL;
            while(temp!=NULL){
                    if(temp->nombre==ciudad){
                        if(aux==NULL){
                            if(temp->sig!=NULL){//Esta opcion elimina al que esta al principio pero no esta solo
                                //cout<<"Entro al inicio medio"<<endl;
                                primeroCiudades=temp->sig;
                                delete temp;
                                return;
                                               }
                            else{//elimina al nodo que esta al principio solo
                                primeroCiudades=NULL;
                                delete temp;
                                return;
                                }
                                     }
                        else if((temp->sig!=NULL)and (aux->sig!=NULL)and (aux!=NULL)){//esta opcion es para eliminar el nodo que esta en medio de dos nodos
                            aux->sig=temp->sig;
                            delete temp;
                            return;
                                                                      }
                        else{//Esta opcion es por si hay que eliminar el final
                            aux->sig=NULL;
                            delete temp;
                            return;
                            }
                                                                                                              }
                    else{
                        aux=temp;
                        temp=temp->sig;
                        }
                             }
            }
}
//Esta funcion se encarga de desmarcar las ciudades
void desmarcar(){
    struct Vertice*temp=primeroCiudades;
    while(temp!=NULL){
        temp->bandera=false;
        temp=temp->sig;
                     }
                }
bool existeRuta=false;
//Esta funcion se encarga de determinar si hay ruta
void HayRuta(string origen,string destino){
            struct Vertice*O=buscarCiudad(origen);
            if((O==NULL)or (O->bandera==true)){//Se valida primero si existe la memoria
                return;
                                              }
            if(origen==destino){
                existeRuta=true;
                return;
                               }
            O->bandera=true;
            struct Arcos*tempA=O->primeroCaminos;
            while(tempA!=NULL){
                HayRuta(tempA->destino->nombre,destino);
                tempA=tempA->sig;
                              }
                                         }
//imprime los clientes del archivo encomienda.
void ImprimirArchivoClientes(){
    fstream archiCliente("ArchivoClientes.txt",ios::in|ios::out|ios::binary);
    cout<<"----------------Clientes-------------------"<<endl;
    archiCliente.seekg(0);
    cout<<"|Cedula|  "<<" |Nombre|  "<<"           |Direccion|     "<<"       |Enlace|       "<<endl;
    while (archiCliente.eof()!=true){
        archiCliente.read(reinterpret_cast<char*>(&clientes),sizeof(clientes));
        if (archiCliente.eof()!=true){
             printf("%-11i%-22s%-22s%-10i\n",clientes.cedula,clientes.nombre,clientes.direccion,clientes.primeraEncomienda);
                                     }
                                     }
    archiCliente.close();
                                }
void ImprimirArchivoEncomiendas(){
    fstream archiEncomienda("ArchivoEncomiendas.txt",ios::in|ios::out|ios::binary);
    archiEncomienda.seekg(0);
    if (archiEncomienda.eof()!=true){
        cout<<"----------------------Encomiendas----------------------------------"<<endl;
        cout<<"|Reg|   "<<" |ID|   "<<"   |Peso|   "<<" |Descripcion|    "<<"     |Destino|      "<<"     |Sig|  "<<endl;
                                    }
    int reg=0;
    while (archiEncomienda.eof()!=true){
        archiEncomienda.read(reinterpret_cast<char*>(&encomiendas),sizeof(encomiendas));
        if (archiEncomienda.eof()!=true){
            printf("%-10i%-10i%-10i%-22s%-22s%-10i\n",reg,encomiendas.id,encomiendas.peso,encomiendas.descripcion,encomiendas.destino,encomiendas.sig);
            reg++;
                                        }
                                       }
    archiEncomienda.close();
}
//Esta funcion permite ver las encomiendas que un cliente X tenga
void ImprimirEncomiendasClienteX(int cedula){
    fstream ArchiCliente("ArchivoClientes.txt",ios::in|ios::out|ios::binary);
    ArchiCliente.seekg(0);
    while (ArchiCliente.eof()!=true){
        ArchiCliente.read(reinterpret_cast<char*>(&clientes),sizeof(clientes));         //lee encuentra el cliente el cliente
        if (clientes.cedula==cedula){
            if (clientes.primeraEncomienda==-1){
                cout<<"El usuario no cuenta con encomiendas"<<endl;
                break;
            }
            else{
                fstream ArchiEncomienda("ArchivoEncomiendas.txt",ios::in|ios::binary);            //abre el archivo en modo lectura
                ArchiEncomienda.seekg(clientes.primeraEncomienda*sizeof(encomiendas));
                while(true){
                    cout<<"----------------------Encomiendas----------------------------------"<<endl;
                    ArchiEncomienda.read(reinterpret_cast<char *>(&encomiendas), sizeof(encomiendas));
                    cout<<"Descripcion: "<<encomiendas.descripcion<<endl;
                    cout<<"Destino: "<<encomiendas.destino<<endl;
                    cout<<"ID de la encomienda: "<<encomiendas.id<<endl;
                    cout<<"Peso: "<<encomiendas.peso<<endl;
                    int cont=encomiendas.sig;
                    if (cont!=-1){
                        ArchiEncomienda.seekg(cont*sizeof(encomiendas));
                    }
                    else{
                        ArchiEncomienda.close();
                        break;
                    }
                }
                break;
            }
        }
    }
    ArchiCliente.close();
}
int dism=3000;//Distancia minima encontrada
string rutaCorta="";
//Este metodo se encarga de sacar la ruta mas corta
void RutaCorta(string origen,string destino,string ruta,int d){
            struct Vertice*O=buscarCiudad(origen);
            if((O==NULL)or (O->bandera==true)){//Se valida primero si existe la memoria
                return;
                                               }
            if(origen==destino){
                    if(dism>d){
                        dism=d;
                        rutaCorta=ruta+","+destino;
                              }
                return;
                               }
            O->bandera=true;
            struct Arcos*tempA=O->primeroCaminos;
            while(tempA!=NULL){
                RutaCorta(tempA->destino->nombre,destino,ruta+","+origen,d+tempA->distancia);
                tempA=tempA->sig;
                              }
            O->bandera=false;
                                                                      }
//Este metodo se enecarga de determinar si existe una encomienda
bool ExisteIdEncomienda(int id){
                fstream temp("ArchivoEncomiendas.txt", ios::in | ios::out |ios::binary);
                temp.seekg(0);
                while(temp.eof() != true){//eof = end of file
                    temp.read(reinterpret_cast<char *> (&encomiendas), sizeof(encomiendas));
                    if(temp.eof() != true){
                            if(encomiendas.id==id){
                                    temp.close();
                                    return true;
                                                  }
                                          }
                                         }
                    temp.close();
                    return false;
                               }
//Funcion q se encarga de retornar el peso
int RetornaPeso(int id){
                fstream temp("ArchivoEncomiendas.txt", ios::in | ios::out |ios::binary);
                temp.seekg(0);
                while(temp.eof() != true){//eof = end of file
                    temp.read(reinterpret_cast<char *> (&encomiendas), sizeof(encomiendas));
                    if(temp.eof() != true){
                            if(encomiendas.id==id){
                                    temp.close();
                                    return encomiendas.peso;
                                                  }
                                          }
                                         }
                    temp.close();
                    return 0;
                        }
//Retornar el destino de la encomienda
string RetornarDestinoEncomienda(int id){
                fstream temp("ArchivoEncomiendas.txt", ios::in | ios::out |ios::binary);
                temp.seekg(0);
                while(temp.eof() != true){//eof = end of file
                    temp.read(reinterpret_cast<char *> (&encomiendas), sizeof(encomiendas));
                    if(temp.eof() != true){
                            if(encomiendas.id==id){
                                string destiny=encomiendas.destino;
                                temp.close();
                                return destiny;
                                                  }
                                          }
                                         }
                    temp.close();
                    return "";
                                        }
//Retorna los datos de la encomienda
string RetornarDatosEncomienda(int id){
                fstream temp("ArchivoEncomiendas.txt", ios::in | ios::out |ios::binary);
                temp.seekg(0);
                while(temp.eof() != true){//eof = end of file
                    temp.read(reinterpret_cast<char *> (&encomiendas), sizeof(encomiendas));
                    if(temp.eof() != true){
                            if(encomiendas.id==id){
                                string id1="";
                                string peso="";
                                string sig="";
                                id1=static_cast<std::ostringstream*>(&(std::ostringstream() << id))->str();
                                peso=static_cast<std::ostringstream*>(&(std::ostringstream() << encomiendas.peso))->str();
                                sig=static_cast<std::ostringstream*>(&(std::ostringstream() << encomiendas.sig))->str();
                                string info="   "+id1+"   ,   "+peso+"   ,   "+encomiendas.descripcion+"   ,   "+encomiendas.destino+"   ,   "+sig+"   .   ";
                                temp.close();
                                return info;
                                                  }
                                          }
                                         }
                    temp.close();
                    return "";
                                        }
//Determina la ruta de un paquete
void DeterminaRutaPaquete(string origen,int paquete[5][5]){
                    int temp=0;
                    int temp1=0;
                    string destino;
                    int peso=0;
                    int pesot=0;
                    bool GAM=false;
                    bool GAMD=false;
                    //Siglas GAM (La Gran Area Metropolitana)
                    int tariGAMDGAM=760;//Tarifa por el primer kilogramo de la GAM hacia la GAM
                    int tariGAMMasKgDGAM=330;//Tarifa mas de un kg de la GAM a la GAM
                    int tariGAMDResto=1150;//Tarifa por el primer kilogramo de la GAM hacia el resto del pais
                    int tariGAMMasKgDResto=520;//Tarifa mas de un kg de la GAM al resto del pais

                    int tariRestoGAM=1140;//Tarifa por el primer kilogramo de el resto del pais hacia la GAM
                    int tariRestoMasKgDGAM=520;//Tarifa mas de un kg de el resto del pais hacia la GAM
                    int tariRestoResto=1750;//Tarifa por el primer kilogramo de el resto del pais hacia resto del pais
                    int tariRestoMasKgDResto=650;//Tarifa mas de un kg de el resto del pais hacia al resto del pais
                    int countra=0;
                    int maxlargeDisRuta=3000000;
                    int maxlargeDisRutatemp=0;
                    string rutaCortaLarge="";
                    string datosIds="";
                    string datosIdstemp="";
                    string rutaCortaLargetemp="";
                    string origentemp="";
                    for(int x=0;x<5;x++){
                            if(maxlargeDisRuta>maxlargeDisRutatemp and maxlargeDisRutatemp!=0){
                                rutaCortaLarge=rutaCortaLargetemp;
                                maxlargeDisRuta=maxlargeDisRutatemp;
                                peso=pesot;
                                datosIds=datosIdstemp;
                                                                                             }
                            datosIdstemp="";
                            maxlargeDisRutatemp=0;
                            rutaCortaLargetemp="";
                            origentemp=origen;
                            pesot=0;
                        for(int y=0;y<5;y++){
                                    if(paquete[x][y]!=0){

                                                    if((origentemp=="San_Jose" or origentemp=="Alajuela" or origentemp=="Heredia")and countra<1){
                                                        GAM=true;
                                                        countra++;
                                                                                                                                    }
                                                    if(destino=="San_Jose" or destino=="Alajuela" or destino=="Heredia"){
                                                        GAMD=true;
                                                                                                                        }
                                                    destino=RetornarDestinoEncomienda(paquete[x][y]);
                                                    RutaCorta(origentemp,destino,"",0);
                                                    origentemp=destino;
                                                    datosIdstemp+=RetornarDatosEncomienda(paquete[x][y])+"\n";
                                                    maxlargeDisRutatemp+=dism;
                                                    rutaCortaLargetemp+=rutaCorta;
                                                    pesot+=RetornaPeso(paquete[x][y]);
                                                    dism=3000;
                                                    rutaCorta="";
                                                        }
                                            }
                                       }

                    cout<<"La ruta mas corta del paquete es:"<<rutaCortaLarge<<"Con una distancia de: "<<maxlargeDisRuta<<" KM"<<endl;
                    int total=0;
                    if(GAM ==true and GAMD==true ){
                        total+=tariGAMDGAM;
                        if(peso>1){
                            int counta=2;
                            while(counta<=peso){
                                total+=tariGAMMasKgDGAM;
                                 counta++;
                                               }
                                  }
                                                  }
                    if(GAM ==true and GAMD!=true){
                        total+=tariGAMDResto;
                        if(peso>1){
                            int counta=2;
                            while(counta<=peso){
                                total+=tariGAMMasKgDResto;
                                counta++;
                                               }
                                  }
                                                 }
                    if(GAM==false and GAMD==true){
                        total+=tariRestoGAM;
                        if(peso>1){
                            int counta=2;
                            while(counta<=peso){
                                total+=tariRestoMasKgDGAM;
                                counta++;
                                               }
                                  }
                                                 }

                    if(GAM==false and GAMD==false){
                        total+=tariRestoResto;
                        if(peso>1){
                            int counta=2;
                            while(counta<=peso){
                                total+=tariRestoMasKgDResto;
                                counta++;
                                               }
                                  }
                                                  }
                    cout<<"  |ID|  "<<"  |Peso|  "<<"  |Descripcion|  "<<"  |Destino|  "<<"  |Sig|  "<<endl;
                    cout<<datosIds<<endl;
                    cout<<"Peso:"<<peso<<"   Tasa Colones:"<<total<<endl;
                    datosIds="";
                                                       }
//Esta funcion se encarga de determinar si el grafo es conexo
bool esConexo=false;
void GrafoEsConexo(){
        struct Vertice*tempV=primeroCiudades;
        struct Vertice*tempV1=primeroCiudades;
        while(tempV!=NULL){
            while(tempV1!=NULL){
                    if(tempV->nombre!=tempV1->nombre){
                            HayRuta(tempV->nombre,tempV1->nombre);
                            if(existeRuta==true){
                                esConexo=true;
                                existeRuta=false;
                                desmarcar();
                                tempV1=tempV1->sig;
                                                }
                            else{
                                cout<<"O"<<tempV->nombre<<",D"<<tempV1->nombre<<endl;
                                esConexo=false;
                                return;
                                }
                                                     }
                    else{
                        tempV1=tempV1->sig;
                        }
                               }
                tempV=tempV->sig;
                          }
                    }
//Con esta funcion se ve las ciudades sus arcos o caminos                                            }
void imprimirArcos(){
    struct Vertice*tempV=primeroCiudades;
    system("cls");
    while(tempV!=NULL){
        cout<<"----------------------------------------"<<endl;
        cout<<"Origen: "<<tempV->nombre<<endl;
        struct Arcos*tempA = tempV->primeroCaminos;
        int counta=0;
        while(tempA!=NULL){
            cout<<"destino("<<counta<<"):"<<tempA->destino->nombre<<",Distancia:"<<tempA->distancia<<" Km"<<endl;
            counta++;
            tempA=tempA->sig;
        }
        tempV=tempV->sig;
    }
}
//Esta funcion permite insertar los caminos a sus provincias
void insertarRutas(string c1,string c2,int dist){

    struct Vertice*PuebloOrigen=buscarCiudad(c1);
    struct Vertice*PuebloDestino=buscarCiudad(c2);
    if (PuebloDestino==NULL || PuebloOrigen==NULL){
        cout<<"Datos de la ciudad es inconsistente"<<endl;
    }
    else{
        struct Arcos*no = new Arcos();
        no->destino=PuebloDestino;
        no->distancia=dist;
        no->sig=PuebloOrigen->primeroCaminos;
        PuebloOrigen->primeroCaminos=no;

        //Se encarga de que sea no direccinado lo que hace que se devuelva del destino al origen
        struct Arcos*nd = new Arcos();
        nd->destino=PuebloOrigen;
        nd->distancia=dist;
        nd->sig=PuebloDestino->primeroCaminos;
        PuebloDestino->primeroCaminos=nd;
    }
}
//Esta funcion elimina una ruta entre dos ciudades
void BorrarCamino(string cO, string cD){
    struct Vertice*CiudadO=buscarCiudad(cO);
    struct Vertice*CiudadD=buscarCiudad(cD);
    if (CiudadD==NULL || CiudadO==NULL){
        cout<<"Error en los datos"<<endl;
    }
    else{
        struct Arcos*auxA=CiudadO->primeroCaminos;
        if (auxA==NULL){
            cout<<"Esta ciudad no tiene caminos"<<endl;
        }
        else{
            struct Arcos*tempA=CiudadO->primeroCaminos;
            if (tempA->destino==CiudadD){
                CiudadO->primeroCaminos=tempA->sig;
                delete tempA;
            }
            else{
                auxA=tempA;
                tempA=tempA->sig;
                while(tempA!=NULL){
                    if (tempA->destino==CiudadD){
                        auxA->sig=tempA->sig;
                        tempA->destino=NULL;
                        delete tempA;
                    }
                }
            }
        }
    }
}
//esta funcion modifica la distancia de las ciudades
void ModificarDistancia(string cO,string cD,int nD){
    struct Vertice*CiudOrigen=buscarCiudad(cO);
    struct Vertice*CiudDestino=buscarCiudad(cD);
    if (CiudDestino==NULL || CiudOrigen==NULL){
        cout<<"Datos erroneos"<<endl;
    }
    else{
        struct Arcos*tempA=CiudOrigen->primeroCaminos;
        while(tempA!=NULL){
            if(tempA->destino==CiudDestino){
                tempA->distancia=nD;
                cout<<"Distancia modificada"<<endl;
            }
            tempA=tempA->sig;
        }
    }
}

//esta funcion modifica el nombre de la ciudad
void ModificarCiudad(string cO,string nuevoN){
    struct Vertice*CiudOrigen=buscarCiudad(cO);
    if (CiudOrigen==NULL){
        cout<<"La ciudad no existe"<<endl;
    }
    else{
        if(buscarCiudad(nuevoN)!=NULL){
            cout<<"Imposible realizar, Esta ciudad ya existe"<<endl;
        }
        else{
            CiudOrigen->nombre=nuevoN;
            cout<<"Nombre editado"<<endl;
        }
    }
}

//Esta funcion se encarga de insertar los datos en el sistema
void CargarDatos(){
    //Estos son los datos temporales de las ciudades del grafo
    InsertarCiudades("Alajuela");
    InsertarCiudades("Heredia");
    InsertarCiudades("Limon");
    InsertarCiudades("Puntarenas");
    InsertarCiudades("Guanacaste");
    InsertarCiudades("San_Jose");
    InsertarCiudades("Cartago");
    //Arcos de las ciudades
    insertarRutas("Alajuela","Heredia",15);
    insertarRutas("Alajuela","Guanacaste",15);
    insertarRutas("Alajuela","San_Jose",15);
    insertarRutas("Limon","Puntarenas",150);
    insertarRutas("Limon","Cartago",150);
    insertarRutas("Limon","San_Jose",150);
    insertarRutas("Limon","Guanacaste",150);
    insertarRutas("Cartago","Heredia",150);
    insertarRutas("Cartago","San_Jose",150);
    insertarRutas("Cartago","Puntarenas",150);
    insertarRutas("Heredia","San_Jose",15);
    insertarRutas("Guanacaste","San_Jose",15);
    insertarRutas("Guanacaste","Puntarenas",15);
    insertarRutas("San_Jose","Puntarenas",15);
    //Insertar en Archivo Clientes
    	//Insertar en Archivo Clientes
    	fp1.seekp(0);
    	insertarClientes(207450217,"Andres","Alajuela",0);
        insertarClientes(00000000,"Jurguen","Heredia",1);
    	insertarClientes(2074502176,"Carlos","San_Carlos",2);
        insertarClientes(207450215,"Esteban","San_Jose",3);
        insertarClientes(207450214,"Roberto","Limon",4);
        fp1.close();
        fp2.seekp(0);
        insertarEncomiendas(10,10,"Ropa","San_Jose",5);
        insertarEncomiendas(12,1,"Tenis","Alajuela",4);
        insertarEncomiendas(1,2,"Libros","Heredia",6);
        insertarEncomiendas(56,10,"Vajilla","Cartago",-1);
        insertarEncomiendas(3,5,"Ropa de cama","Limon",-1);
        insertarEncomiendas(4,1,"Libro","Guanacaste",-1);
        insertarEncomiendas(8,1,"Perfumes","Puntarenas",-1);
        fp2.close();
                  }
//Menu para direccionar a la modificacion de alguna ciudad o distancia de una ciudad a otra
void MenuModificar(){
    string op;
    cout<<"1.Modificar distancia de ciudad origen a ciudad destino"<<endl;
    cout<<"2.Modificar nombre de la ciudad Origen"<<endl;
    cout<<"< Atras"<<endl;
    cin>>op;
    if (op=="1"){
        system("cls");
        string ciudadO;
        cout<<"Digite el nombre de la ciudad de origen"<<endl;
        cin>>ciudadO;

        string ciudadD;
        cout<<"Digite el nombre de la ciudad de destino"<<endl;
        cin>>ciudadD;

        int nD;
        cout<<"Nueva distancia"<<endl;
        cin>>nD;
        ModificarDistancia(ciudadO,ciudadD,nD);
        MenuGrafo();
    }
    else if(op=="2"){
        system("cls");
        string ciudadO;
        cout<<"Digite el nombre de la ciudad que desea modificar"<<endl;
        cin>>ciudadO;
        string ciuNueva;
        cout<<"Digite el nuevo nombre"<<endl;
        cin>>ciuNueva;
        ModificarCiudad(ciudadO,ciuNueva);
        MenuGrafo();
    }
    else if(op=="<"){
        system("cls");
        MenuGrafo();
    }
    else{
        cout<<"Digite lo que se le solicita"<<endl;
        MenuModificar();
    }
}
//El menu donde se realiza todas las llamadas que tengan que ver con el grafo
void MenuGrafo(){
    string option;
    cout<<"Bienvenido al menu de grafo ,que desea realizar:"<<endl;
    cout<<"1.Insertar Ciudad"<<endl;
    cout<<"2.Borrar Ciudad"<<endl;
    cout<<"3.Insertar camino"<<endl;
    cout<<"4.Borrar camino "<<endl;
    cout<<"5.Salir"<<endl;
    cout<<"6.Imprimir Ciudades"<<endl;
    cout<<"7.Imprimir Ciudad y caminos"<<endl;
    cout<<"8.Modificar camino"<<endl;
    cout<<"9.Determina si el grafo es conexo"<<endl;
    cout<<"<.Atras"<<endl;
    cin>>option;
    if(option=="1"){
        system("cls");
        string city;
        cout<<"Digite la ciudad que desea insertar"<<endl;
        cin>>city;
        InsertarCiudades(city);
        MenuGrafo();
                   }
    else if(option=="2"){
            system("cls");
            string city;
            cout<<"Digite la ciudad que desea borrar"<<endl;
            cin>>city;
            BorrarCiudades(city);
            MenuGrafo();
                        }
    else if(option=="3"){
            system("cls");
            string ciud1;
            cout<<"Digite la ciudad de origen"<<endl;
            cin >>ciud1;
            string ciud2;
            cout<<"Digite la ciudad de destino"<<endl;
            cin >>ciud2;
            int distancia=0;
            cout<<"Distancia entre los pueblos"<<endl;
            cin>> distancia;
            insertarRutas(ciud1,ciud2, distancia);
            MenuGrafo();
                        }
    else if(option=="4"){
            system("cls");
            string cO;
            cout<<"Digite la ciudad de origen de la ruta a borrar"<<endl;
            cin>>cO;
            string cD;
            cout<<"Digite la ciudad de destino de la ruta a borrar"<<endl;
            cin>>cD;
            BorrarCamino(cO,cD);
            MenuGrafo();
                        }
    else if(option=="5"){

                        }
    else if(option=="6"){
            system("cls");
            ImprimirCiudades();
            MenuGrafo();
                        }
    else if(option=="7"){
            system("cls");
            imprimirArcos();
            MenuGrafo();
                        }
    else if(option=="8"){
            system("cls");
            MenuModificar();
            MenuGrafo();
                        }
    else if(option=="9"){
            system("cls");
            GrafoEsConexo();
            if(esConexo==true){
                cout<<"El grafo es conexo"<<endl;
                             }
            else{
                cout<<"El grafo no es conexo"<<endl;
                }
            MenuGrafo();
                        }
    else if(option=="<"){
        system("cls");
        MenuPrincipal();
                        }
    else{
        system("cls");
        cout<<"ERROR(Digite los datos que se le solicitan)"<<endl;
        MenuGrafo();
        }
             }
void MenuArchivos(){
    string option;
    cout<<"Bienvenido al menu de Archivos,que desea realizar:"<<endl;
    cout<<"1.Imprimir las encomiendas de un cliente X"<<endl;
    cout<<"2.Imprimir la ruta corta y su respectiva factura con las encomiendas entregadas y el precio de la entrega"<<endl;
    cout<<"3.Imprimir  archivo clientes en el formato indicado"<<endl;
    cout<<"4.Imprimir  archivo encomiendas en el formato indicado "<<endl;
    cout<<"5.Salir"<<endl;
    cout<<"6.Imprimir el arbol binario con toda la informacion en Orden y preOrden"<<endl;
    cin>>option;
    if(option=="1"){
        system("cls");
        cout<<"Digite el id del cliente que desea ver"<<endl;
        int cli;
        cin>>cli;
        ImprimirEncomiendasClienteX(cli);
        MenuArchivos();
                   }
    else if(option=="2"){
            system("cls");
            int maxin=0;
            int paquete[5];
            int add;
            int deseo;
            cout<<"Digite cuantas encomiendas va ha insertar "<<endl;
            cin>>deseo;
            if(deseo<=5){
                while(maxin<5){
                    if(maxin<deseo){
                        cout<<"Digite los id de las encomiendas que desea agregar al paquete"<<endl;
                        cin>>add;
                        if(ExisteIdEncomienda(add)==true){
                                paquete[maxin]=add;
                                maxin++;
                                              }
                        else{
                            cout<<"No existe ese id en encomiendas,digite uno que si exista"<<endl;
                            maxin=maxin;
                            }

                                   }
                    else{
                        paquete[maxin]=0;
                        maxin++;
                        }
                                  }
                int paqueteCompleto[5][5];
                for(int x=0;x<5;x++){
                        for(int y=0;y<5;y++){
                                if(y==0){
                                    paqueteCompleto[x][y]=paquete[x];
                                        }
                                else{
                                    if(x!=y){
                                        paqueteCompleto[x][y]=paquete[y];
                                            }
                                    else{
                                        paqueteCompleto[x][y]=paquete[y-x];
                                        }
                                    }
                                             }
                                    }
                string original;
                cout<<"Digite de donde quiere que inicie el recorrido del paque hacia su destino"<<endl;
                cin>>original;
                DeterminaRutaPaquete(original,paqueteCompleto);
                MenuArchivos();
                        }
            else{
                cout<<"Los paquetes solo pueden tener un maximo de cinco encomiendas"<<endl;
                MenuArchivos();
                }

            cout<<"Congratulation for your first pass"<<endl;
            MenuArchivos();
                        }
    else if(option=="3"){
        system("cls");
        ImprimirArchivoClientes();
        MenuArchivos();
                        }
    else if(option=="4"){
        system("cls");
        ImprimirArchivoEncomiendas();
        MenuArchivos();
                        }
    else if(option=="5"){
            MenuPrincipal();
                        }

    else if(option=="6"){
            cout<<"...........................Impresion en preorden............................."<<endl;
            cout<<"|ID|   "<<"   |Peso|   "<<" |Descripcion|    "<<"     |Destino|      "<<"     |Sig|  "<<endl;
            imprimir_pre(primeroEncomiendas);
            cout<<"...........................Impresion en  orden................................"<<endl;
            cout<<"|ID|   "<<"   |Peso|   "<<" |Descripcion|    "<<"     |Destino|      "<<"     |Sig|  "<<endl;
            imprimir_Enorden(primeroEncomiendas);
            MenuArchivos();
                        }
    else{
        system("cls");
        cout<<"ERROR(Digite los datos que se le solicitan)"<<endl;
        MenuArchivos();
        }
                }

void MenuPrincipal(){
    string option;
    cout<<"Bienvenido al menu de principal de Sistema de Correos Costa Rica ,que desea realizar:"<<endl;
    cout<<"1.Menu grafo"<<endl;
    cout<<"2.Archivos"<<endl;
    cout<<"3.Salir"<<endl;
    cin>>option;
    if(option=="1"){
        system("cls");
        MenuGrafo();
                   }
    else if(option=="2"){
            system("cls");
            MenuArchivos();
                        }
    else if(option=="3"){
        cout<<endl<<"Adios"<<endl;

                        }
    else{
        system("cls");
        cout<<"ERROR(Digite los datos que se le solicitan)"<<endl;
        MenuPrincipal();
        }
                }
int main(){
    system("color 0b");
    CargarDatos();
    MenuPrincipal();
    return 0;
          }
