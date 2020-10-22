# NATConfigGenerator-iptables

基于iptables的NAT转发规则配置脚本

运行方式(CentOS7)：
```
echo "nameserver 119.29.29.29" > /etc/resolv.conf && wget https://raw.githubusercontent.com/HXHGTS/NATConfigGenerator-iptables/main/NATGenerator-iptables.c -O NATGenerator-iptables.c && gcc -o NATGenerator-iptables NATGenerator-iptables.c && ./NATConfigGenerator-iptables
```
如需基于firewalld转发请使用[这个](https://hxhgts.icu/NATConfigGenerator)
