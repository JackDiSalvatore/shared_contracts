/* appdemo.cpp
*  Jack DiSalvatore
*/
#include <appdemo.hpp>

void appdemo::hello(account_name account) {
    print("Hello ", name{account});
}

void appdemo::create(const account_name account,
                     const string&      username,
                     uint32_t           age,
                     const string&      bio) {
    require_auth(account);

    profile_table profiles(_self, _self);

    auto itr = profiles.find(account);

    eosio_assert(itr == profiles.end(), "Account already exists");

    profiles.emplace(account, [&](auto& p) {
        p.account  = account;
        p.username = username;
        p.age      = age;
        p.bio      = bio;
    });
}

void appdemo::get(const account_name account) {
    profile_table profiles(_self, _self);

    auto itr = profiles.find(account);

    eosio_assert(itr != profiles.end(), "Account does not exist");

    print("Account: ", name{itr->account}, " , ");
    print("Username: ", itr->username.c_str(), " , ");
    print("Age: ", itr->age , " , ");
    print("Bio: ", itr->bio.c_str());
}

void appdemo::update(const account_name account,
                     const string&      username,
                     uint32_t           age,
                     const string&      bio) {
    require_auth(account);

    profile_table profiles(_self, _self);

    auto itr = profiles.find(account);

    eosio_assert(itr != profiles.end(), "Account does not exist");

    profiles.modify(itr, account, [&](auto& p) {
        p.username = username;
        p.age      = age;
        p.bio      = bio;
    });
}

void appdemo::remove(const account_name account) {
    require_auth(account);

    profile_table profiles(_self, _self);

    auto itr = profiles.find(account);

    eosio_assert(itr != profiles.end(), "Account does not exist");

    profiles.erase(itr);
    print(name{account} , " deleted!");
}