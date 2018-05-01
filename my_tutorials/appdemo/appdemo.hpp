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
    void hello(const account_name account);

    // @abi action
    void create(const account_name account,
                const string&      username,
                uint32_t           age,
                const string&      bio);

    // @abi action
    void get(const account_name account);

    // @abi action
    void update(const account_name account,
                const string&      username,
                uint32_t           age,
                const string&      bio);

    // @abi action
    void remove(const account_name account);

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