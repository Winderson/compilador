/*=====================================================================================================================
Autores: Daniel Deda
         Winderson Jose Barboza dos Santos

Disciplina: Compiladores
Curso: Ciência da Computação
=====================================================================================================================*/

#include "TabelaDeSimbolos.h"
#include <algorithm>

void TabelaDeSimbolos::Insere(int id,string tipo, int tamanho, string escopo, string valor)
{
    Simbolo identificador = Simbolo(id, tipo, tamanho, escopo, valor);
    this->tabelaDeSimbolos.push_back(identificador);
}

void TabelaDeSimbolos::Insere(Simbolo simbolo)
{
    simbolo.SetId(this->ultimoAdicionado+1);
    this->tabelaDeSimbolos.push_back(simbolo);
}

Simbolo TabelaDeSimbolos::Consulta(int id)
{
    for(int i=0; i<tabelaDeSimbolos.size();i++){
        if(tabelaDeSimbolos[i].GetId() == id){
            return tabelaDeSimbolos[i];
        }
    }
    return Simbolo();
}

int TabelaDeSimbolos::Busca(std::string nome){
    for(int i=0; i<this->tabelaDeSimbolos.size();i++){
        if(this->tabelaDeSimbolos[i].GetNome() == nome){
            return tabelaDeSimbolos[i].GetId();
        }
    }
    return -1;
}

Simbolo TabelaDeSimbolos::Tipo(int id)
{
//    // TODO: testar esse esquema de comparar os iteradores
//    for (auto & elem : this->tabelaDeSimbolos)
//    {
//        if(elem == id)
//        {
//            return elem;
//        }
//    }
//    throw "Identificador não se encontra na tabela de simbolos";
}

void TabelaDeSimbolos::Remove(int id)
{
    this->tabelaDeSimbolos.erase(std::remove(this->tabelaDeSimbolos.begin(),
                                             this->tabelaDeSimbolos.end(), id),
                                             this->tabelaDeSimbolos.end());
}