/*=====================================================================================================================
Autores: Daniel Deda
         Winderson Jose Barboza dos Santos

Disciplina: Compiladores
Curso: Ciência da Computação
=====================================================================================================================*/
#include <iostream>
#include "AnalisadorSintatico.h"
#include "../Enuns/TokenEnum.h"
#include "Arquivo.h"
#include "../Enuns/SaidaEnum.h"
#include "../Exception/CompilationException.h"
#include "../Exception/SuccessException.h"

using namespace std;

/**
 * Construtor
 * @param tokens
 */
AnalisadorSintatico::AnalisadorSintatico(std::vector<Token> tokens) {
    this->TokenAtual = Token();
    this->Tokens = tokens;
}

/**
 * Método responsável pela inicialização do analisador sintático
 */
void AnalisadorSintatico::Anasin() {
    this->Programa();
    this->Bloco();
}

/**
 * Método responsável por pegar o próximo token
 * para validá-lo
 * @return
 */
Token AnalisadorSintatico::ProxToken() {
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
void AnalisadorSintatico::Accept(string esperado, string msg) {
    if (this->TokenAtual.GetTokenId() == esperado) {
        this->TokensSaida.push_back(Token(this->TokenAtual.GetTokenId(), this->TokenAtual.GetLexema(), "OK"));
        if (this->Tokens.empty()) {
            Arquivo arquivo;
            arquivo.GravaToken(this->TokensSaida, SaidaEnum::SINTATICO);
            //throw SuccessException();
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
void AnalisadorSintatico::Programa() {
    this->TokensSaida.push_back(Token("", "", "Prog"));
    this->TokensSaida.push_back(Token("", "", "Principal"));
    this->TokenAtual = this->ProxToken();
    this->ListaDecl();
}

/**
 * Método de lista de declarações
 */
void AnalisadorSintatico::ListaDecl() {
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
void AnalisadorSintatico::Decl() {
    if (this->TokenAtual.GetTokenId() == TokenEnum::R_VAR) {
        this->DeclVar();
    } else if (this->TokenAtual.GetTokenId() == TokenEnum::R_MAN) {
        this->DeclMain();
    }
}

/**
 * Método de declaração de variável
 */
void AnalisadorSintatico::DeclVar() {
    this->TokensSaida.push_back(Token("", "", "Decl. de Variável"));
    this->Accept(TokenEnum::R_VAR, "Esperado 'VAR'");
    // Chamada para o método que valida o tipo
    this->EspecTipo();
    // Chamada para o método que valida o var
    this->Var();
    // Accept
    this->Accept(TokenEnum::O_POV, "Esperado ';'");
}

/**
 * Método de declaração do main
 */
void AnalisadorSintatico::DeclMain() {
    this->TokensSaida.push_back(Token("", "", "Decl. Main"));
    this->Accept(TokenEnum::R_MAN, "Esperado 'MAIN'");
    this->Accept(TokenEnum::R_APR, "Esperado '('");
    this->Accept(TokenEnum::R_FPR, "Esperado ')'");
    this->Bloco();
    this->Accept(TokenEnum::R_END, "Esperado 'END'");
}

/**
 * Método de verificação do var
 */
void AnalisadorSintatico::Var() {
    this->Accept(TokenEnum::L_IDF, "Esperado Identificador");
}


/**
 * método de inicialização do bloco
 */
void AnalisadorSintatico::Bloco() {
    this->ListaCom();
}

/**
 * Método de verificação do tipo
 */
void AnalisadorSintatico::EspecTipo() {
    if (this->TokenAtual.GetTokenId() == TokenEnum::R_INT) {
        this->Accept(TokenEnum::R_INT, "Esperado 'INT'");
    } else if (this->TokenAtual.GetTokenId() == TokenEnum::R_REA) {
        this->Accept(TokenEnum::R_REA, "Esperado 'REAL'");
    } else if (this->TokenAtual.GetTokenId() == TokenEnum::R_CHA) {
        this->Accept(TokenEnum::R_CHA, "Esperado 'CHAR'");
    } else {
        Erro("Esperado tipo válido");
    }
}

/**
 * Método responsável pela lista de comandos
 */
void AnalisadorSintatico::ListaCom() {
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
void AnalisadorSintatico::Comando() {
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
void AnalisadorSintatico::ComAtrib() {
    this->TokensSaida.push_back(Token("", "", "Atribuição"));
    this->Var();
    this->Accept(TokenEnum::O_ATR, "'=' esperado");
    this->Exp1();
    this->Accept(TokenEnum::O_POV, "';' esperado");
}

/**
 *
 */
void AnalisadorSintatico::ComEscrita() {
    this->TokensSaida.push_back(Token("", "", "Escrita"));
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
void AnalisadorSintatico::ComRepeticao() {
    this->TokensSaida.push_back(Token("", "", "Repetição"));
    this->Accept(TokenEnum::R_WLE, "'WHILE' esperado");
    this->Exp1();
    this->Accept(TokenEnum::R_DOO, "'DO' esperado.");
    this->Bloco();
    this->Accept(TokenEnum::R_LOP, "'LOOP' esperado.");
}

/**
 *
 */
void AnalisadorSintatico::Exp1() {
    this->ExpMult1();
    this->Exp2();
}

/**
 *
 */
void AnalisadorSintatico::Exp2() {
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
void AnalisadorSintatico::ExpMult1() {
    this->ExpSimples();
    this->ExpMult2();
}

/**
 *
 */
void AnalisadorSintatico::ExpMult2() {
    if (this->TokenAtual.GetTokenId() == TokenEnum::O_DIV || this->TokenAtual.GetTokenId() == TokenEnum::O_MOD) {
        this->OpMult();
    } else {
        // Vazio
    }
}

/**
 *
 */
void AnalisadorSintatico::OpMult() {
    if (this->TokenAtual.GetTokenId() == TokenEnum::O_DIV) {
        this->Accept(TokenEnum::O_DIV, "Esperado '/'");
    } else if (this->TokenAtual.GetTokenId() == TokenEnum::O_MOD) {
        this->Accept(TokenEnum::O_MOD, "Esperado '%'");
    }
}

/**
 *
 */
void AnalisadorSintatico::ExpSimples() {
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
void AnalisadorSintatico::Literal() {
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
void AnalisadorSintatico::Erro(string erro) {
    this->TokensSaida.push_back(Token("", "", "Erro na compilação"));
    this->TokensSaida.push_back(Token("", "", erro));
    Arquivo arquivo;
    arquivo.GravaToken(this->TokensSaida, SaidaEnum::SINTATICO);
    throw CompilationException();
}

/**
 *
 */
void AnalisadorSintatico::OpSoma() {
    if (this->TokenAtual.GetTokenId() == TokenEnum::O_SUM) {
        this->Accept(TokenEnum::O_SUM, "Esperado '+'");
    } else {
        this->Accept(TokenEnum::O_SUB, "Esperado '-'");
    }
}

/**
 * Método de verificação de comando de seleção IF/ELSE
 */
void AnalisadorSintatico::ComSelecao() {
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