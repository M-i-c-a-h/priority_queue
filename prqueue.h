/**
G++ SYSTEM
COURSE: CS251 DATA STRUCTURES- FALL 2022/2023
        University of Illinois Chicago
PROJECT TITLE: PROJECT 4 -Priority Queue
STARTER CODE BY: Prof Adam Koehler
EDITED BY: MICAH OREOLUWA OLUGBAMILA
DATE:  7th NOVEMBER 2023
 * */

#pragma once

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

template<typename T>
class prqueue {
private:
    struct NODE {
        int priority;  // used to build BST
        T value;       // stored data for the p-queue
        bool dup;      // marked true when there are duplicate priorities
        NODE* parent;  // links back to parent
        NODE* link;    // links to linked list of NODES with duplicate priorities
        NODE* left;    // links to left child
        NODE* right;   // links to right child

        // Default constructor to initialize members
        NODE() : priority(0), value(T()), dup(false), parent(nullptr), link(nullptr), left(nullptr), right(nullptr) {}
    };

    NODE* root; // pointer to root node of the BST
    int sz;     // # of elements in the prqueue
    NODE* curr; // pointer to next item in prqueue (see begin and next)

    ///**************************************   private helper functions() *********************************************

    /// _recursiveFunction() is a recursive function builds a string of all the priority in the BST
    void _recursiveFunction(NODE* node, ostream& output) {

        // base case1:
        if(node == nullptr){
            return;
        }
        // traverse through left of BST
        _recursiveFunction(node->left, output);

        // append ostream output
        output << node->priority <<" value: "<< node->value << endl;

        // check node for possible duplicate
        if(node->dup){
            NODE *linkedList = node->link;      // node to traverse link
            // get linkedList priorities
            while(linkedList){
                // append ostream output
                output << linkedList->priority <<" value: "<< linkedList->value << endl;
                linkedList = linkedList->link;
            }
        }

        // traverse through right of BST
        _recursiveFunction(node->right, output);
    }
    /// clearBSS() is clears up all heap allocated nodes of a BST and sets root to nullptr
    /// function is called by public member function clear() && passes the root at first call to recursive function
    void clearBST(NODE *travelNode){

        // base case1:
        if(travelNode == nullptr){
            return;
        }

        // recursive call to left subtree
        clearBST(travelNode->left);
        travelNode->left = nullptr;
        // recursive call to right subtree
        clearBST(travelNode->right);
        travelNode->right = nullptr;

        // free all duplicates until last duplicate
        if(travelNode->dup){
            NODE *linkedList = travelNode->link;       // traverses link
            NODE *del = nullptr;        // point to next link

            while(linkedList){
                del = linkedList->link;
                delete linkedList;
                linkedList = del;
            }
        }
        // free memory of travelNode
        delete travelNode;
        travelNode = nullptr;    // set travelNode to null
    }
    /// copyBST() creates a deep copy of a BST passed into the =operator
    /// copyBST() allocates heep memory for a implicitly passed root in =operator
    /// copyBST() uses a recursive algorithm to traverse BST to_be_copied & created replica in BST_copied_into
    /// function has onr parameter, current node && no return type
    void copyBST(NODE *copyThis){
        // if BST to be copied is null, return
        if(copyThis == nullptr){
            return;
        }
        // enqueue root values of copyThis
        this->enqueue(copyThis->value, copyThis->priority);

        // if duplicates exist in copyThis, repeatedly enqueue all duplicates into thisBST
        if(copyThis->dup){
            NODE *linkedList = copyThis->link;

            while(linkedList){
                this->enqueue(linkedList->value, linkedList->priority);
                linkedList = linkedList->link;
            }
        }

        // recursive call to left subtree
        copyBST(copyThis->left);

        // recursive call to right subtree
        copyBST(copyThis->right);

    }
    /// findRightMinPriority() finds the min priority in the right subtree and returns such pointer
    /// findRightMinPriority() is a helper function for next()
    /// function returns the next inorder node for curr
    NODE* findRightMinPriority(NODE *rightNode){
        // if current rightNode has a left child, move rightNode to smaller priority
        while(rightNode->left){
            rightNode = rightNode->left;
        }
        return rightNode;
    }
    /// isEqual() is a recursive function that finds if 2 BSTs are equal by traversing each node in BST vs the other
    /// isEqual is a helper function for the =operator
    /// function returns true if 2 BST have identical value and priority
    bool isEqual(NODE *a, NODE *b) const{
        if(!a && !b){
            return true;
        }
        else if(!a){
            return false;
        }
        else if(!b){
            return false;
        }
        else if ((a->dup == b->dup) && a->value == b->value  && a->priority == b->priority){

            return isEqual(a->left, b->left) && isEqual(a->right, b->right) && isEqual(a->link, b->link);

        }
        return false;
    }
    NODE* leftMostNode(NODE* aRoot){

        if(aRoot){
            // find the lowest priority be search left subtree of BST
            while(aRoot->left){
                aRoot = aRoot->left;
            }
            return aRoot;

        }
        else{
            return nullptr;
        }

    }
    ///**************************************   private helper functions() *********************************************
public:
    /// default constructor:
    /// constructor creates an empty priority queue (i.e. root is NULL)
    prqueue() {
        root = nullptr; // set private member root to null
        sz = 0;         // set private member sz to default size 0
        curr = nullptr; // set private member curr to null
    }

    /// prqueue& operator() clears implicitly passed prqueue object and copies tree structure of other prqueue object
    /// passed by reference
    ///function return a "this*" of the newly copied BST
    prqueue& operator=(const prqueue& other) {

        // clear old BST
        this->clear();

        // recursive call to helper function
        copyBST(other.root);

        return *this; // return new heap allocated BST
    }

    /// Frees the memory associated with the priority queue but is public.
    /// O(n), where n is total number of nodes in custom BST
    /// clear() frees all heap allocated memory for BST
    void clear() {
        // if BST exist traverse inorder to free BST
        if(root){
            clearBST(root);
            root = nullptr; // set private member root to null
            sz = 0;         // set private member sz to default size 0
            curr = nullptr; // set private member curr to null
        }

    }

    /// prqueue destructor class class member function clear()
    /// Frees the memory associated with the priority queue.
    /// O(n), where n is total number of nodes in custom BST
    ~prqueue() {

        clear();
    }

    /// Inserts the value into the custom BST in the correct location based on priority.
    /// O(logn + m), where n is number of unique nodes in tree and m is number of duplicate priorities
    void enqueue(T value, int priority) {

        // create new Node to be added into BST && set newNode values && priority and other related data member
        // to parameters passed in to function or default values
        NODE *newNode = new NODE;
        newNode->value = value;         // value
        newNode->priority = priority;   // priority
        newNode->dup = false;           // if duplicate Node exists
        newNode->parent = nullptr;      // parent of Node if Node is a child
        newNode->link = nullptr;        // linkedList to duplicate Node
        newNode->left = nullptr;        // ptr to left Node
        newNode->right = nullptr;       // ptr to rightNode

        // if BST is empty, create new root
        if(root == nullptr){
            root = newNode;
        }
        else {
            // if BST has otherNodes
            // traverse BST to insert Node at correct position using following BST rule

            // create a node that travels through BST and finds correct position to insert NewNode
            NODE *travelNode = root;

            // traverse BST going left for lower priorities &&  right for higher priority && place newNode appropriately
            while(travelNode){
                // traverse left of BST for lower priorities if NewNode is of lower priority
                if(priority < travelNode->priority){
                    // if traveling node has no left, insert newNode to left of travelNode
                    if(travelNode->left == nullptr){
                        travelNode->left = newNode;
                        // set newNode's parent to travelNode
                        newNode->parent = travelNode;

                        travelNode = nullptr;   // terminate loop
                    }
                        // travel to next lower priority
                    else{
                        travelNode = travelNode->left;
                    }
                }
                    // traverse right of BST for high priorities if NewNode is of higher priority
                else if(priority > travelNode->priority){
                    // if traveling node has no right, insert newNode to right of travelNode
                    if(travelNode->right == nullptr){
                        travelNode->right = newNode;
                        // set newNode's parent to travelNode
                        newNode->parent = travelNode;

                        travelNode = nullptr;   // terminate loop
                    }
                        // travel to next higher priority
                    else{
                        travelNode = travelNode->right;
                    }
                }
                else{
                    // if previous cases were not met, then newNode is a duplicate Node
                    // create a linkedList connecting prior duplicate (if any) to newNode && set "dup" data member to true
                    NODE *linkedList = travelNode->link;

                    // if no duplicate exist
                    if(!linkedList){
                        travelNode->dup = true;
                        travelNode->link = newNode;

                        newNode->parent = travelNode;
                    }
                        // find last link in linkedList of duplicates, && insert newNode, && set newNode->dup = true;
                    else{
                        while(linkedList->link){
                            linkedList = linkedList->link;
                        }
                        linkedList->dup = true;
                        linkedList->link = newNode;

                        newNode->parent = linkedList;
                        newNode->dup = true;
                    }

                    travelNode = nullptr;   // terminate loop
                }
            }
        }

        ++sz;  // size of BST increases
    }

    /// dequeue() returns the value of the next element in the priority queue and removes
    /// the element from the priority queue.
    /// function has no input parameter and returns a templated value of priorityQueue type
    T dequeue() {

        T valueOut;    // item to be dequeued
        // call peek() to return the next inorder element

        valueOut = peek();    // value to return
        NODE *temp = root;
        NODE* myCurr = leftMostNode(temp);

        // if BST is not empty
        if(myCurr != nullptr){
            // To free memory of top priority we need to find the next inorder priority &&
            // adjust BST structure appropriately

            // CASE 1:
            // if curr has a link (duplicates),
            // shift BST to exclude curr (transfer curr ancestors and rightChild if any to temp)
            if(myCurr->dup && myCurr->link){

                if(myCurr == root){
                    // Task 1:
                    // point linkedList parent from curr to curr->parent
                    myCurr->link->parent = nullptr;
                    root = myCurr->link;
                }
                else{
                    myCurr->link->parent = myCurr->parent;
                }

                // Task 2:
                // point curr->parent to curr->link (left/right)
                if(myCurr->parent){
                    if(myCurr == myCurr->parent->left){
                        myCurr->parent->left  = myCurr->link;
                    }
                    else if(myCurr == myCurr->parent->right){
                        myCurr->parent->right  = myCurr->link;
                    }
                }
                // if no parent and delete link
                // Task 3:
                // if curr has a child, move to next link
                if(myCurr->right){
                    myCurr->link->right = myCurr->right;
                    myCurr->right->parent =  myCurr->link;
                }
                else if(myCurr->left){
                    myCurr->link->left = myCurr->left;
                    myCurr->left->parent =  myCurr->link;
                }

                // Task 4:
                // for each shift in linkedList adjust link->dup to suit appropriately
                if(!myCurr->link->link){
                    myCurr->link->dup = false;
                }

            }
            // CASE 2:
            // if curr has a right subtree only
            // shift BST to exclude curr (move right subtree up the ancestral chain)
            else if(myCurr->right){
                if(myCurr == root){
                    root = myCurr->right;
                    myCurr->right->parent = nullptr;
                }
                else{
                    myCurr->right->parent = myCurr->parent;
                }
            }
            // If curr is a leaf node, remove it from its parent.
            if(myCurr->parent) {
                if (myCurr->parent->left == myCurr) {
                    // if curr had a right child,
                    // Move child up to parents left
                    if(myCurr->right){
                        myCurr->parent->left = myCurr->right;
                    }
                    else{
                        myCurr->parent->left = nullptr;
                    }

                }
                else if (myCurr->parent->right == myCurr) {
                    // if curr had a right child,
                    // Move child up to parents left
                    if(myCurr->right){
                        myCurr->parent->right = myCurr->right;
                    }
                    else{
                        myCurr->parent->right = nullptr;
                    }
                }
            }

            // now free memory with the lowest priority(i.e. element returned by peek)
            if(myCurr != nullptr){
                delete myCurr;
                myCurr = nullptr;

                // reduce the size of BST by 1 to account for Node dequeued
                --sz;
                if(sz==0){
                    root = nullptr;
                }
            }

        }

        return valueOut; // return value of node dequeued

    }

    /// size() returns the number of elements in the priority queue
    /// function has no parameter and returns a private member sz
    int size() {

        return sz;
    }

    /// begin() sets private member curr to the first inorder node (i.e. node with top priority)
    /// function has no parameters and no return type
    /// O(logn), where n is number of unique nodes in tree
    void begin() {

        if(root == nullptr){
            return;
        }
        // set curr to the top of left subtree
        curr = root;

        // check for strictly lower leaf nodes of left subtree
        while(curr->left){
            curr = curr->left;
        }
    }

    /// next() is called after a call to begin() points curr to the first inorder node.
    /// each call to next() returns curr’s priority and value and then advance curr to the next in order node.
    /// function has 2 parameters,T value(template value), && int priority. Both parameters are passed by reference
    /// function returns false if no inorder priority is available (empty tree) && true otherwise
    bool next(T& value, int &priority) {
        // if after call to begin() curr is null, tree is empty
        if(!curr){
            return false;
        }
        else{
            value = curr->value;
            priority = curr->priority;
        }

        // If the right subtree of the node is not empty, then the next inorder node lies in the right subtree.
        // Go to the right subtree and return the node with the minimum priority in the right subtree.
        if(curr->right && !curr->dup){
            curr = findRightMinPriority(curr->right);
        }
            // If the right subtree is empty, then the next inorder node is one of its ancestors.
            // Travel up the tree using the parent pointer until you see a node which is the left child of its parent.
            // The parent of such a node is the next inorder node.
        else{
            // if curr has duplicates, move to next link
            if(curr->dup && curr->link){
                curr = curr->link;
            }
            else{
                // if curr node has equal priority as its parent
                // we must have been to the last node in the linkedList && need to advance curr back to first link
                // && repeat next algorithm on first link
                if(curr->parent && curr->parent->priority == curr->priority){
                    NODE *moveLinkBack = curr;

                    while (moveLinkBack->parent && moveLinkBack->parent->priority == curr->priority) {
                        moveLinkBack = moveLinkBack->parent;
                    }
                    curr = moveLinkBack;
                }
                // If the right subtree of the node is not empty, then the next inorder node lies in the right subtree.
                // Go to the right subtree and return the node with the minimum priority in the right subtree.
                if(curr->right && curr->dup){
                    curr = findRightMinPriority(curr->right);
                }

                else{
                    int prevPriority = curr->priority;
                    // No right subtree, find the next inorder node in the ancestor nodes
                    NODE* ancestor = curr->parent;
                    if(ancestor == root ){
                        curr = nullptr;
                        return false;
                    }
                    // found is true when a curr is the left child of its parent.
                    bool found = false;
                    while (ancestor && !found) {

                        if(curr == ancestor->left){
                            found = true;
                            curr = ancestor;
                        }
                        else{
                            // move up the ancestral chain
                            curr = ancestor;
                            ancestor = ancestor->parent;
                        }
                    }

                    if(curr && prevPriority >= curr->priority){
                        curr = nullptr;
                        return false;
                    }

                }
            }

        }
        // if a curr node exist, update parameters and return true
        if (curr) {
            return true;
        }
        else {
            return false;
        }

    }

    /// function creates a string of all BST priority and values
    /// toString() calls a private helper function _recursiveFunction() which build the string of for BST nodes in-order
    string toString() {

        string str = "";    // string of BST nodes and priority
        // create stringStream for stream output
        stringstream myStream;
        // load myStream by call to _recursiveFunction
        _recursiveFunction(root, myStream);

        str = myStream.str();       // extract the contents of the stringStream

        return str;
    }

    /// peek() returns the value of the next element in the priority queue to be dequeued
    /// function utilizes the class begin() && next() to find the next inorder priority
    T peek() {

        T valueOut;
        // set peek to root
        NODE *peek = root;

        if(peek){
            // find the lowest priority be search left subtree of BST
            while(peek->left){
                peek = peek->left;
            }
            // update valueOut
            valueOut = peek->value;
        }

        return valueOut;

    }

    /// ==operator
    /// Returns true if this priority queue as the priority queue passed in as
    /// other.  Otherwise returns false.
    bool operator==(const prqueue& other) const {

        bool valid = false;

        // if BSTs have different size they are unequal
        if(this->sz != other.sz){
            return valid;
        }
            // recursively call helper function to validate equal nodes for each traversal
        else{
            valid = isEqual(this->root, other.root);
        }

        return valid;
    }

    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void* getRoot() {
        return root;
    }
};