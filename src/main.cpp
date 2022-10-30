#include <SFML/Graphics.hpp>
#include <iostream>

//window size at start
#define defaultWindowWidth 1280.0
#define defaultWindowHeight 720.0

//basic elements
sf::RenderWindow window;
sf::VertexBuffer vertexBuffer(sf::PrimitiveType::TriangleStrip, sf::VertexBuffer::Usage::Dynamic);
sf::Shader fragmentShader;
sf::View camera;
float zoom = 1.0f;

//deltatime for keyevents
sf::Clock frameTimer;
double deltaTime = 0;

//defines the iteration count
float iterations = 100.0f;

//creates an vertex buffer to know the pixel position for komplex numbers
void uploadVertexbuffer() {
	
	sf::Vertex verticies[4];
	verticies[0].position = sf::Vector2f(0 , 0);
	verticies[1].position = sf::Vector2f(defaultWindowWidth, 0);
	verticies[2].position = sf::Vector2f(0, defaultWindowHeight);
	verticies[3].position = sf::Vector2f(defaultWindowWidth, defaultWindowHeight);


	verticies[0].texCoords = sf::Vector2f(-2.5f,1.0f);
	verticies[1].texCoords = sf::Vector2f(1.f,1.0f);
	verticies[2].texCoords = sf::Vector2f(-2.5f,-1.0f);
	verticies[3].texCoords = sf::Vector2f(1.f,-1.0f);

	vertexBuffer.update(verticies);
}

//is only called at startup
void setup() {
	//create window with specific size
	window.create(sf::VideoMode(defaultWindowWidth, defaultWindowHeight), "Mandelbrotmenge", sf::Style::Default);

	//create canvas for mandelbrotset
	vertexBuffer.create(4);
	uploadVertexbuffer();

	//get the camera from window view
	camera = window.getDefaultView();
	window.setView(camera);

	//load the mandelbrot shader
	fragmentShader.loadFromFile("shader.frag",sf::Shader::Fragment);
}

void update(const sf::Event& events) {
	//store the last states of the mouse
	static bool mouseButtonLastUpdatePressed = false;
	static sf::Vector2i lastMousePos;
	//mouse difference between last update
	sf::Vector2<double> difference;

	switch (events.type)
	{
		//increase/decrease iterations
	case sf::Event::KeyPressed: {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			iterations += deltaTime / 1000;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {

			iterations -= deltaTime / 1000;
		}

		break;
	}
	//zoom in/out
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

	//reset mouse pressed state
	case sf::Event::MouseButtonReleased:
		mouseButtonLastUpdatePressed = false;
		break;

	default:
		break;
	}
	//move technice
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (!mouseButtonLastUpdatePressed) {
			lastMousePos = sf::Mouse::getPosition();
			mouseButtonLastUpdatePressed = true;
			//save position and return if button was the first time pressed
			return;
		}
		//calculate the difference from last update 
		difference = (sf::Vector2<double>)(lastMousePos - sf::Mouse::getPosition()) * (double)zoom;
		//match the difference to the projection matrix
		difference.x *= defaultWindowWidth / window.getSize().x;
		difference.y *= defaultWindowHeight / window.getSize().y;
		//know move the cam
		camera.move((sf::Vector2f) difference);
		window.setView(camera);
		//store the last state to calculate the difference next time
		lastMousePos = sf::Mouse::getPosition();
	}
}

void draw() {
	//draw everything and give the iteration count to the shader
	fragmentShader.setUniform("maxIteration", iterations);
	window.draw(vertexBuffer,&fragmentShader);
}

int main() {

	setup();
	//main loop
	while (window.isOpen()) {
		//manage window events
		sf::Event events;
		while (window.pollEvent(events)) {
			switch (events.type)
			{
			case sf::Event::Closed:

				window.close();
				break;
			default:
			update(events);
				break;
			}

		}

		//clear frame buffer
		window.clear(sf::Color(30,30,30,255));
		draw();
		window.display();
		//calculate delta time in milliseconds
		deltaTime = frameTimer.getElapsedTime().asMicroseconds() / 10;
		frameTimer.restart();
	}
	
	return 0;
}