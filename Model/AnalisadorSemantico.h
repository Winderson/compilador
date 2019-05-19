/*=====================================================================================================================
Autores: Daniel Deda
         Winderson Jose Barboza dos Santos

Disciplina: Compiladores
Curso: Ciência da Computação
=====================================================================================================================*/
#ifndef _ANALISADORSEMANTICO_H
#define _ANALISADORSEMANTICO_H
#include <string>
#include <vector>
#include "Token.h"
#include "Simbolo.h"
#include "TabelaDeSimbolos.h"

class AnalisadorSemantico {

public:
    // Construtor
    AnalisadorSemantico(std::vector <Token> tokens);
    void Anasem();
    void Erro(std::string message);

private:
    // Variaveis
    std::vector<Token> Tokens;                             // Lista de Tokens gerado pelo Léxico
    std::vector<Token> TokensSaida;
    std::vector<string> Mepa;
    TabelaDeSimbolos TabelaSimbolos;
    Token TokenAtual;                                       // Token atual a ser analisado
    Token ProxToken();                                      // Retorna o proximo token da lista
    void Accept(std::string esperado, std::string msg);     // Compara se o token Atual é o token esperado

    // Variáveis da linguagem D+ Basica
    void Programa();
    void DeclMain();
    void Decl();
    void ListaDecl();
    void DeclVar();
    std::string EspecTipo();
    std::string Var();
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


#endif //_ANALISADORSEMANTICO_H
