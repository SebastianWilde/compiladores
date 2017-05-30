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
inline bool is_number(char a)
{
    return int(a)>47 && int(a)<58;
}

inline bool is_letter(char a)
{
    return ((int(a)>96 && int(a)<123)|| (a == '_'));
}

inline bool is_simbol(char a)
{
    return (int(a)>32 && int (a)<48) ||(int(a)>57 && int (a)<64)||(int(a)>122 && int (a)<126) ||(int(a)==57 || int (a)==93);
}
/*Funcion para aumentar espacios entre palabras*/
bool tramp(string &palabra)
{
    string temp="";
    for (int i=0;i<(int)palabra.size();)
    {
        if (is_letter(palabra[i])) //palabras
        {
            while (!is_simbol(palabra[i]) && int(palabra[i])!=32 && (is_letter(palabra[i]) || is_number(palabra[i])))
            {
                temp+=palabra[i];
                i++;
            }
            temp +=" ";
            //cout<<"her "<<temp<<endl;
        }
        else if (is_number(palabra[i])) //numeros
        {

            while( is_number(palabra[i]))//(palabra[i]==',') || (!is_simbol(palabra[i]) && int(palabra[i])!=32)) //!is_letter(palabra[i]) &&
            {
                temp+=palabra[i];
                i++;
            }
            if (palabra[i]==',')
            {
                temp+=palabra[i];
                i++;
                while( is_number(palabra[i])&& i<(int)palabra.size())
                {
                    temp+=palabra[i];
                    i++;
                }
            }
            temp += " ";
        }
        else
        {
            if (int(palabra[i])==39) // 'char'
            {
                temp += palabra[i];
                i+=1;
                while (int(palabra[i])!=39 && i<(int)palabra.size())
                {
                    temp += palabra[i];
                    i++;
                }
                //cout<<palabra[i]<<endl;
                temp += palabra[i];
                temp += " ";
                i+=1;
                //cout<<"her "<<temp<<endl;
            }
            else if (int(palabra[i])==34) //"string"
            {
                temp += palabra[i];
                i+=1;
                while ( int(palabra[i])!=34 && i<(int)palabra.size())
                {
                    temp += palabra[i];
                    i++;
                }
                temp += palabra[i];
                temp += " ";
                i+=1;
                //cout<<"her "<<temp<<endl;
            }
            else //otros simbolos
            {
                temp += palabra[i];
                temp += " ";
                i++;
            }
        }
    }
    palabra=temp;
    return 1;
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
        if (int(linea[i]) == 32 || int(linea[i]) == 9)//32 es espacio y 9 es tab
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
