/*=====================================================================================================================
Autores: Daniel Deda
         Winderson Jose Barboza dos Santos

Disciplina: Compiladores
Curso: Ciência da Computação
=====================================================================================================================*/

#ifndef ANALISADOR_LEXICO_H
#define ANALISADOR_LEXICO_H

#include "Token.h"
#include "Arquivo.h"
#include <string>


class AnalisadorLexico
{
public:
    AnalisadorLexico(Arquivo &arquivo): ArquivoEntrada(arquivo), Lexema(""), Estado(1){};
    Token Analex(char caracter);
    void SetaEstadoInicial(){this->Estado = 1; this->Lexema = "";};

private:
    std::string Lexema;
    Arquivo &ArquivoEntrada;
    int Estado;
    Token ChecaReservado(std::string palavra);
};






#endif //ANALISADOR_LEXICO_H
