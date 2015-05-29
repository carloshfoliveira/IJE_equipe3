#include "layer.h"
#include <core/environment.h>

#include <iostream>
using namespace std;
Layer::Layer(ObjectID id,
	  shared_ptr<Texture> texture,
	  double x, double y, double w, double h)
	: Object(nullptr,id),m_texture(texture),m_clip(Rect(x,y,w,h)) 
{
	set_dimensions(w,h);
}

Layer::~Layer()
{
}

double
Layer::ymin()
{
	return y()+h();
}
double
Layer::xmin()
{
	return x()-w();	
}

void
Layer::draw()
{
	Environment* env = Environment::get_instance();
	if (not m_clip.w() and not m_clip.h())
    	env->canvas->draw(m_texture.get());
	else
    	env->canvas->draw(m_texture.get(),m_clip,x(),y());
}

pair<double,double>
Layer::position_clip()
{
	return make_pair(m_clip.x(),m_clip.y());
}

pair<double,double> 
Layer::dimension_clip()
{
	return make_pair(m_clip.w(),m_clip.h());
}

void 
Layer::set_clip_position(double x,double y )
{
	m_clip.set_position(x,y);
}

void 
Layer::set_clip_dimension(double w,double h)
{
	m_clip.set_dimensions(w,h);
}


void 
Layer::reposition(pair<double,double> moviment)
{
	double mx = moviment.first;
	double my = moviment.second;

	if( mx > 0 ) set_x((x()-0.5));
	if( mx < 0 ) set_x((x()+0.5));
	if (my > 0 ) set_y((y()-0.5));
	if (my < 0 ) set_y((y()+0.5));
}