
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <sstream>


template <typename K>
class RBTree;

template <typename U>
std::string value_to_string(const U& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

template <typename T>
class Visualizer {
    public:
        T &tree;
    public:
        Visualizer(T &tree) : tree(tree) {}
        //operator call overloading
        void operator()() {
            visualize();
        }
    private:
        void visualize() const {
            sf::RenderWindow window(
                sf::VideoMode({1200, 800}),
                "BST Visualization"
            );
        
            sf::Font font;

            if (!font.openFromFile("assets/Roboto.ttf")) {
                std::cerr << "Could not load font!\n";
                std::cerr << "Make sure DejaVuSans.ttf is in the working directory.\n";
                return;
            }
        
            while (window.isOpen()) {
                while (auto event = window.pollEvent()) {
                    if (event->is<sf::Event::Closed>())
                        window.close();
                }
        
                window.clear(sf::Color::White);
        
                if (tree.root != nullptr) {
                    draw_tree(window, tree.root, 600.f, 80.f, 150.f, font);
                }
        
                window.display();
            }
        }
        template <typename U>
        void draw_tree(sf::RenderWindow& window, U * node, float x, float y, float horizontal_distance, const sf::Font& font) const {
            
            if (node == nullptr)
                return;
        
            constexpr float radius = 25.f;
            constexpr float vertical_distance = 80.f;
        
            float left_x  = x - horizontal_distance;
            float right_x = x + horizontal_distance;
            float child_y = y + vertical_distance;
        
            // Draw connections
            if (node->left != nullptr) {
                draw_line(window, x, y, left_x, child_y);
            }
        
            if (node->right != nullptr) {
                draw_line(window, x, y, right_x, child_y);
            }
        
            // Draw left subtree
            draw_tree(
                window,
                node->left,
                left_x,
                child_y,
                horizontal_distance / 2,
                font
            );
        
            // Draw right subtree
            draw_tree(
                window,
                node->right,
                right_x,
                child_y,
                horizontal_distance / 2,
                font
            );
        
            // Draw node
            sf::CircleShape circle(radius);
        
            circle.setPosition({
                x - radius,
                y - radius
            });
        
            circle.setFillColor(sf::Color(70, 130, 180));
        
            window.draw(circle);
        
            // Draw value
            sf::Text text(font, std::to_string(node->val), 20);
        
            text.setFillColor(sf::Color::White);
        
            auto bounds = text.getLocalBounds();
        
            text.setOrigin({
                bounds.position.x + bounds.size.x / 2.f,
                bounds.position.y + bounds.size.y / 2.f
            });
        
            text.setPosition({x, y});
        
            window.draw(text);
        }
        void draw_line(sf::RenderWindow& window, float x1, float y1, float x2, float y2) const {
            
            float dx = x2 - x1;
            float dy = y2 - y1;
        
            float length = std::sqrt(dx * dx + dy * dy);
            float angle = std::atan2(dy, dx) * 180.f / 3.14159265f;
        
            sf::RectangleShape line({length, 2.f});
        
            line.setPosition({x1, y1});
            line.setRotation(sf::degrees(angle));
        
            line.setFillColor(sf::Color::Black);
        
            window.draw(line);
        }
    
};


// Explicit class template specialization for RBTree
template <typename K>
class Visualizer<RBTree<K>> {
    public:
        const RBTree<K> &tree;

        Visualizer(const RBTree<K> &tree) : tree(tree) {}

        void operator()() {
            visualize();
        }

    private:
        void visualize() const {
            sf::RenderWindow window(
                sf::VideoMode({1200, 800}),
                "Red-Black Tree Visualization"
            );
        
            sf::Font font;

            if (!font.openFromFile("assets/Roboto.ttf")) {
                std::cerr << "Could not load font!\n";
                return;
            }
        
            while (window.isOpen()) {
                while (auto event = window.pollEvent()) {
                    if (event->is<sf::Event::Closed>())
                        window.close();
                }
        
                window.clear(sf::Color::White);
        
                if (tree.getRoot() != nullptr) {
                    draw_tree(window, tree.getRoot(), 600.f, 80.f, 150.f, font);
                }
        
                window.display();
            }
        }

        template <typename NodePtr>
        void draw_tree(
            sf::RenderWindow& window,
            NodePtr node,
            float x,
            float y,
            float horizontal_distance,
            const sf::Font& font
        ) const {
            // STOP RECURSION IF NODE IS NULL OR SENTINEL NIL
            if (node == nullptr || node == tree.getNIL())
                return;
        
            constexpr float min_radius = 25.f;
            constexpr float padding = 10.f;
            constexpr float vertical_distance = 80.f;
        
            float left_x = x - horizontal_distance;
            float right_x = x + horizontal_distance;
            float child_y = y + vertical_distance;
        
            // Draw connections only to non-NIL children
            if (node->left != nullptr && node->left != tree.getNIL()) {
                draw_line(window, x, y, left_x, child_y);
            }
        
            if (node->right != nullptr && node->right != tree.getNIL()) {
                draw_line(window, x, y, right_x, child_y);
            }
        
            // Recursively draw children
            draw_tree(window, node->left, left_x, child_y, horizontal_distance / 2.f, font);
            draw_tree(window, node->right, right_x, child_y, horizontal_distance / 2.f, font);
        
            // Render Node
            sf::Text text(font, value_to_string(node->val), 20);
            text.setFillColor(sf::Color::White);
        
            auto bounds = text.getLocalBounds();
            text.setOrigin({
                bounds.position.x + bounds.size.x / 2.f,
                bounds.position.y + bounds.size.y / 2.f
            });
            text.setPosition({x, y});
        
            float radius = std::max(min_radius, std::max(bounds.size.x, bounds.size.y) / 2.f + padding);
        
            sf::CircleShape circle(radius);
            circle.setPosition({x - radius, y - radius});
        
            if (node->color == Color::RED) {
                circle.setFillColor(sf::Color(220, 20, 60));  // Red
            } else {
                circle.setFillColor(sf::Color(30, 30, 30));    // Black
            }
        
            window.draw(circle);
            window.draw(text);
        }

        void draw_line(sf::RenderWindow& window, float x1, float y1, float x2, float y2) const {
            float dx = x2 - x1;
            float dy = y2 - y1;
        
            float length = std::sqrt(dx * dx + dy * dy);
            float angle = std::atan2(dy, dx) * 180.f / 3.14159265f;
        
            sf::RectangleShape line({length, 2.f});
            line.setPosition({x1, y1});
            line.setRotation(sf::degrees(angle));
            line.setFillColor(sf::Color::Black);
        
            window.draw(line);
        }
};