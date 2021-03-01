#include <cstddef>

#include "dodecahedron.hpp"

void Dodecahedron::set_segment(size_t index, CRGB *first, CRGB *last) {
  if (index >= NUM_NODES) {
    return;
  }
  nodes[index].first = first;
  nodes[index].last = last;
}

Dodecahedron::Dodecahedron() {
  nodes[0].to = &nodes[5];
  nodes[0].from = &nodes[4];
  nodes[0].special = &nodes[1];

  nodes[1].to = &nodes[6];
  nodes[1].from = &nodes[0];
  nodes[1].special = &nodes[2];

  nodes[2].to = &nodes[7];
  nodes[2].from = &nodes[1];
  nodes[2].special = &nodes[3];

  nodes[3].to = &nodes[8];
  nodes[3].from = &nodes[2];
  nodes[3].special = &nodes[4];

  nodes[4].to = &nodes[9];
  nodes[4].from = &nodes[3];
  nodes[4].special = &nodes[0];

  nodes[5].to = &nodes[14];
  nodes[5].from = &nodes[0];
  nodes[5].special = &nodes[10];

  nodes[6].to = &nodes[10];
  nodes[6].from = &nodes[1];
  nodes[6].special = &nodes[11];

  nodes[7].to = &nodes[11];
  nodes[7].from = &nodes[2];
  nodes[7].special = &nodes[12];

  nodes[8].to = &nodes[12];
  nodes[8].from = &nodes[3];
  nodes[8].special = &nodes[13];

  nodes[9].to = &nodes[13];
  nodes[9].from = &nodes[4];
  nodes[9].special = &nodes[14];

  nodes[10].to = &nodes[15];
  nodes[10].from = &nodes[6];
  nodes[10].special = &nodes[5];

  nodes[11].to = &nodes[16];
  nodes[11].from = &nodes[7];
  nodes[11].special = &nodes[6];

  nodes[12].to = &nodes[17];
  nodes[12].from = &nodes[8];
  nodes[12].special = &nodes[7];

  nodes[13].to = &nodes[18];
  nodes[13].from = &nodes[9];
  nodes[13].special = &nodes[8];

  nodes[14].to = &nodes[19];
  nodes[14].from = &nodes[5];
  nodes[14].special = &nodes[9];

  nodes[15].to = &nodes[16];
  nodes[15].from = &nodes[10];
  nodes[15].special = &nodes[19];

  nodes[16].to = &nodes[17];
  nodes[16].from = &nodes[11];
  nodes[16].special = &nodes[15];

  nodes[17].to = &nodes[18];
  nodes[17].from = &nodes[12];
  nodes[17].special = &nodes[16];

  nodes[18].to = &nodes[19];
  nodes[18].from = &nodes[13];
  nodes[18].special = &nodes[17];

  nodes[19].to = &nodes[15];
  nodes[19].from = &nodes[14];
  nodes[19].special = &nodes[18];
}
