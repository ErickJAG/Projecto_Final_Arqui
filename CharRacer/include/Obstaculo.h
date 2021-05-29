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

        int posX = 7;
        int posY = 2;

    public:
        Obstaculo() {
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

#endif // OBSTACULO_H
