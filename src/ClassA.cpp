#include <iostream>
#include<sstream>
#include "ClassA.h"
#include<fstream>
#include"ClassB.h"

using namespace std;

ClassA::ClassA(){}

ClassA::ClassA(int entero, string cadena)
{
    this->entero = entero;
    this->cadena = cadena;

    string cad;
    bool bol;

    for(int i = 0; i<10; i++){
        cad = "Cadena";
        if (i%2 == 0)
            bol = 1;
        else
            bol = 0;
        arreglo[i].setStringB(cad);
        arreglo[i].setBoolB(bol);
    }
}
void ClassA::setCad(string cad)
{
    cadena = cad;
}
void ClassA::setEntero(int key)
{
    entero = key;
}
ClassB ClassA::getClassB(int i)
{
    return arreglo[i];
}
int ClassA::getEntero()
{
    return entero;
}
string ClassA::getCadena()
{
    return cadena;
}
string ClassA::tostring()
{
    stringstream ss;
    ss << "\tCadena: " <<cadena<< ", Llave: " <<entero<<endl;
        ss<<"\tObjetos de classB"<<endl;
        for(int i=0; i<10; i++){
        ss<<"Cadena "<< i << " = "<<arreglo[i].getStringB();
        ss<<"\tBoleano "<< i << " = "<<arreglo[i].getBoolB()<<endl;
    }
    ss << endl;
    return ss.str();
}

