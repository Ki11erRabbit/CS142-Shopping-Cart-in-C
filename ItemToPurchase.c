//
// Created by ki11errabbit on 6/8/22.
//

#include "ItemToPurchase.h"



struct ItemToPurchase* ItemToPurchase_constructorDefault() {
    ItemToPurchase* newItem = NULL;
    newItem = malloc(sizeof(ItemToPurchase));
    newItem->private = malloc(sizeof(ItemToPurchasePrivate));

    newItem->private->name = NULL;
    newItem->private->description = NULL;

    newItem->copy = ItemToPurchase_copyConstructor;

    newItem->setDesc = ItemToPurchase_setDesc;
    newItem->getDesc = ItemToPurchase_getDesc;

    newItem->getQuantity = ItemToPurchase_getQuantity;
    newItem->getPrice = ItemToPurchase_getPrice;
    newItem->getName = ItemToPurchase_getName;

    newItem->printCost = ItemToPurchase_printCost;
    newItem->printDesc = ItemToPurchase_printDesc;

    return newItem;
}
struct ItemToPurchase* ItemToPurchase_constructor(char* name, char* desc, double price, int quantity) {
    ItemToPurchase* newItem = NULL;
    newItem = ItemToPurchase_constructorDefault();

    newItem->private->name = strdup(name);
    newItem->private->description = strdup(desc);
    newItem->private->price = price;
    newItem->private->quantity =quantity;

    return newItem;
}
ItemToPurchase* ItemToPurchase_copyConstructor(ItemToPurchase* this) {
    ItemToPurchase* newItem = NULL;
    newItem = ItemToPurchase_constructor(strdup(this->private->name), strdup(this->private->description),
                                         this->private->price, this->private->quantity);

    return newItem;
}
void ItemToPurchase_deconstructor(ItemToPurchase* this) {
    free(this->private->name);
    free(this->private->description);
    free(this->private);
    free(this);
}

int ItemToPurchase_getQuantity(ItemToPurchase* this) {
    return this->private->quantity;
}
double ItemToPurchase_getPrice(ItemToPurchase* this) {
    return this->private->price;
}
char* ItemToPurchase_getName(ItemToPurchase* this) {
    return strdup(this->getName(this));
}

void ItemToPurchase_setDesc(struct ItemToPurchase* this, const char* desc) {
    this->private->description = strdup(desc);
}
char* ItemToPurchase_getDesc(struct ItemToPurchase* this) {
    return strdup(this->private->description);
}
void ItemToPurchase_printCost(struct ItemToPurchase* this) {
    printf("%s %d @ $%.2f = %.2f",this->private->name, this->private->quantity, this->private->price,
           this->private->quantity * this->private->price);
}
void ItemToPurchase_printDesc(struct ItemToPurchase* this) {
    printf("%s: %s",this->private->name, this->private->description);
}