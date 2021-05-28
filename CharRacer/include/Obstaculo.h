#ifndef OBSTACULO_H
#define OBSTACULO_H

#include<string>

using namespace std;

class Obstaculo
//--------------- Esta es la clase que simula el comportamiento de los obstaculos.
{

    private:
        string tipoObstaculo = "";
        int carril = 0;

        int posX = 0;
        int posY = 0;

    public:
        Obstaculo() {}
        virtual ~Obstaculo() {}

        //--------------- getters y setters -------
        string getTipoObstaculo(){
            return tipoObstaculo;
        }

        void setTipoObstaculo(string nuevoTipo){
            tipoObstaculo = nuevoTipo;
        }

        int getCarril(){
            return carril;
        }

        void setCarril(int nuevoCarril){
            carril = nuevoCarril;
        }

};

#endif // OBSTACULO_H
