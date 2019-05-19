/*=====================================================================================================================
Autores: Daniel Deda
         Winderson Jose Barboza dos Santos

Disciplina: Compiladores
Curso: Ciência da Computação
=====================================================================================================================*/

#ifndef SIMBOLO_H
#define SIMBOLO_H
#include <string>

class Simbolo
{

public:
    /**
     * Construtor
     * @param id
     * @param tipo
     * @param tamanho
     * @param escopo
     * @param valor
     */
    Simbolo():Id(0){};
    inline Simbolo(int id, std::string tipo, int tamanho, std::string escopo, std::string valor):
            Id(id), Tipo(tipo), Tamanho(tamanho), Escopo(escopo), Valor(valor) {}

//    inline bool operator == (std::string id)
//    {
//        return this->Id == id;
//    }
//
//    inline bool operator != (std::string id)
//    {
//        return this->Id != id;
//    }

    int GetId();
    void SetId(int id);
    std::string GetNome();
    void SetNome(std::string nome);
    std::string GetTipo();
    void SetTipo(std::string tipo);
    int GetTamanho();
    void SetTamanho(int tamanho);
    std::string GetClasse();
    void SetClasse(std::string classe);
    std::string GetEscopo();
    void SetEscopo(std::string escopo);
    std::string GetValor();
    void SetValor(std::string valor);
    std::string GetDimensao();
    void SetDimensao(std::string dimensao);
    bool GetUtilizado();
    void SetUtilizado(bool utilizado);

private:
    // Variaveis
    int Id;
    std::string Nome;
    std::string Tipo;
    int Tamanho;
    std::string Classe;
    std::string Escopo;
    std::string Valor;
    std::string Dimensao;
    bool Ultilizado;
};


#endif //SIMBOLO_H