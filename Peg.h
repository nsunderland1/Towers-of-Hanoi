#ifndef PEG_H_
#define PEG_H_

#include <allegro.h>
#include "Disc.h"
#include "nStack.h"

//Peg class: modified stack used for Towers of Hanoi
class Peg: public nStack<Disc*> {
    private:
        int x, y; //Coordinates
    
    public:
        Peg(): nStack<Disc*>(), x(0), y(0) {}                   //Empty peg
        Peg(int x1, int y1): nStack<Disc*>(), x(x1), y(y1) {}   //Constructs at location
        Peg(int x1, int y1, int n);                             //Fill constructor
        
        void move(int newX, int newY);       //Moves peg to new location
        void display(BITMAP *&img) const;    //Displays peg and contents
};

#endif
