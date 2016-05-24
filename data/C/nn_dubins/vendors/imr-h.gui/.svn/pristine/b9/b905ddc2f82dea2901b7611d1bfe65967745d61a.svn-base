/*
 * File name: guihandler.cc
 * Date:      2005/11/18 16:30
 * Author:    Jan Faigl
 */

#include "logging.h"
#include "guihandler.h"

using namespace imr::gui;

//----------------------------------------------------------------------------
//Class CGuiHandler 
//----------------------------------------------------------------------------
CGuiHandler::CGuiHandler(int iMaxEvents) : MAX_EVENTS(iMaxEvents) {
   listenersByType = new Listener*[Event::NUMBER];
   for (int i = 0; i < Event::NUMBER; ++i) {
      listenersByType[i] = 0;
   }
}

//----------------------------------------------------------------------------
CGuiHandler::~CGuiHandler() {
   for (int i = 0; i < Event::NUMBER; ++i) {
      if (listenersByType[i] != 0) {
         delete listenersByType[i];
      }
   }
   It end = listeners.end();
   for (It it = listeners.begin(); it != end; ++it) {
      delete *it;
   }
   //cleanup Event
   /* ItEvent endEv = Event.end();
      if (Event.size() > 0) {
      WARN("Handler desctrucotor: " + std::string(Event.size() + " Event are in guihandler queue, they will be deleted"));
      for (ItEvent itEv = Event.begin(); itEv != endEv; itEv++) {
      delete (*itEv);
      }
      Event.clear();
      }*/
}

//----------------------------------------------------------------------------
bool CGuiHandler::registerListener(Listener * listener) {
   ScopedLock lk(mutex);
   bool ret = true;
   listeners.push_back(listener);
   return ret;
}

//----------------------------------------------------------------------------
bool CGuiHandler::registerListener(Listener * listener, Event::TType eventType) {
   ScopedLock lk(mutex);
   bool ret = false;
   if (eventType > 0) {
      if (listenersByType[eventType] == 0) {
         listenersByType[eventType] = listener;
         ret = true;
      } else {
         WARN("Event type:" + Event::str(eventType) + " is already handled");
      }
   } else {
      WARN("Listener can not be registered with specified event type " + Event::str(eventType));
   }
   return ret;
}

//----------------------------------------------------------------------------
void CGuiHandler::unregisterListener(Listener * listener) {
   ScopedLock lk(mutex);
   for (It it = listeners.begin(); it != listeners.end(); it++) {
      if ((*it) == listener) {
         listeners.erase(it);
         break;
      }
   }
}

/*
//----------------------------------------------------------------------------
void CGuiHandler::addEvent(Event & event) {
if (Event.size() < MAX_EVENTS) {
Event.push_back(new Event(event)); 
} else {
ERROR("Maximum number of Event reached, event is not added");
}
}

//----------------------------------------------------------------------------
void CGuiHandler::addEvent(Event * event) {
if (Event.size() < MAX_EVENTS) {
Event.push_back(event); 
} else {
ERROR("Maximum number of Event reached, event is not added");
}
} */

//----------------------------------------------------------------------------
bool CGuiHandler::handle(Event & event) {
   bool handled = false;
   if (listenersByType[event.type] != 0) {
      ScopedLock lk(mutex);
      handled = listenersByType[event.type]->handle(event);
   }
   if (!handled) {
      //find listener in chain of listeners
      It it, end = listeners.end();
      ScopedLock lk(mutex);
      for (it = listeners.begin(); it != end; ++it) {
         if ((*it)->handle(event)) {
            handled = true;
            break;
         }
      }
   }
   /*     if (!handled) {
          WARN("Event "+ event->str() + " has not listener!");
          }*/
   return handled;
   //     Event.erase(Event.begin());
   //   delete event;
   /*  if (Event.size() > 0) {
       Event * event = *(Event.begin());
       bool handled = false;
       if (listenersByType[event->type] != 0) {
       handled = listenersByType[event->type]->handle(event);
       }
       if (!handled) {
   //find listener
   It it, end = listeners.end();
   for (it = listeners.begin(); it != end; ++it) {
   if ((*it)->handle(event)) {
   handled = true;
   break;
   }
   }
   }
   if (!handled) {
   WARN("Event "+ event->str() + " has not listener!");
   }
   Event.erase(Event.begin());
   delete event;
   }
   return (Event.size() > 0);
   */
}

/* end of guihandler.cc */
