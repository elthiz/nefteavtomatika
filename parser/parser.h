/**
 * @file parser.h
 * @author your name (you@domain.com)
 * @brief Парсинг вывода от candump
 * @version 0.1
 * @date 2026-01-16
 *
 *
 */

#pragma once

#include <string>
#include <vector>

/**
 * @brief Парсер вывода candump
 *
 */
class Parser
{
public:
    Parser();
    ~Parser();

    /**
     * @brief Геттер последней прочитанной строки
     */
    std::string getLine() const;

    /**
     * @brief Сеттер искомых nodeID
     */
    void setNodeIds(std::vector<int>& nodeIds);

    /**
     * @brief Получение и проверка одной строки из потока на nodeID
     *
     * @return true - строка найдена, сохранена
     * @return false - не нашлось
     * @note Можно было просто использовать std::istringstream
     */
    bool checkLine();

private:
    /**
     * @brief Последняя прочитанная строка.
     * @note Становится актуальными данными только после успешного вызова checkLine()
     *
     */
    std::string _line;

    /**
     * @brief Искомый nodeID.
     *
     */
    std::vector<int> _nodeIds;
};