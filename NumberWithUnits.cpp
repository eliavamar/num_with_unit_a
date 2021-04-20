#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "NumberWithUnits.hpp"
using namespace std;
using namespace ariel;
std::unordered_map<std::string,std::string> comp;
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

bool NumberWithUnits::operator>(const NumberWithUnits& other)const{
    double error=-1;
    double res1=this->conv(other.unit);
    double res2=other.conv(this->unit);
    bool flag=false;
    if((res1==res2)&&(res1==error)){throw out_of_range{"Units do not match"};}
    if(res1!=error){flag=(this->num_of_unit>other.num_of_unit*res1);}
    else if(res2!=error){flag=(this->num_of_unit*res2>other.num_of_unit);}
    return flag;
}

bool NumberWithUnits::operator>=(const NumberWithUnits& other)  const {
    double error=-1;
    double res1=this->conv(other.unit);
    double res2=other.conv(this->unit);
    bool flag=false;
    if((res1==res2)&&(res1==error)){throw("Units do not match");}
    if(res1!=error){flag = (this->num_of_unit>=other.num_of_unit*res1);}
    else if(res2!=error){flag = (this->num_of_unit*res2>=other.num_of_unit);}
    return flag;
}

bool NumberWithUnits::operator==(const NumberWithUnits& other)const{
    double error=-1;
    bool flag=false;
    double res1=this->conv(other.unit);
    double res2=other.conv(this->unit);
    if((res1==res2)&&(res1==error)){throw out_of_range{"Units do not match"};}
    if(res1!=error){flag = (this->num_of_unit==other.num_of_unit*res1);}
    else if(res2!=error){flag = (this->num_of_unit*res2==other.num_of_unit);}
    return flag;
}

bool NumberWithUnits::operator!=(const NumberWithUnits& other)const{return !(*this==other);}

bool NumberWithUnits::operator<(const NumberWithUnits& other)const{return!(*this>=other);}

bool NumberWithUnits::operator<=(const NumberWithUnits& other)const{return!(*this>other);}

NumberWithUnits ariel::operator-(const NumberWithUnits& other1,const NumberWithUnits& other2){
    double error=-1;
    double res=-1;
    if((res=other2.conv(other1.unit))>error){
        return (NumberWithUnits(other1.num_of_unit-other2.num_of_unit/res,other1.unit));
    }
    if((res=other1.conv(other2.unit))>error){
        return (NumberWithUnits(other1.num_of_unit-other2.num_of_unit*res,other1.unit));
    }
    return (NumberWithUnits(other1.num_of_unit-other2.num_of_unit*res,other1.unit));


}

NumberWithUnits ariel::operator +(const NumberWithUnits& other1,const NumberWithUnits& other2){
    double error=-1;
    double res=-1;
    if((res=other2.conv(other1.unit))>error){
        return (NumberWithUnits(other1.num_of_unit+other2.num_of_unit/res,other1.unit));
    }
    if((res=other1.conv(other2.unit))>error){
        return (NumberWithUnits(other1.num_of_unit+other2.num_of_unit*res,other1.unit));
    }
    throw std::out_of_range{"Units do not match"};
    

}

NumberWithUnits ariel::operator *(double num,const NumberWithUnits& unit){return  NumberWithUnits(unit.num_of_unit*num,unit.unit);}

NumberWithUnits ariel::operator *(const NumberWithUnits& unit,double num){return (num*unit);}

ostream& ariel::operator<< (std::ostream& os, const NumberWithUnits & unit){
    return (os<<unit.num_of_unit<<"["<<unit.unit<<"]");
}
istream& ariel::operator>> (istream& input, NumberWithUnits& other) {
    return (input >> other.num_of_unit >> ch >> other.unit>> ch);
}


 
