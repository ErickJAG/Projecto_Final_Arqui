#ifndef OBSTACULO_H
#define OBSTACULO_H


class Obstaculo
//--------------- Esta es la clase que simula el comportamiento de los obstaculos.
{

    private:
        String tipoObstaculo = "";
        Int carril = 0;

        Int posX = 0;
        Int posY = 0;

    public:
        Obstaculo() {}
        virtual ~Obstaculo() {}

        //--------------- getters y setters -------
        String getTipoObstaculo(){
            return tipoObstaculo;
        }

        void setTipoObstaculo(tipoObstaculo = nuevoTipo){
            tipoObstaculo = nuevoTipo;
        }

        Int getCarril(){
            return carril;
        }

        void setCarril(Int nuevoCarril){
            carril = nuevoCarril;
        }

};

#endif // OBSTACULO_H
