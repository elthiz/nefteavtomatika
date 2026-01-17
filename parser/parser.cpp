#include "parser.h"

#include <iostream>
#include <string>
#include <algorithm>

Parser::Parser()
{
}

Parser::~Parser()
{
}

std::string Parser::getLine() const
{
    return _line;
}

void Parser::setNodeIds(std::vector<int> &nodeIds)
{
    _nodeIds = nodeIds;
    std::sort(_nodeIds.begin(), _nodeIds.end());
}

bool Parser::checkLine()
{
    if (!std::getline(std::cin, _line))
    {
        return false;
    }
    // "can" - будет. ищем позицию старта
    size_t idxCanStart = _line.find("can");
    if (idxCanStart == std::string::npos)
    {
        return false;
    }
    // ищем конец имени интерфейса "canX"
    size_t idxCanEnd = _line.find(' ', idxCanStart + 2);
    if (idxCanEnd == std::string::npos)
    {
        return false;
    }
    // ищем начало cobID
    size_t idxCobStart = _line.find_first_not_of(' ', idxCanEnd);
    if (idxCobStart == std::string::npos)
    {
        return false;
    }
    // ищем конец cobID
    size_t idxCobEnd = _line.find(' ', idxCobStart);
    if (idxCobEnd == std::string::npos)
    {
        return false;
    }
    // 1. Не расширенный формат - достаем младшие биты (7 штук) с nodeID из cobID
    // 2. Расширенный формат - достаем через поиск
    // 3. NMT - достаем второй байт из данных. НЕ УЧИТЫВАЕМ broadcast
    std::string strCob = _line.substr(idxCobStart, idxCobEnd - idxCobStart);
    int nodeId = -1;
    try
    {
        // 1. Не расширенный формат
        if (strCob.length() == 3)
        {
            int cobId = std::stoi(strCob, nullptr, 16);
            // Поймали NMT
            if (cobId == 0)
            {
                // ищем метку размера данных
                size_t idxSizeStart = _line.find("[2]");
                if (idxSizeStart == std::string::npos)
                {
                    return false;
                }
                // ищем начало данных после размера
                size_t idxCommandByteStart = _line.find_first_not_of(' ', idxSizeStart + 3);
                if (idxCommandByteStart == std::string::npos)
                {
                    return false;
                }
                // достаем второй байт с nodeID (+3 - от начала - первый байт с типом NMT и пробел/+5 тоже самое но и размер байта в символах с nodeID)
                std::string strNodeId = _line.substr(idxCommandByteStart + 3, idxCommandByteStart + 5 - idxCommandByteStart + 3);
                nodeId = std::stoi(strNodeId, nullptr, 16);
            }
            // Обычный cobID с nodeID
            else
            {
                nodeId = cobId & 0x7F;
            }
        }
        // 2. Расширенный формат
        // 1E0 0 07 F0 - 07
        if (strCob.length() == 8)
        {
            nodeId = std::stoi(strCob.substr(4, 2), nullptr, 16);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Ошибка парсинга: " << e.what() << '\n';
        return false;
    }

    if (std::binary_search(_nodeIds.begin(), _nodeIds.end(), nodeId))
    {
        return true;
    }

    return false;
}