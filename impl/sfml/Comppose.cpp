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
        Widget() : node(YGNodeNew(), &YGNodeFree)
        {
            YGNodeSetContext(node.get(), this);
        }

        float GetLeftPosition() const noexcept
        {
            return YGNodeLayoutGetLeft(node.get());
        }

        float GetTopPosition() const noexcept
        {
            return YGNodeLayoutGetTop(node.get());
        }

        void SetWidth(float width) const noexcept
        {
            YGNodeStyleSetWidth(node.get(), width);
        }

        void SetHeight(float height) const noexcept
        {
            YGNodeStyleSetHeight(node.get(), height);
        }

    protected:
        friend class ContainerWidget;
        using YGNodePtr = std::unique_ptr<YGNode, decltype(&YGNodeFree)>;
        YGNodePtr node;
    };

    class ContainerWidget : public Widget
    {
    public:
        ContainerWidget(YGFlexDirection flexDirection) : Widget()
        {
            YGNodeStyleSetFlexGrow(node.get(), 1.0f);
            YGNodeStyleSetFlexDirection(node.get(), flexDirection);
        }

        void AddChild(std::shared_ptr<Widget> child)
        {
            children.push_back(std::move(child));
        }

    private:
        std::vector<std::shared_ptr<Widget>> children;
    };

    static inline std::vector<std::shared_ptr<ContainerWidget>> buildContext{
        std::make_shared<ContainerWidget>(YGFlexDirectionColumn),
    };

    class RowWidget : public ContainerWidget
    {
    public:
        RowWidget() : ContainerWidget(YGFlexDirection::YGFlexDirectionRow) {};
    };

    void Row(Content content)
    {
        auto parentContainer = buildContext.back();
        auto row = std::make_shared<RowWidget>();
        buildContext.emplace_back(row);
        parentContainer->AddChild(row);
        content();
        buildContext.pop_back();
    }

    class ColumnWidget : public ContainerWidget
    {
    public:
        ColumnWidget() : ContainerWidget(YGFlexDirection::YGFlexDirectionColumn) {};
    };

    void Column(Content content)
    {
        auto parentContainer = buildContext.back();
        auto column = std::shared_ptr<ColumnWidget>();
        buildContext.emplace_back(column);
        parentContainer->AddChild(column);
        content();
        buildContext.pop_back();
    }

    class TextWidget : public Widget
    {
    public:
        TextWidget(std::string &&text) : text(text), Widget() {}

        size_t GetTextSize() const
        {
            return text.size();
        }

    private:
        std::string text;
        static YGSize MeasureText(
            YGNodeConstRef node,
            float width,
            YGMeasureMode widthMode,
            float height,
            YGMeasureMode heightMode)
        {
            auto textWidget = (TextWidget *)YGNodeGetContext(node);
            float a = (float)textWidget->GetTextSize();
            float b = 30.0f;

            return {a, b};
        }
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
                auto root = comppose::buildContext.at(0);
                root->SetWidth(width);
                root->SetHeight(height);
            }
        }

        window.clear(sf::Color::Black);

        Comppose();

        window.display();
    }
}
