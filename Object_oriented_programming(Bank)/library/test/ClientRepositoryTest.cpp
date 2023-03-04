//
// Created by student on 14.04.2021.
//


#include <string>
#include <boost/test/unit_test.hpp>
#include "repositories/StorageContainer.h"
#include "model/typedefs.h"
#include "model/Bicycle.h"
#include "model/ClientDefault.h"
#include "model/FirstNamePredicate.h"
#include "model/LastNamePredicate.h"

using namespace  std;


BOOST_AUTO_TEST_SUITE(TestSuiteClientRepository)

    struct TestSuiteClientRepositoryFixture {
        const int testid = 12;
          AddressPtr testaddress1;
          ClientPtr testclient1;
          VehiclePtr testvehicle1;
          StorageContainer *teststorage;

        TestSuiteClientRepositoryFixture() {
            testaddress1=std::make_shared <Address>("Poznan", "Zlota", "14");
            ClientTypePtr defaultclient(new ClientDefault);
            testclient1=std::make_shared <Client>((std::string)"Jan", (std::string)"Jankowski", (std::string)"2435435432", testaddress1, defaultclient);
            testvehicle1=std::make_shared <Bicycle>((std::string)"ESI654",  9);
            teststorage = new StorageContainer;
        }

        ~TestSuiteClientRepositoryFixture() {
            delete teststorage;
        }

    };


    BOOST_FIXTURE_TEST_SUITE(TestSuiteClientRepository, TestSuiteClientRepositoryFixture)


        BOOST_AUTO_TEST_CASE(ClientRepositorySizeTest) {
            BOOST_REQUIRE_EQUAL(teststorage->getClientRep()->RepositorySize() , 1);
            teststorage->getClientRep()->add(testclient1);
            BOOST_REQUIRE_EQUAL(teststorage->getClientRep()->RepositorySize() , 2);

        }


        BOOST_AUTO_TEST_CASE(GetClientTest) {

             BOOST_REQUIRE_EQUAL(teststorage->getClientRep()->get(0)->getClientinfo() , "Adam Adamski 1435435435 Wroclaw Piekna 23 DEFAULT Max vehicles: 1");

         }

        BOOST_AUTO_TEST_CASE(GetClientTestIndexBelow0) {

            BOOST_REQUIRE_EQUAL(teststorage->getClientRep()->get(-3) , nullptr);

        }

        BOOST_AUTO_TEST_CASE(GetClientTestIndexOverSize) {

            BOOST_REQUIRE_EQUAL(teststorage->getClientRep()->get(1) , nullptr);

        }

        BOOST_AUTO_TEST_CASE(AddClientTest) {

            teststorage->getClientRep()->add(testclient1);
            BOOST_REQUIRE_EQUAL(teststorage->getClientRep()->RepositorySize() , 2);
            BOOST_REQUIRE_EQUAL(teststorage->getClientRep()->get(1)->getClientinfo() , "Jan Jankowski 2435435432 Poznan Zlota 14 DEFAULT Max vehicles: 1");

        }

        BOOST_AUTO_TEST_CASE(AddClientTestNullPtr) {

            teststorage->getClientRep()->add(nullptr);
            BOOST_REQUIRE_EQUAL(teststorage->getClientRep()->RepositorySize() , 1);
            BOOST_REQUIRE_EQUAL(teststorage->getClientRep()->get(1) , nullptr);

        }

        BOOST_AUTO_TEST_CASE(RemoveClientTest) {

            teststorage->getClientRep()->add(testclient1);
            BOOST_REQUIRE_EQUAL(teststorage->getClientRep()->RepositorySize() , 2);
            teststorage->getClientRep()->remove(testclient1);
            BOOST_REQUIRE_EQUAL(teststorage->getClientRep()->get(1) , nullptr);
            BOOST_REQUIRE_EQUAL(teststorage->getClientRep()->RepositorySize() , 1);

        }

        BOOST_AUTO_TEST_CASE(RemoveClientTestNullPtr) {

            teststorage->getClientRep()->add(testclient1);
            BOOST_REQUIRE_EQUAL(teststorage->getClientRep()->RepositorySize() , 2);
            teststorage->getClientRep()->remove(nullptr);
            BOOST_REQUIRE_EQUAL(teststorage->getClientRep()->get(1) , testclient1);
            BOOST_REQUIRE_EQUAL(teststorage->getClientRep()->RepositorySize() , 2);

        }

        BOOST_AUTO_TEST_CASE(ClientReportTest) {

            teststorage->getClientRep()->add(testclient1);
            BOOST_REQUIRE_EQUAL(teststorage->getClientRep()->Raport() , "Adam Adamski 1435435435 Wroclaw Piekna 23 DEFAULT Max vehicles: 1 Jan Jankowski 2435435432 Poznan Zlota 14 DEFAULT Max vehicles: 1 ");

        }

        BOOST_AUTO_TEST_CASE(FindCientByNameTest) {

            teststorage->getClientRep()->add(testclient1);
            BOOST_REQUIRE_EQUAL((teststorage->getClientRep()->findAll(FirstNamePredicate("Jan"))).size(), 1);
            BOOST_REQUIRE_EQUAL((teststorage->getClientRep()->findAll(FirstNamePredicate("Adam"))).size(), 1);
            BOOST_REQUIRE_EQUAL((teststorage->getClientRep()->findAll(FirstNamePredicate("a"))).size(), 2);
            BOOST_REQUIRE_EQUAL((teststorage->getClientRep()->findAll(FirstNamePredicate("z"))).size(), 0);

        }

        BOOST_AUTO_TEST_CASE(FindCientByLastNameTest) {

            teststorage->getClientRep()->add(testclient1);
            BOOST_REQUIRE_EQUAL((teststorage->getClientRep()->findAll(LastNamePredicate("Adam"))).size(), 1);
            BOOST_REQUIRE_EQUAL((teststorage->getClientRep()->findAll(LastNamePredicate("Jankow"))).size(), 1);
            BOOST_REQUIRE_EQUAL((teststorage->getClientRep()->findAll(LastNamePredicate("a"))).size(), 2);
            BOOST_REQUIRE_EQUAL((teststorage->getClientRep()->findAll(LastNamePredicate("z"))).size(), 0);

        }

//        BOOST_AUTO_TEST_CASE(ClientRepositoryTest2Rents) {
//
//            BOOST_REQUIRE_EQUAL(teststorage->getClientRep().testClientTwoRents(teststorage->getClientRep().getClient(0)), false);
//            RentPtr rent1;
//            rent1 = new Rent(12, teststorage->getClientRep().getClient(0), testvehicle1, boost::posix_time::not_a_date_time);
//            BOOST_REQUIRE_EQUAL(teststorage->getClientRep().testClientTwoRents(teststorage->getClientRep().getClient(0)), true);
//            delete rent1;
//
//        }

//        BOOST_AUTO_TEST_CASE(ClientRepositoryTestFindAll) {
//
//            BOOST_REQUIRE_EQUAL(teststorage->getClientRep().testClientTwoRents(teststorage->getClientRep().getClient(0)), false);
//            RentPtr rent1;
//            rent1 = new Rent(12, teststorage->getClientRep().getClient(0), testvehicle1, boost::posix_time::not_a_date_time);
//            teststorage->getClientRep().addClient(testclient1);
//            BOOST_REQUIRE_EQUAL(teststorage->getClientRep().findAll(teststorage->getClientRep().testClientTwoRents).size(), 1);
//            delete rent1;
//
//        }



    BOOST_AUTO_TEST_SUITE_END()

}