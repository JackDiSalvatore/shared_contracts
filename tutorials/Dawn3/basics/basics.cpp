#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;
using namespace std;

class basics : public contract {

using contract::contract;

public:

    basics(account_name self) :
            contract(self),
            _statuses(_self, _self) {};

    // @abi action
    void test(name sender, string status) {
        require_auth(sender);

        // Find sender with the "primary_key" for
        // the "multi_index" table
        auto iter = _statuses.find(sender);

        if(iter == _statuses.end()) {
            // emplace with primary_key ?
            _statuses.emplace(sender, [&](auto& row){
                row.sender = sender;
                row.status = status;
            });
        } else {
            _statuses.modify(iter, 0, [&](auto& row) {
                row.status = status;
            });
        }

        print("Hello");
    }

private:

    // @abi table
    struct statuses {
        name sender;
        string status;

        // Multi-index
        // "const" means function won't change member vars
        name primary_key() const {
            return sender;
        };

        EOSLIB_SERIALIZE(statuses, (sender)(status))
    };

    // The actual table
    //         <tables_name, data_struct>
    multi_index<N(statuses), statuses>     _statuses;

};

// EOSIO_ABI(contract_name, (action1)(action2)(action3))
EOSIO_ABI(basics, (test))