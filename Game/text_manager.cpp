
#include "text_manager.h"

TextManager::TextManager()
{

    Logger::msg("A TextManager was created.");
}

TextManager::~TextManager()
{
    Logger::msg("A TextManager was destroyed.");
}

TextManager* TextManager::instance()
{
    static TextManager instance;
    return &instance;
}

void TextManager::startup()
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }

    FT_Face face;
    if (FT_New_Face(ft, "Resources/Fonts/Roboto-Regular.ttf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    }
}

void TextManager::shutdown()
{
    //mFont.Destroy();
}

void TextManager::update()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, kWindowWidth, 0, kWindowHeight, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    float currentColor[4];
    glGetFloatv(GL_CURRENT_COLOR, currentColor);

    //mFont.Begin();

    vector<Text*>::iterator it;

    for (it = mTexts.begin(); it != mTexts.end(); ++it)
    {
        Text* text = *it;

        glColor4f(text->color.r, text->color.g, text->color.b, text->color.a);

        //mFont.DrawString(text->str, 0.027f, text->x, text->y);

        delete text;
    }

    mTexts.clear();

    glColor4fv(currentColor);

    glPopMatrix();
}

void TextManager::placeAt(const string& _str, const Color& _color, float _x, float _y)
{
    mTexts.push_back(new Text(_str, _color, _x, _y));
}

