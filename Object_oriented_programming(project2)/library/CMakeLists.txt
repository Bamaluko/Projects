cmake_minimum_required(VERSION 3.4)
project(Library)
add_compile_options(-Wall -Wextra -Werror)

set(SOURCE_FILES

        src/model/Client.cpp include/model/Client.h src/model/Address.cpp include/model/Address.h src/model/Vehicle.cpp include/model/Vehicle.h src/model/Rent.cpp include/model/Rent.h src/repositories/ClientRepository.cpp include/repositories/ClientRepository.h src/repositories/VehicleRepository.cpp include/repositories/VehicleRepository.h src/repositories/RentRepository.cpp include/repositories/RentRepository.h include/model/typedefs.h src/repositories/StorageContainer.cpp include/repositories/StorageContainer.h src/model/Bicycle.cpp include/model/Bicycle.h src/model/MotorVehicle.cpp include/model/MotorVehicle.h src/model/Car.cpp include/model/Car.h src/model/Moped.cpp include/model/Moped.h src/model/ClientType.cpp include/model/ClientType.h src/model/ClientBronze.cpp include/model/ClientBronze.h src/model/ClientDefault.cpp include/model/ClientDefault.h src/model/ClientSilver.cpp include/model/ClientSilver.h src/model/ClientGold.cpp include/model/ClientGold.h src/model/ClientPlatinum.cpp include/model/ClientPlatinum.h src/model/ClientDiamond.cpp include/model/ClientDiamond.h src/managers/ClientManager.cpp include/managers/ClientManager.h src/managers/VehicleManager.cpp include/managers/VehicleManager.h src/managers/RentManager.cpp include/managers/RentManager.h src/model/AddressException.cpp include/model/AddressException.h src/model/ClientException.cpp include/model/ClientException.h src/model/VehicleException.cpp include/model/VehicleException.h src/model/RentException.cpp include/model/RentException.h include/repositories/Repository.h include/model/FirstNamePredicate.h include/model/LastNamePredicate.h)

#Utwórz bibliotekę typu STATIC, SHARED albo MODULE ze wskazanych źródeł
add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)

enable_testing() # dodane wcześniej w punkcie 2

find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_TEST_FILES test/master.cpp test/ClientTest.cpp test/AddressTest.cpp test/VehicleTest.cpp test/RentTest.cpp test/ClientRepositoryTest.cpp test/VehicleRepositoryTest.cpp test/RentRepositoryTest.cpp test/ClientManagerTest.cpp test/VehicleManagerTest.cpp test/RentManagerTest.cpp) # tu w przyszłości będą dodawane pliki źródłowe testów

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

