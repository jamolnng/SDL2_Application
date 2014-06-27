#include "World.h"
#include <stdio.h>

const float World::unitRatio = 30.0f;
bool asdfasdf = false;
bool eeee = false;

World::World(SDL_Activity* activity, b2Vec2 grav)
{
	this->sdl_activity = activity;
	gravity = grav;
}

World::~World(void)
{
}

void World::init(void)
{
	initializePhysics();
	Box2D_Shape::populateBasicShapeVertices();
	GLfloat w = (GLfloat)sdl_activity->getApp()->getWindow()->getWidth();
	GLfloat h = (GLfloat)sdl_activity->getApp()->getWindow()->getHeight();

	b2ds.push_back(new Box2D_Shape_Rect(this, 0.0f, ptm(h) - 0.5f, ptm(w), 0.5f));
	b2ds.push_back(new Box2D_Shape_Rect(this, 0, 0.5f, ptm(w), 0.5f));
	b2ds.push_back(new Box2D_Shape_Rect(this, 0.5f, 0, 0.5f, ptm(h)));
	b2ds.push_back(new Box2D_Shape_Rect(this, ptm(w) - 0.5f, 0, 0.5f, ptm(h)));
	b2ds.push_back(new Box2D_Shape_Rect(this, (5.5f * (sqrt(2.0f) / 2.0f)), (5.5f * (sqrt(2.0f) / 2.0f)), 5.0f, 0.5f, -glm::radians(45.0f)));
	b2ds.push_back(new Box2D_Shape_Rect(this, ptm(w) - (5.5f * (sqrt(2.0f) / 2.0f)), ptm(h) - (5.5f * (sqrt(2.0f) / 2.0f)), 5.0f, 0.5f, -glm::radians(45.0f)));
	b2ds.push_back(new Box2D_Shape_Rect(this, ptm(w / 2.0f) + 0.5f, ptm(h / 2.0f), 3.0f, 0.5f));

	for (Box2D_Shape *b : b2ds)
	{
		b->create(b->getShape(), 1.0f);
		b->setColor(b2Color(1.0f, 1.0f, 0.0f, 1.0f));
	}

	float ww = 0.8f;
	float hh = 0.25f;

	b2FixtureDef f;
	f.density = 1.0f;
	f.friction = 0.3f;

	b2ds.push_back(new Box2D_Shape_Rect(this, 0.5f, ptm(h / 2.0f), ww, hh, 0, b2_dynamicBody));
	b2ds[7]->create(b2ds[7]->getShape(), f);
	b2ds[7]->setColor(b2Color(0.5f, 0.8f, 1.0f, 1.0f));
	b2dc.push_back(new Box2D_Constraint_Joint(this, b2ds[2], b2ds[7]));
	((Box2D_Constraint_Joint*)b2dc[0])->create(e_revoluteJoint, b2Vec2(0.5f, ptm(h / 2.0f) + 0.5f), b2Vec2(-ww, hh), 0, false);

	for (unsigned int i = 0; i < 6; i++)
	{
		b2ds.push_back(new Box2D_Shape_Rect(this, 2.5f + (float(i)*ww), ptm(h / 2.0f), ww, hh, 0.0f, b2_dynamicBody));
		b2ds[8 + i]->create(b2ds[8 + i]->getShape(), f);
		b2ds[8 + i]->setColor(b2Color(0.5f, 0.8f, 1.0f, 1.0f));

		b2dc.push_back(new Box2D_Constraint_Joint(this, b2ds[7 + i], b2ds[8 + i]));
		((Box2D_Constraint_Joint*)b2dc[1 + i])->create(e_revoluteJoint, b2Vec2(ww, hh), b2Vec2(-ww, hh), 0.0f, false, true, b2Vec2(-45, 45), true, 320000.0f);
	}

	b2dc.push_back(new Box2D_Constraint_Joint(this, b2ds[13], b2ds[6]));
	((Box2D_Constraint_Joint*)b2dc[7])->create(e_revoluteJoint, b2Vec2(ww, hh), b2Vec2(-3.0f, 0.5f), 0.0f, false);

	Box2D_Shape_Rect *r = new Box2D_Shape_Rect(this, ptm(w / 2.0f) + 4.75f, ptm(h / 2.0f), 3, hh, 0.0f, b2_dynamicBody);
	b2ds.push_back(r);
	r->create(r->getShape(), f);
	r->setColor(b2Color(1.0f, 1.0f, 1.0f, 1.0f));

	b2dc.push_back(new Box2D_Constraint_Joint(this, b2ds[6], r));
	((Box2D_Constraint_Joint*)b2dc[8])->create(e_revoluteJoint, b2Vec2(2.75, 0.0f), b2Vec2(-2, 0), 0.0f, false, false, b2Vec2(0, 0), false, 0.0f, 100000000, 2);

	fbo = new GLfbo((unsigned int)w, (unsigned int)h, false, true);
}

void World::update(void)
{
	physicsWorld->Step(1.0f / 60.0f, 6, 2);
	for (unsigned int i = 0; i < b2dc.size(); i++)
	{
		b2dc[i]->update(1.0f / 60.0f);
	}
}

void World::render(void)
{
	if (!asdfasdf)
	{
		for (Box2D_Shape *b : b2ds)
		{
			b->render();
		}
	}
	else
	{
		GLfloat w = (GLfloat)sdl_activity->getApp()->getWindow()->getWidth();
		GLfloat h = (GLfloat)sdl_activity->getApp()->getWindow()->getHeight();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		glBindFramebufferEXT(GL_FRAMEBUFFER, *fbo);
		glPushAttrib(GL_VIEWPORT_BIT | GL_ENABLE_BIT);
		glViewport(0, 0, (GLsizei)w, (GLsizei)h);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		for (Box2D_Shape *b : b2ds)
		{
			b->render();
		}
		glPopAttrib();
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
		w = 854;
		h = 500;

		if (eeee)
		{
			glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, fbo->getTexture());
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

			float sx = 0.0f, ex = w / 2.0f;
			float sy = 0.0f, ey = h / 2.0f;

			glBegin(GL_QUADS);

			//////////////////////////////////////////////////

			glTexCoord2f(0, 0);
			glVertex2f(sx, sy);

			glTexCoord2f(1, 0);
			glVertex2f(ex, sy);

			glTexCoord2f(1, 1);
			glVertex2f(ex, ey);

			glTexCoord2f(0, 1);
			glVertex2f(sx, ey);

			//////////////////////////////////////////////////

			sx = w / 2.0f;
			ex = w;

			glTexCoord2f(0, 0);
			glVertex2f(sx, sy);

			glTexCoord2f(1, 0);
			glVertex2f(ex, sy);

			glTexCoord2f(1, 1);
			glVertex2f(ex, ey);

			glTexCoord2f(0, 1);
			glVertex2f(sx, ey);

			//////////////////////////////////////////////////

			sy = h / 2.0f;
			ey = h;

			glTexCoord2f(0, 0);
			glVertex2f(sx, sy);

			glTexCoord2f(1, 0);
			glVertex2f(ex, sy);

			glTexCoord2f(1, 1);
			glVertex2f(ex, ey);

			glTexCoord2f(0, 1);
			glVertex2f(sx, ey);

			//////////////////////////////////////////////////

			sx = 0.0f;
			ex = w / 2.0f;
			sy = h / 2.0f;
			ey = h;

			glTexCoord2f(0, 0);
			glVertex2f(sx, sy);

			glTexCoord2f(1, 0);
			glVertex2f(ex, sy);

			glTexCoord2f(1, 1);
			glVertex2f(ex, ey);

			glTexCoord2f(0, 1);
			glVertex2f(sx, ey);

			//////////////////////////////////////////////////
			glEnd();

			glBindTexture(GL_TEXTURE_2D, 0);
			glPopMatrix();
		}
		else
		{
			glPushMatrix();
			glBindTexture(GL_TEXTURE_2D, fbo->getTexture());
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

			float sx = 0.0f, ex = w;
			float sy = 0.0f, ey = h;

			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex2f(sx, sy);

			glTexCoord2f(1, 0);
			glVertex2f(ex, sy);

			glTexCoord2f(1, 1);
			glVertex2f(ex, ey);

			glTexCoord2f(0, 1);
			glVertex2f(sx, ey);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, 0);
			glPopMatrix();
		}
	}
}

void World::dispose(void)
{
}

void World::onEvent(SDL_Event& e)
{
	GLfloat w = (GLfloat)sdl_activity->getApp()->getWindow()->getWidth();
	GLfloat h = (GLfloat)sdl_activity->getApp()->getWindow()->getHeight();

	if (e.type == SDL_WINDOWEVENT)
	{
		if (e.window.event == SDL_WINDOWEVENT_RESIZED)
		{
			fbo->resize((unsigned int)w, (unsigned int)h);
		}
	}

	if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_f)
	{
		asdfasdf = !asdfasdf;
	}
	if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_e)
	{
		if(asdfasdf) eeee = !eeee;
	}
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		float bx, by, x, y;
		if (eeee)
		{
			bx = e.button.x > w / 2.0f ? e.button.x - w / 2.0f : e.button.x;
			by = e.button.y > h / 2.0f ? e.button.y - h / 2.0f : e.button.y;
			x = (854.0f / w) * (bx * 2.0f);
			y = ((500.0f / h) * (h - by * 2.0f));
		}
		else
		{
			bx = e.button.x;
			by = e.button.y;
			x = (854.0f / w) * (bx);
			y = ((500.0f / h) * (h - by));
		}
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			b2FixtureDef f;
			f.density = 1.0f;
			f.friction = 0.3f;

			Box2D_Shape_Rect *b = new Box2D_Shape_Rect(this, ptm(x), ptm(y), 0.5f, 0.5f, 0.0f, b2_dynamicBody);
			b->setColor(b2Color(0.125f, 1.0f, 0.125f, 1.0f));
			b->create(b->getShape(), f);
			b2ds.push_back(b);
		}
		if (e.button.button == SDL_BUTTON_MIDDLE)
		{
			b2FixtureDef f;
			f.density = 1.0f;
			f.friction = 0.5f;
			f.restitution = 0.0f;
			float s = 0.375f;
			Box2D_Shape_Circle *b = new Box2D_Shape_Circle(this, ptm(x), ptm(y), s, 0.0f, b2_dynamicBody);
			b->setColor(b2Color(1.0f, 0.125f, 0.125f, 1.0f));
			b->create(b->getShape(), f);
			b2ds.push_back(b);
		}
		if (e.button.button == SDL_BUTTON_RIGHT)
		{
			b2FixtureDef f;
			f.density = 1.0f;
			f.friction = 0.3f;
			f.restitution = 0.4f;
			float s = 0.25f;
			Box2D_Shape_Rect *b = new Box2D_Shape_Rect(this, ptm(x), ptm(y), s, s, 0.0f, b2_dynamicBody);
			b->setColor(b2Color(0.125f, 0.125f, 1.0f, 1.0f));
			b->create(b->getShape(), f);
			b2ds.push_back(b);
		}
	}
}

SDL_Activity* World::getActivity(void)
{
	return sdl_activity;
}

b2Vec2& World::getGravity(void)
{
	return gravity;
}

b2World* World::getPhysicsWorld(void)
{
	return physicsWorld;
}

void World::initializePhysics(void)
{
	if (physicsInitialized) return;
	physicsInitialized = true;
	GLfloat w = (GLfloat)sdl_activity->getApp()->getWindow()->getWidth();
	GLfloat h = (GLfloat)sdl_activity->getApp()->getWindow()->getHeight();
	bool ignoreSleeping = true;
	physicsWorld = new b2World(gravity);
	physicsWorld->SetAllowSleeping(false);
	physicsWorld->SetContinuousPhysics(false);
	physicsWorld->SetDebugDraw(&debugDraw);
	debugDraw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);// | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_jointBit);
}

float World::mtp(float meters)
{
	return meters * unitRatio;
}

float World::ptm(float pixels)
{
	return pixels / unitRatio;
}