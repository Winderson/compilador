/*=====================================================================================================================
Autores: Daniel Deda
         Winderson Jose Barboza dos Santos

Disciplina: Compiladores
Curso: Ciência da Computação
=====================================================================================================================*/

#ifndef _TOKENENUM_H
#define _TOKENENUM_H

#include <string>

class TokenEnum {

public:
    static std::string const L_INT; // literal inteiro
    static std::string const L_FLT; // literal float
    static std::string const L_CHR; // literal caracter
    static std::string const L_STR; // literal string
    static std::string const O_INC; // atribuição de adição
    static std::string const O_MEQ; // incremento
    static std::string const O_SUM; // soma
    static std::string const O_SEQ; // decremento
    static std::string const O_SUB; // atribuição subtração
    static std::string const O_SNC; //
    static std::string const O_MAE; // maior ou igual
    static std::string const O_SMA; // maior
    static std::string const O_MEE; // menor igual
    static std::string const O_SME; // menor
    static std::string const O_SEE; // igualdade
    static std::string const O_ATR; // atribuição
    static std::string const O_MMQ; // atribuição multiplicacao
    static std::string const O_MUL; // multiplicacao
    static std::string const O_DEQ; // atribuição divisao
    static std::string const O_CMT; // comentario
    static std::string const O_DIV; // divisao
    static std::string const O_REQ; // atribuição resto
    static std::string const O_MOD; // resto da divisão
    static std::string const O_DIF; // operador diferença
    static std::string const O_NOT; // negação
    static std::string const O_AND; // and
    static std::string const O_COR; // or
    static std::string const L_IDF; // identificador
    static std::string const R_IFF; // if
    static std::string const R_ELS; // else
    static std::string const R_DOO; // do
    static std::string const R_WLE; // while
    static std::string const R_FOR; // for
    static std::string const R_MAN; // main
    static std::string const R_VOD; // void
    static std::string const R_VAR; // var
    static std::string const R_PTR; // print
    static std::string const R_PTN; // println
    static std::string const R_SCA; // scan
    static std::string const R_SCN; // scanln
    static std::string const R_CTN; // continue
    static std::string const R_BRK; // break
    static std::string const R_GTO; // goto
    static std::string const R_TRU; // true
    static std::string const R_FLS; // false
    static std::string const R_CHA; // char
    static std::string const R_INT; // int
    static std::string const R_REA; // real
    static std::string const R_STR; // string
    static std::string const O_POV; // ponto e virgula
    static std::string const R_APR;
    static std::string const R_FPR;
    static std::string const R_END;
    static std::string const R_THN;
    static std::string const R_ENF;
    static std::string const R_LOP;
};


#endif //_TOKENENUM_H
