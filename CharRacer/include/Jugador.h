#ifndef JUGADOR_H
#define JUGADOR_H
#include <string>

using namespace std;

class Jugador
//-------- Esta es la clase que simula el comportamiento del jugador del juego.
{
    private:
        string nickname = " ";
        int puntuacion = 0;
        int carril = 0;
        int vidas = 0;
        string estado = "normal";

        int posX = 6;
        int posY = 11;

    public:
        Jugador() {
            nickname = " ";
            puntuacion = 0;
            carril = 0;
            vidas = 0;
            estado = "normal";

            posX = 6;
            posY = 15;
        }

        virtual ~Jugador() {}

        //-------- getters y setters ----------
        string getNickname(){
            return nickname;
        }

        void setNickname(string nuevoNick){
            nickname = nuevoNick;
        }

        int getPuntuacion(){
            return puntuacion;
        }

        void setPuntuacion(int nuevaPuntuacion){
            puntuacion = nuevaPuntuacion;
        }

        int getCarril(){
            return carril;
        }

        void setCarril(int nuevoCarril){
            carril = nuevoCarril;
        }

        int getVidas(){
            return vidas;
        }

        void setVidas(int nuevasVidas){
            vidas = nuevasVidas;
        }

        int getPosX(){
            return posX;
        }

        void setPosX(int x){
            posX = x;
        }

        int getPosY(){
            return posY;
        }

        void setEstado(string nuevoEstado){
            estado = nuevoEstado;
        }

        string getEstado(){
            return estado;
        }



};

#endif // JUGADOR_H
