//
// Created by student on 27.05.2021.
//
#include <boost/test/unit_test.hpp>
#include "model/typedefs.h"
#include "model/Account.h"
#include "model/Address.h"
#include "model/Bronze.h"
#include "model/Service.h"
#include "model/Deposit.h"
#include <memory>

using namespace std;


    struct TestSuiteDepositFixture {
        AddressPtr address1 ;
        AddressPtr address2 ;
        AccountPtr account1;
        AccountPtr account2;
        DepositPtr deposit1;
        DepositPtr deposit2;


        TestSuiteDepositFixture() {
            address1 = make_shared<Address>("Warszawa", "Zielona", "23", "14");
            account1 = make_shared<Account>("Piotr", "Mamos", "1", address1);
            address2 = make_shared<Address>("Przasnysz", "Polna", "12", "");
            account2 = make_shared<Account>("Jacek", "Wrubel", "1", address2);
            pt::ptime time1(gr::date(2021,3,22), pt::hours(13) + pt::minutes(49));
            pt::ptime time2(gr::date(2022,3,22), pt::hours(13) + pt::minutes(49));
            deposit1 = make_shared<Deposit>("1", time1, 100000, account1, 0.01, false);
            deposit2 = make_shared<Deposit>("2", time2, 100000, account2, 0.01, true);

        }

        ~TestSuiteDepositFixture() {

        }

    };

    BOOST_FIXTURE_TEST_SUITE(TestSuiteDeposit, TestSuiteDepositFixture)

        BOOST_AUTO_TEST_CASE(ParameterConstructorNegativeTest) {
            pt::ptime time3(gr::date(2023,3,22), pt::hours(13) + pt::minutes(49));
            DepositPtr deposit3;
            BOOST_REQUIRE_THROW(deposit3 = make_shared<Deposit>("", time3, 100000, account2, 0.01, true), std::logic_error);
            BOOST_REQUIRE_THROW(deposit3 = make_shared<Deposit>("3", time3, -1, account2, 0.01, true), std::logic_error);
            BOOST_REQUIRE_THROW(deposit3 = make_shared<Deposit>("3", pt::not_a_date_time, 100000, account2, 0.01, true), std::logic_error);
            BOOST_REQUIRE_THROW(deposit3 = make_shared<Deposit>("3", time3, 100000, nullptr, 0.01, true), std::logic_error);
            BOOST_REQUIRE_THROW(deposit3 = make_shared<Deposit>("3", time3, 100000, account2, -0.01, true), std::logic_error);
            BOOST_REQUIRE_THROW(deposit3 = make_shared<Deposit>("3", time3, 100000, account2, 1.01, true), std::logic_error);
        }

        BOOST_AUTO_TEST_CASE(GetBonusNoCapitalizationTest) {
            pt::ptime time1(gr::date(2021,3,22), pt::hours(13) + pt::minutes(49));
            BOOST_CHECK_EQUAL(deposit1->getBonus(time1),0);
            BOOST_CHECK_EQUAL(deposit1->getBonus(time1 + pt::hours(1752)),200);//1/5 roku
            BOOST_CHECK_EQUAL(deposit1->getBonus(time1 + pt::hours(8760)),1000);//rok
            BOOST_CHECK_EQUAL(deposit1->getBonus(time1 + pt::hours(10512)),1200);//6/5 roku
            BOOST_CHECK_EQUAL(deposit1->getBonus(time1 + pt::hours(17520)),2000);//2 lata
            BOOST_CHECK_EQUAL(deposit1->getBonus(time1 + pt::hours(21900)),2498.63);//2 i pol roku, liczba 365 jest nieparzysta, wiec zostanie zaokraglona w dol, zwrocona zostanie liczba zaokraglona do dwoch miejsc po przecinku

        }

        BOOST_AUTO_TEST_CASE(GetBonusWithCapitalizationTest) {
            pt::ptime time2(gr::date(2022,3,22), pt::hours(13) + pt::minutes(49));
            BOOST_CHECK_EQUAL(deposit2->getBonus(time2),0);
            BOOST_CHECK_EQUAL(deposit2->getBonus(time2 + pt::hours(1752)),200);//1/5 roku
            BOOST_CHECK_EQUAL(deposit2->getBonus(time2 + pt::hours(8760)),1000);//rok
            BOOST_CHECK_EQUAL(deposit2->getDepositBalance(time2 + pt::hours(10512)),101000);
            BOOST_CHECK_EQUAL(deposit2->getBonus(time2 + pt::hours(10512)),202);//6/5 roku, pozyczka odlicza po zakonczeniu roku bonus i dodaje go do balansu, zas nowy bonus nalicza od powiekszonego balansu
            BOOST_CHECK_EQUAL(deposit2->getBonus(time2 + pt::hours(17520)),1010);//2 lata
            BOOST_CHECK_EQUAL(deposit2->getDepositBalance(time2 + pt::hours(21900)),102010);
            BOOST_CHECK_EQUAL(deposit2->getBonus(time2 + pt::hours(21900)),508.65);//2 i pol roku

        }

        BOOST_AUTO_TEST_CASE(EndServiceTest) {
            pt::ptime time1(gr::date(2021,3,22), pt::hours(13) + pt::minutes(49));
            BOOST_CHECK_EQUAL(deposit1->getAccount()->getBalance(),0);//Sprawdzamy stan poczatkowy
            deposit1->endService(time1 + pt::hours(8760));
            BOOST_CHECK_EQUAL(deposit1->getAccount()->getBalance(),101000);//Sprawdzamy, czy pieniadze z depozytu zostaly odlozone na konto
            BOOST_CHECK_EQUAL(deposit1->getEndTime(),time1 + pt::hours(8760));
//            BOOST_CHECK_EQUAL(deposit1->getBalance(),0);

            pt::ptime time2(gr::date(2022,3,22), pt::hours(13) + pt::minutes(49));
            BOOST_CHECK_EQUAL(deposit2->getAccount()->getBalance(),0);
            deposit2->endService(time2+pt::hours(10512));
            BOOST_CHECK_EQUAL(deposit2->getAccount()->getBalance(),101202);
            BOOST_CHECK_EQUAL(deposit2->getEndTime(),time2 + pt::hours(10512));
//            BOOST_CHECK_EQUAL(deposit2->getBalance(),0);

        }

        BOOST_AUTO_TEST_CASE(DepositMoneyTest) {
            pt::ptime time1(gr::date(2021,3,22), pt::hours(13) + pt::minutes(49));
            BOOST_CHECK_EQUAL(deposit1->getAccount()->getBalance(),0);
            deposit1->depositMoney(10000, time1 + pt::hours(10512));
            BOOST_CHECK_EQUAL(deposit1->getAccount()->getBalance(),1200);//Sprawdzamy, czy bonus zostal przeniesiony na konto
            BOOST_CHECK_EQUAL(deposit1->getBeginTime(), time1 + pt::hours(10512));//Sprawdzamy, czy nowy beginTime zostal otwarty
            BOOST_CHECK_EQUAL(deposit1->getDepositBalance(deposit1->getBeginTime()),110000);//Upewniamy sie, ze nowy balance zostal naliczony

        }

    BOOST_AUTO_TEST_SUITE_END()
