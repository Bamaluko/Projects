//
// Created by student on 01.06.2021.
//
#include <string>
#include <memory>
#include <boost/test/unit_test.hpp>
#include "repositories/AccountRepository.h"
#include "model/typedefs.h"

using namespace  std;

    struct TestSuiteAccountRepositoryFixture {
        AddressPtr address1;
        AddressPtr address2;
        AccountPtr account1;
        AccountPtr account2;
        AccountRepoPtr repo;

        TestSuiteAccountRepositoryFixture() {
            address1 = make_shared <Address>("Warszawa", "Zielona", "23", "14");
            address2 = make_shared <Address>("Wroclaw", "Blekitna", "13", "31");
            account1 = make_shared<Account>("Piotr", "Mamos", "1", address1);
            account2 = make_shared<Account>("Jacek", "Wrubel", "2", address2);
            repo = make_shared<AccountRepository>();
            repo->add(account1);

        }

        ~TestSuiteAccountRepositoryFixture() = default;

    };


    BOOST_FIXTURE_TEST_SUITE(TestSuiteAccountRepository, TestSuiteAccountRepositoryFixture)

        BOOST_AUTO_TEST_CASE(GetterTest) {
            BOOST_REQUIRE_EQUAL(repo->size(), 1);
            BOOST_REQUIRE_EQUAL(repo->get(0), account1);
            BOOST_REQUIRE_EQUAL(repo->get(1), nullptr);
        }

        BOOST_AUTO_TEST_CASE(AddToRepositoryTest) {
            BOOST_REQUIRE_EQUAL(repo->size(), 1);
            repo->add(account2);
            BOOST_REQUIRE_EQUAL(repo->size(), 2);
        }

        BOOST_AUTO_TEST_CASE(RemoveFromRepositoryTest) {
            BOOST_REQUIRE_EQUAL(repo->size(), 1);
            repo->remove(account1);
            BOOST_REQUIRE_EQUAL(repo->size(), 0);
        }

        BOOST_AUTO_TEST_CASE(ReportTest) {
            BOOST_REQUIRE_EQUAL(repo->report(), account1->getAccountInfo() + "\n");
            repo->add(account2);
            BOOST_REQUIRE_EQUAL(repo->report(), account1->getAccountInfo() + "\n" + account2->getAccountInfo() + "\n");

        }

        BOOST_AUTO_TEST_CASE(FindByUsingFindAllTest) {
            BOOST_REQUIRE_EQUAL((repo->findBy(AccountRepository::findAll)).size(), 1);
            repo->add(account2);
            BOOST_REQUIRE_EQUAL((repo->findBy(AccountRepository::findAll)).size(), 2);

        }


    BOOST_AUTO_TEST_SUITE_END()


