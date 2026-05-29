#include <iostream>

class Real{
    private:
        int real; // This is the "secret" data that we want to protect
        int complex; // This is the "secret" data that we want to protect

    public:
        Real(int r, int c) : real(r), complex(c) {} // Constructor to initialize the data

        // Getter for the real part
        int getReal() const {
            return real;
        }

        // Getter for the complex part
        int getComplex() const {
            return complex;
        }

        // Method to display the complex number in a nice format
        void display() const {
            std::cout << real << " + " << complex << "i" << std::endl;
        }
};


int main() {
    Real myNumber(3, 4); // Create a complex number 3 + 4i

    std::cout << "The complex number is: ";
    myNumber.display(); // Display the complex number

    // Accessing the real and complex parts using getters
    std::cout << "Real part: " << myNumber.getReal() << std::endl;
    std::cout << "Complex part: " << myNumber.getComplex() << std::endl;

    return 0;
}
