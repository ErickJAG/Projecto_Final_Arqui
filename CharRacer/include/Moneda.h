#ifndef MONEDA_H
#define MONEDA_H


class Moneda
//------------ Esta es la clase que simula el comportamiento de las monedas.
{
    private:
        int cantidad = 0;
        int carril = 0;
        int posX = 7;
        int posY = 2;

    public:
        Moneda() {
            cantidad = 0;
            carril = 0;
            posX = 7;
            posY = 2;
        }
        virtual ~Moneda() {}

        //------------ getters y setters -------
        int getCantidad(){
            return cantidad;
        }

        void setCantidad(int nuevaCantidad){
            cantidad = nuevaCantidad;
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

#endif // MONEDA_H
