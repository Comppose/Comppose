#include <iostream>

#include <comppose/Comppose.hpp>

namespace comppose
{
    void Row(Content content)
    {
        std::cout << "Row" << std::endl;
        content();
    }

    void Column(Content)
    {
        std::cout << "Column" << std::endl;
    }

    void Text(std::string &&text)
    {
        std::cout << "Text" << std::endl;
    }
}