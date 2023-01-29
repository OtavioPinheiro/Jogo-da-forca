#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <clocale>
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
    }
    else {
        wcout << L"Parabéns! Você acertou a palavra secreta!" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    string palavra_secreta = "MELANCIA";

    cabecalho();

    while(nao_acertou(palavra_secreta) && nao_enforcou()) {
        chutes_errados_info();
        mascara(palavra_secreta);

        char chute = '\0';
        chute = pede_chute(chute);

        verifica_se_acertou(chute, palavra_secreta);
    }
    fim_de_jogo(palavra_secreta);
}