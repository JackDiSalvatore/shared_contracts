/* appdemo.hpp
*  Jack DiSalvatore
*/
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

#include <string>

using namespace eosio;
using std::string;

class appdemo : public contract {
public:
    using contract::contract;

    appdemo(account_name self)
            : contract(self) {}

    // @abi action
    void hello(account_name account);

    // @abi action
    void create(account_name account, string username, uint32_t age, string bio);

    // @abi action
    void get(account_name account);

    // @abi action
    void update(account_name account, string username, uint32_t age, string bio);

    // @abi action
    void remove(account_name account);

private:
    // @abi table profile i64
    struct profile {
        account_name    account;
        string          username;
        uint32_t        age;
        string          bio;

        account_name primary_key() const { return account; }
        EOSLIB_SERIALIZE(profile, (account)(username)(age)(bio))
    };

    typedef eosio::multi_index< N(profile), profile> profile_table;

};

EOSIO_ABI(appdemo, (hello)(create)(get)(update)(remove))