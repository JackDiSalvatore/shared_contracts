#include <eosiolib/eosio.hpp>
#include <eosiolib/singleton.hpp>

using namespace std;
using namespace eosio;


class keepscore : public contract {
public:
    keepscore(account_name self) : contract(self) {}

    void init(account_name app_owner);

    void scored(uint64_t          id,
               string&             username,
               const account_name  account,
               uint64_t           score);

    void remove();

    static constexpr uint64_t code = N(keepscore);

private:
    /* Use this to make your app sign transactions */
    account_name appOwner() {
        return AppSettings().get().app_owner;
    }

    struct Scores {
        uint64_t     id;
        string       username;
        account_name account;
        uint64_t     score;

        EOSLIB_SERIALIZE(Scores, (id)(username)(account)(score))
    };

    struct AppConfig {
        account_name app_owner;

        account_name primary_key() const { return app_owner; }
        EOSLIB_SERIALIZE(AppConfig, (app_owner))
    };


    typedef singleton<code, N(appconfig),
                      code, AppConfig   >   AppSettings;
};

EOSIO_ABI(keepscore, (init)(scored))