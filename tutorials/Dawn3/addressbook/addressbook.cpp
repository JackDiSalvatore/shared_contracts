#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

#include <string>

using eosio::indexed_by;
using eosio::const_men_fun;
using std::string;

using namespace eosio;

struct hi {
    account_name account;
};

class hello : public contract {

public:
    /* Pulls in constructor from parent 'contract' */
    using contract::contract;

    explicit addressbook(action_name self)
            : contract(self) {}

    // @abi action
    void add(const account_name account,
             const string& first_name,
             const

};

EOSIO_ABI( addressbook, (hi))