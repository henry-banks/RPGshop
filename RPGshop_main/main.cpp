#include <iostream>
#include <string>
using namespace std;

struct Item
{
	string name;
	float cost;
	int quantity;
};
bool isItemValid(Item inItem)
{
	if (inItem.name != "NULL_ITEM" && inItem.cost >= 0 && inItem.quantity != -1) { return true; }
	else { return false; }
}

struct Shop
{
	float money;
	Item items[100]; //I do hope there are no more than 1 hundred items.
					 //also i wish i could use vectors for this...
};

void ChangePriceSingle(Shop &inShop)
{
	string itemName;
	float newPrice;

	printf("\nName of item(case-sensitive): ");
	cin >> itemName;
	if (itemName == "NULL_ITEM") {
		printf("Invalid name.\n");
		return;
	}
	printf("New price: ");
	cin >> newPrice;
	if (newPrice < 0) {
		printf("Price must be positive.\n");
		return;
	}


	bool isFound = false;
	for (int i = 0; i < 100; i++)
	{
		if (inShop.items[i].name == itemName && isItemValid(inShop.items[i]))
		{
			if (newPrice >= 0) { inShop.items[i].cost = newPrice; }
			else { printf("Price must be at least 0."); }

			isFound = true;
			break;
		}
	}
	if (isFound) {
		cout << "\n\nNew price for " << itemName << ": " << newPrice << endl;
	}
	else {
		cout << itemName << " not found.\n";
	}

}
void ChangePriceAll(Shop &inShop)
{
	printf("This could take a while if there are a lot of items.\n");
	printf("Input a cost of -1 to exit.\n");
	system("pause");

	int newPrice; //I do this to search for -1, the exit code.

	for (int i = 0; i < 100; i++)
	{
		if (isItemValid(inShop.items[i]))
		{
			cout << "\n" << inShop.items[i].name << ".  New cost: ";
			cin >> newPrice;
			if (newPrice >= 0) { inShop.items[i].cost = newPrice; }
			else if (newPrice == -1) {
				printf("Exiting...");
				return;
			}
			else {
				printf("Price must be at least 0.");
				return;
			}
		}
	}

}
void SellItem(Shop &inShop)
{
	string itemName;
	int numToSell;
	float totalCost;

	printf("Choose item to sell(case-sensitive): ");
	cin >> itemName;
	if (itemName == "NULL_ITEM") {
		printf("Invalid name.\n");
		return;
	}
	printf("Amount to sell (will sell all if not enough): ");
	cin >> numToSell;
	if (numToSell < 1) {
		printf("Must sell at least 1 item.");
		return;
	}

	bool isFound = false;
	for (int i = 0; i < 100; i++)
	{
		if (inShop.items[i].name == itemName && isItemValid(inShop.items[i]))
		{
			//Open these if you want to die. :)
			if (inShop.items[i].quantity >= numToSell) {
				totalCost = inShop.items[i].cost*numToSell;
				inShop.money += totalCost;
				inShop.items[i].quantity -= numToSell;
			}
			else {
				for (int j = 0; j < inShop.items[i].quantity; j++) {
					inShop.money += inShop.items[i].cost;
					inShop.items[i].quantity--;
				}
			}
			isFound = true;
			break;
		}
	}
	if (!isFound) {
		cout << "\n" << itemName << " not found!";
	}
	else {
		cout << "\nSold " << numToSell << " of " << itemName << " for " << totalCost << ".";
	}
}
void BuyItem(Shop &inShop)
{
	string itemName;
	int numToBuy;
	float itemCost, totalCost;
	char isNew;

	printf("Choose item to buy(case-sensitive): ");
	cin >> itemName;
	if (itemName == "NULL_ITEM") {
		printf("Invalid name.\n");
		return;
	}
	printf("Amount to buy: ");
	cin >> numToBuy;
	if (numToBuy < 1) {
		printf("Must buy at least 1 item.");
		return;
	}
	printf("Is this a new item (y/n)? ");
	cin >> isNew;

	if (isNew == 'y')
	{
		printf("Cost of item: ");
		cin >> itemCost;
		if (itemCost < 0) {
			printf("Cost must be positive.\n");
			return;
		}
		for (int i = 0; i < 100; i++)
		{
			//Change the first 'invalid' Item to this new item.
			//I REALLY wish I had vectors right now.
			if (!isItemValid(inShop.items[i]))
			{
				inShop.items[i].name = itemName;
				inShop.items[i].quantity = numToBuy;
				inShop.items[i].cost = itemCost;

				totalCost = inShop.items[i].cost*numToBuy; //I'm going to let the shop go into debt if need be.
				inShop.money -= totalCost;

				cout << "\nBought " << numToBuy << " of " << itemName << " for " << totalCost << ".";
				break;
			}
		}

	}

	else
	{
		bool isFound = false;
		for (int i = 0; i < 100; i++)
		{
			if (inShop.items[i].name == itemName && isItemValid(inShop.items[i]))
			{
				inShop.items[i].quantity += numToBuy;
				totalCost = inShop.items[i].cost*numToBuy;
				inShop.money -= totalCost;

				isFound = true;
				break;
			}
		}
		if (!isFound) {
			cout << "\n" << itemName << " not found!";
		}
		else {
			cout << "\nBought " << numToBuy << " of " << itemName << " for " << totalCost << ".";
		}
	}

}
void ShowItems(Shop &inShop)
{
	//Simplest one. ;D
	printf("\n\n");
	bool isItem = false;

	/*I already have the foreach loop setup and would rather do this
	than convert it to a for loop and change everything to 'inShop.items[i]'*/
	int count = 1;

	for (Item i : inShop.items)
	{
		if (isItemValid(i)) {
			cout << count++ << ". Name: " << i.name << " Cost: " << i.cost << " Quantity: " << i.quantity << "\n";
			isItem = true;
		}
	}
	if (!isItem) {
		printf("No items found!\n");
	}
}

//Shows menu and lets player chose an action
void Menu(int &choice, Shop &shop)
{
	printf("============================\n");
	printf("RPG Shop\n");
	printf("============================\n");
	printf("Money: %f\n", shop.money);
	printf("----------------------------\n");
	printf("0. Change price of 1 item\n");
	printf("1. Change price of ALL items\n");
	printf("2. Buy item\n");
	printf("3. Sell item\n");
	printf("4. Show all items\n");
	printf("5. Exit\n\n");

	printf("Your Choice (0-5, do NOT put in a char): ");
	cin >> choice;
	printf("----------------------------\n");

	switch (choice)
	{
	case 0:
		ChangePriceSingle(shop);
		printf("\n\n");
		break;
	case 1:
		ChangePriceAll(shop);
		printf("\n\n");
		break;
	case 2:
		BuyItem(shop);
		printf("\n\n");
		break;
	case 3:
		SellItem(shop);
		printf("\n\n");
		break;
	case 4:
		ShowItems(shop);
		printf("\n\n");
		break;
	case 5:
		break;
	default:
		printf("Invalid input.  Try again.\n\n");
		break;
	}
}

//Sets all items to 'invalid' (see isItemValid).
void setupShop(Shop &shop)
{
	printf("Setting up Shop...\n");
	for (int i = 0; i < 100; i++)
	{
		shop.items[i].name = "NULL_ITEM";
		shop.items[i].cost = -1;
		shop.items[i].quantity = -1;
	}
	printf("Shop set up.\n\n\n");
}

//RPG shop
void main()
{
	Shop shop;
	shop.money = 1000; //I'll start with 1K money.
	int choice = -1;

	setupShop(shop);

	do
	{
		Menu(choice, shop);
	} while (choice != 5);

	printf("\n\n");
	system("pause");
}