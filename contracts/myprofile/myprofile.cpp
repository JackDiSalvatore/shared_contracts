#include <eosiolib/eosio.hpp>
#include <eosiolib/action.hpp>
#include <eosiolib/asset.hpp>


using namespace eosio;

// static const uint64_t EOS_PRECISION = 4;
// static const asset_symbol EOS_SYMBOL = S(EOS_PRECISION, EOS);

namespace eosio {
/**
 * FIXME:
 * The actual `eosio.token` transfer struct definition until its definition is accesible
 * from an actual `eosio.token.hpp` file. Until then, we define it ourself so
 * we can unpack the actual action data when a token transfer occurs inside
 * the `eosio.token` contract to this contract's account.
 */
struct token_transfer {
  account_name from;
  account_name to;
  asset quantity;
  std::string memo;
};
}  // namespace eosio


class myprofile : public eosio::contract {
  public:
      using contract::contract;

      static bool is_token_transfer(uint64_t code, uint64_t action) {
         return code == N(eosio.token) && action == N(transfer);
      }

      /// @abi action
      void hi( account_name user ) {
         print( "Hello, ", name{user} );
      }

      // Notifications
      void mytransfer(const asset& pot) {
        print("myprofile::mytransfer");
      }

private:

};

/**
 * SmartContract C entrypoint using a macro based on the list of action in the.
 * For each of defined action, a switch branch is added
 * automatically unpacking the data into the action's structure and dispatching
 * a method call to `action` define in this SmartContract.
 *
 * Each time a new action is added, EOSIO_API definition should be expanded with the
 * new action handler's method name.
 */
extern "C" {
void apply(uint64_t receiver, uint64_t code, uint64_t action) {
  auto self = receiver;
  if (code == self) {
    // Don't rename `thiscontract`, it's being use verbatim in `EOSIO_API` macro
    myprofile thiscontract(self);
    switch (action) { EOSIO_API(myprofile, (hi)) }

    eosio_exit(0);
  }

  if (myprofile::is_token_transfer(code, action)) {
    eosio::token_transfer action = unpack_action_data<eosio::token_transfer>();

    // Only pass notification to myprofile if transfer `to` is myprofile contract account and `quantity` are EOS tokens
    if (action.to == self && action.quantity.symbol == CORE_SYMBOL) {
      myprofile(self).mytransfer(action.quantity);
    }

    eosio_exit(0);
  }
}
}
