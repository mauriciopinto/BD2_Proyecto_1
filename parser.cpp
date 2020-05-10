#include "parser.h"

void printvector(vector<string> invector){
    cout<<"Tamaño vector: "<<invector.size()<<endl;
    for (int i = 0; i < invector.size(); i++) {
        cout<<invector[i]<<";";
    }
    cout<<endl;
}
vector<string> read(string input){
    input = input+" ";
    std::for_each(input.begin(), input.end(), [](char & c){
        c = ::toupper(c);
    });
    vector<string> elementos;
    string delimiter=" ";
    size_t pos = 0;
    string token;
    while ((pos = input.find(delimiter)) != string::npos) {
        token = input.substr(0, pos);
        elementos.push_back(token);
        input.erase(0, pos + delimiter.length());
    }
    return elementos;
}

void determinefunction(vector<string> function){

    if(function[0] == "SELECT"){
        cout<<"Esta funcion es un Select."<<endl;
    }

    else if(function[0] == "CREATE"){
        cout<<"Esta funcion es para crear una tabla."<<endl;
    }

    else if(function[0] == "INSERT"){
        cout<<"Esta funcion es para insertar un elemento en la tabla."<<endl;
    }

    else{
        cout<<"Esta función no esta reconocida por es gestor de base de datos."<<endl;
    }
}

int main(){
    string prueba="Select * from tabla1 where h = jonathan";
    vector<string> test=read(prueba);
    printvector(test);
    determinefunction(test);
}