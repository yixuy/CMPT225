#pragma once
#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

// NodeT<T> class
template<class T>
class NodeT{
    public:
        T data;
        bool isBlack;
        NodeT<T>* left;
        NodeT<T>* right;
        NodeT<T>* parent;
        NodeT(int value) : 
            data(value), left(nullptr), right(nullptr),parent(nullptr) ,isBlack(false) {};
        NodeT(int value, bool color) : 
            data(value), left(nullptr), right(nullptr),parent(nullptr) ,isBlack(color) {};
        ~ NodeT(){};
};
// Red black tree class
template<class T>
class RedBlackTree
{
    private:
        // Attribute
        NodeT<T>* root;

        // Copy helper 
        NodeT<T>* copyTree(NodeT<T>* ptr);
        // Delete helper for the whole tree
        void deleteTree(NodeT<T>* ptrRoot);
        // Size helper function
        int countTree(NodeT<T>* ptr) const;
        // Search helper function
        NodeT<T>* find(NodeT<T>* ptr, int value);
        // Search range helper function
        void findRange(NodeT<T>* ptr, vector<T> &v,int small, int large);

        // Insert helper function
        // Binary search tree insert 
        NodeT<T>* bstInsert(NodeT<T>* root, NodeT<T>* ptr);
        // after insert the helper function fix the tree to keep the property
        void fixInsertTree(NodeT<T>* ptr);

        // remove helper function
        // Find the predecessor of the delete node
        NodeT<T>* predecessor(NodeT<T>* ptr) const;
        // Fix the tree after delete
        void fixDeleteTree(NodeT<T>* ptr, NodeT<T>* parentPtr, bool isLeft);

        // left rotation
        void leftRotate(NodeT<T>* x);
        // right rotation
        void rightRotate(NodeT<T>* x);

        // dump Helper
        void dumpHelper(NodeT<T>* ptr, vector<T> &v);
    
    public: 
        // Default Constructor
        RedBlackTree();
        // Destructor
        ~RedBlackTree();
        // copy constructor
        RedBlackTree(const RedBlackTree& tree);
        //  = operator
        RedBlackTree& operator= (const RedBlackTree& tree);
        // get the size the tree
        int size() const;
        
        // Insert value in proper position in tree
        bool insert(int value);
        // Remove value in proper position in tree
        bool remove(int value);
        // Searches tree for target
        bool search(int target);
        // Search and get the vector contain these value
        vector<T> search(int start, int end);
        // Get all the values in the tree using InOdeTr traverse
        vector<T> dump();
        // Get the a pointer to the tree's root nodeT
        NodeT<T>* getRoot() const;
        // Print the tree 
        // void print(NodeT<T>* ptr);
};

// Default Constructor
// PRE:
// POST: root set to NULL
template<class T>
RedBlackTree<T>::RedBlackTree(){
	root = nullptr;
}
// Destructor
// PRE:
// POST: delete the whole tree
template<class T>
RedBlackTree<T>::~RedBlackTree(){
	deleteTree(root);
}
// Delete helper
// PARAM: the pointer to root node
// PRE:
// POST: delete the tree of the root 
template<class T>
void RedBlackTree<T>::deleteTree(NodeT<T>* ptrRoot){
    if(ptrRoot == nullptr)
        return;
    // traverse in order 
    deleteTree(ptrRoot->left);
    free(ptrRoot);
    deleteTree(ptrRoot->right);
}
// Copy constructor
// PARAM: the Redblack tree need to be copy deeply
// PRE: 
// POST: copy the tree from parameter
template<class T>
RedBlackTree<T>::RedBlackTree(const RedBlackTree& tree){
    this->root = nullptr;
    if(tree.root != nullptr){
        this->root = copyTree(tree.getRoot());
    }
}
// Copy helper
// PARAM: the Redblack tree need to be copy deeply
// PRE: the tree is not null
// POST: copy the tree from parameter
template<class T>
NodeT<T>* RedBlackTree<T>::copyTree(NodeT<T>* ptr){
    if(ptr == nullptr)
        return nullptr;

    NodeT<T>* newRoot = new NodeT<T>(ptr->data, ptr->isBlack);
    newRoot->left = copyTree(ptr->left);
    newRoot->right = copyTree(ptr->right);
    if(ptr->left != nullptr)
        newRoot->left->parent = newRoot;
    if(ptr->right != nullptr)
        newRoot->right->parent = newRoot;

    return newRoot;
}
// Get the a pointer to the tree's root nodeT
// PARAM: 
// PRE: 
// POST: the root of the tree
template<class T>
NodeT<T>* RedBlackTree<T>::getRoot() const{
    return root;
}
// overwrite = operator
// PARAM: the Redblack tree need to be copy 
// PRE: 
// POST: the calling object copy the tree from parameter
template<class T>
RedBlackTree<T>& RedBlackTree<T>::operator= (const RedBlackTree<T>& tree){
    if(this != &tree){
        deleteTree(root);
        this->root = copyTree(tree.getRoot());
    }
    return *this;
}
// the size of the tree
// PARAM: 
// PRE: 
// POST: get the size of the tree
template<class T>
int RedBlackTree<T>::size() const{
    int count = 0;
    if(root != nullptr)
        count = countTree(root);
    return count;
}
// Size helper
// PARAM: the root of the tree
// PRE: 
// POST: count the size of the tree
template<class T>
int RedBlackTree<T>::countTree(NodeT<T>* ptr) const{
    int count = 1;
    if(ptr->left !=  nullptr)
        count += countTree(ptr->left);
    if(ptr->right != nullptr)
        count += countTree(ptr->right);
    return count;
}
// Insert value in tree maintaining bst property
// PRE:
// PARAM: the root and the pointer to the node which is going to be inserted 
// POST: Node is inserted, in order, in tree
template<class T>
NodeT<T>* RedBlackTree<T>::bstInsert(NodeT<T>* root, NodeT<T>* ptr){
    if(root == nullptr)
        return ptr;
    if(root->data > ptr->data){
        root->left = bstInsert(root->left, ptr);
        root->left->parent =root;
    }else if(root->data < ptr->data){
        root->right= bstInsert(root->right, ptr); 
        root->right->parent = root;
    }
    return root;
}
// Fix the tree after inserted 
// PRE:
// PARAM: the node has been inserted 
// POST: tree still have the red black tree property
template<class T>
void RedBlackTree<T>::fixInsertTree(NodeT<T>* ptr){
    while(ptr != root && !ptr->parent->isBlack ){
        if(ptr->parent->parent->left == ptr->parent){
            NodeT<T>* unclePtr = ptr->parent->parent->right;
            // uncle nodeT is red 
            if(unclePtr != nullptr && !unclePtr->isBlack){
                unclePtr->isBlack =  true;
                ptr->parent->isBlack = true;
                ptr->parent->parent->isBlack = false;
                ptr = ptr->parent->parent;
            }
            // uncle nodeT is black or nullptr
            else{
                if(ptr == ptr->parent->right){
                    ptr = ptr->parent;
                    leftRotate(ptr);
                }
                ptr->parent->isBlack = true;
                ptr->parent->parent->isBlack = false;
                // could be better?
                rightRotate(ptr->parent->parent);
            }
        }
        else{
            NodeT<T>* unclePtr = ptr->parent->parent->left;

            // uncle nodeT is red 
            if(  unclePtr != nullptr && !unclePtr->isBlack){
                unclePtr->isBlack =  true;
                ptr->parent->isBlack = true;
                ptr->parent->parent->isBlack = false;
                ptr = ptr->parent->parent;
            }
            // uncle nodeT is black
            else{
                if(ptr == ptr->parent->left){
                    ptr = ptr->parent;
                    rightRotate(ptr);
                }
                ptr->parent->isBlack = true;
                ptr->parent->parent->isBlack = false;
                // could be better?
                leftRotate(ptr->parent->parent);
            }
        }
    }
    // after end while, set the root as black
    root->isBlack = true;
}
// Insert value in tree maintaining Red Black tree property
// PRE:
// PARAM: the value is going to be inserted 
// POST: Value is inserted, in order, in tree
template<class T>
bool RedBlackTree<T>::insert(int value){
    if(search(value))
        return false;

	NodeT<T>* newNodeT = new NodeT<T>(value);
    root = bstInsert(root, newNodeT);
    fixInsertTree(newNodeT);
    // free?
    // free(newNodeT);
    return true;
}
// Remove value in tree maintaining Red Black tree property
// PRE:
// PARAM: the value is going to be removed 
// POST: Value is removed in order
template<class T>
bool RedBlackTree<T>::remove(int value){
    NodeT<T>* temp =  find(root, value);
    if(!temp || root == nullptr)
        return false;
	NodeT<T>* deleteNode =  find(root,value);
    if(deleteNode == root && deleteNode->left == nullptr && deleteNode->right == nullptr){
        free(deleteNode);
        root = nullptr;
        return true;
    }
    NodeT<T>* deletePtr = nullptr;
    
    // deleteNode has no children or one child
    if(deleteNode->left == nullptr || deleteNode->right == nullptr)
        deletePtr =  deleteNode;
    // delete node has two children
    else
        deletePtr = predecessor(deleteNode->left);

    // identify deletePtr has left or right child
    NodeT<T>* child = nullptr;
    if(deletePtr->left != child)
        child = deletePtr->left;
    else
        child = deletePtr->right; 
    // child could not be nullptr
    if(child != nullptr)
        child->parent = deletePtr->parent; 
    
    
    // if deletePtr is root 
    bool isLeft = true;
    if(deletePtr->parent == nullptr)
        root = child;
    else{
        // attach x to y's parent
        if(deletePtr == deletePtr->parent->left)
            deletePtr->parent->left = child;
        else{
            deletePtr->parent->right= child;
            isLeft = false;
        }
    }
    if(deletePtr != deleteNode)
        deleteNode->data = deletePtr->data;
    // pass three parameter in case the child is nullptr
    if(deletePtr->isBlack)
        fixDeleteTree(child, deletePtr->parent, isLeft);
    // the order?
    free(deletePtr);
    return true;
}
// Fix the tree after deletion
// PRE:
// PARAM: two pointers to the delete Node's parent and child, 
//        and the bool variable if it is left child
// POST:  The tree maintain the red black tree after the deletion
template<class T>
void RedBlackTree<T>::fixDeleteTree(NodeT<T>* ptr, NodeT<T>* parentPtr, bool isLeft){
    while(ptr != root && (ptr == nullptr || ptr->isBlack == true)){
        if(isLeft){
            NodeT<T>* silbling = parentPtr->right;
            if(!silbling->isBlack){
                silbling->isBlack = true;
                parentPtr->isBlack = false;
                leftRotate(parentPtr);
                silbling = parentPtr->right;
            }
            if((silbling->left == nullptr || silbling->left->isBlack) && ((silbling->right == nullptr)|| silbling->right->isBlack)){
                silbling->isBlack = false;
                ptr = parentPtr;
                // the parent of ptr can not be nullpter if the ptr is the root
                if(ptr->parent == nullptr)
                    return;
                parentPtr = ptr->parent;
                isLeft = (ptr == parentPtr->left);    
            }
            else{
                if(silbling->right == nullptr || silbling->right->isBlack){
                    silbling->left->isBlack =true;
                    silbling->isBlack =false;
                    rightRotate(silbling);
                    silbling = parentPtr->right;
                }
                silbling->isBlack = parentPtr->isBlack;
                parentPtr->isBlack = true;
                silbling->right->isBlack = true;
                leftRotate(parentPtr);
                ptr = root;
            }
        }   
        else{
            NodeT<T>* silbling = parentPtr->left;
            if(!silbling->isBlack){
                silbling->isBlack = true;
                parentPtr->isBlack = false;
                rightRotate(parentPtr);
                silbling = parentPtr->left;
            }
            if((silbling->right == nullptr|| silbling->right->isBlack)&&(silbling->left == nullptr || silbling->left->isBlack)){
                silbling->isBlack = false;
                ptr = parentPtr;
                // the parent of ptr can not be nullpter if the ptr is the root
                if(ptr->parent == nullptr)
                    return;
                parentPtr = ptr->parent;
                isLeft = (ptr == parentPtr->left);
            }
            else{
                if(silbling->left == nullptr || silbling->left->isBlack){

                    silbling->right->isBlack =true;
                    silbling->isBlack =false;
                    leftRotate(silbling);
                    silbling = parentPtr->left;
              
                }
                
                silbling->isBlack = parentPtr->isBlack;
                parentPtr->isBlack = true;
                silbling->left->isBlack = true;
                rightRotate(parentPtr);
                ptr = root;
            
            }
        } 
    }
    ptr->isBlack = true;
}
// Find the predecessor(right most of left subtree)
// PRE:
// PARAM: the pointer to node to be deleted
// POST: the pointe to the predecessor
template<class T>
NodeT<T>* RedBlackTree<T>::predecessor(NodeT<T>* ptr) const{
    NodeT<T>* temp = ptr;
    while(temp->right != nullptr)
        temp = temp->right;
    return temp;
}
// Find the value if it is in the tree
// PRE:
// PARAM: the root of tree, the value is going to be searched
// POST: return the pointer to the node if it is found
template<class T>
NodeT<T>* RedBlackTree<T>::find(NodeT<T>* ptr,int value){
    if(ptr == nullptr)
        return nullptr;
    if(ptr->data < value)
        return find(ptr->right, value);
    else if(ptr->data == value)
        return ptr;
    else
        return find(ptr->left, value);    
}
// Searches tree for target
// PRE:
// PARAM: target = value to be found
// POST: Returns true iff target is in tree
template<class T>
bool RedBlackTree<T>::search(int target){
    return (find(root, target) != nullptr);
}
// Searches tree for target
// PRE:
// PARAM: the range of start and end
// POST: Returns true iff target is in tree
template<class T>
vector<T> RedBlackTree<T>::search(int start, int end){
    vector<T> v;
    int small = start < end ? start: end;
    int large = start < end ? end : start;
    findRange(root, v, small, large);
    return v;  
}
// Searches tree for range of target
// PRE:
// PARAM: the root of the tree, a vector to store the element in the range
//        the small value and large value
// POST: Returns true iff target is in tree
template<class T>
void RedBlackTree<T>::findRange(NodeT<T>* ptr, vector<T> &v,int small, int large){
    if(ptr ==  nullptr)
        return;
    if(ptr->data < small)
        findRange(ptr->right, v, small, large);
    if(ptr->data >= small && ptr->data <= large){
        findRange(ptr->left, v,  small, large);
        v.push_back(ptr->data);
        findRange(ptr->right,v,small, large);
    }  
    if(ptr->data > large)
        findRange(ptr->left,v ,small, large);
}
// dump all entity in the vector
// PRE:
// PARAM: 
// POST: Returns the vector contains all element in the tree
template<class T>
vector<T> RedBlackTree<T>::dump(){
    vector<T> v;
    if(nullptr ==  root)
        return v;
    dumpHelper(root, v);
    return v;    
 }
// dump Helper
// PRE:
// PARAM: the root, the vetor store the  element in the tree
// POST:  
template<class T>
void RedBlackTree<T>::dumpHelper(NodeT<T>* ptr, vector<T> &v){
    if(ptr->left != nullptr)
        dumpHelper(ptr->left, v);
    v.push_back(ptr->data);
    if(ptr->right != nullptr)
        dumpHelper(ptr->right, v);
}
// Prints contents of tree pre, in, post order
// PRE:
// POST: Prints contents of tree three times:
//       pre order, in order and post order
// template<class T>
// void RedBlackTree<T>::print(NodeT<T>* ptr){
//     if(ptr ==  nullptr)
//         return ;
//     if(ptr->left != nullptr)
//         print(ptr->left);
//     if(ptr->isBlack)
//         cout<<ptr->data<<": Black" <<endl;
//     else
//         cout<<ptr->data<<": RED"<<endl;
//     if(ptr->right != nullptr)
//         print(ptr->right);
// }

// left Rotate
// PRE:
// PARAM: the pointer to node need to be rotated to keep the property
// POST: 
template<class T>
void RedBlackTree<T>::leftRotate(NodeT<T>* x){
    NodeT<T>* temp = x->right;
    x->right = temp->left;
    if(x->right != nullptr){
        temp->left->parent = x;
    }

    temp->parent = x->parent;
    if(x->parent == nullptr)
        root = temp;
    else if( x->parent->left == x)
        x->parent->left = temp;
    else 
        x->parent->right = temp;

    temp->left = x;
    x->parent = temp; 
}
// right rotate
// PRE:
// PARAM: the pointer to node need to be rotated to keep the property
// POST: 
template<class T>
void RedBlackTree<T>::rightRotate(NodeT<T>* x){
    NodeT<T>* temp = x->left;

    x->left = temp->right;
    if(x->left != nullptr){
        temp->right->parent = x;
    }

    temp->parent = x->parent;
    if(x->parent == nullptr)
        root = temp;
    else if( x->parent->left == x)
        x->parent->left = temp;
    else 
        x->parent->right = temp;

    temp->right = x;
    x->parent = temp;    
}