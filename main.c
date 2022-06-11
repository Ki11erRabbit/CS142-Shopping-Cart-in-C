//
// Created by ki11errabbit on 6/8/22.
//
#include "ShoppingCart.h"


void printHelp() {
    printf("add - Add item to cart\nremove - Remove item from cart\nchange - Change item quantity\n");
    printf("descriptions - Print the items' descriptions\ncart - Print the shopping cart\n");
    printf("options - Print the options menu\nquit - Quit\n\n");
}


int main() {

    ShoppingCart* cart = NULL;

    char* buff = NULL;
    char* name = NULL;
    char* date = NULL;
    size_t buffSize = 0;
    int cont = 1;

    printf("Enter Customer's Name: ");
    getline(&name,&buffSize,stdin);
    name = strtok(name,"\n");
    printf("Enter Today's Date: ");
    getline(&date,&buffSize,stdin);
    date = strtok(date,"\n");

    cart = ShoppingCart_constructor(name,date);
    /*free(name);
    free(date);
    name = NULL;
    date = NULL;*/
    printHelp();
    while (cont) {
        printf("Enter option: ");
        getline(&buff,&buffSize,stdin);

        if(strcmp(buff,"add\n") == 0) {
            char* itemName = NULL;
            char* itemDesc = NULL;
            char* itemPrice = NULL;
            char* itemQuantity = NULL;

            printf("Enter the item name: ");
            getline(&itemName,&buffSize, stdin);
            itemName = strtok(itemName,"\n");

            printf("Enter the item description: ");
            getline(&itemDesc,&buffSize,stdin);
            itemDesc = strtok(itemDesc,"\n");

            printf("Enter the item price: ");
            getline(&itemPrice,&buffSize,stdin);
            itemPrice = strtok(itemPrice,"\n");

            printf("Enter the item quantity: ");
            getline(&itemQuantity,&buffSize,stdin);
            itemQuantity = strtok(itemQuantity,"\n");

            char* endpoint = NULL;
            ItemToPurchase* newItem = NULL;
            newItem = ItemToPurchase_constructor(strdup(itemName), strdup(itemDesc),
                          strtod(itemPrice,&endpoint),atoi(itemQuantity));

            cart->addItem(cart, newItem);

            free(itemName);
            free(itemDesc);
            free(itemPrice);
            //free(endpoint);
            free(itemQuantity);
        }
        else if (strcmp(buff,"remove\n") == 0) {
            printf("Enter name of the item to remove: ");
            char* itemName = NULL;
            getline(&itemName, &buffSize,stdin);
            cart->removeItem(cart,strtok(itemName,"\n"));
            free(itemName);
        }
        else if (strcmp(buff,"change\n") == 0) {
            printf("Enter the item name: ");
            char* itemName = NULL;
            char* itemQuantity = NULL;
            getline(&itemName, &buffSize,stdin);
            printf("Enter the new quantity: ");
            getline(&itemQuantity, &buffSize, stdin);
            cart->updateQuantity(cart,strtok(itemName, "\n"),atoi(strtok(itemQuantity, "\n")));
            free(itemName);
            free(itemQuantity);
        }
        else if (strcmp(buff,"descriptions\n") == 0) {
            cart->printDesc(cart);
        }
        else if (strcmp(buff,"cart\n") == 0) {
            cart->printCost(cart);
        }
        else if (strcmp(buff,"options\n") == 0) {
            printHelp();
        }
        else if (strcmp(buff,"quit\n") == 0) {
            cont = 0;
        }
        else {
            printHelp();
        }

    }
    cart->destroy(cart);
    free(buff);


    return 0;
}