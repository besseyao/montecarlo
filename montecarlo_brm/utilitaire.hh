#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <array>
#include <iostream>
#include "../jeu.hh"

using ligne=std::array<char,MAX_LARGEUR>;
using board=std::array<ligne,MAX_HAUTEUR>;

class utilitaire{
public:
    static std::vector<std::string> explode(std::string const & s, char delim)
    {
        std::vector<std::string> result;
        std::istringstream iss(s);

        for (std::string token; std::getline(iss, token, delim); )
        {
            result.push_back(std::move(token));
        }

        return result;
    }

    static board plateau(std::string & p){
        board board;
        for(unsigned int i(0); i < MAX_HAUTEUR; ++i)
            for(size_t j(0); j < MAX_LARGEUR; ++j)
                board[i][j] = p[(i * MAX_LARGEUR) + j];
        return board;
    }

    static bool stob(std::string const & v){
        return (v == "1");
    }

};
