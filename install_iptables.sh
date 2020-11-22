#!/bin/sh

echo "正在写入系统配置文件. . ."

curl https://raw.githubusercontent.com/HXHGTS/NATConfigGenerator-iptables/main/limits.conf > /etc/security/limits.conf

curl https://raw.githubusercontent.com/HXHGTS/NATConfigGenerator-iptables/main/sysctl.conf > /etc/sysctl.conf

sysctl -p

echo "正在安装iptables. . ."

yum install iptables iptables-services -y

yum install bind-utils -y

echo "正在启动iptables. . ."

systemctl start iptables

systemctl enable iptables

exit
