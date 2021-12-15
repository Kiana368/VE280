#include <iostream>
#include "Dlist.h"
using namespace std;

int main(int argc, char *argv[])
{
    int result = 0;

    Dlist<int> ilist;
    int *ip = new int(1);

    ilist.insertBack(ip);
    *ip=2;
    ilist.insertBack(ip);
    cout<<ilist<<endl;

    ip = ilist.removeBack();
    if(*ip != 1)
        result = -1;
    delete ip;
    cout<<ilist<<endl;

    if(!ilist.isEmpty())
        result = -1;

    return result;
}
