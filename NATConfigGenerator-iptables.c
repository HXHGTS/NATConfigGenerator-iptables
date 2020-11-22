#include <stdio.h>
#include <stdlib.h>

int ServerStartNum, ServerEndNum, NATStartNum, NATEndNum, PortGap, ServerPort, NATPort,mode;
char cmd[300], protocol[5],local_ip[16],ip[40];
FILE* info,*resolve;
int main() {
	preload();
	system("clear");
	MENU:UI();
	if (mode == 1) {
		CheckNAT();
		printf("请输入远程服务器起始端口号-终止端口号，如10000-20000:");
		scanf("%d-%d", &ServerStartNum, &ServerEndNum);
		printf("\n");
		printf("请输入中转服务器起始端口号-终止端口号，如10000-20000:");
		scanf("%d-%d", &NATStartNum, &NATEndNum);
		printf("\n");
		printf("请输入端口号间隔:");
		scanf("%d", &PortGap);
		printf("\n");
		printf("请输入远程服务器域名或ip，如8.8.8.8:");
		scanf("%s", ip);
		printf("\n");
		printf("请输入转发协议(t=tcp or u=udp):");
		scanf("%s", protocol);
		printf("\n");
	if (CheckInput() == 1) {
		printf("非法输入，请检查输入！\n");
	}
	else {
		NATProtocol();
		AddNAT();
		printf("\n\n");
		printf("执行完成!\n");
		goto MENU;
	}
	}
	else if (mode == 2) {
		DelNAT();
		printf("\n\n");
		printf("执行完成！\n");
		goto MENU;
	}
	else if (mode == 3) {
		CheckNAT();
		goto MENU;
	}
	else if (mode == 4) {
		printf("正在删除iptables规则. . .\n");
		system("iptables -F");
		printf("正在关闭iptables模块. . .\n");
		system("systemctl stop iptables");
		system("systemctl disable iptables");
		printf("执行完成！\n");
		goto MENU;
	}
	else if (mode == 5) {
		system("wget https://raw.githubusercontent.com/HXHGTS/NATConfigGenerator-iptables/main/install_iptables.sh -O install_iptables.sh");
		system("chmod +x install_iptables.sh");
		system("bash install_iptables.sh");
		system("rm -f install_iptables.sh");
		printf("执行完成！\n");
		goto MENU;
	}
	else{
		exit(0);
	}
	return 0;
}

int Domain_Transfer() {
	if (ip[0] != '0' && ip[0] != '1' && ip[0] != '2' && ip[0] != '3' && ip[0] != '4' && ip[0] != '5' && ip[0] != '6' && ip[0] != '7' && ip[0] != '8' && ip[0] != '9') {
		sprintf(cmd, "nslookup -q=A %s | grep 'Address:' | grep -v '#53' > dns.resolve",ip);
		system(cmd);
		resolve = fopen("dns.resolve", "r");
		fscanf(resolve, "Address: %s",ip);
		fclose(resolve);
		system("rm -f dns.resolve");
	}
	return 0;
}

int UI() {
	printf("请注意：本软件仅支持CentOS系统，其它Linux系统不支持！\n\n");
	printf("请选择要执行的操作：\n\n1.添加转发规则\n\n2.删除转发规则\n\n3.查询并备份转发规则\n\n4.关闭iptables\n\n5.安装并开启iptables(第一次使用建议执行，否则可能会转发失败)\n\n0.退出\n\n请输入：");
	scanf("%d", &mode);
	printf("\n");
	return 0;
}

int AddNAT() {
	Domain_Transfer();
	for (ServerPort = ServerStartNum, NATPort = NATStartNum; ServerPort <= ServerEndNum; ServerPort = ServerPort + PortGap, NATPort = NATPort + PortGap) {
		sprintf(cmd, "iptables -t nat -A PREROUTING -p %s --dport %d -j DNAT --to-destination %s:%d",protocol,NATPort,ip,ServerPort);
		system(cmd);
		sprintf(cmd, "iptables -t nat -A POSTROUTING -p %s -d %s --dport %d -j SNAT --to-source %s", protocol,ip,ServerPort, local_ip);
		system(cmd);
	}
	system("service iptables save");
	return 0;
}

int DelNAT(){
	int rule;
	CheckNAT();
	printf("出站与入站规则同时配置，如果删除会被同时删除！\n");
	printf("想要删除第几行规则（只看出站或入站规则即可）:");
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
	printf("出站规则:\n");
	system("iptables -t nat -vnL POSTROUTING");
	printf("入站规则:\n");
	system("iptables -t nat -vnL PREROUTING");
	printf("\n");
	printf("正在备份规则. . .\n");
	system("echo '出站规则' > route.backup");
	system("iptables -t nat -vnL POSTROUTING  >> route.backup");
	system("echo '入站规则' >> route.backup");
	system("iptables -t nat -vnL PREROUTING  >> route.backup");
	printf("规则已备份至/root/route.backup\n");
	return 0;
}

int CheckInput() {
	if (mode == 1) {
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
	system("rm -f net_info.txt");
}
