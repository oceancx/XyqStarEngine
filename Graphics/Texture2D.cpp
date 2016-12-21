#include "Texture2D.h"

#include "../Helpers/Helpers.h"
#include <SOIL.h>
namespace star
{
	const tstring Texture2D::LIBSOIL_LOG_TAG = _T("LIBSOIL");

	Texture2D::Texture2D(const tstring & pPath)
			: mTextureId(0)
			, mFormat(0)
			, mWidth(0)
			, mHeight(0)
			, mPath(pPath)
	{
		Load();
	}


	Texture2D::~Texture2D()
	{
		if(mTextureId != 0)
		{
			glDeleteTextures(1, &mTextureId);
			mTextureId = 0;
		}
		mWidth = 0;
		mHeight = 0;
		mFormat = 0;
	}
	
	uint8* Texture2D::ReadImage()
	{
		FILE *fp;
		tfopen(&fp, mPath.c_str(), _T("rb"));

		if (fp == NULL)
		{
			LOG(LogLevel::Error,
				_T("Texture2D::ReadSOIL: the image \"") +
				mPath +
				_T("\" could not be loaded"), LIBSOIL_LOG_TAG
			);
			return NULL;
		}
		return	SOIL_load_image(mPath.c_str(), &mWidth,&mHeight, 0, SOIL_LOAD_RGB);
	}

	void Texture2D::Load()
	{
		uint8* lImageBuffer = ReadImage();
		if(lImageBuffer == NULL)
		{
			LOG(LogLevel::Error, 
				_T("PNG : ReadSOIL FAILED - NO IMAGE BUFFER"), LIBSOIL_LOG_TAG);
			return;
		}

		glGenTextures(1, &mTextureId);
		glBindTexture(GL_TEXTURE_2D, mTextureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, mFormat, mWidth, mHeight, 0, mFormat, GL_UNSIGNED_BYTE, lImageBuffer);
		delete[] lImageBuffer;
	}

	const tstring & Texture2D::GetPath() const
	{
		return mPath;
	}

	int32 Texture2D::GetHeight() const
	{
		return mHeight;
	}

	int32 Texture2D::GetWidth() const
	{
		return mWidth;
	}

	GLuint Texture2D::GetTextureID() const
	{
		return mTextureId;
	}
}
