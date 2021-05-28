#ifndef LIST_H
#define LIST_H

template <typename E>
class list{
private:
    //void operator =(const list&){}
    //list(const list&){}

public:
    list(){}
    virtual ~list(){}
    virtual void insert(E element) = 0 ;
    virtual void append(E element) = 0 ;
    virtual E remove() = 0;
    virtual void clear() = 0;
    virtual E getElement() = 0;
    virtual void gotoStart() = 0;
    virtual void gotoEnd() = 0;
    virtual void gotoPos(int pos) = 0;
    virtual void next() = 0;
    virtual void previous() = 0;
    virtual bool atStart() = 0;
    virtual bool atEnd() = 0;
    virtual int getPos() = 0;
    virtual int getSize() = 0;

};

#endif // LIST_H
