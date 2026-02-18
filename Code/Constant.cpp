//File: Constant.cpp
#include "Constant.h"
#include <cassert>

gamelang::Type  Constant::type() const 
{ return intrinsic_type; }

const Constant*   Integer_constant::evaluate() const
{ return new Integer_constant(*this); }

const Constant*   Double_constant::evaluate() const
{ return new Double_constant(*this); }

const Constant*   String_constant::evaluate() const
{ return new String_constant(*this); }

int Game_attribute_constant::as_int() const{
    if(gop->attribute_type(attribute_name) != gamelang::INT){
        throw (Constant::type());
    }
    int value;
    gop->read_attribute(attribute_name, value);
    return value;
}

double Game_attribute_constant::as_double() const{
    

    gamelang::Type got = gop->attribute_type(attribute_name);
    if(got == gamelang::DOUBLE){
        double value;
        gop->read_attribute(attribute_name, value);
        return value;
    }else if(got == gamelang::INT){
        int value;
        gop->read_attribute(attribute_name, value);
        return value;
    }else{
        throw (Constant::type());
    }
}

std::string  Game_attribute_constant::as_string() const{
   
    gamelang::Type got = gop->attribute_type(attribute_name);
    if(got == gamelang::STRING){
        std::string value;
        gop->read_attribute(attribute_name, value);
        return value;
    }else if(got == gamelang::DOUBLE){
        double value;
        gop->read_attribute(attribute_name, value);
        return std::to_string(value);
    }else if(got == gamelang::INT){
        int value;
        gop->read_attribute(attribute_name, value);
        return std::to_string(value);
    }else{
        //assert(false);
        throw (Constant::type());
    }
}

const Constant* Game_attribute_constant::evaluate() const{
    gamelang::Type got = gop->attribute_type(attribute_name);
    if(got == gamelang::STRING){
        std::string value;
        gop->read_attribute(attribute_name, value);
        return new String_constant(value);
    }else if(got == gamelang::DOUBLE){
        double value;
        gop->read_attribute(attribute_name, value);
        return new Double_constant(value);
    }else if(got == gamelang::INT){
        int value;
        gop->read_attribute(attribute_name, value);
        return new Integer_constant(value);
    }else{
        //assert(false);
        throw (Constant::type());
    }
}
