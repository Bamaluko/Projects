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
#include "managers/RentManager.h"

using namespace  std;
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

BOOST_AUTO_TEST_SUITE(TestSuiteRentManager)

    struct TestSuiteRentManagerFixture {
        const int testid = 12;
        AddressPtr testaddress1;
        ClientPtr testclient1;
        VehiclePtr testvehicle1;
        VehiclePtr testvehicle2;
        RentRepoPtr rentrepo1;
        RentPtr testrent1;
        RentPtr testrent2;
        RentPtr testrent3;
        StorageContainer *teststorage;
        ClientTypePtr defaultclient;
        RentManager * manager;
        VehiclePtr testvehicle3;

        TestSuiteRentManagerFixture() {
            defaultclient = ClientTypePtr (new ClientDefault);
            testaddress1=std::make_shared <Address>("Poznan", "Zlota", "14");
            testclient1=std::make_shared <Client>((std::string)"Jan", (std::string)"Jankowski", (std::string)"2435435432", testaddress1, defaultclient);
            testvehicle1=std::make_shared <Bicycle>((std::string)"ESI654",  9);
            testvehicle2=std::make_shared <Car>((std::string)"ESI658",  15, 2000, B);
            testvehicle3=std::make_shared <Car>((std::string)"ESU654",  18, 2500, E);
            teststorage = new StorageContainer;
            testrent1 =std::make_shared <Rent>(12, testclient1, testvehicle1, pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(25)));
            testrent2 =std::make_shared <Rent>(112, testclient1, testvehicle2, pt::ptime(gr::date(2021,2,14),pt::hours(9)+pt::minutes(25)));
            testrent3 =std::make_shared <Rent>(113, testclient1, testvehicle2, boost::posix_time::not_a_date_time);
            rentrepo1 = std::make_shared<RentRepository>();
            rentrepo1->add(testrent1);
            rentrepo1->add(testrent2);
            manager = new RentManager(teststorage->getRentRep(), rentrepo1 );
        }

        ~TestSuiteRentManagerFixture() {
            delete teststorage;
            delete manager;
        }

    };

    BOOST_FIXTURE_TEST_SUITE(TestSuiteRentManager, TestSuiteRentManagerFixture)

        BOOST_AUTO_TEST_CASE(GetAllClientRentsTest) {

            BOOST_REQUIRE_EQUAL(manager->getAllClientRents(teststorage->getClientRep()->get(0)).size(),1);

        }
        BOOST_AUTO_TEST_CASE(GetVehicleRentTest) {

            BOOST_REQUIRE_EQUAL(manager->getVehicleRent(teststorage->getVehRep()->get(0))->getId(),1);

        }

        BOOST_AUTO_TEST_CASE(FindRentsByPredicateTest) {

            std::vector<RentPtr> vector;
            vector=manager->findRents(RentManager::rentIdValue100AndHigher);
            BOOST_REQUIRE_EQUAL(vector.size(),0);
            teststorage->getRentRep()->add(testrent3);
            vector=manager->findRents(RentManager::rentIdValue100AndHigher);
            BOOST_REQUIRE_EQUAL(vector.size(),1);

        }

        BOOST_AUTO_TEST_CASE(FindFindAllTest) {
            std::vector<RentPtr> vector;
            vector=manager->findRents(RentManager::findAll);
            BOOST_REQUIRE_EQUAL(vector.size(),1);
            teststorage->getRentRep()->add(testrent3);
            vector=manager->findRents(RentManager::findAll);
            BOOST_REQUIRE_EQUAL(vector.size(),2);
        }

        BOOST_AUTO_TEST_CASE(CheckBalanceTest) {
            testrent1->endRent(pt::ptime(gr::date(2021,2,17),pt::hours(9)+pt::minutes(26)));
            testrent2->endRent(pt::ptime(gr::date(2021,2,17),pt::hours(9)+pt::minutes(26)));
            BOOST_REQUIRE_EQUAL(testrent1->getRentDays(),5);
            BOOST_REQUIRE_EQUAL(testrent2->getRentDays(),4);
            BOOST_REQUIRE_EQUAL(manager->checkClientRentBalance(testclient1),144);
            BOOST_REQUIRE_EQUAL(manager->checkClientRentBalance(testclient1),144);
        }

        BOOST_AUTO_TEST_CASE(RentVehicleCanRentTest) {
            BOOST_REQUIRE_EQUAL(testclient1->isInArchive(), 0);
            BOOST_REQUIRE_EQUAL(testvehicle1->isArchive(), 0);
            BOOST_REQUIRE_EQUAL(manager->getAllClientRents(testclient1).size(), 0);
            BOOST_REQUIRE_EQUAL(manager->getVehicleRent(testvehicle1), nullptr);
            BOOST_REQUIRE_NE(manager->rentVehicle(120, testclient1, testvehicle1, pt::not_a_date_time), nullptr);
        }

        BOOST_AUTO_TEST_CASE(RentVehicleOverLimitTest) {
            BOOST_REQUIRE_NE(manager->rentVehicle(120, testclient1, testvehicle1, pt::not_a_date_time), nullptr);
            BOOST_REQUIRE_EQUAL(testclient1->isInArchive(), 0);
            BOOST_REQUIRE_EQUAL(testvehicle2->isArchive(), 0);
            BOOST_REQUIRE_EQUAL(manager->getAllClientRents(testclient1).size(), 1);
            BOOST_REQUIRE_EQUAL(manager->getVehicleRent(testvehicle2), nullptr);
            BOOST_REQUIRE_EQUAL(manager->rentVehicle(120, testclient1, testvehicle2, pt::not_a_date_time), nullptr);
        }

        BOOST_AUTO_TEST_CASE(RentVehicleVehicleIsArchiveTest) {
            testvehicle2->setArchive(1);
            BOOST_REQUIRE_EQUAL(testclient1->isInArchive(), 0);
            BOOST_REQUIRE_EQUAL(testvehicle2->isArchive(), 1);
            BOOST_REQUIRE_EQUAL(manager->getAllClientRents(testclient1).size(), 0);
            BOOST_REQUIRE_EQUAL(manager->getVehicleRent(testvehicle2), nullptr);
            BOOST_REQUIRE_EQUAL(manager->rentVehicle(120, testclient1, testvehicle2, pt::not_a_date_time), nullptr);
        }

        BOOST_AUTO_TEST_CASE(ReturnVehicleTestAndChangeTypeTest) {
            manager->rentVehicle(120, testclient1, testvehicle1, pt::ptime(gr::date(2021,2,14),pt::hours(9)+pt::minutes(25)));
            BOOST_REQUIRE_EQUAL(manager->checkClientRentBalance(testclient1),0);
            BOOST_REQUIRE_EQUAL(rentrepo1->RepositorySize(), 2);
            BOOST_REQUIRE_EQUAL(teststorage->getRentRep()->RepositorySize(), 2);
            manager->returnVehicle(testvehicle1, pt::ptime(gr::date(2021,2,28),pt::hours(8)+pt::minutes(25)));
            BOOST_REQUIRE_EQUAL(teststorage->getRentRep()->RepositorySize(), 1);
            BOOST_REQUIRE_EQUAL(manager->getVehicleRent(testvehicle1), nullptr);
            BOOST_REQUIRE_EQUAL(rentrepo1->RepositorySize(), 3);
            BOOST_REQUIRE_EQUAL(manager->checkClientRentBalance(testclient1),126);
            BOOST_REQUIRE_EQUAL(testclient1->getMaxVehicles(), 2);

;
        }


    BOOST_AUTO_TEST_SUITE_END()

}