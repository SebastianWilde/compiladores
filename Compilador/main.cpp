#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "analizadorLexico.h"
using namespace std;
int main()
{
    /*string test = "int a=3+3.";
    tramp(test);
    cout <<test<<endl;*/
    vector<string> lineas;
    string codigo = "codigo.txt";
    txt_to_vectorstr(codigo,lineas);
    /*Permite sin espacios*/
    for (int i=0;i<(int)lineas.size();i++)
        tramp(lineas[i]);

    analizador_lexico(lineas);
    cout<< "Analizador lexico terminado"<<endl;
    cout << "Hello world!" << endl;
    return 0;
}
