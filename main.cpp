//
// Created by Micah Olugbamila on 11/4/23.
//
#include "prqueue.h"
#include <iostream>

using namespace std;

int main(){

//    prqueue<string> temp;
//    temp.enqueue("41", 4);
//    temp.enqueue("42", 4);
//    temp.enqueue("5", 5);
//    temp.enqueue("52", 5);
//    temp.enqueue("3", 3);
//    temp.enqueue("2", 2);
//
//    int num = 4;
//    while(num > -3){
//        string hello = temp.dequeue();
//        cout << hello << endl;
//        num--;
//    }
//    prqueue<string> pq;
//
////    pq.enqueue("10",10);
////    pq.enqueue("12",12);
////
////    pq.enqueue("4",4);
////    pq.enqueue("2",2);
////    pq.enqueue("71",7);
////    pq.enqueue("1",1);
////    pq.enqueue("72",7);
////    pq.enqueue("73",7);
////    pq.enqueue("8",8);
////    pq.enqueue("3",3);
//    pq.enqueue("6", 6);
//    pq.enqueue("1", 1);
//    pq.enqueue("15", 15);
//    pq.enqueue("2", 2);
//    pq.enqueue("4",4);
//    pq.enqueue("10",10);
//    pq.enqueue("20",20);
//    pq.enqueue("62", 6);
//    pq.enqueue("63", 6);
//    pq.enqueue("64",6);
//    cout << pq.toString() << endl;
//
//    prqueue<string> dq;
//    dq = pq;
//    if (pq == dq){
//        cout << "yes\n";
//    }
//
//
//    cout << pq.dequeue() << endl;
//    cout << pq.dequeue() << endl;
//    cout << pq.dequeue() << endl;
//    cout << pq.dequeue() << endl;
//    cout << pq.dequeue() << endl;
//    cout << pq.dequeue() << endl;
//    cout << pq.dequeue() << endl;
//    cout << pq.dequeue() << endl;
//    cout << pq.dequeue() << endl;
//
//    temp.enqueue("41", 4);
//    temp.enqueue("42", 4);
//    temp.enqueue("5", 5);
//    temp.enqueue("52", 5);
//    temp.enqueue("3", 3);
//    temp.enqueue("2", 2);
//    //cout << dq.toString() << endl << pq.toString() << endl;
//
//    string x ;
//    int y;
//
//    pq.begin();
//    for (int i = 0; i < pq.size(); i++) {
//        bool b = pq.next(x, y);
//        cout << b << " " << y << " value: " << x << endl;
//    }
//
//    while (pq.next(x, y)) {
//        cout << y << " value: " << x << endl;
//    }
//    cout << y << " value: " << x << endl;
//    //cout << pq.next(x, y) << endl;
//
//    pq.begin();
//    cout <<  "peak is now " << pq.peek() << endl;
//    cout <<  "peak is now " << pq.peek() << endl;
//    cout <<  "peak is now " << pq.peek() << endl;
//    cout <<  "peak is now " << pq.peek() << endl;
//    cout <<  "peak is now " << pq.peek() << endl;
//    pq.next( x, y);
//    cout << " next returned " << x <<" " << y << endl;
//    pq.next( x, y);
//    cout << " next returned " << x <<" " << y << endl;
//    pq.next( x, y);
//    cout << " next returned " << x <<" " << y << endl;
//    pq.next( x, y);
//    cout << " next returned " << x <<" " << y << endl;
//    pq.next( x, y);
//    cout << " next returned " << x <<" " << y << endl << endl;
//
//    pq.begin();
//
//    //cout << " next returned " << x <<" " << y << endl;
//    cout << "peak before dequeue " << pq.peek() << endl;
//    cout << " dequeued "<< pq.dequeue() << endl;
//    cout <<  "peak is now " << pq.peek() << endl;
//    //pq.next( x, y);
//   // cout << " next returned " << x <<" " << y << endl;
//    cout <<  "peak before dequeue " << pq.peek() << endl;
//    cout << " dequeued "<<pq.dequeue() << endl;
//    cout <<  "peak is now " << pq.peek() << endl;
//   // pq.next( x, y);
//    //cout << " next returned " << x <<" " << y << endl;
//    cout <<  "peak before dequeue " << pq.peek() << endl;
//    cout << " dequeued "<<pq.dequeue() << endl;
//    cout <<  "peak is now " << pq.peek() << endl;
//   // pq.next( x, y);
//    //cout << " next returned " << x <<" " << y << endl;
//    cout <<  "peak before dequeue " << pq.peek() << endl;
//    cout << " dequeued "<<pq.dequeue() << endl;
//    //pq.next( x, y);
//   // cout << " next returned " << x <<" " << y << endl;
//    cout <<  "peak is now " << pq.peek() << endl;
//   // pq.next( x, y);
//   // cout << " next returned " << x <<" " << y << endl;
//    cout <<  "peak before dequeue " << pq.peek() << endl;
//    cout << " dequeued "<<pq.dequeue() << endl;
//    cout <<  "peak is now " << pq.peek() << endl;
//   // pq.next( x, y);
//    //cout << " next returned " << x <<" " << y << endl;
//    cout <<  "peak before dequeue " << pq.peek() << endl;
//    cout << " dequeued "<<pq.dequeue() << endl;
//    cout <<  "peak is now " << pq.peek() << endl;
//   // pq.next( x, y);
//    cout << " next returned " << x <<" " << y << endl;
//    cout <<  "peak before dequeue " << pq.peek() << endl;
//    cout << " dequeued "<<pq.dequeue() << endl;
//    cout <<  "peak is now " << pq.peek() << endl;
//  //  pq.next( x, y);
//   // cout << " next returned " << x <<" " << y << endl;
//    cout <<  "peak before dequeue " << pq.peek() << endl;
//    cout << " dequeued "<<pq.dequeue() << endl;
//    cout <<  "peak is now " << pq.peek() << endl;
//    //pq.next( x, y);
//    //cout << " next returned " << x <<" " << y << endl;
//    cout <<  "peak before dequeue " << pq.peek() << endl;
//    cout << " dequeued "<<pq.dequeue() << endl;
//    cout <<  "peak is now " << pq.peek() << endl;
//    pq.next( x, y);
//    cout << " next returned " << x <<" " << y << endl;
//    cout <<  "peak before dequeue " << pq.peek() << endl;
//    cout << " dequeued "<<pq.dequeue() << endl;
//    cout << " dequeued "<<pq.dequeue() << endl;
//    cout << " dequeued "<<pq.dequeue() << endl;
//    cout << " dequeued "<<pq.dequeue() << endl;
//    //pq.clear();
//    dq.clear();
//
    for (int i=0; i<10; i++){
        printf("54 ");
    }




    return 0;
}
