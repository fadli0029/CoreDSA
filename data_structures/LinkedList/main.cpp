#include "bits/stdc++.h"
#include "linkedlist.h"

template <typename T>
void print_forward_list(const std::forward_list<T>& std_list) {
    std::cout << "[";
    for (auto it = std_list.begin(); it != std_list.end(); ++it) {
        std::cout << *it;
        if (std::next(it) != std_list.end()) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

template <typename T>
void compare_lists(const LinkedList<T>& my_list, const std::forward_list<T>& std_list) {
        // std::cerr << "std::forward_list:" << std::endl;
        // print_forward_list(std_list);

    // Convert LinkedList to std::vector for easy comparison
    std::vector<T> my_vec;
    auto node = my_list.get_head();
    while (node) {
        my_vec.push_back(node->data);
        node = node->next;
    }

    // Convert std::forward_list to std::vector for easy comparison
    std::vector<T> std_vec(std_list.begin(), std_list.end());

    if (my_vec != std_vec) {
        std::cerr << "Mismatch between lists!" << std::endl;
        std::cerr << "LinkedList:" << std::endl;
        my_list.print_list();

        std::cerr << "std::forward_list:" << std::endl;
        print_forward_list(std_list);
        throw std::runtime_error("Test failed");
    }
}


int main() {
    try {
        std::cout << "Running tests for LinkedList class..." << std::endl;
        LinkedList<int> my_list;
        std::forward_list<int> std_list;

        // Test push_front
        std::cout << "Test push_front" << std::endl;
        for (int i = 0; i < 5; ++i) {
            my_list.push_front(i);
            std_list.push_front(i);
            compare_lists(my_list, std_list);
        }
        std::cout << "===> PASSED" << std::endl << std::endl;

        // Test push_back
        std::cout << "Test push_back" << std::endl;
        for (int i = 5; i < 10; ++i) {
            my_list.push_back(i);
            // std::forward_list has no push_back
            auto it = std_list.begin();
            while (std::next(it) != std_list.end()) {
                ++it;
            }
            std_list.insert_after(it, i);
            compare_lists(my_list, std_list);
        }
        std::cout << "===> PASSED" << std::endl << std::endl;

        // Test pop_front
        std::cout << "Test pop_front" << std::endl;
        for (int i = 0; i < 5; ++i) {
            my_list.pop_front();
            std_list.pop_front();
            compare_lists(my_list, std_list);
        }
        std::cout << "===> PASSED" << std::endl << std::endl;

        // Test pop_back
        std::cout << "Test pop_back" << std::endl;
        for (int i = 0; i < 3; ++i) {
            my_list.pop_back();

            // std::forward_list has no pop_back
            auto it = std_list.begin();
            while (std::next(it, 2) != std_list.end()) {
                ++it;
            }
            std_list.erase_after(it);
            compare_lists(my_list, std_list);
        }
        std::cout << "===> PASSED" << std::endl << std::endl;

        // Test clear
        std::cout << "Test clear" << std::endl;
        my_list.clear();
        std_list.clear();
        compare_lists(my_list, std_list);
        std::cout << "===> PASSED" << std::endl << std::endl;

        // Test is_empty
        std::cout << "Test is_empty" << std::endl;
        assert(my_list.is_empty() == std_list.empty());
        std::cout << "===> PASSED" << std::endl << std::endl;

        // Test front, back (both const and non-const versions)
        std::cout << "Test front, back" << std::endl;
        my_list.push_back(1);
        std_list.push_front(1);
        assert(my_list.front() == std_list.front());
        assert(my_list.back() == std_list.front());
        my_list.front() = 2;
        assert(my_list.front() == 2);
        my_list.back() = 3;
        assert(my_list.back() == 3);
        std::cout << "===> PASSED" << std::endl << std::endl;

        // Test get_size
        std::cout << "Test get_size" << std::endl;
        assert(my_list.get_size() == std::distance(std_list.begin(), std_list.end()));
        std::cout << "===> PASSED" << std::endl << std::endl;

        // Test find
        std::cout << "Test find" << std::endl;
        my_list.push_back(2);
        std_list.push_front(2);
        assert(my_list.find(2) != nullptr);
        assert(my_list.find(3) != nullptr);
        std::cout << "===> PASSED" << std::endl << std::endl;

        // Test insert_after
        std::cout << "Test insert_after" << std::endl;
        my_list.clear();
        std_list.clear();
        my_list.push_back(1);
        my_list.push_back(2);
        my_list.push_back(3);
        std_list.push_front(3);
        std_list.push_front(2);
        std_list.push_front(1);
        print_forward_list(std_list);
        my_list.print_list();
        auto node = my_list.find(1);
        my_list.insert_after(node, 5);
        auto std_node = std_list.begin();
        std_list.insert_after(std_node, 5);
        compare_lists(my_list, std_list);
        std::cout << "===> PASSED" << std::endl << std::endl;

        // Test pop (remove first occurrence)
        std::cout << "Test pop" << std::endl;
        my_list.pop(3);
        std_list.remove(3); // std::forward_list::remove removes all occurrences
        compare_lists(my_list, std_list);
        std::cout << "===> PASSED" << std::endl << std::endl;

        // Test copy constructor (deep copy)
        std::cout << "Test copy constructor" << std::endl;
        LinkedList<int> my_list_copy = my_list;
        std::forward_list<int> std_list_copy = std_list;
        compare_lists(my_list_copy, std_list_copy);
        std::cout << "===> PASSED" << std::endl << std::endl;

        // Test move constructor (resource transfer)
        std::cout << "Test move constructor" << std::endl;
        LinkedList<int> my_list_move = std::move(my_list_copy);
        assert(my_list_copy.get_size() == 0);
        compare_lists(my_list_move, std_list_copy);
        std::cout << "===> PASSED" << std::endl << std::endl;

        // Test assignment operator (deep copy)
        std::cout << "Test assignment operator" << std::endl;
        LinkedList<int> my_list_assign;
        my_list_assign = my_list;
        compare_lists(my_list_assign, std_list);
        std::cout << "===> PASSED" << std::endl << std::endl;

        // Test move assignment operator (resource transfer)
        std::cout << "Test move assignment operator" << std::endl;
        LinkedList<int> my_list_move_assign;
        my_list_move_assign = std::move(my_list_assign);
        assert(my_list_assign.get_size() == 0);
        compare_lists(my_list_move_assign, std_list);

        // Test destructor (implicitly)
        std::cout << "All tests passed successfully!" << std::endl;
    }

    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
