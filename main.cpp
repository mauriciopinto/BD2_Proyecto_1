#include <iostream>
#include "parser.h"
#include "randomfile.h"
#include "statichashing.h"

using namespace std;


int main(){
    string prueba="Select * from Test where key = 1";
    //string prueba="Create Test Index hash";
    //string prueba="Insert Into Test ( 1 , Jonathan )";
    vector<string> test=read(prueba);
    printvector(test);
    determinefunction(test);
}
