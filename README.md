# nefteavtomatika
Тестовой вариант 1 (Linux)

* ******************************************************************************
# Стандарт:
* C++17 - для std::optional
* ******************************************************************************
# Окружение:
* gcc 14.2.0
* WSL-2 (Debian 14.2.0-19)
* UDP Sender/Receiver (Microsoft store) - тестирование с dump.txt
* ******************************************************************************
# Сборка:
* gcc (Debian 14.2.0-19) 14.2.0
* arm-linux-gnueabihf-g++
* ******************************************************************************
# Запуск:
* Пример: ./[appname] -i 172.18.160.1 -p 7674 7 10 2 (nodeID для поиска 0x7, 0x10, 0x2 по порту 7674, ip = 172.18.160.1)
* ******************************************************************************
# Источники:
* https://man7.org/linux/man-pages/man3/getopt.3.html - парсинг аргументов коммандной строки
* https://man7.org/linux/man-pages/man3/exit.3.html - человеческий выход
* https://en.cppreference.com/w/cpp/string/basic_string/stol - касты всякие стдэшные
* https://habr.com/ru/articles/583110/ - сигналы
* https://en.cppreference.com/w/c/program/sig_atomic_t - флажки в обработчиках сигналов
* https://man7.org/linux/man-pages/man7/signal-safety.7.html - чудесный мир async-signal-safe
* https://stackoverflow.com/questions/61586272/using-sigaction-without-sa-restart-and-preventing-an-infinte-loop? - подтверждаем мысль об EOF, сигналах и выходе из блокирующего чтение
* https://stackoverflow.com/questions/8573842/use-of-sigaction - еще
* https://man7.org/linux/man-pages/man2/sigaction.2.html - sigaction
* https://man7.org/linux/man-pages/man2/mprotect.2.html - пример sigaction
* https://www.csselectronics.com/pages/canopen-tutorial-simple-intro - canopen с картинками и конвертором cobID
* https://www.opennet.ru/man.shtml?topic=optind&category=3&russian=2 - optind
* https://www.opennet.ru/man.shtml?topic=htons&category=3&russian=0 - htons
* https://www.opennet.ru/man.shtml?topic=socket&category=2&russian=2 - socket
* https://www.opennet.ru/man.shtml?topic=inet_addr&category=3&russian=0 - inet_addr
* https://stackoverflow.com/questions/53051590/udp-server-client-c-sendto-recvfrom - пример udp
* https://www.opennet.ru/man.shtml?topic=inet_aton&category=3&russian=0 - inet_aton
* https://www.opennet.ru/man.shtml?topic=sendto&category=2&russian=0 - sendto
* https://habr.com/ru/articles/319736/ - arm кросс-компил.
