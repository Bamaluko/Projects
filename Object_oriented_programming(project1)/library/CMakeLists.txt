cmake_minimum_required(VERSION 3.4)
project(Library)

add_compile_options(-Wall -Wextra -Werror)

set(SOURCE_FILES
        src/model/Account.cpp
        src/model/AccountType.cpp
        src/model/Bronze.cpp
        src/model/Silver.cpp
        src/model/Gold.cpp
        src/model/Address.cpp
        src/model/Service.cpp
        src/model/Deposit.cpp
        src/model/Loan.cpp
        src/model/Payment.cpp
        src/model/ShortTermLoan.cpp
        src/model/AccountException.cpp
        src/model/AddressException.cpp
        src/model/DepositException.cpp
        src/model/LongTermLoan.cpp
        src/model/Mortgage.cpp
        src/model/MortgageException.cpp
        src/model/ShortTermLoanException.cpp
        src/model/LongTermLoanException.cpp
        src/repositories/AccountRepository.cpp
        src/repositories/ServiceRepository.cpp
        src/managers/AccountManager.cpp
        src/managers/ServicesManager.cpp)

#Utwórz bibliotekę typu STATIC, SHARED albo MODULE ze wskazanych źródeł
add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include include/model include/managers include/repositories)

enable_testing()

find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_TEST_FILES
        test/master.cpp
        test/AddressTest.cpp
        test/AccountTest.cpp
        test/PaymentTest.cpp
        test/LoanTest.cpp
        test/DepositTest.cpp
        test/AccountRepositoryTest.cpp
        test/ServiceRepositoryTest.cpp
        test/AccountManagerTest.cpp
        test/MortgageTest.cpp
        test/LongTermLoanTest.cpp
        test/ShortTermLoanTest.cpp
        test/ServicesManagerTest.cpp) # tu w przyszłości będą dodawane pliki źródłowe testów

add_executable (LibraryTest ${SOURCE_TEST_FILES})

#dołącz bibliotekę z testowanymi klasami oraz bibliotekę boost.test do programu testów
target_link_libraries (LibraryTest
        Library
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )

#dodaj test TestBiblioteki1. Instrukcji cmake add_test może być wiele.
#Dodatkowe parametry wpływają na szczegółowość generowanego raportu. Standardowo znajduje się on w Testing/Temporary.
add_test(LibraryTest1 LibraryTest
        --report_level=detailed
        --log_level=all
        --color_output=yes
        )

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

