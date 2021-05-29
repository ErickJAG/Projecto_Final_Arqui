#ifndef POWERUP_H
#define POWERUP_H

#include <string>

using namespace std;

class PowerUp
//---------------- Esta es la clase que simula el comportamiento de los power ups.
{
    private:
        string tipoPoder = "";
        int carril = 0;

        int posX = 7;
        int posY = 2;

    public:
        PowerUp() {
            srand (time(NULL));
            carril = rand() % 3 + 1;
            if(carril == 1){
                posX = 1;
            }
            else if(carril == 2){
                posX = 6;
            }
            else if(carril == 3){
                posX = 11;
            }
            posY = 0;
        }
        virtual ~PowerUp() {}

        //--------------- getters y setters ---------
        string getTipoPoder(){
            return tipoPoder;
        }

        void setTipoPoder(string nuevoPoder){
            tipoPoder = nuevoPoder;
        }

        int getCarril(){
            return carril;
        }

        void setCarril(int nuevoCarril){
            carril = nuevoCarril;
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

        void setPosY(int y){
            posY = y;
        }

};

#endif // POWERUP_H
