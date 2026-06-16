#include <iostream>

#include <comppose/Comppose.hpp>
using namespace comppose;

void Comppose()
{
    Row([] {
        Column([] {
            Text("Hello");
            Text("World");

            Row([] {
                Text("Hello");
                Text("World");
            });
        });

        Column([] {
            Text("Hello");
            Text("World");

            Row([] {
                Text("Hello");
                Text("World");
            });
        });
    });
}
