#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

class Grafo {
    //atributos privados
    int num_vertices;
    vector<vector<int>> matriz_adj;
    vector<vector<int>> lista_adj;

    //atributos publicos
    public:
        Grafo(int n) : num_vertices(n), matriz_adj(n, vector<int>(n, 0)), lista_adj(n) {};
    
        void adicionar_aresta(int u, int v) {
            matriz_adj[u][v] = 1; //1 é o valor padrão de distância entre os vertices
            matriz_adj[v][u] = 1;
            lista_adj[u].push_back(v);
            lista_adj[v].push_back(u);
        };
        
        void bfs_caminho(int s, int t) {
            vector<bool> visitados(num_vertices, false); //marca os vértices visitados
            vector<int> pais(num_vertices, -1); //mantém o histórico de pais
            
            queue<int> q; //fila para a BFS
            visitados[s] = true; // marca o vértice do início como visitado
            q.push(s); // adiciona o vértice do início à fila
            
            while (!q.empty()) {//enquanto houver vértices na fila
                int u = q.front();
                q.pop();//remove o vértice da fila para que ele não seja revisitado
                
                for (int v : lista_adj[u]) {//vai verificar todos os vertices adjacentes ao vertice atual
                                           //usando a Lista de Adjacência
                    
                    if (!visitados[v]) {//verifica se o vertice foi visitado ou não
                        q.push(v);
                        visitados[v] = true;
                        pais[v] = u;
                    };
                };
            };
            
            if (!visitados[t]) { // verifica se t foi visitado a partir de s
                //se não foi
                cout << "Não existe caminho entre os vértices" << endl;
            } 
            else {//se foi
                vector<int> caminho;
                int vet_atual = t;
                
                while (vet_atual != -1) {//vai percorrer os vertices pais
                    caminho.push_back(vet_atual);
                    vet_atual = pais[vet_atual];
                };
                
                cout << "Caminho entre os vértices " << s << " e " << t << ": " << endl;;
                //vai percorrer caminho (de trás pra frente)
                for (int i = caminho.size() - 1; i >= 0; i--) {
                    cout << caminho[i];
                    if (i != 0) cout << " -> "; //separador (menos o do indice 0)
                };
                cout << endl;
            };
        };
};

int main() {
    
    ifstream arquivo("grafo.txt"); //input-file-stream - faz o fluxo de entrada do arquivo
    int vertices, arestas;
    arquivo >> vertices >> arestas; //usado para ler e armazenar 
                                   //os valores que estavam no arquivo

    //cria o objeto
    Grafo g(vertices);

    for (int i = 0; i < arestas; i++) {
        int u, v;
        arquivo >> u >> v; //lê a proxima aresta do arquivo
        g.adicionar_aresta(u, v);
    }

    int s, t;
    cout << "Digite o vertice de origem e o de destino: ";
    cin >> s >> t; //o usuario vai informar os dois valores 
                  //que serão armazenados nas variaveis s e t

    //executa o bfs do caminho
    g.bfs_caminho(s, t);

    arquivo.close(); //fecha o arquivo

    return 0;
}
