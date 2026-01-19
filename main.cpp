#include <SFML/Graphics.hpp>
#include <vector>
#include <random>


const int WinWidth = 600;
const int WinHeight = 800;

const sf::Color SkyColor = sf::Color(0, 26, 56);
const sf::Color SprusColor = sf::Color(61, 108, 81);
const sf::Color SprusOutlineColor = sf::Color(45, 78, 71);
const sf::Color TrunkColor = sf::Color(115, 81, 65);
const sf::Color TrunkOutlineColor = sf::Color(102, 73, 58);
const sf::Color SnowColor = sf::Color(163, 188, 203);
const sf::Color SnowOutlineColor = sf::Color(82, 121, 164);
const sf::Color RibbonColor = sf::Color(252, 225, 0);
const sf::Color RibbonOutlineColor = sf::Color(252, 203, 0);
const sf::Color StarColor = sf::Color(242, 223, 31);
const sf::Color StarOutlineColor = sf::Color(247, 234, 104);

sf::Color randomBrightColor() {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(150, 255);

    return {static_cast<sf::Uint8>(dist(gen)), static_cast<sf::Uint8>(dist(gen)), static_cast<sf::Uint8>(dist(gen))};
}


struct Triangle {
    float size = static_cast<float>(WinHeight) / 3;
    float posX{};
    float posY{};
    sf::Color color;
    sf::Color outlineColor;
    sf::CircleShape shape;
};

struct SprusSteps {
    float posX{};
    float posY{};
    std::vector<Triangle> sprusSteps;
};

Triangle couseTriangle(float size, float posX, float posY, sf::Color color, sf::Color outlineColor) {
    sf::CircleShape triangle(size, 3);
    triangle.setPosition(sf::Vector2f(posX, posY));
    triangle.setOutlineColor(outlineColor);
    triangle.setOutlineThickness(5.f);
    triangle.setFillColor(color);
    Triangle t;
    t.size = size;
    t.posX = posX;
    t.posY = posY;
    t.color = color;
    t.outlineColor = outlineColor;
    t.shape = triangle;
    return t;
}


SprusSteps couseSprusSteps(float posX, float posY) {
    SprusSteps s;
    s.posX = posX;
    s.posY = posY;

    for (int i = 0; i < 6; i++) {
        float size = static_cast<float>(WinWidth) / 3 - i * 40;
        float posX = s.posX + i * 40;
        float posY = s.posY - i * 30;
        sf::Color color = SprusColor;
        sf::Color outlineColor = SprusOutlineColor;
        Triangle t = couseTriangle(size, posX, posY, color, outlineColor);
        s.sprusSteps.push_back(t);
    }

    return s;
}

struct Rectangle {
    float sizeX;
    float sizeY;
    float posX;
    float posY;
    sf::Color color;
    sf::Color outlineColor;
    sf::RectangleShape shape;
};

Rectangle couseRectangle(float sizeX, float sizeY, float posX, float posY, sf::Color color, sf::Color outlineColor) {
    Rectangle rect;
    rect.sizeX = sizeX;
    rect.sizeY = sizeY;
    rect.posX = posX;
    rect.posY = posY;
    rect.color = color;
    rect.outlineColor = outlineColor;
    sf::RectangleShape r;
    r.setSize(sf::Vector2f(rect.sizeX, rect.sizeY));
    r.setPosition(sf::Vector2f(posX, posY));
    r.setOutlineThickness(5.f);
    r.setOutlineColor(outlineColor);
    r.setFillColor(color);
    rect.shape = r;
    return rect;
}

struct Circle {
    float radius;
    sf::Vector2f pos;
    sf::Color color;
    sf::Color outlineColor;
    sf::CircleShape shape;
};

Circle couseCircle(float radius, sf::Vector2f pos, sf::Color color, sf::Color outlineColor) {
    Circle c;
    c.radius = radius;
    c.pos = pos;
    c.color = color;
    c.outlineColor = outlineColor;
    c.shape.setRadius(radius);
    c.shape.setPosition(pos);
    c.shape.setOutlineColor(outlineColor);
    c.shape.setOutlineThickness(5.f);
    c.shape.setFillColor(color);
    return c;
}

struct SnowHills {
    sf::Vector2f pos1;
    sf::Vector2f pos2;
    sf::Vector2f pos3;
    std::vector<Circle> snowHills;
};

SnowHills couseSnowHills(float radius, sf::Vector2f pos1, sf::Vector2f pos2, sf::Vector2f pos3, sf::Color color,
                         sf::Color outlineColor) {
    SnowHills s;
    s.pos1 = pos1;
    s.pos2 = pos2;
    s.pos3 = pos3;
    s.snowHills.push_back(couseCircle(radius, pos1, color, outlineColor));
    s.snowHills.push_back(couseCircle(radius, pos2, color, outlineColor));
    s.snowHills.push_back(couseCircle(radius, pos3, color, outlineColor));
    return s;
}

struct Present {
    sf::Vector2f totalSize;
    sf::Vector2f totalPos;
    std::vector<Rectangle> presents;
};

Present cousePresent(sf::Vector2f totalSize, sf::Vector2f totalPos, sf::Color color, sf::Color outlineColor) {
    Present p;
    float sizeX = totalSize.x - 10;
    p.presents.push_back(couseRectangle(sizeX / 4, totalSize.y, totalPos.x + totalSize.x / 2,
                                        totalPos.y + totalSize.y / 10, RibbonColor, RibbonOutlineColor));
    p.presents.push_back(couseRectangle(sizeX / 4, totalSize.y, totalPos.x + totalSize.x / 2,
                                        totalPos.y + totalSize.y / 10, RibbonColor, RibbonOutlineColor));
    p.presents[0].shape.setOrigin(p.presents[0].shape.getSize().x / 2, p.presents[0].shape.getSize().y / 2);
    p.presents[0].shape.rotate(-45);
    p.presents[1].shape.setOrigin(p.presents[1].shape.getSize().x / 2, p.presents[1].shape.getSize().y / 2);
    p.presents[1].shape.rotate(45);
    p.presents.push_back(couseRectangle(sizeX, totalSize.y, totalPos.x + (totalSize.x - sizeX) / 2, totalPos.y, color,
                                        outlineColor));
    p.presents.push_back(couseRectangle(totalSize.x, totalSize.y / 3, totalPos.x, totalPos.y, color, outlineColor));
    p.presents.push_back(couseRectangle(sizeX / 4, totalSize.y, totalPos.x + (totalSize.x - sizeX / 4) / 2, totalPos.y,
                                        RibbonColor, RibbonOutlineColor));
    return p;
}

struct SnowFlake {
    sf::Text text;
    sf::Vector2f velosity;
    float driftTime;
};

SnowFlake couseSnowFlakes(sf::Font font, float with) {
    std::mt19937 gen(std::random_device{}());

    std::uniform_real_distribution<float> size(-10.f, 20.f);
    std::uniform_real_distribution<float> drift(-20.0f, 20.0f);
    std::uniform_real_distribution<float> speed(0.1f, 100.0f);
    std::uniform_real_distribution<float> posX(0, with);

    SnowFlake s;
    s.text.setString("*");
    s.text.setFont(font);
    s.text.setCharacterSize(size(gen));
    s.text.setFillColor(sf::Color::White);
    s.text.setPosition(posX(gen), speed(gen));
    s.velosity = sf::Vector2f(drift(gen), speed(gen));
    s.driftTime = drift(gen);


    return s;
}

void snowUpdate(SnowFlake &s, float dt) {
    s.driftTime += dt;

    float wind = std::sin(s.driftTime * 2) * 2;

    s.text.move((s.velosity.x + wind) * dt, s.velosity.y * dt);
}

void respawnSnowFlake(SnowFlake &s, float height, float width) {
    if (s.text.getPosition().x > height) {
        s.text.setPosition(static_cast<float>(std::rand() % static_cast<int>(width)), -20.f);
    }
}

struct Star {
    sf::Vector2f radius; // radius.x = inner, radius.y = outer
    sf::Vector2f pos; // center position
    sf::Color color;
    sf::Color outlineColor;
    sf::ConvexShape shape;
};

Star couseStar(sf::Vector2f radius, sf::Vector2f pos, sf::Color color, sf::Color outlineColor) {
    const float PI = 3.14159265f;
    Star s;
    s.radius = radius;
    s.pos = pos;
    s.color = color;
    s.outlineColor = outlineColor;

    s.shape.setPointCount(10); // 5 outer + 5 inner points

    for (int i = 0; i < 10; i++) {
        float angle = i * 2 * PI / 10 - PI / 2 + PI; // start pointing up
        float r = (i % 2 == 0) ? radius.y : radius.x; // alternate outer/inner
        float x = pos.x + std::cos(angle) * r;
        float y = pos.y + std::sin(angle) * r;
        s.shape.setPoint(i, sf::Vector2f(x, y));
    }

    s.shape.setFillColor(color);
    s.shape.setOutlineColor(outlineColor);
    s.shape.setOutlineThickness(5.f);

    return s;
}

// struct CristmasBauble {
//     sf::Vector2f size;
//     sf::Vector2f pos;
//     sf::Color color;
//     sf::Color outlineColor;
//     std::vector<sf::Shape*> shape;
// };
// std::vector<sf::Shape*> couseCristmasBauble(sf::Vector2f size, sf::Vector2f pos, sf::Color color, sf::Color outlineColor) {
//     CristmasBauble b;
//     b.size = size;
//     b.pos = pos;
//     b.color = color;
//     b.outlineColor = outlineColor;
//     Rectangle r = couseRectangle(size.x/10,size.y/2, pos.x,pos.y, RibbonColor, RibbonOutlineColor);
//     r.shape.setOrigin(r.shape.getSize().x / 2, 0);
//     r.shape.setPosition(pos.x + b.size.x / 2, 0);
//     Circle c = couseCircle(size.x, pos, b.color, b.outlineColor);
//     c.shape.setOrigin(c.shape.getRadius()/2, c.shape.getRadius()/2);
//     c.shape.setPosition(pos.x + b.size.x / 2, pos.y + b.size.y / 2);
//     std::vector<sf::Shape*> shape;
//     shape.push_back(&r.shape);
//     shape.push_back(&c.shape);
//     return shape;
// }
struct CristmasBauble {
    Rectangle ribbon;
    Circle ball;

    void draw(sf::RenderWindow &win) const {
        win.draw(ribbon.shape);
        win.draw(ball.shape);
    }
};

CristmasBauble couseCristmasBauble(
    sf::Vector2f size,
    sf::Vector2f pos,
    sf::Color color,
    sf::Color outlineColor
) {
    CristmasBauble b;

    b.ribbon = couseRectangle(
        size.x / 10, size.y / 2,
        pos.x, pos.y,
        RibbonColor, RibbonOutlineColor
    );
    b.ribbon.shape.setOrigin(b.ribbon.shape.getSize().x / 2, 0);
    b.ribbon.shape.setPosition(pos.x + size.x / 2, pos.y - size.y / 4);

    b.ball = couseCircle(size.x / 2, pos, color, outlineColor);
    b.ball.shape.setOrigin(
        b.ball.shape.getRadius(),
        b.ball.shape.getRadius()
    );
    b.ball.shape.setPosition(
        pos.x + size.x / 2,
        pos.y + size.y / 2
    );

    return b;
}

int main() {
    sf::RenderWindow win(sf::VideoMode(WinWidth, WinHeight), "Swierk");


    SprusSteps s = couseSprusSteps(WinWidth / 2 - static_cast<float>(WinWidth) / 3, WinHeight / 3);
    Rectangle trunk = couseRectangle(WinWidth / 12, WinHeight / 2,
                                     s.sprusSteps[0].posX + s.sprusSteps[0].size - WinWidth / 24, s.sprusSteps[0].posY,
                                     TrunkColor, TrunkOutlineColor);
    SnowHills snowHills = couseSnowHills(700, {trunk.posX - 200, static_cast<float>(trunk.posY + trunk.sizeY * 0.7)},
                                         {trunk.posX - 800, static_cast<float>(trunk.posY + trunk.sizeY * 0.7)}, {
                                             trunk.posX - 60, static_cast<float>(trunk.posY + trunk.sizeY * 0.9)
                                         }, SnowColor, SnowOutlineColor);
    sf::Color randBrightColor = randomBrightColor();
    Present p = cousePresent({120, 75}, {130, 600}, randBrightColor,
                             sf::Color(randBrightColor.r - 20, randBrightColor.g - 20, randBrightColor.b - 20));
    randBrightColor = randomBrightColor();
    Present p1 = cousePresent({60, 60}, {360, 600}, randBrightColor,
                              sf::Color(randBrightColor.r - 20, randBrightColor.g - 20, randBrightColor.b - 20));
    randBrightColor = randomBrightColor();
    Present p2 = cousePresent({90, 90}, {270, 600}, randBrightColor,
                              sf::Color(randBrightColor.r - 20, randBrightColor.g - 20, randBrightColor.b - 20));
    Star star = couseStar({40, 20}, {s.sprusSteps[5].posX, s.sprusSteps[5].posY}, StarColor, StarOutlineColor);

    std::vector<CristmasBauble> baubles;

    for (int i = 0; i < 5; i++) {
        randBrightColor = randomBrightColor();
        baubles.push_back(
            couseCristmasBauble({25, 25}, {star.pos.x + i * 30 - 15, star.pos.y + i * 90 + 60}, randBrightColor,
                                sf::Color(randBrightColor.r - 20, randBrightColor.g - 20, randBrightColor.b - 20))
        );
        randBrightColor = randomBrightColor();
        baubles.push_back(
            couseCristmasBauble({25, 25}, {star.pos.x - i * 30 - 15, star.pos.y + i * 90 + 60}, randBrightColor,
                                sf::Color(randBrightColor.r - 20, randBrightColor.g - 20, randBrightColor.b - 20))
        );
    }
    for (int i = 0; i < 3; i++) {
        randBrightColor = randomBrightColor();
        baubles.push_back(
            couseCristmasBauble({25, 25}, {star.pos.x + i * 30 - 15, star.pos.y + i * 90 + 200}, randBrightColor,
                                sf::Color(randBrightColor.r - 20, randBrightColor.g - 20, randBrightColor.b - 20))
        );
        randBrightColor = randomBrightColor();
        baubles.push_back(
            couseCristmasBauble({25, 25}, {star.pos.x - i * 30 - 15, star.pos.y + i * 90 + 200}, randBrightColor,
                                sf::Color(randBrightColor.r - 20, randBrightColor.g - 20, randBrightColor.b - 20))
        );
    }
    for (int i = 0; i < 2; i++) {
        randBrightColor = randomBrightColor();
        baubles.push_back(
            couseCristmasBauble({25, 25}, {star.pos.x + i * 30 - 15, star.pos.y + i * 90 + 340}, randBrightColor,
                                sf::Color(randBrightColor.r - 20, randBrightColor.g - 20, randBrightColor.b - 20))
        );
        randBrightColor = randomBrightColor();
        baubles.push_back(
            couseCristmasBauble({25, 25}, {star.pos.x - i * 30 - 15, star.pos.y + i * 90 + 340}, randBrightColor,
                                sf::Color(randBrightColor.r - 20, randBrightColor.g - 20, randBrightColor.b - 20))
        );
    }


    std::vector<SnowFlake> snow;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // handle error
        return -1;
    }
    for (int i = 0; i < 2048; i++) {
        snow.push_back(couseSnowFlakes(font, WinWidth));
    }
    sf::Clock clock;


    while (win.isOpen()) {
        float dt = clock.restart().asSeconds();

        sf::Event event;
        while (win.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                win.close();

        }
        for (auto &s: snow) {
            snowUpdate(s, dt);
            respawnSnowFlake(s, WinHeight, WinWidth);
        }
        win.clear(SkyColor);

        for (int i = 0; i < static_cast<int>(snowHills.snowHills.size()); i++) {
            win.draw(snowHills.snowHills[i].shape);
        }
        win.draw(trunk.shape);
        for (int i = 0; i < static_cast<int>(s.sprusSteps.size()); i++) {
            win.draw(s.sprusSteps[i].shape);
        }
        for (int i = 0; i < static_cast<int>(p1.presents.size()); i++) {
            win.draw(p.presents[i].shape);
            win.draw(p1.presents[i].shape);
            win.draw(p2.presents[i].shape);
        }
        win.draw(star.shape);
        for (const auto &b: baubles) {
            b.draw(win);
        }


        for (auto &s: snow)
            win.draw(s.text);

        win.display();
    }
    return 0;
}
