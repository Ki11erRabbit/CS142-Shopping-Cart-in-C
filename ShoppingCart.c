//
// Created by ki11errabbit on 6/8/22.
//

#include "ShoppingCart.h"

ShoppingCart* ShoppingCart_constructorDefault() {
    ShoppingCart* newCart = NULL;
    newCart = malloc(sizeof(ShoppingCart));
    newCart->private = NULL;
    newCart->private = malloc((sizeof(ShoppingCartPrivate)));
    newCart->private->customerName = strdup("none");
    newCart->private->date = strdup("January 1, 1970");
    newCart->private->itemArray = NULL;
    newCart->private->itemArraySize = 0;
    newCart->private->itemArrayMaxSize = 0;

    newCart->newBlank = ShoppingCart_constructorDefault;
    newCart->new = ShoppingCart_constructor;
    newCart->destroy = ShoppingCart_deconstructor;

    newCart->getName = ShoppingCart_getName;
    newCart->getDate = ShoppingCart_getDate;

    newCart->addItem = ShoppingCart_addItem;
    newCart->removeItem = ShoppingCart_removeItem;
    newCart->updateQuantity = ShoppingCart_updateQuantity;

    newCart->getQuantity = ShoppingCart_getQuantity;
    newCart->getCost = ShoppingCart_getTotalCost;

    newCart->printDesc = ShoppingCart_printDesc;
    newCart->printCost = ShoppingCart_printCost;

    return newCart;
}
ShoppingCart* ShoppingCart_constructor(char* name, char* date) {
    ShoppingCart* newCart = NULL;
    newCart = ShoppingCart_constructorDefault();

    newCart->private->customerName = strdup(name);
    newCart->private->date = strdup(date);


    return newCart;
}
void ShoppingCart_deconstructor(ShoppingCart* self) {
    free(self->private->customerName);
    free(self->private->date);

    for (size_t i = 0; i < self->private->itemArraySize; i++) {
        ItemToPurchase_deconstructor(&self->private->itemArray[i]);
    }
    free(self->private->itemArray);
    free(self->private);
    free(self);
    self = NULL;
}

char* ShoppingCart_getName(ShoppingCart* self) {
    return strdup(self->private->customerName);
}
char* ShoppingCart_getDate(ShoppingCart* self) {
    return strdup(self->private->date);
}

void ShoppingCart_addItem(ShoppingCart* self, ItemToPurchase* item);
void ShoppingCart_removeItem(ShoppingCart* self, char* itemName);
void ShoppingCart_updateQuantity(ShoppingCart* self, char* itemName);

int ShoppingCart_getQuantity(ShoppingCart* self);
double ShoppingCart_getTotalCost(ShoppingCart* self);

void ShoppingCart_printDesc(ShoppingCart* self);
void ShoppingCart_printCost(ShoppingCart* self);