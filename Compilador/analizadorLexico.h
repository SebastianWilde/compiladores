#ifndef ANALIZADORLEXICO_H_INCLUDED
#define ANALIZADORLEXICO_H_INCLUDED
#include "funciones.h"
/*Analisis si es identificador o numero o char o string*/

struct Lexema
{
    int n_linea;
    string token;
    string lex;
    void Print()
    {
        cout<<n_linea <<" "<<token<<" "<<lex<<endl;
    }
};
string others(string palabra)
{
    int aux = 0;
    if (int(palabra[0])>47 && int(palabra[0])<58)
    {
        for (int i = 1; i < (int)palabra.size();i++)
        {
            if (palabra[i] == ',' && aux == 0 )
            {
                aux = 1;
                continue;
            }
            if (palabra[i] == ',' && aux == 1 )
            {
                aux = 2;
                continue;
            }
            if (aux == 1 && (int(palabra[i])>47 && int(palabra[i])<58))
            {
                aux = 3;
                //cout<<"here "<<endl;
                continue;
            }
            if (int(palabra[0])<47 && int(palabra[0])>58) aux = 2;
        }
        if (aux == 0) return "NUM";
        else if (aux == 3) return "DEC";
        else return "err";
    }
    else if ((int(palabra[0])>96 && int(palabra[0])<123) || palabra[0] == '_')
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
            token = ";";
            break;
        case '&':
            token = "&";
            break;
        case '|':
            token = "|";
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
    if (palabra == "retornar")
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
            token = a5(palabra);
            break;
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
bool analizador_linea(int n, string linea, vector<Lexema> & lexemas)
{
    Lexema aux;
    string temp="";
    string n_linea = int_to_string(n+1);
    aux.n_linea = str_to_int(n_linea);
    string token,lexema;
    vector <string> palabras;
    str_to_vector(palabras,linea);
    string escritura = "analisisLexico.txt";
    for (int i=0; i< (int)palabras.size();i++)
    {
        token = my_token(palabras[i]);
        aux.token = token;
        if (token == "err")
        {
            cout <<"Linea "<<n_linea<<" lexema "<<palabras[i]<<endl;
            return 0;
        }
        lexema = palabras[i];
        aux.lex = lexema;
        temp += n_linea + espacio(4-(int)n_linea.size()) + token + espacio(10-(int)token.size()) + lexema;
        str_to_txt(escritura,temp);
        lexemas.push_back(aux);
        temp = "";
    }
    return 1;
}

/*Analizador lexico de todo el codigo*/
bool analizador_lexico(vector <string> lineas,vector<Lexema> &lexemas)
{
    string aux = "Nº  TOKEN     LEXEMA";
    string escritura = "analisisLexico.txt";
    str_to_txt(escritura,aux);
    for(int i=0;i<(int)lineas.size();i++)
    {
        if (is_Empty(lineas[i])) continue;
        if (analizador_linea(i,lineas[i],lexemas)==0)
        {
            cout<<"Error lexico"<<endl;
            return 0;
        }

    }
    Lexema temp;
    temp.lex="$";
    temp.token="$";
    temp.n_linea=(int) lineas.size() + 1;
    lexemas.push_back(temp);
    return 1;
}


#endif // ANALIZADORLEXICO_H_INCLUDED
