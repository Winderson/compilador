/*=====================================================================================================================
Autores: Daniel Deda
         Winderson Jose Barboza dos Santos

Disciplina: Compiladores
Curso: Ciência da Computação
=====================================================================================================================*/


#include <iostream>
#include <string>
#include <exception>
#include "CompiladorController.h"
#include "../Model/AnalisadorLexico.h"
#include "../Model/AnalisadorSintatico.h"
#include "../Model/Arquivo.h"
#include "../Enuns/SaidaEnum.h"
#include "../Exception/CompilationException.h"
#include "../Model/AnalisadorSemantico.h"

using namespace std;



/**
 *
 */
void CompiladorController::executar() {
    //AnalisadorLexico analisadorLexico;
    Arquivo arquivo("../entrada.txt");
    AnalisadorLexico analisadorLexico(arquivo);
    vector<Token> tokens;

    while (!arquivo.getBuffer().empty()) {
        char c = arquivo.Prox_char();
        analisadorLexico.SetaEstadoInicial();
        Token token = analisadorLexico.Analex(c);
//        cout << "ANALISADOR LOG --> " << token.GetLog() << endl;
//        cout << "TOKEN ID --> " << token.GetTokenId() << endl;
//        cout << "LEXEMA --> " << token.GetLexema() << endl;
        tokens.push_back(token);
    }
    arquivo.GravaToken(tokens, SaidaEnum::LEXICO);

    // Configuração de lista de tokens sintático
    // OBS: Todos os estados com espaço foram retirados
    vector<Token> tokensSintatico;
    for(int i=tokens.size(); i>=0;i--){
        if(tokens[i].GetLexema() != ""){
            tokensSintatico.push_back(tokens[i]);
        }
    }

    try{
        AnalisadorSintatico analisadorSintatico(tokensSintatico);
        analisadorSintatico.Anasin();
        AnalisadorSemantico analisadorSemantico(tokensSintatico);
        analisadorSemantico.Anasem();
    } catch (exception& e){
        cout << e.what() << '\n';
    }
}




void CompiladorController::analisar(Arquivo arquivo) {
//    AnalisadorLexico analisadorLexico;
//    while(!arquivo.IsEmpty()){
//        char caracter = arquivo.Prox_char();
//        Token token = analisadorLexico.Analex(caracter);
//        arquivo.GravaToken(token);
//    }
}