#ifndef TextView_h
#define TextView_h

class TextView {
  private:
    const char data[12] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'};
    
  public: TextView(void);
    void setup( uint16_t colour, String title, String text);
};
#endif
