#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/currency.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/multi_index.hpp>

using namespace eosio;
using std::string;

/*
namespace models {
    enum status_type {
        pending = 0,
        accepted = 1,
        rejected = 2,
    };

    // @abi table incomingTrans i64
    struct incoming_type {
        uint64_t id;
        account_name from;

        uint64_t primary_key() const { return id; }
        EOSLIB_SERIALIZE(incoming_type, (id)(from))
    };

    typedef eosio::multi_index<N(incoming), incoming_type> incomingTrans;

    // @abi table outgoingTrans i64
    struct outgoing_type {
        uint64_t date;
        account_name to;
        asset amount;
        uint8_t status; 

        uint64_t primary_key() const { return date; }
        uint64_t get_status() const { return static_cast<uint64_t>(status); }
        EOSLIB_SERIALIZE(outgoing_type, (date)(to)(amount)(status))
    };

    typedef eosio::multi_index<N(outgoing), outgoing_type,
        indexed_by<N(bystatus), 
        const_mem_fun<outgoing_type, uint64_t, &outgoing_type::get_status>>
    > outgoingTrans;

    // @abi table config
    struct config_type {
        account_name contract;
        account_name app;
        account_name hw;
        uint64_t balance;

        account_name primary_key() const { return contract; }
        EOSLIB_SERIALIZE(config_type, (contract)(app)(hw)(balance))
    };

    typedef eosio::multi_index<N(config), config_type> config;
} */

class tpass : public contract {
    public:			
        using contract::contract;
		
		tpass(account_name s) : contract(s), _attempts(s,s) 
		{}
		

        // @abi action sendLogin1
        void sendLogin1(uint64_t id, account_name acc);

        // @abi action sendLogin2
        void sendLogin2(uint64_t id, account_name acc);
		
        // @abi action revokeAutorization
		void revokeAuth(account_name acc, uint64_t id);

		// @abi action checkLogin1
        account_name checkLogin1(uint64_t id) const;

		// @abi action checkLogin1
        account_name checkLogin2(uint64_t id) const;
		
		// @abi action isValid
        bool isValid(uint64_t id) const;
		
		
   private: 
      struct attempt {
         uint64_t     id;
         uint32_t     date;
         account_name key1 = 0;                                      
         account_name key2 = 0;  
		 bool 		  valid = false;

         uint64_t primary_key() const { return id; }
      };
	  
	   typedef eosio::multi_index<N(attempt), attempt,
		  eosio::indexed_by<N(primary_key), eosio::const_mem_fun<attempt, uint64_t, &attempt::primary_key> >
	   > attempts;

	   attempts _attempts;
};

EOSIO_ABI( tpass, (sendLogin1)(sendLogin2)(revokeAuth) )