#include <eosiolib/eosio.hpp>
#include <eosiolib/singleton.hpp>
#include <eosiolib/crypto.h>

using namespace std;
using namespace eosio;

class ballot : public contract {
public:
    // Constuct an instance of both the Members multi_index
    // and the Proposals multi_index with in the context of the
    // contracts scope itself
    ballot(account_name _self) :
          contract(_self),
          Members(_self, _self),
          Proposals(_self, _self) {}

    static constexpr uint64_t code = N(ballot);

    // @abi action
    void init(account_name appKey);

    // @abi action
    void newmember(account_name  account, account_name granter,
                   uint32_t     weight, bool invite_permission);

    // @abi action
    void rmmember(account_name member);

    // @abi action
    void propose(account_name proposer, string title, string description);

    // @abi action
    void addvote(account_name voter, uint64_t proposal_id);

    // @abi action
    void rmvote(account_name voter, uint64_t proposal_id);

private:
    // @abi table members i64
    struct Member {
        uint64_t     member_id;
        account_name account;
        uint64_t     weight = 1;
        account_name granter;
        bool         invite_permission = false;

        uint64_t primary_key() const { return member_id; }
        EOSLIB_SERIALIZE(Member, (member_id)(account)(weight)(granter)(invite_permission))
    };

    struct Vote {
        account_name voter;
        uint64_t     vote;
    };

    // @abi table proposals i64
    struct Proposal {
        uint64_t     id;
        account_name account;
        string       title;
        string       description;
        vector<Vote> votes;
        bool         approved = false;

        uint64_t primary_key() const { return id; }
        EOSLIB_SERIALIZE(Proposal, (id)(account)(title)(description)(votes)(approved))
    };

    // @abi table settings i64
    struct Settings {
        account_name            appKey;

        uint64_t primary_key() const { return 0; }
        EOSLIB_SERIALIZE( Settings, (appKey) )
    };

    multi_index<N(members), Member>                Members;
    multi_index<N(proposals), Proposal>            Proposals;

    typedef singleton<N(settings), Settings>  BallotSettings;

    inline Member get_member(account_name voter);

/*    inline Member create_member(account_name account,
                                account_name granter,
                                uint32_t     weight,
                                bool         invite_permission);*/

    /* HELPER FUNCTIONS */
    account_name appKey() {
        return BallotSettings(code,_self).get().appKey;
    }

    inline static uint64_t murmur( const string& strkey ){
        return std::hash<string>{}(strkey);
    }

    inline static uint64_t accountHash( const account_name& key ){
        return std::hash<uint64_t>{}(key);
    }

};