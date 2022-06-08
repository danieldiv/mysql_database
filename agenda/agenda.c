#include<stdio.h>
#include<stdlib.h>
#include<mysql/mysql.h>

int main(int argc, char** argv){
    printf("%s\n",mysql_get_client_info());
    MYSQL* conexao = mysql_init(NULL);
    if (conexao == NULL) {
        printf("Não foi possível carregar o cliente MySQL\n");
        return EXIT_FAILURE;
    }
    if (mysql_real_connect(conexao, "127.0.0.1", "admin", "Grid89878987", "agenda", 0, NULL, 0) == NULL){
        printf("Não foi possível conectar ao SGBD\n");
        return EXIT_FAILURE;
    }
    int opcao;
    do{
        printf("[1] Novo contato\n");
        printf("[2] Listar contatos\n");
        printf("[0] Sair\n\n");
        printf(">>> ");
        scanf("%d", &opcao);
        if(opcao == 1){
            printf("Nome: ");
            char nome[65];
            scanf(" %[^\n]", nome);
            printf("Telefone: ");
            char telefone[65];
            scanf(" %[^\n]", telefone);
            printf("E-mail: ");
            char email[65];
            scanf(" %[^\n]", email);

            char query[1024];
            sprintf(query, "INSERT INTO contatos (nome, telefone, email) VALUES ('%s', '%s', '%s')",
            nome, telefone, email);
            if(mysql_query(conexao, query) != 0){
                printf("Oops... não conseguir cadastrar seu contato.\n");
            }
        }else if(opcao==2){
            mysql_query(conexao, "SELECT * FROM contatos");
            MYSQL_RES* resultado = mysql_store_result(conexao);
            int n_col = mysql_num_fields(resultado);
            MYSQL_ROW linha;
            while (linha = mysql_fetch_row(resultado)){
                printf("(%s)-(%s)-(%s)-(%s)\n",linha[0],linha[1],linha[2],linha[3]);
            }
        }else if(opcao==0){
            printf("Até logo!\n\n");
        }else {
            printf("opção escolhida não é válida...\n");
        }
    } while (opcao != 0);
    mysql_close(conexao);
    return 0;
}