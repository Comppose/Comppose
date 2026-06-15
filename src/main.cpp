#include <iostream>

#include <comppose/Comppose.hpp>
using namespace comppose;

int main()
{
    std::cout << "Hello World" << std::endl;

    Row([]{
        Text("Hello World");
    });
}
