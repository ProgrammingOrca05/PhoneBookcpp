#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

// Function to check if a string consists only of numeric characters
bool isNumeric(const string str)
{
	for (char c : str)
	{
		if (!isdigit(c)) // Check if the character is not a digit
			return false;
	}
	return !str.empty(); // Ensure the string is not empty
}

// Function to clear the input buffer (not used in the code)
void clearBuffer();

// Structure to store contact information
struct contact
{
	string name;    // Name of the contact
	string Num1;    // Primary phone number
	string Num2;    // Secondary phone number (optional)
};

// Node structure for the linked list
struct Node
{
	contact data; // Stores contact information
	Node* next;  // Pointer to the next node in the list
};

// Class for implementing a linked list
class linkedlist
{
private:
	Node* head = NULL; // Pointer to the first node in the list
	Node* tail = NULL; // Pointer to the last node in the list
	int len = 0;       // Length of the linked list

public:
	// Function to insert a new contact into the linked list
	void insert(const contact cont)
	{
		Node* newnode = new Node; // Create a new node
		newnode->data = cont;    // Assign contact data to the node
		if (head == NULL && tail == NULL) // If the list is empty
		{
			head = newnode; // Set head and tail to the new node
			tail = newnode;
			len++; // Increment the length of the list
		}
		else
		{
			tail->next = newnode; // Add the new node to the end of the list
			tail = newnode;       // Update the tail pointer
			len++;               // Increment the length of the list
		}
	}

	// Function to remove a contact by name
	bool remove(const string name) {
		Node* current = head;
		Node* previous = NULL;
		while (current)
		{
			if (current->data.name == name) // If the contact is found
			{
				if (previous) // If the contact is not the first node
				{
					previous->next = current->next; // Bypass the current node
				}
				else // If the contact is the first node
				{
					head = current->next; // Update the head pointer
				}
				if (current == tail) // If the contact is the last node
				{
					tail = previous; // Update the tail pointer
				}
				delete current; // Free the memory of the deleted node
				len--; // Decrement the length of the list
				return true; // Return true to indicate successful removal
			}
			previous = current;
			current = current->next;
		}
		return false; // Return false if the contact was not found
	}

	// Function to traverse and display a contact by name
	void traversename(const string name)
	{
		Node* current = head;
		if (current->data.name == name) // If the contact is the first node
		{
			cout << "Contact:" << endl;
			cout << "Name : " << current->data.name << endl;
			cout << "Phone Number 1 :" << current->data.Num1 << endl;
			if (current->data.Num2.empty()) // If the second phone number is empty
			{
				return;
			}
			else
			{
				cout << "Phone Number 2 :" << current->data.Num2 << endl;
				return;
			}
		}
		else
		{
			while (current != tail->next) // Traverse the list
			{
				if (current->data.name == name) // If the contact is found
				{
					cout << "Contact:" << endl;
					cout << "Name : " << current->data.name << endl;
					cout << "Phone Number 1 :" << current->data.Num1 << endl;
					if (current->data.Num2.empty()) // If the second phone number is empty
					{
						return;
					}
					else
					{
						cout << "Phone Number 2 :" << current->data.Num2 << endl;
						return;
					}
				}
				else
				{
					current = current->next; // Move to the next node
				}
			}
			return;
		}
	}

	// Function to count the number of contacts in the list
	int count()
	{
		int count = 0;
		Node* current = head;
		while (current != tail->next) {
			++count;
			current = current->next;
		}
		return count;
	}

	// Function to display all contacts in the list
	void display()
	{
		Node* current = head;
		while (current != tail->next)
		{
			cout << "Name: " << current->data.name << endl;
			cout << "Phone 1: " << current->data.Num1 << endl;
			cout << "Phone 2: " << current->data.Num2 << endl;
			current = current->next;
		}
		return;
	}

	// Function to check if the list is empty
	bool IsEmpty()
	{
		if (len == 0)
		{
			return true;
		}
		return false;
	}

	// Function to check if a phone number is not unique
	bool IsNotUnique(const string& number1, const string& number2)
	{
		Node* current = head;
		while (current != nullptr)
		{
			if (current->data.Num1 == number1 || current->data.Num2 == number1 ||
				(!number2.empty() && (current->data.Num1 == number2 || current->data.Num2 == number2))) {
				cout << "Repeated number was found! Contact was not inserted!" << endl;
				return true;
			}
			current = current->next;
		}
		return false;
	}
};

// Array of linked lists to store contacts for each letter of the alphabet
linkedlist phonebook[26];

// Global vector to store all contact names for sorting and searching
vector <string> GLOBALNAME;

// Function prototypes
void addcontact();
void searchcontact();
void editcontact();
void deletecontact();
void CountOfContactPerLetter();
void PrintAllContacts();
void menu();

// Main function
int main()
{
	menu(); // Start the program by displaying the menu
	return 0;
}

// Function to display the menu and handle user input
void menu()
{
	cout << "Welcome to the contacts book! Please choose an option" << endl;
	int choice;
	do
	{
		cout << "1. Add Contact" << endl;
		cout << "2. Edit Contact" << endl;
		cout << "3. Delete Contact" << endl;
		cout << "4. Search Contact" << endl;
		cout << "5. Number of Contacts per letter" << endl;
		cout << "6. Print All Contacts" << endl;
		cout << "7. Exit" << endl;

		cin >> choice;
		switch (choice)
		{
		case 1:
			addcontact(); // Add a new contact
			break;
		case 2:
			editcontact(); // Edit an existing contact
			break;
		case 3:
			deletecontact(); // Delete a contact
			break;
		case 4:
			searchcontact(); // Search for a contact
			break;
		case 5:
			CountOfContactPerLetter(); // Count contacts per letter
			break;
		case 6:
			PrintAllContacts(); // Print all contacts
			break;
		case 7:
			cout << "Thanks for using the contact book!" << endl;
			return;
		default:
			cout << "Invalid Choice!" << endl;
			break;
		}
	} while (choice != 7);
}

// Function to get the index of a letter in the alphabet (0 for 'A', 1 for 'B', etc.)
int getindex(char x)
{
	x = toupper(x); // Convert to uppercase to handle case sensitivity
	return x - 'A';
}

// Function to sort the global vector of names using selection sort
void SelectionSort()
{
	int VSize = GLOBALNAME.size();
	for (int i = 0; i < VSize - 1; i++)
	{
		int minindex = i;
		for (int j = i + 1; j < VSize; j++)
		{
			if (GLOBALNAME[j] < GLOBALNAME[minindex])
			{
				minindex = j;
			}
		}
		if (minindex != i)
		{
			swap(GLOBALNAME[i], GLOBALNAME[minindex]);
		}
	}
}

// Function to perform binary search on the global vector of names
int BinarySearch(const string name)
{
	int low = 0;
	int high = GLOBALNAME.size() - 1;
	while (low <= high)
	{
		int mid = low + (high - low) / 2;
		if (GLOBALNAME[mid] == name)
		{
			return mid;
		}
		else if (GLOBALNAME[mid] < name)
		{
			low = mid + 1;
		}
		else if (GLOBALNAME[mid] > name)
		{
			high = mid - 1;
		}
	}
	return -1; // Return -1 if the name is not found
}

// Function to add a new contact to the phonebook
void addcontact()
{
	contact cont;
	while (cont.name.empty())
	{
		cout << "Enter Name(necessary): ";
		getline(cin, cont.name);
	}

	while (cont.Num1.empty())
	{
		cout << "Enter Phone 1(necessary) : " << endl;
		getline(cin, cont.Num1);

		if (!isNumeric(cont.Num1))
		{
			cout << "Invalid phone number. Please enter a valid numeric value." << endl;
			cont.Num1.clear();
		}
	}
	cout << "Enter Phone 2 (Press enter to skip if you only have one phone number) : " << endl;
	getline(cin, cont.Num2);

	int index = getindex(cont.name[0]); // Get the index for the contact's first letter

	if (index < 0 || index >= 26)
	{
		cout << "Error: Invalid index for the name. Contact not added." << endl;
		return;
	}

	if (phonebook[index].IsNotUnique(cont.Num1, cont.Num2)) // Check for duplicate phone numbers
	{
		return;
	}

	phonebook[index].insert(cont); // Insert the contact into the appropriate linked list
	GLOBALNAME.push_back(cont.name); // Add the name to the global vector
	SelectionSort(); // Sort the global vector
	cout << "Contact added successfully ;)" << endl;
	return;
}

// Function to search for a contact by name
void searchcontact()
{
	if (GLOBALNAME.empty())
	{
		cout << "Phone book is empty." << endl;
		return;
	}
	string name;
	cout << "Enter name to search for: " << endl;
	while (name.empty())
	{
		cout << "Enter Name(necessary): " << endl;
		getline(cin, name);
	}
	int searchresult = BinarySearch(name); // Perform binary search on the global vector
	if (searchresult >= 0)
	{
		int index = getindex(name[0]); // Get the index for the contact's first letter
		phonebook[index].traversename(name); // Display the contact details
	}
	else
	{
		cout << "Name Not found!" << endl;
	}
}

// Function to edit an existing contact
void editcontact()
{
	if (GLOBALNAME.empty())
	{
		cout << "Phone book is empty." << endl;
		return;
	}
	string name;
	cout << "Enter name to edit for: " << endl;
	while (name.empty())
	{
		cout << "Enter Name(necessary): " << endl;
		getline(cin, name);
	}

	int searchresult = BinarySearch(name); // Perform binary search on the global vector
	if (searchresult >= 0)
	{
		int oldindex = getindex(name[0]); // Get the index for the contact's first letter
		phonebook[oldindex].remove(name); // Remove the old contact

		contact updatedcontact;
		while (updatedcontact.name.empty())
		{
			cout << "Enter updated Name(necessary): " << endl;
			getline(cin, updatedcontact.name);
		}

		while (updatedcontact.Num1.empty())
		{
			cout << "Enter updated Phone 1(necessary) : " << endl;
			getline(cin, updatedcontact.Num1);

			if (!isNumeric(updatedcontact.Num1))
			{
				cout << "Invalid phone number. Please enter a valid numeric value." << endl;
				updatedcontact.Num1.clear();
			}
		}
		cout << "Enter updated Phone 2 (Press enter to skip if you only have one phone number) : " << endl;
		getline(cin, updatedcontact.Num2);

		int index = getindex(updatedcontact.name[0]); // Get the index for the updated contact's first letter
		if (index < 0 || index >= 26) // Validate index range
		{
			cout << "Error: Invalid index for the name. Contact not added." << endl;
			return;
		}
		phonebook[index].insert(updatedcontact); // Insert the updated contact
		if (phonebook[index].IsNotUnique(updatedcontact.Num1, updatedcontact.Num2)) // Check for duplicate phone numbers
		{
			cout << "Error: A repeated phone number was found! Contact was not added!";
			return;
		}

		auto it = find(GLOBALNAME.begin(), GLOBALNAME.end(), name); // Find the old name in the global vector
		if (it != GLOBALNAME.end())
		{
			GLOBALNAME.erase(it); // Remove the old name
		}
		GLOBALNAME.push_back(updatedcontact.name); // Add the updated name
		SelectionSort(); // Sort the global vector
		return;
	}
	else
	{
		cout << "Name was not found!" << endl;
		return;
	}
}

// Function to delete a contact by name
void deletecontact()
{
	if (GLOBALNAME.empty())
	{
		cout << "Phone book is empty." << endl;
		return;
	}
	string name;
	cout << "Enter name to edit for: " << endl;
	while (name.empty())
	{
		cout << "Enter Name(necessary): " << endl;
		getline(cin, name);
	}
	int searchresult = BinarySearch(name); // Perform binary search on the global vector
	if (searchresult >= 0)
	{
		int index = getindex(name[0]); // Get the index for the contact's first letter
		phonebook[index].remove(name); // Remove the contact from the linked list
		GLOBALNAME[searchresult].erase(); // Remove the name from the global vector
		cout << "Contact was deleted successfully" << endl;
		return;
	}
	else
	{
		cout << "Name was not found!" << endl;
		return;
	}
}

// Function to count the number of contacts for a specific letter
void CountOfContactPerLetter()
{
	if (GLOBALNAME.empty())
	{
		cout << "Phone book is empty." << endl;
		return;
	}
	char x;
	cout << "Enter character: ";
	cin >> x;

	int index = getindex(x); // Get the index for the entered character
	if (index < 0 || index >= 26) // Validate index range
	{
		cout << "Error: Invalid index for the name. Contact not added." << endl;
		return;
	}

	cout << x << " => " << phonebook[index].count() << " contacts" << endl; // Display the count of contacts
	return;
}

// Function to print all contacts in the phonebook
void PrintAllContacts()
{
	if (GLOBALNAME.empty()) {
		cout << "Phone book is empty." << endl;
		return;
	}

	for (int i = 0; i < 26; i++)
	{
		if (phonebook[i].IsEmpty()) // Skip empty linked lists
		{
			continue;
		}
		char x = 'A' + i;
		cout << "Contacts under the letter: " << x << endl;
		phonebook[i].display(); // Display all contacts in the linked list
	}
}

// Function to clear the input buffer (not used in the code)
void clearBuffer() {
	cin.clear();               // Clear any error flags on cin
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard leftover characters in the buffer
}