#ifndef CLASSB_H
#define CLASSB_H
#include <cstdlib>
#include<sstream>

using namespace std;

class ClassB
{
    private:
        string stringB;
        bool boolB;

    public:
        ClassB();
        string getStringB();
        bool getBoolB();
        void setStringB(string b);
        void setBoolB(bool b);

};

#endif // CLASSB_H
