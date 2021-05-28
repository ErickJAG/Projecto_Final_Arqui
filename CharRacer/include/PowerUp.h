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

        int posX = 0;
        int posy = 0;

    public:
        PowerUp() {}
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


};

#endif // POWERUP_H
