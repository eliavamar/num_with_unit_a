#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <cstdlib>
#include "NumberWithUnits.hpp" 
constexpr double EPS=0000.1;
char actualChar;
using namespace std;
namespace ariel{
unordered_map<string,string>NumberWithUnits::comp;
char ch;

NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& other){
    double error=-1;
    double res=-1;
    if((res=this->conv(other.unit))>error){
        this->num_of_unit-=other.num_of_unit*res;
        return (*this);
    }
    if((res=other.conv(this->unit))>error){
        this->num_of_unit-=((other.num_of_unit)/res);
        return  (*this);
    }
    throw out_of_range {"Units do not match"};
         
}

NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& other){
    double error=-1;
    double res=-1;
    if((res=this->conv(other.unit))>error){
        this->num_of_unit+=other.num_of_unit*res;
        return *this;
    }
    if((res=other.conv((this)->unit))>error){
        this->num_of_unit+=((other.num_of_unit)/res);
        return *this;
    }
    throw out_of_range{"Units do not match"};
          
    
}

NumberWithUnits NumberWithUnits::operator--(int dummy_flag_for_postfix_increment){
    NumberWithUnits  copy  =*this;
    this->num_of_unit-=1;
    return copy;                
}

NumberWithUnits& NumberWithUnits::operator--(){
    this->num_of_unit-=1;
    return *this;
}

NumberWithUnits NumberWithUnits::operator++(int dummy_flag_for_postfix_increment){
    NumberWithUnits copy=*this;
    this->num_of_unit+=1;
    return copy;                
}

NumberWithUnits& NumberWithUnits::operator++(){
    this->num_of_unit+=1;
    return *this;
}

bool NumberWithUnits::operator>(const NumberWithUnits& other)const{return (this->eql(other)>0);}

bool NumberWithUnits::operator>=(const NumberWithUnits& other)  const {return (this->eql(other)>=0);}

bool NumberWithUnits::operator==(const NumberWithUnits& other)const{return (abs(this->eql(other))<EPS);}

bool NumberWithUnits::operator!=(const NumberWithUnits& other)const{return !(*this==other);}

bool NumberWithUnits::operator<(const NumberWithUnits& other)const{return!(*this>=other);}

bool NumberWithUnits::operator<=(const NumberWithUnits& other)const{return!(*this>other);}

NumberWithUnits operator-(const NumberWithUnits& other1,const NumberWithUnits& other2){
    double error=-1;
    double res=-1;
    if((res=other2.conv(other1.unit))>error){
        return (NumberWithUnits(other1.num_of_unit-other2.num_of_unit/res,other1.unit));
    }
    if((res=other1.conv(other2.unit))>error){
        return (NumberWithUnits(other1.num_of_unit-other2.num_of_unit*res,other1.unit));
    }
    throw out_of_range{"Units do not match"};

}

NumberWithUnits operator +(const NumberWithUnits& other1,const NumberWithUnits& other2){
    double error=-1;
    double res=-1;
    double num=other2.num_of_unit;
    string u=other2.unit;
    string spilt_char=":";
    while(NumberWithUnits::comp[u]!="flag"){
        unsigned long pos1=(unsigned long)NumberWithUnits::comp[u].find(spilt_char);                    
        num*=stod(NumberWithUnits::comp[u].substr(0,pos1));
        u=NumberWithUnits::comp[u].substr(pos1+1);      
    }
    NumberWithUnits other3{num,u};
    if((res=other3.conv(other1.unit))>error){
        return (NumberWithUnits(other1.num_of_unit+other3.num_of_unit/res,other1.unit));
    }
    // if((res=other1.conv(other.unit))>error){
    //     return (NumberWithUnits(other1.num_of_unit+other2.num_of_unit*res,other1.unit));
    // }
    throw out_of_range{"Units do not match"};
    

}

NumberWithUnits operator *(double num,const NumberWithUnits& unit){return  NumberWithUnits(unit.num_of_unit*num,unit.unit);}

NumberWithUnits operator *(const NumberWithUnits& unit,double num){return (num*unit);}

ostream& operator<< (std::ostream& os, const NumberWithUnits & unit){
    return (os<<unit.num_of_unit<<"["<<unit.unit<<"]");
}
static istream& getAndCheckNextCharIs(istream& input, char expectedChar) {
    input >> actualChar;
    if (!input) {return input;}
    if (actualChar!=expectedChar) {
        // failbit is for format error
        input.setstate(ios::failbit);
    }
    return input;
}

istream& operator>> (istream& input, NumberWithUnits& other) {
    double num = 0;
    string unit;
    ios::pos_type startPosition = input.tellg();
    if ((!(input >> num))||(!getAndCheckNextCharIs(input,'['))||(!(input >> unit))) {
        auto errorState = input.rdstate(); // remember error state
        input.clear(); // clear error so seekg will work
        input.seekg(startPosition); // rewind
        input.clear(errorState); // set back the error flag
    } else {
        if(unit.at(unit.length()-1)==']'){unit=unit.substr(0,unit.length()-1);}
        else{getAndCheckNextCharIs(input,']');}
        if(NumberWithUnits::comp.find(unit)==NumberWithUnits::comp.end()){throw out_of_range{"Units do not match"};}
        other.unit = unit;
        other.num_of_unit = num;
    }

    return input;
}


}
