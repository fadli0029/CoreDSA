#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "bits/stdc++.h"
#include "doublylinkedlist.h"

TEST_CASE("DoublyLinkedList - Default Constructor", "[DoublyLinkedList]") {
    DoublyLinkedList<int> custom_list;
    REQUIRE(custom_list.front() == nullptr);
    REQUIRE(custom_list.back() == nullptr);
    REQUIRE(custom_list.size() == 0);
    REQUIRE(custom_list.empty());
}

TEST_CASE("DoublyLinkedList - Push Front", "[DoublyLinkedList]") {
    DoublyLinkedList<int> custom_list;
    custom_list.push_front(3);
    custom_list.push_front(2);
    custom_list.push_front(1);

    auto it = custom_list.front();
    REQUIRE(it->data == 1);
    it = it->next;
    REQUIRE(it->data == 2);
    it = it->next;
    REQUIRE(it->data == 3);
    REQUIRE(it->next == nullptr);
    REQUIRE(it->prev->data == 2);
    REQUIRE(custom_list.size() == 3);
}

TEST_CASE("DoublyLinkedList - Push Back", "[DoublyLinkedList]") {
    DoublyLinkedList<int> custom_list;
    custom_list.push_back(1);
    custom_list.push_back(2);
    custom_list.push_back(3);

    auto it = custom_list.front();
    REQUIRE(it->data == 1);
    it = it->next;
    REQUIRE(it->data == 2);
    it = it->next;
    REQUIRE(it->data == 3);
    REQUIRE(it->next == nullptr);
    REQUIRE(it->prev->data == 2);
    REQUIRE(custom_list.size() == 3);
}

TEST_CASE("DoublyLinkedList - Pop Front", "[DoublyLinkedList]") {
    DoublyLinkedList<int> custom_list;
    custom_list.push_front(3);
    custom_list.push_front(2);
    custom_list.push_front(1);

    REQUIRE(custom_list.pop_front());
    auto it = custom_list.front();
    REQUIRE(it->data == 2);
    REQUIRE(it->prev == nullptr);
    REQUIRE(custom_list.size() == 2);

    REQUIRE(custom_list.pop_front());
    it = custom_list.front();
    REQUIRE(it->data == 3);
    REQUIRE(it->prev == nullptr);
    REQUIRE(custom_list.size() == 1);

    REQUIRE(custom_list.pop_front());
    REQUIRE(custom_list.front() == nullptr);
    REQUIRE(custom_list.size() == 0);

    REQUIRE_FALSE(custom_list.pop_front());
}

TEST_CASE("DoublyLinkedList - Pop Back", "[DoublyLinkedList]") {
    DoublyLinkedList<int> custom_list;
    custom_list.push_back(1);
    custom_list.push_back(2);
    custom_list.push_back(3);

    REQUIRE(custom_list.pop_back());
    auto it = custom_list.back();
    REQUIRE(it->data == 2);
    REQUIRE(it->next == nullptr);
    REQUIRE(custom_list.size() == 2);

    REQUIRE(custom_list.pop_back());
    it = custom_list.back();
    REQUIRE(it->data == 1);
    REQUIRE(it->next == nullptr);
    REQUIRE(custom_list.size() == 1);

    REQUIRE(custom_list.pop_back());
    REQUIRE(custom_list.back() == nullptr);
    REQUIRE(custom_list.size() == 0);

    REQUIRE_FALSE(custom_list.pop_back());
}

TEST_CASE("DoublyLinkedList - Insert", "[DoublyLinkedList]") {
    DoublyLinkedList<int> custom_list;
    custom_list.push_back(1);
    custom_list.push_back(3);

    auto it = custom_list.front()->next;
    custom_list.insert(it, 2);

    it = custom_list.front();
    REQUIRE(it->data == 1);
    it = it->next;
    REQUIRE(it->data == 2);
    it = it->next;
    REQUIRE(it->data == 3);
    REQUIRE(it->next == nullptr);
    REQUIRE(it->prev->data == 2);
    REQUIRE(custom_list.size() == 3);
}

TEST_CASE("DoublyLinkedList - Erase", "[DoublyLinkedList]") {
    DoublyLinkedList<int> custom_list;
    custom_list.push_back(1);
    custom_list.push_back(2);
    custom_list.push_back(3);

    auto it = custom_list.front()->next;
    custom_list.erase(it);

    it = custom_list.front();
    REQUIRE(it->data == 1);
    it = it->next;
    REQUIRE(it->data == 3);
    REQUIRE(it->next == nullptr);
    REQUIRE(it->prev->data == 1);
    REQUIRE(custom_list.size() == 2);

    custom_list.erase(custom_list.front(), custom_list.back());

    REQUIRE(custom_list.front() == custom_list.back());
    REQUIRE(custom_list.size() == 1);
}

TEST_CASE("DoublyLinkedList - Clear", "[DoublyLinkedList]") {
    DoublyLinkedList<int> custom_list;
    custom_list.push_back(1);
    custom_list.push_back(2);
    custom_list.push_back(3);

    custom_list.clear();
    REQUIRE(custom_list.front() == nullptr);
    REQUIRE(custom_list.back() == nullptr);
    REQUIRE(custom_list.size() == 0);
}

TEST_CASE("DoublyLinkedList - Copy Constructor", "[DoublyLinkedList]") {
    DoublyLinkedList<int> custom_list;
    custom_list.push_back(1);
    custom_list.push_back(2);
    custom_list.push_back(3);

    DoublyLinkedList<int> copied_list(custom_list);

    auto copied_it = copied_list.front();
    std::forward_list<int> std_list = {1, 2, 3};

    auto std_it = std_list.begin();
    while (copied_it != nullptr && std_it != std_list.end()) {
        REQUIRE(copied_it->data == *std_it);
        copied_it = copied_it->next;
        ++std_it;
    }

    REQUIRE(copied_it == nullptr);
    REQUIRE(std_it == std_list.end());
}

TEST_CASE("DoublyLinkedList - Move Constructor", "[DoublyLinkedList]") {
    DoublyLinkedList<int> custom_list;
    custom_list.push_back(1);
    custom_list.push_back(2);
    custom_list.push_back(3);

    DoublyLinkedList<int> moved_list(std::move(custom_list));

    REQUIRE(custom_list.front() == nullptr);
    REQUIRE(custom_list.size() == 0);

    auto moved_it = moved_list.front();
    std::forward_list<int> std_list = {1, 2, 3};

    auto std_it = std_list.begin();
    while (moved_it != nullptr && std_it != std_list.end()) {
        REQUIRE(moved_it->data == *std_it);
        moved_it = moved_it->next;
        ++std_it;
    }

    REQUIRE(moved_it == nullptr);
    REQUIRE(std_it == std_list.end());
}

TEST_CASE("DoublyLinkedList - Assignment Operator Deep Copy", "[DoublyLinkedList]") {
    DoublyLinkedList<int> custom_list;
    custom_list.push_back(1);
    custom_list.push_back(2);
    custom_list.push_back(3);

    DoublyLinkedList<int> assigned_list;
    assigned_list = custom_list;

    auto custom_it = custom_list.front();
    auto assigned_it = assigned_list.front();

    while (custom_it != nullptr && assigned_it != nullptr) {
        REQUIRE(custom_it->data == assigned_it->data);
        custom_it = custom_it->next;
        assigned_it = assigned_it->next;
    }

    REQUIRE(custom_it == nullptr);
    REQUIRE(assigned_it == nullptr);
}

TEST_CASE("DoublyLinkedList - Assignment Operator Transfer Resource", "[DoublyLinkedList]") {
    DoublyLinkedList<int> custom_list;
    custom_list.push_back(1);
    custom_list.push_back(2);
    custom_list.push_back(3);

    DoublyLinkedList<int> moved_list;
    moved_list = std::move(custom_list);

    REQUIRE(custom_list.front() == nullptr);
    REQUIRE(custom_list.size() == 0);

    auto moved_it = moved_list.front();
    std::forward_list<int> std_list = {1, 2, 3};

    auto std_it = std_list.begin();
    while (moved_it != nullptr && std_it != std_list.end()) {
        REQUIRE(moved_it->data == *std_it);
        moved_it = moved_it->next;
        ++std_it;
    }

    REQUIRE(moved_it == nullptr);
    REQUIRE(std_it == std_list.end());
}
