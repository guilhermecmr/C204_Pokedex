#include<iostream>
#include<list>
#include<string>

using namespace std;

struct treenode{
	int numero_id;
    string nome;
    string tipo;
    string pokebola;
	treenode *esq;
	treenode *dir;
};
typedef treenode *treenodeptr;

bool ehMaior(string s1, string s2) {
    for(int i = 0; i < s1.size() && i < s2.size(); i++){
        if(s1[i] > s2[i]){
            return 1;
        }else if(s1[i] < s2[i]){
            return 0;
        }
    }
    if(s1.size() >= s2.size()){
        return 1;
    }
    return 0;
}

void insert(treenodeptr &arvore, int num, string nome, string tipo, string pokebola){
	if(arvore == NULL){
		arvore = new treenode;
		arvore -> numero_id = num;
        arvore -> nome = nome;
        arvore -> tipo = tipo;
        arvore -> pokebola = pokebola;
		arvore -> esq = NULL;
		arvore -> dir = NULL;
	}else if(ehMaior(arvore -> nome, nome)){
		insert(arvore -> esq, num, nome, tipo, pokebola);
    }
	else{
		insert(arvore -> dir, num, nome, tipo, pokebola);
    }
}

treenodeptr search(treenodeptr pesq, string nome){
	if(pesq == NULL){
		return NULL;
    }else if(nome.compare(pesq -> nome) == 0){
		return pesq;
    }else if(ehMaior(pesq -> nome, nome)){
		return search(pesq -> esq, nome);
    }else{
		return search(pesq -> dir, nome);
    }
}

/*
treenodeptr menor(treenodeptr &raiz){
	treenodeptr t;
	t = raiz;
	if (t->esq == NULL){
		raiz = raiz->dir;
		return t;
	}else{
		return menor(raiz->esq);
    }
}

int remove(treenodeptr &arvore, int num){
	treenodeptr p;
	if (arvore == NULL){
		return 1;
    }
	if (num == arvore->numero_id){
		p = arvore;
		if(arvore->esq == NULL){
			arvore = arvore->dir;
        }else if(arvore->dir == NULL){
			arvore = arvore->esq;
        }else{
			p = menor(arvore->dir);
			arvore->numero_id = p->numero_id;
		}
		delete p;
		return 0;
	}else if(num < arvore->numero_id){
		return remove(arvore->esq, num);
    	}else{
		return remove(arvore->dir, num);
    }
}

void emNivel(treenodeptr t){
	treenodeptr n;
	list<treenodeptr> q;

	if(t != NULL){
		q.push_back(t);
		while(!q.empty()){
			n = *q.begin();
			q.pop_front();
			if(n->esq != NULL)
				q.push_back(n->esq);
			if(n->dir != NULL)
				q.push_back(n->dir);
			cout << n->numero_id << " ";
		}
	}
}
*/

int main(){
	treenodeptr arvore = NULL;
	treenodeptr pesq;
    int opcao = 0;
	int num = 0;
    string nome;
    string tipo;
    string pokebola;

	cin >> opcao;

    while(opcao != 0){
        switch(opcao){
            case 1:
                cin >> num;
                cin >> nome;
                cin >> tipo;
                cin >> pokebola;
                insert(arvore,num,nome,tipo,pokebola);
                break;
            
            case 2:
                cin >> nome;
                pesq = search(arvore, nome);
                if(pesq == NULL){
                    cout << "Pokemon nao encontrado!";
                }else{
                    cout << "Pokemon encontrado!";
                }
                break;

            default:
                cout << "Opcao Inválida";
                break;
        }
        cin >> opcao;
    }

    /*
	cout << "Em nivel\n";
	emNivel(arvore);

    remove(arvore,num);
	
	cout << "\nDepois do remove\n";
    emNivel(arvore);
    */

    return 0;
}