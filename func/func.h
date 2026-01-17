/**
 * @file func.h
 * @author your name (you@domain.com)
 * @brief Не сорить в main.cpp и где попало
 * @version 0.1
 * @date 2026-01-16
 *
 *
 */

#pragma once

#include <stdlib.h>
#include <optional>
#include <tuple>
#include <string>
#include <vector>

/**
 * @brief Обработка аргументов запуска
 *
 * @param argc
 * @param argv
 * @return std::nullopt - чего-то не хватило или ошибка каста
 * @return std::tuple<std::string, int, std::vector<int>> - udpIp, udpPort, nodeIds
 */
inline std::optional<std::tuple<std::string, int, std::vector<int>>> handleArgs(int argc, char *argv[])
{
    // Не зайдем в default ветку, если аргументов нет
    if (argc == 1)
    {
        return std::nullopt;
    }

    int opt;
    std::tuple<std::string, int, std::vector<int>> castedArgs = std::make_tuple("", 0, std::vector<int>());
    try
    {
        while ((opt = getopt(argc, argv, "i:p:")) != -1)
        {
            switch (opt)
            {
            case 'i':
                std::get<0>(castedArgs) = std::string(optarg);
                break;
            case 'p':
                std::get<1>(castedArgs) = std::stoi(optarg);
                break;
            default:
                break;
            }
        }

        // Достаем просто аргументы
        std::vector<int> simpleArgs;
        for (int i = optind; i < argc; ++i)
        {
            simpleArgs.push_back(std::stoi(argv[i], nullptr, 16));
        }
        std::get<2>(castedArgs) = simpleArgs;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Ошибка в аргументах запуска:" << e.what() << '\n';
        return std::nullopt;
    }

    // Проверка на полную передачу аргументов
    if (std::get<0>(castedArgs).empty() || std::get<1>(castedArgs) == 0 || std::get<2>(castedArgs).size() < 1)
    {
        std::cerr << "Не переданы все аргументы запуска\n";
        return std::nullopt;
    }

    return castedArgs;
}
