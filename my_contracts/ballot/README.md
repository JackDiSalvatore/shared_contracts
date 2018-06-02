# Abstract
This contract can be used by any application that wishes to create proposals that can be voted on and approved by eosio accounts.

# About
Users can create proposals that consist of a description.  In order for other users to vote on the proposal, they must become a member of the contract.


## Tables
members
--------
* member_id ( key )
+ account
+ weight
+ granter
+ invite_permission
--------

proposals
---------
* id  ( key )
+ account
+ title
+ description
+ votes[]
+ approved
---------

proposals: Any member can create a proposal.  A proposal can be anything, i.e. new law or rule.  Proposals must be approved by x% of the active members within the contract.

approval mechanism:
x% of active members must vote for proposal
Need to know
* p = percentage of votes need for approval (as decimal)
* m = members: get the amount of elements in the container
* v = votes needed: proposal.votes.size()
v = p * m

Ex:
m = 100
p = 60% (0.6)

v = 100 * 0.6
v = 60 votes

## Actions
init: Conceive this contract
* creates the settings for the contract
  * creates the 'creator' of the contract.  The creator is the first member of the
    contract.  Since the creator is also the owner, they cannot vote (weight=0), 
    instead that have only have the ability to add new members.
  * percentage of members needed to approve a proposal
* creates the first member of the contract

addmember: Adds a new member to the contract

rmmember: Free up the storage for the member that wants to leave

propose: Creates a new proposal

rmproposal: Free up storage for a proposal that wants to be deleted

addvote: Allows members to vote on a proposals

rmvote: Removes vote to free up storage


### Example Commands
```
$cleos get table ballot ballot members
{
  "rows": [{
      "member_id": 829746564,
      "account": "ballot",
      "weight": 0,
      "granter": "ballot",
      "invite_permission": 1
    },{
      "member_id": 3803100191,
      "account": "usera",
      "weight": 1,
      "granter": "ballot",
      "invite_permission": 1
    },{
      "member_id": 3877138775,
      "account": "userc",
      "weight": 3,
      "granter": "userb",
      "invite_permission": 1
    }
  ],
  "more": false
}

```

```
$cleos get table ballot ballot proposals
{
  "rows": [{
      "id": 1578512733,
      "account": "usera",
      "title": "Declare Today As A Holiday",
      "description": "May 29, 2018 shall be declared a holiday since because I say so.",
      "votes": [],
      "approved": 0
    },{
      "id": 2136098542,
      "account": "usera",
      "title": "My Proposal",
      "description": "My rule goes here.",
      "votes": [{
          "vote": 1,
          "voter_name": "usera"
        },{
          "vote": 3,
          "voter_name": "userc"
        },{
          "vote": 1,
          "voter_name": "userb"
        }
      ],
      "approved": 0
    }
  ],
  "more": false
}
```