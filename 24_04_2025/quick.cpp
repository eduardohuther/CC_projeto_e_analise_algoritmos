#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <iomanip>

using namespace std;
using namespace chrono;

void quickSort(vector<int>& arr, int low, int high, int& comparacoes, int& trocas) {
    if (low < high) {
        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            comparacoes++;
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
                trocas++;
            }
        }
        swap(arr[i + 1], arr[high]);
        trocas++;
        int pi = i + 1;

        quickSort(arr, low, pi - 1, comparacoes, trocas);
        quickSort(arr, pi + 1, high, comparacoes, trocas);
    }
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

void testarQuickSort(int tamanho, string tipo, int execucoes) {
    vector<double> tempos;
    int totalComp = 0, totalTrocas = 0;

    for (int i = 0; i < execucoes; i++) {
        vector<int> vetor;

        if (tipo == "ordenado") vetor = gerarOrdenado(tamanho);
        else if (tipo == "inverso") vetor = gerarInverso(tamanho);
        else vetor = gerarAleatorio(tamanho);

        int comparacoes = 0, trocas = 0;
        auto inicio = high_resolution_clock::now();
        quickSort(vetor, 0, vetor.size() - 1, comparacoes, trocas);
        auto fim = high_resolution_clock::now();

        double duracao = duration<double, milli>(fim - inicio).count();
        tempos.push_back(duracao);
        totalComp += comparacoes;
        totalTrocas += trocas;
    }

    cout << "Tipo: " << tipo << ", Tamanho: " << tamanho << "\n";
    cout << "M�dia (sem extremos) tempo (ms): " << mediaSemExtremos(tempos) << "\n";
    cout << "M�dia compara��es: " << totalComp / static_cast<double>(execucoes) << "\n";
    cout << "M�dia trocas: " << totalTrocas / static_cast<double>(execucoes) << "\n\n";
}

int main() {
    srand(time(0));
    cout << fixed << setprecision(4);
    vector<int> tamanhos = {100, 1000, 5000};

    for (int tam : tamanhos) {
        testarQuickSort(tam, "ordenado", 1);
        testarQuickSort(tam, "inverso", 1);
        testarQuickSort(tam, "aleatorio", 10);
    }

    return 0;
}
