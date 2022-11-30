#include <inputs/ButtonGroup.hpp>

namespace Inputs {

  ButtonGroup::ButtonGroup(Button *up, Button *down, Button *left, Button *right, Button *select)
    : Lifecycle()
    , up(up)
    , down(down)
    , left(left)
    , right(right)
    , select(select)
  {}

  ButtonGroup::~ButtonGroup()
  {}

  void ButtonGroup::init(unsigned long ms)
  {
    if (up != NULL) up->init(ms);
    if (down != NULL) down->init(ms);
    if (left != NULL) left->init(ms);
    if (right != NULL) right->init(ms);
    if (select != NULL) select->init(ms);
  }

  void ButtonGroup::tick(unsigned long ms)
  {
    if (up != NULL) up->tick(ms);
    if (down != NULL) down->tick(ms);
    if (left != NULL) left->tick(ms);
    if (right != NULL) right->tick(ms);
    if (select != NULL) select->tick(ms);
  }

  void ButtonGroup::message(Message *msg)
  {
    if (up != NULL) up->message(msg);
    if (down != NULL) down->message(msg);
    if (left != NULL) left->message(msg);
    if (right != NULL) right->message(msg);
    if (select != NULL) select->message(msg);
  }
};
