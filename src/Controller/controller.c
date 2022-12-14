#include "controller.h"
#include <stdio.h>
#include <unistd.h>

static void clear() {
    show("\e[1;1H\e[2J\n");
}

static void showMenu() {
    char buffer[1024];
        snprintf(buffer, sizeof(buffer),
                "\t\t\tMENU\t\t\t\n\n"
                "0.  Load Files\n"
                "1.  Query 1\n"
                "2.  Query 2\n"
                "3.  Query 3\n"
                "4.  Query 4\n"
                "5.  Query 5\n"
                "6.  Query 6\n"
                "7.  Query 7\n"
                "8.  Query 8\n"
                "9.  Query 9\n"
                "10. Query 10\n"
                "11. Query 11\n"
                "12. Query 12\n"
                "13. Destroy\n"
                "14. Exit\n");

        show(buffer);
}

void checkFiles(char* path, char* clientsFilePath, char* productsFilePath, char* salesFilePath) {
    int files = 0;

    do {
        show("\nProducts filename: ");
        scanf("%s", productsFilePath);
        show("\nClients filename: ");
        scanf("%s", clientsFilePath);
        show("\nSales filename: ");
        scanf("%s", salesFilePath);


        files = access(strcat(path, productsFilePath), F_OK) && 
                access(strcat(path, clientsFilePath), F_OK) &&
                access(strcat(path, salesFilePath), F_OK);

        files ? show("\nCorrect Files!!\n") : show("\nFiles don't exist!!\n");

    } while(!files);
}



void controller() {
    int input = -1;

    SGV sgv = initSGV();

    do {
        showMenu();
        show("Option: ");
        scanf("%d", &input);

        switch(input) {
            case 0:
                char clientsFilePath[128] = "Files/Clientes.txt",
                     productsFilePath[128] = "Files/Produtos.txt", 
                     salesFilePath[128] = "Files/Vendas_1M.txt";
                
                //char path[20] = "../../Files/";
                //checkFiles(path, clientsFilePath, productsFilePath, salesFilePath);
                loadSGVFromFiles(sgv, clientsFilePath, productsFilePath, salesFilePath);
                getCurrentFileInfo(sgv);
                break;
            
            case 1:
                char letter;
                show("\nLetter: ");
                scanf(" %c", &letter);

                getProductsStartedByLetter(sgv, letter);
                break;
            
            case 2:
                break;
            
            case 3:
                char mode[10];
                int branch = 0;

                show("\nMode (Total or Branch): ");
                scanf(" %s", &mode);

                if(strcmp(mode, "Branch") == 0) {
                    show("\nBranch (1-3): ");
                    scanf("%d", &branch);
                }
                
                getProductsNeverBought(sgv, branch);

                break;
            
            case 4:
                getClientsOfAllBranches(sgv);
                break;
            
            case 5:
                getClientsAndProductsNeverBoughtCount(sgv);
                break;
            
            case 6:
                char client[10];

                show("\nClient: ");
                scanf(" %s", &client);

                getProductsBoughtByClient(sgv, client);
                break;
            
            case 7:
                int minMonth, maxMonth;

                show("\nMinimum month: ");
                scanf("%d", &minMonth);

                show("\nMaximum month: ");
                scanf("%d", &maxMonth);

                getSalesAndProfit(sgv, minMonth, maxMonth);
                break;
            
            case 8:
                break;
            
            case 9:
                break;
            
            case 10:
                break;
            
            case 11:
                break;
            
            case 12:
                break;
            
            case 13:
                destroySGV(sgv);
                break;
            
            case 14:
                show("\n\n\t\t... CLOSING SGV ...\n\n");
                break;
            
            default:
                show("\nWrong option\n"); 
                break;
            }
    } while(input != 14);
}