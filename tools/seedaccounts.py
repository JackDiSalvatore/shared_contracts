# Title: seedaccounts.py
# Description: creates eosio accounts from snapshot file
#
import os, sys, csv, time

account_creator = 'eosio'
public_key = 'EOS8fMgnGaH4FvKPUWFioZcPQHdwb71omadNUUu1q4Ft9LaikH8su' # Fake public key for testing

def main():
	assert(len(sys.argv) == 2), 'Expected usage: python accountseed.py' + \
						  		' snapshot.csv'
	snapshot_file_name = sys.argv[1]
	
	eosio_accounts = {}

	with open(snapshot_file_name, 'r') as snapshot_csv:
		snapshot_reader = csv.reader(snapshot_csv)

		for row in snapshot_reader:
			# { acount_name, balance }
			eosio_accounts[row[1]] = public_key # row[2]

	for account,key in eosio_accounts.items():
	 	print repr(account.strip('0')), repr(key)

	 	cmd = 'cleos create account ' + account_creator + ' ' + account.strip('0') + \
			  ' ' + public_key + ' ' + public_key
		os.system(cmd)
		time.sleep(2)

	#os.system('cleos wallet list')

if __name__ == '__main__':
	main()