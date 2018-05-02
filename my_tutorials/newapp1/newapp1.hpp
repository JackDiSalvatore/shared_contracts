#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

#include <string>

using namespace eosio;
using std::string;

class newapp1 : public contract {
public:
    newapp1(account_name self) : contract(self) {}

    // @abi action
    void hello(account_name account);

    // @abi action
    void create(const account_name account,
                const string&      username,
                const string&      bio,
                uint32_t           age);

    // @abi action
    void update(const account_name account,
                const string&      username,
                const string&      bio,
                uint32_t           age);

    // @abi action
    void remove(const account_name account);

    // @abi action
    void get(const account_name);

private:

    // @abi table profiles i64
    struct profile {
        account_name account;
        string       username;
        string       bio;
        uint32_t     age;

        account_name primary_key() const { return account; }
        EOSLIB_SERIALIZE(profile, (account)(username)(bio)(age))
    };

    typedef eosio::multi_index<N(profiles), profile> profile_table;
};

EOSIO_ABI(newapp1, (hello)(create)(update)(remove)(get))