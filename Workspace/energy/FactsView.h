#ifndef FactsView_h
#define FactsView_h

#define S_COLUMNS F("Mo Tu  We Th Fr  Sa Su")

class FactsView{

  public: FactsView(void);
    void setup();
    void loop( uint16_t days);
    void loop();
};
#endif
