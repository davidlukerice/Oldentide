// Filename:    LoginManager.h
// Author:      Michael Hinton
// Date:        Jul_29_2016
// Purpose:     Login authentication process.
// NOTE:        OpenSSL 1.0.2h needs to be installed on the system! It is the LTS solution and will be supported until Dec 2019

#ifndef OLDENTIDE_LOGINMANAGER_H
#define OLDENTIDE_LOGINMANAGER_H

class LoginManager{
    public:
        LoginManager();
        ~LoginManager();
        static void generateSaltAndKey(char *, char *, char *);
        static void generateKey(char *, char *, char *);
    private:
        static const long long int ITERATIONS;
};

#endif // OLDENTIDE_LOGINMANAGER_H
