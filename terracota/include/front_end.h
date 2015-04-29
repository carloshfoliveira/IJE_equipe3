#ifndef FRONT_END_H
#define FRONT_END_H

#include "level.h"

#include "mousebuttonevent.h"
#include "joystickevent.h"
#include "mousemotionevent.h"

class Image;

class FrontEnd : public Level
{
public:
    FrontEnd(const string& next, const string& image,
        unsigned long duration = 3000);

private:
    Image *m_image;
    unsigned long m_start;
    unsigned long m_duration;
    int m_x, m_y;

    void update_self(unsigned long elapsed);
    void draw_self();
};

#endif

