#ifndef JUGADOR_H
#define JUGADOR_H


class Jugador
//-------- Esta es la clase que simula el comportamiento del jugador del juego.
{
    private:
        String nickname = "";
        Int puntuacion = 0;
        Int carril = 0;
        Int vidas = 0;

        Int posX = 0;
        Int posY = 0;

    public:
        Jugador() {}
        virtual ~Jugador() {}

        //-------- getters y setters ----------
        String getNickname(){
            return nickname;
        }

        void setNickname(String nuevoNick){
            nickname = nuevoNick;
        }

        Int getPuntuacion(){
            return puntuacion;
        }

        void setPuntuacion(Int nuevaPuntuacion){
            puntuacion = nuevaPuntuacion;
        }

        Int getCarril(){
            return carril;
        }

        void setCarril(Int nuevoCarril){
            carril = nuevoCarril;
        }

        Int getVidas(){
            return vidas;
        }

        void setVidas(Int nuevasVidas){
            vidas = nuevasVidas;
        }

};

#endif // JUGADOR_H
