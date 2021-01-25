
#include "texture_manager.h"

TextureManager::TextureManager() : mTextures(vector<GLuint>())
{
	Logger::outputs("TextureManager", "A TextureManager was created.");
}

TextureManager::~TextureManager()
{
	const GLsizei count = mTextures.size();

	if (count > 0)
	{
		for (int i = 0; i < count; ++i)
		{
			GLuint candidate = mTextures[i];

			if (glIsTexture(candidate))
			{
				GLuint texture[1] = {candidate};

				Logger::outputs("TextureManager", "Deleting texture with id", (int) texture);

				glDeleteTextures(1, texture);

				Error::glPopError("TextureManager");	
			}
		}		
	}

	Logger::outputs("TextureManager", "A TextureManager was destroyed.");
}

TextureManager* TextureManager::instance()
{
	static TextureManager instance;
	return &instance;
}

void TextureManager::startup()
{
}

void TextureManager::shutdown()
{
}

SDL_Surface* TextureManager::loadSurface(const string& filename)
{
	if (filename.empty())
	{
		Error::show("TextureManager", "Trying to load a surface with an empty filename.");

		return 0;
	}

	stringstream out;
	out << "Loading surface with filename: [ " << filename << " ]";
	Logger::outputs("TextureManager", out.str());

	SDL_Surface* surface = IMG_Load(filename.c_str());

	if (0 == surface)
	{
		Error::show("TextureManager", "Error loading surface.", true);

		return 0;
	}

	return surface;

	Logger::outputs("TextureManager", "Optimizing...");

	SDL_Surface* optimizedImage = SDL_DisplayFormatAlpha(surface);

	SDL_FreeSurface(surface);

	if (0 == optimizedImage)
	{
		Error::show("TextureManager", "Error optimizing surface.", true);

		return 0;
	}

	Logger::outputs("TextureManager", "Returning optimized texture...");

	return optimizedImage;
}

GLuint TextureManager::createFromSurface(SDL_Surface* surface)
{
	Logger::outputs("TextureManager", "Creating from surface...");

	if (!surface)
	{
		Error::show("TextureManager", "Trying to create a texture from a surface with an empty surface.");

		return -1;
	}

	GLuint id = 0;

	glGenTextures(1, &id);

	if (!id)
	{
		Error::show("TextureManager", "Couldn't generate texture.");

		return -1;
	}

	Logger::outputs("TextureManager", "Generated a texture with id", id);

	mTextures.push_back(id);

	glBindTexture(GL_TEXTURE_2D, id);

	// filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// wrap
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLint format = surface->format->BytesPerPixel == 3 ? GL_RGB : GL_RGBA;

	// mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, format, 64, 64, format, GL_UNSIGNED_BYTE, surface->pixels);

	glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

	SDL_FreeSurface(surface);

	Error::glPopError("TextureManager");

	return id;
}

GLuint TextureManager::createFromFile(const string& filename)
{
	return createFromSurface(loadSurface(filename));
}