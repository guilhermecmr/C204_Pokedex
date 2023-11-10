#include<iostream> 
#include<string>

using namespace std;

string vet_tipos[] = {"Agua", "Fogo", "Normal"}; // Vetor global para facilitar a conversão de int para string dos tipos

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

// Função para verificar se o nome é maior que o outro em relação a ordem
bool nome_maior(string s1, string s2) {
    if(s1.size() >= s2.size()){ // Se o tamanho da primeira string for maior ou igual ao da segunda
        return 1; // Retorna verdadeiro
    }
	for(int i = 0; i < s1.size() && i < s2.size(); i++){ // Se o tamanho da primeira string for menor que o da segunda
        if(s1[i] > s2[i]){ // Verifica se o caractere da primeira string é maior que o da segunda
            return 1; // Retorna verdadeiro
        }else if(s1[i] < s2[i]){ // Verifica se o caractere da primeira string é menor que o da segunda
            return 0; // Retorna falso
        }
    }
    return 0; // Retorna falso
}

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
	}else if(nome_maior(arvore -> nome, nome)){ // Se o nome do Pokemon for maior que o nome do Pokemon da árvore
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
    }else if(nome_maior(pesq -> nome, nome)){ // Se o nome do Pokemon for maior que o nome do Pokemon da árvore
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

// Função para remover um Pokemon da árvore binária por pokebola
treenodeptr remove_pokebola(treenodeptr raiz, string pokebola) {
    treenodeptr temp; // Ponteiro temporário
    
    // Caso base
    if(raiz == NULL){
        return raiz;
    }

    if(pokebola < raiz->pokebola){ // Se a pokebola do Pokemon for menor que a pokebola do Pokemon da árvore
        raiz->esq = remove_pokebola(raiz->esq, pokebola); // Chama recursivamenet a função remove_pokebola para o filho da esquerda
    }else if(pokebola > raiz->pokebola) {
        raiz->dir = remove_pokebola(raiz->dir, pokebola); // Chama recursivamenet a função remove_pokebola para o filho da direita
    }else{
        
        if(raiz->esq == NULL){ // Se o filho da esquerda for NULL
            temp = raiz->dir; // Atribui o filho da direita para o ponteiro temporário 
            delete raiz; // Deleta o Pokemon
            return temp; // Retorna o ponteiro temporário
        }else if (raiz->dir == NULL){
            temp = raiz->esq; // Atribui o filho da esquerda para o ponteiro temporário
            delete raiz; // Deleta o Pokemon
            return temp; // Retorna o ponteiro temporário
        }

        while(temp->esq != NULL){ // Encontra o menor valor da subárvore da direita
                temp = temp -> esq;
            }

        // Copia o menor valor da subárvore da direita para o Pokemon a ser removido
        raiz->numero_id = temp->numero_id;
        raiz->nome = temp->nome;
        raiz->tipo = temp->tipo;
        raiz->pokebola = temp->pokebola;

        raiz->dir = remove_pokebola(raiz->dir, temp->pokebola); // Chama recursivamenet a função remove_pokebola para o filho da direita
    }
    return raiz; // Retorna a raiz
}

// Função auxiliar para encontrar primeiro por número
bool encontrar_primeiro_temp(treenodeptr raiz, int numero, bool &encontrou) {
    // Caso base
    if(raiz == NULL){
        return false;
    }

    // Pré-Ordem
    if(raiz->numero_id == numero){ // Se o número do Pokemon for igual ao número do Pokemon da árvore
        encontrou = true; // Atribui verdadeiro para a variável encontrou
        return true; // Retorna verdadeiro
    }
    bool esquerda = encontrar_primeiro_temp(raiz->esq, numero, encontrou); // Chama recursivamenet a função encontrar_primeiro_temp para o filho da esquerda
    if (encontrou) { // Se encontrou for verdadeiro
        return true; // Retorna verdadeiro
    }

    // Em Ordem
    bool meio = (raiz->numero_id == numero); // Se o número do Pokemon for igual ao número do Pokemon da árvore
    if(meio){ // Se meio for verdadeiro
        encontrou = true; // Atribui verdadeiro para a variável encontrou
        return true; // Retorna verdadeiro
    }

    bool direita = encontrar_primeiro_temp(raiz->dir, numero, encontrou); // Chama recursivamenet a função encontrar_primeiro_temp para o filho da direita
    if(encontrou){ // Se encontrou for verdadeiro
        return true; // Retorna verdadeiro
    }

    // Pós-Ordem
    return esquerda || meio || direita; // Retorna verdadeiro se esquerda, meio ou direita for verdadeiro
}

// Função para encontrar primeiro por número
void encontrar_primeiro(treenodeptr raiz, int numero) {
    bool encontrou = false; // Variável para verificar se o Pokemon foi encontrado
    // Chama a função auxiliar para verificar a ordem que encontra primeiro por número
    if(encontrar_primeiro_temp(raiz, numero, encontrou)){
        cout << "O número " << numero << " foi encontrado primeiro na ordem: ";
        // Verifica a ordem que encontra primeiro por número
        if(raiz->numero_id == numero){
            cout << "Pré-Ordem";
        }else if(encontrou){
            cout << "Em Ordem";
        }else{
            cout << "Pós-Ordem";
        }
        cout << endl;
    }else{
        cout << "O Pokemon de numero " << numero << " nao foi encontrado na pokedex." << endl; // Imprime caso o Pokemon não seja encontrado
    }
}

int main(){
	// Árvores binárias
    treenodeptr arvore_nome = NULL;
	treenodeptr arvore_tipo = NULL;
	treenodeptr pesq;

    // Contadores dos tipos de Pokemons
	int cont_agua = 0;
	int cont_fogo = 0;
	int cont_normal = 0;

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
		cout << "8 - Determinar o percurso que encontra primeiro o Pokemon pelo numero." << endl;
		cout << "0 - Sair." << endl << endl;

		cin >> opcao; // Lê a opção do menu
		
        // Verifica a opção escolhida
		switch(opcao){
            // Opção para inserir um novo Pokemon
            case 1:
                cin >> num;
                cin >> nome;
                cin >> tipo;
                cin >> pokebola;
                // Verifica o tipo do Pokemon e o converte para int
				for(int i = 0; i < 3; i++){
					if(tipo.compare(vet_tipos[i]) == 0){
						num_tipo = i;
						break;
					}
					cout << "Tipo inválido! Foi adicionado o tipo normal." << endl;
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
				remove_pokebola(arvore_nome, rem_pokebola);
				remove_pokebola(arvore_tipo, rem_pokebola);
				cout << "Pokemons removidos com sucesso!";
				break;

            // Opção para imprimir os Pokemons por ordem alfabética dos nomes
			case 4:
				cout << "Pokemons por ordem alfabética dos nomes:" << endl;
				imprimir(arvore_nome);
				break;

            // Opção para imprimir os Pokemons por ordem alfabética dos tipos
			case 5:
				cout << "Pokemons por ordem alfabética dos tipos:" << endl;
				imprimir(arvore_tipo);
				break;

            // Opção para imprimir os Pokemons por pokebola
			case 6:
				cout << "Digite a pokebola a ser pesquisada: ";
				cin >> pesq_pokebola;
				cout << "Pokemons que utilizam a pokebola " << pesq_pokebola << ":";
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
				encontrar_primeiro(arvore_nome, pesq_numero);
				break;

            // Opção para sair do programa
			case 0:
				cout << endl << "Desligando Pokedex..." << endl;
				break;

            // Opção para caso a opção digitada seja inválida
            default:
                cout << "Opcao Invalida!" << endl;
                break;
        }
    }

    return 0; // Retorna 0
}