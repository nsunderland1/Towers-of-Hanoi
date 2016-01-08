#ifndef DISC_H_
#define DISC_H_

//Definitions for colours used in discs

#define RED makecol(255, 0, 0)
#define GREEN makecol(0, 255, 0)
#define BLUE makecol(0, 0, 255)
#define ORANGE makecol(255, 128, 0)
#define YELLOW makecol(255, 255, 0)
#define PINK makecol(255, 0, 255)
#define WHITE makecol(255, 255, 255)
#define PURPLE makecol(127, 0, 255)
#define GRAY makecol(128, 128, 128)
#define CYAN makecol(0, 255, 255)

//Disc class: represents the discs in Towers of Hanoi, can vary in size and colour
class Disc {
    protected:
        int myRadius; 
        int myColour;
        int myHeight;
    public:
        Disc(): myRadius(0), myHeight(0) {}             //"Empty" disc
        Disc(int r, int h): myRadius(r), myHeight(h) {} //Radius and height constructor
        
        void setRadius(int r) {myRadius = r;} 
        void setColour(int c) {myColour = c;} 
        void setHeight(int h) {myHeight = h;}  
        
        int radius() {return myRadius;}
        int colour() {return myColour;} 
        int height() {return myHeight;}
};

#endif
