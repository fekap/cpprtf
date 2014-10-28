#ifndef BASEELEMENT_H
#define BASEELEMENT_H
#include <typeinfo>

class CppRtf_ParFormat;
class BaseElement
{
public:

    void* get(){return m_pointer;}
    unsigned long hash(){return m_hash;}

    template<class type>
    void set(type newClass){
        m_pointer = (void*)newClass;
        m_name = typeid(type).name();
        m_hash = _hash((unsigned char*)m_name);
    }

    template<class type>
    bool instanceOf(){
//        if(_hash((unsigned char*)typeid(type).name())==m_hash){
//            return true;
//        }
        if(typeid(type).name()==m_name){
            return true;
        }
        return false;
    }

    static unsigned long _hash(unsigned char *str)
    {
        unsigned long _hash = 5381;
        int c;

        while ((bool)(c = *str++))
            _hash = ((_hash << 5) + _hash) + c; /* hash * 33 + c */

        return _hash;
    }

    const char* name(){return m_name;}


//        virtual?
    CppRtf_ParFormat* getParFormat();
    void render();
private:

    void* m_pointer;
    unsigned long m_hash;
    const char * m_name;
};

#endif // BASEELEMENT_H
