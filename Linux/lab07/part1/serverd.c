#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <signal.h>

// 1.Организовать взаимодействие параллельных процессов на отдельном компьютере.

#define PATH "/dev/sock.soc"
#define BUF_LEN 256


int sock;

void catch_ctrlc(int signum)
{
    printf("Получен сигнал Ctrl+C - остановка работы сервера\n");
    close(sock);

    //Перед выходом из программы-сервера следует удалить файл сокета, созданный в результате вызова socket()
    unlink(PATH);
}


int main()
{
	// Для сокетов Unix (сокетов в файловом пространстве имен)
	// есть специализированная структура sockaddr_un - адрес сервера
    struct sockaddr_un server_addr;
    char message[BUF_LEN];
    int er_flag = 0;
    int message_len = 0;
	
	// Создание сокета в файловом пространстве имен 
	// Домен -- обозн. тип соединения AF_UNIX (локальн. соед-е)
	// адреса интерпретируются как имена файлов в UNIX.
	// Тип сокета -- SOCK_DGRAM означает датаграммный сокет сохраняющий границы сообщений 
	// В пространстве файловых имен датаграммные сокеты также надежны, как и потоковые сокеты.
	// Протокол -- 0, протокол выбирается по умолчанию
	// (домен, тип, протокол), возвр дескриптор сокета
    sock = socket(AF_UNIX, SOCK_DGRAM, 0); 
    if (sock < 0)
    {
        printf("%s", strerror(errno));
        return EXIT_FAILURE;
    }

    // семейство адресов, которыми мы будем пользоваться
    server_addr.sun_family = AF_UNIX; 
	// имя файла сокета
    strcpy(server_addr.sun_path, PATH);

    // bind(дескриптор сокета, указатель на структуру, длина структуры)
    // связывает дескриптор сокета к заданному адресу. (присв-е имени)
    //   struct sockaddr 
    // { 
    //        unsigned short sa_family; // Семейство адресов, AF_xxx 
    //        char sa_data[14]; // 14 байтов для хранения адреса 
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) 
    {
        printf("%s", strerror(errno));
        return EXIT_FAILURE;
    }
	
	// отслеживаем сигнал
    signal(SIGINT, catch_ctrlc);

	// программа-сервер доступна для соединения по заданному адресу (имени файла)
    while (!er_flag)
    {
		// Для чтения данных из датаграммного сокета - recvfrom,
		// блокирует программу,пока на входе не появятся новые данные
		// Так как нас не интересуют данные об адресе клиента - NULL в предпоследнем и последнем параметрах
        if ((message_len = recvfrom(sock, message, BUF_LEN, 0, NULL, NULL)) < 0) 
        {
            printf("%s", strerror(errno));
            er_flag = 1;
        }

		message[message_len] = 0;
		printf("== Получено сообщение == : %s\n", message);
    }
	
	// Закрываем сокет
    close(sock);
	// Удаляем файл сокета
    unlink(PATH);

    return -er_flag;
}