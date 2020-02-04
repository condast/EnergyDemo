#ifndef Wizard_h
#define Wizard_h

#include "View.h"
#include "IntroView.h"
#include "TextView.h"
#include "ModelView.h"
#include "FactsView.h"
#include "Outcome.h"

#define S_INTRO_TITLE F("SELECT A GAME:")
#define S_MENU_1 F("PLAN YOUR ENERGY")
#define S_MENU_2 F("PLACE POWER STATION")
#define S_MENU_3 F("OVERVIEW")

static View view;
static IntroView introView;
static TextView textView;
static ModelView modelView;
static FactsView factsView;
static Outcome outcome;

class Wizard {

  private: ModelView::Options option;
  
  public: Wizard(void);
    /**
       States
    */
    enum Steps {
      MENU = 0,
      EXPLANATION = 1,
      FACTS = 2,
      MODEL = 3,
      OUTCOME = 4
    };

    byte step;
    void setup();
    void home();
    byte next();
    void update();
    void loop();

};
#endif
