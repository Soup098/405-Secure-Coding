// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

//This code is to create a custom exception to be thrown in the do_custom_application_logic() method.
class CustomException : public std::exception {
public:
    const char* what() const noexcept override {
        return "This is a custom exception";
    }
};

bool do_even_more_custom_application_logic()
{
    std::cout << "Running Even More Custom Application Logic." << std::endl;

    throw std::runtime_error("Even More Custom Application Logic FAILED");//Throw a runtime_error exception when this method is called.
    
    return true;
}
void do_custom_application_logic()
{
    std::cout << "Running Custom Application Logic." << std::endl;

    //implementation of a try/catch block to throw an exception in the case where do_even_more_application_logic() fails
    try {
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }

        std::cout << "Leaving Custom Application Logic." << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }

    throw CustomException();
    
}

float divide(float num, float den)
{
    //use of an if statement that will throw an invalid_argument exception if the denominator is zero. you can not divide by zero
    if (den == 0) {
        throw std::invalid_argument("Can not divide by zero");
    }
    return (num / den);
}

void do_division() noexcept
{
    float numerator = 10.0f;
    float denominator = 0;

    //I used a try catch block that will throw an exception if the divide() method fails
    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (std::invalid_argument& e) {
        std::cout << "Invalid argument: " << e.what() << std::endl;
    }
}


int main() {
    //try/catch block that will run the methods of the program, and throw custom, standard and uncaught exceptions respectivly if the methods do not succeed.
    try {
        std::cout << "Exceptions Tests!" << std::endl;

        do_division();
        do_custom_application_logic();
    }
    catch (const CustomException& e) {
        std::cout << "custom exception: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "standard exception: " << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "uncaught exception: " << std::endl;
    }
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu