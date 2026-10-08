#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

MYSQL *conn;

void Delete_Dado(int id);
void Insert_Dado();
void Update_Dado(int id);
void Select_Dado();

int main() {
    conn = mysql_init(NULL);

    if (conn == NULL) {
        printf("Erro ao inicializar a biblioteca MySQL\n");
        return 1;
    }

    // 1. Conexão com o banco de dados
    //        Parâmetros: conexão, host,     usuário,     senha,   nome_do_banco, porta, socket, flags
    if (mysql_real_connect(conn, "localhost", "root", "12345", "misterio_rpg", 3306, NULL, 0) == NULL) {
        printf("Erro de Conexão: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    //Delete_Dado(1);
    Select_Dado("SELECT * FROM aventureiros");
    //Update_Dado(1);
    //Insert_Dado();


    // Encerrar conexão
    mysql_close(conn);
    return 0;
}

void Delete_Dado(int id)
{

    printf("\n--- EXECUTANDO DELETE ---\n");
    if (mysql_query(conn, "DELETE FROM diario_pessoal WHERE aventureiro_id = 2")) {
        printf("Erro no DELETE: %s\n", mysql_error(conn));
    } else {
        printf("Linhas afetadas no DELETE: %llu\n", mysql_affected_rows(conn));
    }
}

void Insert_Dado()
{
    printf("--- EXECUTANDO INSERT ---\n");
    if (mysql_query(conn, "INSERT INTO aventureiros (id,nome, classe) VALUES (102,'Lucas Silva', 'Mago')")) {
        printf("Erro no INSERT: %s\n", mysql_error(conn));
    } else {
        printf("Registro inserido com sucesso!\n");
        printf("ID gerado (AUTO_INCREMENT): %llu\n", mysql_insert_id(conn));
    }
}
void Update_Dado(int id)
{
    printf("\n--- EXECUTANDO UPDATE ---\n");
    if (mysql_query(conn, "UPDATE aventureiros SET classe = 'Goblin' WHERE id = 1")) {
        printf("Erro no UPDATE: %s\n", mysql_error(conn));
    } else {
        printf("Linhas afetadas no UPDATE: %llu\n", mysql_affected_rows(conn));
    }
}
void Select_Dado(char comando[])
{
    printf("\n--- EXECUTANDO SELECT ---\n");
    if(conn == NULL)
    {
         printf("\n--- ERRO CONN ---\n");
    }
    if (mysql_query(conn, comando)) {
        printf("Erro no SELECT: %s\n", mysql_error(conn));
    } else {
        MYSQL_RES *res = mysql_use_result(conn);
        MYSQL_ROW row;

        while ((row = mysql_fetch_row(res)) != NULL) {
            printf("ID: %s | Nome: %s \n", row[0], row[1]);
        }
        mysql_free_result(res); // Libera a memória alocada para o resultado
    }
}
