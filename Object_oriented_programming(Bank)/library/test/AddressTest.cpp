//
// Created by student on 06.04.2021.
//

#include <boost/test/unit_test.hpp>
#include "model/Address.h"
#include "model/typedefs.h"

BOOST_AUTO_TEST_SUITE(TestSuiteAdress)


    BOOST_AUTO_TEST_CASE(ParameterConstructor) {
        AddressPtr address1 = std::make_shared <Address>((std::string)"Wroclaw", (std::string)"Wyborna", (std::string)"23");
        BOOST_CHECK_EQUAL(address1->getCity(), "Wroclaw");
        BOOST_CHECK_EQUAL(address1->getStreet(), "Wyborna");
        BOOST_CHECK_EQUAL(address1->getNumber(), "23");
        BOOST_CHECK_EQUAL(address1->getAddress(), "Wroclaw Wyborna 23");
        BOOST_REQUIRE_THROW(AddressPtr address2 = std::make_shared <Address>((std::string)"Wroclaw", (std::string)"", (std::string)"23"), std::logic_error);
        BOOST_REQUIRE_THROW(AddressPtr address2 = std::make_shared <Address>((std::string)"", (std::string)"Wyborna", (std::string)"23"), std::logic_error);
        BOOST_REQUIRE_THROW(AddressPtr address2 = std::make_shared <Address>((std::string)"Wroclaw", (std::string)"Wyborna", (std::string)""), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(SetCityEmptyString) {
        Address address1((std::string)"Wroclaw", (std::string)"Wyborna", (std::string)"23");
        BOOST_REQUIRE_THROW(address1.setCity(""), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(SetStreetCEmptyString) {
        Address address1((std::string)"Wroclaw", (std::string)"Wyborna", (std::string)"23");
        BOOST_REQUIRE_THROW(address1.setStreet(""), std::logic_error);
    }

   BOOST_AUTO_TEST_CASE(SetNumberEmptyString) {
        Address address1((std::string)"Wroclaw", (std::string)"Wyborna", (std::string)"23");
        BOOST_REQUIRE_THROW(address1.setNumber(""), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(SetCityConformance) {
        Address address1((std::string)"Wroclaw", (std::string)"Wyborna", (std::string)"23");
        address1.setCity("Lodz");
        BOOST_REQUIRE_EQUAL(address1.getCity(), "Lodz");
    }

    BOOST_AUTO_TEST_CASE(SetStreetConformance) {
        Address address1((std::string)"Wroclaw", (std::string)"Wyborna", (std::string)"23");
        address1.setStreet("Piotrkowska");
        BOOST_REQUIRE_EQUAL(address1.getStreet(), "Piotrkowska");
    }

    BOOST_AUTO_TEST_CASE(SetNumberConformance) {
        Address address1((std::string)"Wroclaw", (std::string)"Wyborna", (std::string)"23");
        address1.setNumber("123");
        BOOST_REQUIRE_EQUAL(address1.getNumber(), "123");
    }

BOOST_AUTO_TEST_SUITE_END()