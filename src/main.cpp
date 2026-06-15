#include <iostream>

#include <comppose/Comppose.hpp>
using namespace comppose;

void Comppose()
{
    Row([]{
        Text("Hello World");
    });
}
