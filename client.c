
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    int sockfd, len;
    struct sockaddr_un address;
    int res;
    char ch = 'A';

    // 创建一个客户端套接字
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    // 根据服务器情况给套接字命名
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket");
    len = sizeof(address);

    // 将客户套接字连接到服务器套接字
    res = connect(sockfd, (struct sockaddr *)&address, len);
    if(res == -1)
    {
        perror("err");
        exit(1);
    }

    write(sockfd, &ch, 1);
    read(sockfd, &ch, 1);
    printf("char from server = %c\n", ch);
    close(sockfd);

    return 0;
}