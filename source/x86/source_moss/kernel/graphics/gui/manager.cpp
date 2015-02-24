#include "manager.h"

#include "../../input/mouse.h"

#include "../vesa/framebuffer.h"
#include "../color.h"

#include "frame.h"
#include "mouse.h"


namespace MOSS { namespace Graphics { namespace GUI {


Manager::Manager(void) {
	mouse = new Mouse();
}
Manager::~Manager(void) {
	delete mouse;
}

void Manager::update(void) {
	for (int i=0;i<frames.size;++i) {
		if (!frames[i]->alive) {
			delete frames[i];
			frames.remove(i);
		}
	}
}

void Manager::handle_mouse(Input::Mouse::   EventMouseMove const& event) {
	mouse->x = event.x;
	mouse->y = event.y;

	for (int i=0;i<frames.size;++i) {
		if (frames[i]->handle_mouse(event)) break;
	}
}
void Manager::handle_mouse(Input::Mouse::  EventMouseClick const& event) {
	mouse->buttons[event.index] =  true;

	for (int i=0;i<frames.size;++i) {
		if (frames[i]->handle_mouse(event)) break;
	}
}
void Manager::handle_mouse(Input::Mouse::EventMouseUnclick const& event) {
	mouse->buttons[event.index] = false;

	for (int i=0;i<frames.size;++i) {
		if (frames[i]->handle_mouse(event)) break;
	}
}

void Manager::add_frame(MOSST::String const& title, int x,int y,int w,int h) {
	Frame* frame = new Frame(nullptr, x,y,w,h);
	frame->set_title(title);

	frames.insert_back(frame);
}

void Manager::draw(VESA::Framebuffer* framebuffer) const {
	framebuffer->draw_fill(Color(0,0,0));

	for (int i=0;i<frames.size;++i) {
		frames[i]->draw(framebuffer);
	}

	mouse->draw(framebuffer);
}


}}}
