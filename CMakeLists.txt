cmake_minimum_required(VERSION 3.12)
project(Compiladores)

set(CMAKE_CXX_STANDARD 17)

add_executable(Compiladores main.cpp Model/Arquivo.h Model/AnalisadorLexico.h Model/Token.h Model/Arquivo.cpp Model/AnalisadorLexico.cpp Model/AnalisadorSintatico.h Model/AnalisadorSintatico.cpp Controller/CompiladorController.cpp Controller/CompiladorController.h Enuns/EstadoEnum.cpp Enuns/EstadoEnum.h Enuns/PalavrasReservadasEnum.cpp Enuns/PalavrasReservadasEnum.h Enuns/TokenEnum.cpp Enuns/TokenEnum.h Enuns/SaidaEnum.cpp Enuns/SaidaEnum.h Model/AnalisadorSemantico.cpp Model/AnalisadorSemantico.h Exception/CompilationException.cpp Exception/CompilationException.h Model/Simbolo.h Model/Simbolo.cpp Exception/SuccessException.cpp Exception/SuccessException.h)