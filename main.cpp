#include <iostream>
#include <string>
#include "MyContainer.hpp"
using namespace ariel;
int main() {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "INT CONTAINER DEMONSTRATION" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    MyContainer<int> container;
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);

    std::cout << "Size of container: " << container.size() << std::endl;

    std::cout << container << std::endl;


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

    // add additional 2 elements
    container.add(2);
    container.add(2);

    std::cout << "Size of container: " << container.size() << std::endl; // 7
    std::cout << container << std::endl; // 7 15 6 1 2 2 2

    container.remove(2); // 7 15 6 1

    std::cout << "Size of container: " << container.size() << std::endl; 
    std::cout << container << std::endl; // 7 15 6 1

    try{
        container.remove(2);
    }catch (std::exception& e){
        std::cout<<e.what(); // throws an error 'Object does not exist'
    }

    // -------------------------------------------------------------------------------------------

    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "STRING CONTAINER DEMONSTRATION" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    MyContainer<std::string> stringContainer;
    stringContainer.add("apple");
    stringContainer.add("zebra");
    stringContainer.add("banana");
    stringContainer.add("cherry");
    stringContainer.add("date");

    std::cout << "Size of string container: " << stringContainer.size() << std::endl; // 5
    std::cout << stringContainer << std::endl; // apple zebra banana cherry date

    std::cout << "ASCENDING ORDER (strings): \n";
    for (auto it = stringContainer.begin_ascending_order(); it != stringContainer.end_ascending_order(); ++it) {
        std::cout << *it << ' ';   // apple banana cherry date zebra
    }
    std::cout << std::endl;

    std::cout << "DESCENDING ORDER (strings): \n";
    for (auto it = stringContainer.begin_descending_order(); it != stringContainer.end_descending_order(); ++it) {
        std::cout << *it << ' ';  // zebra date cherry banana apple
    }
    std::cout << std::endl;

    std::cout << "SIDE CROSS ORDER (strings): \n";
    for (auto it = stringContainer.begin_side_cross_order(); it != stringContainer.end_side_cross_order(); ++it) {
        std::cout << *it << ' ';  // apple zebra banana date cherry
    }
    std::cout << std::endl;

    std::cout << "REVERSE ORDER (strings): \n";
    for (auto it = stringContainer.begin_reverse_order(); it != stringContainer.end_reverse_order(); ++it) {
        std::cout << *it << ' ';  // date cherry banana zebra apple
    }
    std::cout << std::endl;

    std::cout << "ORDER (strings): \n";
    for (auto it = stringContainer.begin_order(); it != stringContainer.end_order(); ++it) {
        std::cout << *it << ' ';  // apple zebra banana cherry date
    }
    std::cout << std::endl;

    std::cout << "MIDDLE OUT ORDER (strings): \n";
    for (auto it = stringContainer.begin_middle_out_order(); it != stringContainer.end_middle_out_order(); ++it) {
        std::cout << *it << ' ';  // banana zebra cherry apple date
    }
    std::cout << std::endl;

    // Test string operations
    stringContainer.add("apple");
    stringContainer.add("apple");
    std::cout << "Size after adding duplicates: " << stringContainer.size() << std::endl;
    std::cout << stringContainer << std::endl;

    stringContainer.remove("apple");
    std::cout << "Size after removing all 'apple': " << stringContainer.size() << std::endl;
    std::cout << stringContainer << std::endl;

    // -------------------------------------------------------------------------------------------

    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "DOUBLE CONTAINER DEMONSTRATION" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    MyContainer<double> doubleContainer;
    doubleContainer.add(3.14);
    doubleContainer.add(2.71);
    doubleContainer.add(1.41);
    doubleContainer.add(9.81);
    doubleContainer.add(6.28);

    std::cout << "Size of double container: " << doubleContainer.size() << std::endl;
    std::cout << doubleContainer << std::endl;

    std::cout << "ASCENDING ORDER (doubles): \n";
    for (auto it = doubleContainer.begin_ascending_order(); it != doubleContainer.end_ascending_order(); ++it) {
        std::cout << *it << ' ';   // 1.41 2.71 3.14 6.28 9.81
    }
    std::cout << std::endl;

    std::cout << "DESCENDING ORDER (doubles): \n";
    for (auto it = doubleContainer.begin_descending_order(); it != doubleContainer.end_descending_order(); ++it) {
        std::cout << *it << ' ';  // 9.81 6.28 3.14 2.71 1.41
    }
    std::cout << std::endl;

    std::cout << "SIDE CROSS ORDER (doubles): \n";
    for (auto it = doubleContainer.begin_side_cross_order(); it != doubleContainer.end_side_cross_order(); ++it) {
        std::cout << *it << ' ';  // 1.41 9.81 2.71 6.28 3.14
    }
    std::cout << std::endl;

    std::cout << "REVERSE ORDER (doubles): \n";
    for (auto it = doubleContainer.begin_reverse_order(); it != doubleContainer.end_reverse_order(); ++it) {
        std::cout << *it << ' ';  // 6.28 9.81 1.41 2.71 3.14
    }
    std::cout << std::endl;

    std::cout << "ORDER (doubles): \n";
    for (auto it = doubleContainer.begin_order(); it != doubleContainer.end_order(); ++it) {
        std::cout << *it << ' ';  // 3.14 2.71 1.41 9.81 6.28
    }
    std::cout << std::endl;

    std::cout << "MIDDLE OUT ORDER (doubles): \n";
    for (auto it = doubleContainer.begin_middle_out_order(); it != doubleContainer.end_middle_out_order(); ++it) {
        std::cout << *it << ' ';  // 1.41 2.71 9.81 3.14 6.28
    }
    std::cout << std::endl;

    // Test double operations and precision
    doubleContainer.add(3.14);
    doubleContainer.add(3.14);
    std::cout << "Size after adding duplicates: " << doubleContainer.size() << std::endl;
    std::cout << doubleContainer << std::endl;

    doubleContainer.remove(3.14);
    std::cout << "Size after removing all '3.14': " << doubleContainer.size() << std::endl;
    std::cout << doubleContainer << std::endl;

    // Test exception handling
    try{
        doubleContainer.remove(99.99);
    }catch (std::exception& e){
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}
