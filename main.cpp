#include <iostream>
#include "MyContainer.hpp"
using namespace ariel;
int main() {
    MyContainer<int> container;
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);
    container.add(2);
    container.add(2);

    std::cout << "Size of container: " << container.size() << std::endl;
    std::cout << container << std::endl;
    container.remove(2);

    std::cout << "Size of container: " << container.size() << std::endl;

    std::cout << container << std::endl;

    try{
        container.remove(2);
    }catch (exception& e){
        cout<<e.what();
    }

    std::cout << "ASCENDING ORDER: \n";
    for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
        std::cout << *it << ' ';   // 1 2 6 7 15
    }
    std::cout << std::endl;

    std::cout << "DESCENDING ORDER: \n";
    for (auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it) {
        std::cout << *it << ' ';  // 15 7 6 2 1
    }
    std::cout << std::endl;

    std::cout << "SIDE CROSS ORDER: \n";
    for (auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) {
        std::cout << *it << ' ';  // 1 15 2 7 6
    }
    std::cout << std::endl;

    std::cout << "REVERSE ORDER: \n";
    for (auto it = container.begin_reverse_order(); it != container.end_reverse_order(); ++it) {
        std::cout << *it << ' ';  // 2 1 6 15 7
    }
    std::cout << std::endl;

    std::cout << "ORDER: \n";
    for (auto it = container.begin_order(); it != container.end_order(); ++it) {
        std::cout << *it << ' ';  // 7 15 6 1 2
    }
    std::cout << std::endl;

    std::cout << "BEGIN MIDDLE ORDER OUT: \n";
    for (auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {
        std::cout << *it << ' ';  // 6 15 1 7 2
    }
    std::cout << std::endl;

  

    return 0;
}
