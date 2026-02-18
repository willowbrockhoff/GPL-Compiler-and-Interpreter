/***

  Use this file and Event_manager.cpp w/o modification in p4.

  These files serve as a starting point for the Event_manager class in p5.

***/

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <memory>
#include <iostream>
#include <string>
#include <vector>

#include "Window.h" // for Keystroke enum

class Statement;

class Event_manager
{
  public:

    Event_manager() : eventlist(26) {}
    void execute_handlers(Window::Keystroke keystroke) const;
    //execute will look smth like. slightly more complex bc strcture
    /*{
      data_structure[keystroke]->execute();
    }*/
    void add_handler(Window::Keystroke, const Statement*); // on block calls. add

    ~Event_manager();

    Event_manager(const Event_manager&) = delete; 
    const Event_manager &operator=(const Event_manager&) = delete;

  private:
  
  std::vector<std::vector<const Statement*>> eventlist;
  // add attribute that can store stmt pointers for each event type
  // event types are Windows.h lines 36-62
  // create a vector of 26 items to avoid seg faulting
  // needs to be able to store stmt poitners for each keystroke, but for each keystroke be able to store 
  // multiple statment pointers. 
  //could be vector of vectors, map of vectors
  /*
  vector<const Statement*> eventlist; // I have zero items. 
  i will crash if i do smth like
  eventlist[keystroke]->execute.
  this is correct vector<const Statement*> eventlist(26); 
  */

};

#endif
