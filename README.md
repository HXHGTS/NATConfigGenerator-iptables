# NATConfigGenerator-iptables

NAT跳转服务器，流量中转，基于iptables，效率高

运行方式(CentOS7)：
```
echo "nameserver 223.5.5.5" > /etc/resolv.conf && wget https://raw.githubusercontent.com/HXHGTS/NATConfigGenerator-iptables/main/NATGenerator-iptables.c -O NATGenerator-iptables.c && gcc -o NATGenerator-iptables NATGenerator-iptables.c && ./NATConfigGenerator-iptables
```
如需基于firewalld转发请使用[这个](https://hxhgts.icu/NATConfigGenerator)
