cmake_minimum_required(VERSION "3.16.3")

project("Distributed_Systems")

add_executable("load_client" "01_load_deamon/client.c")
add_executable("load_deamon" "01_load_deamon/server.c")
add_executable("ssh_proxy"   "02_ssh_proxy/tcp_proxy.c")
