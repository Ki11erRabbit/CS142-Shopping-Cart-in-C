//
// Created by ki11errabbit on 6/8/22.
//

#ifndef CS142_SHOPPING_CART_IN_C_ITEMTOPURCHASE_H
#define CS142_SHOPPING_CART_IN_C_ITEMTOPURCHASE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct ItemToPurchasePrivate {
    char* name;
    char* description;
    double price;
    int quantity;
} ItemToPurchasePrivate;

typedef struct ItemToPurchase {
    struct ItemToPurchasePrivate* private;

    struct ItemToPurchase* (*copy)(struct ItemToPurchase*);
    void (*setDesc)(struct ItemToPurchase*, const char*);
    char* (*getDesc)(struct ItemToPurchase*);

    int (*getQuantity)(struct ItemToPurchase*);
    double (*getPrice)(struct ItemToPurchase*);
    char* (*getName)(struct ItemToPurchase*);

    void (*printCost)(struct ItemToPurchase*);
    void (*printDesc)(struct ItemToPurchase*);

} ItemToPurchase;

struct ItemToPurchase* ItemToPurchase_constructorDefault();
struct ItemToPurchase* ItemToPurchase_constructor(char* name, char* desc, double price, int quantity);
ItemToPurchase* ItemToPurchase_copyConstructor(ItemToPurchase* self);
void ItemToPurchase_deconstructor(ItemToPurchase* self);

int ItemToPurchase_getQuantity(ItemToPurchase* self);
double ItemToPurchase_getPrice(ItemToPurchase* self);
char* ItemToPurchase_getName(ItemToPurchase* self);

void ItemToPurchase_setDesc(struct ItemToPurchase* self, const char* desc);
char* ItemToPurchase_getDesc(struct ItemToPurchase* self);
void ItemToPurchase_printCost(struct ItemToPurchase* self);
void ItemToPurchase_printDesc(struct ItemToPurchase* self);

#endif //CS142_SHOPPING_CART_IN_C_ITEMTOPURCHASE_H
