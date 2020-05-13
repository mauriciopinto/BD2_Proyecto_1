#include "parser.h"
#include "randomfile.h"
#include "statichashing.h"

bool checkfileexist(string tablename){
    ifstream file;
    file.open(tablename+".bin", ios::binary);
    if(file.good()){
        return true;
    }
    else{
        return false;
    }
}

bool checkindex(string tablename){
    ifstream file;
    file.open(tablename+".bin", ios::binary);
    file.seekg(0);
    char buffer[sizeof(int)];
    file.read(buffer,sizeof(int));
    int lectura=atoi(buffer);
    //1 es random
    if(lectura==1){
        return true;
    }
    //0 si es hashing dinamico
    else if(lectura==0){
        return false;
    }
    else{
        cout<<"El tipo de indice no es reconocible!"<<endl;
    }
}

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

    //Crear una funcion de busqueda por rango que guarde elementos en vector
    //Select * from tabla1 where key = 1
    if(function[0] == "SELECT"){
        cout<<"Esta funcion es un Select."<<endl;
        if(checkfileexist(function[3])==true){
            if(checkindex(function[3])==true){
                random_file temp((function[3]+".bin").c_str(),(function[3]+"_index.bin").c_str());
                record a=temp.search_record(stoi(function[7]));
                if(function[1]=="*"){
                    cout<<"La key: "<<a.key<<", tiene un value de: "<<a.value<<endl;
                }
                else if(function[1]=="KEY"){
                    cout<<function[1]<<": "<<a.key<<endl;
                }

                else if(function[1]=="VALUE"){
                    cout<<function[1]<<": "<<a.value<<endl;
                }
                else{
                    cout<<"La columna que ingreso no existe en la estructura de la Base de Datos."<<endl;
                }
            }
            else{
                hash_file temp((function[3]+".bin").c_str(),(function[3]+"_index.bin").c_str(),6,6);
                record a=temp.search_record(stoi(function[7]));
                cout<<"La key: "<<a.key<<", tiene un value de: "<<a.value<<endl;
            }
        }
        else{
            cout<<"Esta tabla no existe!"<<endl;
        }

    }

    //Buscar la lectura del tipo de indice
    //Generar el ingreso de columnas
    else if(function[0] == "CREATE"){
        cout<<"Esta funcion es para crear una tabla."<<endl;
        ofstream file;
        file.open(function[1]+".bin", ios::binary | ios::app);
        int choice;
        //CREATE TEST INDEX RANDOM (O HASH)
        if(function[3]=="RANDOM"){
            choice=1;
            file.write((char*)&choice,0);
        }
        else if(function[3]=="HASH"){
            choice=0;
            file.write((char*)&choice,0);
        }
        else{
            cout<<"El indice que ingreso no esta disponible en este Gestor!"<<endl;
        }

    }

    //tabla y el valor de cada columna (metiendo los valores en el objeto record)
    //INSERT INTO table_name (KEY, VALUE)
    else if(function[0] == "INSERT"){
        cout<<"Esta funcion es para insertar un elemento en la tabla."<<endl;
        if(checkfileexist(function[3])==true){
            if(checkindex(function[3])==true){
                record *a=new record;
                init_record(a,stoi(function[4]),(function[6]).c_str());
                random_file temp((function[2]+".bin").c_str(),(function[2]+"_index.bin").c_str());
                temp.add_record(a);
            }
            else{
                record *a=new record;
                init_record(a,stoi(function[4]),(function[6]).c_str());
                hash_file temp((function[2]+".bin").c_str(),(function[2]+"_index.bin").c_str(),6,6);
                temp.add_record(a);
            }
        }

    }

    else{
        cout<<"Esta función no esta reconocida por es gestor de base de datos."<<endl;
    }
}