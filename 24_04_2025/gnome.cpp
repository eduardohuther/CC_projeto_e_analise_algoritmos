#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>

using namespace std;

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

void testarGnomeSort(int tamanho, string tipo, int execucoes) {
    vector<double> tempos;
    int totalComp = 0, totalTrocas = 0;

    for (int i = 0; i < execucoes; i++) {
        vector<int> vetor;

        if (tipo == "ordenado") vetor = gerarOrdenado(tamanho);
        else if (tipo == "inverso") vetor = gerarInverso(tamanho);
        else vetor = gerarAleatorio(tamanho);

        int comparacoes = 0, trocas = 0;

        clock_t inicio = clock();
        gnomeSort(vetor, comparacoes, trocas);
        clock_t fim = clock();

        double duracao = double(fim - inicio) / CLOCKS_PER_SEC * 1000.0; // em milissegundos
        tempos.push_back(duracao);

        //printf("Tempo execução #%d: %.4f ms\n", i + 1, duracao);

        totalComp += comparacoes;
        totalTrocas += trocas;
    }

    cout << "Tipo: " << tipo << ", Tamanho: " << tamanho << "\n";

    if (execucoes > 1)
        cout << "Média (sem extremos) tempo (ms): " << mediaSemExtremos(tempos) << "\n";
    else
        cout << "Tempo (ms): " << tempos[0] << "\n";

    cout << "Média comparações: " << totalComp / static_cast<double>(execucoes) << "\n";
    cout << "Média trocas: " << totalTrocas / static_cast<double>(execucoes) << "\n\n";
}

int main() {
    srand(time(0));
    cout << fixed << setprecision(4);
    vector<int> tamanhos = {100, 1000, 5000};

    for (int tam : tamanhos) {
        testarGnomeSort(tam, "ordenado", 1);
        testarGnomeSort(tam, "inverso", 1);
        testarGnomeSort(tam, "aleatorio", 10);
    }

    return 0;
}
