#include "parque.h"
#include <vector>
#include <algorithm>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) :
 lotacao{lot}, numMaximoClientes{nMaxCli}, clientes {vector<InfoCartao>()}, vagas{lot}{
}

unsigned int ParqueEstacionamento::getNumLugares() const {
    return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const {
    return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string &nome) const {
    for (unsigned i = 0; i < clientes.size(); ++i){
        if (clientes.at(i).nome == nome) return i;
    }
    return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string &nome) {
    if (vagas < 1 || clientes.size() >= numMaximoClientes) return false;
    InfoCartao cliente = {nome, false};
    clientes.push_back(cliente);
    return true;
}

bool ParqueEstacionamento::entrar(const string &nome) {
    if (!vagas) return false;
    for (auto& c: clientes){
        if (c.nome == nome){
            if (!c.presente){
                c.presente = true;
                vagas--;
                return true;
            }
            return false;
        }
    }
    return false;
}

bool ParqueEstacionamento::retiraCliente(const string &nome) {
    for (auto& c: clientes){
        if (c.nome == nome && !c.presente){
            //clientes.erase(find(clientes.begin(),clientes.end(),c));
            return true;
        }
    }
    return false;
}

bool ParqueEstacionamento::sair(const string &nome) {
    for (auto& c: clientes){
        if (c.nome == nome){
            if (c.presente){
                c.presente = false;
                vagas++;
                return true;
            }
            else return false;
        }
    }
    return false;
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const {
    return lotacao - vagas;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const {
    return clientes.size();
}