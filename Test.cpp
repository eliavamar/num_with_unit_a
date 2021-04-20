
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "doctest.h"
#include "NumberWithUnits.hpp"
using namespace std;
using namespace ariel;

 

TEST_CASE("Working codes"){ 
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);
    NumberWithUnits USD{1,"USD"};
    NumberWithUnits ILS{3,"ILS"};
    NumberWithUnits km{4,"km"};
    NumberWithUnits m{2500,"m"};
    NumberWithUnits kg{200,"kg"};
    NumberWithUnits ton{1,"ton"};
    NumberWithUnits hour{3,"hour"};
    NumberWithUnits min{5,"min"};
    CHECK((USD!=ILS));
    CHECK(!(USD<=ILS));
    CHECK((USD<3*ILS));
    CHECK(((km+m)==NumberWithUnits{6.5,"km"}));
    CHECK(((m+=NumberWithUnits{6.5,"km"})>km));
    CHECK(((m-=NumberWithUnits{6.5,"km"})==NumberWithUnits {2500,"m"}));
    CHECK((hour<=(min+NumberWithUnits{180,"min"})));
    CHECK(((hour*5)>=(min+NumberWithUnits{180,"min"})));
    CHECK(((++(++ILS))>USD++));//ILS=4,USD=2
    CHECK((USD>ILS));
 }
  TEST_CASE("unworking code") {
    NumberWithUnits USD{1,"USD"};
    NumberWithUnits ILS{3,"ILS"};
    NumberWithUnits km{4,"km"};
    NumberWithUnits m{2500,"m"};
    NumberWithUnits kg{200,"kg"};
    NumberWithUnits ton{1,"ton"};
    NumberWithUnits hour{3,"hour"};
    NumberWithUnits min{5,"min"};
    CHECK_THROWS((USD+hour));
    CHECK_THROWS((hour-=ton));
    CHECK_THROWS((m+USD));
    CHECK_THROWS((m+=kg));
    CHECK_THROWS((NumberWithUnits {200,"Kg"}));
    CHECK_THROWS(km-min+ton);
    CHECK_THROWS(((500*(min))+ILS));
    CHECK_THROWS((ton+NumberWithUnits{1,"g"}+NumberWithUnits{1,"G"}));
    CHECK_THROWS((NumberWithUnits{1,"USd"}));
    CHECK_THROWS((NumberWithUnits{8,"KG"}));

}
    