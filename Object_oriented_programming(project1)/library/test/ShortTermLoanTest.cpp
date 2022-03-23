//
// Created by student on 04.06.2021.
//

#include "boost/test/unit_test.hpp"
#include "Address.h"
#include "Account.h"
#include "ShortTermLoan.h"

BOOST_AUTO_TEST_SUITE(ShortTermLoanTestSuite)

    BOOST_AUTO_TEST_CASE(endServiceForShortLoanTest) {
        pt::ptime beginTime(gr::date(2021,3,12), pt::hours(13) + pt::minutes(49));
        pt::ptime endTime(gr::date(2022,3,12), pt::hours(13) + pt::minutes(49));
        AddressPtr address = std::make_shared<Address>("LA", "Rich", "22", "71");
        AccountPtr account = std::make_shared<Account>("Wojciech", "Baljon", "A1", address);
        LoanPtr loan = std::make_shared<ShortTermLoan>("1", beginTime, endTime, 30000, account, 0.01);
        pt::ptime payDate(gr::date(2021,3,14), pt::hours(13) + pt::minutes(49));//Data pierwszej wplaty
        pt::ptime payDate2(gr::date(2021,3,18), pt::hours(13) + pt::minutes(49));//Data drugiej wplaty
        BOOST_REQUIRE_EQUAL(loan->getEndTime(),boost::posix_time::not_a_date_time);//Sprawdzamy, czy endTime dla uslugi jest wciaz nieustawiony
        loan->payMoney(15000, payDate);//Ta wplata powinna obnizyc balance pozyczki, ale pozyczka powinna pozostac niesplacona
        BOOST_REQUIRE_EQUAL(loan->getBalance(),15300);//Sprawdzamy, czy pieniadze zostaly wykorzystane do splaty pozyczki
        BOOST_REQUIRE_EQUAL(loan->getEndTime(),boost::posix_time::not_a_date_time);//Sprawdzamy, czy endTime dla uslugi jest wciaz nieustawiony
        loan->payMoney(15300, payDate2);//Tym razem pozyczka powinna zostac splacona i powinnma sie uruchomic metoda endService
        BOOST_REQUIRE_EQUAL(loan->getBalance(),0);//Sprawdzamy, czy pieniadze zostaly wykorzystane do splaty pozyczki
        BOOST_REQUIRE_EQUAL(loan->getEndTime(),payDate2);//Sprawdzamy, czy endTime dla uslugi zostal ustawiony na date ostatniej wplaty
    }

    BOOST_AUTO_TEST_CASE(endServiceForShortLoanWhileOverpayingTest) {
        //Ten test sprawdzi, czy w sytuacji, gdy przeplacimy w ostatniej splacie, pozyczka zakonczy sie prawidlowo, a nadplata zostanie nam przelana na konto
        pt::ptime beginTime(gr::date(2021,3,12), pt::hours(13) + pt::minutes(49));
        pt::ptime endTime(gr::date(2022,3,12), pt::hours(13) + pt::minutes(49));
        AddressPtr address = std::make_shared<Address>("LA", "Rich", "22", "71");
        AccountPtr account = std::make_shared<Account>("Wojciech", "Baljon", "A1", address);
        LoanPtr loan = std::make_shared<ShortTermLoan>("1", beginTime, endTime, 30000, account, 0.01);
        pt::ptime payDate(gr::date(2021,3,14), pt::hours(13) + pt::minutes(49));
        BOOST_REQUIRE_EQUAL(account->getBalance(),0);
        loan->payMoney(31000, payDate);
        BOOST_REQUIRE_EQUAL(loan->getBalance(),0);
        BOOST_REQUIRE_EQUAL(loan->getEndTime(),payDate);
        BOOST_REQUIRE_EQUAL(account->getBalance(),700);//700 to kwota nadwyzki w naszej splacie pozyczki. Powinna ona zostac nam zrocona przez bank na konto

    }

    BOOST_AUTO_TEST_CASE(endServiceForShortLoanWithPenealtyTest) {
        //W tym tescie splacimy pozyczke zbyt pozno, co docelowo ma nam naliczyc odpowiednia kare (10$ za kazdy dzien)
        pt::ptime beginTime(gr::date(2021,3,12), pt::hours(13) + pt::minutes(49));
        pt::ptime endTime(gr::date(2022,3,12), pt::hours(13) + pt::minutes(49));
        AddressPtr address = std::make_shared<Address>("LA", "Rich", "22", "71");
        AccountPtr account = std::make_shared<Account>("Wojciech", "Baljon", "A1", address);
        LoanPtr loan = std::make_shared<ShortTermLoan>("1", beginTime, endTime, 30000, account, 0.01);
        pt::ptime payDate(gr::date(2022,3,22), pt::hours(13) + pt::minutes(49));
        loan->payMoney(30300, payDate);
        BOOST_REQUIRE_EQUAL(loan->getEndTime(),boost::posix_time::not_a_date_time);//Sprawdzamy, czy endTime dla uslugi jest wciaz nieustawiony, czyli czy pozyczka nie jest zakonczona
        BOOST_REQUIRE_EQUAL(loan->getBalance(),100);
        BOOST_REQUIRE_EQUAL(loan->getDeadline(),payDate + boost::posix_time::hours(8640));//Sprawdzamy, czy ustawiono nowy, prawidlowy czas splaty kary (360 dni)
        loan->payMoney(100, payDate + boost::posix_time::hours(12));
        BOOST_REQUIRE_EQUAL(loan->getEndTime(),payDate + boost::posix_time::hours(12));//Sprawdzamy, czy splata zaleglosci konczy pozyczke
        BOOST_REQUIRE_EQUAL(loan->getBalance(),0);
    }

BOOST_AUTO_TEST_SUITE_END()