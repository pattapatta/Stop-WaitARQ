client_swarq.o: ./src/client_swarq.cpp
	g++ -c -I ./include ./src/client_swarq.cpp -o client_swarq.o

frame.o: ./src/frame.cpp
	g++ -c -I ./include ./src/frame.cpp -o frame.o

file_reader.o: ./src/file_reader.cpp
	g++ -c -I ./include ./src/file_reader.cpp -o file_reader.o

server_swarq.o: ./src/server_swarq.cpp
	g++ -c -I ./include ./src/server_swarq.cpp -o server_swarq.o

test_client.o: ./test/test_client.cpp
	g++ -c -I ./include ./test/test_client.cpp -o test_client.o

test_server.o: ./test/test_server.cpp
	g++ -c -I ./include ./test/test_server.cpp -o test_server.o

test_client: test_client.o client_swarq.o frame.o file_reader.o
	g++ test_client.o client_swarq.o frame.o file_reader.o -lboost_system -lpthread -o test_client

test_server: test_server.o server_swarq.o frame.o
	g++ test_server.o server_swarq.o frame.o -lboost_system -lpthread -o test_server
clean:
	rm client_swarq.o frame.o file_reader.o server_swarq.o test_client.o test_server.o


