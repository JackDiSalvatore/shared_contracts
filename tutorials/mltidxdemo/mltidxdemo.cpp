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
    void set(const uint64_t unique_id, std::string name = "", std::string address = "") {

        auto my_database_itr = my_database.find(unique_id);

        /* Check if this is a new ID and create Row */
        if (my_database_itr == my_database.end()) {

            print(" ID doesn't exist ");
            print(" Creating new Row for ID ");

            auto my_database_itr = my_database.emplace(_self, [&](db_table& my_row) {
                my_row.id           = unique_id;
                my_row.name         = name;
                my_row.address      = address;
                my_row.date_created = now();
            });

            print(" Database set ");
            return;

        } else {
            /* Check if this should update an existing ID */
            print(" Changing Row for ID ", unique_id);

            print(" I dont know how to update existing row yet ");
            return;
        }

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
            print(" PRINT REST OF INFO HERE ");
        }

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

EOSIO_ABI(mltidxdemo, (get)(set)(erase))