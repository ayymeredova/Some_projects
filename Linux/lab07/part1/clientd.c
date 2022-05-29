#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

// некоторые системы разрешают создать сокет только в некоторых директориях
#define PATH "/dev/sock.soc"  
#define BUF_LEN 256

int main(int argc, char **argv)
{
    struct sockaddr_un server_addr;  //адрес сервера
    int c_pid; //pid клиента
    char message[BUF_LEN];
    //   struct sockaddr 
    // { 
    //        unsigned short sa_family; // Семейство адресов, AF_xxx 
    //        char sa_data[14]; // 14 байтов для хранения адреса 


   // Создание сокета в файловом пространстве имен 
   // Домен -- обозн. тип соединения AF_UNIX (локальн. соед-е)
   // Тип сокета -- SOCK_DGRAM -датаграммный сокет
   // Протокол -- 0 - протокол выбирается по умолчанию
    int sock = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        printf("%s", strerror(errno));
        return EXIT_FAILURE;
    }

	// Укажем семейство адресов, которыми мы будем пользоваться
    server_addr.sun_family = AF_UNIX;
	// Укажем имя файла сокета
    strcpy(server_addr.sun_path, PATH);

    // Получаем pid клиента 
    c_pid =  getpid();

    while (1)
    {
        printf("== Сообщение клиента (pid = %d) == : ", c_pid);
        fgets(message, BUF_LEN, stdin);
        printf("\n");

        // отправка серверу
        // Первый пар-р – дескриптор сокета, 
		// второй и третий пар-ры - адрес буфера для передачи данных и его длина.
        // Четвертый пар-р - для передачи дополнительных флагов.
        // Предпоследний и последний пар-ры - адрес сервера и его длина
        sendto(sock, message, strlen(message), 0,
               (struct sockaddr *)&server_addr, sizeof(server_addr));
    }

    return EXIT_SUCCESS;
}