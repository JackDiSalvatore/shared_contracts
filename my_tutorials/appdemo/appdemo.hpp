/* appdemo.hpp
*  Jack DiSalvatore
*/
#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

class appdemo : public contract {
public:
    using contract::contract;
    // @abi action
    void hello(account_name user);
};

EOSIO_ABI(appdemo, (hello))