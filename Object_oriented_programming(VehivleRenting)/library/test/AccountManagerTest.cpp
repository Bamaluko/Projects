//
// Created by student on 04.06.2021.
//

#include <string>
#include <memory>
#include <boost/test/unit_test.hpp>
#include "repositories/AccountRepository.h"
#include "model/typedefs.h"
#include "managers/AccountManager.h"

using namespace  std;


    struct TestSuiteAccountManagerFixture {
        AddressPtr address1;
        AddressPtr address2;
        AddressPtr address3;
        AccountManagerPtr manager;

        TestSuiteAccountManagerFixture() {
            address1 = make_shared <Address>("Warszawa", "Zielona", "23", "14");
            address2 = make_shared <Address>("Wroclaw", "Blekitna", "13", "31");\
            address3 = make_shared <Address>("Gdansk", "Srebrna", "11", "");
            manager = make_shared<AccountManager>();
            manager->registerAccount("Piotr", "Mamos", "1", address1);
            manager->registerAccount("Jacek", "Wrubel", "2", address2);
        }

        ~TestSuiteAccountManagerFixture() = default;

    };


    BOOST_FIXTURE_TEST_SUITE(TestSuiteAccountManager, TestSuiteAccountManagerFixture)

        BOOST_AUTO_TEST_CASE(getAccountTest) {
            BOOST_REQUIRE_EQUAL(manager->findAccounts(AccountManager::findAll).size(), 2);
            BOOST_REQUIRE_EQUAL(manager->getAccount("1")->getId(), "1");
            BOOST_REQUIRE_EQUAL(manager->getAccount("2")->getId(), "2");
            BOOST_REQUIRE_EQUAL(manager->getAccount("3"), nullptr);
        }

        BOOST_AUTO_TEST_CASE(registerAccountTest) {
            BOOST_REQUIRE_EQUAL(manager->findAccounts(AccountManager::findAll).size(), 2);
            manager->registerAccount("Poranta", "Jolada", "3", address3);
            BOOST_REQUIRE_EQUAL(manager->findAccounts(AccountManager::findAll).size(), 3);
            BOOST_REQUIRE_EQUAL(manager->getAccount("3")->getFirstName(), "Poranta");
        }

        BOOST_AUTO_TEST_CASE(unregisterAccountTest) {
            BOOST_REQUIRE_EQUAL(manager->getAccount("1")->isArchive(), false);
            manager->unregisterAccount("1");
            BOOST_REQUIRE_EQUAL(manager->getAccount("1")->isArchive(), true);
        }

        BOOST_AUTO_TEST_CASE(findAllReisteredAccountsTest) {
            BOOST_REQUIRE_EQUAL(manager->findAccounts(AccountManager::findAll).size(), 2);
            manager->unregisterAccount("1");
            BOOST_REQUIRE_EQUAL(manager->findAccounts(AccountManager::findAll).size(), 1);
            manager->unregisterAccount("2");
            BOOST_REQUIRE_EQUAL(manager->findAccounts(AccountManager::findAll).size(), 0);
            manager->registerAccount("Poranta", "Jolada", "3", address3);
            BOOST_REQUIRE_EQUAL(manager->findAccounts(AccountManager::findAll).size(), 1);

        }

    BOOST_AUTO_TEST_SUITE_END()
