app: ../implementation_hash_table/ideal_hash.c testing_p3.c
	gcc -O3 ../implementation_hash_table/ideal_hash.c testing_p3.c -o app

open_hash_app: ../implementation_hash_table/open_hash.c ../implementation_hash_table/hash_func.c testing_p3.c
	gcc -O3 ../implementation_hash_table/open_hash.c ../implementation_hash_table/hash_func.c testing_p3.c -o open_hash_app

open_metod_chain_app: ../implementation_hash_table/metod_chain.c ../implementation_hash_table/hash_func.c testing_p3.c
	gcc -O3 ../implementation_hash_table/metod_chain.c ../implementation_hash_table/hash_func.c testing_p3.c -o open_metod_chain_app

run_app: app
	./app

run_open_hash_app: open_hash_app
	./open_hash_app

run_metod_chain_app: open_metod_chain_app
	./open_hash_app

