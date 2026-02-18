#include <memory>
#include <cassert>
#include "Event_manager.h"
#include "Statement.h"
//global event manager
Event_manager em;


Event_manager::~Event_manager() {
  for(auto& handlers : eventlist){
    for(const Statement* stmt : handlers){
      delete stmt;
    }
 }
}

void Event_manager::execute_handlers(Window::Keystroke keystroke) const {
/*void execute_handlers(Window::Keystroke keystroke) const
Loop through the private data, calling Statement::execute() on each head Statement* (head of a linked list)
associated with the input keystroke. 
This function is called automatically by the provided GPL classes.*/

  for(const Statement* block : eventlist[keystroke])
    block->execute();
    
}

void Event_manager::add_handler(Window::Keystroke keystroke, const Statement* handler){
  eventlist[keystroke].push_back(handler);
}// on block calls. add

