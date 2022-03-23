//
// Created by student on 22.05.2021.
//

#include "boost/test/unit_test.hpp"
#include "Payment.h"
#include "Address.h"
#include "Account.h"
#include "ShortTermLoan.h"
#include "typedefs.h"

struct LoanTestSuiteFixture {
    double percentage = 0.02;
    double balance = 30000;
    pt::ptime beginTime;
    pt::ptime endTime;
    AddressPtr address;
    AccountPtr account;

    LoanTestSuiteFixture() {
        beginTime = pt::ptime(gr::date(2021,3,12), pt::hours(13) + pt::minutes(49));
        endTime = pt::ptime(gr::date(2022,3,12), pt::hours(13) + pt::minutes(49));
        address = std::make_shared<Address>("LA", "Rich", "22", "71");
        account = std::make_shared<Account>("Wojciech", "Baljon", "A1", address);
    }

    ~LoanTestSuiteFixture() = default;
};

BOOST_FIXTURE_TEST_SUITE(LoanTestSuite, LoanTestSuiteFixture)

    BOOST_AUTO_TEST_CASE(getPaymentTest) {
        LoanPtr loan = std::make_shared<ShortTermLoan>("1", beginTime, endTime, balance, account, percentage);
        pt::ptime payDate(gr::date(2021,3,14), pt::hours(13) + pt::minutes(49));
        BOOST_TEST_REQUIRE(loan->getPayment(0) == nullptr);
        loan->payMoney(1000, payDate);
        BOOST_TEST(loan->getPayment(0) != nullptr);
    }

    BOOST_AUTO_TEST_CASE(getInfoTest) {
        LoanPtr loan = std::make_shared<ShortTermLoan>("1", beginTime, endTime, balance, account, percentage);
        std::string expInfo = "POZYCZKA: 1 O BALANSIE: " + std::to_string(balance) + " I OPROCENTOWANIU : " + std::to_string(percentage);
        BOOST_TEST(loan->getInfo().compare(expInfo));
    }

    BOOST_AUTO_TEST_CASE(getDeadLineTest) {
        LoanPtr loan = std::make_shared<ShortTermLoan>("1", beginTime, endTime, balance, account, percentage);
        BOOST_TEST(loan->getDeadline() == endTime);
    }

BOOST_AUTO_TEST_SUITE_END()