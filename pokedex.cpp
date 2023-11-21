#include<iostream> 
#include<string>

using namespace std;

string vet_tipos[] = {"Agua", "Fogo", "Normal"}; // Vetor global para facilitar a conversão de int para string dos tipos

// Contadores globais dos tipos de Pokemons
int cont_agua = 0;
int cont_fogo = 0;
int cont_normal = 0;

// Contador global para a quantidade de nós visitados
int nos_total = 0; 
int cont_nos_eO = 0; // Contador global para a quantidade de nós visitados na varredura em ordem
int cont_nos_pO = 0; // Contador global para a quantidade de nós visitados na varredura pre ordem
int cont_nos_posO = 0; // Contador global para a quantidade de nós visitados na varredura pos ordem

// Estrutura de dados para a árvore binária
struct treenode{
	int numero_id; // Número do Pokemon
    string nome; // Nome do Pokemon
    int tipo; // Tipo do Pokemon
    string pokebola; // Pokebola do Pokemon
	treenode *esq; // Ponteiro para o filho da esquerda
	treenode *dir; // Ponteiro para o filho da direita
};
typedef treenode *treenodeptr; // Ponteiro para a estrutura de dados

// Função que insere um novo Pokemon na árvore binária por nome
void insert_nome(treenodeptr &arvore, int num, string nome, int tipo, string pokebola){
	if(arvore == NULL){ // Se a árvore estiver vazia
		arvore = new treenode; // Aloca memória para a árvore
		arvore -> numero_id = num; // Atribui o número do Pokemon
        arvore -> nome = nome; // Atribui o nome do Pokemon
        arvore -> tipo = tipo; // Atribui o tipo do Pokemon
        arvore -> pokebola = pokebola; // Atribui a pokebola do Pokemon
		arvore -> esq = NULL; // Atribui NULL para o filho da esquerda
		arvore -> dir = NULL; // Atribui NULL para o filho da direita
	}else if(arvore -> nome > nome){ // Se o nome do Pokemon for maior que o nome do Pokemon da árvore
		insert_nome(arvore -> esq, num, nome, tipo, pokebola); // Chama recursivamenet a função insert_nome para o filho da esquerda
    }
	else{
		insert_nome(arvore -> dir, num, nome, tipo, pokebola); // Chama recursivamenet a função insert_nome para o filho da direita
    }
}

// Função que insere um novo Pokemon na árvore binária por tipo
void insert_tipo(treenodeptr &arvore, int num, string nome, int tipo, string pokebola){
	if(arvore == NULL){ // Se a árvore estiver vazia
		arvore = new treenode; // Aloca memória para a árvore
		arvore -> numero_id = num; // Atribui o número do Pokemon
        arvore -> nome = nome; // Atribui o nome do Pokemon
        arvore -> tipo = tipo; // Atribui o tipo do Pokemon
        arvore -> pokebola = pokebola; // Atribui a pokebola do Pokemon
		arvore -> esq = NULL; // Atribui NULL para o filho da esquerda
		arvore -> dir = NULL; // Atribui NULL para o filho da direita
	}else if(tipo < arvore -> tipo){ // Se o tipo do Pokemon for menor que o tipo do Pokemon da árvore
		insert_tipo(arvore -> esq, num, nome, tipo, pokebola); // Chama recursivamenet a função insert_tipo para o filho da esquerda
    }
	else{
		insert_tipo(arvore -> dir, num, nome, tipo, pokebola); // Chama recursivamenet a função insert_tipo para o filho da direita
    }
}

// Função que pesquisa um Pokemon na árvore binária por nome
treenodeptr search_nome(treenodeptr pesq, string nome){
	if(pesq == NULL){ // Se a árvore estiver vazia
		return NULL; // Retorna NULL
    }else if(nome.compare(pesq -> nome) == 0){ // Se o nome do Pokemon for igual ao nome do Pokemon da árvore
		return pesq; // Retorna o Pokemon
    }else if(pesq -> nome > nome){ // Se o nome do Pokemon for maior que o nome do Pokemon da árvore
		return search_nome(pesq -> esq, nome); // Chama recursivamenet a função search_nome para o filho da esquerda
    }else{
		return search_nome(pesq -> dir, nome); // Chama recursivamenet a função search_nome para o filho da direita
    }
}

// Função que pesquisa um Pokemon na árvore binária por tipo
void imprimir(treenodeptr arvore) {
    if(arvore != NULL){ // Se a árvore não estiver vazia
        imprimir(arvore->esq); // Chama recursivamenet a função imprimir para o filho da esquerda
        cout << endl << "Numero: " << arvore->numero_id << endl << "Nome: " << arvore->nome << endl << "Tipo: " 
			<< vet_tipos[arvore->tipo] << endl << "Pokebola: " << arvore->pokebola << endl; // Imprime as informações do Pokemon
        imprimir(arvore->dir); // Chama recursivamenet a função imprimir para o filho da direita
    }
}

// Função que pesquisa um Pokemon na árvore binária por tipo
void imprimir_pokebola(treenodeptr arvore, string pokebola) {
    if(arvore != NULL){ // Se a árvore não estiver vazia
        imprimir_pokebola(arvore->esq, pokebola); // Chama recursivamenet a função imprimir_pokebola para o filho da esquerda
        if(arvore->pokebola.compare(pokebola) == 0) // Se a pokebola do Pokemon for igual a pokebola pesquisada
			cout << endl << "Numero: " << arvore->numero_id << endl << "Nome: " << arvore->nome << endl << "Tipo: " 
				<< vet_tipos[arvore->tipo] << endl << "Pokebola: " << arvore->pokebola << endl; // Imprime as informações do Pokemon
        imprimir_pokebola(arvore->dir, pokebola); // Chama recursivamenet a função imprimir_pokebola para o filho da direita
    }
}

// Função auxiliar para remover um Pokemon da árvore binária
treenodeptr remove_menor(treenodeptr &atual)
{
    treenodeptr aux = atual; // Auxiliar para o nó a ser removido

    if (aux->esq == NULL) // Encontrou o menor elemento da subárvore
    {
        atual = atual->dir; // Salva os filhos da direita
        return aux; // Retorna a referência para esse nó
    }

    // continua a busca na subárvore da esquerda
    return remove_menor(atual->esq); // Chama recursivamenet a função remove_menor para o filho da esquerda
}

// Remove um pokemon da árvore pela sua pokebola
int remove(treenodeptr &atual, string pkbola, int arvore)
{
    treenodeptr aux; // Auxiliar para o nó a ser removido
    int removed = 0; // Variável para verificar se o Pokemon foi removido

    while (atual != NULL && atual->pokebola == pkbola)
    {
        // Verifica o tipo do Pokemon e decrementa o contador
        if(arvore == 0){
            if(atual->tipo == 0)
                cont_agua--;
            else if(atual->tipo == 1)
                cont_fogo--;
            else if(atual->tipo == 2)
                cont_normal--;
        }

        aux = atual; // Auxiliar para o nó a ser removido

        // Verifica se o Pokemon tem filhos e atribui o filho da direita para o nó atual
        if (atual->esq == NULL){
            atual = aux->dir;
        }

        // Verifica se o Pokemon tem filhos e atribui o filho da esquerda para o nó atual
        else if (atual->dir == NULL){
            atual = aux->esq;
        }

        else{
            aux = remove_menor(atual->dir); // Chama a função auxiliar para remover o menor elemento da subárvore da direita
            atual->pokebola = aux->pokebola; // Atribui a pokebola do Pokemon removido para o Pokemon atual
        }

        delete aux; // Deleta o Pokemon removido
        removed = 1; // Atribui 1 para a variável removed
    }

    // Verifica se o Pokemon foi removido e retornaa variável removed
    if (atual == NULL)
        return removed;

    removed += remove(atual->dir, pkbola, arvore); // Chama recursivamenet a função remove para o filho da direita
    removed += remove(atual->esq, pkbola, arvore); // Chama recursivamenet a função remove para o filho da esquerda

    return removed; // Retorna a variável removed
}

// Função para a varredura em ordem
void emOrdem(treenodeptr arvore, int num){
    if(arvore != NULL){
		emOrdem(arvore -> esq, num);
        cont_nos_eO++;
		if(num == arvore -> numero_id){
			nos_total = cont_nos_eO;
        }
		emOrdem(arvore -> dir, num);
	}
}

// Função para a varredura pre ordem
void preOrdem(treenodeptr arvore, int num){
    if(arvore != NULL){
        cont_nos_pO++;
		if(num == arvore -> numero_id){
			nos_total = cont_nos_pO;
        }
		preOrdem(arvore -> esq, num);
		preOrdem(arvore -> dir, num);
	}
}

// Função para a varredura pos ordem
void posOrdem(treenodeptr arvore, int num){
    if(arvore != NULL){
		posOrdem(arvore -> esq, num);
		posOrdem(arvore -> dir, num);
        cont_nos_posO++;
		if(num == arvore -> numero_id){
			nos_total = cont_nos_posO;
        }
	}
}

// Função para determinar qual das varreduras encontra o Pokemon pelo número primeiro
void menor_varredura(treenodeptr arvore, int num){
    emOrdem(arvore, num); // Chama a função para a varredura em ordem
    int emOrdem_nos = nos_total; // Variável para a quantidade de nós visitados na varredura em ordem
    nos_total = 0; // Zera a variável cont_nos
    cont_nos_eO = 0; // Contador global para a quantidade de nós visitados na varredura em ordem
    preOrdem(arvore, num); // Chama a função para a varredura pre ordem
    int preOrdem_nos = nos_total; // Variável para a quantidade de nós visitados na varredura pre ordem
    nos_total = 0; // Zera a variável cont_nos
    cont_nos_pO = 0;
    posOrdem(arvore, num); // Chama a função para a varredura pos ordem
    int posOrdem_nos = nos_total; // Variável para a quantidade de nós visitados na varredura pos ordema
    nos_total = 0; // Zera a variável cont_nos
    cont_nos_posO = 0;
	
    // Verifica qual das varreduras é a mais eficiente
    if(emOrdem_nos == 0 && preOrdem_nos == 0 && posOrdem_nos == 0){
        cout << "Pokemon nao encontrado!" << endl;
    }else if(emOrdem_nos <= preOrdem_nos && emOrdem_nos <= posOrdem_nos){
		cout << "A varredura mais eficiente foi a 'em ordem' com " << emOrdem_nos << " nos visitados." << endl;
    }else if(preOrdem_nos <= emOrdem_nos && preOrdem_nos <= posOrdem_nos){
		cout << "A varredura mais eficiente foi a 'pre ordem' com " << preOrdem_nos << " nos visitados." << endl;
    }else{
		cout << "A varredura mais eficiente foi a 'pos ordem' com " << posOrdem_nos << " nos visitados." << endl;
    }
}

int main(){
	// Árvores binárias
    treenodeptr arvore_nome = NULL;
	treenodeptr arvore_tipo = NULL;
	treenodeptr pesq;

    // Variáveis para pesquisar um Pokemon
	string pesq_pokebola; // Pesquisa por Pokebola
	string rem_pokebola; // Remove por Pokebola
	int pesq_numero; // Pesquisa por número

    // Variáveis para inserir um novo Pokemon
	int num;
    string nome;
    string tipo;
	int num_tipo; // Variavel auxiliar para converter o tipo de string para int
    string pokebola;

    int opcao = -1; // Variável para a opção do menu

    while(opcao != 0){ // Enquanto a opção for diferente de 0 executar o menu
        
        // Mostra as opções do menu
		cout << endl << "Menu:" << endl;
		cout << "1 - Inserir Pokemon." << endl;
		cout << "2 - Pesquisar Pokemon." << endl; 
		cout << "3 - Remover Pokemon pela sua pokebola." << endl;
		cout << "4 - Imprimir informacoes dos Pokemons cadastrados em ordem alfabetica dos nomes." << endl;
		cout << "5 - Imprimir informacoes dos Pokemons cadastrados em ordem alfabetica dos tipos." << endl;
		cout << "6 - Imprimir informacoes dos Pokemons cadastrados de uma dada pokebola." << endl;
		cout << "7 - Imprimir informacoes sobre a quantidade de Pokemons de cada tipo." << endl;
		cout << "8 - Determinar o percurso que encontra primeiro o Pokemon pelo numero." << endl; // Sei nem oq isso significa
		cout << "0 - Sair." << endl;
        cout << "Digite a opcao: ";

		cin >> opcao; // Lê a opção do menu
        cout << endl;
		
        // Verifica a opção escolhida
		switch(opcao){
            // Opção para inserir um novo Pokemon
            case 1:
                cout << "Digite o numero do Pokemon: ";
                cin >> num;
                cout << "Digite o nome do Pokemon: ";
                cin >> nome;
                cout << "Digite o tipo do Pokemon: ";
                cin >> tipo;
                cout << "Digite a pokebola do Pokemon: ";
                cin >> pokebola;
                cout << endl << "Pokemon adicionado com sucesso!" << endl;
                // Verifica o tipo do Pokemon e o converte para int
				num_tipo = -1;
                for(int i = 0; i < 3; i++){
					if(tipo.compare(vet_tipos[i]) == 0){
						num_tipo = i;
						break;
					}
				}
                if(num_tipo == -1){
                    cout << "Tipo invalido! Foi adicionado o tipo normal." << endl;
					num_tipo = 2;
                }

                // Verifica o tipo do Pokemon e incrementa o contador
				if(num_tipo == 0)
					cont_agua++;
				else if(num_tipo == 1)
					cont_fogo++;
				else if(num_tipo == 2)
					cont_normal++;
                // Chama as funções para inserir um novo Pokemon
                insert_nome(arvore_nome,num,nome,num_tipo,pokebola);
				insert_tipo(arvore_tipo,num,nome,num_tipo,pokebola);
                break;
            
            // Opção para pesquisar um Pokemon
            case 2:
                cout << "Digite o nome do Pokemon: ";
                cin >> nome;
                pesq = search_nome(arvore_nome, nome);
                if(pesq == NULL){
                    cout << "Pokemon nao encontrado!" << endl;
                }else{
                    cout << "Pokemon encontrado!" << endl;
                }
                break;

            // Opção para remover um Pokemon
			case 3:
				cout << "Digite a pokebola dos Pokemons a seres apagados: ";
				cin >> rem_pokebola;
				
                remove(arvore_nome, rem_pokebola,0); // Chama a função para remover um Pokemon por nome
                remove(arvore_tipo, rem_pokebola,1); // Chama a função para remover um Pokemon por tipo
                cout <<  "Pokemons removidos com sucesso!" << endl; // Chama a função para remover um Pokemon por tipo e imprime a quantidade de Pokemons removidos
				break;

            // Opção para imprimir os Pokemons por ordem alfabética dos nomes
			case 4:
				cout << "Pokemons por ordem alfabetica dos nomes:" << endl;
				imprimir(arvore_nome);
				break;

            // Opção para imprimir os Pokemons por ordem alfabética dos tipos
			case 5:
				cout << "Pokemons por ordem alfabetica dos tipos:" << endl;
				imprimir(arvore_tipo);
				break;

            // Opção para imprimir os Pokemons por pokebola
			case 6:
				cout << "Digite a pokebola a ser pesquisada: ";
				cin >> pesq_pokebola;
				cout << "Pokemons que utilizam a pokebola " << pesq_pokebola << ":" << endl;
				imprimir_pokebola(arvore_nome, pesq_pokebola);
				break;

            // Opção para imprimir a quantidade de Pokemons por tipo
			case 7:
				cout << "Quantidade de Pokemons por tipos:" << endl << "Agua: " << cont_agua << endl << 
				"Fogo: "<< cont_fogo << endl << "Normal: " << cont_normal << endl;
				break;

            // Opção para imprimir o percurso que encontra primeiro por número
			case 8:
				cout << "Digite o numero a ser pesquisado: ";
				cin >> pesq_numero;
                cout << endl;
				menor_varredura(arvore_nome, pesq_numero);
				break;

            // Opção para sair do programa
			case 0:
				cout << "Desligando Pokedex..." << endl;
				break;

            // Opção para caso a opção digitada seja inválida
            default:
                cout << "Opcao Invalida!" << endl;
                break;
        }
    }

    return 0; // Retorna 0
}