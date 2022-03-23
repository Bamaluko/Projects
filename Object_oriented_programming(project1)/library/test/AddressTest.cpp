//
// Created by student on 18.05.2021.
//

#include <boost/test/unit_test.hpp>
#include "model/Address.h"
#include "model/typedefs.h"

BOOST_AUTO_TEST_SUITE(TestSuiteAdress)

    BOOST_AUTO_TEST_CASE(ParameterConstructorAndGettersTest) {

        AddressPtr address1 (new Address("Warszawa", "Zielona", "23", "14"));
        BOOST_REQUIRE_EQUAL(address1->getCity(), "Warszawa");
        BOOST_REQUIRE_EQUAL(address1->getStreet(), "Zielona");
        BOOST_REQUIRE_EQUAL(address1->getHouseNumber(), "23");
        BOOST_REQUIRE_EQUAL(address1->getFlatNumber(), "14");
    }

    BOOST_AUTO_TEST_CASE(ParameterConstructorNegativeTest) {


        BOOST_CHECK_THROW(AddressPtr address1 (new Address("", "Zielona", "23", "14")), std::logic_error);
        BOOST_CHECK_THROW(AddressPtr address1 (new Address("Warszawa", "", "23", "14")), std::logic_error);;
        BOOST_CHECK_THROW(AddressPtr address1 (new Address("Warszawa", "Zielona", "", "14")), std::logic_error);
        BOOST_CHECK_NO_THROW(AddressPtr address1 (new Address("Warszawa", "Zielona", "23", "14")));
    }


BOOST_AUTO_TEST_SUITE_END()