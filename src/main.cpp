#include <SFML/Graphics.hpp>

sf::RenderWindow window;
sf::VertexBuffer vertexBuffer(sf::PrimitiveType::TriangleStrip, sf::VertexBuffer::Usage::Dynamic);
sf::Shader fragmentShader;
sf::View camera;


sf::Clock frameTimer;
double timeSinceLastFrame = 0;

float zoom = 1.0f;

float iterations = 100.0f;

void uploadVertexbuffer() {
	
	sf::Vertex verticies[4];
	verticies[0].position = sf::Vector2f(0 , 0);
	verticies[1].position = sf::Vector2f(window.getSize().x, 0);
	verticies[2].position = sf::Vector2f(0, window.getSize().y);
	verticies[3].position = sf::Vector2f(window.getSize().x,window.getSize().y);


	verticies[0].texCoords = sf::Vector2f(-2.5f,1.0f);
	verticies[1].texCoords = sf::Vector2f(1.f,1.0f);
	verticies[2].texCoords = sf::Vector2f(-2.5f,-1.0f);
	verticies[3].texCoords = sf::Vector2f(1.f,-1.0f);

	vertexBuffer.update(verticies);
}


void setup() {
	window.create(sf::VideoMode(1280,720), "Mandelbrotmenge", sf::Style::Default);

	vertexBuffer.create(4);
	uploadVertexbuffer();
	camera = window.getDefaultView();
	window.setView(camera);
	fragmentShader.loadFromFile("../../shader/shader.frag",sf::Shader::Fragment);
}

void update(const sf::Event& events) {
	switch (events.type)
	{
	case sf::Event::KeyPressed: {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			camera.move(sf::Vector2f(0.0f, -.15f * zoom / timeSinceLastFrame));
			window.setView(camera);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			camera.move(sf::Vector2f(0.0f, .15f * zoom / timeSinceLastFrame));
			window.setView(camera);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			camera.move(sf::Vector2f(-.15f * zoom / timeSinceLastFrame, 0.0f));
			window.setView(camera);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			camera.move(sf::Vector2f(.15f * zoom / timeSinceLastFrame, 0.0f));
			window.setView(camera);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			iterations += timeSinceLastFrame / 1000;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {

			iterations -= timeSinceLastFrame / 1000;
		}

		break;
	}
	case sf::Event::MouseWheelScrolled: {

		if (events.mouseWheelScroll.delta > 0) {
			camera.zoom(0.833333);
			zoom *= 0.833333;
		}
		else {
			if (zoom < .9f) {
				camera.zoom(1.2);
				zoom *= 1.2;
			}
		}

		window.setView(camera);
		break;
	}


	default:
		break;
	}

}

void draw() {
	fragmentShader.setUniform("maxIteration", iterations);
	window.draw(vertexBuffer,&fragmentShader);
}

int main() {

	setup();

	while (window.isOpen()) {

		sf::Event events;
		while (window.pollEvent(events)) {
			switch (events.type)
			{
			case sf::Event::Closed:

				window.close();
				break;

			case sf::Event::KeyPressed: {
				update(events);
				break;
			}
			case sf::Event::MouseWheelScrolled: {
				update(events);
				break;
			}
			
			default:
				break;
			}

		}

		window.clear(sf::Color(30,30,30,255));
		draw();
		window.display();
		timeSinceLastFrame = frameTimer.getElapsedTime().asMicroseconds() / 10;
		frameTimer.restart();
	}
	
	return 0;
}