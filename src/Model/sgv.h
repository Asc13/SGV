#ifndef SGV_H
#define SGV_H

#define OBJECTSIZE 7

typedef struct sgv* SGV;

SGV initSGV();
void destroySGV(SGV sgv);
SGV loadSGVFromFiles(SGV sgv, 
                     char* clientsFilePath,
                     char* productsFilePath,
                     char* salesFilePath
                    );

void getCurrentFileInfo(SGV sgv);
void getProductsStartedByLetter(SGV sgv, char letter);
void getProductSalesAndProfit(SGV sgv, char* productID, int month);
void getProductsNeverBought(SGV sgv, int branch);
void getClientsOfAllBranches(SGV sgv);
void getClientsAndProductsNeverBoughtCount(SGV sgv);
void getProductsBoughtByClient(SGV sgv, char* clientID);
void getSalesAndProfit(SGV sgv, int minMonth, int maxMonth);
void getProductsBuyers(SGV sgv, char* productID, int branch);
void getClientFavoriteProducts(SGV sgv, char* clientID, int month);
void getTopSelledProducts(SGV sgv, int limit);
void getClientTopProfitProducts(SGV sgv, char* clientID, int limit);

#endif