#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/singleton.hpp>

using namespace eosio;

class deep : contract {

    using contract::contract;

public:
    deep(account_name self) : contract(self) {}

    void setapp(account_name application) {
        //require_auth2(user, N(owner));
        //eosio_assert(false, "Something happened!");
        require_auth(_self); // require owner of deep account
        require_auth(application);

        // comment this for testing
        eosio_assert(!configs::exists(), "Configuration already exists!");
        configs::set(config{application}, _self);  // config applicaton;
                                                   // scope to _self
    }

    void setacc(account_name user) {
        require_auth(user);
        require_auth(configs::get(_self).application);

        // "user" is the "scope"
        eosio_assert(!ids::exists(user), "User already has an ID");
        ids::set(nextId(), user);
        // This allows us to keep track of user id's
        // (by saving them to a singleton) and increments them
        // in an atomic way
    }

    void getacc(account_name user) {
        eosio_assert(ids::exists(user), "User does not have an ID");
        print("User's ID is: ", ids::get(user));
    }

    void removeacc(account_name user) {
        require_auth2(user, N(active));
        require_auth(configs::get().application);
        // the "_self" is implicit

        eosio_assert(ids::exists(user), "User does not have and ID");
        ids::remove(user);
    }

private:
    typedef uint64_t id;

    // singleton
    struct config {
        account_name application;

        EOSLIB_SERIALIZE(config, (application))
    };

    //          code , name-of-singleton, scope , data_struct
    typedef singleton<N(deep), N(config), N(deep), config> configs;
    typedef singleton<N(deep), N(ids), N(deep), id> ids;
    typedef singleton<N(deep), N(lastId), N(deep), id> lastId;

    id nextId() {
        id lid = lastId::exists() ? lastId::get()+1 : 0;
        lastId::set(lid);
        return lid;
    }

};

EOSIO_ABI(deep, (setapp)(setacc)(getacc)(removeacc))