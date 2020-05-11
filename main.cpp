#include <iostream>
#include "parser.h"

using namespace std;

int main(){
    string prueba="Select * from tabla1 where h = jonathan";
    vector<string> test=read(prueba);
    printvector(test);
    determinefunction(test);
}
