#include "Peg.h"

//FILL CONSTRUCTOR
//Constructs peg at (x1, y1), and fills with n discs 
Peg::Peg(int x1, int y1, int n) {
    head = NULL;
    mySize = 0;
    
    x = x1;
    y = y1;
    
    //Colour selection to loop through
    int colours[] = {RED, GREEN, BLUE, ORANGE, YELLOW, 
                     PINK, WHITE, PURPLE, GRAY, CYAN};
    
    //Pushing discs of decreasing size and cycling colours
    for (int i = 0; i < n; i++) {
        Disc *newDisc = new Disc(10*n - i*10, 30);
        newDisc->setColour(colours[i%10]);
        push(newDisc);
    }
}

//MOVE FUNCTION
//Sets new values for location of peg
void Peg::move(int newX, int newY) {
    x = newX;
    y = newY;
}

//DISPLAY FUNCTION
//Displays peg and its contents on parameter bitmap
void Peg::display(BITMAP *&img) const {
    if (!head)
        return;
    
    int radius, height = head->data->height(); 
    int vPos = y - (size() - 1) * height;       //"Vertical position"
    
    //Displying each disc starting from the top, and then moving downwards
    for (NODE<Disc*> *itr = head; itr; itr = itr->next) {
        radius = itr->data->radius();
        
        rectfill(img, x - radius, vPos, x + radius, vPos + height, itr->data->colour());  
        vPos += height;
    } 
}
