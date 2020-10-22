#include <stdio.h>
#include <stdlib.h>

int ServerStartNum, ServerEndNum, NATStartNum, NATEndNum, PortGap, ServerPort, NATPort,mode;
int ip1,ip2,ip3,ip4;
char cmd[200], protocol[5],local_ip[16];
FILE* info;
int main() {
	preload();
	system("clear");
	UI();
	if (mode == 3) {
		CheckNAT();
	}
	else if (mode == 1 || mode == 2) {
		printf("请输入远程服务器起始端口号-终止端口号，如10000-20000:");
		scanf("%d-%d", &ServerStartNum, &ServerEndNum);
		printf("\n");
		printf("请输入中转服务器起始端口号-终止端口号，如10000-20000:");
		scanf("%d-%d", &NATStartNum, &NATEndNum);
		printf("\n");
		printf("请输入端口号间隔:");
		scanf("%d", &PortGap);
		printf("\n");
		printf("请输入远程服务器ip，注意中间点改成空格，如8.8.8.8请写为8 8 8 8:");
		scanf("%d %d %d %d", &ip1, &ip2, &ip3, &ip4);
		printf("\n");
		printf("请输入转发协议(t=tcp or u=udp):");
		scanf("%s", protocol);
		printf("\n");
		if (CheckInput()==1) {
			printf("非法输入，请检查输入！\n");
		}
		else {
			NATProtocol();
			if (mode == 1) {
				AddNAT();
				printf("\n\n");
				printf("执行完成!\n");
			}
			else {
				DelNAT();
				printf("\n\n");
				printf("生成完成!\n");
			}
			printf("\n");
			printf("执行完成！\n");
		}
	}
	else if (mode == 4) {
		printf("正在删除iptables规则. . .\n");
		system("iptables -F");
		printf("正在关闭iptables模块. . .\n");
		system("systemctl stop iptables");
		system("systemctl disable iptables");
		printf("执行完成！\n");
	}
	else if (mode == 5) {
		system("wget https://raw.githubusercontent.com/HXHGTS/NATConfigGenerator-iptables/main/install_iptables.sh -O install_iptables.sh");
		system("chmod +x install_iptables.sh");
		system("bash install_iptables.sh");
		system("rm -f install_iptables.sh");
		printf("执行完成！\n");
	}
	else{
		exit(0);
	}
	return 0;
}

int UI() {
	printf("请注意：本软件仅支持CentOS系统，其它Linux系统不支持！\n\n");
	printf("请选择要执行的操作：\n\n1.添加转发规则\n\n2.删除转发规则\n\n3.查询转发规则\n\n4.关闭iptables\n\n5.安装并开启iptables(第一次使用建议执行，否则可能会转发失败)\n\n0.退出\n\n请输入：");
	scanf("%d", &mode);
	printf("\n");
	return 0;
}

int AddNAT() {
	for (ServerPort = ServerStartNum, NATPort = NATStartNum; ServerPort <= ServerEndNum; ServerPort = ServerPort + PortGap, NATPort = NATPort + PortGap) {
		sprintf(cmd, "iptables -t nat -A PREROUTING -p %s --dport %d -j DNAT --to-destination %d.%d.%d.%d:%d",protocol,NATPort,ip1,ip2,ip3,ip4,ServerPort);
		system(cmd);
		sprintf(cmd, "iptables -t nat -A POSTROUTING -p %s -d %d.%d.%d.%d --dport %d -j SNAT --to-source %s", protocol,ip1,ip2,ip3,ip4,ServerPort, local_ip);
		system(cmd);
	}
	system("service iptables save");
	return 0;
}

int DelNAT(){
	int rule;
	CheckNAT();
	printf("想要删除第几行规则:");
	scanf("%d", &rule);
	sprintf(cmd,"iptables -t nat -D POSTROUTING %d",rule);
	system(cmd);
	sprintf(cmd,"iptables -t nat -D PREROUTING %d",rule);
	system(cmd);
	system("clear");
	CheckNAT();
	return 0;
}

int CheckNAT() {
	printf("系统NAT设置记录:\n\n");
	system("iptables -t nat -vnL POSTROUTING");
	system("iptables -t nat -vnL PREROUTING");
	printf("\n");
	return 0;
}

int CheckInput() {
	if (mode == 1 || mode == 2) {
		if (ServerStartNum > ServerEndNum || NATStartNum > NATEndNum || ServerStartNum > 65535 || ServerEndNum > 65535 || NATStartNum > 65535 || NATEndNum > 65535) {
			return 1;
		}
		else {
			return 0;
		}
	}
}

int NATProtocol() {
	if (protocol[0] == 't') {
		sprintf(protocol, "tcp");
	}
	else {
		sprintf(protocol, "udp");
	}
	return 0;
}

int preload() {
	char netmask[16], public_ip[16];
	printf("正在获取网卡信息. . .\n");
	system("ifconfig | grep inet | grep -v inet6 | grep -v 127.0.0.1 > net_info.txt");
	info = fopen("net_info.txt", "r");
	fscanf(info, "        inet %s  netmask %s  broadcast %s", local_ip, netmask, public_ip);
	fclose(info);
}
