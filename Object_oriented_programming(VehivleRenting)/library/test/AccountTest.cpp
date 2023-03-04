//
// Created by student on 18.05.2021.
//

#include <boost/test/unit_test.hpp>
#include "model/Account.h"
#include "model/Address.h"
#include "model/Bronze.h"
#include "model/Silver.h"
#include "model/Gold.h"
#include "model/typedefs.h"

using namespace  std;


    struct TestSuiteAccountFixture {
        AddressPtr address1 ;
        AddressPtr address2 ;
        AccountPtr account1;



        TestSuiteAccountFixture() {
            address1 = make_shared<Address>("Warszawa", "Zielona", "23", "14");
            address2 = make_shared<Address>("Poznan", "Brunatna", "12", "9");
            account1 = make_shared<Account>("Piotr", "Mamos", "1", address1);
        }

        ~TestSuiteAccountFixture() {

        }

    };

    BOOST_FIXTURE_TEST_SUITE(TestSuiteAccount, TestSuiteAccountFixture)

        BOOST_AUTO_TEST_CASE(ParameterConstructorAndGettersTest) {

            AccountPtr account2 (new Account("Jacek", "Wrubel", "2", address2));
            BOOST_REQUIRE_EQUAL(account2->getBalance(), 0);
            BOOST_REQUIRE_EQUAL(account2->getFirstName(), "Jacek");
            BOOST_REQUIRE_EQUAL(account2->getLastName(), "Wrubel");
            BOOST_REQUIRE_EQUAL(account2->getId(), "2");
            BOOST_REQUIRE_EQUAL(account2->getAccountType()->getType(), "Bronze");
            BOOST_REQUIRE_EQUAL(account2->getAddress(), address2);
            BOOST_REQUIRE_EQUAL(account2->isArchive(), false);
        }

        BOOST_AUTO_TEST_CASE(ParameterConstructorNegativeTest) {
            BOOST_CHECK_THROW(AccountPtr account2 (new Account("", "Wrubel", "2", address2)),std::logic_error);
            BOOST_CHECK_THROW(AccountPtr account2 (new Account("Jacek", "", "2", address2)),std::logic_error);
            BOOST_CHECK_THROW(AccountPtr account2 (new Account("Jacek", "Wrubel", "", address2)),std::logic_error);
            BOOST_CHECK_THROW(AccountPtr account2 (new Account("Jacek", "Wrubel", "2", nullptr)),std::logic_error);

        }

        BOOST_AUTO_TEST_CASE(SettersNegativeTest) {
            BOOST_CHECK_THROW(account1->setFirstName(""),std::logic_error);
            BOOST_CHECK_THROW(account1->setLastName(""),std::logic_error);
            BOOST_CHECK_THROW(account1->setAddress(nullptr),std::logic_error);
            account1->putMoneyIn(1000);
            BOOST_REQUIRE_EQUAL(account1->getBalance(),1000);
            BOOST_CHECK_THROW(account1->takeMoneyOut(2000),std::logic_error);

        }

        BOOST_AUTO_TEST_CASE(BasicSettersTest) {

            AccountPtr account2 (new Account("Jacek", "Wrubel", "2", address2));
            account2->setFirstName("Adam");
            BOOST_REQUIRE_EQUAL(account2->getFirstName(), "Adam");
            account2->setLastName("Wrubelkowski");
            BOOST_REQUIRE_EQUAL(account2->getLastName(), "Wrubelkowski");
            account2->setAddress(address1);
            BOOST_REQUIRE_EQUAL(account2->getAddress(), address1);
            AccountTypePtr silver;
            silver = make_shared<Silver>();
            account2->setAccountType(silver);
            BOOST_REQUIRE_EQUAL(account2->getAccountType()->getType(), "Silver");
            account2->setIsArchive(true);
            BOOST_REQUIRE_EQUAL(account2->isArchive(), true);
        }

        BOOST_AUTO_TEST_CASE(MoneyTransferingTest) {
            BOOST_REQUIRE_EQUAL(account1->getBalance(), 0);
            account1->putMoneyIn(100);
            BOOST_REQUIRE_EQUAL(account1->getBalance(), 100);
            account1->takeMoneyOut(20);
            BOOST_REQUIRE_EQUAL(account1->getBalance(), 80);
            BOOST_REQUIRE_THROW(account1->takeMoneyOut(100),std::logic_error);
            BOOST_REQUIRE_EQUAL(account1->getBalance(), 80);

        }
    BOOST_AUTO_TEST_SUITE_END()
