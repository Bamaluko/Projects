//
// Created by student on 04.06.2021.
//

#include <boost/test/unit_test.hpp>
#include "typedefs.h"
#include "LongTermLoan.h"
#include "Account.h"

struct LongTermLoanTestSuiteFixture {
    pt::ptime beginTime;
    AddressPtr address;
    AccountPtr account;

    LongTermLoanTestSuiteFixture() {
        beginTime = pt::ptime(gr::date(2021,3,12), pt::hours(13) + pt::minutes(49));
        address = std::make_shared<Address>("LA", "Rich", "22", "71");
        account = std::make_shared<Account>("Wojciech", "Baljon", "A1", address);
    }
};

BOOST_FIXTURE_TEST_SUITE(LongTermLoanTestSuite, LongTermLoanTestSuiteFixture)

    BOOST_AUTO_TEST_CASE(ConstructorTest) {
        LongTermLoanPtr loan;
        loan = std::make_shared<LongTermLoan>("1", beginTime, account, SHORT);
        BOOST_TEST(loan->getBalance() == 107000);
        BOOST_TEST(loan->getPercentage() == 0.07);
        BOOST_TEST(loan->getDeadline() == (beginTime + gr::years(10)));
        loan = std::make_shared<LongTermLoan>("1", beginTime, account, MEDIUM_SHORT);
        BOOST_TEST(loan->getBalance() == 211000);
        BOOST_TEST(loan->getPercentage() == 0.055);
        BOOST_TEST(loan->getDeadline() == (beginTime + gr::years(15)));
        loan = std::make_shared<LongTermLoan>("1", beginTime, account, MEDIUM);
        BOOST_TEST(loan->getBalance() == 364700);
        BOOST_TEST(loan->getPercentage() == 0.042);
        BOOST_TEST(loan->getDeadline() == (beginTime + gr::years(20)));
        loan = std::make_shared<LongTermLoan>("1", beginTime, account, LONG);
        BOOST_TEST(loan->getBalance() == 622200);
        BOOST_TEST(loan->getPercentage() == 0.037);
        BOOST_TEST(loan->getDeadline() == (beginTime + gr::years(25)));
        loan = std::make_shared<LongTermLoan>("1", beginTime, account, VERY_LONG);
        BOOST_TEST(loan->getBalance() == 927000);
        BOOST_TEST(loan->getPercentage() == 0.03);
        BOOST_TEST(loan->getDeadline() == (beginTime + gr::years(30)));
    }

    BOOST_AUTO_TEST_CASE(ConstructorNegative) {
        LongTermLoanPtr loan;
        BOOST_REQUIRE_THROW(loan = std::make_shared<LongTermLoan>("", beginTime, account, SHORT), std::logic_error);
        BOOST_REQUIRE_THROW(loan = std::make_shared<LongTermLoan>("1", pt::not_a_date_time, account, SHORT), std::logic_error);
        BOOST_REQUIRE_THROW(loan = std::make_shared<LongTermLoan>("1", beginTime, nullptr, SHORT), std::logic_error);
    }

    //---------END SERVICE METHOD----------

    BOOST_AUTO_TEST_CASE(endServiceLongTermLoanTest) {
        LongTermLoanPtr loan = std::make_shared<LongTermLoan>("1", beginTime, account, SHORT);
        pt::ptime payDate(gr::date(2021,3,14), pt::hours(13) + pt::minutes(49));//Data pierwszej wplaty
        pt::ptime payDate2(gr::date(2021,3,18), pt::hours(13) + pt::minutes(49));//Data drugiej wplaty
        BOOST_REQUIRE_EQUAL(loan->getEndTime(),boost::posix_time::not_a_date_time);//Sprawdzamy, czy endTime dla uslugi jest wciaz nieustawiony
        loan->payMoney(50000, payDate);//Ta wplata powinna obnizyc balance pozyczki, ale pozyczka powinna pozostac niesplacona
        BOOST_REQUIRE_EQUAL(loan->getBalance(),57000);//Sprawdzamy, czy pieniadze zostaly wykorzystane do splaty pozyczki
        BOOST_REQUIRE_EQUAL(loan->getEndTime(),boost::posix_time::not_a_date_time);//Sprawdzamy, czy endTime dla uslugi jest wciaz nieustawiony
        loan->payMoney(57000, payDate2);//Tym razem pozyczka powinna zostac splacona i powinnma sie uruchomic metoda endService
        BOOST_REQUIRE_EQUAL(loan->getBalance(),0);//Sprawdzamy, czy pieniadze zostaly wykorzystane do splaty pozyczki
        BOOST_REQUIRE_EQUAL(loan->getEndTime(),payDate2);//Sprawdzamy, czy endTime dla uslugi zostal ustawiony na date ostatniej wplaty
    }

    BOOST_AUTO_TEST_CASE(endServiceLongTermLoanWhileOverpayingTest) {
        //Ten test sprawdzi, czy w sytuacji, gdy przeplacimy w ostatniej splacie, pozyczka zakonczy sie prawidlowo, a nadplata zostanie nam przelana na konto
        LongTermLoanPtr loan = std::make_shared<LongTermLoan>("1", beginTime, account, SHORT);
        pt::ptime payDate(gr::date(2021,3,14), pt::hours(13) + pt::minutes(49));
        BOOST_REQUIRE_EQUAL(account->getBalance(),0);
        loan->payMoney(110000, payDate);
        BOOST_REQUIRE_EQUAL(loan->getBalance(),0);
        BOOST_REQUIRE_EQUAL(loan->getEndTime(),payDate);
        BOOST_REQUIRE_EQUAL(account->getBalance(),3000);//700 to kwota nadwyzki w naszej splacie pozyczki. Powinna ona zostac nam zrocona przez bank na konto

    }

    BOOST_AUTO_TEST_CASE(endServiceLongTermLoanWithPenealtyTestSHORT) {
        //SHORT
        LongTermLoanPtr loan = std::make_shared<LongTermLoan>("1", beginTime, account, SHORT);
        pt::ptime payDate(gr::date(2031,3,22), pt::hours(13) + pt::minutes(49));
        loan->payMoney(107000, payDate);
        BOOST_REQUIRE_EQUAL(loan->getEndTime(),boost::posix_time::not_a_date_time);
        BOOST_REQUIRE_EQUAL(loan->getBalance(),120);
        BOOST_REQUIRE_EQUAL(loan->getDeadline(),payDate + boost::posix_time::hours(8640));
        loan->payMoney(120, payDate + boost::posix_time::hours(12));
        BOOST_REQUIRE_EQUAL(loan->getEndTime(),payDate + boost::posix_time::hours(12));
        BOOST_REQUIRE_EQUAL(loan->getBalance(),0);
    }

    BOOST_AUTO_TEST_CASE(endServiceLongTermLoanWithPenealtyTestMEDIUM_SHORT) {
        //MEDIUM_SHORT
        LongTermLoanPtr loan = std::make_shared<LongTermLoan>("1", beginTime, account, MEDIUM_SHORT);
        pt::ptime payDate(gr::date(2036,3,22), pt::hours(13) + pt::minutes(49));
        loan->payMoney(211000, payDate);
        BOOST_REQUIRE_EQUAL(loan->getEndTime(),boost::posix_time::not_a_date_time);
        BOOST_REQUIRE_EQUAL(loan->getBalance(),150);
        BOOST_REQUIRE_EQUAL(loan->getDeadline(),payDate + boost::posix_time::hours(8640));
        loan->payMoney(150, payDate + boost::posix_time::hours(12));
        BOOST_REQUIRE_EQUAL(loan->getEndTime(),payDate + boost::posix_time::hours(12));
        BOOST_REQUIRE_EQUAL(loan->getBalance(),0);
    }

    BOOST_AUTO_TEST_CASE(endServiceLongTermLoanWithPenealtyTestMEDIUM) {
        //MEDIUM
        LongTermLoanPtr loan = std::make_shared<LongTermLoan>("1", beginTime, account, MEDIUM);
        pt::ptime payDate(gr::date(2041,3,22), pt::hours(13) + pt::minutes(49));
        loan->payMoney(364700, payDate);
        BOOST_REQUIRE_EQUAL(loan->getEndTime(),boost::posix_time::not_a_date_time);
        BOOST_REQUIRE_EQUAL(loan->getBalance(),200);
        BOOST_REQUIRE_EQUAL(loan->getDeadline(),payDate + boost::posix_time::hours(8640));
        loan->payMoney(200, payDate + boost::posix_time::hours(12));
        BOOST_REQUIRE_EQUAL(loan->getEndTime(),payDate + boost::posix_time::hours(12));
        BOOST_REQUIRE_EQUAL(loan->getBalance(),0);
    }

    BOOST_AUTO_TEST_CASE(endServiceLongTermLoanWithPenealtyTestLONG) {
        //LONG
        LongTermLoanPtr loan = std::make_shared<LongTermLoan>("1", beginTime, account, LONG);
        pt::ptime payDate(gr::date(2046,3,22), pt::hours(13) + pt::minutes(49));
        loan->payMoney(622200, payDate);
        BOOST_REQUIRE_EQUAL(loan->getEndTime(),boost::posix_time::not_a_date_time);
        BOOST_REQUIRE_EQUAL(loan->getBalance(),500);
        BOOST_REQUIRE_EQUAL(loan->getDeadline(),payDate + boost::posix_time::hours(8640));
        loan->payMoney(500, payDate + boost::posix_time::hours(12));
        BOOST_REQUIRE_EQUAL(loan->getEndTime(),payDate + boost::posix_time::hours(12));
        BOOST_REQUIRE_EQUAL(loan->getBalance(),0);
    }

    BOOST_AUTO_TEST_CASE(endServiceLongTermLoanWithPenealtyTestVERY_LONG) {
        //VERY_LONG
        LongTermLoanPtr loan = std::make_shared<LongTermLoan>("1", beginTime, account, VERY_LONG);
        pt::ptime payDate(gr::date(2051,3,22), pt::hours(13) + pt::minutes(49));
        loan->payMoney(927000, payDate);
        BOOST_REQUIRE_EQUAL(loan->getEndTime(),boost::posix_time::not_a_date_time);
        BOOST_REQUIRE_EQUAL(loan->getBalance(), 1000);
        BOOST_REQUIRE_EQUAL(loan->getDeadline(),payDate + boost::posix_time::hours(8640));
        loan->payMoney(1000, payDate + boost::posix_time::hours(12));
        BOOST_REQUIRE_EQUAL(loan->getEndTime(),payDate + boost::posix_time::hours(12));
        BOOST_REQUIRE_EQUAL(loan->getBalance(),0);
    }

BOOST_AUTO_TEST_SUITE_END()
