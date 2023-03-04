//
// Created by student on 04.06.2021.
//

#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "Mortgage.h"
#include "Account.h"

struct MortgageTestSuiteFixture {
    double percentage = 0.02;
    double balance = 30000;
    pt::ptime beginTime;
    pt::ptime endTime;
    AddressPtr address;
    AccountPtr account;

    MortgageTestSuiteFixture() {
        beginTime = pt::ptime(gr::date(2021,3,12), pt::hours(13) + pt::minutes(49));
        endTime = pt::ptime(gr::date(2022,3,12), pt::hours(13) + pt::minutes(49));
        address = std::make_shared<Address>("LA", "Rich", "22", "71");
        account = std::make_shared<Account>("Wojciech", "Baljon", "A1", address);
    }

    ~MortgageTestSuiteFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(MortgageTestSuite, MortgageTestSuiteFixture)

    BOOST_AUTO_TEST_CASE(ConstructorNegativeTest) {
        MortgagePtr mortgage;
        BOOST_REQUIRE_THROW(mortgage = std::make_shared<Mortgage>("", beginTime, endTime, 100000, account, 0.2, address), std::logic_error);
        BOOST_REQUIRE_THROW(mortgage = std::make_shared<Mortgage>("1", pt::not_a_date_time, endTime, 100000, account, 0.2, address), std::logic_error);
        BOOST_REQUIRE_THROW(mortgage = std::make_shared<Mortgage>("1", beginTime, pt::not_a_date_time, 100000, account, 0.2, address), std::logic_error);
        BOOST_REQUIRE_THROW(mortgage = std::make_shared<Mortgage>("1", beginTime, endTime, 0, account, 0.2, address), std::logic_error);
        BOOST_REQUIRE_THROW(mortgage = std::make_shared<Mortgage>("1", beginTime, endTime, -5, account, 0.2, address), std::logic_error);
        BOOST_REQUIRE_THROW(mortgage = std::make_shared<Mortgage>("1", beginTime, endTime, 100000, account, -1, address), std::logic_error);
        BOOST_REQUIRE_THROW(mortgage = std::make_shared<Mortgage>("1", beginTime, endTime, 100000, account, 2, address), std::logic_error);
        BOOST_REQUIRE_THROW(mortgage = std::make_shared<Mortgage>("1", beginTime, endTime, 100000, account, 0.2, nullptr), std::logic_error);
        BOOST_REQUIRE_THROW(mortgage = std::make_shared<Mortgage>("1", beginTime, endTime, 100000, nullptr, 0.2, nullptr), std::logic_error);
        BOOST_REQUIRE_THROW(mortgage = std::make_shared<Mortgage>("1", beginTime, endTime, 100000, nullptr, 0.2, address), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(ConstructorAndGetAddress) {
        MortgagePtr mortgage;
        mortgage = std::make_shared<Mortgage>("1", beginTime, endTime, 100000, account, 0.2, address);
        BOOST_TEST(mortgage->getHouseAddress() == address);
    }

    BOOST_AUTO_TEST_CASE(endServiceMortgageTest) {
        MortgagePtr mortgage = std::make_shared<Mortgage>("1", beginTime, endTime, 30000, account, 0.01, address);
        pt::ptime payDate(gr::date(2021,3,14), pt::hours(13) + pt::minutes(49));//Data pierwszej wplaty
        pt::ptime payDate2(gr::date(2021,3,18), pt::hours(13) + pt::minutes(49));//Data drugiej wplaty
        BOOST_REQUIRE_EQUAL(mortgage->getEndTime(),boost::posix_time::not_a_date_time);//Sprawdzamy, czy endTime dla uslugi jest wciaz nieustawiony
        mortgage->payMoney(15000, payDate);//Ta wplata powinna obnizyc balance pozyczki, ale pozyczka powinna pozostac niesplacona
        BOOST_REQUIRE_EQUAL(mortgage->getBalance(),15300);//Sprawdzamy, czy pieniadze zostaly wykorzystane do splaty pozyczki
        BOOST_REQUIRE_EQUAL(mortgage->getEndTime(),boost::posix_time::not_a_date_time);//Sprawdzamy, czy endTime dla uslugi jest wciaz nieustawiony
        mortgage->payMoney(15300, payDate2);//Tym razem pozyczka powinna zostac splacona i powinnma sie uruchomic metoda endService
        BOOST_REQUIRE_EQUAL(mortgage->getBalance(),0);//Sprawdzamy, czy pieniadze zostaly wykorzystane do splaty pozyczki
        BOOST_REQUIRE_EQUAL(mortgage->getEndTime(),payDate2);//Sprawdzamy, czy endTime dla uslugi zostal ustawiony na date ostatniej wplaty
    }

    BOOST_AUTO_TEST_CASE(endServiceMortgageWhileOverpayingTest) {
        //Ten test sprawdzi, czy w sytuacji, gdy przeplacimy w ostatniej splacie, pozyczka zakonczy sie prawidlowo, a nadplata zostanie nam przelana na konto
        MortgagePtr mortgage = std::make_shared<Mortgage>("1", beginTime, endTime, 30000, account, 0.01, address);
        pt::ptime payDate(gr::date(2021,3,14), pt::hours(13) + pt::minutes(49));
        BOOST_REQUIRE_EQUAL(account->getBalance(),0);
        mortgage->payMoney(31000, payDate);
        BOOST_REQUIRE_EQUAL(mortgage->getBalance(),0);
        BOOST_REQUIRE_EQUAL(mortgage->getEndTime(),payDate);
        BOOST_REQUIRE_EQUAL(account->getBalance(),700);//700 to kwota nadwyzki w naszej splacie pozyczki. Powinna ona zostac nam zrocona przez bank na konto

    }

    BOOST_AUTO_TEST_CASE(endServiceMortgageWithPenealtyTest) {
        //W tym tescie splacimy pozyczke zbyt pozno, co docelowo ma nam naliczyc odpowiednia kare (10$ za kazdy dzien)
        MortgagePtr mortgage = std::make_shared<Mortgage>("1", beginTime, endTime, 30000, account, 0.01, address);
        pt::ptime payDate(gr::date(2022,3,22), pt::hours(13) + pt::minutes(49));
        mortgage->payMoney(30300, payDate);
        BOOST_REQUIRE_EQUAL(mortgage->getEndTime(),boost::posix_time::not_a_date_time);//Sprawdzamy, czy endTime dla uslugi jest wciaz nieustawiony, czyli czy pozyczka nie jest zakonczona
        BOOST_REQUIRE_EQUAL(mortgage->getBalance(),200);
        BOOST_REQUIRE_EQUAL(mortgage->getDeadline(),payDate + boost::posix_time::hours(720));//Sprawdzamy, czy ustawiono nowy, prawidlowy czas splaty kary (360 dni)
        mortgage->payMoney(200, payDate + boost::posix_time::hours(12));
        BOOST_REQUIRE_EQUAL(mortgage->getEndTime(),payDate + boost::posix_time::hours(12));//Sprawdzamy, czy splata zaleglosci konczy pozyczke
        BOOST_REQUIRE_EQUAL(mortgage->getBalance(),0);
    }

BOOST_AUTO_TEST_SUITE_END()
