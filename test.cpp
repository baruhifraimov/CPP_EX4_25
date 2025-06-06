#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "MyContainer.hpp"
#include "doctest.h"
#include <iostream>
#include <string>

using namespace ariel;
using namespace std;


TEST_CASE("Basic Operations") {
    SUBCASE("Default constructor creates empty container") {
        MyContainer<int> container;
        CHECK(container.size() == 0); // Should be empty
    }
    
    SUBCASE("Copy constructor") {
        MyContainer<int> original;
        original.add(1);
        original.add(2);
        original.add(3);
        
        MyContainer<int> copy(original);
        CHECK(copy.size() == original.size()); // Should match original size
        CHECK(copy.size() == 3); // Should have 3 elements
    }
    
    SUBCASE("Assignment operator") {
        MyContainer<int> original;
        original.add(1);
        original.add(2);
        
        MyContainer<int> assigned;
        assigned.add(99);
        assigned = original;
        
        CHECK(assigned.size() == 2); // Should have 2 elements after assignment
    }
    
    SUBCASE("Size method") {
        MyContainer<int> container;
        CHECK(container.size() == 0); // Empty container
        
        container.add(5);
        CHECK(container.size() == 1); // One element
        
        container.add(10);
        container.add(15);
        CHECK(container.size() == 3); // Three elements
    }
    
    SUBCASE("Output operator") {
        MyContainer<int> container;
        ostringstream oss;
        oss << container;
        CHECK(oss.str() == "{}"); // Empty container output
        
        container.add(1);
        container.add(2);
        container.add(3);
        
        ostringstream oss2;
        oss2 << container;
        CHECK(oss2.str() == "{1, 2, 3}"); // Container with elements
    }
}

TEST_CASE("Add Elements") {
    SUBCASE("Add single element") {
        MyContainer<int> container;
        container.add(5);
        CHECK(container.size() == 1); // One element added
    }
    
    SUBCASE("Add multiple elements") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        container.add(3);
        CHECK(container.size() == 3); // Three elements added
    }
    
    SUBCASE("Add duplicate elements") {
        MyContainer<int> container;
        container.add(5);
        container.add(5);
        container.add(5);
        CHECK(container.size() == 3); // All duplicates should be added
    }
    
    SUBCASE("Add different types") {
        MyContainer<string> strContainer;
        strContainer.add("hello");
        strContainer.add("world");
        CHECK(strContainer.size() == 2); // String container with 2 elements
        
        MyContainer<double> doubleContainer;
        doubleContainer.add(3.14);
        doubleContainer.add(2.71);
        CHECK(doubleContainer.size() == 2); // Double container with 2 elements
    }
}

TEST_CASE("Remove Elements") {
    SUBCASE("Remove existing element") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        container.add(3);
        
        container.remove(2);
        CHECK(container.size() == 2); // One element removed
    }
    
    SUBCASE("Remove all occurrences of duplicate elements") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        container.add(2);
        container.add(3);
        container.add(2);
        
        container.remove(2);
        CHECK(container.size() == 2); // Should remove all three 2's
    }
    
    SUBCASE("Remove non-existing element throws exception") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        
        CHECK_THROWS_AS(container.remove(99), std::invalid_argument); // Should throw exception
    }
    
    SUBCASE("Remove from empty container throws exception") {
        MyContainer<int> container;
        CHECK_THROWS_AS(container.remove(1), std::invalid_argument); // Should throw exception
    }
}

TEST_CASE("Order Iterator") {
    SUBCASE("Empty container") {
        MyContainer<int> container;
        auto begin = container.begin_order();
        auto end = container.end_order();
        CHECK(begin == end); // Begin should equal end for empty container
    }
    
    SUBCASE("Single element") {
        MyContainer<int> container;
        container.add(42);
        
        vector<int> result;
        for (auto it = container.begin_order(); it != container.end_order(); ++it) {
            result.push_back(*it);
        }
        
        vector<int> expected = {42};
        CHECK(result == expected); // Should contain single element
    }
    
    SUBCASE("Multiple elements - insertion order") {
        MyContainer<int> container;
        container.add(7);
        container.add(15);
        container.add(6);
        container.add(1);
        container.add(2);
        
        vector<int> result;
        for (auto it = container.begin_order(); it != container.end_order(); ++it) {
            result.push_back(*it);
        }
        
        vector<int> expected = {7, 15, 6, 1, 2};
        CHECK(result == expected); // Should maintain insertion order
    }
    
    SUBCASE("Iterator operators") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        
        auto it1 = container.begin_order();
        auto it2 = container.begin_order();
        auto end = container.end_order();
        
        CHECK(it1 == it2); // Two begin iterators should be equal
        CHECK(it1 != end); // Begin should not equal end
        
        CHECK(*it1 == 1); // First element
        ++it1;
        CHECK(*it1 == 2); // Second element after increment
        CHECK(it1 != it2); // Iterators should be different after increment
    }
    
    SUBCASE("Error handling") {
        CHECK_THROWS_AS(MyContainer<int>::Order(nullptr, 0), std::invalid_argument); // Null pointer should throw
        
        MyContainer<int> container;
        container.add(1);
        
        auto it = container.end_order();
        CHECK_THROWS_AS(*it, std::out_of_range); // Dereferencing end should throw
        
        auto it2 = container.begin_order();
        ++it2; // Now at end
        CHECK_THROWS_AS(++it2, std::out_of_range); // Incrementing past end should throw
    }
}

TEST_CASE("AscendingOrder Iterator") {
    SUBCASE("Empty container") {
        MyContainer<int> container;
        auto begin = container.begin_ascending_order();
        auto end = container.end_ascending_order();
        CHECK(begin == end); // Begin should equal end for empty container
    }
    
    SUBCASE("Ascending order - example from README") {
        MyContainer<int> container;
        container.add(7);
        container.add(15);
        container.add(6);
        container.add(1);
        container.add(2);
        
        vector<int> result;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            result.push_back(*it);
        }
        
        vector<int> expected = {1, 2, 6, 7, 15};
        CHECK(result == expected); // Should be sorted in ascending order
    }
    
    SUBCASE("With duplicates") {
        MyContainer<int> container;
        container.add(3);
        container.add(1);
        container.add(3);
        container.add(2);
        
        vector<int> result;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            result.push_back(*it);
        }
        
        vector<int> expected = {1, 2, 3, 3};
        CHECK(result == expected); // Should handle duplicates in ascending order
    }
    
    SUBCASE("Error handling") {
        CHECK_THROWS_AS(MyContainer<int>::AscendingOrder(nullptr, 0), std::invalid_argument); // Null pointer should throw
    }
}

TEST_CASE("DescendingOrder Iterator") {
    SUBCASE("Descending order - example from README") {
        MyContainer<int> container;
        container.add(7);
        container.add(15);
        container.add(6);
        container.add(1);
        container.add(2);
        
        vector<int> result;
        for (auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it) {
            result.push_back(*it);
        }
        
        vector<int> expected = {15, 7, 6, 2, 1};
        CHECK(result == expected); // Should be sorted in descending order
    }
    
    SUBCASE("Single element") {
        MyContainer<int> container;
        container.add(42);
        
        vector<int> result;
        for (auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it) {
            result.push_back(*it);
        }
        
        vector<int> expected = {42};
        CHECK(result == expected); // Single element container
    }
    
    SUBCASE("Error handling") {
        CHECK_THROWS_AS(MyContainer<int>::DescendingOrder(nullptr, 0), std::invalid_argument); // Null pointer should throw
    }
}

TEST_CASE("ReverseOrder Iterator") {
    SUBCASE("Reverse order - example from README") {
        MyContainer<int> container;
        container.add(7);
        container.add(15);
        container.add(6);
        container.add(1);
        container.add(2);
        
        vector<int> result;
        for (auto it = container.begin_reverse_order(); it != container.end_reverse_order(); ++it) {
            result.push_back(*it);
        }
        
        vector<int> expected = {2, 1, 6, 15, 7};
        CHECK(result == expected); // Should be in reverse insertion order
    }
    
    SUBCASE("Single element") {
        MyContainer<int> container;
        container.add(99);
        
        vector<int> result;
        for (auto it = container.begin_reverse_order(); it != container.end_reverse_order(); ++it) {
            result.push_back(*it);
        }
        
        vector<int> expected = {99};
        CHECK(result == expected); // Single element container
    }
    
    SUBCASE("Error handling") {
        CHECK_THROWS_AS(MyContainer<int>::ReverseOrder(nullptr, 0), std::invalid_argument); // Null pointer should throw
    }
}

TEST_CASE("SideCrossOrder Iterator") {
    SUBCASE("Side cross order - example from README") {
        MyContainer<int> container;
        container.add(7);
        container.add(15);
        container.add(6);
        container.add(1);
        container.add(2);
        
        vector<int> result;
        for (auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) {
            result.push_back(*it);
        }
        
        // Sorted: [1, 2, 6, 7, 15]
        // Side cross: min, max, 2nd min, 2nd max, middle
        vector<int> expected = {1, 15, 2, 7, 6};
        CHECK(result == expected); // Should alternate between smallest and largest
    }
    
    SUBCASE("Even number of elements") {
        MyContainer<int> container;
        container.add(4);
        container.add(1);
        container.add(3);
        container.add(2);
        
        vector<int> result;
        for (auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) {
            result.push_back(*it);
        }
        
        // Sorted: [1, 2, 3, 4]
        // Side cross: 1, 4, 2, 3
        vector<int> expected = {1, 4, 2, 3};
        CHECK(result == expected); // Should handle even number of elements
    }
    
    SUBCASE("Single element") {
        MyContainer<int> container;
        container.add(42);
        
        vector<int> result;
        for (auto it = container.begin_order(); it != container.end_order(); ++it) {
            result.emplace_back(*it);
        }
        
        vector<int> expected = {42};
        CHECK(result == expected); // Single element container
    }
    
    SUBCASE("Empty container") {
        MyContainer<int> container;
        auto begin = container.begin_side_cross_order();
        auto end = container.end_side_cross_order();
        CHECK(begin == end); // Begin should equal end for empty container
    }
    
    SUBCASE("Error handling") {
        CHECK_THROWS_AS(MyContainer<int>::SideCrossOrder(nullptr, 0), std::invalid_argument); // Null pointer should throw
        
        MyContainer<int> container;
        auto it = container.begin_side_cross_order();
        CHECK_THROWS_AS(*it, std::out_of_range); // Empty container dereference should throw
    }
}

TEST_CASE("MiddleOutOrder Iterator") {
    SUBCASE("Middle out order - example from README") {
        MyContainer<int> container;
        container.add(7);
        container.add(15);
        container.add(6);
        container.add(1);
        container.add(2);
        
        vector<int> result;
        for (auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {
            result.push_back(*it);
        }
        
        // Middle index is 2 (6), then alternate left/right
        vector<int> expected = {6, 15, 1, 7, 2};
        CHECK(result == expected); // Should start from middle and expand outward
    }
    
    SUBCASE("Even number of elements") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        container.add(3);
        container.add(4);
        
        vector<int> result;
        for (auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {
            result.push_back(*it);
        }
        
        // Should start from middle (index 2), then alternate
        CHECK(result.size() == 4); // Should have all 4 elements
        CHECK(result[0] == 3); // Middle element
    }
    
    SUBCASE("Single element") {
        MyContainer<int> container;
        container.add(42);
        
        vector<int> result;
        for (auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {
            result.push_back(*it);
        }
        
        vector<int> expected = {42};
        CHECK(result == expected); // Single element container
    }
    
    SUBCASE("Error handling") {
        CHECK_THROWS_AS(MyContainer<int>::MiddleOutOrder(nullptr, 0), std::invalid_argument); // Null pointer should throw
    }
}

TEST_CASE("String Container") {
    SUBCASE("String basic operations") {
        MyContainer<string> container;
        container.add("hello");
        container.add("world");
        container.add("test");
        
        CHECK(container.size() == 3); // Three string elements
        
        container.remove("world");
        CHECK(container.size() == 2); // One string removed
    }
    
    SUBCASE("String ascending order") {
        MyContainer<string> container;
        container.add("zebra");
        container.add("apple");
        container.add("banana");
        container.add("cherry");
        
        vector<string> result;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            result.push_back(*it);
        }
        
        vector<string> expected = {"apple", "banana", "cherry", "zebra"};
        CHECK(result == expected); // Strings should be sorted alphabetically
    }
    
    SUBCASE("String descending order") {
        MyContainer<string> container;
        container.add("apple");
        container.add("zebra");
        container.add("banana");
        
        vector<string> result;
        for (auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it) {
            result.push_back(*it);
        }
        
        vector<string> expected = {"zebra", "banana", "apple"};
        CHECK(result == expected); // Strings should be sorted in reverse alphabetical order
    }
    
    SUBCASE("String output operator") {
        MyContainer<string> container;
        container.add("hello");
        container.add("world");
        
        ostringstream oss;
        oss << container;
        CHECK(oss.str() == "{hello, world}"); // Should format strings correctly
    }
}

TEST_CASE("Double Container") {
    SUBCASE("Double basic operations") {
        MyContainer<double> container;
        container.add(3.14);
        container.add(2.71);
        container.add(1.41);
        
        CHECK(container.size() == 3); // Three double elements
        
        container.remove(2.71);
        CHECK(container.size() == 2); // One double removed
    }
    
    SUBCASE("Double ascending order") {
        MyContainer<double> container;
        container.add(3.14);
        container.add(1.41);
        container.add(2.71);
        
        vector<double> result;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            result.push_back(*it);
        }
        
        CHECK(result[0] == doctest::Approx(1.41)); // First element should be smallest
        CHECK(result[1] == doctest::Approx(2.71)); // Second element
        CHECK(result[2] == doctest::Approx(3.14)); // Third element should be largest
    }
    
    SUBCASE("Double precision handling") {
        MyContainer<double> container;
        container.add(0.1);
        container.add(0.2);
        container.add(0.3);
        
        CHECK(container.size() == 3); // Should handle decimal values correctly
    }
}

TEST_CASE("Error Handling") {
    SUBCASE("Iterator null pointer exceptions") {
        CHECK_THROWS_AS(MyContainer<int>::Order(nullptr, 0), std::invalid_argument); // All iterators should reject null pointers
        CHECK_THROWS_AS(MyContainer<int>::AscendingOrder(nullptr, 0), std::invalid_argument);
        CHECK_THROWS_AS(MyContainer<int>::DescendingOrder(nullptr, 0), std::invalid_argument);
        CHECK_THROWS_AS(MyContainer<int>::ReverseOrder(nullptr, 0), std::invalid_argument);
        CHECK_THROWS_AS(MyContainer<int>::SideCrossOrder(nullptr, 0), std::invalid_argument);
        CHECK_THROWS_AS(MyContainer<int>::MiddleOutOrder(nullptr, 0), std::invalid_argument);
    }
    
    SUBCASE("Iterator out of bounds") {
        MyContainer<int> container;
        container.add(1);
        
        // Test dereference at end
        auto end_it = container.end_order();
        CHECK_THROWS_AS(*end_it, std::out_of_range); // Dereferencing end iterator should throw
        
        // Test increment past end
        auto it = container.begin_order();
        ++it; // Now at end
        CHECK_THROWS_AS(++it, std::out_of_range); // Incrementing past end should throw
    }
    
    SUBCASE("Remove exceptions") {
        MyContainer<int> container;
        
        // Remove from empty container
        CHECK_THROWS_AS(container.remove(1), std::invalid_argument); // Empty container removal should throw
        
        // Remove non-existing element
        container.add(5);
        CHECK_THROWS_AS(container.remove(10), std::invalid_argument); // Non-existing element removal should throw
    }
    
    SUBCASE("Empty container iterator handling") {
        MyContainer<int> container;
        
        CHECK_THROWS_AS(*container.begin_side_cross_order(), std::out_of_range); // Empty container dereference should throw
    }
}

TEST_CASE("Post-Increment Operators") {
    SUBCASE("Order post-increment") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        container.add(3);
        
        auto it = container.begin_order();
        auto old_it = it++;
        CHECK(*old_it == 1); // Old iterator should point to first element
        CHECK(*it == 2); // New iterator should point to second element
    }
    
    SUBCASE("AscendingOrder post-increment") {
        MyContainer<int> container;
        container.add(3);
        container.add(1);
        container.add(2);
        
        auto it = container.begin_ascending_order();
        auto old_it = it++;
        CHECK(*old_it == 1); // Old iterator should point to smallest element
        CHECK(*it == 2); // New iterator should point to second smallest
    }
    
    SUBCASE("DescendingOrder post-increment") {
        MyContainer<int> container;
        container.add(1);
        container.add(3);
        container.add(2);
        
        auto it = container.begin_descending_order();
        auto old_it = it++;
        CHECK(*old_it == 3); // Old iterator should point to largest element
        CHECK(*it == 2); // New iterator should point to second largest
    }
    
    SUBCASE("ReverseOrder post-increment") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        container.add(3);
        
        auto it = container.begin_reverse_order();
        auto old_it = it++;
        CHECK(*old_it == 3); // Old iterator should point to last inserted element
        CHECK(*it == 2); // New iterator should point to second-to-last
    }
    
    SUBCASE("SideCrossOrder post-increment") {
        MyContainer<int> container;
        container.add(2);
        container.add(1);
        container.add(3);
        
        auto it = container.begin_side_cross_order();
        auto old_it = it++;
        CHECK(*old_it == 1); // Should start with smallest
        CHECK(*it == 3); // Should move to largest
    }
    
    SUBCASE("MiddleOutOrder post-increment") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        container.add(3);
        
        auto it = container.begin_middle_out_order();
        auto old_it = it++;
        CHECK(*old_it == 2); // Should start with middle element
    }
}

TEST_CASE("Iterator Assignment Operators") {
    SUBCASE("Order assignment") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        
        auto it1 = container.begin_order();
        auto it2 = container.end_order();
        it2 = it1;
        CHECK(it1 == it2); // Should be equal after assignment
        CHECK(*it2 == 1); // Should point to same element
    }
    
    SUBCASE("AscendingOrder assignment") {
        MyContainer<int> container;
        container.add(2);
        container.add(1);
        
        auto it1 = container.begin_ascending_order();
        auto it2 = container.end_ascending_order();
        it2 = it1;
        CHECK(it1 == it2); // Should be equal after assignment
    }
    
    SUBCASE("DescendingOrder assignment") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        
        auto it1 = container.begin_descending_order();
        auto it2 = container.end_descending_order();
        it2 = it1;
        CHECK(it1 == it2); // Should be equal after assignment
    }
    
    SUBCASE("ReverseOrder assignment") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        
        auto it1 = container.begin_reverse_order();
        auto it2 = container.end_reverse_order();
        it2 = it1;
        CHECK(it1 == it2); // Should be equal after assignment
    }
    
    SUBCASE("SideCrossOrder assignment") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        
        auto it1 = container.begin_side_cross_order();
        auto it2 = container.end_side_cross_order();
        it2 = it1;
        CHECK(it1 == it2); // Should be equal after assignment
    }
    
    SUBCASE("MiddleOutOrder assignment") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        
        auto it1 = container.begin_middle_out_order();
        auto it2 = container.end_middle_out_order();
        it2 = it1;
        CHECK(it1 == it2); // Should be equal after assignment
    }
    
    SUBCASE("Self-assignment safety") {
        MyContainer<int> container;
        container.add(42);
        
        auto it = container.begin_order();
        it = it; // Self-assignment should be safe
        CHECK(*it == 42); // Should still work after self-assignment
    }
}

TEST_CASE("Iterator Copy Constructors") {
    SUBCASE("Order copy constructor") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        
        auto it1 = container.begin_order();
        auto it2(it1); // Copy constructor
        CHECK(it1 == it2); // Should be equal
        CHECK(*it2 == 1); // Should point to same element
        
        ++it1;
        CHECK(it1 != it2); // Should be different after incrementing one
    }
    
    SUBCASE("AscendingOrder copy constructor") {
        MyContainer<int> container;
        container.add(3);
        container.add(1);
        
        auto it1 = container.begin_ascending_order();
        auto it2(it1); // Copy constructor
        CHECK(it1 == it2); // Should be equal
        CHECK(*it2 == 1); // Should point to smallest element
    }
    
    SUBCASE("DescendingOrder copy constructor") {
        MyContainer<int> container;
        container.add(1);
        container.add(3);
        
        auto it1 = container.begin_descending_order();
        auto it2(it1); // Copy constructor
        CHECK(it1 == it2); // Should be equal
        CHECK(*it2 == 3); // Should point to largest element
    }
    
    SUBCASE("ReverseOrder copy constructor") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        
        auto it1 = container.begin_reverse_order();
        auto it2(it1); // Copy constructor
        CHECK(it1 == it2); // Should be equal
        CHECK(*it2 == 2); // Should point to last inserted element
    }
    
    SUBCASE("SideCrossOrder copy constructor") {
        MyContainer<int> container;
        container.add(2);
        container.add(1);
        
        auto it1 = container.begin_side_cross_order();
        auto it2(it1); // Copy constructor
        CHECK(it1 == it2); // Should be equal
        CHECK(*it2 == 1); // Should point to smallest element
    }
    
    SUBCASE("MiddleOutOrder copy constructor") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        container.add(3);
        
        auto it1 = container.begin_middle_out_order();
        auto it2(it1); // Copy constructor
        CHECK(it1 == it2); // Should be equal
        CHECK(*it2 == 2); // Should point to middle element
    }
}

TEST_CASE("Empty Container Iterator Edge Cases") {
    SUBCASE("All empty iterators equal their end") {
        MyContainer<int> container;
        
        CHECK(container.begin_order() == container.end_order());
        CHECK(container.begin_ascending_order() == container.end_ascending_order());
        CHECK(container.begin_descending_order() == container.end_descending_order());
        CHECK(container.begin_reverse_order() == container.end_reverse_order());
        CHECK(container.begin_side_cross_order() == container.end_side_cross_order());
        CHECK(container.begin_middle_out_order() == container.end_middle_out_order());
    }
    
    SUBCASE("Empty container dereference errors") {
        MyContainer<int> container;
        
        CHECK_THROWS_AS(*container.begin_order(), std::out_of_range);
        CHECK_THROWS_AS(*container.begin_ascending_order(), std::out_of_range);
        CHECK_THROWS_AS(*container.begin_descending_order(), std::out_of_range);
        CHECK_THROWS_AS(*container.begin_reverse_order(), std::out_of_range);
        CHECK_THROWS_AS(*container.begin_side_cross_order(), std::out_of_range);
        CHECK_THROWS_AS(*container.begin_middle_out_order(), std::out_of_range);
    }
    
    SUBCASE("Empty container increment errors") {
        MyContainer<int> container;
        
        auto order_it = container.begin_order();
        CHECK_THROWS_AS(++order_it, std::out_of_range);
        
        auto asc_it = container.begin_ascending_order();
        CHECK_THROWS_AS(++asc_it, std::out_of_range);
        
        auto desc_it = container.begin_descending_order();
        CHECK_THROWS_AS(++desc_it, std::out_of_range);
        
        auto rev_it = container.begin_reverse_order();
        CHECK_THROWS_AS(++rev_it, std::out_of_range);
        
        auto side_it = container.begin_side_cross_order();
        CHECK_THROWS_AS(++++side_it, std::out_of_range);
    }
}

TEST_CASE("Container Boundary Conditions") {
    SUBCASE("Single element all iterators") {
        MyContainer<int> container;
        container.add(42);
        
        // All single-element iterations should return the same element
        vector<int> order_result, asc_result, desc_result, rev_result, side_result, middle_result;
        
        for (auto it = container.begin_order(); it != container.end_order(); ++it) {
            order_result.push_back(*it);
        }
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            asc_result.push_back(*it);
        }
        for (auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it) {
            desc_result.push_back(*it);
        }
        for (auto it = container.begin_reverse_order(); it != container.end_reverse_order(); ++it) {
            rev_result.push_back(*it);
        }
        for (auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) {
            side_result.push_back(*it);
        }
        for (auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {
            middle_result.push_back(*it);
        }
        
        vector<int> expected = {42};
        CHECK(order_result == expected);
        CHECK(asc_result == expected);
        CHECK(desc_result == expected);
        CHECK(rev_result == expected);
        CHECK(side_result == expected);
        CHECK(middle_result == expected);
    }
    
    SUBCASE("Two elements - all iterator behaviors") {
        MyContainer<int> container;
        container.add(2);
        container.add(1);
        
        vector<int> order_result, asc_result, desc_result, rev_result, side_result, middle_result;
        
        for (auto it = container.begin_order(); it != container.end_order(); ++it) {
            order_result.push_back(*it);
        }
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            asc_result.push_back(*it);
        }
        for (auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it) {
            desc_result.push_back(*it);
        }
        for (auto it = container.begin_reverse_order(); it != container.end_reverse_order(); ++it) {
            rev_result.push_back(*it);
        }
        for (auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) {
            side_result.push_back(*it);
        }
        for (auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {
            middle_result.push_back(*it);
        }
        
        CHECK(order_result == vector<int>({2, 1})); // Insertion order
        CHECK(asc_result == vector<int>({1, 2})); // Ascending
        CHECK(desc_result == vector<int>({2, 1})); // Descending
        CHECK(rev_result == vector<int>({1, 2})); // Reverse insertion
        CHECK(side_result == vector<int>({1, 2})); // Side cross: min, max
        CHECK(middle_result == vector<int>({1, 2})); // Middle out from index 1
    }
}

TEST_CASE("Iterator Increment Edge Cases") {
    SUBCASE("Multiple increments to end") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        
        auto it = container.begin_order();
        CHECK(*it == 1);
        ++it;
        CHECK(*it == 2);
        ++it; // Should be at end now
        CHECK(it == container.end_order());
        CHECK_THROWS_AS(++it, std::out_of_range); // Incrementing past end should throw
    }
    
    SUBCASE("SideCrossOrder specific edge cases") {
        MyContainer<int> container;
        container.add(1);
        
        auto it = container.begin_side_cross_order();
        CHECK(*it == 1);
        ++it; // Should reach end
        CHECK(it == container.end_side_cross_order());
        CHECK_THROWS_AS(++it, std::out_of_range); // Past end increment
    }
    
    SUBCASE("MiddleOutOrder edge expansion") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        container.add(3);
        container.add(4);
        container.add(5);
        
        vector<int> result;
        for (auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {
            result.push_back(*it);
        }
        
        // Middle out from index 2 (element 3): 3, 2, 4, 1, 5
        CHECK(result.size() == 5);
        CHECK(result[0] == 3); // Middle element
    }
}

TEST_CASE("Large Container Performance Edge Cases") {
    SUBCASE("Large container with duplicates") {
        MyContainer<int> container;
        for (int i = 0; i < 100; ++i) {
            container.add(i % 10); // Add lots of duplicates
        }
        
        CHECK(container.size() == 100);
        
        // Remove all instances of a duplicate value
        container.remove(5);
        CHECK(container.size() == 90); // Should remove 10 instances
        
        // Test that iterators still work with large containers
        vector<int> asc_result;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            asc_result.push_back(*it);
        }
        CHECK(asc_result.size() == 90);
        CHECK(std::is_sorted(asc_result.begin(), asc_result.end()));
    }
}

TEST_CASE("Type-Specific Edge Cases") {
    SUBCASE("Character container") {
        MyContainer<char> container;
        container.add('z');
        container.add('a');
        container.add('m');
        
        vector<char> asc_result;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            asc_result.push_back(*it);
        }
        
        vector<char> expected = {'a', 'm', 'z'};
        CHECK(asc_result == expected);
    }
    
    SUBCASE("Float precision edge cases") {
        MyContainer<float> container;
        container.add(1.1f);
        container.add(1.100001f); // Very close values
        container.add(1.0999999f);
        
        CHECK(container.size() == 3); // All should be treated as different
        
        vector<float> asc_result;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            asc_result.push_back(*it);
        }
        CHECK(asc_result.size() == 3);
        CHECK(std::is_sorted(asc_result.begin(), asc_result.end()));
    }
}

TEST_CASE("Container State After Operations") {
    SUBCASE("Container state after copy") {
        MyContainer<int> original;
        original.add(1);
        original.add(2);
        
        MyContainer<int> copy = original;
        original.add(3); // Modify original
        
        CHECK(original.size() == 3); // Original should have 3 elements
        CHECK(copy.size() == 2); // Copy should still have 2 elements
        
        // Verify copy is independent
        vector<int> copy_result;
        for (auto it = copy.begin_order(); it != copy.end_order(); ++it) {
            copy_result.push_back(*it);
        }
        CHECK(copy_result == vector<int>({1, 2}));
    }
    
    SUBCASE("Container state after assignment") {
        MyContainer<int> container1;
        container1.add(1);
        container1.add(2);
        
        MyContainer<int> container2;
        container2.add(99);
        container2.add(88);
        container2.add(77);
        
        container2 = container1; // Assignment
        CHECK(container2.size() == 2); // Should match container1
        
        container1.add(3); // Modify container1
        CHECK(container2.size() == 2); // container2 should be unaffected
    }
    
    SUBCASE("Self-assignment safety") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        
        container = container; // Self-assignment
        CHECK(container.size() == 2); // Should be unchanged
        
        vector<int> result;
        for (auto it = container.begin_order(); it != container.end_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == vector<int>({1, 2})); // Content should be intact
    }
}

