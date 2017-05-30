#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "analizadorLexico.h"
#include "analisisSintactico.h"
using namespace std;
int main()
{
    /*string test = "int a=3+3.";
    tramp(test);
    cout <<test<<endl;*/
/*
    vector <string> auxiliar;
    txt_to_vectorstr("terminales.txt",auxiliar);

    cout<<auxiliar.size();
    for (int i=0;i<auxiliar.size();i++)
        cout<<auxiliar[i]<<endl;*/

 /*   vector<string> reglas;
    string fichero = "reglas.txt";
    txt_to_vectorstr(fichero,reglas);
    for (int i = 0;i<(int)reglas.size();i++)
    {
        cout<<reglas[i]<<endl;
    }*/


/*
    vector<Componte> terminales, nTerminales;
    cout<< incializarGramatica(terminales,nTerminales);

*/




    vector<string> lineas;
    vector <Lexema> lexemas;
    string codigo = "codigo.txt";
    txt_to_vectorstr(codigo,lineas);
    /*Permite sin espacios*/
    for (int i=0;i<(int)lineas.size();i++)
        tramp(lineas[i]);
    analizador_lexico(lineas,lexemas);
    cout<< "Analizador lexico terminado"<<endl;
    /*for (int i=0;i<(int)lexemas.size();i++)
        lexemas[i].Print();*/
    aSintactico(lexemas);
    cout << "Hello world!" << endl;
    return 0;
}
