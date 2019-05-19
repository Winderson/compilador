/*=====================================================================================================================
Autores: Daniel Deda
         Winderson Jose Barboza dos Santos

Disciplina: Compiladores
Curso: Ciência da Computação
=====================================================================================================================*/
#include <iostream>
#include "AnalisadorSemantico.h"
#include "../Enuns/TokenEnum.h"
#include "Arquivo.h"
#include "../Enuns/SaidaEnum.h"
#include "../Exception/CompilationException.h"
#include "../Enuns/PalavrasReservadasEnum.h"
#include "TabelaDeSimbolos.h"

using namespace std;

/**
 * Construtor
 * @param tokens
 */
AnalisadorSemantico::AnalisadorSemantico(std::vector<Token> tokens) {
    this->TokenAtual = Token();
    this->Tokens = tokens;
}

/**
 * Método responsável pela inicialização do analisador sintático
 */
void AnalisadorSemantico::Anasem() {
    this->Programa();
    this->Bloco();
}

/**
 * Método responsável por pegar o próximo token
 * para validá-lo
 * @return
 */
Token AnalisadorSemantico::ProxToken() {
    Token token = this->Tokens.back();
    this->Tokens.pop_back();
    return token;
}

/**
 * Método Accept responsável pela verificação do token esperado
 * a caso o token não seja o esperado é chamado o método de erro
 * @param esperado
 * @param msg
 */
void AnalisadorSemantico::Accept(string esperado, string msg) {
    if (this->TokenAtual.GetTokenId() == esperado) {
        this->TokensSaida.push_back(Token(this->TokenAtual.GetTokenId(), this->TokenAtual.GetLexema(), "OK"));
        if (this->Tokens.empty()) {
            Arquivo arquivo;
            //arquivo.GravaToken(this->TokensSaida, SaidaEnum::SINTATICO);
            arquivo.GravaTabelaSimbolos(this->TabelaSimbolos);
            return;
        } else {
            this->TokenAtual = this->ProxToken();  // pega o proximo token para comparar
        }
    } else {
        this->Erro(msg);
    }
}

/**
 * Método de inicialização do programa
 */
void AnalisadorSemantico::Programa() {
    this->TokensSaida.push_back(Token("", "", "Prog"));
    this->TokensSaida.push_back(Token("", "", "Principal"));
    this->TokenAtual = this->ProxToken();
    this->ListaDecl();
}

/**
 * Método de lista de declarações
 */
void AnalisadorSemantico::ListaDecl() {
    // Chamada o para o método de declaração
    this->Decl();

    // Verifica se existem mais variaveis a ser declaradas
    // e encaminha para a declaração
    if (this->TokenAtual.GetTokenId() == TokenEnum::R_VAR || this->TokenAtual.GetTokenId() == TokenEnum::R_MAN) {
        // Chamada o para o método de declaração
        this->ListaDecl();
    }
}


/**
 * Método de declaração
 */
void AnalisadorSemantico::Decl() {
    if (this->TokenAtual.GetTokenId() == TokenEnum::R_VAR) {
        this->DeclVar();
    } else if (this->TokenAtual.GetTokenId() == TokenEnum::R_MAN) {
        this->DeclMain();
    }
}

/**
 * Método de declaração de variável
 */
void AnalisadorSemantico::DeclVar() {

    Simbolo simbolo;
    this->TokensSaida.push_back(Token("", "", "Decl. de Variável"));
    this->Accept(TokenEnum::R_VAR, "Esperado 'VAR'");
    simbolo.SetClasse(PalavrasReservadasEnum::VAR);
    // Chamada para o método que valida o tipo
    simbolo.SetTipo(this->EspecTipo());
    // Chamada para o método que valida o var
    simbolo.SetNome(this->Var());
    // Accept
    this->Accept(TokenEnum::O_POV, "Esperado ';'");
    this->TabelaSimbolos.tabelaDeSimbolos.push_back(simbolo);
}

/**
 * Método de declaração do main
 */
void AnalisadorSemantico::DeclMain() {

    Simbolo simbolo;
    this->TokensSaida.push_back(Token("", "", "Decl. Main"));
    this->Accept(TokenEnum::R_MAN, "Esperado 'MAIN'");
    simbolo.SetNome(PalavrasReservadasEnum::MAIN);
    simbolo.SetClasse("function");
    simbolo.SetTipo(PalavrasReservadasEnum::INT);
    this->TabelaSimbolos.tabelaDeSimbolos.push_back(simbolo);
    this->Accept(TokenEnum::R_APR, "Esperado '('");
    this->Accept(TokenEnum::R_FPR, "Esperado ')'");
    this->Bloco();
    this->Accept(TokenEnum::R_END, "Esperado 'END'");
}

/**
 * Método de verificação do var
 */
string AnalisadorSemantico::Var() {
    string identificador = this->TokenAtual.GetLexema();
    this->Accept(TokenEnum::L_IDF, "Esperado Identificador");
    return identificador;
}


/**
 * método de inicialização do bloco
 */
void AnalisadorSemantico::Bloco() {
    this->ListaCom();
}

/**
 * Método de verificação do tipo
 */
string AnalisadorSemantico::EspecTipo() {
    if (this->TokenAtual.GetTokenId() == TokenEnum::R_INT) {
        this->Accept(TokenEnum::R_INT, "Esperado 'INT'");
        return PalavrasReservadasEnum::INT;
    } else if (this->TokenAtual.GetTokenId() == TokenEnum::R_REA) {
        this->Accept(TokenEnum::R_REA, "Esperado 'REAL'");
        return PalavrasReservadasEnum::REAL;
    } else if (this->TokenAtual.GetTokenId() == TokenEnum::R_CHA) {
        this->Accept(TokenEnum::R_CHA, "Esperado 'CHAR'");
        return PalavrasReservadasEnum::CHAR;
    }
}

/**
 * Método responsável pela lista de comandos
 */
void AnalisadorSemantico::ListaCom() {
    if (this->TokenAtual.GetTokenId() == TokenEnum::R_VAR ||  // TODO: Só confere se os estados batem pra mim
        this->TokenAtual.GetTokenId() == TokenEnum::R_SCA ||
        this->TokenAtual.GetTokenId() == TokenEnum::R_PTR ||
        this->TokenAtual.GetTokenId() == TokenEnum::R_WLE ||
        this->TokenAtual.GetTokenId() == TokenEnum::R_PTN ||
        this->TokenAtual.GetTokenId() == TokenEnum::R_SCN ||
        this->TokenAtual.GetTokenId() == TokenEnum::R_IFF ||
        this->TokenAtual.GetTokenId() == TokenEnum::L_IDF ||
        this->TokenAtual.GetTokenId() == TokenEnum::R_ELS) {
        // Chamado para o método de verificação do comando
        this->Comando();
        this->ListaCom();
    }
}

/**
 *
 */
void AnalisadorSemantico::Comando() {
    if (this->TokenAtual.GetTokenId() == TokenEnum::R_VAR) {
        this->DeclVar();
    } else if (this->TokenAtual.GetTokenId() == TokenEnum::L_IDF) {
        this->ComAtrib();
    } else if (this->TokenAtual.GetTokenId() == TokenEnum::R_IFF) {
        this->ComSelecao();
    } else if (this->TokenAtual.GetTokenId() == TokenEnum::R_WLE) {
        this->ComRepeticao();
    } else if (this->TokenAtual.GetTokenId() == TokenEnum::R_PTN || this->TokenAtual.GetTokenId() == TokenEnum::R_PTR) {
        this->ComEscrita();
    } else if (this->TokenAtual.GetTokenId() == "ID") {
        this->ComAtrib();
    } else {
        this->Erro("");
    }
}

/**
 *
 */
void AnalisadorSemantico::ComAtrib() {
    this->TokensSaida.push_back(Token("", "", "Atribuição"));
    this->Var();
    this->Accept(TokenEnum::O_ATR, "'=' esperado");
    this->Exp1();
    this->Accept(TokenEnum::O_POV, "';' esperado");
}

/**
 *
 */
void AnalisadorSemantico::ComEscrita() {
    if(this->TokenAtual.GetTokenId() == TokenEnum::R_PTR){
        this->Accept(TokenEnum::R_PTR, "'PRINT' esperado");
    }
    else if(this->TokenAtual.GetTokenId() == TokenEnum::R_PTN){
        this->Accept(TokenEnum::R_PTN, "'PRINTLN' esperado");
    }

    this->Accept(TokenEnum::R_APR, "'(' esperado");
    this->Exp1();
    this->Accept(TokenEnum::R_FPR, "')' esperado");
    this->Accept(TokenEnum::O_POV, "';' esperado");
}

/**
 *
 */
void AnalisadorSemantico::ComRepeticao() {
    this->Accept(TokenEnum::R_WLE, "'WHILE' esperado");
    this->Exp1();
    this->Accept(TokenEnum::R_DOO, "'DO' esperado.");
    this->Bloco();
}

/**
 *
 */
void AnalisadorSemantico::Exp1() {
    this->ExpMult1();
    this->Exp2();
}

/**
 *
 */
void AnalisadorSemantico::Exp2() {
    if (this->TokenAtual.GetTokenId() == TokenEnum::O_SUM || this->TokenAtual.GetTokenId() == TokenEnum::O_SUB) {
        this->OpSoma();
        this->Exp1();
    } else {
        // Vazio
    }
}

/**
 *
 */
void AnalisadorSemantico::ExpMult1() {
    this->ExpSimples();
    this->ExpMult2();
}

/**
 *
 */
void AnalisadorSemantico::ExpMult2() {
    if (this->TokenAtual.GetTokenId() == TokenEnum::O_DIV || this->TokenAtual.GetTokenId() == TokenEnum::O_MOD) {
        this->OpMult();
    } else {
        // Vazio
    }
}

/**
 *
 */
void AnalisadorSemantico::OpMult() {
    if (this->TokenAtual.GetTokenId() == TokenEnum::O_DIV) {
        this->Accept(TokenEnum::O_DIV, "Esperado '/'");
    } else if (this->TokenAtual.GetTokenId() == TokenEnum::O_MOD) {
        this->Accept(TokenEnum::O_MOD, "Esperado '%'");
    }
}

/**
 *
 */
void AnalisadorSemantico::ExpSimples() {
    if (this->TokenAtual.GetTokenId() == TokenEnum::R_APR) {
        this->Accept(TokenEnum::R_APR, "Esperado '('");
        this->Exp1();
        this->Accept(TokenEnum::R_FPR, "Esperado ')'");
    } else if (this->TokenAtual.GetTokenId() == TokenEnum::L_IDF) {
        this->Var();
    } else if (this->TokenAtual.GetTokenId() == TokenEnum::L_INT ||
               this->TokenAtual.GetTokenId() == TokenEnum::L_FLT ||
               this->TokenAtual.GetTokenId() == TokenEnum::L_CHR) {
        this->Literal();
    }
}


/**
 *
 */
void AnalisadorSemantico::Literal() {
    if (this->TokenAtual.GetTokenId() == TokenEnum::L_INT) {
        this->Accept(TokenEnum::L_INT, "Esperado numero inteiro");
    } else if (this->TokenAtual.GetTokenId() == TokenEnum::L_FLT) {
        this->Accept(TokenEnum::L_FLT, "Esperado numero real");
    } else if (this->TokenAtual.GetTokenId() == TokenEnum::L_CHR) {
        this->Accept(TokenEnum::L_CHR, "Esperado caracter");
    }

    // TODO: Não podemos ter string somente vetor de caracter
}

/**
 *
 * @param erro
 */
void AnalisadorSemantico::Erro(string erro) {
    this->TokensSaida.push_back(Token("", "", "Erro na compilação"));
    this->TokensSaida.push_back(Token("", "", erro));
    Arquivo arquivo;
    arquivo.GravaToken(this->TokensSaida, SaidaEnum::SINTATICO);
    throw CompilationException();
}

/**
 *
 */
void AnalisadorSemantico::OpSoma() {
    if (this->TokenAtual.GetTokenId() == TokenEnum::O_SUM) {
        this->Accept(TokenEnum::O_SUM, "Esperado '+'");
    } else {
        this->Accept(TokenEnum::O_SUB, "Esperado '-'");
    }
}

/**
 * Método de verificação de comando de seleção IF/ELSE
 */
void AnalisadorSemantico::ComSelecao() {
    this->TokensSaida.push_back(Token("", "", "Seleção"));
    this->Accept(TokenEnum::R_IFF, "Esperado 'IF'");
    this->Exp1();
    this->Accept(TokenEnum::R_THN, "Esperado 'THEN'");
    this->Bloco();
    if (this->TokenAtual.GetTokenId() == TokenEnum::R_ELS) {
        this->Accept(TokenEnum::R_ELS, "Esperado 'ELSE'");
        this->Bloco();
    }
    this->Accept(TokenEnum::R_ENF, "Esperado 'END-IF'");
}