/*=====================================================================================================================
Autores: Daniel Deda
         Winderson Jose Barboza dos Santos

Disciplina: Compiladores
Curso: Ciência da Computação
=====================================================================================================================*/

#ifndef _ANALISADORSINTATICO_H
#define _ANALISADORSINTATICO_H

#include <string>
#include <vector>
#include <exception>
#include "Token.h"
#include "../Exception/CompilationException.h"


/**
 *
 */
class AnalisadorSintatico {
public:
    // Construtor
    AnalisadorSintatico(std::vector <Token> tokens);
    void Anasin();
    void Erro(std::string message);

private:
    // Variaveis
    std::vector <Token> Tokens;                             // Lista de Tokens gerado pelo Léxico
    std::vector <Token> TokensSaida;
    Token TokenAtual;                                       // Token atual a ser analisado
    Token ProxToken();                                      // Retorna o proximo token da lista
    void Accept(std::string esperado, std::string msg);     // Compara se o token Atual é o token esperado

    // Variáveis da linguagem D+ Basica
    void Programa();
    void DeclMain();
    void Decl();
    void ListaDecl();
    void DeclVar();
    void EspecTipo();
    void Var();
    void Bloco();
    void ListaCom();
    void Comando();
    void ComAtrib();
    void ComSelecao();
    void ComRepeticao();
    void ComEscrita();
    void Exp1();
    void Exp2();
    void ExpMult1();
    void ExpMult2();
    void ExpSimples();
    void OpSoma();
    void OpMult();
    void Literal();
};

#endif //_ANALISADORSINTATICO_H
