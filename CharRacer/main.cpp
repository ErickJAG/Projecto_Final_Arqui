#include <ncurses.h>
#include <curses.h>

using namespace std;

#include <unistd.h>  /* only for sleep() */

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <time.h>       /* time */
#if HAVE_STROPTS_H
#include <stropts.h>
#endif


#include <locale.h>
#include <string>
#include <stdio.h>
#include "/home/michael/Documentos/Carpeta de proyectos en c++/prueba2/include/Jugador.h"
#include "/home/michael/Documentos/Carpeta de proyectos en c++/prueba2/include/Moneda.h"
#include "/home/michael/Documentos/Carpeta de proyectos en c++/prueba2/include/Obstaculo.h"
#include "/home/michael/Documentos/Carpeta de proyectos en c++/prueba2/include/PowerUp.h"
#include "/home/michael/Documentos/Carpeta de proyectos en c++/prueba2/include/arraylist.h"

using namespace std;


//-------------- Declaración de variables importantes -----------

const int width  = 40;                      // El largo
const int height = 26;                      // El ancho


string background[width][height];   //--- Matriz del juego

int score = 0;                      //--- Puntuacion
int lives = 3;                      //--- Vidas
int speed = 4;                      //--- Velocidad
int frecuencia = 15;                //--- Frecuencia con que salen objetos

int lap = 100;                      //--- lapso entre frames

int bytesWaiting, i;
char k;

bool escuadoActivado = false;
bool imanActivado = false;
int turnosIman = 4;
int colorCode = 3;


//-------------- booleans para condicionales ---------
bool seguirJugando = true;
bool juegoPausado = false;
bool juegoPerdido = false;

Jugador *jugador = new Jugador();

ArrayList<Moneda*> *listaMonedas = new ArrayList<Moneda*>();
ArrayList<Obstaculo*> *listaObstaculos = new ArrayList<Obstaculo*>();
ArrayList<PowerUp*> *listaPowerUps = new ArrayList<PowerUp*>();

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
void imprimirMatriz(WINDOW *pantallaJuego){

    background[18][1] = to_string(score);
    background[18][4] = to_string(lives);
    background[18][7] = to_string(speed);

    if(escuadoActivado){
        background[18][10] = "∩";
    }
    else{
        background[18][10] = " ";   
    }


    if(imanActivado){
        background[19][10] = "Ω";
    }
    else{
        background[19][10] = " ";
    }

    for(int h = 0; h < height; h++){

        for(int w = 0; w < width; w++){
            string caracter = "";
            caracter = background[w][h];

            if(caracter == "©"){
                colorCode = 3; // verde
            }

            else if(caracter == "∩" or caracter == "Ω"){
                colorCode = 4; // azul
            }

            else if(caracter == "/" or caracter == "\\"){
                colorCode = 1; // rojo
            }

            else if(caracter == "|" or caracter == "╔" or caracter == "╗" or caracter == "▄"){
                colorCode = 1; // rojo
            }   

            else if(caracter == "=" or caracter == "≤" or caracter == "≥"){
                colorCode = 1; // rojo
            }

            else{
                colorCode = 7; // blanco
            }


            attron(COLOR_PAIR(colorCode));
            mvprintw(h, w, caracter.c_str());
            //wattroff(pantallaJuego, COLOR_PAIR(1));

        }

    }

    mvprintw(1, 18, to_string(score).c_str());


    //refresh();
    refresh();
}


//------- Generacion de objetos ------------
void generarObjeto(int frame){

    if(frame % frecuencia == 0){
        /* generate secret number between 1 and 10: */
        int opcion1 = rand() % 10 + 1;
        //---- Si es opcion 1 entonces es una moneda

        if(opcion1 >= 1 and opcion1 <= 3){
            Moneda *moneda = new Moneda();
            listaMonedas->append(moneda);
        }

        //---- Si es opcion 2 entonces es un obstaculo
        else if(opcion1 >= 4 and opcion1 <= 8){
            Obstaculo *obstaculo = new Obstaculo();
            listaObstaculos->append(obstaculo);

            int opcion2 = rand() % 3 + 1;

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
        else if(opcion1 >= 9){
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
            background[jugador->getPosX()][jugador->getPosY()]        = "֍";
            background[jugador->getPosX() + 3][jugador->getPosY()]    = "֍";
            background[jugador->getPosX()][jugador->getPosY() + 3]    = "֍";
            background[jugador->getPosX() +3][jugador->getPosY() + 3] = "֍";


            background[jugador->getPosX()][jugador->getPosY() + 4]    = " ";
            background[jugador->getPosX() +3][jugador->getPosY() + 4] = " ";
            background[jugador->getPosX()][jugador->getPosY() + 1]     = " ";
            background[jugador->getPosX() + 3][jugador->getPosY() + 1] = " ";


            background[jugador->getPosX() + 1][jugador->getPosY() + 1] = "ʘ";
            background[jugador->getPosX() + 2][jugador->getPosY() + 1] = "ʘ";
            background[jugador->getPosX() + 1][jugador->getPosY() + 2] = "ʘ";
            background[jugador->getPosX() + 2][jugador->getPosY() + 2] = "ʘ";


        }
        else if(jugador->getEstado() == "agacharse"){
            background[jugador->getPosX()][jugador->getPosY()]        = " ";
            background[jugador->getPosX()][jugador->getPosY() + 3]    = " ";
            background[jugador->getPosX() + 3][jugador->getPosY()]    = " ";
            background[jugador->getPosX() +3][jugador->getPosY() + 3] = " ";

            background[jugador->getPosX() + 1][jugador->getPosY() + 1] = "ʘ";
            background[jugador->getPosX() + 2][jugador->getPosY() + 1] = "ʘ";
            background[jugador->getPosX() + 1][jugador->getPosY() + 2] = "ʘ";
            background[jugador->getPosX() + 2][jugador->getPosY() + 2] = "ʘ";

            background[jugador->getPosX()][jugador->getPosY() + 4] = " ";
            background[jugador->getPosX() + 3][jugador->getPosY() + 4] = " ";
        }
        else if(jugador->getEstado() == "salto"){
            background[jugador->getPosX()][jugador->getPosY()]         = "֍";
            background[jugador->getPosX() + 3][jugador->getPosY()]     = "֍";


            background[jugador->getPosX()][jugador->getPosY() + 3]    = "֍";
            background[jugador->getPosX() +3][jugador->getPosY() + 3] = "֍";
            background[jugador->getPosX()][jugador->getPosY() + 4]    = "֍";
            background[jugador->getPosX() +3][jugador->getPosY() + 4] = "֍";

            background[jugador->getPosX() + 1][jugador->getPosY() + 2] = "ʘ";
            background[jugador->getPosX() + 2][jugador->getPosY() + 2] = "ʘ";
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


            if(imanActivado){
                if(moneda->getPosY() == jugador->getPosY()){
                    background[moneda->getPosX()][moneda->getPosY() - 1] = " ";
                    background[moneda->getPosX()][moneda->getPosY()] = " ";
                    listaMonedas->remove();
                    score += 1;
                    turnosIman -= 1;

                    system("play coin1.wav >>/dev/null 2>>/dev/null");

                    if(score % 10 == 0){
                        speed += 1;
                        lap -= 4;
                    }

                    if(turnosIman <= 0){
                        imanActivado = false;
                    }
                }
            }

            else{
                if(moneda->getPosY() == jugador->getPosY() and moneda->getPosX() == jugador->getPosX()){
                    background[moneda->getPosX()][moneda->getPosY() - 1] = " ";
                    background[moneda->getPosX()][moneda->getPosY()] = " ";
                    listaMonedas->remove();
                    score += 1;

                    system("play coin1.wav >>/dev/null 2>>/dev/null");

                    if(score % 10 == 0){
                        speed += 1;
                        lap -= 4;
                    }
                }
            }


            //-------- Eliminar al objeto cuando llega al final de la matriz.
            if(moneda->getPosY() == height - 1){
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
                background[obstaculo->getPosX()][obstaculo->getPosY() + 1] = "|";
                background[obstaculo->getPosX() + 3][obstaculo->getPosY() + 1] = "|";

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
            if(obstaculo->getTipoObstaculo() == "pared"){
                background[obstaculo->getPosX()][obstaculo->getPosY() - 2] = " ";
                background[obstaculo->getPosX() + 1][obstaculo->getPosY() - 2] = " ";
                background[obstaculo->getPosX() + 2][obstaculo->getPosY() - 2] = " ";
                background[obstaculo->getPosX() + 3][obstaculo->getPosY() - 2] = " ";
           

                //------------- choque escudo --------------
                if(escuadoActivado){
                    if(obstaculo->getPosY() == jugador->getPosY() - 1 and obstaculo->getPosX() == jugador->getPosX()){
                        background[obstaculo->getPosX()][obstaculo->getPosY() - 1] = " ";
                        background[obstaculo->getPosX() + 1][obstaculo->getPosY() - 1] = " ";
                        background[obstaculo->getPosX() + 2][obstaculo->getPosY() - 1] = " ";
                        background[obstaculo->getPosX() + 3][obstaculo->getPosY() - 1] = " ";
                        background[obstaculo->getPosX()][obstaculo->getPosY()] = " ";
                        background[obstaculo->getPosX() + 1][obstaculo->getPosY()] = " ";
                        background[obstaculo->getPosX() + 2][obstaculo->getPosY()] = " ";
                        background[obstaculo->getPosX() + 3][obstaculo->getPosY()] = " ";
           
                        listaObstaculos->remove();

                        escuadoActivado = false;

                        system("play crashSound.wav >>/dev/null 2>>/dev/null");
                    }
                }
                //------------- choque normal --------------
                if(obstaculo->getPosY() == jugador->getPosY() and obstaculo->getPosX() == jugador->getPosX()){
                    background[obstaculo->getPosX()][obstaculo->getPosY() - 1] = " ";
                    background[obstaculo->getPosX() + 1][obstaculo->getPosY() - 1] = " ";
                    background[obstaculo->getPosX() + 2][obstaculo->getPosY() - 1] = " ";
                    background[obstaculo->getPosX() + 3][obstaculo->getPosY() - 1] = " ";
                    background[obstaculo->getPosX()][obstaculo->getPosY()] = " ";
                    background[obstaculo->getPosX() + 1][obstaculo->getPosY()] = " ";
                    background[obstaculo->getPosX() + 2][obstaculo->getPosY()] = " ";
                    background[obstaculo->getPosX() + 3][obstaculo->getPosY()] = " ";
           
                    lives -= 1;
                    listaObstaculos->remove();

                    system("play Crash.wav >>/dev/null 2>>/dev/null");

                    if(lives <= 0){
                        background[18][4] = "0";
                        juegoPerdido = true;
                    }
                }
            }
            else if(obstaculo->getTipoObstaculo() == "barricada"){
                background[obstaculo->getPosX()][obstaculo->getPosY() - 2] = " ";
                background[obstaculo->getPosX() + 1][obstaculo->getPosY() - 2] = " ";
                background[obstaculo->getPosX() + 2][obstaculo->getPosY() - 2] = " ";
                background[obstaculo->getPosX() + 3][obstaculo->getPosY() - 2] = " ";
           
                if(jugador->getEstado() != "salto"){


                    //--------- choque escudo ---------------
                    if(escuadoActivado){
                        if(obstaculo->getPosY() == jugador->getPosY() - 1 and obstaculo->getPosX() == jugador->getPosX()){
                            background[obstaculo->getPosX()][obstaculo->getPosY() - 1] = " ";
                            background[obstaculo->getPosX() + 1][obstaculo->getPosY() - 1] = " ";
                            background[obstaculo->getPosX() + 2][obstaculo->getPosY() - 1] = " ";
                            background[obstaculo->getPosX() + 3][obstaculo->getPosY() - 1] = " ";
                            background[obstaculo->getPosX()][obstaculo->getPosY()] = " ";
                            background[obstaculo->getPosX() + 1][obstaculo->getPosY()] = " ";
                            background[obstaculo->getPosX() + 2][obstaculo->getPosY()] = " ";
                            background[obstaculo->getPosX() + 3][obstaculo->getPosY()] = " ";

                            listaObstaculos->remove();

                            escuadoActivado = false;

                            system("play crashSound.wav >>/dev/null 2>>/dev/null");
                        }
                    }

                    //--------- choque normal ---------------
                    if(obstaculo->getPosY() == jugador->getPosY() and obstaculo->getPosX() == jugador->getPosX()){
                        background[obstaculo->getPosX()][obstaculo->getPosY() - 1] = " ";
                        background[obstaculo->getPosX() + 1][obstaculo->getPosY() - 1] = " ";
                        background[obstaculo->getPosX() + 2][obstaculo->getPosY() - 1] = " ";
                        background[obstaculo->getPosX() + 3][obstaculo->getPosY() - 1] = " ";
                        background[obstaculo->getPosX()][obstaculo->getPosY()] = " ";
                        background[obstaculo->getPosX() + 1][obstaculo->getPosY()] = " ";
                        background[obstaculo->getPosX() + 2][obstaculo->getPosY()] = " ";
                        background[obstaculo->getPosX() + 3][obstaculo->getPosY()] = " ";

                        lives -= 1;
                        listaObstaculos->remove();

                        system("play Crash.wav >>/dev/null 2>>/dev/null");

                        if(lives <= 0){
                            background[18][4] = "0";
                            juegoPerdido = true;
                        }
                    }
                }
            }
            else if(obstaculo->getTipoObstaculo() == "rotuloAlto"){
                background[obstaculo->getPosX()][obstaculo->getPosY() - 2] = " ";
                background[obstaculo->getPosX() + 1][obstaculo->getPosY() - 2] = " ";
                background[obstaculo->getPosX() + 2][obstaculo->getPosY() - 2] = " ";
                background[obstaculo->getPosX() + 3][obstaculo->getPosY() - 2] = " ";
                background[obstaculo->getPosX()][obstaculo->getPosY() - 1] = " ";
                background[obstaculo->getPosX() + 3][obstaculo->getPosY() - 1] = " ";

                if(jugador->getEstado() != "agacharse"){


                    //---------- choque escudo ------------
                    if(escuadoActivado){
                        if(jugador->getPosX() - 1 == obstaculo->getPosX() and jugador->getPosY() <= obstaculo->getPosY() + 2 and jugador->getPosY() >= obstaculo->getPosY()){
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
                        
                            listaObstaculos->remove();

                            escuadoActivado = false;

                            system("play crashSound.wav >>/dev/null 2>>/dev/null");
                        }
                    }

                    //---------- choque normal ------------
                    if(jugador->getPosX() == obstaculo->getPosX() and jugador->getPosY() <= obstaculo->getPosY() + 2 and jugador->getPosY() >= obstaculo->getPosY()){
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
                        
                        lives -= 1;
                        listaObstaculos->remove();  

                        system("play Crash.wav >>/dev/null 2>>/dev/null");

                        if(lives <= 0){
                            background[18][4] = "0";
                            juegoPerdido = true;
                        }

                    }
                }
            }

            //-------- Eliminar al objeto cuando llega al final de la matriz.
            if(obstaculo->getPosY() == height - 1){

                if(obstaculo->getTipoObstaculo() == "barricada"){
                    background[obstaculo->getPosX()][obstaculo->getPosY() - 1] = " ";
                    background[obstaculo->getPosX() + 1][obstaculo->getPosY() - 1] = " ";
                    background[obstaculo->getPosX() + 2][obstaculo->getPosY() - 1] = " ";
                    background[obstaculo->getPosX() + 3][obstaculo->getPosY() - 1] = " ";
                    background[obstaculo->getPosX()][obstaculo->getPosY()] = " ";
                    background[obstaculo->getPosX() + 1][obstaculo->getPosY()] = " ";
                    background[obstaculo->getPosX() + 2][obstaculo->getPosY()] = " ";
                    background[obstaculo->getPosX() + 3][obstaculo->getPosY()] = " ";

                    listaObstaculos->remove();

                }
                else if(obstaculo->getTipoObstaculo() == "pared"){
                    background[obstaculo->getPosX()][obstaculo->getPosY() - 1] = " ";
                    background[obstaculo->getPosX() + 1][obstaculo->getPosY() - 1] = " ";
                    background[obstaculo->getPosX() + 2][obstaculo->getPosY() - 1] = " ";
                    background[obstaculo->getPosX() + 3][obstaculo->getPosY() - 1] = " ";
                    background[obstaculo->getPosX()][obstaculo->getPosY()] = " ";
                    background[obstaculo->getPosX() + 1][obstaculo->getPosY()] = " ";
                    background[obstaculo->getPosX() + 2][obstaculo->getPosY()] = " ";
                    background[obstaculo->getPosX() + 3][obstaculo->getPosY()] = " ";

                    listaObstaculos->remove();
                }
            }
            else if(obstaculo->getPosY() == height - 2){
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
                
                    listaObstaculos->remove();
                }
                
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
                background[powerUp->getPosX()][powerUp->getPosY()] = "∩";
            }
            else if(powerUp->getTipoPoder() == "iman"){
                background[powerUp->getPosX()][powerUp->getPosY()] = "Ω";
            }

            //-------- Aumentar una posición hacia abajo al objeto.
            powerUp->setPosY(powerUp->getPosY() + 1);

            //-------- Borrar el dibujo del objeto en la posición anterior.
            background[powerUp->getPosX()][powerUp->getPosY() - 2] = " ";


            //-------- Interactuar con un escudo --------
            if(powerUp->getTipoPoder() == "escudo" and powerUp->getPosX() == jugador->getPosX() and powerUp->getPosY() == jugador->getPosY()){
                escuadoActivado = true;

                system("play powerUpSound.wav >>/dev/null 2>>/dev/null");

            }

            //------- Interactuar con un iman -----------
            if(powerUp->getTipoPoder() == "iman" and powerUp->getPosX() == jugador->getPosX() and powerUp->getPosY() == jugador->getPosY()){
                imanActivado = true;
                turnosIman = 4;

                system("play powerUpSound.wav >>/dev/null 2>>/dev/null");
            }


            //-------- Eliminar al objeto cuando llega al final de la matriz.
            if(powerUp->getPosY() == height - 1){
                background[powerUp->getPosX()][powerUp->getPosY() - 1] = " ";
                background[powerUp->getPosX()][powerUp->getPosY()] = " ";
                listaPowerUps->remove();
            }
        }

    }

}

//------- funcion para controlar el frameRate ---
/// Waiting Function
void sleepcp(int milliseconds) // Cross-platform sleep function
{
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end)
    {
    }
}



int kbhit2(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

int main(){

    WINDOW * pantallaJuego = newwin(height, width, 0, 0);

    int frame = 0;

    // inicializa la pantalla
    // sets up memory and clears the screen

    setlocale(LC_ALL, "en_US.utf8");
    inicializarTerreno();

    initscr();
    start_color();

    //---------- Colores ----------
    init_pair(1, COLOR_RED, COLOR_BLACK);    // Rojo
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Amarillo
    init_pair(3, COLOR_GREEN, COLOR_BLACK);  // Verde
    init_pair(4, COLOR_BLUE, COLOR_BLACK);   // Azul
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);// Magenta
    init_pair(6, COLOR_CYAN, COLOR_BLACK);   // Cyan
    init_pair(7, COLOR_WHITE, COLOR_BLACK);  // Blanco

    init_pair(8, COLOR_RED, COLOR_WHITE);    // Rojo
    init_pair(9, COLOR_YELLOW, COLOR_WHITE); // Amarillo
    init_pair(10, COLOR_GREEN, COLOR_WHITE);  // Verde
    init_pair(11, COLOR_BLUE, COLOR_WHITE);   // Azul
    init_pair(12, COLOR_MAGENTA, COLOR_WHITE);// Magenta
    init_pair(13, COLOR_CYAN, COLOR_WHITE);   // Cyan
    init_pair(14, COLOR_BLACK, COLOR_WHITE);   // Cyan


    //-----------------------------



    cbreak();
    noecho();
    nodelay(stdscr, TRUE);

    keypad(stdscr, TRUE);
    scrollok(stdscr, TRUE);

    int c;

    //------------------------
    //--------------------
    while(seguirJugando){ 

        sleepcp(lap);


        if (kbhit2()) {
            c = getch();

            if(c == KEY_UP){
                jugador->setEstado("salto");
            }
            else if(c == KEY_DOWN){
                jugador->setEstado("agacharse");
            }
            else if(c == KEY_LEFT){
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
            else if(c == KEY_RIGHT){
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
            //------------- Pausar ------------------
            else if(c == 10){
                juegoPausado = !juegoPausado; 
            }
            //------------- Salir del juEgo ---------
            else if(c == KEY_BACKSPACE){
                seguirJugando = false;
            }   

            refresh();
        } else {
            refresh();
            //sleep(1);
        }


        if(juegoPerdido == false){
            if(juegoPausado == false){
                imprimirJugador();
                imprimirMatriz(pantallaJuego);

                generarObjeto(frame);

                imprimirMonedas(frame);
                imprimirObstaculos(frame);
                imprimirPowerUps(frame);


                frame += 1;
            }
            else{
                mvprintw(10, 10, "JUEGO EN PAUSA");
            }
        }
        else{
            mvprintw(10, 10, "PERDEDOR");
        }

    }
    //--------------------
//------------------------

    refresh();
    // termina la pantalla
    endwin();


    return 0;
}
