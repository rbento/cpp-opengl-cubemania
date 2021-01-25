
#include "primitive.h"

Primitive::Primitive(const GLuint& _id, const GLfloat _width, const GLfloat _height, const GLfloat _depth, const Transform& _offset) : id(_id), width(_width), height(_height), depth(_depth), offset(_offset) 
{
	Logger::outputs("Primitive", "A primitive was created.");
}

Primitive::~Primitive()
{
	if (glIsList(id))
	{
		Logger::outputs("Primitive", "Deleting display list with id", (int) id);

		glDeleteLists(id, 1);

		Error::glPopError("Primitive");
	}

	Logger::outputs("Primitive", "A primitive was destroyed.");
}

GLuint Primitive::loadTexture(const string& _filename)
{			
	if (!_filename.empty())
	{
		return TextureManager::instance()->createFromFile(_filename);
	}

	return 0;
}

vector<GLuint> Primitive::loadTextures(const vector<string>& _filenames)
{
	vector<GLuint> result;

	int count = _filenames.size();

	if (count > 0)
	{
		GLuint texture = 0;

		for (int i = 0; i < count; ++i)
		{
			texture = loadTexture(_filenames[i]);

			if (texture)
			{
				result.push_back(texture);
			}
		}
	}

	return result;
}

void Primitive::drawCubeFace(GLfloat _size, const Color& _color, GLuint _texture)
{
	_size /= 2.0f;

	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);

	glColor4f(_color.r, _color.g, _color.b, _color.a);

	if (0 != _texture)
	{
		glBindTexture(GL_TEXTURE_2D, _texture);

		glBegin(GL_QUADS);

			glTexCoord2f (0.0f, 0.0f);
			glVertex3f(-_size, -_size, _size); 
		
			glTexCoord2f (1.0f, 0.0f);
			glVertex3f(_size, -_size, _size); 

			glTexCoord2f (1.0f, 1.0f);
			glVertex3f(_size, _size, _size);   

			glTexCoord2f (0.0f, 1.0f);
			glVertex3f(-_size, _size, _size);  

		glEnd();
	}
	else
	{
		glBegin(GL_QUADS);

			glVertex3f(-_size, -_size, _size); 		
			glVertex3f(_size, -_size, _size); 
			glVertex3f(_size, _size, _size);  
			glVertex3f(-_size, _size, _size);  

		glEnd();
	}

	glColor4fv(currentColor);
}

void Primitive::drawCube(GLfloat _size, const Color& _color, GLuint _texture)
{
	glPushMatrix();

		//ft
		drawCubeFace(_size, _color, _texture);

		//dn
		glRotatef (90.0f, 1.0f, 0.0f, 0.0f);
		drawCubeFace(_size, _color, _texture);

		//bk
		glRotatef (90.0f, 1.0f, 0.0f, 0.0f);
		drawCubeFace(_size, _color, _texture);

		//up
		glRotatef (90.0f, 1.0f, 0.0f, 0.0f);
		drawCubeFace(_size, _color, _texture);

		//rt
		glRotatef (90.0f, 0.0f, 1.0f, 0.0f);
		drawCubeFace(_size, _color, _texture);

		//lf
		glRotatef (180.0f, 0.0f, 1.0f, 0.0f);
		drawCubeFace(_size, _color, _texture);

	glPopMatrix();
}

void Primitive::drawSkybox(GLfloat _size, GLuint* _textures)
{
	_size /= 2.0f;

	glPushMatrix();

		//ft
		glBindTexture(GL_TEXTURE_2D, _textures[0]);

		glBegin(GL_QUADS);

			glTexCoord2f (1.0f, 1.0f); glVertex3f(-_size, -_size, _size); 
			glTexCoord2f (0.0f, 1.0f); glVertex3f(_size, -_size, _size); 
			glTexCoord2f (0.0f, 0.0f); glVertex3f(_size, _size, _size);   
			glTexCoord2f (1.0f, 0.0f); glVertex3f(-_size, _size, _size);  

		glEnd();

		//dn
		glRotatef (90.0f, 1.0f, 0.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, _textures[1]);
		glBegin(GL_QUADS);

			glTexCoord2f (1.0f, 1.0f); glVertex3f(-_size, -_size, _size); 
			glTexCoord2f (0.0f, 1.0f); glVertex3f(_size, -_size, _size); 
			glTexCoord2f (0.0f, 0.0f); glVertex3f(_size, _size, _size);   
			glTexCoord2f (1.0f, 0.0f); glVertex3f(-_size, _size, _size);  

		glEnd();

		//bk
		glRotatef (90.0f, 1.0f, 0.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, _textures[2]);
		glBegin(GL_QUADS);

			glTexCoord2f (0.0f, 0.0f); glVertex3f(-_size, -_size, _size); 
			glTexCoord2f (1.0f, 0.0f); glVertex3f(_size, -_size, _size); 
			glTexCoord2f (1.0f, 1.0f); glVertex3f(_size, _size, _size);   
			glTexCoord2f (0.0f, 1.0f); glVertex3f(-_size, _size, _size);  

		glEnd();

		//up
		glRotatef (90.0f, 1.0f, 0.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, _textures[3]);
		glBegin(GL_QUADS);

			glTexCoord2f (1.0f, 1.0f); glVertex3f(-_size, -_size, _size); 
			glTexCoord2f (0.0f, 1.0f); glVertex3f(_size, -_size, _size); 
			glTexCoord2f (0.0f, 0.0f); glVertex3f(_size, _size, _size);   
			glTexCoord2f (1.0f, 0.0f); glVertex3f(-_size, _size, _size);  

		glEnd();

		//rt
		glRotatef (90.0f, 0.0f, 1.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, _textures[4]);
		glBegin(GL_QUADS);

			glTexCoord2f (1.0f, 0.0f); glVertex3f(-_size, -_size, _size); 
			glTexCoord2f (1.0f, 1.0f); glVertex3f(_size, -_size, _size); 
			glTexCoord2f (0.0f, 1.0f); glVertex3f(_size, _size, _size);   
			glTexCoord2f (0.0f, 0.0f); glVertex3f(-_size, _size, _size);  

		glEnd();

		//lf
		glRotatef (180.0f, 0.0f, 1.0f, 0.0f);
		glBindTexture(GL_TEXTURE_2D, _textures[5]);
		glBegin(GL_QUADS);

			glTexCoord2f (0.0f, 1.0f); glVertex3f(-_size, -_size, _size); 
			glTexCoord2f (0.0f, 0.0f); glVertex3f(_size, -_size, _size); 
			glTexCoord2f (1.0f, 0.0f); glVertex3f(_size, _size, _size);   
			glTexCoord2f (1.0f, 1.0f); glVertex3f(-_size, _size, _size);  

		glEnd();

	glPopMatrix();
}

Primitive* Primitive::createSphere(GLdouble _radius, GLint _slices, GLint _stacks, const string& _filename)
{			
	GLuint texture = loadTexture(_filename);

	GLUquadricObj* sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricNormals(sphere, GLU_SMOOTH);	

	if (texture)
	{
		gluQuadricTexture(sphere, GL_TRUE);
	}

	GLuint id = glGenLists(1);

	glNewList(id, GL_COMPILE);

		if (texture)
		{
			glBindTexture(GL_TEXTURE_2D, texture);
		}

		gluSphere(sphere, _radius, _slices, _stacks);

	glEndList();

	gluDeleteQuadric(sphere);

	Error::glPopError("Primitive");

	GLfloat size =  (GLfloat) _radius * 2;

	return new Primitive(id, size, size, size, Transform());
}

Primitive* Primitive::createCube(GLfloat _size, const Color& _color, const string& _filename)
{
	GLuint texture = loadTexture(_filename);

	GLuint id = glGenLists(1);

	glNewList(id, GL_COMPILE);

		if (texture)
		{
			drawCube(_size, _color, texture);
		}
		else
		{
			drawCube(_size, _color);
		}

	glEndList();

	Error::glPopError("Primitive");

	return new Primitive(id, _size, _size, _size, Transform());
}

Primitive* Primitive::createPlane(GLfloat _width, GLfloat _height, const Color& _color, const string& _filename)
{
	_width /= 2.0f;
	_height /= 2.0f;

	float currentColor[4];
	glGetFloatv(GL_CURRENT_COLOR, currentColor);
	glColor4f(_color.r, _color.g, _color.b, _color.a);

	GLuint texture = loadTexture(_filename);
	GLuint id = glGenLists(1);

	glNewList(id, GL_COMPILE);

	if (texture)
	{
		glBindTexture(GL_TEXTURE_2D, texture);

		glBegin(GL_QUADS);

			glTexCoord2f (0.0f, 0.0f);
			glVertex3f(-_width, -_height, 0.0f); 

			glTexCoord2f (1.0f, 0.0f);
			glVertex3f(_width, -_height, 0.0f); 

			glTexCoord2f (1.0f, 1.0f);
			glVertex3f(_width, _height, 0.0f);   

			glTexCoord2f (0.0f, 1.0f);
			glVertex3f(-_width, _height, 0.0f);  

		glEnd();
	}
	else
	{
		glBegin(GL_QUADS);

			glVertex3f(-_width, -_height, 0.0f); 		
			glVertex3f(_width, -_height, 0.0f); 
			glVertex3f(_width, _height, 0.0f);  
			glVertex3f(-_width, _height, 0.0f);  

		glEnd();
	}

	glEndList();

	glColor4fv(currentColor);

	Error::glPopError("Primitive");

	return new Primitive(id, _width, _height, 0.0f, Transform());
}

Primitive* Primitive::createSkybox(GLfloat _size, const vector<string>& _filenames)
{
	if (6 != _filenames.size())
	{
		Error::show("Primitive", "Trying to create a skybox with a wrong number of texture files. Must specify 6 texture files.", true);
	}

	vector<GLuint> textures = loadTextures(_filenames);

	GLuint id = glGenLists(1);

	glNewList(id, GL_COMPILE);

		glPushMatrix();

		glPushAttrib(GL_ENABLE_BIT);

		glDisable(GL_BLEND);
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		glEnable(GL_TEXTURE_CUBE_MAP);

		glPushMatrix();

			drawSkybox(_size, &textures[0]);

		glPopMatrix();

		glDisable(GL_TEXTURE_CUBE_MAP);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glEnable(GL_BLEND);

		glPopAttrib();

		glPopMatrix();

	glEndList();

	Error::glPopError("Primitive");

	return new Primitive(id, _size, _size, _size, Transform());
}