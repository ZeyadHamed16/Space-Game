// Game.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

using namespace sf;
using namespace std;

int main()
{
	RenderWindow win(VideoMode(1000, 562), "Game");
	win.setFramerateLimit(90);

	int score = 0; //variable used in score

	//Image
	bool changeImage = false; //Variable to change the image when pressed the ENTER key
	bool gameOver = false; //variable to changer the image when losing
	Texture startWallpaper, spaceWallpaper, gameOverWallpaper;
	if (!startWallpaper.loadFromFile("D:/Programming/Github/C++/Game/DATA/startWallpaper2.png"))
		cout << "StartWallpaper Error\n";
	if (!spaceWallpaper.loadFromFile("D:/Programming/Github/C++/Game/DATA/spaceWallpaper.jpg"))
		cout << "spaceWallpaper Error\n";
	if (!gameOverWallpaper.loadFromFile("D:/Programming/Github/C++/Game/DATA/GameOver_Wallpaper.jpg"))
		cout << "gameOverWallpaper Error\n";
	Sprite imageStart, imageSpace, imageGameOver;
	imageStart.setTexture(startWallpaper);
	imageSpace.setTexture(spaceWallpaper);
	imageGameOver.setTexture(gameOverWallpaper);

	//text
	Font startText;
	if (!startText.loadFromFile("D:/Programming/Github/C++/Game/DATA/FontFile.ttf"))
	{
		cout << "Error loading font file\n";
		system("pause");
	}
	Text textEneter, textTitle1, textTitle2, textShoot, textScore, textLastScore, textEsc, textBackspace;
	textEneter.setFont(startText);
	textEneter.setString("Press ENTER to start");
	textEneter.setPosition(470, 270);
	textEneter.setCharacterSize(70);
	textEneter.setFillColor(Color::Black);
	textEneter.setStyle(Text::Style::Bold);

	textTitle1.setFont(startText);
	textTitle1.setString("Baladi chicken");
	textTitle1.setPosition(550, 20);
	textTitle1.setCharacterSize(180);
	textTitle1.setFillColor(Color::Black);
	textTitle1.setStyle(Text::Style::Bold);

	textTitle2.setFont(startText);
	textTitle2.setString("Creativa");
	textTitle2.setPosition(660, 170);
	textTitle2.setCharacterSize(55);
	textTitle2.setFillColor(Color::Black);
	textTitle2.setStyle(Text::Style::Underlined);

	textShoot.setFont(startText);
	textShoot.setString("( LEFT click ) to fire the rocket");
	textShoot.setPosition(630, 500);
	textShoot.setCharacterSize(55);
	textShoot.setFillColor(Color::White);
	textShoot.setStyle(Text::Style::Bold);
	textShoot.setOutlineThickness(3);
	textShoot.setOutlineColor(Color::Black);

	textEsc.setFont(startText);
	textEsc.setString("( ESCAPE ) to close the game");
	textEsc.setPosition(630, 400);
	textEsc.setCharacterSize(55);
	textEsc.setFillColor(Color::White);
	textEsc.setStyle(Text::Style::Bold);
	textEsc.setOutlineThickness(3);
	textEsc.setOutlineColor(Color::Black);

	textBackspace.setFont(startText);
	textBackspace.setString("( Backspace ) to back to main menu");
	textBackspace.setPosition(630, 450);
	textBackspace.setCharacterSize(55);
	textBackspace.setFillColor(Color::White);
	textBackspace.setStyle(Text::Style::Bold);
	textBackspace.setOutlineThickness(3);
	textBackspace.setOutlineColor(Color::Black);


	//Audio
	Music startMusic;
	if (!startMusic.openFromFile("D:/Programming/Github/C++/Game/DATA/Sakura_Cherry_-_Classical_Koto_Music.ogg"))
		cout << "startMusic Error\n";
	startMusic.play();

	//SoundBuffer effect;
	//if (!effect.loadFromFile("D:/Programming/Github/C++/Game/DATA/Super_Mario_(Game_Over)_Sound_Effect.wav"))
	//	cout << "sound gameOver Error\n";
	//Sound soundGameOver;
	//soundGameOver.setBuffer(effect);

	//Chicken object
	int dir; //Variable to get the Chicken to move right and left
	Texture Enemy;
	if (!Enemy.loadFromFile("D:/Programming/Github/C++/Game/DATA/enemy_chicken.png"))
		cout << "could not load Enmy.png\n";
	Sprite opEnemy;
	opEnemy.setTexture(Enemy);
	opEnemy.setScale(Vector2f(0.5f, 0.5f));

	//Space ship object
	Texture Rocket;
	if (!Rocket.loadFromFile("D:/Programming/Github/C++/Game/DATA/spaceShip.png"))
		cout << "could not load Rocket.png\n";
	Sprite opRocket;
	opRocket.setTexture(Rocket);
	opRocket.setScale(Vector2f(0.2f, 0.2f));
	opRocket.setPosition(Vector2f(0, 460.f));

	//bullet
	bool isShot = false; //Variable used in shooting the bullet
	CircleShape  hoop;
	hoop.setRadius(10);
	hoop.setFillColor(Color::Red);
	hoop.setPosition(Vector2f(0, win.getSize().y - hoop.getRadius() * 3));


	while (win.isOpen())
	{
		Event event;
		while (win.pollEvent(event))
		{
			if (event.type == Event::Closed)
				win.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				win.close();

		}

		//--- Moving the chicken object ---
		if (opEnemy.getPosition().x <= 0)
			dir = 1;
		else if (opEnemy.getPosition().x >= win.getSize().x)
			dir = 0;

		if (dir == 0)
			opEnemy.move(-5.f, 0);
		else
			opEnemy.move(5.f, 0);

		//--- Moving the Rocket object ---
		opRocket.setPosition(Mouse::getPosition(win).x, Mouse::getPosition(win).y);

		//Firing the bullet + Moving the bullet object
		if (Mouse::isButtonPressed(Mouse::Left))
			isShot = true;
		if (!isShot)
			hoop.setPosition(Mouse::getPosition(win).x + 39.f, Mouse::getPosition(win).y + 39.f);
		else
			hoop.move(0, -5);
		//if the bullet hit the top of the screen
		if (hoop.getPosition().y <= 0 )
		{
			isShot = false;
			hoop.setPosition(Mouse::getPosition(win).x + 39.f, Mouse::getPosition(win).y + 39.f);
		}

		//if the spaceShip hit the chicken
		if (opRocket.getGlobalBounds().intersects(opEnemy.getGlobalBounds()))
		{
			gameOver = true;
		}

		//score + if the bullet hit the chicken
		else if (hoop.getGlobalBounds().intersects(opEnemy.getGlobalBounds()))
		{
			isShot = false;
			hoop.setPosition(Mouse::getPosition(win).x + 39.f, Mouse::getPosition(win).y + 39.f);
			score++;
		}
		//text for score
		textScore.setFont(startText);
		textScore.setString("Scroe:" + to_string(score));
		textScore.setPosition(20, 10);
		textScore.setCharacterSize(55);
		textScore.setFillColor(Color::White);
		textScore.setStyle(Text::Style::Bold);
		textScore.setOutlineThickness(3);
		textScore.setOutlineColor(Color::Blue);

		textLastScore.setFont(startText);
		textLastScore.setString("Your score: " + to_string(score));
		textLastScore.setPosition(400, 400);
		textLastScore.setCharacterSize(85);
		textLastScore.setFillColor(Color::Yellow);
		textLastScore.setStyle(Text::Style::Bold);
		textLastScore.setOutlineThickness(3);
		textLastScore.setOutlineColor(Color::Red);
		

		//Draw
		if (gameOver == true)
		{
			win.clear();
			win.draw(imageGameOver);
			win.draw(textLastScore);
			//soundGameOver.play();
			win.display();
		}
		else 
		{
			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				changeImage = true;
			}
			else if (Keyboard::isKeyPressed(Keyboard::BackSpace))
			{
				changeImage = false;
			}
			if (changeImage == true)
			{
				win.clear();
				//------------------
				//image
				win.draw(imageSpace);
				//text
				win.draw(textEsc);
				win.draw(textBackspace);
				win.draw(textShoot);
				win.draw(textScore);
				//objetcs
				win.draw(opEnemy);
				win.draw(hoop);
				win.draw(opRocket);
				//music
				startMusic.pause();
				//------------------
				win.display();
			}
			if (changeImage == false)
			{
				win.clear();
				//------------------
				//image
				win.draw(imageStart);
				//text
				win.draw(textEneter);
				win.draw(textTitle1);
				win.draw(textTitle2);
				//music

				//------------------
				win.display();
			}
		}
	}
	return 0;
}