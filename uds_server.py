import socket
import os

import time

# Set the path for the Unix socket
socket_path = '/tmp/latency_tester_socket'

# remove the socket file if it already exists
try:
    os.unlink(socket_path)
except OSError:
    if os.path.exists(socket_path):
        raise

# Create the Unix socket server
server = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)

# Bind the socket to the path
server.bind(socket_path)

# Listen for incoming connections
server.listen(1)

# accept connections
print('Server is listening for incoming connections...')
connection, client_address = server.accept()

start_time = time.time()
end_time = time.time()

last_time = time.time()

try:
    print('Connection from', str(connection).split(", ")[0][-4:])

    # receive data from the client
    while True:
        data_len = 1
        data_len = 8
        data = connection.recv(data_len + 1)
        if not data:
            break
        #print('Received data:', data.decode())

        data = data.decode()

        now = time.time()

        """
        if data[0] == 's':
            print(f's {(now - end_time) * 1000:.2f} ms --- {(now - start_time) * 1000:.2f} ms')
            start_time = now
        if data[0] == 'e':
            print(f'e {(now - start_time) * 1000:.2f} ms')
            end_time = now
        """

        print(f'{data} - {(now - last_time) * 1000:.2f}')
        last_time = now

        

finally:
    # close the connection
    connection.close()
    # remove the socket file
    os.unlink(socket_path)
