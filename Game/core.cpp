
#include "core.h"

Core::Core() : mComponents(vector<CoreComponent*>()), quit(false)
{
}

Core::~Core()
{
}

void Core::initialize()
{
	mGraphicsManager = GraphicsManager::instance();
	mSoundManager = SoundManager::instance();
	mInputManager = InputManager::instance();
	mTextureManager = TextureManager::instance();
	mTextManager = TextManager::instance();

	mOrthoRenderer = OrthoRenderer::instance();
	mPerspectiveRenderer = PerspectiveRenderer::instance();

	mCamera = new Camera();

	int count = mComponents.size();
	for (int i = 0; i < count; ++i)
	{
		mComponents[i]->initialize();
	}
}

void Core::cleanup()
{
	int count = mComponents.size();
	for (int i = 0; i < count; ++i)
	{
		mComponents[i]->cleanup();
	}

	delete mCamera;
}

void Core::startup()
{
	mGraphicsManager->startup();
	mSoundManager->startup();
	mInputManager->startup();
	mTextureManager->startup();
	mTextManager->startup();

	mCamera->updatePerspective();
	mCamera->updateView();
}

void Core::shutdown()
{
	mTextManager->shutdown();
	mTextureManager->shutdown();
	mInputManager->shutdown();
	mSoundManager->shutdown();
	mGraphicsManager->shutdown();
}

void Core::loadContent()
{
	int count = mComponents.size();
	for (int i = 0; i < count; ++i)
	{
		mComponents[i]->loadContent();
	}
}

void Core::unloadContent()
{
	int count = mComponents.size();
	for (int i = 0; i < count; ++i)
	{
		mComponents[i]->unloadContent();
	}
}

void Core::reset()
{
	int count = mComponents.size();
	for (int i = 0; i < count; ++i)
	{
		mComponents[i]->reset();
	}
}

void Core::attachComponent(CoreComponent* _component)
{
	if (!_component)
	{
		Logger::outputs("Core", "Tried to attach a null component.");
		return;
	}

	mComponents.push_back(_component);
	
	stringstream out;		
	out << "A component of type " << typeid(_component).name() << " was attached.";
	Logger::outputs("Core", out.str());
}

void Core::detachComponent(CoreComponent* _component)
{
	if (!_component)
	{
		Logger::outputs("Core", "Tried to detach a null component.");
		return;
	}

	stringstream out;
	out << "A component of type " << typeid(_component).name() << " was detached.";
	Logger::outputs("Core", out.str());

	vector<CoreComponent*>::iterator result = find(mComponents.begin(), mComponents.end(), _component);

	if (result != mComponents.end())
	{
		mComponents.erase(result);
	}	
}

void Core::input()
{
	mInputManager->update();

	if (mInputManager->onEvent(SDL_QUIT))
	{
		quit = true;
	}

	int count = mComponents.size();
	for (int i = 0; i < count; ++i)
	{
		mComponents[i]->input();
	}
}

void Core::update(const Time& _time)
{
	mGraphicsManager->beginScene();
	
	mCamera->updatePerspective();
	mCamera->updateView();

	int count = mComponents.size();
	for (int i = 0; i < count; ++i)
	{
		mComponents[i]->update(_time);
	}

	mPerspectiveRenderer->render();
	mTextManager->update();
	mOrthoRenderer->render();


	mGraphicsManager->endScene();
}

void Core::run()
{
	const Uint32 frameRate = 1000 / 60;

	Time time;

	while (!quit) 
	{
		time.present = SDL_GetTicks();
		time.delta = (time.present - time.past) / 1000.0f;

		if (time.present - time.past >= frameRate) 
		{
			update(time);
			input();

			time.past = time.present;
		}
	}
}
