#include <string>
#include <eosiolib/types.hpp>
#include <eosiolib/print.hpp>
#include <eosio.system/eosio.system.hpp>

using namespace eosio;

class mltidxdemo : public contract {

using contract::contract;

public:
    mltidxdemo(account_name self) :
        contract(self),
        my_database(_self, _self)
    {}

    // @abi action
    void create(const uint64_t unique_id, std::string name = "", std::string address = "") {

        auto my_database_itr = my_database.find(unique_id);

        eosio_assert(my_database_itr == my_database.end(),
                    " ID already exists, use 'set' to update info ");

        print(" ID doesn't exist ");
        print(" Creating new Row for ID ");

        my_database.emplace(_self, [&](db_table& my_row) {
            my_row.id           = unique_id;
            my_row.name         = name;
            my_row.address      = address;
            my_row.date_created = now();
        });

        print(" Database set ");
        return;

    }

    // @abi action
    void get(const uint64_t unique_id) {

        auto my_database_itr = my_database.find(unique_id);

        if (my_database_itr == my_database.end()) {
            print(" ID doesn't exist ");
        }

        if (my_database_itr->id == unique_id) {
            print(" Here is your info ");
            print(" ID: ", my_database_itr->id);
            print(" Name: ", my_database_itr->name.c_str());
            print(" Address: ", my_database_itr->address.c_str());
            print(" Date Created: ", my_database_itr->date_created);
        }

    }

    // @abi action
    void update(const uint64_t unique_id, std::string name = "", std::string address = "") {
        /* NOTE: In the future you will want to require the authorizations of the sender
        *        when preforming the update function. */
        auto my_database_itr = my_database.find(unique_id);

        eosio_assert(my_database_itr != my_database.end(), "That ID doesn't exist");
        /* The zero in the parameters indicates that the contract will be billed for ram*/
        my_database.modify(my_database_itr, 0, [&](db_table& db_to_update) {
            db_to_update.name    = name;
            db_to_update.address = address;
        });

        print(" ID: ", unique_id, " updated ");

    }

    // @abi action
    void erase(const uint64_t unique_id) {

        auto my_database_itr = my_database.find(unique_id);

        if (my_database_itr == my_database.end()) {
            print(" ID doesn't exist ");
        }

        if (my_database_itr->id == unique_id) {
            print(" Deleting your info ");
            my_database.erase(my_database_itr);
        }
    }

private:
    // @abi table mltidxdb i64
    struct db_table {
        uint64_t    id;
        std::string name;
        std::string address;
        time date_created;

        uint64_t primary_key() const { return id; }
        EOSLIB_SERIALIZE(db_table, (id)(name)(address)(date_created))
    };

    typedef eosio::multi_index< N(mltidxdb), db_table> db_multi_index;
    db_multi_index my_database;

};

EOSIO_ABI(mltidxdemo, (create)(get)(update)(erase))