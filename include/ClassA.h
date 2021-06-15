#ifndef CLASSA_H
#define CLASSA_H
#include <cstdlib>
#include "ClassB.h"
using namespace std;

class ClassA
{
    private:
        string cadena;
        int entero;
        ClassB arreglo[10];
    public:
        ClassA();
        ClassA(int entero, string cadena);
        void setCad(string cad);
        void setEntero(int key);
        int getEntero();
        string getCadena();
        ClassB getClassB(int i);
        string tostring();


};

#endif // CLASSA_H
