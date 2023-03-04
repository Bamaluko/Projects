//
// Created by student on 29.04.2021.
//

#include <string>
#include <iostream>
#include <vector>
#include <boost/test/unit_test.hpp>
#include "repositories/StorageContainer.h"
#include "model/typedefs.h"
#include "model/Bicycle.h"
#include "model/ClientDefault.h"
#include "managers/ClientManager.h"

using namespace  std;


BOOST_AUTO_TEST_SUITE(TestSuiteClientManager)

    struct TestSuiteClientManagerFixture {
        const int testid = 12;
        AddressPtr testaddress1;
        ClientPtr testclient1;
        VehiclePtr testvehicle1;
        RentPtr testrent1;
        StorageContainer *teststorage;
        ClientTypePtr defaultclient;
        ClientManager * manager;

        TestSuiteClientManagerFixture() {
            defaultclient = ClientTypePtr (new ClientDefault);
            testaddress1=std::make_shared <Address>("Poznan", "Zlota", "14");
            testclient1=std::make_shared <Client>((std::string)"Jan", (std::string)"Jankowski", (std::string)"2435435432", testaddress1, defaultclient);
            testvehicle1=std::make_shared <Bicycle>((std::string)"ESI654",  9);
            teststorage = new StorageContainer;
            testrent1 =std::make_shared <Rent>(12, testclient1, testvehicle1, boost::posix_time::not_a_date_time);
            manager = new ClientManager(teststorage->getClientRep());
        }

        ~TestSuiteClientManagerFixture() {
            delete teststorage;
            delete manager;
        }

    };

    BOOST_FIXTURE_TEST_SUITE(TestSuiteClientManager, TestSuiteClientManagerFixture)

        BOOST_AUTO_TEST_CASE(GetClientTest) {

            BOOST_REQUIRE_EQUAL(manager->getClient("1435435435")->getPersonalID(),"1435435435");
            BOOST_REQUIRE_EQUAL(manager->getClient("1435435435")->getFirstName(),"Adam");

        }

        BOOST_AUTO_TEST_CASE(GetClientNullPtrTest) {

            BOOST_REQUIRE_EQUAL(manager->getClient("1435435400"),nullptr);

        }

        BOOST_AUTO_TEST_CASE(RegisterClientAlreadyExistingTest) {

            BOOST_REQUIRE_EQUAL(manager->registerClient((std::string)"Adam", (std::string)"Adamski", (std::string)"1435435435", testaddress1, defaultclient),
                                teststorage->getClientRep()->findByPersonalId("1435435435"));

        }

        BOOST_AUTO_TEST_CASE(RegisterClientNewClientTest) {
            BOOST_REQUIRE_EQUAL(teststorage->getClientRep()->RepositorySize(),1);
            manager->registerClient((std::string)"Adam", (std::string)"Adamczyk", (std::string)"1435435400", testaddress1, defaultclient);
            BOOST_REQUIRE_EQUAL(teststorage->getClientRep()->RepositorySize(),2);
            BOOST_REQUIRE_EQUAL("Adamczyk",manager->getClient("1435435400")->getLastName());

        }

        BOOST_AUTO_TEST_CASE(FindAllTest) {
            std::vector<ClientPtr> vector;
            vector = manager->findClients(ClientManager::findAll);
            BOOST_REQUIRE_EQUAL(vector.size(),1);
            manager->registerClient((std::string)"Adam", (std::string)"Adamczyk", (std::string)"1435435400", testaddress1, defaultclient);
            vector = manager->findClients(ClientManager::findAll);
            BOOST_REQUIRE_EQUAL(vector.size(),2);
            manager->unregisterClient("1435435400");
            vector = manager->findClients(ClientManager::findAll);
            BOOST_REQUIRE_EQUAL(vector.size(),1);


        }

        BOOST_AUTO_TEST_CASE(FindClientsTest) {
            std::vector<ClientPtr> vector;
            vector = manager->findClients(ClientManager::testClientMaxRentsIsOne);
            BOOST_REQUIRE_EQUAL(vector.size(),1);
            manager->registerClient((std::string)"Adam", (std::string)"Adamczyk", (std::string)"1435435400", testaddress1, defaultclient);
            vector = manager->findClients(ClientManager::findAll);
            BOOST_REQUIRE_EQUAL(vector.size(),2);

        }


    BOOST_AUTO_TEST_SUITE_END()

}