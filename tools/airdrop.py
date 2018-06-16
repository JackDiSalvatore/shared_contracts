# Title: airdrop.py
# Description: air drops a token to all eosio accounts in a snapshot
#   file at a  1:1 ratio
import os, sys, csv, time

issuer_account = 'testera'

def main():
	assert(len(sys.argv) == 3), 'Expected usage: python airdrop.py' + \
						  		' snapshot.csv TOKENSYMBOL'
	snapshot_file_name = sys.argv[1]
	token_symbol  = sys.argv[2]
	
	with open(snapshot_file_name, 'r') as snapshot_csv:
		eosio_accounts = {}
		snapshot_reader = csv.reader(snapshot_csv)

		for row in snapshot_reader:
			# { acount_name, balance }
			eosio_accounts[row[1]] = row[3]

	
	memo = 'HorusPay HORUS token airdrop test'
	
	for to_account,quantity_EOS in eosio_accounts.items():
		quantity_NEW = quantity_EOS + ' ' + token_symbol

		print('EOS Account: ' + repr(to_account) + ' EOS Balance: ' + \
			  repr(quantity_EOS) + ' HORUS Issued: ' + quantity_NEW)

		cmd = 'cleos push action eosio.token issue \'["' + to_account + \
				  '","'+ quantity_NEW +'","' + memo + '"]\' -p ' + issuer_account
		os.system(cmd)
		time.sleep(2)

	
	#print(eosio_accounts['haytamrrgu00'])


if __name__ == '__main__':
	main()