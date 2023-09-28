#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>

using namespace std;

/*Implemente a estrutura grafo com representação em: Matriz de Adjacência
e Lista de Adjacência.*/

class grafo{
    //atributos privados
    int num_vertices;  // número de vértices no grafo
    vector<vector<int>> matriz_adj; // matriz de Adjacência
    vector<vector<int>> lista_adj; // lista de Adjacência
    
    //atributos publicos
    public:
        // construtor que inicializa o número de vértices, a matriz e a lista
        grafo(int n):num_vertices(n), matriz_adj(n, vector<int>(n, 0)), lista_adj(n){};
        
        //gets
        const vector<int> &get_matriz_adj(int v) const { return matriz_adj[v]; }
        
        const vector<int> &get_lista_adj(int u) const { return lista_adj[u]; }
        
        int get_num_vertice() { return num_vertices; }
        
        //metodos
        void adicionar_aresta(int u, int v){
            matriz_adj[u][v] = 1; //1 é o valor padrão de distância entre os vertices
            matriz_adj[v][u] = 1;
            lista_adj[u].push_back(v);
            lista_adj[v].push_back(u);
        };
        
        /*Busca em Largura (BFS) - o criar uma função que imprima o caminho entre
        dois vértices s e t  formado pelo BFS. 
        indicar que “não há caminho entre os vértices” caso não haja o caminho. */

        // Função BFS para encontrar um caminho entre s e t
        void bfs_caminho(int s, int t){
            //atributos privados
            vector<bool> visitados(num_vertices, false); // marca os vértices visitados
            vector<int> pais(num_vertices, -1); // mantém o histórico de pais
            
            queue<int> q; // fila para a BFS
            visitados[s] = true; // marca o vértice de início como visitado
            q.push(s); // adiciona o vértice de início à fila
            
            while (!q.empty()){ // enquanto houver vértices na fila
                int u = q.front(); // pega o vértice na posição atual da fila
                q.pop(); // Remove o vértice da fila para que ele não seja revisitado
                
                for(int v:lista_adj[u]){//vai verificar todos os vertices adjacentes ao vertice atual
                                        //usando a Lista de Adjacência
                                        
                    if(!visitados[v]){ //verifica se o vertice foi visitado ou não
                        q.push(v); //se o vertice 'v' n foi visitado, ele é adicionado a fila q.
                        visitados[v] = true; //marca o vertice v como visitado
                        pais[v] = u; //registra o vertice 'u' como pai do vertice 'v'.
                        //usado para reconstruir o caminho entre eles 
                    };
                };
            };
            
            if(!visitados[t]){ // verifica se t foi visitado a partir de s
                //se não foi
                cout << "Não existe caminho entre o vertice t e s" << endl;
                
            }
            
            else { //se foi  
                
                vector<int> caminho; //vetor que vai armazenar o caminho entre os vetores
                int vet_atual = t; //armazena o vertice do destino (t) para rastrear o caminho até a origem
                
                while(vet_atual != -1){ //vai percorrer os vertices pais
                    caminho.push_back(vet_atual); //vertice atual é adicionado ao vetor caminho para construir o caminho
                    vet_atual = pais[vet_atual]; //A variável vet_atual é atualizada para o pai do vértice atual, permitindo
                                                    //que o loop continue varrendo todo o caminho.
                };
                
                cout << "Caminho entre os vertices " << s << " e " << t << ": ";
                //vai percorrer caminho (de trás pra frente)
                for(int i = caminho.size() - 1; i >=0; i--){
                    cout << caminho[i];
                    if(i != 0) cout << "->"; //todos tem (menos o do indice 0)
                };
                cout << endl;
            };
        };
        // Destrutor
        ~grafo(){
            lista_adj.clear();
        };
};

int main()
{
    //Leitor dos arquivos e carregamento das estruturas do grafo
    
    ifstream arquivo("arq_teste.txt"); //input-file-stream - faz o fluxo de entrada do arquivo
    int vertices, arestas;
    arquivo >> vertices >> arestas; //usado para ler e armazenar os valores que estavam no arquivo
    
    //teste cout << vertices << endl << arestas << endl;
    
    //cria o objeto
    grafo g(vertices);
    
    //lê e adiciona as arestas ao grafo
    for(int i = 0; i < arestas; i++){
        int u, v;
        arquivo >> u >> v; //lê a proxima aresta do arquivo
        g.adicionar_aresta(u,v); //adiciona a aresta ao grafo 
    };
    
    int s,t;
    cout << "Digite o vertice de origem e o de destino: ";
    cin >> s >> t; //o usuario vai informar os dois valores que serão armazenados nas variaveis

    //executa o bfs do caminho
    g.bfs_caminho(s,t);
    
    arquivo.close(); //fecha o arquivo

    
    return 0;
}


