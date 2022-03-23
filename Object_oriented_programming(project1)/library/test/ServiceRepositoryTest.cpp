//
// Created by student on 02.06.2021.
//

#include <string>
#include <memory>
#include <boost/test/unit_test.hpp>
#include "repositories/ServiceRepository.h"
#include "Account.h"
#include "ShortTermLoan.h"
#include "Deposit.h"
#include "Loan.h"
#include "model/typedefs.h"

using namespace  std;


    struct TestSuiteServiceRepositoryFixture {
        AddressPtr address1;
        AddressPtr address2;
        AccountPtr account1;
        AccountPtr account2;
        ServiceRepoPtr repo;
        ServicePtr shortTermLoan;
        ServicePtr  deposit;

        TestSuiteServiceRepositoryFixture() {
            address1 = make_shared <Address>("Warszawa", "Zielona", "23", "14");
            address2 = make_shared <Address>("Wroclaw", "Blekitna", "13", "31");
            account1 = make_shared<Account>("Piotr", "Mamos", "1", address1);
            account2 = make_shared<Account>("Jacek", "Wrubel", "2", address2);
            pt::ptime time1(gr::date(2021,3,22), pt::hours(13) + pt::minutes(49));
            pt::ptime time2(gr::date(2025,3,22), pt::hours(13) + pt::minutes(49));
            shortTermLoan = make_shared<ShortTermLoan>("1", time1, time2, 100000, account1, 0.02);
            deposit = make_shared<Deposit>("2", time1, 100000, account2, 0.01, false);
            repo = make_shared<ServiceRepository>();
            repo->add(shortTermLoan);

        }

        ~TestSuiteServiceRepositoryFixture() = default;

    };


    BOOST_FIXTURE_TEST_SUITE(TestSuiteServiceRepository, TestSuiteServiceRepositoryFixture)

        BOOST_AUTO_TEST_CASE(GetterTest) {
            BOOST_REQUIRE_EQUAL(repo->size(), 1);
            BOOST_REQUIRE_EQUAL(repo->get(0), shortTermLoan);
            BOOST_REQUIRE_EQUAL(repo->get(1), nullptr);
        }

        BOOST_AUTO_TEST_CASE(AddToRepositoryTest) {
            BOOST_REQUIRE_EQUAL(repo->size(), 1);
            repo->add(deposit);
            BOOST_REQUIRE_EQUAL(repo->size(), 2);
        }

        BOOST_AUTO_TEST_CASE(RemoveFromRepositoryTest) {
            BOOST_REQUIRE_EQUAL(repo->size(), 1);
            repo->remove(shortTermLoan);
            BOOST_REQUIRE_EQUAL(repo->size(), 0);
        }

        BOOST_AUTO_TEST_CASE(ReportTest) {
            BOOST_REQUIRE_EQUAL(repo->report(), shortTermLoan->getInfo() + "\n");
            repo->add(deposit);
            BOOST_REQUIRE_EQUAL(repo->report(), shortTermLoan->getInfo() + "\n" + deposit->getInfo() + "\n");

        }

        BOOST_AUTO_TEST_CASE(FindByUsingFindAllTest) {
            BOOST_REQUIRE_EQUAL(repo->findAll().size(), 1);
            repo->add(deposit);
            BOOST_REQUIRE_EQUAL(repo->findAll().size(), 2);

        }


    BOOST_AUTO_TEST_SUITE_END()
