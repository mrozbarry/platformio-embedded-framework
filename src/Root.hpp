#include <lib/Lifecycle.hpp>
#include <Message.hpp>
#include <lib/Navigator.hpp>
#include <outputs/Output.hpp>
#include <inputs/TempSensor.hpp>

#pragma once

#ifndef ROOT_QUEUE_SIZE
#define ROOT_QUEUE_SIZE 20
#endif

class Root : public Lifecycle
{
  public:
    Root();
    ~Root();

    void init(unsigned long ms);
    void tick(unsigned long ms);
    void publish(Message *message);
    void publishNow(Message *message);
    void handleMessages(unsigned long ms);

  protected:
    Navigator           navigator;
    Outputs::Output     *output;
    Inputs::TempSensor  indoor;
    Inputs::TempSensor  outdoor;

    Message             *queue[ROOT_QUEUE_SIZE];
};

extern Root root;
