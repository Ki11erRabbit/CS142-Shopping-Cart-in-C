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

size_t ShoppingCart_find(ShoppingCart* this, char* itemName) {
    for (size_t i = 0; i < this->private->itemArraySize; i++) {
        if (strcmp(itemName,this->private->itemArray[i].getName(&this->private->itemArray[i])) == 0) {
            return i;
        }
    }
    return 0;
}

void ShoppingCart_addItem(ShoppingCart* this, ItemToPurchase* item) {
    size_t pos = ShoppingCart_find(this, item->getName(item));
    if (pos) {
        printf("Item is already found in the cart. It will not be added.\n");
        ItemToPurchase_deconstructor(item);
    }
    else {
        this->private->itemArraySize++;
        if (this->private->itemArraySize > this->private->itemArrayMaxSize) {
            ItemToPurchase* newItemArray = NULL;
            size_t newArrayMaxSize = (this->private->itemArrayMaxSize + (this->private->itemArrayMaxSize / 4));
            newItemArray = malloc(sizeof(newItemArray) * newArrayMaxSize);

            for (size_t i = 0; i < this->private->itemArrayMaxSize; i++) {
                newItemArray[i] = *this->private->itemArray[0].copy(&this->private->itemArray[0]);
            }
            newItemArray[this->private->itemArraySize] = *item;

            for (size_t i = 0; i < this->private->itemArrayMaxSize; i++) {
                ItemToPurchase_deconstructor(&this->private->itemArray[0]);
            }
            free(this->private->itemArray);
            this->private->itemArray = NULL;
            this->private->itemArray = newItemArray;
            this->private->itemArrayMaxSize = newArrayMaxSize;

        }
        else {
            this->private->itemArray[this->private->itemArraySize] = *item;
        }

    }
}
void ShoppingCart_removeItem(ShoppingCart* this, char* itemName) {
    size_t pos = ShoppingCart_find(this, itemName);
    if (!pos) {
        printf("Item not found in the cart. It will not be removed.\n");
    }
    else {
        ItemToPurchase_deconstructor(&this->private->itemArray[pos]);

        for (size_t i = 0; i < this->private->itemArraySize; i++) {
            if (i != pos) {

            }
        }
    }
}
void ShoppingCart_updateQuantity(ShoppingCart* this, char* itemName);

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
}
void ShoppingCart_printCost(ShoppingCart* this) {
    printf("%s\'s Shopping Cart - %s\n",this->private->customerName, this->private->date);
    printf("Number of Items: %d\n\n", this->getQuantity(this));

    for (size_t i = 0; i < this->private->itemArraySize; i++) {
        this->private->itemArray[i].printDesc(&this->private->itemArray[i]);
    }
    printf("\nTotal: $%.2f",this->getCost(this));

}