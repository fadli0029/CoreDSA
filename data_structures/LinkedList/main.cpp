#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "bits/stdc++.h"
#include "linkedlist.h"

TEST_CASE("LinkedList and std::forward_list - Push Front", "[LinkedList]") {
    LinkedList<int> custom_list;
    std::forward_list<int> std_list;

    custom_list.push_front(3);
    custom_list.push_front(2);
    custom_list.push_front(1);

    std_list.push_front(3);
    std_list.push_front(2);
    std_list.push_front(1);

    auto custom_it = custom_list.front();
    auto std_it = std_list.begin();

    while (custom_it != nullptr && std_it != std_list.end()) {
        REQUIRE(custom_it->data == *std_it);
        custom_it = custom_it->next;
        ++std_it;
    }

    REQUIRE(custom_it == nullptr);
    REQUIRE(std_it == std_list.end());
}

TEST_CASE("LinkedList and std::forward_list - Pop Front", "[LinkedList]") {
    LinkedList<int> custom_list;
    std::forward_list<int> std_list;

    custom_list.push_front(3);
    custom_list.push_front(2);
    custom_list.push_front(1);

    std_list.push_front(3);
    std_list.push_front(2);
    std_list.push_front(1);

    custom_list.pop_front();
    std_list.pop_front();

    auto custom_it = custom_list.front();
    auto std_it = std_list.begin();

    while (custom_it != nullptr && std_it != std_list.end()) {
        REQUIRE(custom_it->data == *std_it);
        custom_it = custom_it->next;
        ++std_it;
    }

    REQUIRE(custom_it == nullptr);
    REQUIRE(std_it == std_list.end());
}

TEST_CASE("LinkedList and std::forward_list - Insert After", "[LinkedList]") {
    LinkedList<int> custom_list;
    std::forward_list<int> std_list;

    auto custom_it = custom_list.push_front(1);
    custom_list.insert_after(custom_it, 3);
    custom_list.insert_after(custom_it, 2);

    std_list.push_front(1);
    auto std_it = std_list.begin();
    std_it = std_list.insert_after(std_it, 2);
    std_list.insert_after(std_it, 3);

    custom_it = custom_list.front();
    std_it = std_list.begin();

    while (custom_it != nullptr && std_it != std_list.end()) {
        REQUIRE(custom_it->data == *std_it);
        custom_it = custom_it->next;
        ++std_it;
    }

    REQUIRE(custom_it == nullptr);
    REQUIRE(std_it == std_list.end());
}

TEST_CASE("LinkedList and std::forward_list - Erase After", "[LinkedList]") {
    LinkedList<int> custom_list;
    std::forward_list<int> std_list;

    auto custom_it = custom_list.push_front(1);
    custom_list.insert_after(custom_it, 2);
    custom_list.insert_after(custom_it, 3);

    std_list.push_front(1);
    auto std_it = std_list.begin();
    std_list.insert_after(std_it, 2);
    std_list.insert_after(std_it, 3);

    custom_list.erase_after(custom_it);
    std_list.erase_after(std_it);

    custom_it = custom_list.front();
    std_it = std_list.begin();

    while (custom_it != nullptr && std_it != std_list.end()) {
        REQUIRE(custom_it->data == *std_it);
        custom_it = custom_it->next;
        ++std_it;
    }

    REQUIRE(custom_it == nullptr);
    REQUIRE(std_it == std_list.end());
}

TEST_CASE("LinkedList and std::forward_list - Clear", "[LinkedList]") {
    LinkedList<int> custom_list;
    std::forward_list<int> std_list;

    custom_list.push_front(3);
    custom_list.push_front(2);
    custom_list.push_front(1);

    std_list.push_front(3);
    std_list.push_front(2);
    std_list.push_front(1);

    custom_list.clear();
    std_list.clear();

    REQUIRE(custom_list.size() == 0);
    REQUIRE(custom_list.front() == nullptr);
    REQUIRE(std_list.empty());
}

TEST_CASE("LinkedList - Copy Constructor Deep Copy", "[LinkedList]") {
    LinkedList<int> custom_list;
    custom_list.push_front(3);
    custom_list.push_front(2);
    custom_list.push_front(1);

    LinkedList<int> copied_list(custom_list);

    auto custom_it = custom_list.front();
    auto copied_it = copied_list.front();

    while (custom_it != nullptr && copied_it != nullptr) {
        REQUIRE(custom_it->data == copied_it->data);
        custom_it = custom_it->next;
        copied_it = copied_it->next;
    }

    REQUIRE(custom_it == nullptr);
    REQUIRE(copied_it == nullptr);
}

TEST_CASE("LinkedList - Move Constructor Transfer Resource", "[LinkedList]") {
    LinkedList<int> custom_list;
    custom_list.push_front(3);
    custom_list.push_front(2);
    custom_list.push_front(1);

    LinkedList<int> moved_list(std::move(custom_list));

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

TEST_CASE("LinkedList - Assignment Operator Deep Copy", "[LinkedList]") {
    LinkedList<int> custom_list;
    custom_list.push_front(3);
    custom_list.push_front(2);
    custom_list.push_front(1);

    LinkedList<int> assigned_list;
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

TEST_CASE("LinkedList - Assignment Operator Transfer Resource", "[LinkedList]") {
    LinkedList<int> custom_list;
    custom_list.push_front(3);
    custom_list.push_front(2);
    custom_list.push_front(1);

    LinkedList<int> moved_list;
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
