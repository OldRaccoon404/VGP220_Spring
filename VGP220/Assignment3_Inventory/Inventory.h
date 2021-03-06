#pragma once
#include <ostream>
#include <iostream>
#include "Item.h"

class Inventory
{
public:
	//COMMENT: Use initialization listfor constructors, mMaxSlots and mSlotsOccupied.
	Inventory()
	{
		//TODO: Implement a default constructor for the Inventory class where the max number of slots
		// is 5 and all the slots are free (They are not occupied).

		mInventory = new Item[5];
		mMaxSlots = 5;
		mSlotsOccupied = 0;
		//std::cout << "Default constructor called\n";
	}
	//COMMENT: mSlotsOccupied in an initialization list like mMaxSlots.
	Inventory(uint32_t capacity)
		:mMaxSlots(capacity)
	{
		//TODO: Implement a non default constructor for the Inventory class where 
		//all the slots are free (They are not occupied).
		mInventory = new Item[mMaxSlots];
		mSlotsOccupied = 0;
		//std::cout << "Custom constructor called\n";

	}

	Inventory(const Inventory& other)
	{
		//TODO: Implement a copy constructor for this class. Avoid shallow copy.

		CopyingInvetory(other);


		//std::cout << "Copy constructor called\n";

	}
	Inventory(Inventory&& other)
	{
		//TODO: Implement a move constructor for this class. Reset to a default state the other inventory.
		MovingElements(std::move(other));

		//std::cout << "Move constructor called\n";

	}

	~Inventory()
	{
		//TODO: Implement a destructor for this class.
		delete[] mInventory;
		mInventory = nullptr;
		std::cout << "Destructor called\n";

	}

	//TODO: Implement a copy assignment operator
	Inventory& operator=(const Inventory& rhs)
	{
		if (this != &rhs)
		{
			
			CopyingInvetory(rhs);
			//std::cout << "Copy assignment operator called\n";
		}
		return *this;
	}
	//TODO: Implement a move assignment operator
	Inventory& operator =(Inventory&& rhs)
	{
		if (this != &rhs)
		{

			MovingElements(std::move(rhs));
			//std::cout << "Move assignment operator called\n";
		}
		return *this;
		
	}

	void AddItem(Item newItem)
	{
		//TODO: Implement AddItem MethodThis method adds a new item to the inventory. 
		//First it searches for this item to see if the item exists, and if the item exists 
		//it checks the quantity, because the max quantity allowed per slot is 50.
		//So, for example, if you have 50 healing potions in your inventory, and you want to add one more, this potion
		//should occupy a new slot. Pay attention that the SearchItem function already does this quantity check for you.
		//The extra check that you should do is for the accumulated quantity. So your function should check
		//how many items this current slot has and if you add this new item quantity, how many items you will have.
		//If it's greater than 50, you should make the quantity of one slot 50 and add the remainder quantity to a new slot.
		//For example:
		//[ HP 48 ] [  ] [  ] [  ] [  ] Inventory has a HP(healing potions) with 48 as quantity and you want to add more 5 HP
		//[ HP 50 ] [HP 3] [  ] [  ] [  ] Inventory after you added 5 HP

		//If the Inventory is full, return a message to the user that the inventory is full and the items will be discarted.
		//Use the method IsFullForItem;

		//If after you insert the item your inventory becomes full for the remainder, Print a message to the user with how many
		//items will be discarted;

		//SPECIAL CASE: If the user adds an item of type charm with the name "Expansion" your inventory
		//should expand adding 5 more empty slots for the user.
		std::cout << "Adding " << newItem.quantity << " " << newItem.name << " in inventory." << "\n";

	
		//TO:DO ADD CHARM
			if (newItem.name == "Expansion" && newItem.type==ItemType::Charm)
			{
				Item* temp = mInventory;
				mInventory = new Item[mMaxSlots + 5];
				mMaxSlots += 5;


				for (int i = 0; i < mSlotsOccupied; ++i)
				{
					mInventory[i] = temp[i];
				}

				mInventory[mSlotsOccupied] = newItem;
				++mSlotsOccupied;

				std::cout << "Expansion was successfully applied!\n";
			}
			else
			{

				int remainder = 0;
				int index = -1;
				if (isFullForItem(&newItem) == false) // Znachit mojno rabototat
				{
					if (SearchItemByNameLessThan50(newItem.name) == -1)
					{
						mInventory[mSlotsOccupied] = newItem;
						mSlotsOccupied++;

						if (mInventory[mSlotsOccupied - 1].quantity > 50)
						{
							remainder = (50 - mInventory[mSlotsOccupied - 1].quantity) * -1;
							if (mInventory[mSlotsOccupied - 1].quantity > 50)
							{
								mInventory[mSlotsOccupied - 1].quantity = 50;
							}
							newItem.quantity = remainder;

							while (isFullForItem(&newItem) == false && remainder > 0)
							{
								mInventory[mSlotsOccupied] = newItem;
								mSlotsOccupied++;
								remainder = (50 - mInventory[mSlotsOccupied - 1].quantity) * -1;
								if (mInventory[mSlotsOccupied - 1].quantity > 50)
								{
									mInventory[mSlotsOccupied - 1].quantity = 50;
								}
								newItem.quantity = remainder;
							}
						}

						if (isFullForItem(&newItem) == true && remainder > 0)
						{
							std::cout << newItem.name << " x " << newItem.quantity << "items will be discarted" << "\n";
						}
					}
					else
					{
						index = SearchItemByNameLessThan50(newItem.name);

						mInventory[index].quantity += newItem.quantity;
						
						remainder = (50 - mInventory[index].quantity) * -1;
						if (mInventory[index].quantity > 50)
						{
						mInventory[index].quantity = 50;
						}
						newItem.quantity = remainder;

						while (isFullForItem(&newItem) == false && remainder > 0)
						{
							mInventory[mSlotsOccupied] = newItem;
							mSlotsOccupied++;
							remainder = (50 - mInventory[mSlotsOccupied - 1].quantity) * -1;
							if (mInventory[mSlotsOccupied - 1].quantity > 50)
							{
								mInventory[mSlotsOccupied - 1].quantity = 50;
							}
							newItem.quantity = remainder;
						}

						if (isFullForItem(&newItem) == true && remainder>0)
						{
							std::cout << newItem.name << " x " << newItem.quantity << "items will be discarted" << "\n";
						}
						
					}
				}
				else
				{
					std::cout << "The inventory is full " << newItem.quantity << " " << newItem.name << " will be discarted." << "\n";

				}
			}
				
	}

	void RemoveItem(std::string itemName, int quantity)
	{
		//TODO: Implement RemoveItem method
		//RemoveItem, should remove a quantity from the slot with the item. If the whole slot 
		//is empty, you should shift all the other items of the inventory;
		//If you try to remove more than what you have in one slot, just make the slot empty.
		//For example:
		//[ HP 50 ] [ HP 30 ] [  ] [  ] [  ] //You tried to remove 80 HP from the inventory
		//[ HP 30 ] [  ] [  ] [  ] [  ] //You just remove from one slot.

		std::cout << "Removing " << quantity << " " << itemName << " from inventory." << "\n";

		if (SearchItemByName(itemName) != -1)
		{
			int indexBiggestItem = -1;
			int biggestQuantity = 0;
			for (int i = 0; i < mSlotsOccupied; ++i)
			{
				if (itemName.compare(mInventory[i].name) == 0 && mInventory[i].quantity > biggestQuantity)
				{
					indexBiggestItem = i;
					biggestQuantity = mInventory[i].quantity;

				}
			}
			
			biggestQuantity -= quantity;
			if (biggestQuantity - quantity <= 0)
			{
				mInventory[indexBiggestItem].quantity = 0;
				//Check if not the last was deleted

				if (indexBiggestItem != mSlotsOccupied)
				{
					for (int i = indexBiggestItem; i < mSlotsOccupied-1; ++i)
					{
						
						mInventory[i].name = mInventory[i + 1].name;
						mInventory[i].quantity = mInventory[i + 1].quantity;
						mInventory[i].type = mInventory[i + 1].type;


						mInventory[i + 1].quantity = 0;
						mInventory[i + 1].name = "";

					}
					--mSlotsOccupied;
				}
				else
				{

					mInventory[indexBiggestItem].quantity = 0;
					mInventory[indexBiggestItem].name = "";
					--mSlotsOccupied;
				}
				
			}
			else
			{
				mInventory[indexBiggestItem].quantity -= quantity;
			}
			
		}
		else
		{
			std::cout << "You don't have " << itemName << " in your inventory. Delete operation failed!\n";
		}
		

		//SPECIAL CASE: If the user removes the charm Expansion from the inventory, your inventory 
		//should reduce the number of slots in 5, discarting all the items from the removed slots.
	}

	Item* UseItem(std::string itemName)
	{
		// TODO: Search for the item and if it exists, return this item and remove one from the inventory
		// otherwise, return nullptr.
		// The user is just allowed to use the Types: Posion and Utility.

		std::cout << "Using " << itemName << "\n";

		if (SearchItemByName(itemName) != 1)
		{
			int index = SearchItemByName(itemName);
			if (mInventory[index].type == ItemType::Potion || mInventory[index].type == ItemType::Utility)
			{
				RemoveItem(itemName,1);
				return &mInventory[index];
			}
			else
			{
				std::cout << "You cant use this item. You are allowed to use only -> Potion and Utility. " << itemName << "\n";

			}
		}
		
		std::cout << "You don't have this item in your inventory! You cant use it then.  " << itemName << "\n";

			return nullptr;


	}

	
	//friend std::ostream& operator << (std::ostream& stream,Item item)
	//{
	//	
	//	stream << " [" << item.name << " x " << item.quantity << " ]";
	//	
	//	
	//	
	//	return stream;
	//}

	 void ShowInventory()
	{
		 std::cout << "\n\n";

		for (int i = 0; i < mMaxSlots; ++i)
		{
			if(mInventory[i].quantity<100 && mInventory[i].quantity!=0)
			{
			std::cout << "[" << mInventory[i].name << " x " << mInventory[i].quantity << " ] ";
			}
			else
			{
				std::cout << "[ ] ";

			}

			if ((i+1) % 5 == 0 && i!=0)
			{
				std::cout << "\n";

			}
		}
		
	}


private:
	//Array of Items
	Item* mInventory;
	//This variable tracks the capacity of the inventory
	uint32_t mMaxSlots;
	//This variable tracks how many slots are occupied.
	uint32_t mSlotsOccupied;


	//Help functions
	void CopyingInvetory(const Inventory& other)
	{
		if (mInventory != nullptr)
		{
			mMaxSlots = 0;
			mSlotsOccupied = 0;
			delete[]mInventory;
			mInventory = nullptr;
		}

		mMaxSlots = other.mMaxSlots;
		mSlotsOccupied = other.mSlotsOccupied;
		mInventory = new Item[other.mMaxSlots];

		for (int i = 0; i < other.mSlotsOccupied; ++i)
		{
			mInventory[i] = other.mInventory[i];
		}
	}
	void MovingElements(Inventory&& other)
	{
		mSlotsOccupied = other.mSlotsOccupied;
		other.mSlotsOccupied = 0;

		mMaxSlots = other.mMaxSlots;
		other.mMaxSlots = 0;

		delete[] mInventory;
		mInventory = nullptr;

		mInventory = other.mInventory;
		other.mInventory = nullptr;

	}

	//This method seaches for the item inside the Inventory and if it finds the item with less than
	//50 as quantity, it returns the index of the item inside the inventory array, otherwise, returns -1.
	int SearchItemByNameLessThan50(std::string target) const
	{
		int index = -1;
		for (int i = 0; i < mSlotsOccupied; i++)
		{
			if (target.compare(mInventory[i].name) == 0 && mInventory[i].quantity < 50)
			{
				index = i;
				break;
			}
		}

		return index;
	}

	//Returns the index of the item if it exists and -1 if it doesn't.
	int SearchItemByName(std::string target) const
	{
		int index = -1;
		for (int i = 0; i < mSlotsOccupied; i++)
		{
			if (target.compare(mInventory[i].name) == 0)
			{
				index = i;
				break;
			}
		}
		return index;
	}

	//If you don't have the item inside the inventory and all the slots are occupied - True
	//If you have the item in the inventory with max capacity and all the other slots are occupied - True
	//Otherwise - False.
	bool isFullForItem(Item* item) const
	{
		int index = SearchItemByNameLessThan50((*item).name);
		if (index == -1 && mSlotsOccupied == mMaxSlots)
		{
			return true;
		}
		if (index != -1 && mInventory[index].quantity >= 50 && mSlotsOccupied == mMaxSlots)
		{
			return true;
		}
		return false;
	}
};