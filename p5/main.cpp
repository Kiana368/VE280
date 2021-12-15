#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cassert>
#include "Dlist.h"
#include "Instr.h"
using namespace std;
void add(int *mem){
    mem[2]=10;
}

int main() {
    int mem[5]={1,2,3,4,5};
    add(mem);
    for (int i = 0; i <5 ; ++i) {
        cout<<mem[i]<<endl;
    }
    return 0;
}
