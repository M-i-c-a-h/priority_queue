/**
G++ SYSTEM
COURSE: CS251 DATA STRUCTURES- FALL 2022/2023
        University of Illinois Chicago
PROJECT TITLE: PROJECT 4 -Priority Queue
STARTER CODE BY: Prof Adam Koehler
EDITED BY: MICAH OREOLUWA OLUGBAMILA
DATE:  7th NOVEMBER 2023
 * */

/// Provided testing file to implement framework based tests in. The examples
/// below demonstrates a basic empty test in each framework with a single
/// assertion. The version uses the supplied catch.hpp file in starter code.
///
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Fall 2023

// Catch 2.x - Single Include Framework Testing
#define CATCH_CONFIG_MAIN

#include "prqueue.h"
#include "catch.hpp"
#include <vector>
#include <ctime>
#include <time.h>
#include <algorithm>

using namespace std;

TEST_CASE("TEST_1 -CONSTRUCTOR TESTING OF PRQUEUE()"){

    SECTION("Section 1--"
            "Testing constructor set data members to default values "){

        prqueue<int> pq;
        vector<prqueue<int>> setsOfPq;

        for(int i=0; i<100; i++){
            setsOfPq.push_back(pq);
            REQUIRE(setsOfPq[i].getRoot() == nullptr);
            REQUIRE(setsOfPq[i].size() == 0);
        }
    }

}

TEST_CASE("TEST_2 -DEQUEUE"){
    SECTION("Section 1 "){
        prqueue<string> temp;
        temp.enqueue("t", 4);
        temp.enqueue("t", 4);
        temp.enqueue("t", 3);
        temp.enqueue("t", 2);

        int num = 4;
        while(num > 0){
            string hello = temp.dequeue();
            num--;
        }

        REQUIRE(temp.size() == 0);
    }
    SECTION("Section 2 "){
        prqueue<string> pq;
        pq.enqueue("10", 10);
        pq.enqueue("4", 4);
        pq.enqueue("2", 2);
        pq.enqueue("1", 1);
        pq.enqueue("7", 7);
        pq.enqueue("71", 7);
        pq.enqueue("8", 8);
        pq.enqueue("72", 7);
        pq.enqueue("6", 6);
        pq.enqueue("8", 8);
        pq.enqueue("15", 15);
        pq.enqueue("20", 20);

        while(pq.size() > 0){
            pq.dequeue();
        }
        REQUIRE(pq.size() == 0);
    }
    SECTION("Section 3 "
            "A BST with a complex structure"){
        prqueue<string> pq;

        pq.enqueue("5", 5);
        pq.enqueue("3", 3);
        pq.enqueue("7", 7);
        pq.enqueue("71", 7);
        pq.enqueue("9", 9);
        pq.enqueue("10", 10);
        int count = 7;
        while(count > 0){
            pq.dequeue();
            count--;
        }
        REQUIRE(pq.size() == 0);
    }
    SECTION("Section 4 -"
            "A BST with a linked root only"){
        prqueue<string> pq;

        pq.enqueue("5", 5);
        pq.enqueue("51", 5);
        pq.enqueue("52", 5);

        while(pq.size() > 0){
            pq.dequeue();

        }
        REQUIRE(pq.size() == 0);
        REQUIRE(pq.size() == 0);
    }
    SECTION("Section 5 "
            "A randomly generated BST"
            "enqueued then dequeued"){
        srand(2);
        prqueue<int> pq;

        stringstream s;
        string str;
        vector<int> vec;

        for(int i=0; i<100; i++){
            vec.push_back( i + rand()%10);
            pq.enqueue(vec[i],vec[i]);

            REQUIRE(pq.size() == vec.size());
        }
        sort(vec.begin(),vec.end());
        int x = 0;
        for(int i=0; i<100; i++){
            x  = pq.dequeue();

            REQUIRE(x == vec[i]);
            REQUIRE(pq.size() == vec.size() - i -1);
        }
    }
}

TEST_CASE("TEST_3 -ENQUEUE"){
    SECTION("Section 1 with one element"
            "Testing enqueue() "){

        prqueue<int> pq;
        pq.enqueue(4, 2);

        REQUIRE(pq.getRoot() != nullptr);
        REQUIRE(pq.size() == 1);

    }
    SECTION("Section 2 "
            "A randomly generated BST"
            "enqueued vs vector sort"){
        srand(2);
        prqueue<int> pq;
        vector<int> vec;

        for(int i=0; i<100; i++){
            vec.push_back( i + rand()%10);
            pq.enqueue(vec[i],vec[i]);

            REQUIRE(pq.size() == vec.size());
        }
        sort(vec.begin(),vec.end());
        int x = 0;

        pq.begin();
        for(int i=0; i<100; i++){
             pq.next(x,x);
            REQUIRE(x == vec[i]);
        }
    }
}

TEST_CASE("TEST_4 -TOSTRING"){
    SECTION("Section 1 "
            "Testing toString() "){

        prqueue<int> pq;

        pq.clear();
        REQUIRE(pq.getRoot() == nullptr);
        REQUIRE(pq.size() == 0);

    }

    SECTION("Section 2 "
            "Testing toString() "
            " on a defined names[]"){
        prqueue<string> p1;
        string value;
        string names[]={"miach", "ethan","adam","victor","messi","ronaldo", "Jesus"};

        int nums[]={0,4,4,5,7,9,9,};
        for(int i=0; i<7;i++){
            p1.enqueue(names[i],nums[i]);
        }
        REQUIRE(p1.size()==7);
        p1.begin();

        stringstream s;
        string str = "";

        for(int i=0; i<7; i++){
            s<<nums[i]<<" value: "<<names[i]<<endl;
        }
        str = s.str();
        REQUIRE(str == p1.toString());
    }

}

TEST_CASE("TEST_5 -NEXT"){
    SECTION("Testing next() "){
        prqueue<string> temp;
        temp.enqueue("41", 4);
        temp.enqueue("42", 4);
        temp.enqueue("5", 5);
        temp.enqueue("52", 5);
        temp.enqueue("3", 3);
        temp.enqueue("2", 2);

        string x; int y;
        temp.begin();

        REQUIRE(temp.next(x,y) == true);
    }
    SECTION("Section 2 "
            "Testing randomly generated BST"
            "next priority && final next element returns false"){
        srand(2);
        prqueue<int> pq;
        vector<int> vec;

        for(int i=0; i<100; i++){
            vec.push_back( i + rand()%10);
            pq.enqueue(vec[i],vec[i]);

        }
        sort(vec.begin(),vec.end());
        int x = 0;

        pq.begin();
        for(int i=0; i<100; i++){
            pq.next(x,x);
            REQUIRE(x == vec[i]);
        }
        REQUIRE(pq.next(x,x) == false);
    }

}

TEST_CASE("TEST_6 -SIZE()"){
    SECTION("Section 1 "
            "-A simple BST of size 1"){
        prqueue<double> pq;
        pq.enqueue(3.44,1);

        REQUIRE(pq.size() == 1);
    }
    SECTION("Section 2 "
            "Testing size() after multiple dequeue"
            "(decreased size)"){
        prqueue<string> temp;
        temp.enqueue("41", 4);
        temp.enqueue("42", 4);
        temp.enqueue("5", 5);
        temp.enqueue("52", 5);
        temp.enqueue("3", 3);
        temp.enqueue("2", 2);

        int count = 0; int start = temp.size();
        for(int i=0; i<temp.size(); i++){
            if(i % 2 == 0){
                temp.dequeue();
                count++;
            }
        }

        REQUIRE(temp.size() == start - count);
    }
    SECTION("Section 3 "
            "Randomly generated BST with gradually increasing size"){
        srand(2);
        prqueue<int> pq;
        vector<int> vec;

        for(int i=0; i<100; i++){
            vec.push_back( i + rand()%10);
            pq.enqueue(vec[i],vec[i]);

            REQUIRE(pq.size() == vec.size());
        }
    }
}

TEST_CASE("TEST_7 -PEEK()"){
    SECTION("Section 1 "
            "Testing begin() a simple BST"){
        prqueue<string> temp;
        temp.enqueue("first", 1);
        temp.enqueue("second", 4);
        temp.enqueue("third", 5);

        REQUIRE("first" == temp.peek());
    }SECTION("Section 2 "
             "An increasing peek by dequeueing previous peek"){
        srand(2);
        prqueue<int> pq;
        vector<int> vec;

        for(int i=0; i<100; i++){
            vec.push_back( i + rand()%10);
            pq.enqueue(vec[i],vec[i]);
        }
        sort(vec.begin(),vec.end());
        int x = 0;

        pq.begin();
        for(int i=0; i<100; i++){
            x = pq.peek();
            REQUIRE(x == vec[i]);
            pq.dequeue();
        }
    }
}
TEST_CASE("TEST_8 -BEGIN()") {
    SECTION("Section 1 "
            "Testing begin() a simple BST where "
            "next() advances curr and curr is reset by begin()") {
        prqueue<string> temp;
        temp.enqueue("first", 1);
        temp.enqueue("second", 4);
        temp.enqueue("third", 5);

        int y;
        string x;
        temp.begin();
        temp.next(x, y);
        temp.begin();
        temp.next(x, y);
        REQUIRE(x == "first");
    }SECTION("Section 2 "
             "A non-increasing curr by call to next() && resetting call to begin") {

        prqueue<string> temp;
        temp.enqueue("first", 1);
        temp.enqueue("second", 4);
        temp.enqueue("third", 5);

        int y; string x;
        temp.begin();
        temp.next(x,y);
        temp.begin();
        temp.next(x,y);
        REQUIRE(x == "first");

        for(int i=0; i<100; i++){

            temp.begin();
            temp.next(x,y);
            REQUIRE(x == "first");
        }
    }
}
TEST_CASE("TEST_9 -operator= (assignment)") {
    SECTION("Section 1 ") {
        prqueue<string> temp;
        temp.enqueue("first", 1);
        temp.enqueue("second", 4);
        temp.enqueue("third", 5);


        prqueue<string> tempCopy;

        tempCopy = temp;

        REQUIRE(&tempCopy != &temp);
        REQUIRE(tempCopy.size() == temp.size());
        REQUIRE(tempCopy.peek() == temp.peek());

        temp.dequeue();
        REQUIRE(tempCopy.size() > temp.size());
    }

}
TEST_CASE("TEST_10 -operator== (equality)") {
    SECTION("Section 1"
            "Equal prqueues") {
        prqueue<string> temp;
        temp.enqueue("first", 1);
        temp.enqueue("second", 4);
        temp.enqueue("third", 5);


        prqueue<string> tempCopy;

        tempCopy = temp;

        REQUIRE(true == (tempCopy == temp));
    }
    SECTION("Section 1"
            "Unequal prqueues") {
        prqueue<string> temp;
        temp.enqueue("first", 1);
        temp.enqueue("second", 4);
        temp.enqueue("third", 5);


        prqueue<string> tempCopy;

        tempCopy = temp;
        temp.dequeue();

        REQUIRE(false == (tempCopy == temp));
    }

}
TEST_CASE("TEST_11 -CLEAR()") {
    SECTION("Section 1 "
            "Simple clear for an empty BST") {
        prqueue<string> temp;
        temp.clear();
        REQUIRE(0 == temp.size());
    }
    SECTION("Section 1 "
            "Clear for an non-empty BST"
            "Simple") {
        prqueue<string> temp;
        temp.enqueue("first", 1);
        temp.enqueue("second", 4);
        temp.enqueue("third", 5);

        temp.clear();
        REQUIRE(0 == temp.size());
    }

}