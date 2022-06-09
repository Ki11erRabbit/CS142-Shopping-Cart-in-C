//
// Created by ki11errabbit on 6/8/22.
//

#include "ItemToPurchase.h"



struct ItemToPurchase* ItemToPurchase_constructorDefault() {
    ItemToPurchase* newItem = NULL;
    newItem = malloc(sizeof(ItemToPurchase));
    newItem->private = malloc(sizeof(ItemToPurchasePrivate));

    newItem->setDesc = ItemToPurchase_setDesc;
    newItem->getDesc = ItemToPurchase_getDesc;
    newItem->printCost = ItemToPurchase_printCost;
    newItem->printDesc = ItemToPurchase_printDesc;

}
struct ItemToPurchase* ItemToPurchase_constructor(char* name, char* desc, double price, int quantity) {
    ItemToPurchase* newItem = NULL;
    newItem = ItemToPurchase_constructorDefault();

    newItem->private->name = strdup(name);
    newItem->private->description = strdup(desc);
    newItem->private->price = price;
    newItem->private->quantity =quantity;

}
void ItemToPurchase_deconstructor(ItemToPurchase* this) {
    free(this->private->name);
    free(this->private->description);
    free(this->private);
    free(this);
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