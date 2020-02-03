#ifndef ModelView_h
#define ModelView_h

#include "Model.h"

#define S_MODEL_TITLE F("HOLIDAY PARK (MWh)")
#define DEFAULT_XPOS 1
#define DEFAULT_YPOS 18

#define S_USED F("USED:")
#define S_GEN F("GEN:")
#define S_MJS F("MJ")
#define S_BOOKINGS F("Bookings:")

static Model model;

class ModelView {

  public: ModelView(void);

    enum Options {
      BARE = 0,
      CALENDAR = 1,
      SLIDER = 2,
      TRANSFORMER = 3
    };

    void setup( Options option );
    void setup( Options option, bool next);
    void loop();

  private: byte x, y;
    const char outstr[1];
    const char data[6];
    Options option;
    bool next;
};
#endif
