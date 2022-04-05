#include <iostream>
#include <list>

#include "MyList.h"

int main() {
    MyList<int> myList;

    myList.push_back(7);
    myList.push_back(5);
    myList.push_back(10);
    myList.push_back(-1);
    myList.push_back(6);

//    auto it = myList.begin();
//    auto itend = myList.end();
//    std::cout << "begin: " << it.get_current().data << " end: " << itend.get_current().data << std::endl;

    for (auto i : myList) {
        std::cout << i.data << std::endl;
    }
    return 0;
}
