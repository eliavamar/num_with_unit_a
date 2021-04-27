#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <unordered_map>

namespace ariel{
    class NumberWithUnits{
        private:
            double base_num;
            std::string base_unit;
        public:
            static std::unordered_map<std::string,std::string>comp;
            double num_of_unit;
            std::string unit;
           
            NumberWithUnits(double num,std::string u){
            if(comp.find(u)==comp.end()){   throw std::out_of_range{"Units do not match"};;}
            num_of_unit=num;unit=u;
            }

            static void read_units(std::ifstream& file){
               double num1;
               double num2;
               char equals;
               std::string unit1;
               std::string unit2;
                while(file>>num1>>unit1>>equals>>num2>>unit2){
                    comp[unit1]=std::to_string(num2)+":"+unit2;
                    if(comp.find(unit2)==comp.end()){comp[unit2]="flag";}
                }
            }

            double conv(std::string from)const{
                double convert_num=1;
                double not_found=-1;                
                std::string to=(this->unit);                 
                if((from.compare(to))==0){return convert_num;}
                std::string spilt_char=":";
                int i=1;
                while(comp.find(from)!=comp.end()&&comp[from]!="flag"){
                    unsigned long pos=(unsigned long)comp[from].find(spilt_char);
                    convert_num=convert_num*stod(comp[from].substr(0,pos));
                    from=comp[from].substr(pos+1);
                    if((from.compare(to))==0){return convert_num;}
                }  
                return not_found;
            }
            double eql(const NumberWithUnits& other)const{
                if(this->unit==other.unit){return (this->num_of_unit-other.num_of_unit);}
                double sum1=this->num_of_unit;
                double sum2=other.num_of_unit;
                std::string unit1=this->unit;
                std::string unit2=other.unit;
                std::string flag="flag";
                std::string spilt_char=":";
                while(comp[unit1]!=flag){
                    unsigned long pos1=(unsigned long)comp[unit1].find(spilt_char);                    
                    sum1*=stod(comp[unit1].substr(0,pos1));
                    unit1=comp[unit1].substr(pos1+1);                    
                }
                while(comp[unit2]!=flag){
                    unsigned long pos2=(unsigned long)comp[unit2].find(spilt_char);                    
                    sum2*=stod(comp[unit2].substr(0,pos2));
                    unit2=comp[unit2].substr(pos2+1);                    
                }
                if(unit1!=unit2){
                    throw std::out_of_range{"Units do not match"};}
                return(sum1-sum2);
            }
            
            NumberWithUnits& operator-=(const NumberWithUnits& other);
            
            NumberWithUnits& operator+=(const NumberWithUnits& other);
                          
            NumberWithUnits operator--(int dummy_flag_for_postfix_increment);
            
            NumberWithUnits& operator--();
            
            NumberWithUnits& operator++();
            
            NumberWithUnits operator++(int dummy_flag_for_postfix_increment);            
            
            NumberWithUnits operator-(){return NumberWithUnits(-(this->num_of_unit),this->unit);}//implementation
           
            NumberWithUnits operator+(){return NumberWithUnits((this->num_of_unit),this->unit);} //implementation
            
            bool operator>(const NumberWithUnits& other)const;

            bool operator>= (const NumberWithUnits& other)const;

            bool operator<(const NumberWithUnits& other)const;

            bool operator<=(const NumberWithUnits& other)const;

            bool operator==(const NumberWithUnits& other)const;

            bool  operator!=(const NumberWithUnits& other)const;

            friend NumberWithUnits operator -(const NumberWithUnits& other1,const NumberWithUnits& other2);
            
            friend NumberWithUnits operator +(const NumberWithUnits& other1,const NumberWithUnits& other2);            

            friend NumberWithUnits operator *(const NumberWithUnits& unit,double num);
           
            friend NumberWithUnits operator *(double num,const NumberWithUnits& unit);
    
            friend std::ostream& operator<< (std::ostream& os, const NumberWithUnits & unit);
            
            friend std::istream& operator>> (std::istream& input, NumberWithUnits& other);

    };
}