//
// Created by student on 08.06.2021.
//

#ifndef BANK_SERVICESMANAGER_H
#define BANK_SERVICESMANAGER_H

#include <boost/date_time.hpp>
#include "LongTermLoan.h"
#include "typedefs.h"
#include "ServiceRepository.h"

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;

class ServicesManager
{
private:
    ServiceRepoPtr serviceRepository = std::make_shared<ServiceRepository>();
    ServiceRepoPtr serviceArchive = std::make_shared<ServiceRepository>();
public:
    ServicesManager();
    virtual ~ServicesManager() = default;
    ServicePtr getService(const std::string &id) const;
    ServicePtr getServiceArchive(const std::string &id) const;
    void createLongTermLoan(const std::string &id, const pt::ptime &beginTime, const AccountPtr &account,
                            LongTermLoanType type);
    void createShortTermLoan(const std::string &id, const pt::ptime &beginTime, const pt::ptime &deadline,
                             const AccountPtr &account, double moneyLoan, double percentage);
    void createMortgage(const std::string &id, const pt::ptime &beginTime, const pt::ptime &deadline, double moneyLoan,
                        const AccountPtr &account, double percentage, const AddressPtr &houseAddress);
    void createDeposit(const std::string &id, const pt::ptime &beginTime, double money, const AccountPtr &account,
                       double percentage, bool capitalization);
    void endDeposit(ServicePtr deposit, const pt::ptime &endTime);
    std::vector<ServicePtr> getAllAccountServices(const AccountPtr &account) const;
    std::vector<ServicePtr> findServices(ServicePredicate predicate) const;
    std::vector<ServicePtr> findAll();
    double checkActivity(const AccountPtr &account) const;
    void changeAccountType(const AccountPtr &account) const;
    void payMoneyLoan(const ServicePtr &loan, double money, pt::ptime date);

};

#endif //BANK_SERVICESMANAGER_H
