import socket, subprocess# Libreria para abrir sockets
HOST = "192.168.1.50"
PORT = 5000
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((HOST, PORT))
print("Conectado!")
seed = input("Ingrese el valor privado tuyo: ")
resultado = subprocess.run(["./dh.exe","101","2",seed], capture_output=True)
llave_A = resultado.stdout.strip()
llave_B = client.recv(1024).decode()
client.sendall(llave_A)
client.close()
resultado = subprocess.run(["./dh.exe","101","2",seed, llave_B], capture_output=True)
llave_K = resultado.stdout.strip().decode()
print(f'LLave Privada: {llave_K}')
