//
// Created by student on 29.03.2021.
//

#include <boost/test/unit_test.hpp>
#include "model/Client.h"
#include "model/Address.h"
#include "model/Bicycle.h"
#include <vector>
#include "model/ClientDefault.h"
#include "model/ClientGold.h"
#include "model/ClientDiamond.h"
#include "model/ClientPlatinum.h"
#include "model/ClientBronze.h"
#include "model/ClientSilver.h"
#include "repositories/StorageContainer.h"
#include "model/Car.h"

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

BOOST_AUTO_TEST_SUITE(TestSuiteClient)

    struct TestSuiteClientFixture {
        const std::string testFirstName = "Adam";
        const std::string testLastName = "Adamski";
        const std::string testPersonalID = "1435435435";
        AddressPtr testaddress1;
        AddressPtr testaddress2;
        VehiclePtr testvehicle1;
        ClientTypePtr defaultclient;
        ClientTypePtr silverclient;
        ClientTypePtr platinumclient;
        ClientTypePtr diamondclient;

        TestSuiteClientFixture() {
            defaultclient = ClientTypePtr (new ClientDefault);
            silverclient = ClientTypePtr (new ClientSilver);
            platinumclient = ClientTypePtr (new ClientPlatinum);
            diamondclient = ClientTypePtr (new ClientDiamond);
            testaddress1 = std::make_shared <Address>("Wroclaw", "Piekna", "23");
            testaddress2 = std::make_shared <Address>("London", "Rue Morgue", "13");
            testvehicle1 = std::make_shared <Car>("ESI142" , 8, 2000, C);
        }

        ~TestSuiteClientFixture() {
        }

    };

    BOOST_FIXTURE_TEST_SUITE(TestSuiteClient, TestSuiteClientFixture)

    BOOST_AUTO_TEST_CASE(ParameterConstrutorTest) {

        ClientPtr c = std::make_shared <Client>(testFirstName, testLastName, testPersonalID, testaddress1, defaultclient);
        BOOST_CHECK_EQUAL( (std::string)testFirstName, c->getFirstName());
        BOOST_CHECK_EQUAL((std::string)testLastName , c->getLastName());
        BOOST_CHECK_EQUAL((std::string)testPersonalID , c->getPersonalID());
        BOOST_CHECK_EQUAL(c->getClientinfo() , "Adam Adamski 1435435435 Wroclaw Piekna 23 DEFAULT Max vehicles: 1");
        BOOST_CHECK_EQUAL(testaddress1 , c->getAdres());
        BOOST_REQUIRE_EQUAL(c->isInArchive(),false);
    }

//    BOOST_AUTO_TEST_CASE(getFullClientInfoTest) {
//        Client c(testFirstName, testLastName, testPersonalID, testaddress1);
//        Rent testrent1(543 , &c , testvehicle1, boost::posix_time::not_a_date_time);
//        BOOST_CHECK_EQUAL(c.getFullClientinfo() , "Adam Adamski 1435435435 Wroclaw Piekna 23 | Rent IDs: 543");
//    }

    BOOST_AUTO_TEST_CASE(AssertionsTests) {
        BOOST_TEST_CHECK(1.0/3.0 == 0.333, boost::test_tools::tolerance(0.002));
        BOOST_TEST(true);
    }


    BOOST_AUTO_TEST_CASE(SetFirstNameEmptyString) {
        ClientPtr client1 = std::make_shared <Client>(testFirstName, testLastName, testPersonalID, testaddress1, defaultclient);
        BOOST_REQUIRE_THROW(client1->setFirstName(""), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(SetFirstNameConformance) {
        ClientPtr client1 = std::make_shared <Client>(testFirstName, testLastName, testPersonalID, testaddress1, defaultclient);
        client1->setFirstName("Piotr");
        BOOST_REQUIRE_EQUAL(client1->getFirstName(), "Piotr");
    }

    BOOST_AUTO_TEST_CASE(SetLastNameEmptyString) {
        ClientPtr c = std::make_shared <Client>(testFirstName, testLastName, testPersonalID, testaddress1, defaultclient);
        BOOST_REQUIRE_THROW(c->setLastName(""), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(SetLastNameConformance) {
        ClientPtr client1 = std::make_shared <Client>(testFirstName, testLastName, testPersonalID, testaddress1, defaultclient);
        client1->setLastName("Piotrowski");
        BOOST_REQUIRE_EQUAL(client1->getLastName(), "Piotrowski");
    }

    BOOST_AUTO_TEST_CASE(SetEmptyAddress) {
        BOOST_REQUIRE_THROW(AddressPtr testaddress3 = std::make_shared <Address>("", "", ""), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(SetAddress) {
        ClientPtr client1 = std::make_shared <Client>(testFirstName, testLastName, testPersonalID, testaddress1, defaultclient);
        client1->setAdres(testaddress2);
        BOOST_REQUIRE_EQUAL(client1->getAdres(), testaddress2);
    }

        BOOST_AUTO_TEST_CASE(SetClientTypeTest) {
            ClientPtr client1 = std::make_shared <Client>(testFirstName, testLastName, testPersonalID, testaddress1, defaultclient);
            BOOST_REQUIRE_EQUAL(client1->getClientinfo(), "Adam Adamski 1435435435 Wroclaw Piekna 23 DEFAULT Max vehicles: 1");
            ClientTypePtr gold1(new ClientGold);
            client1->setClientType(gold1);
            BOOST_REQUIRE_EQUAL(client1->getClientinfo(), "Adam Adamski 1435435435 Wroclaw Piekna 23 GOLD Max vehicles: 4");
        }

        BOOST_AUTO_TEST_CASE(GetMaxVehiclesTest) {
            ClientPtr client1 = std::make_shared <Client>(testFirstName, testLastName, testPersonalID, testaddress1, defaultclient);
            BOOST_REQUIRE_EQUAL(client1->getMaxVehicles(), 1);
            ClientTypePtr bronze1(new ClientBronze);
            client1->setClientType(bronze1);
            BOOST_REQUIRE_EQUAL(client1->getMaxVehicles(), 2);
            ClientTypePtr silver1(new ClientSilver);
            client1->setClientType(silver1);
            BOOST_REQUIRE_EQUAL(client1->getMaxVehicles(), 3);
            ClientTypePtr gold1(new ClientGold);
            client1->setClientType(gold1);
            BOOST_REQUIRE_EQUAL(client1->getMaxVehicles(), 4);
            ClientTypePtr platinum1(new ClientPlatinum);
            client1->setClientType(platinum1);
            BOOST_REQUIRE_EQUAL(client1->getMaxVehicles(), 5);
            ClientTypePtr diamond1(new ClientDiamond);
            client1->setClientType(diamond1);
            BOOST_REQUIRE_EQUAL(client1->getMaxVehicles(), 10);
        }

        BOOST_AUTO_TEST_CASE(ApplyDiscountTestCarClassTypeDefault) {
            ClientPtr client1 = std::make_shared <Client>(testFirstName, testLastName, testPersonalID, testaddress1, defaultclient);
            RentPtr rent1 = std::make_shared <Rent>(12, client1, testvehicle1, pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(25)));
            rent1->endRent(pt::ptime(gr::date(2021,2,16),pt::hours(9)+pt::minutes(26)));
            BOOST_REQUIRE_EQUAL(client1->applyDiscount(rent1->getRentCost()), 0);
            BOOST_REQUIRE_EQUAL(rent1->getRentCost(), 57.6);

        }

        BOOST_AUTO_TEST_CASE(ApplyDiscountTestCarClassTypeSilver) {
            ClientPtr client1 = std::make_shared <Client>(testFirstName, testLastName, testPersonalID, testaddress1, silverclient);
            RentPtr rent1 = std::make_shared <Rent>(12, client1, testvehicle1, pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(25)));
            rent1->endRent(pt::ptime(gr::date(2021,2,16),pt::hours(9)+pt::minutes(26)));
            BOOST_REQUIRE_EQUAL(client1->applyDiscount(rent1->getRentCost()), 6);
            BOOST_REQUIRE_EQUAL(rent1->getRentCost(), 51.6);

        }

        BOOST_AUTO_TEST_CASE(ApplyDiscountTestCarClassTypePlatinum) {
            ClientPtr client1 = std::make_shared <Client>(testFirstName, testLastName, testPersonalID, testaddress1, platinumclient);
            RentPtr rent1 = std::make_shared <Rent>(12, client1, testvehicle1, pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(25)));
            rent1->endRent(pt::ptime(gr::date(2021,2,16),pt::hours(9)+pt::minutes(26)));
            BOOST_TEST_CHECK(rent1->getRentCost() == 51.84, boost::test_tools::tolerance(0.001));

        }

        BOOST_AUTO_TEST_CASE(ApplyDiscountTestCarClassTypeDiamond) {
            ClientPtr client1 = std::make_shared <Client>(testFirstName, testLastName, testPersonalID, testaddress1, diamondclient);
            RentPtr rent1 = std::make_shared <Rent>(12, client1, testvehicle1, pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(25)));
            rent1->endRent(pt::ptime(gr::date(2021,3,13),pt::hours(9)+pt::minutes(26)));
            BOOST_TEST_CHECK(rent1->getRentCost() == 292.32, boost::test_tools::tolerance(0.001));

        }

        BOOST_AUTO_TEST_CASE(ArchiveSetterTest) {
            ClientPtr client1 = std::make_shared <Client>(testFirstName, testLastName, testPersonalID, testaddress1, diamondclient);
            BOOST_REQUIRE_EQUAL(client1->isInArchive(),false);
            client1->setArchive(true);
            BOOST_REQUIRE_EQUAL(client1->isInArchive(),true);
        }

BOOST_AUTO_TEST_SUITE_END()

}