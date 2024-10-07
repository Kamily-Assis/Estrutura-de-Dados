#include <iostream>
#include <vector>
#include <fstream>
#include <stack>

using namespace std;

/*
Esse codigo funciona para arquivos que apresentem na primeira linha a quantidade
de vertices, seguido da quantidade de arestas.
Ex.: 5  6
*/

class grafo {
    //atributos privados
    int num_vertices;
    vector<int> pais;
    vector<vector<int>> matriz_adj;
    vector<vector<int>> lista_adj;

    //atributos publicos
    public:
        //construtor
        grafo(int n) : num_vertices(n), matriz_adj(n, vector<int>(n, 0)), lista_adj(n), pais(n, -1) {};
        
        //gets
        const vector<int>& get_matriz_adj(int v) const {return matriz_adj[v];}
        
        const vector<int>& get_lista_adj(int u) const {return lista_adj[u];} 
        
        int get_num_vertice() {return num_vertices;}
        
        const vector<int>& get_pais() const {return pais;}
        
        //metodos
        void adicionar_aresta(int u, int v) {//metodo para adicionar uma aresta entre os vértices u e v
            matriz_adj[u][v] = 1;
            matriz_adj[v][u] = 1;
            lista_adj[u].push_back(v);
            lista_adj[v].push_back(u);
        };
        
        void dfs(int s) {//faz a busca em profundidade (DFS) iterativo
            vector<bool> visitados(num_vertices, false);
            stack<int> pilha;
            pilha.push(s);//vertice inicial é o primeiro a entrar na pilha
            
            while (!pilha.empty()) {//enquanto a pilha não estiver vazia
                int u = pilha.top();//transfere o topo para u
                pilha.pop();//remove o topo
                
                if (!visitados[u]) {//verifica se o vertice foi visitado ou não
                    cout << u << " ";
                    visitados[u] = true; //se não, marca como visitado
                    
                    for (int v : lista_adj[u]) {//para todos os vertices adjacentes
                        if (!visitados[v]) {//verificar se foi visitado
                            pilha.push(v); //se não, adicione a pilha
                            pais[v] = u; //atualiza o pai de v
                        };
                    };
                };
            };
            cout << endl;
        };
    };

int main() {
    
    //Leitor dos arquivos e carregamento das estruturas do grafo (mesma bfs)
    ifstream arquivo("grafod.txt");
    int vertices, arestas;
    arquivo >> vertices >> arestas;

    grafo g(vertices);
    
    //lê e adiciona as arestas ao grafo
    for (int i = 0; i < arestas; i++) {
        int u, v;
        arquivo >> u >> v; //lê a proxima aresta do arquivo
        g.adicionar_aresta(u, v); //adiciona a aresta ao grafo
    };

    int s;
    cout << "Digite o vertice de origem: ";
    cin >> s; //o usuario vai informar o valor que será armazenado na variavel s

    cout << "DFS: ";
    //executa o dfs da pilha
    g.dfs(s);
    
    // Obtém e imprime os pais
    const vector<int>& pais = g.get_pais();
    cout << "Pais: ";
    for (int i = 0; i < vertices; i++) {
        cout << pais[i] << " ";
    }
    cout << endl;

    arquivo.close(); //fecha o arquivo

    return 0;
};
