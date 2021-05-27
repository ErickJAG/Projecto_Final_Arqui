#ifndef MONEDA_H
#define MONEDA_H


class Moneda
//------------ Esta es la clase que simula el comportamiento de las monedas.
{
    private:
        Int cantidad = 0;
        Int carril = 0;
        Int posX = 0;
        Int posY = 0;

    public:
        Moneda() {}
        virtual ~Moneda() {}

        //------------ getters y setters -------
        Int getCantidad(){
            return cantidad;
        }

        void setCantidad(Int nuevaCantidad){
            cantidad = nuevaCantidad();
        }

        Int getCarril(){
            return carril;
        }

        void setCarril(Int nuevoCarril){
            carril = nuevoCarril;
        }

};

#endif // MONEDA_H
