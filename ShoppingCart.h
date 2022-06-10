//
// Created by ki11errabbit on 6/8/22.
//

#ifndef CS142_SHOPPING_CART_IN_C_SHOPPINGCART_H
#define CS142_SHOPPING_CART_IN_C_SHOPPINGCART_H

#include "ItemToPurchase.h"

typedef struct ShoppingCartPrivate {
    char* customerName;
    char* date;
    ItemToPurchase* itemArray;
    size_t itemArraySize;
    size_t itemArrayMaxSize;

} ShoppingCartPrivate;

typedef struct ShoppingCart {
    struct ShoppingCartPrivate* private;

    struct ShoppingCart* (*new)(char*, char*);
    struct ShoppingCart* (*newBlank)(char*, char*);
    void (*destroy)(struct ShoppingCart*);

    char* (*getName)(struct ShoppingCart*);
    char* (*getDate)(struct ShoppingCart*);

    void (*addItem)(struct ShoppingCart*, ItemToPurchase*);
    void (*removeItem)(struct ShoppingCart*, char*);
    void (*updateQuantity)(struct ShoppingCart*, char*, int);

    int (*getQuantity)(struct ShoppingCart*);
    double (*getCost)(struct ShoppingCart*);

    void (*printDesc)(struct ShoppingCart*);
    void (*printCost)(struct ShoppingCart*);

} ShoppingCart;

//Public functions:
ShoppingCart* ShoppingCart_constructorDefault();
ShoppingCart* ShoppingCart_constructor(char* name, char* date);
void ShoppingCart_deconstructor(ShoppingCart* self);

char* ShoppingCart_getName(ShoppingCart* self);
char* ShoppingCart_getDate(ShoppingCart* self);

void ShoppingCart_addItem(ShoppingCart* self, ItemToPurchase* item);
void ShoppingCart_removeItem(ShoppingCart* self, char* itemName);
void ShoppingCart_updateQuantity(ShoppingCart* self, char* itemName, int quantity);

int ShoppingCart_getQuantity(ShoppingCart* self);
double ShoppingCart_getTotalCost(ShoppingCart* self);

void ShoppingCart_printDesc(ShoppingCart* self);
void ShoppingCart_printCost(ShoppingCart* self);

//Private Functions:
size_t ShoppingCart_find(ShoppingCart* self, char* itemName);


#endif //CS142_SHOPPING_CART_IN_C_SHOPPINGCART_H
