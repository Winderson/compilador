//
// Created by winderson on 10/12/18.
//

#ifndef _SUCCESSEXCEPTION_H
#define _SUCCESSEXCEPTION_H
#include <exception>

class SuccessException: public std::exception{
    virtual const char* what() const throw()
    {
        return "";
    }
};


#endif //_SUCCESSEXCEPTION_H
