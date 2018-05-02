#include <newapp1.hpp>

void newapp1::hello(account_name account) {
    print("Hello, ", name{account});
}

void newapp1::create(const account_name account,
                     const string&      username,
                     const string&      bio,
                     uint32_t           age) {
    require_auth(account);

    profile_table profile(_self,_self);

    auto itr = profile.find(account);

    eosio_assert(itr == profile.end(), "Account already has a profile");

    profile.emplace(account, [&](auto& p) {
        p.account  = account;
        p.username = username;
        p.bio      = bio;
        p.age      = age;
    });

    print(name{account}, " profile created");
}

void newapp1::update(const account_name account,
            const string&      username,
            const string&      bio,
            uint32_t           age) {
    require_auth(account);

    profile_table profile(_self,_self);

    auto itr = profile.find(account);

    eosio_assert(itr != profile.end(), "Account does not have a profile");

    profile.modify(itr, account, [&](auto& p) {
        p.username = username;
        p.bio      = bio;
        p.age      = age;
    });

    print(name{account}, " modified");
}

void newapp1::remove(const account_name account) {
    require_auth(account);

    profile_table profile(_self,_self);

    auto itr = profile.find(account);

    eosio_assert(itr != profile.end(), "Account does not have a profile");

    profile.erase(itr);
    print(name{account}, " profile removed");
}

void newapp1::get(const account_name account) {
    profile_table profile(_self,_self);

    auto itr = profile.find(account);

    eosio_assert(itr != profile.end(), "Account does not have a profile");

    print("Account: ",  name{itr->account},    " , ");
    print("Username: ", itr->username.c_str(), " , ");
    print("Bio: ",      itr->bio.c_str(),      " , ");
    print("Age: ",      itr->age);
}