/*  Nicholas Sunderland
  
    ICS4U - Period 2
    November 20 2014

    This program runs a recursive Towers of Hanoi simulation, using user input
    to determine the number of discs and the game speed, and graphically 
    displaying the entire process to the user.
*/

#include <allegro.h>
#include <alfont.h>

#include "apstring.h"
#include "Peg.h"

#define SCREEN_WIDTH 1240
#define SCREEN_HEIGHT 640

float num_input(const apstring &);
void moveDisc(Peg &, Peg &);
void moveTower(int, Peg &, Peg &, Peg &);
void display(Peg &, Peg &, Peg &, int);

volatile int speed_counter = 0; //Used for delays between moves

void inc_speed_counter() {speed_counter++;}
END_OF_FUNCTION(inc_speed_counter);

//Callbacks for running program in the background
void switch_out_callback() {} 
void switch_in_callback() {} 

bool close_button_pressed = false; //Flag for pressing of close button

//Toggles close button flag
void close_button_handler() {
    simulate_keypress(1);        //Simulated keypress for breaking out of readkey()
    close_button_pressed = true;
}

int main(int argc, char **argv) {  
    //Setting up Allegro
    allegro_init();
    alfont_init();
    install_keyboard();
    install_timer();
    
    //Setting up graphics
    set_color_depth(desktop_color_depth());
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_WIDTH, SCREEN_HEIGHT, 0 , 0);
    
    //Allowing program to run in the background
    set_display_switch_mode(SWITCH_BACKGROUND);
    set_display_switch_callback(SWITCH_OUT, switch_out_callback);
    set_display_switch_callback(SWITCH_IN, switch_in_callback);
    
    //Setting up close button handling
    set_close_button_callback(close_button_handler);
    
    LOCK_VARIABLE(speed_counter);
    LOCK_FUNCTION(inc_speed_counter);
    
    int discNum = 0; //Number of discs to be used
    
    //Receiving user input for number of discs
    while (discNum < 1)
        discNum = int(num_input("Enter the number of discs (1 minimum): "));
    
    float speed = 0; //Delay between each move
    
    //Receiving user input for game speed
    while (speed < 0.001) 
        speed = num_input("Enter the number of seconds per move (0.001 minimum): ");
    
    //Setting up timer based on game speed
    install_int_ex(inc_speed_counter, MSEC_TO_TIMER(speed*1000));
    
    //Creating towers, with the left one starting out filled
    Peg left(200, 500, discNum), centre(600, 500), right(1000, 500);  
    
    //Beginning Towers of Hanoi simulation
    moveTower(discNum, left, right, centre);
    
    //Exiting when user hits Esc or the close button
    while (!key[KEY_ESC] && !close_button_pressed);
    return 0;
}
END_OF_MAIN();

//Receives a number as user input
float num_input(const apstring &prompt) {
    int input = 0; //Key pressed by user
    BITMAP*buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    apstring str;  //Stores all user input
    
    //Setting up font
    ALFONT_FONT *myFont = alfont_load_font("calibri.ttf");
    alfont_set_font_size(myFont, 20);
    
    //Ending when user hits enter
    while (input != 13 || str.length() < 1) {
        //Displaying prompt and user input
        clear_bitmap(buffer); 
        alfont_textprintf_ex(buffer, myFont, 0, 0, WHITE, -1, (prompt+str).c_str());
        blit(buffer, screen,0,0,0,0, SCREEN_WIDTH, SCREEN_HEIGHT);
        
        //Converting key on key buffer to ASCII character
        clear_keybuf();
        input = readkey() & 255;
        
        //Exiting if user chooses to do so
        if (input == 27 || close_button_pressed) {
            destroy_bitmap(buffer);
            alfont_destroy_font(myFont);
            exit(EXIT_SUCCESS);
        }
        //Adding valid number input to str
        else if (input >= '0' && input <= '9' || input == '.' && str.find('.') == npos)
            str += input;
        //Handling backspace press
        else if (input == 8 && str.length() > 0)
            str = str.substr(0, str.length() - 1);           
    }
    destroy_bitmap(buffer);
    alfont_destroy_font(myFont);
    
    return atof(str.c_str());
}

//Moving a disc from one peg to another
void moveDisc(Peg &src, Peg &dst) {
    dst.push(src.peek());
    src.pop();    
}

//Recursive Towers of Hanoi function
void moveTower(int n, Peg &src, Peg &dst, Peg &tmp) {
    static int count = 0; //Keeps track of the number of moves
    
    //Displaying all pegs and move count on screen
    display(src, dst, tmp, count);
    
    if (n > 0) {
        //Moving all discs above bottom disc
        moveTower(n-1, src, tmp, dst);
        
        //Moving the (formerly) bottom disc
        moveDisc(src, dst);
        
        count++;
        speed_counter = 0; //Resetting speed counter for move delay
        
        //Delaying next move and handling exit if needed
        while (speed_counter < 1) {
            if (key[KEY_ESC] || close_button_pressed) {
                //Clearing all pegs from memory before exit
                src.clear();
                dst.clear();
                tmp.clear();
                exit(EXIT_SUCCESS);
            }
        }   
        
        //Moving all discs back on top of bottom disc
        moveTower(n-1, tmp, dst, src);    
    }
}

//Displays all pegs and move count on screen
void display(Peg &p1, Peg &p2, Peg &p3, int moves) {
    BITMAP *background = load_bitmap("background.bmp", NULL);
    
    //Adding pegs to background bitmap
    p1.display(background);
    p2.display(background);
    p3.display(background);
    
    //Setting up font for move count
    ALFONT_FONT *myFont = alfont_load_font("calibri.ttf");
    alfont_set_font_size(myFont, 40);
    
    //Setting up move count text
    char temp[10];
    sprintf(temp, "%d", moves);
    apstring moveTxt = apstring("Moves: ") + temp;
    
    //Setting location of move count text to centre of screen
    int x = SCREEN_WIDTH/2 - (alfont_text_length(myFont, moveTxt.c_str())/2);
    
    //Writing move count to background bitmap
    alfont_textprintf_ex(background, myFont, x, SCREEN_HEIGHT - 40, WHITE, -1, moveTxt.c_str());
    
    //Displaying everything
    blit(background, screen, 0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    alfont_destroy_font(myFont);
    destroy_bitmap(background);
}
