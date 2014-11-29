#pragma once

#include "Box2D_Shape_Rect.h"
#include "Box2D_Shape_Circle.h"
#include "Box2D_Debug_Renderer.h"
#include "Box2D_Constraint_Joint.h"
#include <GLFrameBufferObject.h>
#include <SDL_Activity.h>
#include <GLTexture.h>
#include <LTexture.h>
#include <Box2D\Box2D.h>
#include <glm\glm.hpp>
#include <vector>
#include <SDL_Utils.h>

using std::vector;

class World
{
	public:
		World(SDL_Activity* activity, b2Vec2 grav);
		~World(void);

		void init(void);
		void update(void);
		void render(void);
		void dispose(void);
		void onEvent(SDL_Event&);

		SDL_Activity* getActivity(void);

		b2Vec2& getGravity(void);
		b2World* getPhysicsWorld(void);

		//Ratio of pixels to meters (30)
		static const float unitRatio;
		//Converts meters to pixels using the unitRatio
		float mtp(float meters);
		//Converts pixels to meters using the unitRatio
		float ptm(float pixels);

	private:
		SDL_Activity* sdl_activity;
		b2Vec2 gravity;

		//Physics
		void initializePhysics(void);
		bool physicsInitialized = false;
		b2World *physicsWorld;
		vector<Box2D_Shape*> b2ds;
		vector<Box2D_Constraint*> b2dc;
		GLfbo* fbo;
		Box2D_Debug_Renderer debugDraw;
};