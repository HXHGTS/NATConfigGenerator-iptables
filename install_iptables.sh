#!/bin/sh

echo "正在写入系统配置文件. . ."

curl https://cdn.jsdelivr.net/gh/HXHGTS/NATConfigGenerator-iptables/limits.conf > /etc/security/limits.conf

curl https://cdn.jsdelivr.net/gh/HXHGTS/NATConfigGenerator-iptables/sysctl.conf > /etc/sysctl.conf

sysctl -p

echo "正在安装iptables与nslookup. . ."

yum install gcc gcc-c++ bzip2 iptables iptables-services bind-utils -y

wget http://ftp.netfilter.org/pub/iptables/iptables-1.8.7.tar.bz2

tar -xjf iptables-1.8.7.tar.bz2

cd iptables-1.8.7

./configure --disable-nftables

make & make install

cd /usr/local/sbin

cp -rf /usr/local/sbin/iptables /sbin/

cp -rf /usr/local/sbin/iptables-restore /sbin/

cp -rf /usr/local/sbin/iptables-save /sbin/

echo "正在配置iptables默认规则. . ."

iptables -P INPUT ACCEPT

iptables -P OUTPUT ACCEPT

iptables -F

iptables -X

iptables -Z

service iptables save

echo "正在启动iptables. . ."

systemctl start iptables.service

exit
