#include <iostream>
#include "HashMap.cpp"
#include "Hash.cpp"


using namespace std;

int main()
{
    HashMap<int,int> MyTable;
    MyTable.insert(10,766);
    cout << MyTable[10];
    return 0;
}
;