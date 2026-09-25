import socket, subprocess

HOST = "0.0.0.0"
PORT = 5000

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server.bind((HOST, PORT))
server.listen(1)

print("Esperando coneccion ...")
connection, address = server.accept()
print("Conectado:", address)
seed = input("Ingrese el valor privado tuyo: ")
resultado = subprocess.run(["./dh.exe","101","2",seed], capture_output=True)
llave_A = resultado.stdout.strip()
connection.sendall(llave_A)
llave_B = connection.recv(1024).decode()
connection.close()
server.close()
resultado = subprocess.run(["./dh.exe","101","2",seed, llave_B], capture_output=True)
llave_K = resultado.stdout.strip().decode()
print(f'LLave Privada: {llave_K}')
