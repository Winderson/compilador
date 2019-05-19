/*=====================================================================================================================
Autores: Daniel Deda
         Winderson Jose Barboza dos Santos

Disciplina: Compiladores
Curso: Ciência da Computação
=====================================================================================================================*/

#include <iostream>
#include <regex>
#include <algorithm>
#include "AnalisadorLexico.h"
#include "Arquivo.h"
#include "../Enuns/EstadoEnum.h"
#include "../Enuns/PalavrasReservadasEnum.h"
#include "../Enuns/TokenEnum.h"

using namespace std;

/**
 * @param caracter
 * @return Token
 */

Token AnalisadorLexico::Analex(char caracter)
{
    if (this->Estado == static_cast<int>(EstadoEnum::INICIAL))
    {
        if (isdigit(caracter))
        {
            this->Estado = static_cast<int>(EstadoEnum::ESTADO_NUM_1);
            this->Lexema.push_back(caracter);
        }
        else if (caracter == '+')
        {
            this->Estado = static_cast<int>(EstadoEnum::ESTADO_SOMA);
            this->Lexema.push_back(caracter);
        }
        else if (caracter == '-')
        {
            this->Estado = static_cast<int>(EstadoEnum::ESTADO_SUBTRACAO);
            this->Lexema.push_back(caracter);
        }
        else if (caracter == '<')
        {
            this->Estado = static_cast<int>(EstadoEnum::ESTADO_MENOR);
            this->Lexema.push_back(caracter);
        }
        else if (caracter == '>')
        {
            this->Estado = static_cast<int>(EstadoEnum::ESTADO_MAIOR);
            this->Lexema.push_back(caracter);
        }
        else if (caracter == '=')
        {
            this->Estado = static_cast<int>(EstadoEnum::ESTADO_IGUAL);
            this->Lexema.push_back(caracter);
        }
        else if (caracter == '*')
        {
            this->Estado = static_cast<int>(EstadoEnum::ESTADO_MULTIPLICACAO);
            this->Lexema.push_back(caracter);
        }
        else if (caracter == '/')
        {
            this->Estado = static_cast<int>(EstadoEnum::ESTADO_DIVISAO);
            this->Lexema.push_back(caracter);
        }
        else if (caracter == '%')
        {
            this->Estado = static_cast<int>(EstadoEnum::ESTADO_RESTO);
            this->Lexema.push_back(caracter);
        }
        else if (caracter == '!')
        {
            this->Estado = static_cast<int>(EstadoEnum::ESTADO_DIFERENTE);
            this->Lexema.push_back(caracter);
        }
        else if (caracter == '&')
        {
            this->Estado = static_cast<int>(EstadoEnum::ESTADO_E);
            this->Lexema.push_back(caracter);
        }
        else if (caracter == '|')
        {
            this->Estado = static_cast<int>(EstadoEnum::ESTADO_OU);
            this->Lexema.push_back(caracter);
        }
        else if (caracter == '\'')
        {
            this->Estado = static_cast<int>(EstadoEnum::ESTADO_CHAR_1);
            this->Lexema.push_back(caracter);
        }
        else if (caracter == '\"')
        {
            this->Estado = static_cast<int>(EstadoEnum::ESTADO_STR_1);
            this->Lexema.push_back(caracter);
        }
        else if (caracter == ';')
        {
            this->Estado = static_cast<int>(EstadoEnum::ESTADO_PONTO_VIRGULA);
            this->Lexema.push_back(caracter);
        }
        else if (isalpha(caracter))
        {
            this->Estado = static_cast<int>(EstadoEnum::ESTADO_IDENTIFICADOR_1);
            this->Lexema.push_back(caracter);
        }
        else if (caracter == '(')
        {
            this->Estado = static_cast<int>(EstadoEnum::ESTADO_ABRE_PARENTESES);
            this->Lexema.push_back(caracter);
        }
        else if (caracter == ')')
        {
            this->Estado = static_cast<int>(EstadoEnum::ESTADO_FECHA_PARENTESES);
            this->Lexema.push_back(caracter);
        }

            // Exceções
        else if (caracter == ' ')
        {
            return Token("", this->Lexema, "Estado " + std::to_string(1));
        }

        // Recebe o proximo caracter
        if(!this->ArquivoEntrada.getBuffer().empty())
        {
            caracter = this->ArquivoEntrada.Prox_char();
        }
        else
        {
            return Token("", "", "");
        }
    }
    else if (Estado == static_cast<int>(EstadoEnum::ESTADO_NUM_1))
    {
        if (isdigit(caracter) || caracter == '.')
        {
            while (isdigit(caracter))
            {
                this->Lexema.push_back(caracter);
                caracter = this->ArquivoEntrada.Prox_char();
            }
            if (caracter == '.')
            {
                this->Estado = static_cast<int>(EstadoEnum::ESTADO_NUM_2);
                this->Lexema.push_back(caracter);
                caracter = this->ArquivoEntrada.Prox_char();
            }
            else
            {
                this->ArquivoEntrada.Ant_char();
                return Token(TokenEnum::L_INT, this->Lexema, "Estado " + std::to_string(this->Estado));
            }
        }
        else
        {
            this->ArquivoEntrada.Ant_char();
            return Token(TokenEnum::L_INT, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
    }
    else if (Estado == static_cast<int>(EstadoEnum::ESTADO_NUM_2))
    {
        if (isdigit(caracter))
        {
            this->Estado = static_cast<int>(EstadoEnum::ESTADO_NUM_3);
            this->Lexema.push_back(caracter);
            caracter = this->ArquivoEntrada.Prox_char();
        }
    }
    else if (Estado == static_cast<int>(EstadoEnum::ESTADO_NUM_3))
    {
        if (isdigit(caracter))
        {
            while (isdigit(caracter))
            {
                this->Lexema.push_back(caracter);
                caracter = this->ArquivoEntrada.Prox_char();
            }
            this->ArquivoEntrada.Ant_char();
            return Token(TokenEnum::L_FLT, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
        else
        {
            this->ArquivoEntrada.Ant_char();
            return Token(TokenEnum::L_FLT, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
    }
    else if (Estado == static_cast<int>(EstadoEnum::ESTADO_SOMA))
    {
        if (caracter == '+')
        {
            this->Lexema.push_back(caracter);
            return Token(TokenEnum::O_INC, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
        else if (caracter == '=')
        {
            this->Lexema.push_back(caracter);
            return Token(TokenEnum::O_MEQ, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
        else
        {
            this->ArquivoEntrada.Ant_char();
            return Token(TokenEnum::O_SUM, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
    }
    else if (Estado == static_cast<int>(EstadoEnum::ESTADO_SUBTRACAO))
    {
        if (caracter == '=')
        {
            this->Lexema.push_back(caracter);
            return Token(TokenEnum::O_SEQ, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
        else if (caracter == '-')
        {
            this->Lexema.push_back(caracter);
            return Token(TokenEnum::O_SNC, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
        else
        {
            this->ArquivoEntrada.Ant_char();
            return Token(TokenEnum::O_SUB, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
    }
    else if (Estado == static_cast<int>(EstadoEnum::ESTADO_MENOR))
    {
        if (caracter == '=')
        {
            this->Lexema.push_back(caracter);
            return Token(TokenEnum::O_MAE, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
        else
        {
            this->ArquivoEntrada.Ant_char();
            return Token(TokenEnum::O_SMA, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
    }
    else if (Estado == static_cast<int>(EstadoEnum::ESTADO_MAIOR))
    {
        if (caracter == '=')
        {
            this->Lexema.push_back(caracter);
            return Token(TokenEnum::O_MEE, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
        else
        {
            this->ArquivoEntrada.Ant_char();
            return Token(TokenEnum::O_SME, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
    }
    else if (Estado == static_cast<int>(EstadoEnum::ESTADO_IGUAL))
    {
        if (caracter == '=')
        {
            this->Lexema.push_back(caracter);
            return Token(TokenEnum::O_SEE, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
        else
        {
            this->ArquivoEntrada.Ant_char();
            return Token(TokenEnum::O_ATR, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
    }
    else if (Estado == static_cast<int>(EstadoEnum::ESTADO_MULTIPLICACAO))
    {
        if (caracter == '=')
        {
            this->Lexema.push_back(caracter);
            return Token(TokenEnum::O_MMQ, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
        else
        {
            this->ArquivoEntrada.Ant_char();
            return Token(TokenEnum::O_MUL, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
    }
    else if (Estado == static_cast<int>(EstadoEnum::ESTADO_DIVISAO))
    {
        if (caracter == '=')
        {
            this->Lexema.push_back(caracter);
            return Token(TokenEnum::O_DEQ, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
        else if (caracter == '/')
        {
            this->Lexema.push_back(caracter);
            return Token(TokenEnum::O_CMT, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
        else
        {
            this->ArquivoEntrada.Ant_char();
            return Token(TokenEnum::O_DIV, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
    }
    else if (Estado == static_cast<int>(EstadoEnum::ESTADO_RESTO)) // <-- era isso?
    {
        if (caracter == '=')
        {
            this->Lexema.push_back(caracter);
            return Token(TokenEnum::O_REQ, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
        else
        {
            this->ArquivoEntrada.Ant_char();
            return Token(TokenEnum::O_MOD, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
    }
    else if (Estado == static_cast<int>(EstadoEnum::ESTADO_DIFERENTE))
    {
        if (caracter == '=')
        {
            this->Lexema.push_back(caracter);
            return Token(TokenEnum::O_DIF, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
        else
        {
            this->ArquivoEntrada.Ant_char();
            return Token(TokenEnum::O_NOT, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
    }
    else if (Estado == static_cast<int>(EstadoEnum::ESTADO_E))
    {
        if (caracter == '&')
        {
            this->Lexema.push_back(caracter);
            return Token(TokenEnum::O_AND, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
    }
    else if (Estado == static_cast<int>(EstadoEnum::ESTADO_OU))
    {
        if (caracter == '|')
        {
            this->Lexema.push_back(caracter);
            return Token(TokenEnum::O_COR, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
    }
    else if (Estado == static_cast<int>(EstadoEnum::ESTADO_CHAR_1))
    {
        if(caracter != '\'')
        {
            this->Lexema.push_back(caracter);
            this->Estado = static_cast<int>(EstadoEnum::ESTADO_CHAR_2);
            caracter = this->ArquivoEntrada.Prox_char();
        }
    }
    else if (Estado == static_cast<int>(EstadoEnum::ESTADO_CHAR_2))
    {
        if(caracter == '\'')
        {
            this->Lexema.push_back(caracter);
            return Token(TokenEnum::L_CHR, this->Lexema, "Estado " + std::to_string(this->Estado));
        }
        else
        {
            std::cout << "Falha no estado: " << this->Estado << endl;
        }
    } 
    else if (Estado == static_cast<int>(EstadoEnum::ESTADO_IDENTIFICADOR_1)) {
        if (isalpha(caracter) || isdigit(caracter) || caracter == '-') {
            while (isalpha(caracter) || isdigit(caracter) || caracter == '-') {
                this->Lexema.push_back(caracter);
                caracter = this->ArquivoEntrada.Prox_char();
            }
        }
        this->ArquivoEntrada.Ant_char();

        //return Token("O_IDF", this->Lexema, "Estado " + std::to_string(this->Estado));
        return ChecaReservado(this->Lexema);
    }
    else if (Estado == static_cast<int>(EstadoEnum::ESTADO_STR_1))
    {
        if(caracter != '\"')
        {
            this->Lexema.push_back(caracter);
            this->Estado = static_cast<int>(EstadoEnum::ESTADO_STR_2);
        }
    }
    else if(Estado == static_cast<int>(EstadoEnum::ESTADO_STR_2))
    {
        while(caracter != '\"')
        {
            this->Lexema.push_back(caracter);
            caracter = this->ArquivoEntrada.Prox_char();
        }

        this->Lexema.push_back(caracter);
        return Token(TokenEnum::L_STR, this->Lexema, "Estado " + std::to_string(this->Estado));
    }
    else if(Estado == static_cast<int>(EstadoEnum::ESTADO_PONTO_VIRGULA))
    {
        this->ArquivoEntrada.Ant_char();
        return Token(TokenEnum::O_POV, this->Lexema, "Estado " + std::to_string(this->Estado));
    }
    else if(Estado == static_cast<int>(EstadoEnum::ESTADO_ABRE_PARENTESES))
    {
        this->ArquivoEntrada.Ant_char();
        return Token(TokenEnum::R_APR, this->Lexema, "Estado " + std::to_string(this->Estado));
    }
    else if(Estado == static_cast<int>(EstadoEnum::ESTADO_FECHA_PARENTESES))
    {
        this->ArquivoEntrada.Ant_char();
        return Token(TokenEnum::R_FPR, this->Lexema, "Estado " + std::to_string(this->Estado));
    }

    return this->Analex(caracter);
}

/**
 *
 * @param palavra
 * @return
 */
Token AnalisadorLexico::ChecaReservado(std::string palavra)
{
    string palavraAux = "";
    std::locale loc;

    for (std::string::size_type i=0; i<palavra.length(); ++i)
    {
        palavraAux += std::tolower(palavra[i], loc);
    }

    if(palavraAux == PalavrasReservadasEnum::IF)
    {
        return Token(TokenEnum::R_IFF, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::ELSE)
    {
        return Token(TokenEnum::R_ELS, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::DO)
    {
        return Token(TokenEnum::R_DOO, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::WHILE)
    {
        return Token(TokenEnum::R_WLE, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::FOR)
    {
        return Token(TokenEnum::R_FOR, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::MAIN)
    {
        return Token(TokenEnum::R_MAN, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::VOID)
    {
        return Token(TokenEnum::R_VOD, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::VAR)
    {
        return Token(TokenEnum::R_VAR, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::PRINT)
    {
        return Token(TokenEnum::R_PTR, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::PRINTLN)
    {
        return Token(TokenEnum::R_PTN, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::SCAN)
    {
        return Token(TokenEnum::R_SCA, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::SCANLN)
    {
        return Token(TokenEnum::R_SCN, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::CONTINUE)
    {
        return Token(TokenEnum::R_CTN, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::BREAK)
    {
        return Token(TokenEnum::R_BRK, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::GOTO)
    {
        return Token(TokenEnum::R_GTO, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::TRUE)
    {
        return Token(TokenEnum::R_TRU, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::FALSE)
    {
        return Token(TokenEnum::R_FLS, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::CHAR)
    {
        return Token(TokenEnum::R_CHA, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::INT)
    {
        return Token(TokenEnum::R_INT, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::REAL)
    {
        return Token(TokenEnum::R_REA, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::STRING)
    {
        return Token(TokenEnum::R_STR, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::END)
    {
        return Token(TokenEnum::R_END, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::END_IF)
    {
        return Token(TokenEnum::R_ENF, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::THEN)
    {
        return Token(TokenEnum::R_THN, palavra, "Estado " + std::to_string(this->Estado));
    }
    else if(palavraAux == PalavrasReservadasEnum::LOOP)
    {
        return Token(TokenEnum::R_LOP, palavra, "Estado " + std::to_string(this->Estado));
    }
    else
    {
        return Token(TokenEnum::L_IDF, palavra, "Estado " + std::to_string(this->Estado));
    }
}