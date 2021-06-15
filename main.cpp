#include <iostream>
#include<sstream>
#include<cstdlib>
#include "ClassA.h"
#include "ClassB.h"
#include<fstream>
#define N 100

using namespace std;

//FUNCIONES DEL MENU
void agregar();
void Modifica();
void Elimina();
void Busca();
void MuestraTodo();
//FUNCIONES SECUNDARIAS
void insertaFinal();
void insertaInicio();
bool valida(int key);


int main()
{
    int opc;
    do
    {
        system("cls");
        cout<<"\n\tMenu Principal DELIMITADORES"<<endl;
        cout<<"\n\t1.- Agregar: "<<endl;
        cout<<"\t2.- Eliminar: "<<endl;
        cout<<"\t3.- Mostrar: "<<endl;
        cout<<"\t4.- Modificar: "<<endl;
        cout<<"\t5.- Mostrar Todos los Registros: "<<endl;
        cout<<"\t6.- Salir: "<<endl<<endl;
        cout<<"\tTeclee una opcion desde el teclado:\t";
        cin>>opc;

        switch(opc)
        {
        case 1:
            agregar();
            break;
        case 2:
            Elimina();
            break;
        case 3:
            Busca();
            break;
        case 4:
            Modifica();
            break;
        case 5:
            MuestraTodo();
            break;
        case 6:
            system("cls");
            cout<<"\n\n\t\tFin del programa"<<endl;
            break;

        default:
            cout<<"\tSeleccione una opcion valida"<<endl;
            system("Pause");
            break;
        }
    }
    while(opc != 6);

    return 0;
}
void agregar()
{
    system("cls");
    int rpt;
    cout<<"\n\tQUE METODO DESEAS UTILIZAR?: "<<endl;
    cout<<"\t1. Insertar Al Final: "<<endl;
    cout<<"\t2. Insertar Al Inicio: "<<endl;
    cout<<"\t3. Regresar: "<<endl;
    cout<<"\tSeleccione una opcion: \t";
    cin>>rpt;
    switch(rpt)
    {
    case 1:
            insertaFinal();
            break;
    case 2:
            insertaInicio();
            break;
    case 3:
        break;
    default:
        cout<<"\tSeleccione una opcion valida"<<endl;
        system("pause");
    }
}
void insertaFinal()
{
    int ent;
    string cad;
    int campo;

    cout<<"\tINSERTAR AL FINAL"<<endl;
    cout<<"\n\tIngrese la llave primaria: ";
    cin>>ent;
    if (valida(ent)==false){
        cout<<"\tLA LLAVE PRIMARIA YA EXISTE"<<endl;
        system("pause");
        return;
    }

    cout<<"\n\tIngrese la cadena: ";
    cin.ignore();
    getline(cin, cad);

    ClassA obj(ent, cad);

    string cadenaB[10];
    bool bolB[10];

    ofstream fout;
    fout.open("Archivo.bin", ios::binary | ios::app);

    fout.write((char*)&ent, sizeof(int));
    campo = cad.length();
    fout.write((char*)&campo, sizeof(int));
    fout.write(cad.c_str(),  sizeof(char) * campo);

     for(int i = 0; i<10; i++){
            cadenaB[i] = obj.getClassB(i).getStringB();
            bolB[i] = obj.getClassB(i).getBoolB();
            campo = cadenaB[i].length();
            fout.write((char*)&campo, sizeof(int));
            fout.write(cadenaB[i].c_str(),  sizeof(char) * campo);
            fout.write((char*)&bolB[i], sizeof(bool));
        }

    fout.close();

    cout<<"REGISTRO REALIZADO"<<endl;

}
void insertaInicio()
{
    int ent;
    string cad, respaldo;
    int campo;

    cout<<"\t\nINSERTAR AL INICIO"<<endl<<endl;
    cout<<"\tIngrese la llave primaria: ";
    cin>>ent;
    if(valida(ent)==false)
    {
        cout<<"ENTERO YA EXISTENTE"<<endl;
        system("pause");
        return;
    }
    cout<<"\n\tIngrese la cadena: ";
    cin.ignore();
    getline(cin, cad);

    ClassA obj(ent,cad);

    string cadenaB[10];
    bool bolB[10];

    ofstream aux;
    aux.open("auxiliar.bin", ios::binary);

    aux.write((char*)&ent, sizeof(int));
    campo = cad.length();
    aux.write((char*)&campo, sizeof(int));
    aux.write(cad.c_str(),  sizeof(char) * campo);

     for(int i = 0; i<10; i++){
            cadenaB[i] = obj.getClassB(i).getStringB();
            bolB[i] = obj.getClassB(i).getBoolB();
            campo = cadenaB[i].length();
            aux.write((char*)&campo, sizeof(int));
            aux.write(cadenaB[i].c_str(),  sizeof(char) * campo);
            aux.write((char*)&bolB[i], sizeof(bool));
        }

    ifstream fin;
    fin.open("Archivo.bin", ios::binary);

    while(!fin.eof())
    {
        getline(fin, respaldo);
        aux<<respaldo;

    }

    aux.close();
    fin.close();

    remove("Archivo.bin");
    rename("auxiliar.bin","Archivo.bin");
    cout<<"EXITO";
    system("pause");
}
void Modifica()
{

        ofstream aux;
        aux.open("auxiliar.bin", ios::binary | ios::app);

        int llave, campo, ent;
        string cad = "", cadB[10];
        bool bolB[10];

        cout<<"\n\MODIFICAR UN REGISTRO"<<endl;
        cout<<"\n\tIngrese la llave primearia: ";
        cin>>llave;

        ifstream fin;
        fin.open("Archivo.bin", ios::binary | ios::app);

        fin.read((char*)&ent, sizeof(int));

             while(!fin.eof()){
                fin.read((char*)&campo, sizeof(int));
                char cadaux[campo+1];
                fin.read(cadaux, sizeof(char) * campo);
                cadaux[campo] = '\0';

                cad = cadaux;

            for(int i = 0; i < 10; i++){
                fin.read((char*)&campo, sizeof(int));
                char aux1[campo+1];
                fin.read(aux1, sizeof(char) * campo);
                aux1[campo] = '\0';
                cadB[i] = aux1;

                fin.read((char*)&bolB[i], sizeof(bool));
            }
            ClassA obj(ent, cad);

                if(llave != ent)
                {
                    aux.write((char*)&ent, sizeof(int));
                    campo = cad.length();
                    aux.write((char*)&campo, sizeof(int));
                    aux.write(cad.c_str(),  sizeof(char) * campo);

                     for(int i = 0; i<10; i++){
                            cadB[i] = obj.getClassB(i).getStringB();
                            bolB[i] = obj.getClassB(i).getBoolB();
                            campo = cadB[i].length();
                            aux.write((char*)&campo, sizeof(int));
                            aux.write(cadB[i].c_str(),  sizeof(char) * campo);
                            aux.write((char*)&bolB[i], sizeof(bool));
                        }
                }
                else
                    {
                        int rpt;
                        cout<<"\t1) Modificar entero: "<<endl;
                        cout<<"\t2) Modificar cadena: "<<endl;
                        cout<<"\t3) Regresar: "<<endl;
                        cin>>rpt;
                        switch(rpt)
                        {
                        case 1:
                            {
                                int nuevoentero;
                                cout<<"Ingrese el nuevo entero: ";
                                cin>>nuevoentero;
                                if(valida(nuevoentero) == false)
                                    return;
                                aux.write((char*)&nuevoentero, sizeof(int));
                                campo = cad.length();
                                aux.write((char*)&campo, sizeof(int));
                                aux.write(cad.c_str(),  sizeof(char) * campo);

                                 for(int i = 0; i<10; i++){
                                        cadB[i] = obj.getClassB(i).getStringB();
                                        bolB[i] = obj.getClassB(i).getBoolB();
                                        campo = cadB[i].length();
                                        aux.write((char*)&campo, sizeof(int));
                                        aux.write(cadB[i].c_str(),  sizeof(char) * campo);
                                        aux.write((char*)&bolB[i], sizeof(bool));
                                }
                            break;
                            }
                        case 2:
                            {
                                string nuevacadena;
                                cout<<"Ingrese la nueva cadena: ";
                                cin.ignore();
                                getline(cin, nuevacadena);
                                aux.write((char*)&ent, sizeof(int));
                                campo = nuevacadena.length();
                                aux.write((char*)&campo, sizeof(int));
                                aux.write(nuevacadena.c_str(),  sizeof(char) * campo);

                                 for(int i = 0; i<10; i++){
                                        cadB[i] = obj.getClassB(i).getStringB();
                                        bolB[i] = obj.getClassB(i).getBoolB();
                                        campo = cadB[i].length();
                                        aux.write((char*)&campo, sizeof(int));
                                        aux.write(cadB[i].c_str(),  sizeof(char) * campo);
                                        aux.write((char*)&bolB[i], sizeof(bool));
                                        }
                                        break;
                            }

                        case 3: break;
                        default:
                            cout<<"Opcion Invalida"<<endl;
                            break;
                        }

                    }

            fin.read((char*)&ent, sizeof(int));
        }

        aux.close();
        fin.close();
        remove("Archivo.bin");
        rename("auxiliar.bin", "Archivo.bin");

}
void Elimina()
{

    ofstream aux;
    aux.open("auxiliar.bin", ios::binary | ios::app);

        int llave, campo, ent;
        string cad = "", cadB[10];
        bool bolB[10];

        cout<<"\n\tELIMINAR UN REGISTRO"<<endl;
        cout<<"\n\tIngrese la llave primearia: ";
        cin>>llave;

        ifstream fin;
        fin.open("Archivo.bin", ios::binary | ios::app);

        fin.read((char*)&ent, sizeof(int));

             while(!fin.eof()){
                fin.read((char*)&campo, sizeof(int));
                char cadaux[campo+1];
                fin.read(cadaux, sizeof(char) * campo);
                cadaux[campo] = '\0';

                cad = cadaux;

            for(int i = 0; i < 10; i++){
                fin.read((char*)&campo, sizeof(int));
                char aux1[campo+1];
                fin.read(aux1, sizeof(char) * campo);
                aux1[campo] = '\0';
                cadB[i] = aux1;

                fin.read((char*)&bolB[i], sizeof(bool));
            }
            ClassA obj(ent, cad);

                if(llave != ent)
                {
                    aux.write((char*)&ent, sizeof(int));
                    campo = cad.length();
                    aux.write((char*)&campo, sizeof(int));
                    aux.write(cad.c_str(),  sizeof(char) * campo);

                     for(int i = 0; i<10; i++){
                            cadB[i] = obj.getClassB(i).getStringB();
                            bolB[i] = obj.getClassB(i).getBoolB();
                            campo = cadB[i].length();
                            aux.write((char*)&campo, sizeof(int));
                            aux.write(cadB[i].c_str(),  sizeof(char) * campo);
                            aux.write((char*)&bolB[i], sizeof(bool));
                        }
                }

            fin.read((char*)&ent, sizeof(int));
        }

        aux.close();
        fin.close();
        remove("Archivo.bin");
        rename("auxiliar.bin", "Archivo.bin");
}
bool valida(int llave)
{
        int campo, entero;
        string cadena = "", cadB[10];
        bool bolB[10];

        ifstream fin;
        fin.open("Archivo.bin", ios::binary | ios::app);

        fin.read((char*)&entero, sizeof(int));

             while(!fin.eof()){
                fin.read((char*)&campo, sizeof(int));
                char aux[campo+1];
                fin.read(aux, sizeof(char) * campo);
                aux[campo] = '\0';

                cadena = aux;

            for(int i = 0; i < 10; i++){
                fin.read((char*)&campo, sizeof(int));
                char aux1[campo+1];
                fin.read(aux1, sizeof(char) * campo);
                aux1[campo] = '\0';
                cadB[i] = aux1;

                fin.read((char*)&bolB[i], sizeof(bool));
            }
            ClassA obj(entero, cadena);

                if(llave == entero)
                    return false;

            fin.read((char*)&entero, sizeof(int));
        }
        return true;
}
void MuestraTodo()
{
    int campo, entero;
    string cadena = "", cadB[10];
    bool bolB[10];

    ifstream fin;
    fin.open("Archivo.bin", ios::binary | ios::app);

    fin.read((char*)&entero, sizeof(int));

    while(!fin.eof()){
        fin.read((char*)&campo, sizeof(int));
        char aux[campo+1];
        fin.read(aux, sizeof(char) * campo);
        aux[campo] = '\0';

        cadena = aux;

        for(int i = 0; i < 10; i++){
            fin.read((char*)&campo, sizeof(int));
            char aux1[campo+1];
            fin.read(aux1, sizeof(char) * campo);
            aux1[campo] = '\0';
            cadB[i] = aux1;

            fin.read((char*)&bolB[i], sizeof(bool));
        }
        ClassA obj(entero, cadena);
        cout<<obj.tostring();

fin.read((char*)&entero, sizeof(int));
    }

        system("pause");

}
void Busca()
{
    int llave;
    cout<<"METODO DE BUSQUEDA"<<endl;
    cout<<"Ingresa la llave primaria: ";
    cin>>llave;

    int campo, entero;
    string cadena = "", cadB[10];
    bool bolB[10];

    ifstream fin;
    fin.open("Archivo.bin", ios::binary);

    fin.read((char*)&entero, sizeof(int));

         while(!fin.eof()){
            fin.read((char*)&campo, sizeof(int));
            char aux[campo+1];
            fin.read(aux, sizeof(char) * campo);
            aux[campo] = '\0';

            cadena = aux;

        for(int i = 0; i < 10; i++){
            fin.read((char*)&campo, sizeof(int));
            char aux1[campo+1];
            fin.read(aux1, sizeof(char) * campo);
            aux1[campo] = '\0';
            cadB[i] = aux1;

            fin.read((char*)&bolB[i], sizeof(bool));
        }
        ClassA obj(entero, cadena);

            if(llave == entero){
                cout<<obj.tostring();
                system("pause");
                break;
            }

        fin.read((char*)&entero, sizeof(int));
    }
}
