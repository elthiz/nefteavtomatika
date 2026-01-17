/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief Тестовое вариант 1
 * @version 0.1
 * @date 2026-01-16
 *
 *
 * ******************************************************************************
 * Стандарт:
 * C++17 - для std::optional
 *
 * ******************************************************************************
 * Окружение:
 * gcc 14.2.0
 * WSL-2 (Debian 14.2.0-19)
 *
 * ******************************************************************************
 * Сборка:
 * gcc (Debian 14.2.0-19) 14.2.0
 * arm-linux-gnueabihf-g++
 *
 * ******************************************************************************
 * Запуск:
 * Пример: ./[appname] -i 172.18.160.1 -p 7674 7 10 2 (nodeID для поиска 0x7, 0x10, 0x2)
 *
 * ******************************************************************************
 * Источники:
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
 */

#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <csignal>
// user
#include "func/func.h"
#include "parser/parser.h"
#include "udpclient/udpclient.h"

volatile std::sig_atomic_t isRunning = true;

void exitHandler(int signum)
{
    isRunning = false;
}

int main(int argc, char *argv[])
{
    // Получаем аргументы запуска
    std::optional<std::tuple<std::string, int, std::vector<int>>> castedArgs = handleArgs(argc, argv);

    if (castedArgs == std::nullopt)
    {
        // Что-то не то с аргументами...
        std::cerr << "Usage: " << argv[0] << " [-i udpIp] [-p udpPort] (nodeId1 in hex) ... (nodeIdN in hex)\n";
        exit(EXIT_FAILURE);
    }

    std::string udpIp = std::get<0>(castedArgs.value());
    int udpPort = std::get<1>(castedArgs.value());
    std::vector<int> nodeIds = std::get<2>(castedArgs.value());

    struct sigaction sa;
    sa.sa_handler = exitHandler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    // Цепляем сигналы выхода
    sigaction(SIGINT, &sa, nullptr);
    sigaction(SIGTERM, &sa, nullptr);

    Parser parser;
    parser.setNodeIds(nodeIds);

    UdpClient udpClient(udpIp, udpPort);

    while (isRunning)
    {
        if (parser.checkLine())
        {
            std::string line = parser.getLine();
            udpClient.send(line);
        }
    }

    return 0;
}
