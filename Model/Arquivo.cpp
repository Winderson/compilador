/*=====================================================================================================================
Autores: Daniel Deda
         Winderson Jose Barboza dos Santos

Disciplina: Compiladores
Curso: Ciência da Computação
=====================================================================================================================*/

#include <iostream>
#include <string>
#include <iomanip>
#include "Arquivo.h"
using namespace std;

/**
 *
 * @param inputFile
 * @param outputFile
 */
Arquivo::Arquivo(string inputFile)
{
    //this->Log = ofstream(outputFile, ios_base::app);
    this->File = ifstream(inputFile);
    vector<char> auxiliar;

    if (this->File.is_open())
    {
        while (!this->File.eof())
        {
            auxiliar.push_back((char) (this->File.get()));
        }
        this->File.close();
    }

    for(int i=auxiliar.size(); i>=0;i--){
        this->Buffer.push_back(auxiliar[i]);
    }
}

/**
 *
 * @return
 */
char Arquivo::Prox_char()
{
    char prox = this->Buffer.back();
    this->Buffer.pop_back();
    // Guarda o ultimo elemento que foi removido
    UltimaLeitura = prox;
    return prox;
}

/**
 *
 * @return
 */
void Arquivo::Ant_char(){
    this->Buffer.push_back(this->UltimaLeitura);
}

/**
 *
 * @param estado
 * @param token
 */
void Arquivo::Grava_token(string estado, Token token)
{
    //this->Log.open("saida.txt", ios::app);

//    ofstream arquivo("saida", ios_base::trunc);
//
//    if (arquivo.is_open())
//    {
//        std::cout << "Arquivo de texto aberto com sucesso!" << std::endl;
//    }
//    else
//        std::cout << "Erro ao abrir arquivo de texto.";
//
//    arquivo.close();
}


/**
 *
 * @param tokens
 */
void Arquivo::GravaToken(vector<Token> tokens, SaidaEnum saida){


    if(saida == SaidaEnum::LEXICO) {
        ofstream arquivo("../lexico.txt", ios::trunc);
        if (arquivo.is_open())
        {
            arquivo << "|" << setw(27) << "Log do Analisador Léxico" << setw(3) << "|" << setw(9) << "Tokens" << setw(4) << "|" << setw(9) << "Lexemas" << setw(3) << "|";
            arquivo << "\n";
            arquivo << "-------------------------------------------------------\n";
            for(unsigned int i=0; i<tokens.size();i++) {
                arquivo << "|" << setw(19) << tokens[i].GetLog() << setw(10) << "|" << setw(8) << tokens[i].GetTokenId() << setw(5) << "|" << setw(5) << tokens[i].GetLexema() << setw(7) << "|";
                arquivo << "\n";
            }
        }
        else
        {
            std::cout << "Erro ao abrir arquivo de texto.";
        }
        arquivo.close();
    } else if( saida == SaidaEnum::SINTATICO) {
        ofstream arquivo("../sintatico.txt", ios::trunc);
        if (arquivo.is_open())
        {
            arquivo << "|" << setw(9) << "Tokens" << setw(4) << "|" << setw(9) << "Lexemas" << setw(3) << "|" << setw(19) << "Log" << setw(10) << "|" ;
            arquivo << "\n";
            arquivo << "-------------------------------------------------------\n";
            for(unsigned int i=0; i<tokens.size();i++) {
                arquivo << "|" << setw(8) << tokens[i].GetTokenId() << setw(5) << "|" << setw(5) << tokens[i].GetLexema() << setw(7) << "|" << setw(19) << tokens[i].GetLog() << setw(10) << "|";
                arquivo << "\n";
            }
        }
        else
        {
            std::cout << "Erro ao abrir arquivo de texto.";
        }
    } else if (saida == SaidaEnum::SEMANTICO) {
        ofstream arquivo("../semantico.txt", ios::trunc);
    } else if (saida == SaidaEnum::MEPA) {
        ofstream arquivo("../mepa.txt", ios::trunc);
    }
}

void Arquivo::GravaTabelaSimbolos(TabelaDeSimbolos tabelaSimbolos){
    ofstream arquivo("../tabela_simbolos.txt", ios::trunc);
    if (arquivo.is_open())
    {
        arquivo << "|" << setw(9) << "Nome" << setw(4) << "|" << setw(9) << "Tipo" << setw(4) << "|" << setw(9) << "Classe" << setw(3) << "|";
        arquivo << "\n";
        arquivo << "---------------------------------------\n";
        for(unsigned int i=0; i<tabelaSimbolos.tabelaDeSimbolos.size();i++) {
            arquivo << "|" << setw(9) << tabelaSimbolos.tabelaDeSimbolos[i].GetNome() << setw(4) << "|" << setw(9) << tabelaSimbolos.tabelaDeSimbolos[i].GetTipo() << setw(4) << "|" << setw(9) << tabelaSimbolos.tabelaDeSimbolos[i].GetClasse() << setw(3) << "|";
            arquivo << "\n";
        }
    }
    else
    {
        std::cout << "Erro ao abrir arquivo de texto.";
    }
    arquivo.close();
}

/**
 *
 * @return
 */
bool Arquivo::IsEmpty() {
    return this->Buffer.size() == 0;
}
