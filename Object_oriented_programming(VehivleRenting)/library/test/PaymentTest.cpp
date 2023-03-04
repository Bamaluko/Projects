//
// Created by student on 22.05.2021.
//

#include "boost/test/unit_test.hpp"
#include "Payment.h"
#include "typedefs.h"

BOOST_AUTO_TEST_SUITE(PaymentTestSuite)

    BOOST_AUTO_TEST_CASE(ConstructorAndGetters) {
        int id = 1;
        double money = 223;
        pt::ptime time(gr::date(2021,3,12), pt::hours(13) + pt::minutes(49));
        PaymentPtr payment = std::make_shared<Payment>(id, money, time);
        BOOST_TEST(payment->getId() == id);
        BOOST_TEST(payment->getMoney() == money);
        BOOST_TEST(payment->getTime() == time);
    }

BOOST_AUTO_TEST_SUITE_END()