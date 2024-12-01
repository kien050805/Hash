#include "customexceptions.hpp"
#include <iostream>
#include "HashMap.hpp"
#include "Hash.hpp"
#include "HashMapTree.hpp"
#include "Set.hpp"


using namespace std;

int main()
{

    HashMap<int,int> MyTable;
    MyTable.insert(10,766);
    cout << MyTable[10] << endl;
    return 0; 
}
;