//
// Created by student on 07.04.2021.
//

#include <boost/test/unit_test.hpp>
#include "model/Client.h"
#include "model/Address.h"
#include "model/Rent.h"
#include "model/Vehicle.h"
#include "model/Bicycle.h"
#include <boost/date_time.hpp>
#include "model/ClientDefault.h"
#include "model/RentException.h"
namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

BOOST_AUTO_TEST_SUITE(TestSuiteRent)

    struct TestSuiteRentFixture {
        const int testid = 12;
        AddressPtr testaddress1;
        ClientPtr  testclient1;
        VehiclePtr testvehicle1;
        ClientTypePtr defaultclient;

        TestSuiteRentFixture() {
            defaultclient = ClientTypePtr (new ClientDefault);
            testaddress1=std::make_shared <Address>("Wroclaw", "Piekna", "23");
            testclient1=std::make_shared <Client>((std::string)"Adam", (std::string)"Adamski", (std::string)"1435435435", testaddress1, defaultclient);
            testvehicle1=std::make_shared <Bicycle>((std::string)"EPD237",  10);
        }

        ~TestSuiteRentFixture() {

        }

    };

    BOOST_FIXTURE_TEST_SUITE(TestSuiteRent, TestSuiteRentFixture)

    BOOST_AUTO_TEST_CASE(ParameterConstrutorTest) {

            RentPtr rent1 = std::make_shared <Rent>(testid, testclient1, testvehicle1, boost::posix_time::not_a_date_time);
            BOOST_CHECK_EQUAL(rent1->getId(), testid);
            BOOST_CHECK_EQUAL(testclient1, rent1->getClient());
            BOOST_CHECK_EQUAL(testvehicle1, rent1->getVehicle());
            std::stringstream ss;
            ss << boost::posix_time::second_clock::local_time();
            std::string s = ss.str();
            BOOST_CHECK_EQUAL(rent1->getRentInfo(), "12 Adam Adamski 1435435435 Wroclaw Piekna 23 DEFAULT Max vehicles: 1 BICYCLE: EPD237 10  " + s + " not-a-date-time");
            BOOST_REQUIRE_THROW(RentPtr rent2 = std::make_shared <Rent>(15, nullptr, testvehicle1, boost::posix_time::not_a_date_time), std::logic_error);

    }

//    BOOST_AUTO_TEST_CASE(PassingRentToClientTest) {
//
//        Rent rent1(testid, testclient1, testvehicle1, boost::posix_time::not_a_date_time);
//        BOOST_CHECK_EQUAL(testclient1->getCurrentRents().back() , &rent1);
//
//    }

//    BOOST_AUTO_TEST_CASE(IsRentingWorkingTest) {
//
//        BOOST_CHECK_EQUAL(testvehicle1->isRented() , "AVAILABLE");
//        Rent rent1(testid, testclient1, testvehicle1 ,boost::posix_time::not_a_date_time);
//        BOOST_CHECK_EQUAL(testvehicle1->isRented() , "RENTED");
//
//    }

    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestDefaultBeginTime) {

        RentPtr r = std::make_shared <Rent>(testid, testclient1, testvehicle1, boost::posix_time::not_a_date_time);
        boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
        BOOST_TEST_REQUIRE(!r->getBeginTime().is_not_a_date_time());
        boost::posix_time::time_period skew = boost::posix_time::time_period(r->getBeginTime(), now);
        BOOST_TEST((skew.length().hours()==0 && skew.length().minutes()==0));
    }

    BOOST_AUTO_TEST_CASE(ParameterConstrutorTestGivenBeginTime) {

        RentPtr r = std::make_shared <Rent>(testid, testclient1, testvehicle1, pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(25)));
        BOOST_CHECK_EQUAL(r->getBeginTime() ,  pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(25)));
    }

    BOOST_AUTO_TEST_CASE(EndRentTestBasis) {

        RentPtr r = std::make_shared <Rent>(testid, testclient1, testvehicle1, boost::posix_time::not_a_date_time);
        BOOST_REQUIRE_EQUAL(r->getEndTime(),  pt::not_a_date_time);
        r->endRent(pt::not_a_date_time);
        BOOST_CHECK_EQUAL(r->getEndTime() , pt::second_clock::local_time());
    }

    BOOST_AUTO_TEST_CASE(EndRentTestSetGivenEndTimeAfterBeginTime) {

        RentPtr r = std::make_shared <Rent>(testid, testclient1, testvehicle1, boost::posix_time::not_a_date_time);
        BOOST_REQUIRE_EQUAL(r->getEndTime(),  pt::not_a_date_time);
        r->endRent(pt::ptime(gr::date(2022,2,13),pt::hours(9)+pt::minutes(25)));
        BOOST_CHECK_EQUAL(r->getEndTime() , pt::ptime(gr::date(2022,2,13),pt::hours(9)+pt::minutes(25)));

    }

    BOOST_AUTO_TEST_CASE(EndRentTestSetGivenEndTimeEqualsBeginTime) {

        RentPtr r = std::make_shared <Rent>(testid, testclient1, testvehicle1, pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(25)));
        BOOST_REQUIRE_EQUAL(r->getEndTime(),  pt::not_a_date_time);
        r->endRent(pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(25)));
        BOOST_CHECK_EQUAL(r->getEndTime() , pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(25)));

    }

    BOOST_AUTO_TEST_CASE(EndRentTestSetGivenEndTimeBeforeBeginTime) {

        RentPtr r = std::make_shared <Rent>(testid, testclient1, testvehicle1, pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(25)));
        BOOST_REQUIRE_EQUAL(r->getEndTime(),  pt::not_a_date_time);
        r->endRent(pt::ptime(gr::date(2020,2,13),pt::hours(9)+pt::minutes(25)));
        BOOST_CHECK_EQUAL(r->getEndTime() , r->getBeginTime());

    }

    BOOST_AUTO_TEST_CASE(RentDaysTestRentNotEnded) {

        RentPtr r = std::make_shared <Rent>(testid, testclient1, testvehicle1, pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(25)));
        BOOST_REQUIRE_EQUAL(r->getRentDays(),  0);

    }

    BOOST_AUTO_TEST_CASE(RentDaysTestRentEndedWithinMinute) {

        RentPtr r = std::make_shared <Rent>(testid, testclient1, testvehicle1, pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(25)));
        r->endRent(pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(26)));
        BOOST_REQUIRE_EQUAL(r->getRentDays(),  0);

    }

    BOOST_AUTO_TEST_CASE(RentDaysTestRentEndedAfter1m) {

        RentPtr r = std::make_shared <Rent>(testid, testclient1, testvehicle1, pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(25)));
        r->endRent(pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(27)+pt::seconds(1)));
        BOOST_REQUIRE_EQUAL(r->getRentDays(),  1);

    }

    BOOST_AUTO_TEST_CASE(RentDaysTestRentEndedAfter23h59m) {

        RentPtr r = std::make_shared <Rent>(testid, testclient1, testvehicle1, pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(25)));
        r->endRent(pt::ptime(gr::date(2021,2,13),pt::hours(23)+pt::minutes(59)+pt::seconds(1)));
        BOOST_REQUIRE_EQUAL(r->getRentDays(),  1);

    }

    BOOST_AUTO_TEST_CASE(RentDaysTestRentEndedAfter24h00m) {

        RentPtr r = std::make_shared <Rent>(testid, testclient1, testvehicle1, pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(25)));
        r->endRent(pt::ptime(gr::date(2021,2,14),pt::hours(9)+pt::minutes(25)));
        BOOST_REQUIRE_EQUAL(r->getRentDays(),  2);

    }

//    BOOST_AUTO_TEST_CASE(RentEndingTest) {
//
//        Rent *r = new Rent(testid, testclient1, testvehicle1, pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(25)));
//        r->endRent(pt::ptime(gr::date(2021,2,14),pt::hours(9)+pt::minutes(25)));
//        BOOST_REQUIRE_EQUAL(r->getVehicle()->isRented(),  "AVAILABLE");
//        bool isRentedByClient = false;
//        for (unsigned int i = 0; i < r->getClient()->getCurrentRents().size(); i++)
//        {
//            if(r->getClient()->getCurrentRents().at(i) == r)
//            {
//                isRentedByClient=true;
//            }
//        }
//
//        BOOST_CHECK_EQUAL(isRentedByClient,  false);
//
//    }

    BOOST_AUTO_TEST_CASE(RentCostWithinOneMinuteTest) {

        RentPtr r = std::make_shared <Rent>(testid, testclient1, testvehicle1, pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(25)));
        r->endRent(pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(26)));
        BOOST_REQUIRE_EQUAL(r->getRentCost(),  0);

    }

    BOOST_AUTO_TEST_CASE(RentCostOverOneMinuteTest) {

        RentPtr r = std::make_shared <Rent>(testid, testclient1, testvehicle1, pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(25)));
        r->endRent(pt::ptime(gr::date(2021,2,17),pt::hours(9)+pt::minutes(26)));
        BOOST_REQUIRE_EQUAL(r->getRentCost(),  r->getRentDays()*r->getVehicle()->BasePrice());

    }

    BOOST_AUTO_TEST_CASE(RentCostTestRentCostIsPermanentWhenVehiclePriceChanged) {

        RentPtr r = std::make_shared <Rent>(testid, testclient1, testvehicle1, pt::ptime(gr::date(2021,2,13),pt::hours(9)+pt::minutes(25)));
        r->endRent(pt::ptime(gr::date(2021,2,17),pt::hours(9)+pt::minutes(26)));
        int cost = r->getRentDays()*r->getVehicle()->BasePrice();
        r->getVehicle()->setBasePrice(12);
        BOOST_REQUIRE_EQUAL(r->getRentCost(),  cost);

    }



    BOOST_AUTO_TEST_SUITE_END()

}