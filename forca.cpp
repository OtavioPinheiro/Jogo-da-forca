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

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");

    cout << "*********************" << endl;
    cout << "*** JOGO DA FORCA ***" << endl;
    cout << "*********************" << endl;

    string palavra_secreta = "MELANCIA";

    bool nao_acertou = true;
    bool nao_enforcou = true;

    while(nao_acertou && nao_enforcou) {
        chutes_errados_info();
        mascara(palavra_secreta);

        cout << "Digite seu chute: ";
        char chute;
        cin >> chute;
        if (chutou[chute]) {
            wcout << L"Você já chutou a letra " << chute << "!" << endl;
            wcout << L"Escolha outra letra por favor." << endl;
            cout << endl;
            continue;
        }
        chutou[chute] = true;

        if (letra_existe(chute, palavra_secreta)) {
            wcout << L"Você acertou! A letra " << chute << L" está na palavra secreta" << endl;
        }
        else {
            wcout << L"Você errou! A letra " << chute << L" não está na palavra secreta." << endl;
            chutes_errados.push_back(chute);
        }
        cout << endl;
    }
}