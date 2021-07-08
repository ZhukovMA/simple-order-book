//
// Created by Жуков Максим Александрович on 04.07.2021.
//

#ifndef UNTITLED_MESSAGE_H
#define UNTITLED_MESSAGE_H

#include <string>
#include <map>
#include <vector>


struct LevelUpdate {
   unsigned long time;
    std::map<double, int, std::greater<int>> bids;
    std::map<double, int> asks;
};

struct LevelUpdateWithArray {
    unsigned long time;
    std::vector<std::pair<std::string, int>> bids;
    std::vector<std::pair<std::string, int>> asks;
};

#endif //UNTITLED_MESSAGE_H
