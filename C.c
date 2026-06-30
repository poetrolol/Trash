#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

//-----------------------------------------------------------------------------|
//                            Function Code                                    |
//-----------------------------------------------------------------------------|
int main() {
    int Op = 0;
    char Cod[PATH_MAX];
    char *CodL = NULL;
    char mkdir_cmd[PATH_MAX]; 
    char *editor = NULL;
    char Open[PATH_MAX];

    printf("=====================YOU LIST COD=====================\n");
    system("ls -R MyCodES 2>/dev/null");   
    printf("=====================END LIST COD=====================\n");
    
    printf("1.-> [Criar Arquivo de Codigo] 2.-> [Abrir um arquivo]: ");
    scanf("%1i", &Op);
    system("mkdir -p MyCodES");

    switch (Op) {
        case 1:
            printf("Digite o nome do seu Arquivo de codigo (Ex: programa.c): ");
            scanf("%4095s", Cod);
            CodL = strrchr(Cod, '.');

            if (CodL != NULL) {
                char *ext_pura = CodL + 1;
                char comando[PATH_MAX];
                snprintf(mkdir_cmd, sizeof(mkdir_cmd), "mkdir -p MyCodES/%s", ext_pura);
                system(mkdir_cmd);
                snprintf(mkdir_cmd, sizeof(mkdir_cmd), "MyCodES/%s/%s", ext_pura, Cod);
                FILE *Create = fopen(mkdir_cmd, "w");
                snprintf(mkdir_cmd, sizeof(mkdir_cmd), "mkdir -p MyCodES/%s/TimeLine", ext_pura);
                system(mkdir_cmd);
                char destino[PATH_MAX];
                snprintf(destino, sizeof(destino), "MyCodES/%s/TimeLine/%s_backup", ext_pura, Cod);
                snprintf(comando, sizeof(comando), "cp MyCodES/%s/%s %s", ext_pura, Cod, destino);
                system(comando);   
                printf("Backup salvo em: %s\n", destino);
                if (Create != NULL) {
                    fclose(Create);
                    printf("Sucesso! Arquivo criado em: %s\n", mkdir_cmd);
                    
                    editor = getenv("VISUAL");
                    if (editor == NULL) {
                        char *lista_editores[] = {"code", "code-oss", "nvim", "vim", "nano"};
                        int total = 5;
                        char teste_cmd[PATH_MAX];

                        for (int i = 0; i < total; i++) {
                            snprintf(teste_cmd, sizeof(teste_cmd), "which %s > /dev/null 2>&1", lista_editores[i]);
                            if (system(teste_cmd) == 0) { 
                                editor = lista_editores[i]; 
                                break; 
                            }
                        }
                        if (editor == NULL) editor = "vi";
                    }
                    
                    snprintf(mkdir_cmd, sizeof(mkdir_cmd), "%s MyCodES/%s/%s", editor, ext_pura, Cod);
                    system(mkdir_cmd);
                }
            } else {
                printf("Erro: Arquivo sem extensão válida.\n");
            }
            break;

        case 2:
            printf("Digite o nome do arquivo que deseja abrir dentro de MyCodES (Ex: teste.c): ");
            scanf("%4095s", Open);
            CodL = strrchr(Open, '.');
            if (CodL == NULL) { printf("Erro: Sem extensão.\n"); break; }
            
            char *ext = CodL + 1;
            char dir_backup[PATH_MAX];
            char origem[PATH_MAX];
            char destino_final[PATH_MAX];
            char comando[PATH_MAX];

            snprintf(origem, sizeof(origem), "MyCodES/%s/%s", ext, Open);
            snprintf(dir_backup, sizeof(dir_backup), "MyCodES/%s/TimeLine", ext);
            
            // CORREÇÃO: snprintf antes do system
            snprintf(mkdir_cmd, sizeof(mkdir_cmd), "mkdir -p %s", dir_backup);
            system(mkdir_cmd);
            
            int i = 1;
            snprintf(destino_final, sizeof(destino_final), "%s/%s_backup", dir_backup, Open);
            snprintf(comando, sizeof(comando), "cp \"%s\" \"%s\"", origem, destino_final);
            system(comando);
            
            editor = getenv("VISUAL");
            if (editor == NULL) {
                char *lista_editores[] = {"code", "code-oss", "nvim", "vim", "nano"};
                char teste_cmd[PATH_MAX];
                for (int j = 0; j < 5; j++) {
                    snprintf(teste_cmd, sizeof(teste_cmd), "which %s > /dev/null 2>&1", lista_editores[j]);
                    if (system(teste_cmd) == 0) {
                        editor = lista_editores[j];
                        break;
                    }
                }
                if (editor == NULL) editor = "vi";
            }
            // CORREÇÃO: número correto de argumentos
            snprintf(mkdir_cmd, sizeof(mkdir_cmd), "%s \"MyCodES/%s/%s\"", editor, ext, Open);
            system(mkdir_cmd);
            break;
    }
    return 0;
};