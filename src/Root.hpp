#include <Application.hpp>
#include <Message.hpp>
#include <Navigator.hpp>
#include <outputs/Output.hpp>
#include <inputs/TempSensor.hpp>

#pragma once

class Root : public Application
{
  public:
    Root();
    ~Root();

    void init(unsigned long ms) override;
    void tick(unsigned long ms) override;

  protected:
    void publish(Message *message) override;

    Navigator           navigator;
    Outputs::Output     *output;
    Inputs::TempSensor  indoor;
    Inputs::TempSensor  outdoor;
};
