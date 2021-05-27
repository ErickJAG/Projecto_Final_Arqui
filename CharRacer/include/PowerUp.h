#ifndef POWERUP_H
#define POWERUP_H


class PowerUp
//---------------- Esta es la clase que simula el comportamiento de los power ups.
{
    private:
        String tipoPoder = "";
        Int carril = 0;

        Int posX = 0;
        Int posy = 0;

    public:
        PowerUp() {}
        virtual ~PowerUp() {}

        //--------------- getters y setters ---------
        String getTipoPoder(){
            return tipoPoder;
        }

        void setTipoPoder(String nuevoPoder){
            tipoPoder = nuevoPoder;
        }

        Int getCarril(){
            return carril;
        }

        void setCarril(Int nuevoCarril){
            carril = nuevoCarril;
        }


};

#endif // POWERUP_H
