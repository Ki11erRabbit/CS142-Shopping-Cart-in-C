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
    newCart->private->itemArray = malloc(sizeof(ItemToPurchase));
    newCart->private->itemArraySize = 0;
    newCart->private->itemArrayMaxSize = 1;

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

    newCart->private->customerName = name;
    newCart->private->date = date;


    return newCart;
}
void ShoppingCart_deconstructor(ShoppingCart* this) {
    free(this->private->customerName);
    free(this->private->date);

    for (size_t i = 0; i < this->private->itemArraySize; i++) {
        ItemToPurchase_deconstructor(&this->private->itemArray[i]);
    }
    free(this->private->itemArray);
    free(this->private);
    free(this);
    this = NULL;
}

char* ShoppingCart_getName(ShoppingCart* this) {
    return strdup(this->private->customerName);
}
char* ShoppingCart_getDate(ShoppingCart* this) {
    return strdup(this->private->date);
}

size_t* ShoppingCart_find(ShoppingCart* this, char* itemName) {

    size_t* foundAndPos = malloc(sizeof(size_t) * 2);
    foundAndPos[0] = 0;
    foundAndPos[1] = 0;

    for (size_t i = 0; i < this->private->itemArraySize; i++) {
        if (strcmp(itemName,this->private->itemArray[i].getName(&this->private->itemArray[i])) == 0) {
            foundAndPos[0] = 1;
            foundAndPos[1] = i;
            return foundAndPos;
        }
    }
    return foundAndPos;
}

void ShoppingCart_addItem(ShoppingCart* this, ItemToPurchase* item) {
    size_t* pos = ShoppingCart_find(this, item->getName(item));
    if (pos[0]) {
        printf("Item is already found in the cart. It will not be added.\n");
        ItemToPurchase_deconstructor(item);
    }
    else {
        this->private->itemArraySize++;
        if (this->private->itemArraySize > this->private->itemArrayMaxSize) {
            ItemToPurchase* newItemArray = NULL;
            size_t newArrayMaxSize = this->private->itemArrayMaxSize / 2;
            if (newArrayMaxSize == 0) {
                newArrayMaxSize += this->private->itemArrayMaxSize * 2;
            }
            else {
                newArrayMaxSize += this->private->itemArrayMaxSize;
            }
            newItemArray = calloc(newArrayMaxSize,sizeof(newItemArray));

            for (size_t i = 0; i < this->private->itemArrayMaxSize; i++) {
                newItemArray[i] = this->private->itemArray[i];
            }
            newItemArray[this->private->itemArraySize - 1] = *item;

            /*for (size_t i = 0; i < this->private->itemArrayMaxSize; i++) {
                ItemToPurchase_deconstructor(&this->private->itemArray[i]);
            }*/
            free(this->private->itemArray);
            this->private->itemArray = NULL;
            this->private->itemArray = newItemArray;
            this->private->itemArrayMaxSize = newArrayMaxSize;

        }
        else {
            this->private->itemArray[this->private->itemArraySize - 1] = *item;
        }

    }
    free(pos);
}
void ShoppingCart_removeItem(ShoppingCart* this, char* itemName) {
    size_t* pos = ShoppingCart_find(this, itemName);
    if (!pos[0]) {
        printf("Item not found in the cart. It will not be removed.\n");
    }
    else {
        ItemToPurchase_deconstructor(&this->private->itemArray[pos[1]]);

        for (size_t i = 0; i < this->private->itemArraySize; i++) {
            if (i == pos[1]) {
                ItemToPurchase_deconstructor(&this->private->itemArray[pos[1]]);
                for (i = pos[1] + 1; i < this->private->itemArraySize; i ++) {
                    this->private->itemArray[i - 1] = this->private->itemArray[i];
                }
                goto arrayShifted;
            }
        }
        arrayShifted:
        this->private->itemArraySize--;
    }
    free(pos);
}
void ShoppingCart_updateQuantity(ShoppingCart* this, char* itemName, int quantity) {
    size_t* pos = ShoppingCart_find(this, itemName);
    if (!pos[0]) {
        printf("Item not found in the cart. It will not be modified.\n");
    }
    else {
        this->private->itemArray[pos[1]].updateQuantity(&this->private->itemArray[pos[1]],quantity);
    }
    free(pos);
}

int ShoppingCart_getQuantity(ShoppingCart* this) {
    int total = 0;
    for (size_t i = 0; i < this->private->itemArraySize; i ++) {
        total += this->private->itemArray[i].getQuantity(&this->private->itemArray[i]);
    }

    return total;
}
double ShoppingCart_getTotalCost(ShoppingCart* this) {
    double total = 0;
    for (size_t i = 0; i < this->private->itemArraySize; i ++) {
        total += this->private->itemArray[i].getQuantity(&this->private->itemArray[i])
                * this->private->itemArray[i].getPrice(&this->private->itemArray[i]);
    }
    return total;
}

void ShoppingCart_printDesc(ShoppingCart* this) {
    printf("%s\'s Shopping Cart - %s\n\n",this->private->customerName, this->private->date);

    for (size_t i = 0; i < this->private->itemArraySize; i++) {
        this->private->itemArray[i].printDesc(&this->private->itemArray[i]);
    }
    printf("\n");
}
void ShoppingCart_printCost(ShoppingCart* this) {
    printf("%s\'s Shopping Cart - %s\n",this->private->customerName, this->private->date);
    printf("Number of Items: %d\n\n", this->getQuantity(this));

    for (size_t i = 0; i < this->private->itemArraySize; i++) {
        this->private->itemArray[i].printDesc(&this->private->itemArray[i]);
    }
    printf("\nTotal: $%.2f\n",this->getCost(this));

}