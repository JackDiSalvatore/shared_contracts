#include "ballot.hpp"


/*****************************************************************************
 *                      PUBLIC MEMBER FUNCTIONS
 ****************************************************************************/

void ballot::init(account_name appKey) {
    require_auth(_self);
    require_auth(appKey);

    /* First Member Ever Created */
    uint64_t id = accountHash(appKey);

    /* Instantiate the BallotSettings Singleton */
    BallotSettings(code, _self).set(Settings{appKey}, _self);

    /* Emplce the first member; the creator */
    auto creator = Members.emplace(_self, [&](auto& m) {
        m.member_id = id;
        m.account = appKey;
        m.weight = 0;
        m.granter = appKey;
        m.invite_permission = true;
    });

    print("Contract Initialized by ", name{appKey});
}

void ballot::newmember(account_name account, account_name granter,
                       uint32_t     weight, bool invite_permission) {
    require_auth(appKey());
    require_auth(account);
    require_auth(granter);

    uint64_t id = accountHash(account);
    uint64_t granter_id = accountHash(granter);

    /* Error Handling */
    auto granter_member = Members.find(granter_id);
    eosio_assert(granter_member != Members.end(), "Granter does not exist");
    eosio_assert(granter_member->invite_permission,
                 "You do not have permission to add a new member!");

    auto member = Members.find(id);
    eosio_assert(member == Members.end(), "Member already exists!");

    /* Create New Member */
    Members.emplace(_self, [&](auto& m) {
        m.member_id = id;
        m.account   = account;
        m.weight    = weight;
        m.granter   = granter;
        m.invite_permission = invite_permission;
    });

    print("New Member Added: ", name{account});
}

void ballot::rmmember(account_name member) {
    require_auth(appKey());
    require_auth(member);

    uint64_t id = accountHash(member);

    auto itr = Members.find(id);

    Members.erase(itr);
}

void ballot::propose(account_name proposer, string title, string description) {
    require_auth(appKey());
    require_auth(proposer);

    uint64_t proposer_id = accountHash(proposer);
    uint64_t proposal_id = murmur(title);

    // get 'proposer' member
    auto proposer_member = Members.find(proposer_id);
    eosio_assert(proposer_member != Members.end(), "Member does not exist!");

    // check that proposal is new or modify existing
    auto proposal = Proposals.find(proposal_id);
    if (proposal == Proposals.end()) {
        print("Creating new proposal");
        Proposals.emplace(_self, [&](auto& p) {
            p.id = proposal_id;
            p.account = proposer_member->account;
            p.title = title;
            p.description = description;
            p.approved = false;
        });
    } else {
        print("Modifing existing proposal");
        eosio_assert(proposal->id == proposal_id, "Proposal ID mismatch");
        Proposals.modify(proposal, 0, [&](auto& p) {
            p.description = description;
        });
    }

}

void ballot::addvote(account_name voter, uint64_t proposal_id) {
    require_auth(appKey());
    require_auth(voter);

    // Find the member 'voter'
    uint64_t id = accountHash(voter);

    auto member = Members.find(id);
    eosio_assert(member != Members.end(), "Member doesn't exists!");
    // Find the proposal by 'proposal_id'

    // push a vote to the vote vector in the proposal

    print("TODO ");
}

void ballot::rmvote(account_name voter, uint64_t proposal_id) {
    require_auth(voter);

    print("TODO");
}

/*****************************************************************************
 *                      PRIVATE MEMBER FUNCTIONS
 ****************************************************************************/

/*ballot::Member ballot::get_member(account_name voter) {
    auto member = ballot::Members.find(voter);
    eosio_assert(member =! ballot::Members.end(), "Member doesn't exist");

    return *member;  // member object itr points to
}*/

/*Member ballot::create_member(account_name account, account_name granter,
                             uint32_t     weight, bool invite_permission) {
    require_auth(account);
    require_auth(granter);

    auto member = Members.find(account);
    eosio_assert(member == Members.end(), "Memember already exists!");
    eosio_assert(granter.invite_permission,
                 "You do not have permission to add a new member!");
    eosio_assert(weight >= 0, "Weight must be a positive integer");

    // Create New Member
    auto new_member = Members.emplace(_self, [&](auto& m) {
        m.account = account;
        m.weight = weight;
        m.granter = granter;
        m.invite_permission = invite_permission;
    });

    return *new_member;
}*/

EOSIO_ABI( ballot, (init)(propose)(newmember)(rmmember)(addvote)(rmvote) )