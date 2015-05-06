#include "frontend.h"

#include "environment.h"
#include "image.h"
#include "mousebuttonevent.h"
#include "joystickevent.h"
#include "keyboardevent.h"

FrontEnd::FrontEnd(const string& next, const string& image,
			       unsigned long duration )
    : Level("",next), m_image(nullptr), m_start(0), m_duration(duration)
{
    Environment* env = Environment::get_instance();
    
    env->events_manager->register_mouse_button_event_listener(this);
    env->events_manager->register_keyboard_event_listener(this);
    env->events_manager->register_joystick_event_listener(this);
 
    m_image  = env->resources_manager->get_image(image);


    m_x = (env->canvas->w() - m_image->w())/2;
    m_y = (env->canvas->h() - m_image->h())/2;
}

FrontEnd::~FrontEnd()
{
    Environment* env = Environment::get_instance();
    
    env->events_manager->unregister_mouse_button_event_listener(this);
    env->events_manager->unregister_keyboard_event_listener(this);
    env->events_manager->unregister_joystick_event_listener(this);
}

void
FrontEnd::draw_self()
{
    Environment* env = Environment::get_instance();
    env->canvas->clear();
    env->canvas->draw(m_image.get(), m_x, m_y);
}

void
FrontEnd::update_self(unsigned long elapsed)
{
    if (not m_start)
        m_start = elapsed;

    if (elapsed - m_start > m_duration)
        m_done = true;
}

bool
FrontEnd::onMouseButtonEvent(const MouseButtonEvent& event)
{
    if( event.state() == MouseButtonEvent::PRESSED)
        m_done = true;

    return m_done;
}

bool
FrontEnd::onJoyStickEvent(const JoyStickEvent& event)
{
    if( event.state() == JoyStickEvent::PRESSED)
        m_done = true;

    return m_done;
}

bool
FrontEnd::onKeyboardEvent(const KeyboardEvent& event)
{
    if (event.state() == KeyboardEvent::PRESSED)
        m_done = true;  

    return m_done;
}
