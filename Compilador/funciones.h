#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
/*http://www.aprendeaprogramar.com/mod/resource/view.php?id=344*/
/*Algunas funciones para convertir tipos*/
int str_to_int(string s)
{

    string str = s;
    istringstream buffer(str);
    int value;
    buffer >> value;
    return value;
}

string int_to_string(int n)
{
	stringstream ss;
	ss<<n;
	return ss.str();
}

char str_to_char(string s)
{
	return s[0];
}

string char_to_string(char a)
{
	string aux="";
	aux+=a;
	return aux;
}

/*Funcion para aumentar espacios*/
string espacio(int n)
{
    string aux="";
    for (int i=0;i<n;i++)
        aux+=" ";
    return aux;
}

/* Funcion para guardar el txt en un vector*/
bool txt_to_vectorstr(string ficher, vector <string> &lineas)
{
    fstream fichero;
    string aux;
    fichero.open(ficher.c_str(), ios::in);
    if (fichero.is_open())
    {
        while (! fichero.eof() )
        {
            getline (fichero,aux);
            lineas.push_back(aux);
        }
        fichero.close();
    }
    else
    {
        return 0;
        cout << "Fichero inexistente o faltan permisos para abrirlo" << endl;
    }
    return 1;
}
/* Funcion para quitar los espacios a un string*/
bool str_to_vector (vector <string> & palabras, string linea)
{
    if ( linea == "") return 0;
    palabras.clear();
    string temp ="";
    for (int i = 0; i<(int)linea.size() ; i++)
    {
        if (int(linea[i]) == 32 || int(linea[i]) == 9)
        {
            if (temp  != "")
            {
                palabras.push_back(temp);
                temp = "";
            }
            else continue;
        }
        else temp += linea[i];
    }
    if (temp!="") palabras.push_back(temp);
    return 1;
}
/*Funcion para escribir un string en un vector*/
bool str_to_txt(string ficher, string escribir)
{
    fstream fichero;
    escribir += "\n";
    fichero.open(ficher.c_str(), ios::out |ios::app);
    if (fichero.is_open())
    {
        fichero << escribir;
        fichero.close();
    }
    else
    {
        return 0;
        cout << "Fichero inexistente o faltan permisos para abrirlo" << endl;
    }
    return 1;
}

/*Funcion para saber si una linea no contienen nada*/
bool is_Empty(string linea)
{
    if (linea.empty()) return 1;
    for (int i=0; i < (int)linea.size();i++)
        if (linea[i]!=' ') return 0;
    return 1;
}


#endif // FUNCIONES_H_INCLUDED
