#include "keepscore.hpp"

void keepscore::init(account_name app_owner) {
        require_auth(_self);
        require_auth(app_owner);

        eosio_assert(!AppSettings().exists(), "App already exists");

        // construct new singleton data type AppConfig
        AppSettings().set(AppConfig{app_owner});
        print("App created with account: ", name{app_owner});
}

void keepscore::scored(uint64_t          id,
                      string&             username,
                      const account_name  account,
                      uint64_t           score) {
    require_auth(appOwner());
    require_auth(account);

    print("You got this far!");
}