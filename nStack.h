#ifndef NSTACK_H
#define NSTACK_H

#include <cstdlib>
#include <stdexcept>
#include <iostream>

//NODE: used to build linked list 
template <typename type>
struct NODE {
    type data;  //Data stored by node
    NODE *next; //Pointer to following node
};

//nStack: template stack type
template <typename type>
class nStack {
    protected:
        NODE<type> *head;  //Top item
        int mySize;        //Current size
    public: 
        nStack(): head(NULL), mySize(0) {} //Creates empty stack
        nStack(const nStack &source);  //Copy constructor
        ~nStack();
        
        //Accessors
        int size() const {return mySize;} //Returns current size
        const type & peek() const;         //Reads data from top
        
        //Mutators
        bool pop();                     //Removes top item
        bool push(const type &newdata); //Adds item to top
        void clear();                   //Empties stack
        
        //Assignment operator
        const nStack & operator = (const nStack &rhs);
        
        //Comparison operators
        bool operator == (const nStack &rhs) const;
        bool operator != (const nStack &rhs) const {return !(*this == rhs);}
};

/***Due to how C++ handles template classes (they cannot be compiled in
separate .cpp files) the full function definition is included here.***/

//Copy constructor
template <typename type>
nStack<type>::nStack(const nStack<type> &source) {
    if (source.mySize == 0) {
        head = NULL;
        mySize = 0;    
    }
    else {
        head = new NODE<type>;
        mySize = source.mySize;
        
        NODE<type> *a, *b;
        
        for (a = head, b = source.head; b; a = a->next, b = b->next) {
            a->data = b->data; 
            
            if (b->next)
                a->next = new NODE<type>;   
            else
                a->next = NULL;
        }
    }         
}

//Destructor: runs through stack and deletes all nodes
template <typename type>
nStack<type>::~nStack() { 
    while (head) {
        NODE<type> *nextnode = head->next;
        delete head;   
        head = nextnode;  
    }
}

//Reads data from top of stack
template <typename type>
const type & nStack<type>::peek() const {
    if (!head)
        throw std::runtime_error("Reading from empty stack");
        
    return head->data;      
}

//Removes top item of stack
template <typename type>
bool nStack<type>::pop() {
    if (!head)
        return false;
	
    NODE<type> *newhead = head->next; 
    delete head;
    head = newhead; 
    mySize--; 
    
    return true;
}

//Adds item to top of stack
template <typename type>
bool nStack<type>::push(const type &newdata) {
    NODE<type> *newhead;
    
    try {    
        newhead = new NODE<type>;
    }
    catch(std::bad_alloc &) {
        return false;    
    }
    
    newhead->data = newdata;
    newhead->next = head;   
    head = newhead; 
    mySize++;
    
    return true;
}

//Empties stack
template <typename type>
void nStack<type>::clear() {
    while (head) {
        NODE<type> *nextnode = head->next;
        delete head;   
        head = nextnode;  
    }     
    
    mySize = 0;
}

//Assignment operator
template <typename type>
const nStack<type> & nStack<type>::operator = (const nStack<type> &rhs) {
    if (this != &rhs) {
        this->clear();

        if (rhs.mySize > 0) {
            head = new NODE<type>;
            mySize = rhs.mySize;
        
            NODE<type> *a, *b;
        
            for (a = head, b = rhs.head; b; a = a->next, b = b->next) {
                a->data = b->data; 
            
                if (b->next)
                    a->next = new NODE<type>;   
                else
                    a->next = NULL;
            }
        }  
    }
    
    return *this;
}

//Returns true if all data from both stacks match
template <typename type>
bool nStack<type>::operator == (const nStack<type> &rhs) const {
    if (this != &rhs) {
        if (mySize != rhs.mySize)
            return false;
        
        NODE<type> *a, *b;
    
        for (a = head, b = rhs.head; a && b; a = a->next, b = b->next)
            if (a->data != b->data)
                return false;
    }
            
    return true;
}

#endif
