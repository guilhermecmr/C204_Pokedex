#include<iostream>
#include<string>

using namespace std;

string vet_tipos[] = {"Agua", "Fogo", "Normal"};

struct treenode{
	int numero_id;
    string nome;
    int tipo;
    string pokebola;
	treenode *esq;
	treenode *dir;
};
typedef treenode *treenodeptr;

bool nome_maior(string s1, string s2) {
    if(s1.size() >= s2.size()){
        return 1;
    }
	for(int i = 0; i < s1.size() && i < s2.size(); i++){
        if(s1[i] > s2[i]){
            return 1;
        }else if(s1[i] < s2[i]){
            return 0;
        }
    }
    return 0;
}

void insert_nome(treenodeptr &arvore, int num, string nome, int tipo, string pokebola){
	if(arvore == NULL){
		arvore = new treenode;
		arvore -> numero_id = num;
        arvore -> nome = nome;
        arvore -> tipo = tipo;
        arvore -> pokebola = pokebola;
		arvore -> esq = NULL;
		arvore -> dir = NULL;
	}else if(nome_maior(arvore -> nome, nome)){
		insert_nome(arvore -> esq, num, nome, tipo, pokebola);
    }
	else{
		insert_nome(arvore -> dir, num, nome, tipo, pokebola);
    }
}

void insert_tipo(treenodeptr &arvore, int num, string nome, int tipo, string pokebola){
	if(arvore == NULL){
		arvore = new treenode;
		arvore -> numero_id = num;
        arvore -> nome = nome;
        arvore -> tipo = tipo;
        arvore -> pokebola = pokebola;
		arvore -> esq = NULL;
		arvore -> dir = NULL;
	}else if(tipo < arvore -> tipo){
		insert_tipo(arvore -> esq, num, nome, tipo, pokebola);
    }
	else{
		insert_tipo(arvore -> dir, num, nome, tipo, pokebola);
    }
}

treenodeptr search_nome(treenodeptr pesq, string nome){
	if(pesq == NULL){
		return NULL;
    }else if(nome.compare(pesq -> nome) == 0){
		return pesq;
    }else if(nome_maior(pesq -> nome, nome)){
		return search_nome(pesq -> esq, nome);
    }else{
		return search_nome(pesq -> dir, nome);
    }
}

void imprimir(treenodeptr arvore) {
    if (arvore != NULL) {
        imprimir(arvore->esq);
        cout << endl << "Numero: " << arvore->numero_id << endl << "Nome: " << arvore->nome << endl << "Tipo: " 
			<< vet_tipos[arvore->tipo] << endl << "Pokebola: " << arvore->pokebola << endl;
        imprimir(arvore->dir);
    }
}

void imprimir_pokebola(treenodeptr arvore, string pokebola) {
    if (arvore != NULL) {
        imprimir_pokebola(arvore->esq, pokebola);
        if(arvore->pokebola.compare(pokebola) == 0)
			cout << endl << "Numero: " << arvore->numero_id << endl << "Nome: " << arvore->nome << endl << "Tipo: " 
				<< vet_tipos[arvore->tipo] << endl << "Pokebola: " << arvore->pokebola << endl;
        imprimir_pokebola(arvore->dir, pokebola);
    }
}

treenodeptr remove_pokebola(treenodeptr raiz, string pokebola) {
    if (raiz == NULL) {
        return raiz;
    }

    if (pokebola < raiz->pokebola) {
        raiz->esq = remove_pokebola(raiz->esq, pokebola);
    } else if (pokebola > raiz->pokebola) {
        raiz->dir = remove_pokebola(raiz->dir, pokebola);
    } else {
        
        if (raiz->esq == NULL) {
            treenodeptr temp = raiz->dir;
            delete raiz;
            return temp;
        } else if (raiz->dir == NULL) {
            treenodeptr temp = raiz->esq;
            delete raiz;
            return temp;
        }

        treenodeptr aux;
        while (aux -> esq != NULL) {
                aux = aux -> esq;
            }
        treenodeptr temp = aux;

        raiz->numero_id = temp->numero_id;
        raiz->nome = temp->nome;
        raiz->tipo = temp->tipo;
        raiz->pokebola = temp->pokebola;

        raiz->dir = remove_pokebola(raiz->dir, temp->pokebola);
    }
    return raiz;
}

// Função auxiliar para encontrar primeiro por número
bool encontrar_primeiro_aux(treenodeptr raiz, int numero, bool &encontrou) {
    if (raiz == NULL) {
        return false;
    }

    // Pré-Ordem
    if (raiz->numero_id == numero) {
        encontrou = true;
        return true;
    }
    bool esquerda = encontrar_primeiro_aux(raiz->esq, numero, encontrou);
    if (encontrou) {
        return true;
    }

    // Em Ordem
    bool meio = (raiz->numero_id == numero);
    if (meio) {
        encontrou = true;
        return true;
    }

    bool direita = encontrar_primeiro_aux(raiz->dir, numero, encontrou);
    if (encontrou) {
        return true;
    }

    // Pós-Ordem
    return esquerda || meio || direita;
}

// Função para encontrar primeiro por número
void encontrar_primeiro(treenodeptr raiz, int numero) {
    bool encontrou = false;
    if (encontrar_primeiro_aux(raiz, numero, encontrou)) {
        cout << "O número " << numero << " foi encontrado primeiro na ordem: ";
        if (raiz->numero_id == numero) {
            cout << "Pré-Ordem";
        } else if (encontrou) {
            cout << "Em Ordem";
        } else {
            cout << "Pós-Ordem";
        }
        cout << endl;
    } else {
        cout << "O Pokemon de numero " << numero << " nao foi encontrado na pokedex." << endl;
    }
}

int main(){
	treenodeptr arvore_nome = NULL;
	treenodeptr arvore_tipo = NULL;
	treenodeptr pesq;

    int opcao = -1;

	int count_agua = 0;
	int count_fogo = 0;
	int count_normal = 0;

	string pesq_pokebola;
	string rem_pokebola;
	int pesq_numero;

	int num = 0;
    string nome;
    string tipo;
	int num_tipo;
    string pokebola;

    while(opcao != 0){
        
		cout << endl << "Menu:" << endl; //V
		cout << "1 - Inserir Pokemon." << endl; //V
		cout << "2 - Pesquisar Pokemon." << endl; //V
		cout << "3 - Remover Pokemon pela sua pokebola." << endl; //V
		cout << "4 - Imprimir informacoes dos Pokemons cadastrados em ordem alfabetica dos nomes." << endl; //V
		cout << "5 - Imprimir informacoes dos Pokemons cadastrados em ordem alfabetica dos tipos." << endl; //V
		cout << "6 - Imprimir informacoes dos Pokemons cadastrados de uma dada pokebola." << endl; //V
		cout << "7 - Imprimir informacoes sobre a quantidade de Pokemons de cada tipo." << endl; //V
		cout << "8 - Determinar o percurso que encontra primeiro o Pokemon pelo numero." << endl; //P
		cout << "0 - Sair." << endl << endl; //V

		cin >> opcao;
		
		switch(opcao){
            case 1:
                cin >> num;
                cin >> nome;
                cin >> tipo;
                cin >> pokebola;
				for(int i = 0; i < 3; i++){
					if(tipo.compare(vet_tipos[i]) == 0){
						num_tipo = i;
						break;
					}
					cout << "Tipo inválido! Foi adicionado o tipo normal." << endl;
					num_tipo = 2;
				}
				if(num_tipo == 0)
					count_agua++;
				else if(num_tipo == 1)
					count_fogo++;
				else if(num_tipo == 2)
					count_normal++;
                insert_nome(arvore_nome,num,nome,num_tipo,pokebola);
				insert_tipo(arvore_tipo,num,nome,num_tipo,pokebola);
                break;
            
            case 2:
                cin >> nome;
                pesq = search_nome(arvore_nome, nome);
                if(pesq == NULL){
                    cout << "Pokemon nao encontrado!" << endl;
                }else{
                    cout << "Pokemon encontrado!" << endl;
                }
                break;

			case 3:
				cout << "Digite a pokebola dos Pokemons a seres apagados: ";
				cin >> rem_pokebola;
				remove_pokebola(arvore_nome, rem_pokebola);
				remove_pokebola(arvore_tipo, rem_pokebola);
				cout << "Pokemons removidos com sucesso!";
				break;

			case 4:
				cout << "Pokemons por ordem alfabética dos nomes:" << endl;
				imprimir(arvore_nome);
				break;

			case 5:
				cout << "Pokemons por ordem alfabética dos tipos:" << endl;
				imprimir(arvore_tipo);
				break;

			case 6:
				cout << "Digite a pokebola a ser pesquisada: ";
				cin >> pesq_pokebola;
				cout << "Pokemons que utilizam a pokebola " << pesq_pokebola << ":";
				imprimir_pokebola(arvore_nome, pesq_pokebola);
				break;

			case 7:
				cout << "Quantidade de Pokemons por tipos:" << endl << "Agua: " << count_agua << endl << 
				"Fogo: "<< count_fogo << endl << "Normal: " << count_normal << endl;
				break;

			case 8:
				cout << "Digite o numero a ser pesquisado: ";
				cin >> pesq_numero;
				encontrar_primeiro(arvore_nome, pesq_numero);
				break;

			case 0:
				cout << endl << "Desligando Pokedex..." << endl;
				break;

            default:
                cout << "Opcao Invalida!" << endl;
                break;
        }
    }

    return 0;
}