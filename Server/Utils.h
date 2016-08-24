// Filename:    Utils.h
// Author:      Joseph DeVictoria
// Date:        Mar_10_2016
// Purpose:     Header for miscellaneous functions.

#ifndef OLDENTIDE_UTILS_H
#define OLDENTIDE_UTILS_H

#include <string>
#include <vector>

namespace Utils{
    std::vector<std::string> tokenfy(std::string s, char delim);
    bool checkPasswordLength(char *);
    bool checkAccountNameLength(char *);
    bool sanitizeAccountName(char *);
    bool sanitizeAlphanumeric(char *);
    bool sanitizeHexString(char *);
};


#endif // OLDENTIDE_UTILS_H
