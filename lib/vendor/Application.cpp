#include <Application.hpp>
#include <debug/Debug.hpp>

Application *Application::app = NULL;

Application *Application::get()
{
  return app;
}

Application *Application::set(Application *newApplication)
{
  app = newApplication;
  return app;
}

Application::Application()
  : Lifecycle()
{
  for (uint8_t i = 0; i < APPLICATION_MESSAGE_QUEUE_SIZE; i++) {
    messageQueue[i] = NULL;
  }
}

Application::~Application()
{
  for (uint8_t i = 0; i < APPLICATION_MESSAGE_QUEUE_SIZE; i++) {
    if (messageQueue[i] == NULL) continue;
    delete messageQueue[i];
  }
}

void Application::queue(Message *message)
{
  if (message == NULL) return;

  for (uint8_t i = 0; i < APPLICATION_MESSAGE_QUEUE_SIZE; i++) {
    if (messageQueue[i] != NULL) continue;
    messageQueue[i] = message;
    return;
  }

  debug("Unable to messageQueue message!");
}

void Application::handleMessages(unsigned long ms)
{
  for(uint8_t i = 0; i < APPLICATION_MESSAGE_QUEUE_SIZE; i++) {
    if (messageQueue[i] == NULL) continue;
    if (!messageQueue[i]->ready(ms)) continue;

    if (messageQueue[i]->is(Message::Type::MESSAGE_GROUP)) {
    }


    } else {
      publish(messageQueue[i]);
    }

    delete messageQueue[i];
    messageQueue[i] = NULL;
  }

  for(uint8_t i = 0; i < APPLICATION_MESSAGE_QUEUE_SIZE; i++) {
    if (messageQueue[i] != NULL) continue;
    for(uint8_t j = i + 1; j < APPLICATION_MESSAGE_QUEUE_SIZE; j++) {
      if (messageQueue[j] == NULL) continue;
      messageQueue[i] = messageQueue[j];
      messageQueue[j] = NULL;
      break;
    }
  }
}

void Application::publish(Message *message)
{}
