#!/bin/sh

echo "正在优化大文件读写性能. . ."

curl https://raw.githubusercontent.com/HXHGTS/NATConfigGenerator-iptables/master/limits.conf > /etc/security/limits.conf

echo "正在优化文件io性能. . ."

curl https://raw.githubusercontent.com/HXHGTS/NATConfigGenerator-iptables/master/sysctl.conf > /etc/sysctl.conf

sysctl -p

yum install iptables -y

