#pragma once

#include <string>
#include <functional>

namespace comppose {
    using Content = std::function<void(void)>&&;

    void Row(Content);
    void Column(Content);
    void Text(std::string&& text);
}