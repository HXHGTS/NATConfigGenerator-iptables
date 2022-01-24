#!/bin/sh

echo "正在写入系统配置文件. . ."

curl https://cdn.jsdelivr.net/gh/HXHGTS/TCPOptimization/limits.conf > /etc/security/limits.conf

curl https://cdn.jsdelivr.net/gh/HXHGTS/TCPOptimization/sysctl.conf > /etc/sysctl.conf

sysctl -p

echo "正在安装iptables与nslookup. . ."

yum install bind-utils -y

yum update iptables iptables-persistent iptables-services -y

echo "正在配置iptables默认规则. . ."

iptables -P INPUT ACCEPT

iptables -P OUTPUT ACCEPT

iptables -F

iptables -X

iptables -Z

service iptables save

echo "正在启动iptables. . ."

systemctl restart iptables.service

exit
