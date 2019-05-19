/*=====================================================================================================================
Autores: Daniel Deda
         Winderson Jose Barboza dos Santos

Disciplina: Compiladores
Curso: Ciência da Computação
=====================================================================================================================*/

#ifndef COMPILADORES_CARACTERENUM_H
#define COMPILADORES_CARACTERENUM_H


enum class EstadoEnum {

    // Estado inicial
    INICIAL = 1,

    // Estados dos números
    ESTADO_NUM_1 = 2,       // inteiro
    ESTADO_NUM_2 = 3,       // real
    ESTADO_NUM_3 = 4,       // real

    // Estado operadores
    ESTADO_SOMA = 10,       // soma
    ESTADO_SUBTRACAO = 11,  // subtracao
    ESTADO_MENOR = 12,      // menor
    ESTADO_MAIOR = 13,      // maior
    ESTADO_IGUAL = 14,      // igual
    ESTADO_MULTIPLICACAO = 15,  // multplicacao
    ESTADO_RESTO = 16,      // resto (porcentagem) <- Antigo ESTADO_DIVISAO repetido
    ESTADO_DIVISAO = 17,    // divisao
    ESTADO_DIFERENTE = 18,  // diferente
    ESTADO_E = 19,          // and
    ESTADO_OU = 20,         // or

    // Estado identificador
    ESTADO_IDENTIFICADOR_1 = 21,

    // Estado letras
    ESTADO_STR_1 = 23,      // string
    ESTADO_STR_2 = 24,      // string
    ESTADO_CHAR_1 = 25,     // char
    ESTADO_CHAR_2 = 26,     // char

    ESTADO_PONTO_VIRGULA = 27, // ponto e virgula
    ESTADO_ABRE_PARENTESES = 28,
    ESTADO_FECHA_PARENTESES = 29



};


#endif //COMPILADORES_CARACTERENUM_H
