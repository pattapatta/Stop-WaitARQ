Stop-WaitARQ
============

Stop&amp;WaitARQ Server-Client System

Sviluppato da: Andrea Segalini e Lorenzo Pattarini in c++/boost.

Eseguire i due programmi "test_server" e "test_client".

Usage:
	
	$./test_server <port>

	$./test_client <ip_addr> <port> <path_source_file> <path_dest_file> <buffer_size> <timeout>

Compilazione: è presente un makefile, per compilare i due programmi di test (test_client e test_server) fare:
	
	$make test_client
	
	$make_test_server


