#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <time.h>       /* time */
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
const int height= 17;                      // El ancho
const char* clearcommand = "clear";        // Comando para limpiar la pantalla


string background[width][height];   //--- Matriz del juego

int score = 0;                      //--- Puntuacion
int lives = 3;                      //--- Vidas
int speed = 4;                      //--- Velocidad
int frecuencia = 15;                //--- Frecuencia con que salen objetos

int lap = 100;                      //--- lapso entre frames

int bytesWaiting, i;
char k;

Jugador *jugador = new Jugador();

ArrayList<Moneda*> *listaMonedas = new ArrayList<Moneda*>();
ArrayList<Obstaculo*> *listaObstaculos = new ArrayList<Obstaculo*>();
ArrayList<PowerUp*> *listaPowerUps = new ArrayList<PowerUp*>();


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
    /* initialize random seed: */
    srand (time(NULL));


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

    for(int h = 0; h < height; h++){

        for(int w = 0; w < width; w++){
            string caracter = "";
            caracter = background[w][h];

            cout << caracter;

        }
        cout << endl;


    }


}


//------- Generacion de objetos ------------
void generarObjeto(int frame){

    if(frame % frecuencia == 0){
        /* generate secret number between 1 and 10: */
        int opcion1 = rand() % 3 + 1;
        //---- Si es opcion 1 entonces es una moneda

        if(opcion1 == 1){
            Moneda *moneda = new Moneda();
            listaMonedas->append(moneda);
        }

        //---- Si es opcion 2 entonces es un obstaculo
        else if(opcion1 == 2){
            Obstaculo *obstaculo = new Obstaculo();
            listaObstaculos->append(obstaculo);

            int opcion2 = rand() % 1 + 1;

            //------ Rotulo Alto -----
            if(opcion2 == 1){
                obstaculo->setTipoObstaculo("rotuloAlto");
            }
            //------ Barricada (pinchos) ----
            else if(opcion2 == 2){
                obstaculo->setTipoObstaculo("barricada");
            }
            //------ Pared ----
            else if(opcion2 == 3){
                obstaculo->setTipoObstaculo("pared");
            }
        }

        //---- Si es opcion 3 entonces es un powerUp
        else if(opcion1 == 3){
            PowerUp *powerUp = new PowerUp();

            int opcion2 = rand() % 2 + 1;

            //------ El iman -----
            if(opcion2 == 1){
                powerUp->setTipoPoder("iman");
            }
            //------ El escudo ----
            else if(opcion2 == 2){
                powerUp->setTipoPoder("escudo");
            }


            listaPowerUps->append(powerUp);
        }

    }

}

//------- Dibujar al jugador --------
void imprimirJugador(){
    // Asignar los valores del auto del jugador
        // -------- Llantas ---------
        if(jugador->getEstado() == "normal"){
            background[jugador->getPosX()][jugador->getPosY()]        = "ʘ";
            background[jugador->getPosX() + 3][jugador->getPosY()]    = "ʘ";
            background[jugador->getPosX()][jugador->getPosY() + 3]    = "ʘ";
            background[jugador->getPosX() +3][jugador->getPosY() + 3] = "ʘ";


            background[jugador->getPosX()][jugador->getPosY() + 4]    = " ";
            background[jugador->getPosX() +3][jugador->getPosY() + 4] = " ";
            background[jugador->getPosX()][jugador->getPosY() + 1]     = " ";
            background[jugador->getPosX() + 3][jugador->getPosY() + 1] = " ";


            background[jugador->getPosX() + 1][jugador->getPosY() + 1] = "֍";
            background[jugador->getPosX() + 2][jugador->getPosY() + 1] = "֍";
            background[jugador->getPosX() + 1][jugador->getPosY() + 2] = "֍";
            background[jugador->getPosX() + 2][jugador->getPosY() + 2] = "֍";


        }
        else if(jugador->getEstado() == "agacharse"){
            background[jugador->getPosX()][jugador->getPosY()]        = " ";
            background[jugador->getPosX() + 3][jugador->getPosY()]    = " ";
            background[jugador->getPosX()][jugador->getPosY() + 3]    = " ";
            background[jugador->getPosX() +3][jugador->getPosY() + 3] = " ";

            background[jugador->getPosX() + 1][jugador->getPosY() + 1] = "֍";
            background[jugador->getPosX() + 2][jugador->getPosY() + 1] = "֍";
            background[jugador->getPosX() + 1][jugador->getPosY() + 2] = "֍";
            background[jugador->getPosX() + 2][jugador->getPosY() + 2] = "֍";
        }
        else if(jugador->getEstado() == "salto"){
            background[jugador->getPosX()][jugador->getPosY()]         = "ʘ";
            background[jugador->getPosX() + 3][jugador->getPosY()]     = "ʘ";


            background[jugador->getPosX()][jugador->getPosY() + 3]    = "ʘ";
            background[jugador->getPosX() +3][jugador->getPosY() + 3] = "ʘ";
            background[jugador->getPosX()][jugador->getPosY() + 4]    = "ʘ";
            background[jugador->getPosX() +3][jugador->getPosY() + 4] = "ʘ";

            background[jugador->getPosX() + 1][jugador->getPosY() + 2] = "֍";
            background[jugador->getPosX() + 2][jugador->getPosY() + 2] = "֍";
        }
}

//------- imprimir las monedas -------
void imprimirMonedas(int frame){

    if(frame % speed >= 0){
        for(listaMonedas->gotoStart(); !listaMonedas->atEnd(); listaMonedas->next()){

            Moneda *moneda = new Moneda();
            moneda = listaMonedas->getElement();

            //-------- Poner el objeto en su posición de la matriz.
            background[moneda->getPosX()][moneda->getPosY()] = "©";

            //-------- Aumentar una posición hacia abajo al objeto.
            moneda->setPosY(moneda->getPosY() + 1);

            //-------- Borrar el dibujo del objeto en la posición anterior.
            background[moneda->getPosX()][moneda->getPosY() - 2] = " ";

            //-------- Eliminar al objeto cuando llega al final de la matriz.
            if(moneda->getPosY() == 14){
                background[moneda->getPosX()][moneda->getPosY() - 1] = " ";
                background[moneda->getPosX()][moneda->getPosY()] = " ";
                listaMonedas->remove();
            }
        }
    }

}

//------- imprimir los obstáculos -------
void imprimirObstaculos(int frame){

    if(frame % speed >= 0){
        for(listaObstaculos->gotoStart(); !listaObstaculos->atEnd(); listaObstaculos->next()){

            Obstaculo *obstaculo = new Obstaculo();
            obstaculo = listaObstaculos->getElement();

            //-------- Poner el objeto en su posición de la matriz.
            if(obstaculo->getTipoObstaculo() == "rotuloAlto"){
                background[obstaculo->getPosX()][obstaculo->getPosY()] = "╔";
                background[obstaculo->getPosX() + 1][obstaculo->getPosY()] = "▄";
                background[obstaculo->getPosX() + 2][obstaculo->getPosY()] = "▄";
                background[obstaculo->getPosX() + 3][obstaculo->getPosY()] = "╗";
                background[obstaculo->getPosX()][obstaculo->getPosY() + 1] = "║";
                background[obstaculo->getPosX() + 3][obstaculo->getPosY() + 1] = "║";

            }
            else if(obstaculo->getTipoObstaculo() == "barricada"){
                background[obstaculo->getPosX()][obstaculo->getPosY()] = "/";
                background[obstaculo->getPosX() + 1][obstaculo->getPosY()] = "\\";
                background[obstaculo->getPosX() + 2][obstaculo->getPosY()] = "/";
                background[obstaculo->getPosX() + 3][obstaculo->getPosY()] = "\\";
            }
            else if(obstaculo->getTipoObstaculo() == "pared"){
                background[obstaculo->getPosX()][obstaculo->getPosY()] = "≤";
                background[obstaculo->getPosX() + 1][obstaculo->getPosY()] = "=";
                background[obstaculo->getPosX() + 2][obstaculo->getPosY()] = "=";
                background[obstaculo->getPosX() + 3][obstaculo->getPosY()] = "≥";
            }


            //-------- Aumentar una posición hacia abajo al objeto.
            obstaculo->setPosY(obstaculo->getPosY() + 1);

            //-------- Borrar el dibujo del objeto en la posición anterior.
            if(obstaculo->getTipoObstaculo() == "barricada" || obstaculo->getTipoObstaculo() == "pared"){
                background[obstaculo->getPosX()][obstaculo->getPosY() - 2] = " ";
                background[obstaculo->getPosX() + 1][obstaculo->getPosY() - 2] = " ";
                background[obstaculo->getPosX() + 2][obstaculo->getPosY() - 2] = " ";
                background[obstaculo->getPosX() + 3][obstaculo->getPosY() - 2] = " ";
            }
            else if(obstaculo->getTipoObstaculo() == "rotuloAlto"){
                background[obstaculo->getPosX()][obstaculo->getPosY() - 2] = " ";
                background[obstaculo->getPosX() + 1][obstaculo->getPosY() - 2] = " ";
                background[obstaculo->getPosX() + 2][obstaculo->getPosY() - 2] = " ";
                background[obstaculo->getPosX() + 3][obstaculo->getPosY() - 2] = " ";
                background[obstaculo->getPosX()][obstaculo->getPosY() - 1] = " ";
                background[obstaculo->getPosX() + 3][obstaculo->getPosY() - 1] = " ";
            }
            //-------- Eliminar al objeto cuando llega al final de la matriz.
            if(obstaculo->getPosY() == 14){

                if(obstaculo->getTipoObstaculo() == "barricada" || obstaculo->getTipoObstaculo() == "pared"){
                    background[obstaculo->getPosX()][obstaculo->getPosY() - 1] = " ";
                    background[obstaculo->getPosX() + 1][obstaculo->getPosY() - 1] = " ";
                    background[obstaculo->getPosX() + 2][obstaculo->getPosY() - 1] = " ";
                    background[obstaculo->getPosX() + 3][obstaculo->getPosY() - 1] = " ";
                    background[obstaculo->getPosX()][obstaculo->getPosY()] = " ";
                    background[obstaculo->getPosX() + 1][obstaculo->getPosY()] = " ";
                    background[obstaculo->getPosX() + 2][obstaculo->getPosY()] = " ";
                    background[obstaculo->getPosX() + 3][obstaculo->getPosY()] = " ";
                }
            }
            else if(obstaculo->getPosY() == 13){
                if(obstaculo->getTipoObstaculo() == "rotuloAlto"){
                    background[obstaculo->getPosX()][obstaculo->getPosY() - 2] = " ";
                    background[obstaculo->getPosX() + 1][obstaculo->getPosY() - 2] = " ";
                    background[obstaculo->getPosX() + 2][obstaculo->getPosY() - 2] = " ";
                    background[obstaculo->getPosX() + 3][obstaculo->getPosY() - 2] = " ";
                    background[obstaculo->getPosX()][obstaculo->getPosY() - 1] = " ";
                    background[obstaculo->getPosX() + 3][obstaculo->getPosY() - 1] = " ";

                    background[obstaculo->getPosX()][obstaculo->getPosY() - 1] = " ";
                    background[obstaculo->getPosX() + 1][obstaculo->getPosY() - 1] = " ";
                    background[obstaculo->getPosX() + 2][obstaculo->getPosY() - 1] = " ";
                    background[obstaculo->getPosX() + 3][obstaculo->getPosY() - 1] = " ";
                    background[obstaculo->getPosX()][obstaculo->getPosY()] = " ";
                    background[obstaculo->getPosX() + 3][obstaculo->getPosY()] = " ";
                }
                listaObstaculos->remove();
            }
        }
    }

}

//------- imprimir las powerUps -------
void imprimirPowerUps(int frame){

    if(frame % speed >= 0){
        for(listaPowerUps->gotoStart(); !listaPowerUps->atEnd(); listaPowerUps->next()){

            PowerUp *powerUp = new PowerUp();
            powerUp = listaPowerUps->getElement();

            //-------- Poner el objeto en su posición de la matriz.
            if(powerUp->getTipoPoder() == "escudo"){
                background[powerUp->getPosX()][powerUp->getPosY()] = "◠";
            }
            else if(powerUp->getTipoPoder() == "iman"){
                background[powerUp->getPosX()][powerUp->getPosY()] = "Ω";
            }

            //-------- Aumentar una posición hacia abajo al objeto.
            powerUp->setPosY(powerUp->getPosY() + 1);

            //-------- Borrar el dibujo del objeto en la posición anterior.
            background[powerUp->getPosX()][powerUp->getPosY() - 2] = " ";

            //-------- Eliminar al objeto cuando llega al final de la matriz.
            if(powerUp->getPosY() == 14){
                background[powerUp->getPosX()][powerUp->getPosY() - 1] = " ";
                background[powerUp->getPosX()][powerUp->getPosY()] = " ";
                listaPowerUps->remove();
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

    generarObjeto(frame);        // generar objetos

    imprimirMonedas(frame);      // imprimir monedas
    imprimirObstaculos(frame);   // imprimir obstaculos
    imprimirPowerUps(frame);     // imprimir power ups
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


// Las acciones de las teclas.
void escucharTeclado(const char k){
    if(k == 'd'|| k == 'D'){
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

            background[jugador->getPosX()][jugador->getPosY() + 4]    = " ";
            background[jugador->getPosX() +3][jugador->getPosY() + 4] = " ";
            background[jugador->getPosX()][jugador->getPosY() + 1]     = " ";
            background[jugador->getPosX() + 3][jugador->getPosY() + 1] = " ";
            jugador->setPosX(jugador->getPosX() + 5);
            jugador->setEstado("normal");
        }

    }
    else if(k == 'a' || k == 'A'){
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

            background[jugador->getPosX()][jugador->getPosY() + 4]    = " ";
            background[jugador->getPosX() +3][jugador->getPosY() + 4] = " ";
            background[jugador->getPosX()][jugador->getPosY() + 1]     = " ";
            background[jugador->getPosX() + 3][jugador->getPosY() + 1] = " ";
            jugador->setPosX(jugador->getPosX() - 5);
            jugador->setEstado("normal");
        }
    }
    else if(k == 'w' || k == 'W'){
        jugador->setEstado("salto");

    }
    else if(k == 's' || k == 'S'){
        jugador->setEstado("agacharse");
    }
    else if(k == 'q' || k == 'z' || k == 'c'){
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
            escucharTeclado(k);
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
