#include "FastLED.h"

#define NUM_NODES 20

class Node {
  public:
    Node* to;
    Node* from;
    Node* special;
    CRGB *first;
    CRGB *last;
};

class Dodecahedron {
  public:
    Dodecahedron();
    void set_segment(size_t index, CRGB *first, CRGB *last);

  private:
    Node nodes[NUM_NODES];
};
