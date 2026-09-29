#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int FPS_LIMIT = 30;

// global tween function
std::function<float(float, float, float)> tween = [](float a, float b, float t) {
    return (1 - t) * a + t * b;
};

void handleInput(sf::Window& window, bool& shouldQuit) {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
            shouldQuit = true;
        }

        // ====== ====== ======
        // TODO: (Q2)
        //  implement key presses (1-9) that replace the tween function
        //  with different alternate tween functions.
        //  Functions can be from lecture or from https://easings.net/#
        // ====== ====== ======
        //
      if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
          if (keyPressed->code == sf::Keyboard::Key::Num1) {

            tween = [](float a, float b, float t) {
              return (1 - t) * a + t * b;
            };

          }

          // key 2 
          else if (keyPressed->code == sf::Keyboard::Key::Num2){
            tween = [](float a, float b, float t) {
              const float con = (2.0f * M_PI) / 3.0f;

              float easedT = (t == 0.0f) ? 0.0f :
                             (t == 1.0f) ? 1.0f :
                             -std::pow(2.0f, 10.0f * t - 10.0f) * std::sin((t * 10.0f - 10.75) * con);

              return (1.0f - easedT) * a + easedT * b;
            };
          }

          // key 3
          else if (keyPressed->code == sf::Keyboard::Key::Num3) {
            tween = [](float a, float b, float t) {
              float easedT = std::sin((t * M_PI) / 2);
              
              return (1.0f - easedT) * a + easedT * b;
            };
          }

          // Key 4
          else if (keyPressed->code == sf::Keyboard::Key::Num4){
            tween = [](float a, float b, float t) {
              float easedT = - (std::sin((t * M_PI) - 1)) / 2;
              
              return (1.0f - easedT) * a + easedT * b;
            };
          }
          
           // Key 5
            else if (keyPressed->code == sf::Keyboard::Key::Num5) {
              tween = [](float a, float b, float t) {
                float easedT = (t == 1.0f) ? 1.0f :
                         1.0f - std::pow(2.0f, -10.0f * t);

                return (1.0f - easedT) * a + easedT * b;

              };
          }

             // Key 6
            else if (keyPressed->code == sf::Keyboard::Key::Num6) {
              tween = [](float a, float b, float t) {
                const float c1 = 1.70158;
                const float c3 = c1 + 1.0f;

                float easedT = c3 * t * t * t - c1 * t * t;

                return (1.0f - easedT) * a + easedT * b;

              };
            }

             // Key 7
            else if (keyPressed->code == sf::Keyboard::Key::Num7) {
              tween = [](float a, float b, float t) {
                float easedT = (t < 0.5f) ? 8.0f * t * t * t * t :
                               1 - std::pow(-2.0f * t + 2.0f, 4.0f) / 2.0f;

                return (1.0f - easedT) * a + easedT * b;

              };
            }

             // Key 8
            else if (keyPressed->code == sf::Keyboard::Key::Num8) {
              tween = [](float a, float b, float t) {
                float easedT = std::sqrt(1.0f - std::pow(t - 1.0f, 2.0f));
                return (1.0f - easedT) * a + easedT * b;

              };
            }

             // Key 9
            else if (keyPressed->code == sf::Keyboard::Key::Num9) {
              tween = [](float a, float b, float t) {
                float easedT = 1.0f - (1.0f - t) * (1.0f - t);

                return (1.0f - easedT) * a + easedT * b;

              };
            }



          }
        }
          
        }
      


void render(sf::RenderWindow& window) {
    // Clear with blue background (sky)
    window.clear(sf::Color::Black);
    // ====== ====== ======
    // TODO: (Q1) Draw circle that moves between
    // the left/right half of the screen.
    // Movement should be governed by the tween function.
    // ====== ====== ======
    const int fpa = 120;
    static int frames = 0;
    frames++;

    float t = static_cast<float>(frames % fpa) / static_cast<float>(fpa);

    float startingX = 50.0f;
    float finalX = WINDOW_WIDTH - 50.0f;

    float currX = tween(startingX, finalX, t);
    float currY =  WINDOW_HEIGHT / 3.0f;

    // draw the circle
    sf::CircleShape circle(15.0f);
    circle.setOrigin(sf::Vector2f(15.0f, 15.0f));
    circle.setPosition(sf::Vector2f(currX, currY));
    circle.setFillColor(sf::Color::Green);
    window.draw(circle);

    // ====== ====== ======
    // TODO: (Q3) Draw tween function graph with a dot
    // on the current portion of the curve
    // ====== ====== ======

    float graphX = 100.0f;
    float graphY = WINDOW_HEIGHT - 400.0f;
    float graphWidth = 600.0f;
    float graphHeight = 300.0f;

    sf::RectangleShape graphBox(sf::Vector2f(graphWidth, graphHeight));
    graphBox.setPosition(sf::Vector2f(graphX, graphY));
    graphBox.setFillColor(sf::Color::Black); // Dark grey background
    graphBox.setOutlineColor(sf::Color::White);
    window.draw(graphBox);

    sf::RectangleShape yAxis(sf::Vector2f(1.0f, graphHeight));
    yAxis.setPosition(sf::Vector2f(graphX, graphY));
    yAxis.setFillColor(sf::Color::White);
    window.draw(yAxis);

    sf::RectangleShape xAxis(sf::Vector2f(graphWidth, 1.0f));
    xAxis.setPosition(sf::Vector2f(graphX, graphY + graphHeight));
    xAxis.setFillColor(sf::Color::White);
    window.draw(xAxis);

    const int numSteps = 100;
    std::vector<sf::Vector2f> points;

    for (int i = 0; i <= numSteps; ++i) {
        float u = static_cast<float>(i) / static_cast<float>(numSteps);
        float v = tween(0.0f, 1.0f, u);

        float screenX = graphX + (u * graphWidth);
        float screenY = graphY + graphHeight - (v * graphHeight);

        points.push_back(sf::Vector2f(screenX, screenY));
    }

    for (size_t i = 0; i < points.size() - 1; ++i) {
        sf::CircleShape stepDot(1.5f);
        stepDot.setPosition(points[i]);
        stepDot.setFillColor(sf::Color::Cyan);
        window.draw(stepDot);
    }

    float currentM = tween(0.0f, 1.0f, t);
    sf::Vector2f trackingPos(
        graphX + (t * graphWidth),
        graphY + graphHeight - (currentM * graphHeight)
    );

    sf::CircleShape trackingDot(5.0f);
    trackingDot.setOrigin(sf::Vector2f(5.0f, 5.0f));
    trackingDot.setPosition(trackingPos);
    trackingDot.setFillColor(sf::Color::Red);
    window.draw(trackingDot);


    window.display();
}

int main() {
    sf::RenderWindow window;

    try {
        // Initialize window
        window.create(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Tween");
        window.setFramerateLimit(FPS_LIMIT);
        // Prevent key repeats.
        window.setKeyRepeatEnabled(false);

        bool shouldQuit = false;
        // Main game loop
        while (window.isOpen()) {
            handleInput(window, shouldQuit);
            if (shouldQuit) {
                break;
            }
            render(window);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}
