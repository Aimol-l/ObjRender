#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
namespace str{
    inline std::vector<std::string> split(const std::string& src,const char gap = ' '){
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream iss(src);
        while (std::getline(iss, token, gap)) {
            tokens.push_back(token);
        }
        return std::move(tokens);
    }
    bool startswith(const std::string& src, const std::string& start) {
        return src.compare(0, start.size(), start) == 0;
    }
    bool endswith(const std::string& src, const std::string& end) {
        return src.compare(src.size() - end.size(), end.size(), end) == 0;
    }

} 
