//
//  LinkedList.cpp
//  TestCpp
//
//  Created by Timur Murzakov on 25/03/2023.
//

#include "LinkedList.hpp"

#include <gmock/gmock.h>

TEST(LinkedListConstructor, NoParameters) {
    LinkedList <long long> *list = new LinkedList <long long>();
    EXPECT_THAT(list->size(), 0);
    EXPECT_THAT(list->isEmpty(), true);
    
    EXPECT_THROW(list->indexOf(100), std::runtime_error);
    EXPECT_THROW(list->receive(100), std::runtime_error);
    EXPECT_THROW(list->remove((uint_fast64_t(500))), std::runtime_error);
    
    delete list;
}

TEST(LinkedListDestructor, NoParameters) {
    LinkedList <std::string> *list = new LinkedList <std::string>();
    list->add("fallen");
    list->add("angel");
    
    EXPECT_THAT(list->isEmpty(), false);
    EXPECT_THAT(list->size(), 2);
    EXPECT_THAT(list->indexOf("fallen"), 0);
    EXPECT_THAT(list->receive(1), "angel");
    EXPECT_THROW(list->receive(222), std::out_of_range);
    
    list->eraseMe();
    
    EXPECT_THAT(list->isEmpty(), true);
    EXPECT_THAT(list->size(), 0);
    EXPECT_THROW(list->indexOf("fallen"), std::runtime_error);
    EXPECT_THROW(list->receive(1), std::runtime_error);
    
    delete list;
}

TEST(LinkedListMethods, ClassicParameters) {
    LinkedList <std::string> *list = new LinkedList <std::string>();
    list->add("fallen");
    list->add("angel");
    
    EXPECT_THAT(list->isHere("angelo"), false);
    EXPECT_THAT(list->isHere("angel"), true);
    
    list->add("malon");
    EXPECT_THAT(list->receive(2), "malon");
    EXPECT_THAT(list->indexOf("malon"), 2);
    
    list->remove("fallen");
    list->remove("malon");
    EXPECT_THROW(list->receive(22), std::out_of_range);
    EXPECT_THAT(list->indexOf("fallen"), UINT_FAST64_MAX);
    EXPECT_THAT(list->size(), 1);
    EXPECT_THROW((*list)[2], std::out_of_range);
    EXPECT_THAT(list->receive(0), "angel");
    
    list->add("grown", 0);
    EXPECT_THAT(list->change("fellow", 0), "grown");
    EXPECT_THAT(list->receive(0), "fellow");
    EXPECT_THAT(list->receive(1), "angel");
    
    delete list;
}

TEST(LinkedListOthers, SliceAndSwap) {
    LinkedList <std::string> *list = new LinkedList <std::string>();
    for (int i = 0; i < 10; i++)  {
        list->add(std::to_string(i));
    }
    
    list->swap(0, 9);
    EXPECT_THAT(list->receive(0), "9");
    EXPECT_THAT(list->receive(9), "0");
    
    LinkedList <std::string> sliceList = list->receiveSlice(5, 8);
    
    for (int i = 5; i < 9; i++) {
        EXPECT_THAT(list->receive(i), std::to_string(i));
    }
}

int main(void) {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
