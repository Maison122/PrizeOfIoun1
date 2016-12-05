/*
==================================================================================
cGame.cpp
==================================================================================
*/
#include "cGame.h"

cGame* cGame::pInstance = NULL;
static cTextureManager* theTextureManager = cTextureManager::getInstance();
static cFontManager* theFontManager = cFontManager::getInstance();
static cSoundManager* theSoundManager = cSoundManager::getInstance();
static cButtonManager* theButtonManager = cButtonManager::getInstance();


/*
=================================================================================
Constructor
=================================================================================
*/
cGame::cGame()
{

}
/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cGame* cGame::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cGame();
	}
	return cGame::pInstance;
}


void cGame::initialise(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	// Get width and height of render context
	SDL_GetRendererOutputSize(theRenderer, &renderWidth, &renderHeight);
	this->m_lastTime = high_resolution_clock::now();
	// It clears the buffer and puts a black background in its place
	SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(theRenderer);

	theTextureManager->setRenderer(theRenderer);
	theFontManager->initFontLib();
	theSoundManager->initMixer();
	theAreaClicked = { 0, 0 };

	// Store the textures
	textureName = {"boulder1", "boulder2", "TNT", "PlayerCharacter", "Arrow", "Background" };
	texturesToUse = { "Images\\boulder1.png", "Images\\boulder2.png", "Images\\TNT.png", "Images\\PlayerCharacter.png", "Images\\Arrow.png", "Images\\Background.png" };
	for (int tCount = 0; tCount < textureName.size(); tCount++)
	{
		theTextureManager->addTexture(textureName[tCount], texturesToUse[tCount]);
	}

	// Store the button textures
	btnNameList = { "quit_btn", "instructionsmenu_btn",  "mainmenu_btn", "play_btn" };
	btnTexturesToUse = { "Images/Buttons/button_exit.png", "Images/Buttons/button_instructions.png",  "Images/Buttons/button_menu.png", "Images/Buttons/button_play.png",  };
	btnPos = {};
	for (int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		theTextureManager->addTexture(btnNameList[bCount], btnTexturesToUse[bCount]);
	}
	for (int bCount = 0; bCount < btnNameList.size(); bCount++)
	{
		cButton * newBtn = new cButton();
		newBtn->setTexture(theTextureManager->getTexture(btnNameList[bCount]));
		newBtn->setSpritePos(btnPos[bCount]);
		newBtn->setSpriteDimensions(theTextureManager->getTexture(btnNameList[bCount])->getTWidth(), theTextureManager->getTexture(btnNameList[bCount])->getTHeight());
		theButtonManager->add(btnNameList[bCount], newBtn);
	}
	theGameState = MENU;
	theBtnType = EXIT;
	// This creates all the textures for the Game Text
	fontList = { "tiza", "thelastcall" };
	fontsToUse = { "Fonts/tiza.ttf", "Fonts/TheLastCall.ttf" };
	for (int fonts = 0; fonts < fontList.size(); fonts++)
	{
		theFontManager->addFont(fontList[fonts], fontsToUse[fonts], 48);
	}

	//Creating the textures for the text
	gameTextNames = { "TitleTxt", "ScoreTxt", "GameOverTxt" };
	gameTextList = { "Score : ", "Prize Of Ioun", "GameOver" };
	
	theTextureManager->addTexture("Title", theFontManager->getFont("TheLastCall")->createTextTexture(theRenderer, gameTextList[0], SOLID, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));
	theTextureManager->addTexture("Score", theFontManager->getFont("tiza")->createTextTexture(theRenderer, gameTextList[1], SOLID, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));

	//This Loads All The Sounds In The Game
	soundList = { "Theme", "Throw", "Explosion", "Click"  };
	soundTypes = { MUSIC, SFX, SFX};
	soundsToUse = { "Audio/Theme/AdventureTheme.wav", "Audio/SFX/Explosion.wav", "Audio/SFX/Throw.wav", "Audio/SFX/ButtonClick.wav" };
	for (int sounds = 0; sounds < soundList.size(); sounds++)
	{
		theSoundManager->add(soundList[sounds], soundsToUse[sounds], soundTypes[sounds]);
	}

	theSoundManager->getSnd("Theme")->play(-1);

	spriteBkgd.setSpritePos({ 0, 0 });
	spriteBkgd.setTexture(theTextureManager->getTexture("Background"));
	spriteBkgd.setSpriteDimensions(theTextureManager->getTexture("Background")->getTWidth(), theTextureManager->getTexture("Background")->getTHeight());

	thePlayer.setSpritePos({ 500, 350 });
	thePlayer.setTexture(theTextureManager->getTexture("PlayerCharacter"));
	thePlayer.setSpriteDimensions(theTextureManager->getTexture("PlayerCharacter")->getTWidth(), theTextureManager->getTexture("PlayerCharacter")->getTHeight());
	thePlayer.setPlayerVelocity({ 0, 0 });

	// Create vector array of textures
	srand(time(NULL));
	for (int bould = 0; bould < 3; bould++)
	{
		theBoulders.push_back(new cBoulder);
		theBoulders[bould]->setSpritePos({ 100 * (rand() % 5 + 1), 50 * (rand() % 5 + 1) });
		theBoulders[bould]->setSpriteTranslation({ (rand() % 8 + 1), (rand() % 8 + 1) });
		int randBoulder = rand() % 4;
		theBoulders[bould]->setTexture(theTextureManager->getTexture(textureName[randBoulder]));
		theBoulders[bould]->setSpriteDimensions(theTextureManager->getTexture(textureName[randBoulder])->getTWidth(), theTextureManager->getTexture(textureName[randBoulder])->getTHeight());
		theBoulders[bould]->setBoulderVelocity({ 3.0f, 3.0f });
		theBoulders[bould]->setActive(true);
	}

}

void cGame::run(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	bool loop = true;

	while (loop)
	{
		//This part of the code lets us get the time that has passed since the last frame
		double elapsedTime = this->getElapsedSeconds();
		loop = this->getInput(loop);
		this->update(elapsedTime);
		this->render(theSDLWND, theRenderer);
	}
}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer)
{
	SDL_RenderClear(theRenderer);
	switch (theGameState)
	{
	case MENU:
	{
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		// This part renders the title that appears in the main menu
		tempTextTexture = theTextureManager->getTexture("TitleTxt");
		pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		scale = { 1, 1 };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		tempTextTexture = theTextureManager->getTexture("ScoreTxt");
		pos = { 300, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		tempTextTexture = theTextureManager->getTexture("GameOverTxt");
		pos = { 300, 75, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		// This part renders each of the buttons in the main menu
		theButtonManager->getBtn("play_btn")->render(theRenderer, &theButtonManager->getBtn("play_btn")->getSpriteDimensions(), &theButtonManager->getBtn("play_btn")->getSpritePos(), theButtonManager->getBtn("play_btn")->getSpriteScale());
		theButtonManager->getBtn("quit_btn")->setSpritePos({ 400, 375 });
		theButtonManager->getBtn("quit_btn")->render(theRenderer, &theButtonManager->getBtn("quit_btn")->getSpriteDimensions(), &theButtonManager->getBtn("quit_btn")->getSpritePos(), theButtonManager->getBtn("quit_btn")->getSpriteScale());
	}
	break;
	case PLAYING:
	{
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		tempTextTexture = theTextureManager->getTexture("Background");
		pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		theButtonManager->getBtn("pause_btn")->setSpritePos({ 740, 575 });
		theButtonManager->getBtn("pause_btn")->render(theRenderer, &theButtonManager->getBtn("pause_btn")->getSpriteDimensions(), &theButtonManager->getBtn("pause_btn")->getSpritePos(), theButtonManager->getBtn("pause_btn")->getSpriteScale());
		
		// This renders the score
		theTextureManager->addTexture("Score", theFontManager->getFont("")->createTextTexture(theRenderer, strScore.c_str(), SOLID, { 0, 255, 0, 255 }, { 0, 0, 0, 0 }));
		tempTextTexture = theTextureManager->getTexture("");
		pos = { 10, 30, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);

		// Render each boulder in the vector array
		for (int draw = 0; draw < theBoulders.size(); draw++)
		{
			theBoulders[draw]->render(theRenderer, &theBoulders[draw]->getSpriteDimensions(), &theBoulders[draw]->getSpritePos(), theBoulders[draw]->getSpriteRotAngle(), &theBoulders[draw]->getSpriteCentre(), theBoulders[draw]->getSpriteScale());
		}
		// Render TNT in the vector array
		for (int draw = 0; draw < theTNTs.size(); draw++)
		{
			theTNTs[draw]->render(theRenderer, &theTNTs[draw]->getSpriteDimensions(), &theTNTs[draw]->getSpritePos(), theTNTs[draw]->getSpriteRotAngle(), &theTNTs[draw]->getSpriteCentre(), theTNTs[draw]->getSpriteScale());
		}
		// Render Arrows in the vector array
		for (int draw = 0; draw < theTNTs.size(); draw++)
		{
			theTNTs[draw]->render(theRenderer, &theTNTs[draw]->getSpriteDimensions(), &theTNTs[draw]->getSpritePos(), theTNTs[draw]->getSpriteRotAngle(), &theTNTs[draw]->getSpriteCentre(), theTNTs[draw]->getSpriteScale());
		}
		// This renders the player
		thePlayer.render(theRenderer, &thePlayer.getSpriteDimensions(), &thePlayer.getSpritePos(), thePlayer.getSpriteRotAngle(), &thePlayer.getSpriteCentre(), thePlayer.getSpriteScale());
		SDL_RenderPresent(theRenderer);
	}
	break;
	case END:
	{
		spriteBkgd.render(theRenderer, NULL, NULL, spriteBkgd.getSpriteScale());
		tempTextTexture = theTextureManager->getTexture("");
		pos = { 10, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		tempTextTexture = theTextureManager->getTexture("");
		pos = { 300, 10, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		tempTextTexture = theTextureManager->getTexture("");
		pos = { 300, 75, tempTextTexture->getTextureRect().w, tempTextTexture->getTextureRect().h };
		tempTextTexture->renderTexture(theRenderer, tempTextTexture->getTexture(), &tempTextTexture->getTextureRect(), &pos, scale);
		theButtonManager->getBtn("mainmenu_btn")->setSpritePos({ 500, 500 });
		theButtonManager->getBtn("mainmenu_btn")->render(theRenderer, &theButtonManager->getBtn("mainmenu_btn")->getSpriteDimensions(), &theButtonManager->getBtn("mainmenu_btn")->getSpritePos(), theButtonManager->getBtn("mainmenu_btn")->getSpriteScale());
		theButtonManager->getBtn("quit_btn")->setSpritePos({ 500, 575 });
		theButtonManager->getBtn("quit_btn")->render(theRenderer, &theButtonManager->getBtn("quit_btn")->getSpriteDimensions(), &theButtonManager->getBtn("quit_btn")->getSpritePos(), theButtonManager->getBtn("quit_btn")->getSpriteScale());
	}
	break;
	case QUIT:
	{
		loop = false;
	}
	}
	
	


}

void cGame::render(SDL_Window* theSDLWND, SDL_Renderer* theRenderer, double rotAngle, SDL_Point* spriteCentre)
{

	SDL_RenderPresent(theRenderer);
}

void cGame::update()
{

}

void cGame::update(double deltaTime)
{
	// This checks that the button has been clicked and the state changes as a result
	if (theGameState == MENU || theGameState == END)
	{
		theGameState = theButtonManager->getBtn("quit_btn")->update(theGameState, QUIT, theAreaClicked);
	}
	else
	{
		theGameState = theButtonManager->getBtn("quit_btn")->update(theGameState, END, theAreaClicked);
	}
	if (theGameState == MENU || theGameState == PLAYING)
	{
		theGameState = theButtonManager->getBtn("play_btn")->update(theGameState, PLAYING, theAreaClicked);
	}
	else
	{
		theGameState = theButtonManager->getBtn("mainmenu_btn")->update(theGameState, MENU, theAreaClicked);
	}

	// Update the visibility and position of each boulder
	vector<cBoulder*>::iterator boulderIterator = theBoulders.begin();
	while (boulderIterator != theBoulders.end())
	{
		if ((*boulderIterator)->isActive() == false)
		{
			boulderIterator = theBoulders.erase(boulderIterator);
		}
		else
		{
			(*boulderIterator)->update(deltaTime);
			if (
				(*boulderIterator)->getSpritePos().x < -20 ||
				(*boulderIterator)->getSpritePos().x > 950
				)
			{
				(*boulderIterator)->setSpriteTranslation({ (*boulderIterator)->getSpriteTranslation().x * (-1), (*boulderIterator)->getSpriteTranslation().y * (-1) });
			}

			if (
				(*boulderIterator)->getSpritePos().y < 20 ||
				(*boulderIterator)->getSpritePos().y > 1000
				)
			{
				(*boulderIterator)->setSpriteTranslation({ (*boulderIterator)->getSpriteTranslation().x * (-1), (*boulderIterator)->getSpriteTranslation().y * (-1) });
			}
			++boulderIterator;
		}
	}
	// Update the visibility and position of TNT
	vector<cTNT*>::iterator tntIterator = theTNTs.begin();
	while (tntIterator != theTNTs.end())
	{
		if ((*tntIterator)->isActive() == false)
		{
			tntIterator = theTNTs.erase(tntIterator);
		}
		else
		{
			(*tntIterator)->update(deltaTime);
			if (
				(*tntIterator)->getSpritePos().x < 0 ||
				(*tntIterator)->getSpritePos().y < 0 ||
				(*tntIterator)->getSpritePos().x > 1028 ||
				(*tntIterator)->getSpritePos().y > 1028
				)
			{
				(*tntIterator)->setActive(false);
			}
			++tntIterator;
		}
	}
	// Update the visibility and position of the Arrow
	vector<cArrow*>::iterator arrowIterator = theArrows.begin();
	while (arrowIterator != theArrows.end())
	{
		if ((*arrowIterator)->isActive() == false)
		{
			arrowIterator = theArrows.erase(arrowIterator);
		}
		else
		{
			(*arrowIterator)->update(deltaTime);
			if (
				(*arrowIterator)->getSpritePos().x < 0 ||
				(*arrowIterator)->getSpritePos().y < 0 ||
				(*arrowIterator)->getSpritePos().x > 1028 ||
				(*arrowIterator)->getSpritePos().y > 1028
				)
			{
				(*arrowIterator)->setActive(false);
			}
			++arrowIterator;
		}
	}
	/*
	==============================================================
	| Check for collisions
	==============================================================
	*/
	for (vector<cTNT*>::iterator tntIterator = theTNTs.begin(); tntIterator != theTNTs.end(); ++tntIterator)
	{

		for (vector<cBoulder*>::iterator boulderIterator = theBoulders.begin(); boulderIterator != theBoulders.end(); ++boulderIterator)
		{
			if ((*boulderIterator)->collidedWith(&(*boulderIterator)->getBoundingRect(), &(*tntIterator)->getBoundingRect()))
			{
				// if a collision occurs this sets the tnt and boulder to false
				(*boulderIterator)->setActive(false);
				(*tntIterator)->setActive(false);
				theSoundManager->getSnd("Explosion")->play(0);
				score += 100;
				strScore = gameTextList[1] + to_string(score);
				theTextureManager->deleteTexture("Score : ");
			}
		}
	}
	for (vector<cTNT*>::iterator tntIterator = theTNTs.begin(); tntIterator != theTNTs.end(); ++tntIterator)
	{
		if ((*arrowIterator)->collidedWith(&(*arrowIterator)->getBoundingRect(), &(*tntIterator)->getBoundingRect()))
		{
			// if a collision occurs this sets the tnt and boulder to false
			(*arrowIterator)->setActive(false);
			(*tntIterator)->setActive(false);
			theSoundManager->getSnd("Explosion")->play(0);
			score += 100;
			strScore = gameTextList[1] + to_string(score);
			theTextureManager->deleteTexture("Score : ");
		}

	}



	// Update the Players position
	thePlayer.update(deltaTime);
	}

bool cGame::getInput(bool theLoop)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			theLoop = false;
		}

		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
			{
				theAreaClicked = { event.motion.x, event.motion.y };
			}
			break;
			case SDL_BUTTON_RIGHT:
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
			{
				if (theGameState == PLAYING)
				{
					theAreaClicked = { event.motion.x, event.motion.y };
				}
			}
			break;
			case SDL_BUTTON_RIGHT:
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEMOTION:
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				theLoop = false;
				break;
			case SDLK_DOWN:
			{
				if (thePlayer.getSpritePos().x < (renderWidth - thePlayer.getSpritePos().w))
				{
					thePlayer.setSpriteTranslation({ -5, -5 });

				}
			}
			break;

			case SDLK_UP:
			{
				if (thePlayer.getSpritePos().x > 0)
				{
					thePlayer.setSpriteTranslation({ 5, 5 });
				}
			}
			break;
			case SDLK_RIGHT:
			{
				thePlayer.setSpriteRotAngle(thePlayer.getSpriteRotAngle() + 5);
			}
			break;

			case SDLK_LEFT:
			{
				thePlayer.setSpriteRotAngle(thePlayer.getSpriteRotAngle() - 5);
			}
			break;
			case SDLK_SPACE:
			{
				theTNTs.push_back(new cTNT);
				int numTNT = theTNTs.size() - 1;
				theTNTs[numTNT]->setSpritePos({ thePlayer.getBoundingRect().x + thePlayer.getSpriteCentre().x, thePlayer.getBoundingRect().y + thePlayer.getSpriteCentre().y });
				theTNTs[numTNT]->setSpriteTranslation({ 2.0f, 2.0f });
				theTNTs[numTNT]->setTexture(theTextureManager->getTexture("TNT"));
				theTNTs[numTNT]->setSpriteDimensions(theTextureManager->getTexture("TNT")->getTWidth(), theTextureManager->getTexture("TNT")->getTHeight());
				theTNTs[numTNT]->setTNTVelocity({ 2.0f, 2.0f });
				theTNTs[numTNT]->setSpriteRotAngle(thePlayer.getSpriteRotAngle());
				theTNTs[numTNT]->setActive(true);
				cout << "TNT added to Vector at position - x: " << thePlayer.getBoundingRect().x << " y: " << thePlayer.getBoundingRect().y << endl;
			}
			default:
				break;
			}

		default:
			break;
		}

	}
	return theLoop;
}

double cGame::getElapsedSeconds()
{
	this->m_CurrentTime = high_resolution_clock::now();
	this->deltaTime = (this->m_CurrentTime - this->m_lastTime);
	this->m_lastTime = this->m_CurrentTime;
	return deltaTime.count();
}

void cGame::cleanUp(SDL_Window* theSDLWND)
{
	// Delete our OpengL context
	SDL_GL_DeleteContext(theSDLWND);

	// Destroy the window
	SDL_DestroyWindow(theSDLWND);

	// Quit IMG system
	IMG_Quit();

	// Shutdown SDL 2
	SDL_Quit();
}
