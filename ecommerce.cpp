#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct Data {
    int dia;
    int mes;
    int ano;
};

struct Produto {
    int codigo;
    char descricao[40];
    char categoria;
    int qtd_estoque;
    double preco;
    int desconto;
};

struct Carrinho {
    int codigo_c;
    int quantidade;
};


//operacoes simples
void trim(char str[]) {//limpa os espacos em branco no inicio e no fim

    int i, j;

    j = strlen(str)-1;
    while (j >= 0 && str[j] == ' ')
        str[j--] = 0;

    j = 0;
    while (str[j] != 0 && str[j] == ' ')
       j++;

    if (str[j] != 0) {
        i = 0;
        while (str[j] != 0)
            str[i++] = str[j++];
        str[i] = 0;
    }
}

void data_hora_atual(int &dia, int &mes, int &ano, int &hora, int &min, int &seg){
time_t t = time(NULL);
struct tm lt = *localtime(&t);
ano = lt.tm_year + 1900;
mes = lt.tm_mon + 1;
dia = lt.tm_mday;
hora = lt.tm_hour;
min = lt.tm_min;
seg = lt.tm_sec;
}

void exclui_item(Produto cadastros[], int i, int limite){//transfere o ultimo item do vetor para o local do item que deve ser excluido

    cadastros[i].codigo = cadastros[limite-1].codigo;
    strcpy(cadastros[i].descricao, cadastros[limite-1].descricao);
    cadastros[i].categoria = cadastros[limite-1].categoria;
    cadastros[i].qtd_estoque = cadastros[limite-1].qtd_estoque;
    cadastros[i].preco = cadastros[limite-1].preco;
    cadastros[i].desconto = cadastros[limite-1].desconto;
     
}

bool eh_codigo_repetido(Produto cadastros[], int cod, int limite){

    for(int i=0; i<limite; i++){
        if(cod == cadastros[i].codigo)
        return true;
    }

    return false;
}

void troca_vetor(Produto cadastros[], Produto &aux, int i){

             aux.codigo = cadastros[i+1].codigo;
             strcpy(aux.descricao, cadastros[i+1].descricao);
             aux.categoria = cadastros[i+1].categoria;
             aux.qtd_estoque = cadastros[i+1].qtd_estoque;
             aux.preco = cadastros[i+1].preco;
             aux.desconto = cadastros[i+1].desconto;

             cadastros[i+1].codigo = cadastros[i].codigo;
             strcpy(cadastros[i+1].descricao, cadastros[i].descricao);
             cadastros[i+1].categoria = cadastros[i].categoria;
             cadastros[i+1].qtd_estoque = cadastros[i].qtd_estoque;
             cadastros[i+1].preco = cadastros[i].preco;
             cadastros[i+1].desconto = cadastros[i].desconto;

             cadastros[i].codigo = aux.codigo;
             strcpy(cadastros[i].descricao, aux.descricao);
             cadastros[i].categoria = aux.categoria;
             cadastros[i].qtd_estoque = aux.qtd_estoque;
             cadastros[i].preco = aux.preco;
             cadastros[i].desconto = aux.desconto;

}

void ordena_por_categoria(Produto cadastros[], int limite){

    Produto aux;
    bool trocou = true;

    for(int k=limite-1; k>0 && trocou; k--){
        trocou = false;
        for(int i=0; i<k; i++){
            if(cadastros[i].categoria > cadastros[i+1].categoria ||
            cadastros[i].categoria == cadastros[i+1].categoria && 
            strcmpi(cadastros[i].descricao, cadastros[i+1].descricao) > 0){

                troca_vetor(cadastros, aux, i);
                trocou = true;
            }
        }
    }
}

void ordena_por_preco(Produto cadastros[], int limite){

    Produto aux;
    bool trocou = true;

    for(int k=limite-1; k>0 && trocou; k--){
        trocou = false;
        for(int i=0; i<k; i++){
            if(cadastros[i].preco > cadastros[i+1].preco){
             troca_vetor(cadastros, aux, i);
             trocou = true;
            }
        }
    }
}

//funcoes de interface
int excluir_item_carrinho(Produto cadastros[], Carrinho itens[], int limite_produtos, int &limite_carrinho){

    int cod;
    puts("-------------------------------");
    puts("Exclusao de Produto do Carrinho");
    puts("-------------------------------");

    printf("Codigo: ");
    scanf("%d", &cod);

    for(int i=0; i<limite_carrinho; i++){
        if(cod==itens[i].codigo_c)
        //terminar
    }

}

int incluir_item_carrinho(Produto cadastros[], Carrinho itens[], int limite_produtos, int &limite_carrinho){

    int codigo, quantidade;
    puts("-------------------------------");
    puts("Inclusao de Produto no Carrinho");
    puts("-------------------------------");
    printf("Codigo: ");
    scanf("%d", &codigo);

    for(int i=0; i < limite_produtos; i++){
        if(codigo == cadastros[i].codigo){
            if(limite_carrinho != 0){
                for(int j=0; j < limite_carrinho; j++){
                    if(codigo == itens[j].codigo_c){
                        puts("Esse item ja esta no carrinho.\n");
                        return -1; 
                    } 
                }
            }
            do{
                printf("Quantidade: ");
                scanf("%d", &quantidade);
                if(quantidade < 1)
                puts("Quantidade invalida.\n");  
            }while(quantidade < 1);

            if(quantidade > cadastros[i].qtd_estoque){
                puts("Estoque indisponivel.\n"); 
                return -1;
            } else {
                itens[limite_carrinho].codigo_c = codigo;
                itens[limite_carrinho].quantidade = quantidade;
                cadastros[i].qtd_estoque = cadastros[i].qtd_estoque - quantidade;
                limite_carrinho++;
                return -1;
            }
        }
    }

    puts("Produto nao esta cadastrado no sistema.\n");
    return -1;
}

int imprime_menu_carrinho(Produto cadastros[], Carrinho itens[], int limite_produtos, int &limite_carrinho){

    int opcao, volta;

    if(limite_carrinho == 0)
    puts("\nCarrinho vazio.\n");
    else //imprime itens no carrinho

    puts("================");
    puts("Menu do Carrinho");
    puts("================");
    printf("1-Incluir\n2-Excluir\n3-Aumentar\n4-Diminuir\n5-Esvaziar\n6-Comprar\n7-Voltar\n");
    do{
        printf("Opcao: ");
        scanf("%d", &opcao);
        if(opcao<1 || opcao>7)
        puts("Opcao invalida.\n");    
    }while(opcao<1 || opcao>7);

    if(opcao==1)
    volta = incluir_item_carrinho(cadastros, itens, limite_produtos, limite_carrinho);
    else if(opcao==2)
    volta = excluir_item_carrinho(cadastros, itens, limite_produtos, limite_carrinho);

    return -1;
}

int consulta_preco(Produto cadastros[], int qtd_produtos){

    if(qtd_produtos == 0){
        puts("Nao ha produtos cadastrados.");
        return -1;
    } else

    ordena_por_preco(cadastros, qtd_produtos);

    puts("----------------------------------------------------------------------");
    puts("Codigo  Descricao                      Categ.  Qtd     Preco  Desconto");
    puts("----------------------------------------------------------------------");

    for(int i=0; i<qtd_produtos; i++){
    printf(" %d   %s                   %c  %d      %f  %d\n", cadastros[i].codigo, cadastros[i].descricao,
     cadastros[i].categoria, cadastros[i].qtd_estoque, cadastros[i].preco, cadastros[i].desconto);
    }
    return -1; 
}

int consulta_categoria(Produto cadastros[], int qtd_produtos){

    if(qtd_produtos == 0){
        puts("Nao ha produtos cadastrados.\n");
        return -1;
    }

    ordena_por_categoria(cadastros, qtd_produtos);

    puts("----------------------------------------------------------------------");
    puts("Codigo  Descricao                      Categ.  Qtd     Preco  Desconto");
    puts("----------------------------------------------------------------------");

    for(int i=0; i<qtd_produtos; i++){
    printf(" %d   %s                   %c  %d      %f  %d\n", cadastros[i].codigo, cadastros[i].descricao,
     cadastros[i].categoria, cadastros[i].qtd_estoque, cadastros[i].preco, cadastros[i].desconto);
    }
    return -1;  
}

int altera_cadastro(Produto cadastros[], int limite){

    int cod, troca, desconto;
    double preco;
    
    puts("--------------------");
    puts("Alteracao de Produto");
    puts("--------------------");
    printf("Codigo: ");
    scanf("%d", &cod);

    for(int i=0; i<limite; i++){
        if(cod == cadastros[i].codigo){

            do{// le qtd de estoque
            printf("Quantidade em estoque (-1 não altera): ");
            scanf("%d", &troca);
            if( troca < -1 || troca > 9999)
            puts("Quantidade invalida. Insira um numero entre 0 e 9999.\n");
            }while( troca < -1 || troca > 9999);

            if(troca > -1)
            cadastros[i].qtd_estoque = troca;

            do{//le preco
            printf("Preco (-1 nao altera): ");
            scanf("%f", &preco);
            if(preco == -1)
            break;
            if(preco < 0.01 || preco > 9999999.99)
            printf("Valor invalido.\n");
            else 
                cadastros[i].preco = preco;
            }while(preco < 0.01 || preco > 9999999.99);

            do{//le desconto
            printf("Porcentagem de desconto (-1 nao altera): ");
            scanf("%d", &desconto);
            if(desconto == -1)
            break;
            if(desconto < 0 || desconto > 99)
            puts("Valor invalido.\n");
            else
                cadastros[i].desconto = desconto;
            }while(desconto < 0 || desconto > 99);
            
            puts("Mudancas salvas.\n");
            return -1;
        }
    }
    puts("Codigo nao encontrado nos registros. Nao foi possivel alterar.");
    return -1;
}

int exclui_cadastro(Produto cadastros[], Carrinho itens[], int &limite){

    int cod;

    puts("-------------------");
    puts("Exclusao de Produto");
    puts("-------------------");
    printf("Codigo: ");
    scanf("%d", &cod);

     //falta checar se o item existe no carrinho
    for(int i=0; i < limite; i++){
        if (cod == cadastros[i].codigo){
            if(i == limite-1){
                limite--;
                puts("Cadastro excluido com sucesso!");
                return -1;
            } else {
                exclui_item(cadastros, i, limite);
                limite--;
                puts("Cadastro excluido com sucesso!");
                return -1; 
            }          
        }
    }
    puts("Produto não consta nos cadastros.");
    return -1;
}

int cadastra_produto(Produto cadastros[], int &i){
    
    char c;
    int cod;
    bool codigo_repetido;

    puts("-------------------");
    puts("Inclusao de Produto");
    puts("-------------------");

    do{
        do{ //le o codigo
        printf("Codigo: ");
        scanf("%d", &cod);
        if(cod < 1 || cod > 999)
        puts("Codigo invalido. Digite um numero entre 1 e 999.\n");
        }while(cod < 1 || cod > 999);

        codigo_repetido = eh_codigo_repetido(cadastros, cod, i);

        if(codigo_repetido)
            puts("Este produto ja esta cadastrado\n");    
        else 
        cadastros[i].codigo = cod;    
    } while(codigo_repetido); 

    do{//le descricao
        getchar();
        printf("Descricao: ");
        gets(cadastros[i].descricao);
        trim(cadastros[i].descricao);
        if(strlen(cadastros[i].descricao) < 4 || strlen(cadastros[i].descricao) > 40)
        puts("Tamanho incompativel.\n");
    }while(strlen(cadastros[i].descricao) < 4 || strlen(cadastros[i].descricao) > 40);

    do{//le categoria
        getchar();
        printf("Categoria: ");
        c = getchar();

        if(c == 'A' || c =='a')
        cadastros[i].categoria = 'A';
        else if (c == 'B' || c =='b')
        cadastros[i].categoria = 'B';
        else if (c == 'C' || c =='c')
        cadastros[i].categoria = 'C';
        else if (c == 'D' || c =='d')
        cadastros[i].categoria = 'D';
        else if (c == 'E' || c =='e')
        cadastros[i].categoria = 'E';
        else
        puts("Categoria invalida.");

    }while(cadastros[i].categoria != 'A' && cadastros[i].categoria != 'B' 
        && cadastros[i].categoria != 'C' && cadastros[i].categoria != 'D' 
        && cadastros[i].categoria != 'E');

    do{// le qtd de estoque
        printf("Quantidade no estoque: ");
        scanf("%d", &cadastros[i].qtd_estoque);
        if(cadastros[i].qtd_estoque<0 || cadastros[i].qtd_estoque>9999)
        puts("Quantidade invalida.\n");
    }while(cadastros[i].qtd_estoque < 0 || cadastros[i].qtd_estoque > 9999);

    do{//le preco
        printf("Preco: ");
        scanf("%f", &cadastros[i].preco);
        if(cadastros[i].preco<0.01 || cadastros[i].preco > 9999999.99)
        printf("Valor invalido.\n");
    }while(cadastros[i].preco<0.01 || cadastros[i].preco > 9999999.99);

    do{//le desconto
        printf("Porcentagem de desconto: ");
        scanf("%d", &cadastros[i].desconto);
        if(cadastros[i].desconto < 0 || cadastros[i].desconto > 99)
        puts("Valor invalido.");
    }while(cadastros[i].desconto < 0 || cadastros[i].desconto > 99);

    i++;
    return -1;
}

int imprime_menu_produtos(Produto cadastros[], Carrinho itens[], int &qtd_produtos){

    int opcao, volta=0;

    do{
        puts("================");
        puts("Menu de Produtos");
        puts("================");    
        printf("1-Incluir\n2-Excluir\n3-Alterar\n4-Consultar por Categoria\n5-Consultar por preco\n6-Voltar\n");
        do{
        printf("Opcao: ");
        scanf("%d", &opcao);
        if(opcao < 1 || opcao > 6)
        puts("Opcao invalida.\n");
        }while(opcao < 1 || opcao > 6);

        if(opcao==1)
        volta = cadastra_produto(cadastros, qtd_produtos);
        else if(opcao==2)
        volta = exclui_cadastro(cadastros, itens, qtd_produtos);
        else if(opcao==3)
        volta = altera_cadastro(cadastros, qtd_produtos);
        else if(opcao==4)
        volta = consulta_categoria(cadastros, qtd_produtos);
        else if(opcao==5)
        volta = consulta_preco(cadastros, qtd_produtos);
        else
         return -1;    
    }while(volta = -1);
}

int imprime_menu_principal(Produto cadastros[], Carrinho itens[], int &contador_produtos, int &contador_carrinho){

    int opcao, volta=0;

    do{
        puts("=================================");
        puts("  E-Commerce - Menu Principal ");
        puts("=================================");
        printf("1-Produtos\n2-Carrinho\n3-Pedidos\n4-Fim\n");

        do{
            printf("Opcao: ");
            scanf("%d", &opcao);
            if(opcao !=1 && opcao !=2 && opcao !=3 && opcao !=4)
            puts("Opcao invalida.\n");    
        }while(opcao !=1 && opcao !=2 && opcao !=3 && opcao !=4);

        if(opcao==1)
        volta = imprime_menu_produtos(cadastros, itens, contador_produtos);
        else if(opcao==2)
        volta = imprime_menu_carrinho(cadastros, itens, contador_produtos, contador_carrinho);
        else if(opcao==3)
        // imprime_m();
        else
            return;
    }while(volta == -1);
}

int main(){

    Produto cadastros[50];
    Carrinho itens[50];
    int contador_produtos = 0, contador_carrinho = 0;


    imprime_menu_principal(cadastros, itens, contador_produtos, contador_carrinho);

}