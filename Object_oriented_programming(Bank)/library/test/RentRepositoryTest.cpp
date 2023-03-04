//
// Created by student on 15.04.2021.
//

#include <string>
#include <boost/test/unit_test.hpp>
#include "repositories/StorageContainer.h"
#include "model/typedefs.h"
#include "model/Bicycle.h"
#include "model/ClientDefault.h"

using namespace  std;


BOOST_AUTO_TEST_SUITE(TestSuiteRentRepository)

    struct TestSuiteRentRepositoryFixture {
        const int testid = 12;
        AddressPtr testaddress1;
        ClientPtr testclient1;
        VehiclePtr testvehicle1;
        RentPtr testrent1;
        StorageContainer *teststorage;
        ClientTypePtr defaultclient;

        TestSuiteRentRepositoryFixture() {
            defaultclient = ClientTypePtr (new ClientDefault);
            testaddress1=std::make_shared <Address>("Poznan", "Zlota", "14");
            testclient1=std::make_shared <Client>((std::string)"Jan", (std::string)"Jankowski", (std::string)"2435435432", testaddress1, defaultclient);
            testvehicle1=std::make_shared <Bicycle>((std::string)"ESI654",  9);
            teststorage = new StorageContainer;
            testrent1 =std::make_shared <Rent>(12, testclient1, testvehicle1, boost::posix_time::not_a_date_time);
        }

        ~TestSuiteRentRepositoryFixture() {
            delete teststorage;
        }

    };


    BOOST_FIXTURE_TEST_SUITE(TestSuiteRentRepository, TestSuiteRentRepositoryFixture)


        BOOST_AUTO_TEST_CASE(RentRepositorySizeTest) {

            BOOST_REQUIRE_EQUAL(teststorage->getRentRep()->RepositorySize() , 1);
            teststorage->getRentRep()->add(testrent1);
            BOOST_REQUIRE_EQUAL(teststorage->getRentRep()->RepositorySize() , 2);

        }


        BOOST_AUTO_TEST_CASE(GetRentTest) {

            std::stringstream ss;
            ss << boost::posix_time::second_clock::local_time();
            std::string s = ss.str();
            BOOST_REQUIRE_EQUAL(teststorage->getRentRep()->get(0)->getRentInfo(), "1 Adam Adamski 1435435435 Wroclaw Piekna 23 DEFAULT Max vehicles: 1 BICYCLE: EPD237 10  " + s + " not-a-date-time");

        }

        BOOST_AUTO_TEST_CASE(GetRentTestIndexBelow0) {

            BOOST_REQUIRE_EQUAL(teststorage->getRentRep()->get(-3) , nullptr);

        }

        BOOST_AUTO_TEST_CASE(GetRentTestIndexOverSize) {

            BOOST_REQUIRE_EQUAL(teststorage->getRentRep()->get(1) , nullptr);

        }

        BOOST_AUTO_TEST_CASE(AddRentTest) {

            teststorage->getRentRep()->add(testrent1);
            BOOST_REQUIRE_EQUAL(teststorage->getRentRep()->RepositorySize() , 2);
            std::stringstream ss;
            ss << boost::posix_time::second_clock::local_time();
            std::string s = ss.str();
            BOOST_REQUIRE_EQUAL(teststorage->getRentRep()->get(1)->getRentInfo(), "12 Jan Jankowski 2435435432 Poznan Zlota 14 DEFAULT Max vehicles: 1 BICYCLE: ESI654 9  " + s +" not-a-date-time");

        }

        BOOST_AUTO_TEST_CASE(AddRentTestNullPtr) {

            teststorage->getRentRep()->add(nullptr);
            BOOST_REQUIRE_EQUAL(teststorage->getRentRep()->RepositorySize() , 1);
            BOOST_REQUIRE_EQUAL(teststorage->getRentRep()->get(1) , nullptr);

        }

        BOOST_AUTO_TEST_CASE(RemoveRentTest) {

            teststorage->getRentRep()->add(testrent1);
            BOOST_REQUIRE_EQUAL(teststorage->getRentRep()->RepositorySize() , 2);
            teststorage->getRentRep()->remove(testrent1);
            BOOST_REQUIRE_EQUAL(teststorage->getRentRep()->get(1) , nullptr);
            BOOST_REQUIRE_EQUAL(teststorage->getRentRep()->RepositorySize() , 1);

        }

        BOOST_AUTO_TEST_CASE(RemoveRentTestNullPtr) {

            teststorage->getRentRep()->add(testrent1);
            BOOST_REQUIRE_EQUAL(teststorage->getRentRep()->RepositorySize() , 2);
            teststorage->getRentRep()->remove(nullptr);
            BOOST_REQUIRE_EQUAL(teststorage->getRentRep()->get(1) , testrent1);
            BOOST_REQUIRE_EQUAL(teststorage->getRentRep()->RepositorySize() , 2);

        }

        BOOST_AUTO_TEST_CASE(RentReportTest) {

            teststorage->getRentRep()->add(testrent1);
            std::stringstream ss;
            ss << boost::posix_time::second_clock::local_time();
            std::string s = ss.str();
            BOOST_REQUIRE_EQUAL(teststorage->getRentRep()->Raport() , "1 Adam Adamski 1435435435 Wroclaw Piekna 23 DEFAULT Max vehicles: 1 BICYCLE: EPD237 10  " + s + " not-a-date-time" + " " +
            "12 Jan Jankowski 2435435432 Poznan Zlota 14 DEFAULT Max vehicles: 1 BICYCLE: ESI654 9  " + s +" not-a-date-time ");
        }

        BOOST_AUTO_TEST_CASE(RentRepositoryTestIndex12AndHigher) {

            BOOST_REQUIRE_EQUAL(teststorage->getRentRep()->testRentIndex12OrHigher(teststorage->getRentRep()->get(0)), false);
            teststorage->getRentRep()->add(testrent1);
            BOOST_REQUIRE_EQUAL(teststorage->getRentRep()->testRentIndex12OrHigher(teststorage->getRentRep()->get(1)), true);
        }

       BOOST_AUTO_TEST_CASE(RentRepositoryTestFindAll) {

            BOOST_REQUIRE_EQUAL(teststorage->getRentRep()->findAll(teststorage->getRentRep()->testRentIndex12OrHigher).size(), 0);
            teststorage->getRentRep()->add(testrent1);
            BOOST_REQUIRE_EQUAL(teststorage->getRentRep()->findAll(teststorage->getRentRep()->testRentIndex12OrHigher).size(), 1);
        }



    BOOST_AUTO_TEST_SUITE_END()

}