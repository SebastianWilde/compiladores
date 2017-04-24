#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
/*http://www.aprendeaprogramar.com/mod/resource/view.php?id=344*/
using namespace std;
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
bool txt_to_vectorstr(vector <string> &lineas)
{
    fstream fichero;
    string aux;
    fichero.open("codigo.txt", ios::in);
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
bool str_to_txt(string aLexico)
{
    fstream fichero;
    aLexico += "\n";
    fichero.open("analisisLexico.txt", ios::out |ios::app);
    if (fichero.is_open())
    {
        fichero << aLexico;
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

/*Analisis si es identificador o numero o char o string*/
string others(string palabra)
{
    int aux = 0;
    if (int(palabra[0])>47 && int(palabra[0])<58)
    {
        for (int i = 1; i < (int)palabra.size();i++)
        {
            if (palabra[i] == ',') aux = 1;
            if (int(palabra[0])<47 && int(palabra[0])>58) aux = 2;
        }
        if (aux == 0) return "NUM";
        else if (aux == 1) return "DEC";
        else return "err";
    }
    else if (int(palabra[0])>96 && int(palabra[0])<123)
    {
        for (int i = 1; i < (int)palabra.size();i++)
        {
            if (int(palabra[0])<48 && int(palabra[0])>57 )  aux = 1;
            if (int(palabra[0])<97 && int(palabra[0])>123) aux = 1;
        }
        if (aux == 0) return "ID";
        else return "err";
    }
    else if (int(palabra[0]) == 39)
    {
        if (int(palabra[2] == 39)) return "LET";
        cout <<"Falta el simbolo ' "<<endl;
        return "err";
    }
    else if (int(palabra[0]) == 34)
    {
        if (int(palabra[palabra.size()-1]) == 34) return "PAL";
        cout <<"Falta el simbolo"<<char(34)<<endl;
        return "err";
    }
    return "err";
}

/* Analisis para caracter de tamano 1*/
string a1(string palabra)
{
    string token;
    switch(palabra[0])
    {
        case '+':
            token = "+";
            break;
        case '-':
            token = "-";
            break;
        case '*':
            token = "*";
            break;
        case '/':
            token = "/";
            break;
        case '=':
            token = "=";
            break;
        case '<':
            token = "<";
            break;
        case '>':
            token = ">";
            break;
        case '.':
            token = ".";
            break;
        case '{':
            token = "{";
            break;
        case '}':
            token = "}";
            break;
        case '(':
            token = "(";
            break;
        case ')':
            token = ")";
            break;
        case ';':
            token = "+";
            break;
        default:
            token = others(palabra);
            break;
    }
    return token;
}
/*Analizador para caracter de tamano 2 */
string a2 (string palabra)
{
    string token;
    if (palabra == "si")
    {
        return token = palabra;
    }
    else if (palabra == "<=")
    {
        return token = palabra;
    }
    else if (palabra == ">=")
    {
        return token = palabra;
    }
    else if (palabra == "==")
    {
        return token = palabra;
    }
    else if (palabra == "/=")
    {
        return token = palabra;
    }
    else
    {
        token = others(palabra);
    }
    return token;
}

/*Analizador para caracter de tamano 3 */
string a3 (string palabra)
{
    string token;
    if (palabra == "ini")
    {
        return token = palabra;
    }
    else if (palabra == "ent")
    {
        return token = palabra;
    }
    else if (palabra == "dec")
    {
        return token = palabra;
    }
    else if (palabra == "bin")
    {
        return token = palabra;
    }
    else if (palabra == "car")
    {
        return token = palabra;
    }
    else if (palabra == "cad")
    {
        return token = palabra;
    }
    else if (palabra == "vac")
    {
        return token = palabra;
    }
    else if (palabra == "def")
    {
        return token = palabra;
    }
    else if (palabra == "var")
    {
        return token = palabra;
    }
    else
    {
        token = others(palabra);
    }
    return token;
}

/*Analizador para caracter de tamano 4 */
string a4 (string palabra)
{
    string token;
    if (palabra == "sino")
    {
        return token = palabra;
    }
    else if(palabra == "arre")
    {
        return token = palabra;
    }
    else
    {
        token = others(palabra);
    }
    return token;
}

/*Analizador para caracter de tamano 5 */
string a5 (string palabra)
{
    string token;
    if (palabra == "bucle")
    {
        return token = palabra;
    }
    else
    {
        token = others(palabra);
    }
    return token;
}

/*Analizador para caracter de tamano 6 */
string a6 (string palabra)
{
    string token;
    if (palabra == "llamar")
    {
        return token = palabra;
    }
    else if (palabra == "cortar")
    {
        return token = palabra;
    }
    else if (palabra == "quizas")
    {
        return token = palabra;
    }
    else
    {
        token = others(palabra);
    }
    return token;
}

/*Analizador para caracter de tamano 8 */
string a8 (string palabra)
{
    string token;
    if (palabra == "regresar")
    {
        return token = palabra;
    }
    else
    {
        token = others(palabra);
    }
    return token;
}

/*Encontrar el token*/
string my_token(string palabra)
{
    string token = "";
    switch (palabra.size())
    {
        case 1:
            token = a1(palabra);
            break;
        case 2:
            token = a2(palabra);
            break;
        case 3:
            token = a3(palabra);
            break;
        case 4:
            token = a4(palabra);
            break;
        case 5:
            token = a4(palabra);
        case 6:
            token = a6 (palabra);
            break;
        case 8:
            token = a8(palabra);
            break;
        default:
            token = others(palabra);
            break;
    }
    return token;
}

/*Analizador de cada linea*/
bool analizador_linea(int n, string linea)
{
    string temp="";
    string n_linea = int_to_string(n+1);
    string token,lexema;
    vector <string> palabras;
    str_to_vector(palabras,linea);
    for (int i=0; i< (int)palabras.size();i++)
    {
        token = my_token(palabras[i]);
        if (token == "err")
        {
            cout <<"Linea "<<n_linea<<" lexema"<<palabras[i]<<endl;
            return 0;
        }
        lexema = palabras[i];
        temp += n_linea + espacio(4-(int)n_linea.size()) + token + espacio(10-(int)token.size()) + lexema;
        str_to_txt(temp);
        temp = "";
    }
    return 1;
}

/*Analizador lexico de todo el codigo*/
bool analizador_lexico(vector <string> lineas)
{
    string aux = "Nº  TOKEN     LEXEMA";
    str_to_txt(aux);
    for(int i=0;i<(int)lineas.size();i++)
    {
        if (is_Empty(lineas[i])) continue;
        if (analizador_linea(i,lineas[i])==0)
        {
            cout<<"Error lexico"<<endl;
            return 0;
        }
    }
    return 1;
}

int main()
{
    vector<string> lineas;
    txt_to_vectorstr(lineas);
    analizador_lexico(lineas);
    cout<< "Analizador léxico terminado"<<endl;
    cout << "Hello world!" << endl;
    return 0;
}
