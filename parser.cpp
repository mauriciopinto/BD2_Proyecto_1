#include "parser.h"
#include "randomfile.h"
#include "statichashing.h"
#include <algorithm>
#include "ui/mainwindow.h"

bool checkfileexist(const string& tablename){
    ifstream file;
    file.open(tablename+".bin", ios::binary);
    return file.good();
}

bool checkindex(const string& tablename){
    ifstream file;
    file.open(tablename+".bin", ios::binary);
    file.seekg(0);
    char buffer[sizeof(int)];
    file.read(buffer,sizeof(int));
    cout<<"Numero Header1: "<<buffer<<endl;
    int lectura = *((int *) buffer);
    cout<<"Numero Header: "<<lectura<<endl;
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

void printvector(const vector<string>& invector){
    cout<<"Tamaño vector: "<<invector.size()<<endl;
    for (auto & i : invector) {
        cout<<i<<";";
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
        if(checkfileexist(function[3])){
            if(checkindex(function[3])){
                cout<<"Select Random"<<endl;
                random_file temp((function[3]+".bin").c_str(),(function[3]+"_index.bin").c_str());
                if (function.size () == 8) {
			record a=temp.search_record(stoi(function[7]));
			if(function[1]=="*"){
               			cout<<"La key: "<<a.key<<", tiene un value de: "<<a.value<<endl;

               			ofstream fileoutput;
                        fileoutput.open("outputcsv.csv", ios::trunc);
                        fileoutput.flush();
                        fileoutput.close();
                        fileoutput.open("outputcsv.csv", ios::app);

                        fileoutput<<("Key:");
                        fileoutput<<(",");
                        fileoutput<<("Value:");
                        fileoutput<<("\n");

                        fileoutput<<(a.key);
                        fileoutput<<(",");
                        fileoutput<<((char *) &a.value);
                        fileoutput<<("\n");

                        fileoutput.flush();
                        fileoutput.close();

                	}
                	else if(function[1]=="KEY"){
                    		cout<<function[1]<<": "<<a.key<<endl;

                            ofstream fileoutput;
                            fileoutput.open("outputcsv.csv", ios::trunc);

                            fileoutput.flush();
                            fileoutput.close();

                            fileoutput.open("outputcsv.csv", ios::app);

                            fileoutput<<("Key:");
                            fileoutput<<("\n");

                            fileoutput<<(a.key);
                            fileoutput<<("\n");

                            fileoutput.flush();
                            fileoutput.close();

                	}

                	else if(function[1]=="VALUE"){
                    		cout<<function[1]<<": "<<a.value<<endl;

                            ofstream fileoutput;
                            fileoutput.open("outputcsv.csv", ios::trunc);

                            fileoutput.flush();
                            fileoutput.close();

                            fileoutput.open("outputcsv.csv", ios::app);

                            fileoutput<<("Value:");
                            fileoutput<<("\n");

                            fileoutput<<(a.value);
                            fileoutput<<("\n");

                            fileoutput.flush();
                            fileoutput.close();

                	}
                	else{
        			cout<<"La columna que ingreso no existe en la estructura de la Base de Datos."<<endl;
	        	}

		}
		else if (function.size () == 4) {
			cout << "Selecting all records" << endl;
			vector<record> all= temp.get_all_records ();

			ofstream fileoutput;
			fileoutput.open("outputcsv.csv", ios::trunc);

			fileoutput.flush();
			fileoutput.close();

			fileoutput.open("outputcsv.csv", ios::app);

			fileoutput<<("Key:");
			fileoutput<<(",");
			fileoutput<<("Value:");
			fileoutput<<("\n");

			for (int i = 0; i < all.size (); i++){
                cout << all[i].key << " " << all[i].value << endl;
                fileoutput<<(all[i].key);
                fileoutput<<(",");
                fileoutput<<((char *) &all[i].value);
                fileoutput<<("\n");
			}

			fileoutput.flush();
			fileoutput.close();

			return; 
		}

            }
            else{
                cout<<"Select Hash"<<endl;
                hash_file temp((function[3]+".bin").c_str(),(function[3]+"_index.bin").c_str(),6,6);
                if (function.size () == 8) {
			record a=temp.search_record(stoi(function[7]));

                	if(function[1]=="*"){
                    		cout<<"La key: "<<a.key<<", tiene un value de: "<<a.value<<endl;

                    		ofstream fileoutput;
                    		fileoutput.open("outputcsv.csv", ios::trunc);

                    		fileoutput.flush();
                            fileoutput.close();

                            fileoutput.open("outputcsv.csv", ios::app);

                            fileoutput<<("Key:");
                            fileoutput<<(",");
                            fileoutput<<("Value:");
                            fileoutput<<("\n");

                            fileoutput<<(a.key);
                            fileoutput<<(",");
                            fileoutput<<((char *) &a.value);
                            fileoutput<<("\n");

                            fileoutput.flush();
                            fileoutput.close();

                		}
                	else if(function[1]=="KEY"){
                    		cout<<function[1]<<": "<<a.key<<endl;

                            ofstream fileoutput;
                            fileoutput.open("outputcsv.csv", ios::trunc);

                            fileoutput.flush();
                            fileoutput.close();

                            fileoutput.open("outputcsv.csv", ios::app);

                            fileoutput<<("Key:");
                            fileoutput<<("\n");

                            fileoutput<<(a.key);
                            fileoutput<<("\n");

                            fileoutput.flush();
                            fileoutput.close();

                	}

                	else if(function[1]=="VALUE"){
                		cout<<function[1]<<": "<<a.value<<endl;

                        ofstream fileoutput;
                        fileoutput.open("outputcsv.csv", ios::trunc);

                        fileoutput.flush();
                        fileoutput.close();

                        fileoutput.open("outputcsv.csv", ios::app);

                        fileoutput<<("Value:");
                        fileoutput<<("\n");

                        fileoutput<<(a.value);
                        fileoutput<<("\n");

                        fileoutput.flush();
                        fileoutput.close();

                	}
                	else{
                    		cout<<"La columna que ingreso no existe en la estructura de la Base de Datos."<<endl;
                	}

            	}
		else if (function.size () == 4) {
			cout << "Selecting all records" << endl;
                        vector<record> all= temp.get_all_records ();

                        ofstream fileoutput;
                        fileoutput.open("outputcsv.csv", ios::trunc);

                        fileoutput.flush();
                        fileoutput.close();

                        fileoutput.open("outputcsv.csv", ios::app);

                        fileoutput<<("Key:");
                        fileoutput<<(",");
                        fileoutput<<("Value:");
                        fileoutput<<("\n");

                        for (int i = 0; i < all.size (); i++){
                            cout << all[i].key << " " << all[i].value << endl;
                            fileoutput<<(all[i].key);
                            fileoutput<<(",");
                            fileoutput<<((char *) &all[i].value);
                            fileoutput<<("\n");
                        }

                        fileoutput.flush();
                        fileoutput.close();
                        return;
	    	}
            }
	}
        else{
            cout<<"No existe la tabla: "<<function[3]<<endl;
        }

    }

    //Buscar la lectura del tipo de indice
    //Generar el ingreso de columnas
    else if(function[0] == "CREATE"){
        cout<<"Esta funcion es para crear una tabla."<<endl;
        if(checkfileexist(function[1])) {
            ofstream file;
            file.open(function[1] + ".bin", ios::binary | ios::app);
            int choice;
            //CREATE TEST INDEX RANDOM (O HASH)
            if (function[3] == "RANDOM") {
                cout << "Creating Random file" << endl;
                choice = 1;
                file.write((char *) &choice, sizeof(int));
                file.flush();
            } else if (function[3] == "HASH") {
                cout << "Creating Hash file" << endl;
                choice = 0;
                file.write((char *) &choice, sizeof(int));
                file.flush();
            } else {
                cout << "El indice que ingreso no esta disponible en este Gestor!" << endl;
            }
            cout << "Se creo la tabla: " << function[1] << "." << endl;
            file.close();
        }
        else{
            cout<<"La tabla: "<<function[1]<<", ya existe!"<<endl;
        }
    }

    //tabla y el valor de cada columna (metiendo los valores en el objeto record)
    //INSERT INTO table_name (KEY, VALUE)
    else if(function[0] == "INSERT"){
        cout<<"Esta funcion es para insertar un elemento en la tabla."<<endl;
        if(checkfileexist(function[2])){
            if(checkindex(function[2])){
                auto *a=new record;
                init_record(a,stoi(function[4]),function[6]);
                random_file temp((function[2]+".bin").c_str(),(function[2]+"_index.bin").c_str());
                temp.add_record(a);
            }
            else{
                auto *a=new record;
                init_record(a,stoi(function[4]),function[6]);
                hash_file temp((function[2]+".bin").c_str(),(function[2]+"_index.bin").c_str(),6,6);
                temp.add_record(a);
            }
        }
        else{
            cout<<"No existe la tabla: "<<function[2]<<endl;
        }

    }

    else{
        cout<<"Esta función no esta reconocida por es gestor de base de datos."<<endl;
    }
}

//Hacer un select de toda la tabla
//Hacer transacciones concurrentes
//Hacer experimentacion
//Integrar UI