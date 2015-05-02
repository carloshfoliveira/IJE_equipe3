#include "titlescreen.h"

#include "environment.h"
#include "button.h"

#include <iostream>

using namespace std;

TitleScreen::TitleScreen()
    : Level("title")
{
    Environment* env = Environment::get_instance();
    
    double w  = env->canvas->w();
    double h  = env->canvas->h();

    double bw = 100;
    double bh = 50;

    double bx = (w - bw)/2;
    double by = h/2;

    Button* ok = new Button(this,"ok", bx, by, bw , bh);
    Button* exit = new Button(this,"exit", bx, by+bh+80, bw, bh, Color::RED);
	Button* settings = new Button(this,"settings",bx,by+bh+20,bw,bh,Color::YELLOW);
    
    ok->add_observer(this);
    settings->add_observer(this);
    exit->add_observer(this);
        
    add_child(settings);
    add_child(ok);
    add_child(exit);
}

TitleScreen::~TitleScreen()
{
}

void 
TitleScreen::draw_self()
{
    Environment* env = Environment::get_instance();
    env->canvas->clear(Color::WHITE);
}

bool
TitleScreen::on_message(Object* object, MessageID id, Parameters)
{
    if (id != Button::clickedID)
    {
        return false;
    }
    
    Button* button = dynamic_cast<Button *>(object);
    
    if (not button)
        return false;
    if(button->id() == "ok")
        m_next = "stage1";
	if (button->id() == "settings")
		m_next = "settings";

    m_done = true;
    return true;
}









