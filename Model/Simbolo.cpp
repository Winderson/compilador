/*=====================================================================================================================
Autores: Daniel Deda
         Winderson Jose Barboza dos Santos

Disciplina: Compiladores
Curso: Ciência da Computação
=====================================================================================================================*/


#include "Simbolo.h"
using namespace std;

// Getters and Setters

int Simbolo::GetId() {
    return this->Id;
}

void Simbolo::SetId(int id) {
    this->Id = id;
}

string Simbolo::GetNome() {
    return this->Nome;
}

void Simbolo::SetNome(string nome) {
    this->Nome = nome;
}

string Simbolo::GetTipo(){
    return this->Tipo;
}

void Simbolo::SetTipo(string tipo) {
    this->Tipo = tipo;
}

int Simbolo::GetTamanho(){
    return this->Tamanho;
}

void Simbolo::SetTamanho(int tamanho) {
    this->Tamanho = tamanho;
}

string Simbolo::GetClasse() {
    return this->Classe;
}

void Simbolo::SetClasse(string classe) {
    this->Classe = classe;
}

string Simbolo::GetEscopo() {
    return Escopo;
}

void Simbolo::SetEscopo(string escopo) {
    this->Escopo = escopo;
}

string Simbolo::GetValor(){
    return this->Valor;
}

void Simbolo::SetValor(std::string valor) {
    this->Valor = valor;
}

string Simbolo::GetDimensao() {
    return this->Dimensao;
}

void Simbolo::SetDimensao(std::string dimensao) {
    this->Dimensao = dimensao;
}

bool Simbolo::GetUtilizado(){
    return this->Ultilizado;
}
void Simbolo::SetUtilizado(bool utilizado){
    this->Ultilizado = utilizado;
}