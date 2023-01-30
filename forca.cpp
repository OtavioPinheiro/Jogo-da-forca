#include <iostream>
#include <ostream>
#include <string>
#include <map>
#include <vector>
#include <clocale>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

map<char, bool> chutou;
vector<char> chutes_errados;

bool letra_existe(char letra_chutada, const string& palavra) {
    for(char letra : palavra) {
        if (letra_chutada == letra) {
            return true;
        }
    }
    return false;
}

void mascara(string palavra_secreta) {
    for (char letra : palavra_secreta) {
        if (chutou[letra]) {
            cout << letra << " ";
        }
        else {
            cout << "_ ";
        }
    }
    cout << endl;
}

void chutes_errados_info() {
    cout << "CHUTES ERRADOS: ";
    for (char letra : chutes_errados) {
        cout << letra << " ";
    }
    cout << endl;
}

bool nao_acertou(string palavra_secreta) {
    for (char letra : palavra_secreta) {
        if (!chutou[letra]) {
            return true;
        }
    }
    return false;
}

bool nao_enforcou() {
    return chutes_errados.size() < 5;
}

void cabecalho() {
    cout << "*********************" << endl;
    cout << "*** JOGO DA FORCA ***" << endl;
    cout << "*********************" << endl;
}
bool verifica_se_ja_chutou(char letra) {
    if (chutou[letra]) {
        wcout << L"Você já chutou a letra " << letra << "!" << endl;
        wcout << L"Escolha outra letra por favor." << endl;
        cout << endl;
        return true;
    }
    return false;
}

char pede_chute(char chute) {
    cout << "Digite seu chute: ";
    cin >> chute;
    if (verifica_se_ja_chutou(chute)) {
        chute = pede_chute(chute);
    }
    chutou[chute] = true;
    return chute;
}

void verifica_se_acertou(char chute, string palavra_secreta) {
    if (letra_existe(chute, palavra_secreta)) {
        wcout << L"Você acertou! A letra " << chute << L" está na palavra secreta" << endl;
    }
    else {
        wcout << L"Você errou! A letra " << chute << L" não está na palavra secreta." << endl;
        chutes_errados.push_back(chute);
    }
    cout << endl;
}

void fim_de_jogo(string palavra_secreta) {
    cout << "Fim de jogo!" << endl;
    cout << "A palavra secreta era: " << palavra_secreta << endl;
    if (nao_acertou(palavra_secreta)) {
        wcout << L"Você perdeu! Tente novamente!" << endl;
        cout << endl;
    }
    else {
        wcout << L"Parabéns! Você acertou a palavra secreta!" << endl;
        cout << endl;
    }
}

void mensagem_de_erro() {
    cout << "Não possível acessar o banco de palavras." << endl;
    exit(0);
}

vector<string> le_arquivo() {
    ifstream arquivo;
    arquivo.open("palavras.txt");

    if (arquivo.is_open()) {
        int qtde_palavras = 0;
        arquivo >> qtde_palavras;
        vector<string> palavras;

        for (int i = 0; i < qtde_palavras; i++) {
            string palavra;
            arquivo >> palavra;
            palavras.push_back(palavra);
        }
        arquivo.close();
        return palavras;
    } else {
        mensagem_de_erro();
    }
}

string sorteia_palavra(string palavra_secreta) {
    vector<string> palavras = le_arquivo();
    srand(time(NULL));
    if (!palavras.empty()) {
        int indice_sorteado = rand() % palavras.size();
        palavra_secreta = palavras[indice_sorteado];
        return palavra_secreta;
    } else {
        cout << "O banco de palavras está vazio!" << endl;
        exit(0);
    }
}

void salvar_arquivo(vector<string> nova_lista_palavras) {
    ofstream arquivo;
    arquivo.open("palavras.txt");
    if(arquivo.is_open()) {
        arquivo << nova_lista_palavras.size() << endl;
        for (string palavra : nova_lista_palavras) {
            arquivo << palavra << endl;
        }
        arquivo.close();
    } else {
        mensagem_de_erro();
    }
}

void adicionar_palavra() {
    char res;
    wcout << L"Você quer adicionar uma palavra nova no banco de palavras?(s/n) ";
    cin >> res;
    if (res == 's') {
        wcout << L"Digite a nova palavra usando letras maiúsculas!" << endl;
        string nova_palavra;
        cin >> nova_palavra;

        vector<string> lista_palavras = le_arquivo();
        lista_palavras.push_back(nova_palavra);

        salvar_arquivo(lista_palavras);

        cout << "Palavra adicionada no banco da palavras com sucesso!" << endl;
        wcout << L"Encerrando o jogo. Obrigado por jogar! Até a próxima!" << endl;
    } else if (res == 'n') {
        wcout << L"Encerrando o jogo. Obrigado por jogar! Até a próxima!" << endl;
    } else {
        wcout << L"Digite s para Sim ou n para Não" << endl;
        adicionar_palavra();
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    string palavra_secreta;

    cabecalho();
    palavra_secreta = sorteia_palavra(palavra_secreta);

    while(nao_acertou(palavra_secreta) && nao_enforcou()) {
        chutes_errados_info();
        mascara(palavra_secreta);

        char chute = '\0';
        chute = pede_chute(chute);

        verifica_se_acertou(chute, palavra_secreta);
    }
    fim_de_jogo(palavra_secreta);
    adicionar_palavra();
}