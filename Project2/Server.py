import threading
import socket
host='127.0.0.1'
port=59000
server= socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server.bind((host,port))
server.listen()
clients=[]
aliases=[]

def broadcast(message):
    for client in client:
        client.send(message)

def handle_client(client):
    while True:
        try:
            message= client.recv(1024)
            broadcast(message)
        except:
            index=clients.index(client)
            clients.remove(client)
            client.close()
            alias=aliases[index]
            broadcast(f'{alias} has left the chat room'.encode())
            aliases.remove(alias)
            break

def receive():
    while True:
        print(" server is running and listening...")
        client,address=server.accept()
        print(f'connection is established with {str(address)}')
        client.send('alias?'.encode('utf-8'))
        alias=client.recv(1024)
        aliases.append(alias)
        clients.apend(client)
        print(f'the alias of this client is {alias}'.encode('utfd8'))
        broadcast(f'{alias} has connected to chat room'.encode('utf-8'))
        client.send('you are now connected!'.encode('utf-8'))
        thread=threading.Thread(target=handle_client,args=(client,))
        thread.start()

if __name__=="__main__"  :
    receive()      
