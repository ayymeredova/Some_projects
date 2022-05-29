#include <syslog.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h> // char * getlogin ( void );
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <sys/file.h>
#include <sys/wait.h> //wait
#include <pthread.h>

#define LOCKFILE "/var/run/lab1_daemon.pid"

// S_IRUSR - доступно пользователю для чтения
// S_IWUSR -  доступно пользователю для записи
// S_IRGRP - group-read — доступно группе для чтения
// S_IROTH - other-read — доступно остальным для чтения
#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

// sigset_t представляет набор сигналов; 
// Единственный компонент в sigset_t — это массив значений типа unsigned long, каждый разряд которого соответствует одному сигналу.
sigset_t mask; 

// Инициализация процесса-демона
// cmd - команда командной строки (имя демона)
void daemonize(const char *cmd) 
{
    int i, fd0, fd1, fd2;
    pid_t pid;
    struct rlimit rl; // структура для хранения пределов на ресурсы
    struct sigaction sa; // структура для изменений действий процесса при получнии соответствующего сигнала
    
    // сбросить маску режима создания файла в значение 0 
	// разрешаем выставлять все биты прав на создаваемые файлы,
    // иначе у нас могут быть проблемы с правами доступа
    umask(0);   // 1

    // получить максимально возможный номер дескриптора файла (для того чтобы закрыть все дескрипторы до этого
    // номера и не удерживать унаследованные дескрипторы в открытом состоянии)
    // RLIMIT_NOFILE - Определяет значение, на 1 больше максимального количества описателей файлов, возможных для открытыя этим процессом. Попытки исполнить 
    //(open(), pipe(), dup(), и т.п.) для превышения этого лимита приведут к ошибке.

    if (getrlimit(RLIMIT_NOFILE, &rl) < 0) 
    {
        printf("Невозможно получить максимальный номер дескриптора\n");
        exit(1);
    }

    // стать лидером новой сессии, чтобы утратить управляющий терминал
    if ((pid = fork()) < 0)   // 2
    {  // При вызове fork() порождается новый процесс (процесс-потомок)
        printf("Ошибка вызова fork\n");
        exit(1);
    }
    else if (pid != 0) 
    {  // завершить родительский процесс 
        exit(0);
    }
    // гарантирует, что дочерний процесс не является лидеров группы для вызова setsid                                                          

    // Создание новой сессии производится с помощью вызова функции setsid (лидер группы, сессии,лишение управляющего терминала)
	if (setsid() == -1)  // 3
    {
    	printf("Проблема с setsid\n");
    	exit(1);
    }
    
    //обеспечить невозможность обретения управляющего терминала путём игнорирования сигнала SIGHUP
   
   // sa_handler задает тип действий процесса, связанный с сигналом signum SIG_IGN для игнорирования сигнала 
   // или sa_handler может быть указателем на функцию обработки сигнала.
    sa.sa_handler = SIG_IGN; 

    //sa_mask; /* дополнительные блокируемые сигналы */ 
    sigemptyset(&sa.sa_mask); // sigemptyset(sigset_t *set) инициализирует пустой набор сигналов, на который указывает аргумент set. 
    sa.sa_flags = 0; // Если выбран 0, обработчик прерываний запускается при разрешенных посторонних прерываниях
    // и возвращает значение через сигнальные функции обработчика. 


    //SIGHUP - управляющий терминал закрыт
    //Функция sigaction позволяет проверить действие, связанное с определенным
    //сигналом, изменить его или выполнить обе эти операции. 
    if (sigaction(SIGHUP, &sa, NULL) < 0) {
        printf("Невозможно игнорировтаь сигнал sighup\n");
        exit(1);
    }


    // назначить корневой каталог текущим рабочим каталогом
    // чтобы в последствии можно было отмонтировать файловую систему
    if (chdir("/") < 0) {       // 4
        printf("Невозможно сделать корневой каталог текущим рабочим каталогом \n");
        exit(1);
    }

    // закрыть все открытые файловые дескрипторы
    if (rl.rlim_max == RLIM_INFINITY){
        rl.rlim_max = 1024; //  в Linux по умолчанию установлен лимит на 1024 одновременно открытых файлов
    }

    for (i = 0; i < rl.rlim_max; i++) {    // 5
        close(i); // освобождает дескриптор файла, т.е. он станет доступен при последующих вызовах open()
    }


	// теперь демон может выводит информацию только в файл 
    // присоединить файловые дескрипторы 0,1,2 

    // O_RDWR - Файл открывается для чтения и для записи.         // 6
    fd0 = open("dev/null", O_RDWR); // "dev/null" специальный файл в системах класса UNIX, представляющий собой так называемое «пустое устройство»
    //dup(int oldfd) - создаёт копию файлового дескриптора oldfd, использует самый маленький свободный номер дескриптора.
    //Файл дескриптор 0 называется STDIN и ассоциируется с вводом данных у приложения
    fd1 = dup(0);
    fd2 = dup(0);

    // инициализировать файл журнала

    // cmd - содержит строку идентификации, которая содержит имя программы
    //LOG_CONS - битовая маска Если сообщение не может быть передано через сокет домена UNIX,
    //оно будет выведено в консоль

    //LOG_DAEMON - позволяет определить,как должны обрабатываться сообщения из разных источников. Системные демоны: inetd, routed, ...
    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != -0 || fd1 != 1 || fd2 != 2) {
        syslog(LOG_ERR, "ошибочные файловые дескрипторы %d %d %d", fd0, fd1, fd2);
        exit(1);
    }
     syslog(LOG_WARNING, "Демон запущен!"); // LOG_WARNING - уровень серьезности сообщения - предупреждение
}

// обеспечение запуска единственного экземпляра демона
// засчет использования блокировок файла и записей
int already_running(void)
{
    syslog(LOG_ERR, "Проверка на многократный запуск");

    int fd;
    char buf[16];

    fd = open(LOCKFILE, O_RDWR | O_CREAT, LOCKMODE); //O_CREAT если файл не существует, он будет создан

    if (fd < 0)
    {
        syslog(LOG_ERR, "Невозможно открыть файл %s: %s", LOCKFILE, strerror(errno));
        exit(1);
    }

    syslog(LOG_WARNING, "Файл открыт");

    //каждая копия демона будет пытаться создать файл fd
    //flock - установить или снять advisory(мягкую) блокировку на открытый файл
    //LOCK_EX - Установить эксклюзивную блокировку. 
	// Только один процесс может держать эксклюзивную блокировку файла.  
	
    //Вызов flock() может быть блокирован, если несовместимый тип блокировки уже удерживается другим процессом. 
	// Чтобы выполнить неблокирующий запрос, включите LOCK_NB
    if (flock(fd, LOCK_EX | LOCK_NB) != 0)    // если файл уже заблокировн, то вернется 1 (демон уже запущен)                             
    {
    	// EWOULDBLOCK - Файл блокирован и был выбран флаг LOCK_NB .
    	if (errno == EWOULDBLOCK)                                                            
    	{
	        syslog(LOG_ERR, "Демон уже запущен %s: %s", LOCKFILE, strerror(errno));
	        close(fd);
	        exit(1);
    	}

    	syslog(LOG_ERR, "Неверный файловый дескриптор"); 
    	exit(1);
	}

	// усекаем файл (чтобы перезапись 12345 на 9999 не привела к 99995)
	// операция усечения файла удаляет информацию, относящуюся к предыдущей копии демона
    ftruncate(fd, 0);  // укорачивает файл до указанной длины (0)
    sprintf(buf, "%ld", (long)getpid()); //запись в массив
    write(fd, buf, strlen(buf) + 1); // запись в файл

    syslog(LOG_WARNING, "PID записано в файл");
     
    return 0;
}


// имени текущего пользователя и времени syslog
void output_data()
{
    time_t raw_time;
    struct tm *time_info;
    char buf[70];

    time(&raw_time);
    time_info = localtime(&raw_time);
    
    sprintf(buf, "ДЕМОН РАБОТАЕТ, ПОЛЬЗОВАТЕЛЬ: %s; ВРЕМЯ: %s", getlogin(), asctime(time_info));
    syslog(LOG_INFO, buf);
}

void *thr_fn(void *arg)
{
    int signo;
    int code_error = 0;
    while(!code_error)
    {
        code_error = sigwait(&mask, &signo);
        switch (signo)
        {
        case SIGHUP:
			syslog(LOG_INFO, "ПРИНЯТ СИГНАЛ SIGHUP - ВЫВЕСТИ ИМЯ ПОЛЬЗОВАТЕЛЯ И ВРЕМЯ \n");
            time_t raw_time;
			struct tm *time_info;
			char buf[70];

			time(&raw_time);
			time_info = localtime(&raw_time);
			
			sprintf(buf, "ДЕМОН РАБОТАЕТ, ПОЛЬЗОВАТЕЛЬ: %s; ВРЕМЯ: %s", getlogin(), asctime(time_info));
			syslog(LOG_INFO, buf);
            break;
        case SIGTERM:
            syslog(LOG_INFO, "ПРИНЯТ СИГНАЛ SIGTERM - ЗАВЕРШИТЬ ПРОЦЕСС\n");
            return 0;
            break;
        default:
            syslog(LOG_INFO, "ПРИНЯТ НЕПРЕДВИДЕННЫЙ СИГНАЛ - %d\n", signo);
            break;
        }
    }
    return code_error;
}


int main(int argc, char *argv[]) 
{
    int err;
    pthread_t tid;    
    char *cmd;
    struct sigaction sa;

    // strrchr(const char * str, int symbol) - Функция ищет последнее вхождение символа symbol в строку string
    if ((cmd = strrchr(argv[0], '/')) == NULL)
    {
        cmd = argv[0];
    }
    else
        cmd++;

    // cmd теперь == main - это команда и это имя демона

    // переход в режим демона 
    daemonize(cmd);

    // убеждаемся в том, что ранее не был запущен другой экземпляр демона 
    if (already_running() != 0) {
        syslog(LOG_ERR, "Демон уже запущен\n");
        exit(1);
    }

    //Восстановить действие по умолчанию для сигнала SIGHUP и заблокировать все сигналы.
	// sa_handler задает тип действий процесса, связанный с сигналом signum; SIG_DFL - для выполнения стандартных действий
    sa.sa_handler = SIG_DFL; // Использyется с сигнальной функцией на месте yказателя на обpаботчик пpеpывания для выбоpа стандаpтного обpаботчика пpеpывания опеpационной системы.
    sigemptyset(&sa.sa_mask);  //sigemptyset инициализирует набор сигналов, указанный в set, и "очищает" его от всех сигналов.
	// sa_mask задает маску сигналов, которые должны блокироваться при обработке сигнала
    
    sa.sa_flags = 0;

    if (sigaction(SIGHUP, &sa, NULL) < 0){
        syslog(LOG_ERR, "Не удалось установить SIG_DFL на SIGHUP\n");
        exit(1);
    }

	//sigfillset полностью инициализирует набор set, в котором содержатся все сигналы.
    sigfillset(&mask);
    //pthread_sigmask - проверить и изменить маску заблокированных сигналов
    if ((err = pthread_sigmask(SIG_BLOCK, &mask, NULL)) != 0)
    {
        syslog(LOG_ERR, "Не удалось установить SIG_BLOCK\n");
        exit(1);
    }

    // создание потока, который будет заниматься обработкой SIGHUP и SIGTERM
    err = pthread_create(&tid, NULL, thr_fn, 0);
    if (err != 0){
        syslog(LOG_ERR, "Ошибка создания потока\n");
        exit(1); 
    }

    pthread_join(tid, NULL);
	
    exit(0);
}
