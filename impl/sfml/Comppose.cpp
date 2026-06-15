#include <iostream>
#include <memory>
#include <vector>

#include <comppose/Comppose.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

#include <yoga/Yoga.h>

namespace comppose
{
    class Widget
    {
    public:
        virtual ~Widget() = default;
        Widget(const Widget &) = delete;
        Widget &operator=(const Widget &) = delete;
        Widget(Widget &&) = default;
        Widget &operator=(Widget &&) = default;
        Widget() : node(YGNodeNew(), &YGNodeFree) {}

        float GetLeftPosition() const noexcept
        {
            return YGNodeLayoutGetLeft(node.get());
        }

        float GetTopPosition() const noexcept
        {
            return YGNodeLayoutGetTop(node.get());
        }

    protected:
        using YGNodePtr = std::unique_ptr<YGNode, decltype(&YGNodeFree)>;
        YGNodePtr node;
    };

    template <YGFlexDirection flexDirection>
    class ContainerWidget : public Widget
    {
    public:
        ContainerWidget() : Widget()
        {
            YGNodeStyleSetFlexGrow(node.get(), 1.0f);
            YGNodeStyleSetFlexDirection(node.get(), flexDirection);
        }

        void AddChildren(std::unique_ptr<Widget> child)
        {
            children.push_back(std::move(child));
        }

    private:
        std::vector<std::unique_ptr<Widget>> children;
    };

    using RowWidget = ContainerWidget<YGFlexDirection::YGFlexDirectionRow>;

    void Row(Content content)
    {
        std::cout << "Row" << std::endl;
        content();
    }

    using ColumnWidget = ContainerWidget<YGFlexDirection::YGFlexDirectionColumn>;

    void Column(Content)
    {
        std::cout << "Column" << std::endl;
    }

    class TextWidget : public Widget
    {
    public:
        TextWidget(std::string &&text) : Widget() {}
    };

    void Text(std::string &&text)
    {
        std::cout << "Text" << std::endl;
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({320, 240}), "Pontino");
    window.setFramerateLimit(30);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto &resize = event->getIf<sf::Event::Resized>())
            {
                const auto [width, height] = resize->size;
                window.setView(sf::View(sf::FloatRect({0, 0}, {(float)width, (float)height})));
            }
        }

        window.clear(sf::Color::Black);

        Comppose();

        window.display();
    }
}
