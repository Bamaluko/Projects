//
// Created by student on 29.04.2021.
//

#include <string>
#include <iostream>
#include <vector>
#include <boost/test/unit_test.hpp>
#include <managers/VehicleManager.h>
#include "repositories/StorageContainer.h"
#include "model/typedefs.h"
#include "model/Bicycle.h"
#include "model/ClientDefault.h"
#include "managers/ClientManager.h"

using namespace  std;


BOOST_AUTO_TEST_SUITE(TestSuiteVehicleManager)

    struct TestSuiteVehicleManagerFixture {
        const int testid = 12;
        AddressPtr testaddress1;
        ClientPtr testclient1;
        VehiclePtr testvehicle1;
        RentPtr testrent1;
        StorageContainer *teststorage;
        ClientTypePtr defaultclient;
        VehicleManager * manager;

        TestSuiteVehicleManagerFixture() {
            defaultclient = ClientTypePtr (new ClientDefault);
            testaddress1=std::make_shared <Address>("Poznan", "Zlota", "14");
            testclient1=std::make_shared <Client>((std::string)"Jan", (std::string)"Jankowski", (std::string)"2435435432", testaddress1, defaultclient);
            testvehicle1=std::make_shared <Bicycle>((std::string)"ESI654",  9);
            teststorage = new StorageContainer;
            testrent1 =std::make_shared <Rent>(12, testclient1, testvehicle1, boost::posix_time::not_a_date_time);
            manager = new VehicleManager(teststorage->getVehRep());
        }

        ~TestSuiteVehicleManagerFixture() {
            delete teststorage;
            delete manager;
        }

    };

    BOOST_FIXTURE_TEST_SUITE(TestSuiteClientManager, TestSuiteVehicleManagerFixture)

        BOOST_AUTO_TEST_CASE(GetVehicleTest) {

            BOOST_REQUIRE_EQUAL(manager->getVehicle("EPD237")->getPlateNumber(),"EPD237");
            BOOST_REQUIRE_EQUAL(manager->getVehicle("EPD237")->isArchive(),false);

        }

        BOOST_AUTO_TEST_CASE(GetVehicleNullPtrTest) {

            BOOST_REQUIRE_EQUAL(manager->getVehicle("EPP237"),nullptr);

        }

        BOOST_AUTO_TEST_CASE(RegisterBikeAlreadyExistingTest) {

            BOOST_REQUIRE_EQUAL(manager->registerBike("EPD237", 10),
                                teststorage->getVehRep()->get(0));

        }

        BOOST_AUTO_TEST_CASE(RegisterCarNewVehicleTest) {
            BOOST_REQUIRE_EQUAL(teststorage->getVehRep()->RepositorySize(),1);
            manager->registerCar((std::string)"EPD211", 12, 2000, B);
            BOOST_REQUIRE_EQUAL(teststorage->getVehRep()->RepositorySize(),2);
            BOOST_REQUIRE_EQUAL("EPD211",manager->getVehicle("EPD211")->getPlateNumber());

        }

        BOOST_AUTO_TEST_CASE(FindAllTest) {
            std::vector<VehiclePtr> vector;
            vector = manager->findVehicles(VehicleManager::findAll);
            BOOST_REQUIRE_EQUAL(vector.size(),1);
            manager->registerCar((std::string)"EPD211", 12, 2000, B);
            vector = manager->findVehicles(VehicleManager::findAll);
            BOOST_REQUIRE_EQUAL(vector.size(),2);
            manager->unregisterVehicle("EPD211");
            vector = manager->findVehicles(VehicleManager::findAll);
            BOOST_REQUIRE_EQUAL(vector.size(),1);


        }

        BOOST_AUTO_TEST_CASE(FindClientsTest) {
            std::vector<VehiclePtr> vector;
            vector = manager->findVehicles(VehicleManager::testVehicleRentalPrice10AndHigher);
            BOOST_REQUIRE_EQUAL(vector.size(),1);
            manager->registerCar((std::string)"EPD211", 12, 2000, B);
            vector = manager->findVehicles(VehicleManager::testVehicleRentalPrice10AndHigher);
            BOOST_REQUIRE_EQUAL(vector.size(),2);

        }


    BOOST_AUTO_TEST_SUITE_END()

}