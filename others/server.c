#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_un server_address, client_address;

    // 删除之前的套接字
    unlink("server_socket");
    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    
    // 命名套接字
    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "server_socket");
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr*)&server_address, server_len);

    // 创建一个链接队列
    listen(server_sockfd, 5);
    while(1)
    {
        char ch;

        printf("server waitting\n");

        //接受一个链接
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, NULL, 0);
        
        // 读写client socket
        read(client_sockfd, &ch, 1);
        ch++;
        write(client_sockfd, &ch, 1);
        close(client_sockfd);
    }

    return 0;
}
