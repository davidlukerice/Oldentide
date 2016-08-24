// Filename:    AccountManager.h
// Author:      Michael Hinton
// Date:        Jul_23_2016
// Purpose:     Account creation and authentication.
// NOTE:        OpenSSL 1.0.2h needs to be installed on the system! It is the LTS solution and will be supported until Dec 2019

#ifndef OLDENTIDE_ACCOUNTMANAGER_H
#define OLDENTIDE_ACCOUNTMANAGER_H

class AccountManager{
    public:
        AccountManager();
        ~AccountManager();
        static int authenticateAccount(char *, char *);
};

#endif // OLDENTIDE_ACCOUNTMANAGER_H
