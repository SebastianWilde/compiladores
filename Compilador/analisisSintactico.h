#ifndef ANALISISSINTACTICO_H_INCLUDED
#define ANALISISSINTACTICO_H_INCLUDED
#include <stack>
struct Componte
{
    string simbolo;
    char tipo; //t -> terminal, n-> no terminal, f -> funcion
    vector <vector <Componte> > reglas;
};

struct TablaSintactica
{
    int nFila,nColumna;
    int **tabla;
    TablaSintactica(int f, int c)
    {
        nFila = f;
        nColumna = c;
        tabla = new int*[nFila];
        for (int i=0;i<nFila;i++)
            tabla[i] = new int [nColumna];
        for (int i = 0;i<nFila;i++)
            for (int j = 0;j<nColumna;j++)
                tabla[i][j]=-2;
    }
};

int componenteID(string simbolo, vector<Componte> vec)
{
    for (int i=0;i<(int)vec.size();i++)
        if (vec[i].simbolo==simbolo) return i;
    return -1;
}
bool inicializarReglas(vector<Componte> & terminales, vector<Componte> & nTerminales)
{
    //Capturar las reglas en un array de vectores
    vector<string> reglas;
    string fichero = "reglas.txt";
    txt_to_vectorstr(fichero,reglas);
    //for (int i = 0;i<(int)reglas.size();i++) cout<<reglas[i]<<endl;

    // Dividir cada regla en terminales y no terminales y agregarlos
    for (int i=0;i<(int)reglas.size();i++)
    {
        vector<string> vecStrProduccion;
        str_to_vector(vecStrProduccion,reglas[i]);

        int terminalID = componenteID(vecStrProduccion[0],nTerminales);
        if (terminalID == -1)
        {
            cout<<"No se encuentra al terminal"<<endl;
            return 0;
        }

        vector<Componte> produccion;
        for (int j = 1; j<(int)vecStrProduccion.size();j++)
        {
            int compID = componenteID(vecStrProduccion[j],nTerminales);
            if (compID == -1)
            {
                compID = componenteID(vecStrProduccion[j],terminales);
                if (compID == -1)
                {
                    cout<<"No se encuentra el terminal "<<vecStrProduccion[j]<<endl;
                    return 0;
                }
                produccion.push_back(terminales[compID]);
            }
            else produccion.push_back(nTerminales[compID]);
        }
        nTerminales[terminalID].reglas.push_back(produccion);
    }

    //visualizar gramatica
    /*
    for (int i=0;i<(int)nTerminales.size();i++)
    {
        cout<<nTerminales[i].simbolo<<"->";
        for (int j=0;j<(int)nTerminales[i].reglas.size();j++)
        {
            for(int k=0;k<(int)nTerminales[i].reglas[j].size();k++)
                cout<<nTerminales[i].reglas[j][k].simbolo<<" ";
            cout<<" | ";
        }
        cout<<endl;
    }*/
    return 1;
}
bool inicializarGramatica(vector<Componte> &terminales, vector<Componte> &nTerminales)
{
    //Cargando No Terminales
    vector <string> strTerminales;
    string fichero = "terminales.txt";
    txt_to_vectorstr(fichero,strTerminales);
    for (int i = 0;i<(int)strTerminales.size();i++)
    {
        Componte ter;
        ter.tipo = 't';
        ter.simbolo=strTerminales[i];
        terminales.push_back(ter);
    }
   /* for (int i = 0;i<(int)terminales.size();i++)
    {
        cout<<terminales[i].simbolo<<endl;
    }*/

    //Cargando no terminales
    vector <string> strNterminales;
    fichero = "noterminales.txt";
    txt_to_vectorstr(fichero,strNterminales);
    for (int i = 0;i<(int)strNterminales.size();i++)
    {
        Componte ter;
        ter.tipo = 'n';
        ter.simbolo=strNterminales[i];
        nTerminales.push_back(ter);
    }
    cout<<"Reglas inicializadas " <<inicializarReglas(terminales, nTerminales)<<endl;
    return 1;
}
bool cargarTablaSintactica(vector<Componte> &terminales, vector<Componte> &nTerminales, TablaSintactica & tablaSintactica)
{
    //Capturar valores de la tabla sintactica
    vector<string> tabla;
    string fichero = "tabla.txt";
    txt_to_vectorstr(fichero,tabla);
    //for (int i = 0;i<(int)tabla.size();i++) cout<<tabla[i]<<endl;

    // Dividir cada regla en terminales y no terminales y agregarlos
    for (int i=0;i<(int)tabla.size();i++)
    {
        vector<string> vecStrTabla;
        str_to_vector(vecStrTabla,tabla[i]);
        //cout << vecStrTabla[0] <<" "<<vecStrTabla[1]<<" "<<vecStrTabla[2]<<endl;
        tablaSintactica.tabla[componenteID(vecStrTabla[0],nTerminales)][componenteID(vecStrTabla[1],terminales)]
        = str_to_int(vecStrTabla[2]);
    }

    //Conjunto primero
    /*
    tablaSintactica.tabla[componenteID("s",nTerminales)][componenteID("def",terminales)] = 0;
    tablaSintactica.tabla[componenteID("s",nTerminales)][componenteID("ent",terminales)] = 0;
    tablaSintactica.tabla[componenteID("s",nTerminales)][componenteID("dec",terminales)] = 0;
    tablaSintactica.tabla[componenteID("s",nTerminales)][componenteID("bin",terminales)] = 0;
    tablaSintactica.tabla[componenteID("s",nTerminales)][componenteID("car",terminales)] = 0;
    tablaSintactica.tabla[componenteID("s",nTerminales)][componenteID("cad",terminales)] = 0;
    tablaSintactica.tabla[componenteID("s",nTerminales)][componenteID("vac",terminales)] = 0;

    tablaSintactica.tabla[componenteID("declaracion_fun",nTerminales)][componenteID("def",terminales)] = 0;
    tablaSintactica.tabla[componenteID("declaracion_fun",nTerminales)][componenteID("#",terminales)] = 1;

    tablaSintactica.tabla[componenteID("td",nTerminales)][componenteID("ent",terminales)] = 0;
    tablaSintactica.tabla[componenteID("td",nTerminales)][componenteID("dec",terminales)] = 1;
    tablaSintactica.tabla[componenteID("td",nTerminales)][componenteID("bin",terminales)] = 2;
    tablaSintactica.tabla[componenteID("td",nTerminales)][componenteID("car",terminales)] = 3;
    tablaSintactica.tabla[componenteID("td",nTerminales)][componenteID("cad",terminales)] = 4;
    tablaSintactica.tabla[componenteID("td",nTerminales)][componenteID("vac",terminales)] = 5;

    tablaSintactica.tabla[componenteID("parametros",nTerminales)][componenteID("ent",terminales)] = 0;
    tablaSintactica.tabla[componenteID("parametros",nTerminales)][componenteID("dec",terminales)] = 0;
    tablaSintactica.tabla[componenteID("parametros",nTerminales)][componenteID("bin",terminales)] = 0;
    tablaSintactica.tabla[componenteID("parametros",nTerminales)][componenteID("car",terminales)] = 0;
    tablaSintactica.tabla[componenteID("parametros",nTerminales)][componenteID("cad",terminales)] = 0;
    tablaSintactica.tabla[componenteID("parametros",nTerminales)][componenteID("vac",terminales)] = 0;
    tablaSintactica.tabla[componenteID("parametros",nTerminales)][componenteID("#",terminales)] = 1;

    tablaSintactica.tabla[componenteID("parametros_1",nTerminales)][componenteID(";",nTerminales)] = 0;
    tablaSintactica.tabla[componenteID("parametros_1",nTerminales)][componenteID("#",nTerminales)] = 1;

    tablaSintactica.tabla[componenteID("def_variables",nTerminales)][componenteID("ent",terminales)] = 0;
    tablaSintactica.tabla[componenteID("def_variables",nTerminales)][componenteID("dec",terminales)] = 0;
    tablaSintactica.tabla[componenteID("def_variables",nTerminales)][componenteID("bin",terminales)] = 0;
    tablaSintactica.tabla[componenteID("def_variables",nTerminales)][componenteID("car",terminales)] = 0;
    tablaSintactica.tabla[componenteID("def_variables",nTerminales)][componenteID("cad",terminales)] = 0;
    tablaSintactica.tabla[componenteID("def_variables",nTerminales)][componenteID("vac",terminales)] = 0;

    tablaSintactica.tabla[componenteID("def_variables_1",nTerminales)][componenteID("=",terminales)] = 0;
    tablaSintactica.tabla[componenteID("def_variables_1",nTerminales)][componenteID(";",terminales)] = 1;
    tablaSintactica.tabla[componenteID("def_variables_1",nTerminales)][componenteID("#",terminales)] = 2;

    tablaSintactica.tabla[componenteID("asignacion",nTerminales)][componenteID("=",terminales)] = 0;

    tablaSintactica.tabla[componenteID("valor",nTerminales)][componenteID("ID",terminales)] = 0;
    tablaSintactica.tabla[componenteID("valor",nTerminales)][componenteID("NUM",terminales)] = 1;
    tablaSintactica.tabla[componenteID("valor",nTerminales)][componenteID("DEC",terminales)] = 2;
    tablaSintactica.tabla[componenteID("valor",nTerminales)][componenteID("LET",terminales)] = 3;
    tablaSintactica.tabla[componenteID("valor",nTerminales)][componenteID("PAL",terminales)] = 4;
    tablaSintactica.tabla[componenteID("valor",nTerminales)][componenteID("llamar",terminales)] = 5;
    tablaSintactica.tabla[componenteID("valor",nTerminales)][componenteID("(",terminales)] = 6;

    tablaSintactica.tabla[componenteID("cuerpo",nTerminales)][componenteID("var",terminales)] = 0;
    tablaSintactica.tabla[componenteID("cuerpo",nTerminales)][componenteID("ID",terminales)] = 1;//warning
    tablaSintactica.tabla[componenteID("cuerpo",nTerminales)][componenteID("NUM",terminales)] = 2;
    tablaSintactica.tabla[componenteID("cuerpo",nTerminales)][componenteID("DEC",terminales)] = 2;
    tablaSintactica.tabla[componenteID("cuerpo",nTerminales)][componenteID("LET",terminales)] = 2;
    tablaSintactica.tabla[componenteID("cuerpo",nTerminales)][componenteID("PAL",terminales)] = 2;
    tablaSintactica.tabla[componenteID("cuerpo",nTerminales)][componenteID("(",terminales)] = 2;
    tablaSintactica.tabla[componenteID("cuerpo",nTerminales)][componenteID("si",terminales)] = 3;
    tablaSintactica.tabla[componenteID("cuerpo",nTerminales)][componenteID("bucle",terminales)] = 4;
    tablaSintactica.tabla[componenteID("cuerpo",nTerminales)][componenteID("llamar",terminales)] = 5;//warning
    tablaSintactica.tabla[componenteID("cuerpo",nTerminales)][componenteID("retornar",terminales)] = 6;
    tablaSintactica.tabla[componenteID("cuerpo",nTerminales)][componenteID("cortar",terminales)] = 7;
    tablaSintactica.tabla[componenteID("cuerpo",nTerminales)][componenteID("#",terminales)] = 8;

    tablaSintactica.tabla[componenteID("operacion",nTerminales)][componenteID("ID",terminales)] = 0;
    tablaSintactica.tabla[componenteID("operacion",nTerminales)][componenteID("NUM",terminales)] = 0;
    tablaSintactica.tabla[componenteID("operacion",nTerminales)][componenteID("DEC",terminales)] = 0;
    tablaSintactica.tabla[componenteID("operacion",nTerminales)][componenteID("LET",terminales)] = 0;
    tablaSintactica.tabla[componenteID("operacion",nTerminales)][componenteID("PAL",terminales)] = 0;
    tablaSintactica.tabla[componenteID("operacion",nTerminales)][componenteID("llamar",terminales)] = 0;
    tablaSintactica.tabla[componenteID("operacion",nTerminales)][componenteID("(",terminales)] = 0;

    tablaSintactica.tabla[componenteID("operacion_1",nTerminales)][componenteID("ID",terminales)] = 0;
    tablaSintactica.tabla[componenteID("operacion_1",nTerminales)][componenteID("NUM",terminales)] = 0;
    tablaSintactica.tabla[componenteID("operacion_1",nTerminales)][componenteID("DEC",terminales)] = 0;
    tablaSintactica.tabla[componenteID("operacion_1",nTerminales)][componenteID("LET",terminales)] = 0;
    tablaSintactica.tabla[componenteID("operacion_1",nTerminales)][componenteID("PAL",terminales)] = 0;
    tablaSintactica.tabla[componenteID("operacion_1",nTerminales)][componenteID("llamar",terminales)] = 0;
    tablaSintactica.tabla[componenteID("operacion_1",nTerminales)][componenteID("(",terminales)] = 1;

    tablaSintactica.tabla[componenteID("op",nTerminales)][componenteID("+",terminales)] = 0;
    tablaSintactica.tabla[componenteID("op",nTerminales)][componenteID("-",terminales)] = 1;
    tablaSintactica.tabla[componenteID("op",nTerminales)][componenteID("*",terminales)] = 2;
    tablaSintactica.tabla[componenteID("op",nTerminales)][componenteID("/",terminales)] = 3;

    tablaSintactica.tabla[componenteID("condicionales_2",nTerminales)][componenteID("quizas",terminales)] = 0;
    tablaSintactica.tabla[componenteID("condicionales_2",nTerminales)][componenteID("sino",terminales)] = 1;

    tablaSintactica.tabla[componenteID("condicion",nTerminales)][componenteID("ID",terminales)] = 0;
    tablaSintactica.tabla[componenteID("condicion",nTerminales)][componenteID("NUM",terminales)] = 0;
    tablaSintactica.tabla[componenteID("condicion",nTerminales)][componenteID("DEC",terminales)] = 0;
    tablaSintactica.tabla[componenteID("condicion",nTerminales)][componenteID("LET",terminales)] = 0;
    tablaSintactica.tabla[componenteID("condicion",nTerminales)][componenteID("PAL",terminales)] = 0;
    tablaSintactica.tabla[componenteID("condicion",nTerminales)][componenteID("llamar",terminales)] = 0;
    tablaSintactica.tabla[componenteID("condicion",nTerminales)][componenteID("(",terminales)] = 0;

    tablaSintactica.tabla[componenteID("opl",nTerminales)][componenteID("<",terminales)] = 0;
    tablaSintactica.tabla[componenteID("opl",nTerminales)][componenteID(">",terminales)] = 1;
    tablaSintactica.tabla[componenteID("opl",nTerminales)][componenteID("<=",terminales)] = 2;
    tablaSintactica.tabla[componenteID("opl",nTerminales)][componenteID(">=",terminales)] = 3;
    tablaSintactica.tabla[componenteID("opl",nTerminales)][componenteID("==",terminales)] = 4;
    tablaSintactica.tabla[componenteID("opl",nTerminales)][componenteID("/=",terminales)] = 5;

    tablaSintactica.tabla[componenteID("llamada_funcion",nTerminales)][componenteID("llamar",terminales)] = 0;

    tablaSintactica.tabla[componenteID("par",nTerminales)][componenteID("ID",terminales)] = 0;
    tablaSintactica.tabla[componenteID("par",nTerminales)][componenteID("NUM",terminales)] = 0;
    tablaSintactica.tabla[componenteID("par",nTerminales)][componenteID("DEC",terminales)] = 0;
    tablaSintactica.tabla[componenteID("par",nTerminales)][componenteID("LET",terminales)] = 0;
    tablaSintactica.tabla[componenteID("par",nTerminales)][componenteID("PAL",terminales)] = 0;
    tablaSintactica.tabla[componenteID("par",nTerminales)][componenteID("llamar",terminales)] = 0;
    tablaSintactica.tabla[componenteID("par",nTerminales)][componenteID("(",terminales)] = 0;

    tablaSintactica.tabla[componenteID("par_1",nTerminales)][componenteID(";",terminales)] = 0;
    tablaSintactica.tabla[componenteID("par_1",nTerminales)][componenteID("#",terminales)] = 1;

    //Conjunto siguiente
    tablaSintactica.tabla[componenteID("s",nTerminales)][componenteID("$",terminales)] = -1;

    tablaSintactica.tabla[componenteID("declaracion_fun",nTerminales)][componenteID("ent",terminales)] = -1;
    tablaSintactica.tabla[componenteID("declaracion_fun",nTerminales)][componenteID("dec",terminales)] = -1;
    tablaSintactica.tabla[componenteID("declaracion_fun",nTerminales)][componenteID("bin",terminales)] = -1;
    tablaSintactica.tabla[componenteID("declaracion_fun",nTerminales)][componenteID("car",terminales)] = -1;
    tablaSintactica.tabla[componenteID("declaracion_fun",nTerminales)][componenteID("cad",terminales)] = -1;
    tablaSintactica.tabla[componenteID("declaracion_fun",nTerminales)][componenteID("vac",terminales)] = -1;

    tablaSintactica.tabla[componenteID("td",nTerminales)][componenteID("ini",terminales)] = -1;
    tablaSintactica.tabla[componenteID("td",nTerminales)][componenteID("ID",terminales)] = -1;

    tablaSintactica.tabla[componenteID("parametros",nTerminales)][componenteID(")",terminales)] = -1;

    tablaSintactica.tabla[componenteID("parametros_1",nTerminales)][componenteID(")",terminales)] = -1;

    tablaSintactica.tabla[componenteID("def_variables",nTerminales)][componenteID("}",terminales)] = -1;

    tablaSintactica.tabla[componenteID("def_variables_1",nTerminales)][componenteID(".",terminales)] = -1;

    tablaSintactica.tabla[componenteID("asignacion",nTerminales)][componenteID(".",terminales)] = -1;
    tablaSintactica.tabla[componenteID("asignacion",nTerminales)][componenteID("var",terminales)] = -1;
    tablaSintactica.tabla[componenteID("asignacion",nTerminales)][componenteID("ID",terminales)] = -1;
    tablaSintactica.tabla[componenteID("asignacion",nTerminales)][componenteID("(",terminales)] = -1;
    tablaSintactica.tabla[componenteID("asignacion",nTerminales)][componenteID("NUM",terminales)] = -1;
    tablaSintactica.tabla[componenteID("asignacion",nTerminales)][componenteID("DEC",terminales)] = -1;
    tablaSintactica.tabla[componenteID("asignacion",nTerminales)][componenteID("LET",terminales)] = -1;
    tablaSintactica.tabla[componenteID("asignacion",nTerminales)][componenteID("PAL",terminales)] = -1;
    tablaSintactica.tabla[componenteID("asignacion",nTerminales)][componenteID("si",terminales)] = -1;
    tablaSintactica.tabla[componenteID("asignacion",nTerminales)][componenteID("bucle",terminales)] = -1;
    tablaSintactica.tabla[componenteID("asignacion",nTerminales)][componenteID("llamar",terminales)] = -1;
    tablaSintactica.tabla[componenteID("asignacion",nTerminales)][componenteID("retornar",terminales)] = -1;
    tablaSintactica.tabla[componenteID("asignacion",nTerminales)][componenteID("cortar",terminales)] = -1;

    tablaSintactica.tabla[componenteID("valor",nTerminales)][componenteID("+",terminales)] = -1;
    tablaSintactica.tabla[componenteID("valor",nTerminales)][componenteID("-",terminales)] = -1;
    tablaSintactica.tabla[componenteID("valor",nTerminales)][componenteID("*",terminales)] = -1;
    tablaSintactica.tabla[componenteID("valor",nTerminales)][componenteID("/",terminales)] = -1;
    tablaSintactica.tabla[componenteID("valor",nTerminales)][componenteID(";",terminales)] = -1;
    tablaSintactica.tabla[componenteID("valor",nTerminales)][componenteID(")",terminales)] = -1;
    tablaSintactica.tabla[componenteID("valor",nTerminales)][componenteID(".",terminales)] = -1;
    tablaSintactica.tabla[componenteID("valor",nTerminales)][componenteID("<",terminales)] = -1;
    tablaSintactica.tabla[componenteID("valor",nTerminales)][componenteID(">",terminales)] = -1;
    tablaSintactica.tabla[componenteID("valor",nTerminales)][componenteID("<=",terminales)] = -1;
    tablaSintactica.tabla[componenteID("valor",nTerminales)][componenteID(">=",terminales)] = -1;
    tablaSintactica.tabla[componenteID("valor",nTerminales)][componenteID("==",terminales)] = -1;
    tablaSintactica.tabla[componenteID("valor",nTerminales)][componenteID("/=",terminales)] = -1;
    tablaSintactica.tabla[componenteID("valor",nTerminales)][componenteID("}",terminales)] = -1;

    tablaSintactica.tabla[componenteID("cuerpo",nTerminales)][componenteID("}",terminales)] = -1;

    tablaSintactica.tabla[componenteID("operacion",nTerminales)][componenteID("+",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion",nTerminales)][componenteID("-",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion",nTerminales)][componenteID("*",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion",nTerminales)][componenteID("/",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion",nTerminales)][componenteID(";",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion",nTerminales)][componenteID(")",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion",nTerminales)][componenteID(".",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion",nTerminales)][componenteID("<",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion",nTerminales)][componenteID(">",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion",nTerminales)][componenteID("<=",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion",nTerminales)][componenteID(">=",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion",nTerminales)][componenteID("==",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion",nTerminales)][componenteID("/=",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion",nTerminales)][componenteID("}",terminales)] = -1;

    tablaSintactica.tabla[componenteID("operacion_1",nTerminales)][componenteID("+",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion_1",nTerminales)][componenteID("-",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion_1",nTerminales)][componenteID("*",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion_1",nTerminales)][componenteID("/",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion_1",nTerminales)][componenteID(";",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion_1",nTerminales)][componenteID(")",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion_1",nTerminales)][componenteID(".",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion_1",nTerminales)][componenteID("<",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion_1",nTerminales)][componenteID(">",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion_1",nTerminales)][componenteID("<=",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion_1",nTerminales)][componenteID(">=",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion_1",nTerminales)][componenteID("==",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion_1",nTerminales)][componenteID("/=",terminales)] = -1;
    tablaSintactica.tabla[componenteID("operacion_1",nTerminales)][componenteID("}",terminales)] = -1;

    tablaSintactica.tabla[componenteID("op",nTerminales)][componenteID("ID",terminales)] = -1;
    tablaSintactica.tabla[componenteID("op",nTerminales)][componenteID("NUM",terminales)] = -1;
    tablaSintactica.tabla[componenteID("op",nTerminales)][componenteID("DEC",terminales)] = -1;
    tablaSintactica.tabla[componenteID("op",nTerminales)][componenteID("LET",terminales)] = -1;
    tablaSintactica.tabla[componenteID("op",nTerminales)][componenteID("PAL",terminales)] = -1;
    tablaSintactica.tabla[componenteID("op",nTerminales)][componenteID("llamar",terminales)] = -1;
    tablaSintactica.tabla[componenteID("op",nTerminales)][componenteID("(",terminales)] = -1;

    tablaSintactica.tabla[componenteID("condicionales_2",nTerminales)][componenteID(".",terminales)] = -1;
    tablaSintactica.tabla[componenteID("condicionales_2",nTerminales)][componenteID("var",terminales)] = -1;
    tablaSintactica.tabla[componenteID("condicionales_2",nTerminales)][componenteID("ID",terminales)] = -1;
    tablaSintactica.tabla[componenteID("condicionales_2",nTerminales)][componenteID("(",terminales)] = -1;
    tablaSintactica.tabla[componenteID("condicionales_2",nTerminales)][componenteID("NUM",terminales)] = -1;
    tablaSintactica.tabla[componenteID("condicionales_2",nTerminales)][componenteID("DEC",terminales)] = -1;
    tablaSintactica.tabla[componenteID("condicionales_2",nTerminales)][componenteID("LET",terminales)] = -1;
    tablaSintactica.tabla[componenteID("condicionales_2",nTerminales)][componenteID("PAL",terminales)] = -1;
    tablaSintactica.tabla[componenteID("condicionales_2",nTerminales)][componenteID("si",terminales)] = -1;
    tablaSintactica.tabla[componenteID("condicionales_2",nTerminales)][componenteID("bucle",terminales)] = -1;
    tablaSintactica.tabla[componenteID("condicionales_2",nTerminales)][componenteID("llamar",terminales)] = -1;
    tablaSintactica.tabla[componenteID("condicionales_2",nTerminales)][componenteID("retornar",terminales)] = -1;
    tablaSintactica.tabla[componenteID("condicionales_2",nTerminales)][componenteID("cortar",terminales)] = -1;


    tablaSintactica.tabla[componenteID("condicion",nTerminales)][componenteID("}",terminales)] = -1;

    tablaSintactica.tabla[componenteID("opl",nTerminales)][componenteID("ID",terminales)] = -1;
    tablaSintactica.tabla[componenteID("opl",nTerminales)][componenteID("NUM",terminales)] = -1;
    tablaSintactica.tabla[componenteID("opl",nTerminales)][componenteID("DEC",terminales)] = -1;
    tablaSintactica.tabla[componenteID("opl",nTerminales)][componenteID("LET",terminales)] = -1;
    tablaSintactica.tabla[componenteID("opl",nTerminales)][componenteID("PAL",terminales)] = -1;
    tablaSintactica.tabla[componenteID("opl",nTerminales)][componenteID("llamar",terminales)] = -1;
    tablaSintactica.tabla[componenteID("opl",nTerminales)][componenteID("(",terminales)] = -1;

    tablaSintactica.tabla[componenteID("llamada_funcion",nTerminales)][componenteID("+",terminales)] = -1;
    tablaSintactica.tabla[componenteID("llamada_funcion",nTerminales)][componenteID("-",terminales)] = -1;
    tablaSintactica.tabla[componenteID("llamada_funcion",nTerminales)][componenteID("*",terminales)] = -1;
    tablaSintactica.tabla[componenteID("llamada_funcion",nTerminales)][componenteID("/",terminales)] = -1;
    tablaSintactica.tabla[componenteID("llamada_funcion",nTerminales)][componenteID(";",terminales)] = -1;
    tablaSintactica.tabla[componenteID("llamada_funcion",nTerminales)][componenteID(")",terminales)] = -1;
    tablaSintactica.tabla[componenteID("llamada_funcion",nTerminales)][componenteID(".",terminales)] = -1;
    tablaSintactica.tabla[componenteID("llamada_funcion",nTerminales)][componenteID("<",terminales)] = -1;
    tablaSintactica.tabla[componenteID("llamada_funcion",nTerminales)][componenteID(">",terminales)] = -1;
    tablaSintactica.tabla[componenteID("llamada_funcion",nTerminales)][componenteID("<=",terminales)] = -1;
    tablaSintactica.tabla[componenteID("llamada_funcion",nTerminales)][componenteID(">=",terminales)] = -1;
    tablaSintactica.tabla[componenteID("llamada_funcion",nTerminales)][componenteID("==",terminales)] = -1;
    tablaSintactica.tabla[componenteID("llamada_funcion",nTerminales)][componenteID("/=",terminales)] = -1;
    tablaSintactica.tabla[componenteID("llamada_funcion",nTerminales)][componenteID("}",terminales)] = -1;

    tablaSintactica.tabla[componenteID("par",nTerminales)][componenteID(")",terminales)] = -1;

    tablaSintactica.tabla[componenteID("par_1",nTerminales)][componenteID(")",terminales)] = -1;
    */
    return 1;
}

int siguienteProduccion( vector <Componte> & aux,string nt, string t, vector<Componte> nTerminales, vector<Componte> terminales, TablaSintactica ts)
{
    aux.clear();
    int indice = ts.tabla[componenteID(nt,nTerminales)][componenteID(t,terminales)];
    //cout<<endl<<"este es el indice "<<indice<<nt<<t<<endl;
    if (indice == -1) return indice;
    else if(indice == -2) return indice;
    aux = nTerminales[componenteID(nt,nTerminales)].reglas[indice];
    for (int i=0;i<(int)aux.size();i++)
        cout<<aux[i].simbolo<<" ";
    cout<<endl;
    return 1;
}
inline bool esOp(string token)
{
    return token=="+" || token=="-"||token=="*"||token=="/";
}

inline bool esOpl(string token)
{
    return token=="<" || token==">"||token=="<="||token==">="||token=="=="||token=="/="||token=="&"||token=="|";
}

bool aSintactico(vector <Lexema> lexemas)
{
    vector<Componte> terminales, nTerminales;
    cout<<"Gramatica inicializada "<<inicializarGramatica(terminales, nTerminales)<<endl;
    TablaSintactica ts (nTerminales.size(),terminales.size());
    cout<<"Tabla sintactica cargada "<<cargarTablaSintactica(terminales, nTerminales,ts)<<endl;
/*
    vector <Componte> aux;
    aux = nTerminales[0].reglas[ts.tabla[componenteID("s",nTerminales)][componenteID("def",terminales)]];
    for (int i=0;i<(int)aux.size();i++)
        cout<<aux[i].simbolo<<" ";
    cout<<endl;*/

    //Inicializacion de la pila
    cout<<endl<<"Iniciando el analisis sintactico..."<<endl;
    Componte simbolo_inicial, simbolo_final;
    simbolo_final.simbolo="$";
    simbolo_final.tipo='t';
    simbolo_inicial.simbolo="s";
    simbolo_inicial.tipo='n';
    stack<Componte> pila;
    pila.push(simbolo_final);
    pila.push(simbolo_inicial);
    int iterador = 0;
    int errores = 0;
    vector <string> lista_errores;
    while (!pila.empty())//&&iterador<4)
    {
        Componte Saliente;
        Saliente = pila.top();
        pila.pop();
        cout<<"Saliente: "<<Saliente.simbolo<< " lexema: "<<lexemas[iterador].token<<endl;
        if (Saliente.tipo=='t')
        {
            if (Saliente.simbolo == lexemas[iterador].token)
                iterador ++;
            else
            {
                string error;
                error = "Error en la linea: " + int_to_string(lexemas[iterador].n_linea) + " " +
                Saliente.simbolo +" incompatible con el lexema "+lexemas[iterador].token;//<<endl;
                lista_errores.push_back(error);
                iterador ++;
                errores ++;
            }
        }
        else
        {
            vector <Componte> Entrante;
            int busqueda;
            if (Saliente.simbolo == "valor" && (esOp(lexemas[iterador+1].token)||esOpl(lexemas[iterador+1].token)))
            {
                Entrante = nTerminales[componenteID(Saliente.simbolo,nTerminales)].reglas[6];
                busqueda = 1;
            }
            else if(Saliente.simbolo == "operacion_1" && (esOp(lexemas[iterador+1].token)||esOpl(lexemas[iterador+1].token)))
            {
                //Entrante = nTerminales[componenteID("valor",nTerminales)].reglas[0];
                siguienteProduccion(Entrante,"valor",lexemas[iterador].token,nTerminales,terminales,ts);
                busqueda = 1;
            }
            else if(Saliente.simbolo == "cuerpo" && (esOp(lexemas[iterador+1].token)||esOpl(lexemas[iterador+1].token)))
            {
                Entrante = nTerminales[componenteID(Saliente.simbolo,nTerminales)].reglas[2];
                busqueda = 1;
            }
            else if(Saliente.simbolo == "cuerpo_bucle" && (esOp(lexemas[iterador+1].token)||esOpl(lexemas[iterador+1].token)))
            {
                Entrante = nTerminales[componenteID(Saliente.simbolo,nTerminales)].reglas[2];
                busqueda = 1;
            }
            else
                busqueda = siguienteProduccion(Entrante,Saliente.simbolo,lexemas[iterador].token,nTerminales,terminales,ts);
            if (busqueda == 1)
                for (int i = Entrante.size()-1;i>-1;i--)
                    pila.push(Entrante[i]);
        }
    }

    cout<<endl<<endl<<"Cantidad de errores "<<errores<<endl<<endl;
    for (int i=0; i<(int)lista_errores.size();i++)
    {
        cout << lista_errores[i] <<endl;
    }
    return 1;

}

#endif // ANALISISSINTACTICO_H_INCLUDED
