import socket

def session(sock):
    try:
        while True:
            msg = input("enter message: ")
            sock.sendall(msg.encode())
            if msg == "exit":
                print("client exit")
                break

            data = sock.recv(1024).decode()
            print("message from server:", data)
            if data == "exit":
                print("client exit")
                break
    except Exception as e:
        print("session ended:", e)

def main():
    try:
        host, port = "127.0.0.1", 8000
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((host, port))
        print("connected to server")

        session(sock)
    except Exception as e:
        print("[Exception]:", e)

if __name__ == "__main__":
    main()
