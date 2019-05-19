/*=====================================================================================================================
Autores: Daniel Deda
         Winderson Jose Barboza dos Santos

Disciplina: Compiladores
Curso: Ciência da Computação
=====================================================================================================================*/
#ifndef _COMPILATIONEXCEPTION_H
#define _COMPILATIONEXCEPTION_H

#include <exception>
#include <string>


class CompilationException: public std::exception{
    virtual const char* what() const throw()
    {
        return "Houve uma falha ao efetuar a compilação ";
    }
};


#endif //_COMPILATIONEXCEPTION_H
