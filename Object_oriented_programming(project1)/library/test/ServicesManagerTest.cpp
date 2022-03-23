//
// Created by student on 10.06.2021.
//

#include <string>
#include <memory>
#include <boost/test/unit_test.hpp>
#include "repositories/AccountRepository.h"
#include "model/typedefs.h"
#include "ServicesManager.h"

using namespace  std;


struct TestSuiteServicesManagerFixture {
    AddressPtr address1;
    AddressPtr address2;
    pt::ptime beginTime;
    ServicesManagerPtr manager;
    AccountPtr account;
    AccountPtr account2;

    TestSuiteServicesManagerFixture() {
        beginTime = pt::ptime(gr::date(2021,3,12), pt::hours(13) + pt::minutes(49));
        address1 = make_shared <Address>("Warszawa", "Zielona", "23", "14");
        address2 = make_shared <Address>("Wroclaw", "Blekitna", "13", "31");
        account = make_shared<Account>("Wojciech", "Baljon", "A1", address1);
        account2 = make_shared<Account>("Kacper", "Kuchciak", "A2", address2);
        manager = make_shared<ServicesManager>();
        manager->createLongTermLoan("L1", beginTime, account, SHORT);
        manager->createDeposit("D1", beginTime, 500000, account2, 0.02, true);
    }

    ~TestSuiteServicesManagerFixture() = default;

};


BOOST_FIXTURE_TEST_SUITE(TestSuiteServicesManager, TestSuiteServicesManagerFixture)

    BOOST_AUTO_TEST_CASE(getServiceTest) {

        BOOST_REQUIRE_EQUAL(manager->getService("L1")->getAccount(), account);
        BOOST_REQUIRE_EQUAL(manager->getService("L1")->getId(), "L1");
        BOOST_REQUIRE_EQUAL(manager->getService("D1")->getAccount(), account2);
        BOOST_REQUIRE_EQUAL(manager->getService("D1")->getId(), "D1");
        BOOST_REQUIRE_EQUAL(manager->getService("ELO"), nullptr);
    }

    BOOST_AUTO_TEST_CASE(createLoangTermLoanTest) {

        manager->createLongTermLoan("L2", beginTime, account, SHORT);
        BOOST_REQUIRE_EQUAL(manager->getService("L2")->getAccount(), account);
        BOOST_REQUIRE_EQUAL(manager->getService("L2")->getId(), "L2");

    }

    BOOST_AUTO_TEST_CASE(endDepositTest) {

        manager->endDeposit(manager->getService("D1"),beginTime);
        BOOST_REQUIRE_EQUAL(manager->getService("D1"),nullptr);
        BOOST_REQUIRE_EQUAL(manager->getServiceArchive("D1")->getId(),"D1");

    }

    BOOST_AUTO_TEST_CASE(getAllAccountServicesTest) {

        BOOST_REQUIRE_EQUAL(manager->getAllAccountServices(account).size(),1);
        manager->createLongTermLoan("L2", beginTime, account, SHORT);
        BOOST_REQUIRE_EQUAL(manager->getAllAccountServices(account).size(),2);
    }

    BOOST_AUTO_TEST_CASE(checkActivityTest) {

        manager->endDeposit(manager->getService("D1"),beginTime);
        BOOST_REQUIRE_EQUAL(manager->checkActivity(account2),500000);
    }

    BOOST_AUTO_TEST_CASE(changeClientTypeTest) {

        manager->createDeposit("D2", beginTime, 1000000, account2, 0.02, true);
        manager->endDeposit(manager->getService("D2"),beginTime);
        BOOST_REQUIRE_EQUAL(account2->getMaxDeposits(),5);
    }

    BOOST_AUTO_TEST_CASE(payMoneyLoanTest) {
        BOOST_REQUIRE_EQUAL(manager->getService("L1")->getBalance(),107000);
        manager->payMoneyLoan(manager->getService("L1"), 1000, beginTime);
        BOOST_REQUIRE_EQUAL(manager->getService("L1")->getBalance(),106000);

    }




BOOST_AUTO_TEST_SUITE_END()
