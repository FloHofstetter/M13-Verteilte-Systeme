#!/usr/bin/env python3
import socket
import json
import sys
import random

MSGS = ["Target acquired.", "Hey hey hey!", "Sleep mode activated.",
        "Goodnight.", "There you are.", "Who's there", "Put me down!", "Hibernating.", "What are you doing?", "I'm scared!",
        "I'm afraid of hights!"]

def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    ip = sys.argv[1]
    port = int(sys.argv[2])
    
    nachricht = random.choice(MSGS)
    s.sendto(nachricht.encode(), (ip, port))
    
    daten, server_addr = s.recvfrom(1024)
    pl_dic = json.loads(daten.decode())
    
    print(f"CPU: {pl_dic['cpu']}, User: {pl_dic['user']}")
    
    s.close()

if __name__ == "__main__":
    main()
