#include <Lifecycle.hpp>
#include <Application.hpp>

Lifecycle::Lifecycle()
{}

Lifecycle::~Lifecycle()
{}

Application *Lifecycle::app()
{
  return Application::get();
}

void Lifecycle::init(unsigned long ms)
{}

void Lifecycle::tick(unsigned long)
{}

void Lifecycle::message(Message *message)
{}
