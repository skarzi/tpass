#include "tpass.hpp"

/*
extern "C" 
{
    void apply( uint64_t receiver, uint64_t code, uint64_t action )
    {
        tpass eos(receiver);

        switch(action) {
            case N(sendLogin1):
                if(code == receiver) {
					uint64_t id;
                    account_name acc;
                    std::tie(id, acc) = eosio::unpack_action_data<
                        std::tuple<uint64_t, account_name>>();
                    eos.sendLogin1(id, acc);
                }
                break;
            case N(sendLogin2):
                if(code == receiver) {
					uint64_t id;
                    account_name acc;
                    std::tie(id, acc) = eosio::unpack_action_data<
                        std::tuple<uint64_t, account_name>>();
                    eos.sendLogin2(id, acc);
                }
                break;
            case N(revokeAuth):
                if(code == receiver) {
					uint64_t id;
                    account_name acc;
                    std::tie(id, acc) = eosio::unpack_action_data<
                        std::tuple<uint64_t, account_name>>();
                    eos.revokeAuth(id, acc);
                }
                break;
				
            case N(checkLogin1):
                if(code == receiver) {
					uint64_t id;
                    std::tie(id) = eosio::unpack_action_data<std::tuple<uint64_t>>();
                    eos.checkLogin1(id);
                }
                break;
            case N(checkLogin2):
                if(code == receiver) {
					uint64_t id;
                    std::tie(id) = eosio::unpack_action_data<std::tuple<uint64_t>>();
                    eos.checkLogin2(id);
                }
                break;
            case N(isValid):
                if(code == receiver) {
					uint64_t id;
                    std::tie(id) = eosio::unpack_action_data<std::tuple<uint64_t>>();
                    eos.isValid(id);
                }
                break;
				
            default:
                break;
        }
        eosio_exit(0);
    }
} 
*/

// @abi action sendLogin1
void tpass::sendLogin1(uint64_t id, account_name acc) {
	 require_auth( acc );

	 eosio_assert( _attempts.find( id ) == _attempts.end(), "This id is already taken" );
	 _attempts.emplace(id, [&]( auto& rcrd ) {
            rcrd.id   = id;
            rcrd.date   = current_time();
            rcrd.key1 = acc;
            rcrd.key2 = 0;
            rcrd.valid = true;
         });
}

// @abi action sendLogin2
void tpass::sendLogin2(uint64_t id, account_name acc) {
	 require_auth( acc );
	 auto it = _attempts.find( id );
	 eosio_assert( _attempts.find( id ) != _attempts.end(), "This id doesn't exists" );
	 eosio_assert( it->key2 == 0, "This id is already verified" );
	 _attempts.modify( it, id, [&]( auto& rcrd ) {
		rcrd.key2 = acc;
	 });
}

// @abi action revokeAuth
void tpass::revokeAuth(account_name acc, uint64_t id) {
	 require_auth( acc );
	 auto it = _attempts.find( id );
	 eosio_assert( _attempts.find( id ) != _attempts.end(), "This id doesn't exists" );
	 eosio_assert( it->key1 != acc && it->key2 != acc, "You don't have access to revoke that autorization" );
	 _attempts.modify( it, id, [&]( auto& rcrd ) {
		rcrd.valid = false;
	 });	
}

// @abi action checkLogin1
account_name tpass::checkLogin1(uint64_t id) const {
	auto it = _attempts.find( id );
	eosio_assert( _attempts.find( id ) != _attempts.end(), "This id doesn't exists" );
	return it->key1;
}

// @abi action checkLogin1
account_name tpass::checkLogin2(uint64_t id) const {
	auto it = _attempts.find( id );
	eosio_assert( _attempts.find( id ) != _attempts.end(), "This id doesn't exists" );	
	return it->key2;
}

// @abi action isValid
bool tpass::isValid(uint64_t id) const {
	auto it = _attempts.find( id );
	eosio_assert( _attempts.find( id ) != _attempts.end(), "This id doesn't exists" );	
	return it->valid;	
};

