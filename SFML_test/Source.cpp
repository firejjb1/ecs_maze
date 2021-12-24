#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

class Shape 
{
public:
	int rgb[3];
	float x;
	float y;
	float vX;
	float vY;
	std::string name;
	Shape(std::string name, int rgb[3], float x, float y, float vX, float vY) : name{ name }, x { x }, y{ y }, vX{ vX }, vY{ vY }
	{
		this->rgb[0] = rgb[0];
		this->rgb[1] = rgb[1];
		this->rgb[2] = rgb[2];
	}
}; 

class Circle : public Shape 
{
public:
	float radius;
	Circle(std::string name, int rgb[3], float x, float y, float vX, float vY, float rad) :
		Shape(name, rgb, x, y, vX, vY), radius{ rad }
	{}
};

class Rectangle : public Shape 
{
public:
	float width;
	float height;
	Rectangle(std::string name, int rgb[3], float x, float y, float vX, float vY, float w, float h) :
		Shape(name, rgb, x, y, vX, vY), width{x}, height{h}
	{}
};

class Config 
{
public:
	int wWidth;
	int wHeight;
	std::string fontFile;
	int fontSize;
	int fontRGB[3];
	std::vector<Shape> shapes;
	std::vector<Circle> circles;
	std::vector<Rectangle> rectangles;

	Config(std::string filepath) 
	{
		std::ifstream fin(filepath);
		
		std::string type;
		while (fin >> type)
		{
			if (type == "Window")
			{
				fin >> wWidth;
				fin >> wHeight;
			}
			else if (type == "Font")
			{
				fin >> fontFile;
				fin >> fontSize;
				fin >> fontRGB[0];
				fin >> fontRGB[1];
				fin >> fontRGB[2];
				
			}
			else if (type == "Rectangle")
			{
				// 200 200 0.1 0.15 255 0 0 50 25
				int r, g, b;
				float x, y, vX, vY, w, h;
				std::string name;
				fin >> name >> x >> y >> vX >> vY >> r >> g >> b >> w >> h;
				int rgb[3] = { r, g, b };
				Rectangle rect(name, rgb, x, y, vX, vY, w, h);
				shapes.push_back(rect);
				rectangles.push_back(rect);
			}
			else if (type == "Circle")
			{
				int r, g, b;
				float vX, vY, radius, x, y;
				std::string name;
				fin >> name >> x >> y >> vX >> vY >> r >> g >> b >> radius;
				int rgb[3] = { r, g, b };
				Circle circle(name, rgb, x, y, vX, vY, radius);
				shapes.push_back(circle);
				circles.push_back(circle);
			}
			else 
			{
				std::cerr << "Could not load config of type: " << type << "\n";
				exit(-1);
				break;
			}
			
		}
	}
};

void initializeCircles(std::vector<Circle> circles, std::vector<sf::CircleShape> &circleShapes, 
	std::vector<sf::Vector2f> &moveSpeeds,
	std::vector<sf::Text> &circleTexts, sf::Font &myFont, Config config) {
	for (auto circle : circles)
	{
		sf::CircleShape c(circle.radius);
		c.setFillColor(sf::Color(circle.rgb[0], circle.rgb[1], circle.rgb[2]));
		c.setPosition(circle.x, circle.y);
		sf::Vector2f circleMoveSpeed(circle.vX, circle.vY);
		
		sf::Text text(circle.name, myFont, config.fontSize);
		// center the text
		// for x: margin*2 + width  = circleWidth; margin = radius  - width / 2 
		float marginX = circle.radius - text.getLocalBounds().width / 2.f;
		float marginY = circle.radius - text.getCharacterSize() / 2.f;
		text.setPosition(circle.x + marginX, circle.y + marginY);
		text.setFillColor(sf::Color(config.fontRGB[0], config.fontRGB[1], config.fontRGB[2]));

		circleShapes.push_back(c);
		circleTexts.push_back(text);
		moveSpeeds.push_back(circleMoveSpeed);
	}

}
/**
int main() {
	Config config("config.txt");
	const int wWidth = config.wWidth;
	const int wHeight = config.wHeight;

	sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "Test");

	sf::Font myFont;

	if (!myFont.loadFromFile(config.fontFile))
	{
		std::cerr << "Could not load font\n";
		exit(-1);
	}

	Circle circle = config.circles[0];
	std::vector<sf::CircleShape> circles;
	std::vector<sf::Text> circleTexts;
	std::vector<Rectangle> rectangles;
	std::vector<sf::Text> rectangleTexts;
	std::vector<sf::Vector2f> circleMoveSpeeds;

	initializeCircles(config.circles, circles, circleMoveSpeeds, circleTexts, myFont, config);

	sf::Event e;
	
	while (window.isOpen())
	{
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
			if (e.type == sf::Event::KeyPressed)
				std::cout << "key pressed: " << e.key.code << "\n";
	
		}
		window.clear();

		for (int i = 0; i < circles.size(); i++) {
			sf::CircleShape &c = circles[i];
			sf::Text &text = circleTexts[i];
			sf::Vector2f &circleMoveSpeed = circleMoveSpeeds[i];
			// collision

			if (c.getGlobalBounds().intersects(sf::FloatRect(0.f, 0.f, 1.f, wHeight)) && circleMoveSpeed.x < 0.f) {
				circleMoveSpeed.x *= -1.f;
			}
			if (c.getGlobalBounds().intersects(sf::FloatRect(wWidth, 0.f, 1.f, wHeight)) && circleMoveSpeed.x > 0.f)
			{
				circleMoveSpeed.x *= -1.f;
			}
			if (c.getGlobalBounds().intersects(sf::FloatRect(0.f, 0.f, wWidth, 1.f)) && circleMoveSpeed.y < 0.f)
			{
				circleMoveSpeed.y *= -1.f;
			}
			if (c.getGlobalBounds().intersects(sf::FloatRect(0.f, wHeight, wWidth, 1.f)) && circleMoveSpeed.y > 0.f)
			{
				circleMoveSpeed.y *= -1.f;
			}
			c.setPosition(c.getPosition() + circleMoveSpeed);

			text.setPosition(text.getPosition() + circleMoveSpeed);

			window.draw(c);
			window.draw(text);
	
		}
		window.display();
	
	}
	return 0;
}*/
