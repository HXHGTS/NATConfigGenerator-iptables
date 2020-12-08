#!/bin/sh

echo "正在写入系统配置文件. . ."

curl https://raw.githubusercontent.com/HXHGTS/NATConfigGenerator-iptables/main/limits.conf > /etc/security/limits.conf

curl https://raw.githubusercontent.com/HXHGTS/NATConfigGenerator-iptables/main/sysctl.conf > /etc/sysctl.conf

sysctl -p

echo "正在安装iptables与nslookup. . ."

yum install iptables iptables-services -y

yum install bind-utils -y

echo "正在配置iptables默认规则. . ."

iptables -P INPUT ACCEPT

iptables -F

iptables -X

iptables -Z

iptables -P INPUT DROP

iptables -P OUTPUT ACCEPT

iptables -P FORWARD DROP

iptables -A INPUT -i lo -j ACCEPT

iptables -A INPUT -p tcp --dport 22 -j ACCEPT

iptables -A INPUT -p icmp --icmp-type echo-request -j ACCEPT

iptables -A OUTPUT -p icmp --icmp-type echo-reply -j ACCEPT

service iptables save

echo "正在启动iptables. . ."

systemctl restart iptables.service

exit
