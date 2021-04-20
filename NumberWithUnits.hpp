#pragma once
#include <sstream>
#include <istream>
#include <iostream>
#include <unordered_map>
extern std::unordered_map<std::string,std::string> comp;
namespace ariel{
    class NumberWithUnits{
        public:
            double num_of_unit;
            std::string unit;
            
            NumberWithUnits(double num,std::string u){
            if(comp.find(u)==comp.end()){throw std::out_of_range{"Units do not match"};}
            num_of_unit=num;unit=u;
            }

            static void read_units(std::ifstream& t){
                std::string str;   
                str.assign((std::istreambuf_iterator<char>(t)),
                std::istreambuf_iterator<char>());
                unsigned long i=0;
                while(i<str.length()){
                    std::string temp_key;
                    std::string temp_num;
                    std::string temp_unit;                      
                    while((str[i]<'a'||str[i]>'z')&&(str[i]<'A'||str[i]>'Z')&&(i<str.length())){i++;}
                    while(((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z'))&&(i<str.length())){temp_key=temp_key+str[i++];}
                    while((str[i]<'1'||str[i]>'9')&&(i<str.length())){i++;}
                    while(str[i]!=' '&&str[i]!='\n'&&(i<str.length())){temp_num=temp_num+str[i++];}
                    while((str[i]<'a'||str[i]>'z')&&(str[i]<'A'||str[i]>'Z')&&(i<str.length())){i++;}
                    while(((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z'))&&(i<str.length())){temp_unit=temp_unit+str[i++];}
                    if(temp_unit.length()>0&&temp_key.length()>0&&temp_num.length()>0){comp[temp_key]=(temp_num+":"+temp_unit);comp[temp_unit]="empty";}
                }
            }

            double conv(std::string from)const{
                double convert_num=1;
                double not_found=-1;                
                std::string to=(this->unit);                 
                if(from==to){return convert_num;}
                std::string spilt_char=":";
                while(comp.find(from)!=comp.end()&&comp[from]!="empty"){
                    unsigned long pos=(unsigned long)comp[from].find(spilt_char);
                    convert_num=convert_num*stod(comp[from].substr(0,pos));
                    from=comp[from].substr(pos+1);
                    if(from==to){return convert_num;}
                }
                return not_found;
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