#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "analizadorLexico.h"
using namespace std;
int main()
{
    vector<string> lineas;
    string codigo = "codigo.txt";
    txt_to_vectorstr(codigo,lineas);
    analizador_lexico(lineas);
    cout<< "Analizador lexico terminado"<<endl;
    cout << "Hello world!" << endl;
    return 0;
}
