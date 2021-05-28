#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#define DEFAULT_MAX_SIZE 1024
#include "list.h"
#include <stdexcept>

using std::runtime_error;

template <typename E>
class ArrayList : public list<E>{
protected:
    E* elements;
    int max;
    int size;
    int pos;

public:
    ArrayList(int max = DEFAULT_MAX_SIZE){
        elements = new E[max];
        this->max = max;
        size = 0;
        pos = 0;
    }
    ~ArrayList(){
        delete [] elements;
    }
    void insert(E element){
        if(size < max){
            for (int i = size; i > pos; i--){
                this->elements[i]= this->elements[i-1];
            }
            this->elements[pos]= element;
            }
        else{
            max=max*2;
            E* temp = new E[max];
            for (int i = size; i > pos; i--){
                temp[i]= this->elements[i-1];
            }
            temp[pos]= element;
            delete []elements;
            elements=new E[max];
            for(int i=0; i<size+1; i++){
                elements[i]=temp[i];
            }
            delete []temp;
            }
        size++;
    }
    void append(E element){
        if (size<max){
            elements[size]=element;
            size++;}
        else{
            this->max=this->max*2;
            E* temp = new E[max];
            for(int i=0; i<size; i++){
                temp[i]=elements[i];
            }
            delete []elements;
            elements=new E[max];
            for(int i=0; i<size; i++){
                elements[i]=temp[i];
            }
            delete []temp;
            elements[size]=element;
        }
    }
    E remove(){
        if (size==0){
            throw runtime_error("List is empty.");
        }
        if (pos == size){
            throw runtime_error("No current element.");
        }
        E res = elements[pos];
        for(int i=pos; i < size-1; i++){
            elements[i]=elements[i+1];
        }
        size--;
        return res;
    }
    void clear(){
        size = pos = 0;
        delete [] elements;
        elements = new E[max];
    }
    E getElement(){
        if (size==0){
            throw runtime_error("List is empty.");
        }
        if (pos == size){
            throw runtime_error("No current element.");
        }
        return elements[pos];
    }
    void gotoStart(){
        pos = 0;
    }
    void gotoEnd(){
        pos = size;
    }
    void gotoPos(int newPos){
        if (newPos < 0 || newPos > size){
            throw runtime_error("Index out of bounds.");
        }
        pos=newPos;
    }
    void next(){
        if(pos < size){
            pos++;
        }
    }
    void previous(){
        if(pos > 0){
            pos--;
        }
    }
    bool atStart(){
        return pos == 0;
    }
    bool atEnd(){
        return pos == size;
    }
    int getPos(){
        return pos;
    }
    int getSize(){
        return size;
    }
    bool contains(E element){
        for(int i=0; i<size; i++){
            if (elements[i]==element)
                return true;
        }
        return false;
    }
    int indexOf(E element){
        for(int i=0; i<size; i++){
            if (elements[i]==element)
                return i;
        }
        return -1;
    }
    void extend(ArrayList L){
        int cantidad = L.getSize();
        int nuevoMax=max+cantidad;
        E* temp = new E[nuevoMax];
        for(int i=0; i<size; i++){
            temp[i]=elements[i];
        }
        delete []elements;
        this->max=nuevoMax;
        elements=new E[max];
        for(int i=0; i<size; i++){
            elements[i]=temp[i];
        }
        delete []temp;
        int cont=0;
        for(L.gotoStart();!L.atEnd(); L.next()){
            elements[size+cont] = L.getElement();
            cont++;
        }
        size = size + cantidad;
    }

};

#endif // ARRAYLIST_H
