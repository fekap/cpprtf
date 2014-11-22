#ifndef BASEELEMENT_H
#define BASEELEMENT_H
#include <typeinfo>
typedef void (*smartFunction)(void*);

class CppRtf_ParFormat;
class BaseElement
{
public:

    BaseElement();
    ~BaseElement();
    void* get(){return m_pointer;}

    template<class type>
    void set(type newClass, bool clone = false){
        if(clone)
            m_pointer = (void*)type(newClass);
        else
            m_pointer = (void*)newClass;
        m_name = typeid(type).name();
        smartPointer = BaseElement::deletePointer<type>;
    }

    template<class type>
    bool instanceOf(){
        if(typeid(type).name()==m_name){
            return true;
        }
        return false;
    }

    const char* name(){return m_name;}


//        virtual?
    CppRtf_ParFormat* getParFormat();
    void render();
private:
    smartFunction smartPointer;
    void* m_pointer;
    const char * m_name;

    template<class type>
    static void deletePointer(void *pointer){
        delete (type)pointer;
    }
};

#endif // BASEELEMENT_H
