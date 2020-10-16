#!/usr/bin/env python3
import socket
import os
import json

SERVER_ADDR = ""
PORT = 50000


def cpu_load():
    with open("/proc/loadavg", "r") as cpu_file:
        line = cpu_file.readline()
    load = float(line[:4])
    return load


def logged_in_users():
    command = "who | awk -F ' ' '{print $1}' | sort -u | wc -l"
    shell_output = [line.strip() for line in os.popen(command)]
    users = int(shell_output[0])
    return users


def data_to_paylod():
    payload_dic = {
        "cpu"   : cpu_load(),
        "user" : logged_in_users(),
    }
    payload = json.dumps(payload_dic)
    return payload.encode()


def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        s.bind((SERVER_ADDR, PORT))
        while True:
            daten, client_addr = s.recvfrom(1024)
            print("[{}] {}".format(client_addr[0], daten.decode()))
            s.sendto(data_to_paylod(), client_addr)
    finally:
        s.close()


if __name__ == "__main__":
    main()

