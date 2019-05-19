/*=====================================================================================================================
Autores: Daniel Deda
         Winderson Jose Barboza dos Santos

Disciplina: Compiladores
Curso: Ciência da Computação
=====================================================================================================================*/

#ifndef COMPILADORES_TABELADESIMBOLOS_H
#define COMPILADORES_TABELADESIMBOLOS_H

#include<string>
#include<vector>
#include"Simbolo.h"

using namespace std;

// TODO: Podemos fazer um esquema igual ao Enum do Lexico para substitur as strings passadas por parametros e representar o tipo

class TabelaDeSimbolos
{
public:

    // Inclui o primeiro parâmetro na tabela de simbolos com o tipo indicado no egundo parametro
    void Insere(int id, string tipo, int tamanho, string escopo = "", string valor = "");

    // Inclui o identificador na tabela de simbolos com o tipo indicado no egundo parametro
    void Insere(Simbolo identificador);

    // Retorna se o identificador está ou não na TS
    Simbolo Consulta(int id);

    // Retorna se o identificador está ou não na TS
    int Busca(std::string nome);

    // Retorna o tipo de um identificador na TS (que será representado pelo Enum a ser desenvolvido)
    Simbolo Tipo(int id);

    void Remove(int id);

    vector<Simbolo> tabelaDeSimbolos;
    int ultimoAdicionado = 0;
};

#endif