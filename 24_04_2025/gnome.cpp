#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace chrono;

int gnomeSort(vector<int>& arr, int& comparacoes, int& trocas) {
    int index = 0;
    int n = arr.size();
    while (index < n) {
        if (index == 0)
            index++;
        comparacoes++;
        if (arr[index] >= arr[index - 1]) {
            index++;
        } else {
            swap(arr[index], arr[index - 1]);
            trocas++;
            index--;
        }
    }
    return 0;
}

vector<int> gerarOrdenado(int n) {
    vector<int> v(n);
    for (int i = 0; i < n; i++) v[i] = i;
    return v;
}

vector<int> gerarInverso(int n) {
    vector<int> v(n);
    for (int i = 0; i < n; i++) v[i] = n - i;
    return v;
}

vector<int> gerarAleatorio(int n) {
    vector<int> v(n);
    for (int i = 0; i < n; i++) v[i] = rand() % (n * 10);
    return v;
}

double mediaSemExtremos(vector<double>& tempos) {
    sort(tempos.begin(), tempos.end());
    double soma = 0;
    for (size_t i = 1; i < tempos.size() - 1; i++) {
        soma += tempos[i];
    }
    return soma / (tempos.size() - 2);
}

void testarGnomeSort(int tamanho, string tipo) {
    vector<double> tempos;
    int totalComp = 0, totalTrocas = 0;

    for (int i = 0; i < 10; i++) {
        vector<int> vetor;

        if (tipo == "ordenado") vetor = gerarOrdenado(tamanho);
        else if (tipo == "inverso") vetor = gerarInverso(tamanho);
        else vetor = gerarAleatorio(tamanho);

        int comparacoes = 0, trocas = 0;
        auto inicio = high_resolution_clock::now();
        gnomeSort(vetor, comparacoes, trocas);
        auto fim = high_resolution_clock::now();

        double duracao = duration<double, milli>(fim - inicio).count();
        tempos.push_back(duracao);
        totalComp += comparacoes;
        totalTrocas += trocas;
    }

    cout << "Tipo: " << tipo << ", Tamanho: " << tamanho << "\n";
    cout << "Média (sem extremos) tempo (ms): " << mediaSemExtremos(tempos) << "\n";
    cout << "Média comparações: " << totalComp / 10.0 << "\n";
    cout << "Média trocas: " << totalTrocas / 10.0 << "\n\n";
}

int main() {
    srand(time(0));
    cout << fixed << setprecision(4);
    vector<int> tamanhos = {100, 1000, 5000};

    for (int tam : tamanhos) {
        testarGnomeSort(tam, "ordenado");
        testarGnomeSort(tam, "inverso");
        testarGnomeSort(tam, "aleatorio");
    }

    return 0;
}
