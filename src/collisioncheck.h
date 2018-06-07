#ifndef COLLISIONCHECK_H
#define COLLISIONCHECK_H
#include "precomp.h"
#include "cbobject.h"

/** Handles collisions between two objects */
class CollisionCheck {
	public:
		/** The type of collision set with SetupCollision */
		enum CollisionType {
			Box = 1,
			Circle,
			Pixel,
			Map
		};
		/** The way collision are handled */
		enum CollisionHandling {
			Unhandled = 0,
			Stop,
			Slide
		};

		/** An empty constructor */
		CollisionCheck();
		/** Sets the objects during construction */
		CollisionCheck(CBObject *object1, CBObject *object2);

		/** Returns the object that is colliding */
		CBObject* getObject1() const { return object1; }
		/** Returns the object that is collided to */
		CBObject* getObject2() const { return object2; }

		/** Check if either of the collision objects are null */
		bool isNull() const { return object1 == 0 || object2 == 0; }
		/** Sets the objects that take part in this collision and resets safe coordinates. */
		void setObjects(CBObject *a, CBObject *b);
		/** Sets the type of collision for the colliding object. */
		void setCollisionType1(uint16_t c);
		/** Sets the type of collision for the object to collide to. */
		void setCollisionType2(uint16_t c);

		/** Sets the way collision are handled */
		void setCollisionHandling(uint16_t h);

		/** Tests the collision */
		void testCollision();

		/** Tests a rectangle - rectangle collision, with parameters. */
		static bool RectRectTest(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);

		/** Tests a circle - rectangle collision, with parameters. */
		static bool CircleRectTest(float circleX, float circleY, float circleR, float rectX, float rectY, float rectW, float rectH);

		/** Tests a circle - circle collision, with parameter. */
		static bool CircleCircleTest(float x1, float y1, float r1, float x2, float y2, float r2);
	private:
		/** Object that has the collision set */
		CBObject *object1;
		/** Object to collide to */
		CBObject *object2;

		/** Latest coordinates of mObject1 where there were no collision. */
		float safeX, safeY;

		/** The type of collision, @see CollisionType */
		CollisionType collisionType1, collisionType2;
		/** The way collision is handled, @see CollisionHandling */
		CollisionHandling collisionHandling;

		/** The amount of collisions detected */
		uint16_t collisionCount;

		/** A circle - rectangle collision test */
		void CircleRectTest();
		/** A rectangle - circle collision test */
		void RectCircleTest();
		/** A rectangle - rectangle collision test */
		void RectRectTest();
		/** A circle - circle collision test */
		void CircleCircleTest();
		/** A rectangle - map collision test */
		void RectMapTest();
		/** A circle - map collision test */
		void CircleMapTest();

		/** Drawing the collision box, used for debugging only. */
		void DrawCollisionBoundaries();

		/** Handles the collision */
		void handleCollision();
};

#endif // COLLISIONCHECK_H
