#ifndef CBIMAGE_H
#define CBIMAGE_H
#include "precomp.h"
#include "rendertarget.h"
class CBParticleEmitter;
class CBImage
{
	public:
		friend class RenderTarget;
		CBImage();
		~CBImage();
		bool load(const string &path);
		bool save(const string &path);
		void lock();
		void unlock();
		int32_t width()const{return renderTarget.width();}
		int32_t height()const{return renderTarget.height();}
		void makeImage(int32_t w, int32_t h);
		void setHotspot(float x,float y) {hotspotX = x;hotspotY = y;}
		RenderTarget *getRenderTarget(){return &renderTarget;}
		void draw(RenderTarget &r,float x,float y,bool useMask);
		void draw(RenderTarget &r,float x,float y,int frame, bool useMask);
		void drawBox(RenderTarget &r, float sx, float sy, float sw, float sh, float tx, float ty, bool useMask);
		void drawBox(RenderTarget &r,float sx,float sy, float sw, float sh, float tx, float ty, int frame, bool useMask);
		/** Draws this image with the given level (0.0f to 1.0f) of alpha blending. */
		void drawAlphaBlended(RenderTarget &r, float x, float y, float alpha);
		void maskImage(const ALLEGRO_COLOR &color);
		ALLEGRO_COLOR getMaskColor()const{return maskColor;}
		void setAnimParams(int32_t frameW,int32_t frameH,int32_t begin,int32_t animL){frameWidth = frameW;frameHeight = frameH;animBegin = begin;animLength = animL;}
		void resize(int32_t w, int32_t h);
		CBImage *clone();
		ALLEGRO_BITMAP *getMaskedBitmap() const {return maskedBitmap;}
		/** Set this CBImage ready for drawing operations or set it back for drawing. */
		void switchMaskBitmaps(bool switchToUnmasked);
		/** Rotates an image with the given angle (in degrees) clockwise. */
		void rotate(float angle);

	private:
		float hotspotX,hotspotY;
		RenderTarget renderTarget;
		ALLEGRO_COLOR maskColor;
		int32_t frameWidth;
		int32_t frameHeight;
		int32_t animBegin;
		int32_t animLength;

		/** The unmasked version of this image */
		ALLEGRO_BITMAP* unmaskedBitmap;
		/** The masked version of this image - is NULL before setupForDrawOperations() is called. */
		ALLEGRO_BITMAP* maskedBitmap;
		/** Is this image masked or not */
		bool isMasked;
};

#endif // CBIMAGE_H
