# EOSIO NOTES

## Tables

// @abi table
struct table_struct {
    name key;    // first 64 value is key
    string var2;

    EOSLIB_SERIALIZE(N(table_struct), (key)(var2))
};

typedef eosio::multi_index< N(table_name), table_struct> table_namespace;

## Singletons

include<eosiolib/singleton.hpp>

struct config {
    account_name application;

    EOSLIB_SERIALIZE(config, (application))
};

typedef singleton<N(code_name), N(singleton_name), N(contract_name), data_struct> singleton_namespace;
typedef singleton<N(code_name), N(config), N(contract_name), config> configs;

