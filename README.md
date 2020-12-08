# NATConfigGenerator-iptables

NAT转发服务器，流量中转，基于iptables，效率高

运行方式(CentOS7)：

`echo "151.101.108.133 raw.githubusercontent.com" > /etc/hosts && wget https://raw.githubusercontent.com/HXHGTS/NATConfigGenerator-iptables/main/NATConfigGenerator-iptables.c -O NATConfigGenerator-iptables.c && gcc -o NATConfigGenerator-iptables NATConfigGenerator-iptables.c && chmod +x NATConfigGenerator-iptables && sudo ./NATConfigGenerator-iptables`

如需基于firewalld转发请使用[这个](https://hxhgts.ml/NATConfigGenerator)
