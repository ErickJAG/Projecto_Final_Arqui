#include <iostream>   // Standard Header
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#if HAVE_STROPTS_H
#include <stropts.h>
#endif

#include <string>
#include <stdio.h>
#include <Jugador.h>
#include <Moneda.h>
#include <Obstaculo.h>
#include <PowerUp.h>
#include <arraylist.h>

using namespace std;


//-------------- Declaración de variables importantes -----------

const int width = 40;                      // El largo
const int height= 15;                      // El ancho
const char* clearcommand = "clear";        // Comando para limpiar la pantalla


string background[width][height];   //--- Matriz del juego

int score = 0;                      //--- Puntuacion
int lives = 3;                      //--- Vidas
int speed = 1;                      //--- Velocidad

int lap = 100;                      //--- lapso entre frames

int bytesWaiting, i;
char k;
int h,w;
int x,y;

Jugador *jugador = new Jugador();

ArrayList<Moneda> *listaMonedas = new ArrayList<Moneda>();


//-------- Funcion para detectar las teclas ------
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


//------- Poner los valores iniciales del juego ----
void inicializarTerreno(void){
    Moneda *moneda = new Moneda();
    listaMonedas->append(*moneda);

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



//------- Imprimir la matriz --------
void imprimirMatriz(void){

    background[18][1] = to_string(score);
    background[18][4] = to_string(lives);
    background[18][7] = to_string(speed);

    for(h = 0; h < height; h++){

        for(w = 0; w < width; w++){
            string caracter = "";
            caracter = background[w][h];

            cout << caracter;

        }
        cout << endl;


    }


}


//------- Dibujar al jugador --------
void imprimirJugador(){
    // Asignar los valores del auto del jugador
        // -------- Llantas ---------
        background[jugador->getPosX()][jugador->getPosY()]        = "ʘ";
        background[jugador->getPosX() + 3][jugador->getPosY()]    = "ʘ";
        background[jugador->getPosX()][jugador->getPosY() + 3]    = "ʘ";
        background[jugador->getPosX() +3][jugador->getPosY() + 3] = "ʘ";

        background[jugador->getPosX() + 1][jugador->getPosY() + 1] = "֍";
        background[jugador->getPosX() + 2][jugador->getPosY() + 1] = "֍";
        background[jugador->getPosX() + 1][jugador->getPosY() + 2] = "֍";
        background[jugador->getPosX() + 2][jugador->getPosY() + 2] = "֍";
}

//------- imprimir las monedas -------
void imprimirMonedas(int frame){

    if(frame % 4 >= 0){
        for(listaMonedas->gotoStart(); !listaMonedas->atEnd(); listaMonedas->next()){

            //*moneda = listaMonedas->getElement();

            //-------- Poner el objeto en su posición de la matriz.
            background[listaMonedas->getElement().getPosX()][listaMonedas->getElement().getPosY()] = "©";

            //-------- Aumentar una posición hacia abajo al objeto.
            listaMonedas->getElement().setPosY(listaMonedas->getElement().getPosY() + 1);

            //-------- Borrar el dibujo del objeto en la posición anterior.
            background[listaMonedas->getElement().getPosX()][listaMonedas->getElement().getPosY() - 2] = " ";

            //-------- Eliminar al objeto cuando llega al final de la matriz.
            if(listaMonedas->getElement().getPosY() >= 15){
                listaMonedas->remove();
            }
        }
    }

}


//------- Limpiar la pantalla -------
void limpiarPantalla(){
    system(clearcommand);
}


//------- Actualizar el loop --------
void mainloop(int frame){

    limpiarPantalla();           // limpiar pantalla
    imprimirMatriz();            // imprimir los elementos de la interfaz de la matriz
    imprimirJugador();           // imprimir al auto del jugador
    imprimirMonedas(frame);      // imprimir monedas
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
        if(jugador->getPosX() != 11){
        //---------- limpiar posición anterior
            background[jugador->getPosX()][jugador->getPosY()]        = " ";
            background[jugador->getPosX() + 3][jugador->getPosY()]    = " ";
            background[jugador->getPosX()][jugador->getPosY() + 3]    = " ";
            background[jugador->getPosX() +3][jugador->getPosY() + 3] = " ";

            background[jugador->getPosX() + 1][jugador->getPosY() + 1] = " ";
            background[jugador->getPosX() + 2][jugador->getPosY() + 1] = " ";
            background[jugador->getPosX() + 1][jugador->getPosY() + 2] = " ";
            background[jugador->getPosX() + 2][jugador->getPosY() + 2] = " ";

            jugador->setPosX(jugador->getPosX() + 5);
        }

    }else if(k=='a'||k=='4'){
                //---------- limpiar posición anterior
        if(jugador->getPosX() != 1){
            background[jugador->getPosX()][jugador->getPosY()]        = " ";
            background[jugador->getPosX() + 3][jugador->getPosY()]    = " ";
            background[jugador->getPosX()][jugador->getPosY() + 3]    = " ";
            background[jugador->getPosX() +3][jugador->getPosY() + 3] = " ";

            background[jugador->getPosX() + 1][jugador->getPosY() + 1] = " ";
            background[jugador->getPosX() + 2][jugador->getPosY() + 1] = " ";
            background[jugador->getPosX() + 1][jugador->getPosY() + 2] = " ";
            background[jugador->getPosX() + 2][jugador->getPosY() + 2] = " ";

            jugador->setPosX(jugador->getPosX() - 5);
        }

    }else if(k=='q'||k=='z'||k=='c'){
        cout << "[+] Exit Safely [+]"<<endl;
        exit(0);
    }

}


/// Loop
void loop(){
    int frame = 0;

    while(true){
        sleepcp(lap);

        if(_kbhit())   /// If keyboard hit
        {
            cin >> k; /// Character
            reaction_on_keyboard(k);
        }

        mainloop(frame);                 /// RUn Main Loop FUnction

        cout << "< Frame : " << frame << "  | Score  : " << score << " > "<< endl; /// Print Status
        frame++;
    }

}


/// Main Trigger Function
main(){

    inicializarTerreno(); /// Dibujar los carriles y la interfaz de la derecha.
    loop();                 /// run Update Loop
}
