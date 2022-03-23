//
// Created by student on 15.04.2021.
//

#include <string>
#include <boost/test/unit_test.hpp>
#include "repositories/StorageContainer.h"
#include "repositories/VehicleRepository.h"
#include "model/typedefs.h"
#include "model/Bicycle.h"
#include "model/ClientDefault.h"

using namespace  std;


BOOST_AUTO_TEST_SUITE(TestSuiteVehicleRepository)

    struct TestSuiteVehicleRepositoryFixture {
        const int testid = 12;
        AddressPtr testaddress1;
        ClientPtr testclient1;
        VehiclePtr testvehicle1;
        StorageContainer *teststorage;

        TestSuiteVehicleRepositoryFixture() {
            testaddress1=std::make_shared <Address>("Poznan", "Zlota", "14");
            ClientTypePtr defaultclient(new ClientDefault);
            testclient1=std::make_shared <Client>((std::string)"Jan", (std::string)"Jankowski", (std::string)"2435435432", testaddress1, defaultclient);
            testvehicle1=std::make_shared <Bicycle>((std::string)"ESI654",  9);
            teststorage = new StorageContainer;
        }

        ~TestSuiteVehicleRepositoryFixture() {
            delete teststorage;
        }

    };


    BOOST_FIXTURE_TEST_SUITE(TestSuiteVehicleRepository, TestSuiteVehicleRepositoryFixture)


        BOOST_AUTO_TEST_CASE(VehicleRepositorySizeTest) {

            BOOST_REQUIRE_EQUAL(teststorage->getVehRep()->RepositorySize() , 1);
            teststorage->getVehRep()->add(testvehicle1);
            BOOST_REQUIRE_EQUAL(teststorage->getVehRep()->RepositorySize() , 2);

        }


        BOOST_AUTO_TEST_CASE(GetVehicleTest) {

            BOOST_REQUIRE_EQUAL(teststorage->getVehRep()->get(0)->getVehicleInfo(), "BICYCLE: EPD237 10 ");

        }

        BOOST_AUTO_TEST_CASE(GetVehicleTestIndexBelow0) {

            BOOST_REQUIRE_EQUAL(teststorage->getVehRep()->get(-3) , nullptr);

        }

        BOOST_AUTO_TEST_CASE(GetVehicleTestIndexOverSize) {

            BOOST_REQUIRE_EQUAL(teststorage->getVehRep()->get(1) , nullptr);

        }

        BOOST_AUTO_TEST_CASE(AddVehicleTest) {

            teststorage->getVehRep()->add(testvehicle1);
            BOOST_REQUIRE_EQUAL(teststorage->getVehRep()->RepositorySize() , 2);
            BOOST_REQUIRE_EQUAL(teststorage->getVehRep()->get(1)->getVehicleInfo(), "BICYCLE: ESI654 9 ");

        }

        BOOST_AUTO_TEST_CASE(AddVehicleTestNullPtr) {

            teststorage->getVehRep()->add(nullptr);
            BOOST_REQUIRE_EQUAL(teststorage->getVehRep()->RepositorySize() , 1);
            BOOST_REQUIRE_EQUAL(teststorage->getVehRep()->get(1) , nullptr);

        }

        BOOST_AUTO_TEST_CASE(RemoveVehicleTest) {

            teststorage->getVehRep()->add(testvehicle1);
            BOOST_REQUIRE_EQUAL(teststorage->getVehRep()->RepositorySize() , 2);
            teststorage->getVehRep()->remove(testvehicle1);
            BOOST_REQUIRE_EQUAL(teststorage->getVehRep()->get(1) , nullptr);
            BOOST_REQUIRE_EQUAL(teststorage->getVehRep()->RepositorySize() , 1);

        }

        BOOST_AUTO_TEST_CASE(RemoveVehicleTestNullPtr) {

            teststorage->getVehRep()->add(testvehicle1);
            BOOST_REQUIRE_EQUAL(teststorage->getVehRep()->RepositorySize() , 2);
            teststorage->getVehRep()->remove(nullptr);
            BOOST_REQUIRE_EQUAL(teststorage->getVehRep()->get(1) , testvehicle1);
            BOOST_REQUIRE_EQUAL(teststorage->getVehRep()->RepositorySize() , 2);

        }

        BOOST_AUTO_TEST_CASE(VehicleReportTest) {

            teststorage->getVehRep()->add(testvehicle1);
            BOOST_REQUIRE_EQUAL(teststorage->getVehRep()->Raport() , "BICYCLE: EPD237 10  BICYCLE: ESI654 9  ");

        }

//        BOOST_AUTO_TEST_CASE(VehicleRepositoryTestPrice10AndAbove) {
//
//            BOOST_REQUIRE_EQUAL(teststorage->getVehRep().testVehiclePrise10OrHigher(teststorage->getVehRep().getVehicle(0)), true);
//            teststorage->getVehRep().getVehicle(0)->setBasePrice(9);
//            BOOST_REQUIRE_EQUAL(teststorage->getClientRep().testClientTwoRents(teststorage->getClientRep().getClient(0)), false);
//
//        }

        BOOST_AUTO_TEST_CASE(ClientRepositoryTestFindAll) {

            teststorage->getVehRep()->add(testvehicle1);
            teststorage->getVehRep()->add(testvehicle1);
            BOOST_REQUIRE_EQUAL(teststorage->getVehRep()->findAll(teststorage->getVehRep()->testVehiclePrise10OrHigher).size(), 1);
        }



    BOOST_AUTO_TEST_SUITE_END()

}