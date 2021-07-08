//
// Created by Жуков Максим Александрович on 19.06.2021.
//

#ifndef UNTITLED_PARSER_H
#define UNTITLED_PARSER_H

#include <string>
#include <map>
#include "Message.h"
#include <regex>
#include "json.hpp"

class Parser {
private:
    std::string makeFullJsonString(const std::string& updateString);
public:
    LevelUpdate parseUpdate(const std::string& updateString);
};

#endif //UNTITLED_PARSER_H
