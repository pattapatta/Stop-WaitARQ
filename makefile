client_swarq.o: 
	g++ -c -I ./include ./src/client_swarq.cpp -o client_swarq.o

frame.o: 
	g++ -c -I ./include ./src/frame.cpp -o frame.o

file_reader.o: 
	g++ -c -I ./include ./src/file_reader.cpp -o file_reader.o

server_swarq.o: 
	g++ -c -I ./include ./src/server_swarq.cpp -o server_swarq.o

test_client.o:
	g++ -c -I ./include ./test/test_client.cpp -o test_client.o

test_server.o:
	g++ -c -I ./include ./test/test_server.cpp -o test_server.o

test_client: test_client.o client_swarq.o frame.o file_reader.o
	g++ test_client.o client_swarq.o frame.o file_reader.o -lboost_system -lpthread -o test_client

test_server: test_server.o server_swarq.o frame.o
	g++ test_server.o server_swarq.o frame.o -lboost_system -lpthread -o test_server
clean:
	rm client_swarq.o frame.o file_reader.o server_swarq.o test_client.o test_server.o


