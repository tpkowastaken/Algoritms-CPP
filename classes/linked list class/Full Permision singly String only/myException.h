#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H
#include <stdio.h>
class myException{
    public:
        const char *error;
        myException(const char *error){
            this->error = error;
            printf("\n%s\n", error);
        }
};
#endif //EXCEPTION_H