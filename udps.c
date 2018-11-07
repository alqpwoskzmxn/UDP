#include "headerFiles.h"

int main(void){
	int s;
	int len;
	char buffer[256];
	struct sockaddr_in servAddr;
	struct sockaddr_in clntAddr;
	int clntAddrLen = sizeof(clntAddr);
	DIR *dir;
	struct dirent *direntry;
	
	if((dir = opendir("./Videos")) == 0)
	{
		perror("Directory not found!");
		return 0;
	}

	
	
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(8000);
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Error:Creating Socket Failed!");
		return 0;
	}
	
	if(bind(s, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0)
	{
		perror("Error:Binding Socket Failed!");
		return 0;
	}
	
	for(;;)
	{
		len = recvfrom(s, buffer, 5, 0, (struct sockaddr*)&clntAddr, &clntAddrLen);

		if(len > 0)
		{
			buffer[5] = '\0';
			printf("%s", buffer);

			sendto(s, buffer, len, 0, (struct sockaddr*)&clntAddr, sizeof(clntAddr));

			recvfrom(s, buffer, sizeof(buffer), 0, (struct sockaddr*)&clntAddr, sizeof(clntAddr));

			
		
		}
	}
	
}
