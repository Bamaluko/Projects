//
// Created by student on 07.04.2021.
//

#include <boost/test/unit_test.hpp>
#include "model/Vehicle.h"
#include "model/MotorVehicle.h"
#include "model/Car.h"
#include "model/Moped.h"
#include "model/Bicycle.h"
#include "model/typedefs.h"

BOOST_AUTO_TEST_SUITE(TestSuiteVehicle)


    BOOST_AUTO_TEST_CASE(ParameterConstructor) {
        VehiclePtr vehicle1 = std::make_shared <Bicycle>( (std::string)"EPD237",  12);
        BOOST_CHECK_EQUAL(vehicle1->getPlateNumber(), "EPD237");
        BOOST_CHECK_EQUAL(vehicle1->BasePrice(), 12);
        BOOST_CHECK_EQUAL(vehicle1->getVehicleInfo(), "BICYCLE: EPD237 12 ");
    }

    BOOST_AUTO_TEST_CASE(SetPlateNumberEmptyString) {
        VehiclePtr vehicle1 = std::make_shared <Bicycle>( (std::string)"EPD237",  12);
        BOOST_CHECK_THROW(vehicle1->setPlateNumber(""), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(SetBasePriceBelowNull) {
        VehiclePtr vehicle1 = std::make_shared <Bicycle>( (std::string)"EPD237",  12);
        BOOST_CHECK_THROW(vehicle1->setBasePrice(-2), std::logic_error);
    }


    BOOST_AUTO_TEST_CASE(SetPlateNumberConformance) {
        VehiclePtr vehicle1 = std::make_shared <Bicycle>( (std::string)"EPD238",  12);
        BOOST_CHECK_THROW(vehicle1->setPlateNumber(""), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(SetBasePriceConformance) {
        VehiclePtr vehicle1 = std::make_shared <Bicycle>( (std::string)"EPD237",  12);
        vehicle1->setBasePrice(10);
        BOOST_CHECK_EQUAL(vehicle1->BasePrice(), 10);
    }

    BOOST_AUTO_TEST_CASE(CheckMopedPriceTest) {
        VehiclePtr vehicle1 = std::make_shared <Moped>( (std::string)"EPD237",  12, 1500);
        BOOST_CHECK_EQUAL(vehicle1->getActualRentalPrice(), 15);
        VehiclePtr vehicle2 = std::make_shared <Moped>( (std::string)"EPU207",  12, 999);
        BOOST_CHECK_EQUAL(vehicle2->getActualRentalPrice(), 12);
        VehiclePtr vehicle3 = std::make_shared <Moped>( (std::string)"ESI154",  12, 2000);
        BOOST_CHECK_EQUAL(vehicle3->getActualRentalPrice(), 18);
    }

    BOOST_AUTO_TEST_CASE(CheckCarPriceTest) {
        VehiclePtr vehicle1 = std::make_shared <Car>( (std::string)"EPD237",  12, 1500, A);
        BOOST_CHECK_EQUAL(vehicle1->getActualRentalPrice(), 15);
        VehiclePtr vehicle2 = std::make_shared <Car>( (std::string)"EPU207",  12, 999, B);
        BOOST_TEST_CHECK(vehicle2->getActualRentalPrice() == (12*(1.1)), boost::test_tools::tolerance(0.002));
        VehiclePtr vehicle3 = std::make_shared <Car>( (std::string)"ESI154",  12, 2000, E);
        BOOST_CHECK_EQUAL(vehicle3->getActualRentalPrice(), 27);
    }

    BOOST_AUTO_TEST_CASE(CheckBicyclePriceTest) {
        VehiclePtr vehicle1 = std::make_shared <Bicycle>( (std::string)"EPD237",  12);
        BOOST_CHECK_EQUAL(vehicle1->getActualRentalPrice(), 12);

    }

    BOOST_AUTO_TEST_CASE(GetInfoForDerivedClasses) {
        VehiclePtr vehicle1 = std::make_shared <Bicycle>( (std::string)"EPD237",  12);
        BOOST_CHECK_EQUAL(vehicle1->getInfo(), "BICYCLE: EPD237 12 ");

    }

    BOOST_AUTO_TEST_CASE(GetInfoForDerivedClassesSecondVariation) {
        VehiclePtr vehicle1 = std::make_shared <Car>( (std::string)"EPD237",  12, 2000, A);
        BOOST_CHECK_EQUAL(vehicle1->getInfo(), "Car: EPD237 12 . Engine displacement: 2000 segment: 10");

    }



BOOST_AUTO_TEST_SUITE_END()