#include <iostream>   // Standard Header
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#if HAVE_STROPTS_H
#include <stropts.h>
#endif

#include <stdio.h>

using namespace std;


/*
__author__ = suraj singh bisht
__email__  = surajsinghbisht054@gmail.com
__Github__ = https://github.com/surajsinghbisht054

*/


///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
///                       Testing Configuration
///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
///
/// Operating System            :   Linux 4.4.0-109-generic #132-Ubuntu, x86_64 GNU/Linux
/// Editor   : Code::Blocks 13.12
/// Compiler          : g++ (Ubuntu 5.4.0-6ubuntu1~16.04.5) 5.4.0 20160609
/// Blog    : www.bitforestinfo.com
///
///++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


/// ++++++++++++++++++++ [ Configuration Panel] +++++++++++++++++++++++++++++++++{

/// Global Dimension
const int width = 40;                      // Boundary Width
const int height= 15;                      // Boundary Height
const char block='#';                      // Block Char
const char* clearcommand = "clear";        // Teminal Command (Linux: clear | Windows : clr )


/// global arrays for Data Records
string background[width][height];   /// Background Array
int snake[50][2];               /// Maximum Snake Length
int food[2]={0,0};              /// Snake Food Array
int score = 0;                  /// Score
int snakelen = 3;               /// Snake Starting Length
int snakemovementspeedx = 1;    /// Horizontal Speed
int snakemovementspeedy = 1;    /// Vertical Speed
int lap = 100;                    /// Waiting Time Betweeen Frames

/// ++++++++++++++++++++ [ Configuration Panel] END +++++++++++++++++++++++++++++++++}




/// Declearing Global Temporary Variable To Save Memory
int bytesWaiting, i;
int px,py,nx, ny;
char k;
int h,w;
int x,y;
int movementx=snakemovementspeedx;                /// Snake Movement
int movementy=0;                /// Snake Movement


/*
Reference Links:
        https://www.quora.com/With-which-function-can-I-replace-kbhit-in-C++-because-the-header-conio-h-doesnt-exist-in-linux

Ubuntu Users:
    sudo apt-get install libncurses5-dev libncursesw5-dev
*/


///
/// http://www.flipcode.com/archives/_kbhit_for_Linux.shtml
/// Check KeyBoard Pressed Or Not
int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    //int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}




/// Initialise background borders Onto Array
void inicializarTerreno(void){
    // Inicializar la matriz
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            background[i][j] = " ";
        }
    }

    // Asignar las columnas
    for(i = 0; i < height; i++){
        background[0][i] = "║";
        background[5][i] = "║";
        background[10][i] = "║";
        background[15][i] = "║";

    }

    // Inicializar el texto de la derecha
        background[18][0] = "S";
        background[19][0] = "C";
        background[20][0] = "O";
        background[21][0] = "R";
        background[22][0] = "E";

        background[18][3] = "L";
        background[19][3] = "I";
        background[20][3] = "V";
        background[21][3] = "E";
        background[22][3] = "S";

        background[18][6] = "S";
        background[19][6] = "P";
        background[20][6] = "E";
        background[21][6] = "E";
        background[22][6] = "D";

        background[18][9] = "P";
        background[19][9] = "O";
        background[20][9] = "W";
        background[21][9] = "E";
        background[22][9] = "R";
        background[23][9] = "S";
}




/// Print Array Frame
void imprimirMatriz(void){

    for(h = 0; h < height; h++){

        for(w = 0; w < width; w++){
            string caracter = "";
            caracter = background[w][h];

            cout << caracter;

        }
        cout << endl;


    }


}


/// Clear Background
void clear_background(void){
    system(clearcommand);
}


/// Update loop
void mainloop(void){

    clear_background();          // clear background
    imprimirMatriz();         // Print Frame

}



/// Waiting Function
void sleepcp(int milliseconds) // Cross-platform sleep function
{
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end)
    {
    }
}


/// Reaction On Press Button Of Keyboard
void reaction_on_keyboard(const char k){
    if(k=='d'||k=='6'){
        // Right Turn
        movementx = snakemovementspeedx;
        movementy = 0;


    }else if(k=='a'||k=='4'){
        // Left Turn
        movementx = -snakemovementspeedx;
        movementy = 0;

    }else if(k=='w'||k=='8'){

        // Turn UP
        movementx = 0;
        movementy = -snakemovementspeedy;

    }else if(k=='s'||k=='2'){
        // Turn Down
        movementx = 0;
        movementy = snakemovementspeedy;


    }else if(k=='q'||k=='z'||k=='c'){
        cout << "[+] Exit Safely [+]"<<endl;
        exit(0);
    }

}


/// Loop
void loop(void){
    int frame=0;
    x=0;
    y=0;

    while(x<500){
        sleepcp(lap);

        if(_kbhit())   /// If keyboard hit
        {
            cin >> k; /// Character
            reaction_on_keyboard(k);
        }

        mainloop();                 /// RUn Main Loop FUnction

        cout << "< Frame : " << frame << "  | Score  : " << score << " > "<< endl; /// Print Status
        frame++;
    }

}


/// Main Trigger Function
main(){

    inicializarTerreno(); /// Dibujar los carriles y la interfaz de la derecha.
    loop();                 /// run Update Loop
}
