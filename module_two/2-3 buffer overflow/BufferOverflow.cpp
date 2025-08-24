// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>

int main()
{
	std::cout << "Buffer Overflow Example" << std::endl;

	// TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
	//  even though it is a constant and the compiler buffer overflow checks are on.
	//  You need to modify this method to prevent buffer overflow without changing the account_number
	//  variable, and its position in the declaration. It must always be directly before the variable used for input.
	//  You must notify the user if they entered too much data.


	//stop user from entering more than 20 characters


	const std::string account_number = "CharlieBrown42";
	char user_input[20];

	bool input_flag = true;
	// I declared in input_flag boolean variable to jump out of the while loop when the input does not exceed character limit
	while (input_flag) {
		input_flag = false;//set the flag to false
		std::cout << "Enter a value: ";
		std::cin.getline(user_input, 20);//use getline() method with an input limit of 20, so that the input stream stops reading after too many characters
		if (std::cin.fail()) {//if the user input exceeds 19 characters since the C style input (char user_input[20];) uses null terminator, it will trigger cin.fail()
			std::cin.clear(); // use cin.clear() to reset the error state and set cin.fail() back to false
			//use cin.ignore() to discard the invalid input in the input buffer.
			//I used std::numeric_limits<std::streamsize>::max() so that it was discard all characters above the limit, no matter the length of the user input.
			//the second argument '\n' will stop ignoring input at the new line
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			input_flag = true;//reset the flag back to true to repeat the loop
			std::cout << "You have entered too many characters. This would cause a buffer overflow. Please try again.\n";//inform user they have entered too many characters
		}
	}

	std::cout << "You entered: " << user_input << std::endl;
	std::cout << "Account Number = " << account_number << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
