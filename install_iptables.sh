#!/bin/sh

echo "正在写入系统配置文件. . ."

curl https://raw.githubusercontent.com/HXHGTS/NATConfigGenerator-iptables/master/limits.conf > /etc/security/limits.conf

curl https://raw.githubusercontent.com/HXHGTS/NATConfigGenerator-iptables/master/sysctl.conf > /etc/sysctl.conf

sysctl -p

echo "正在安装iptables. . ."

yum install iptables -y

exit
