#include "dodecahedron.hpp"

#include <cstddef>

enum class TraverseType: size_t {
    TO      = 0,
    FROM    = 1,
    SPECIAL = 2,
};

Neighbours Dodecahedron::get_neighbouring_nodes_of(size_t node_index) {
    Neighbours n;
    n[0] = edges[nodes[node_index].edge_index[0]].traverse_from(node_index);
    n[1] = edges[nodes[node_index].edge_index[1]].traverse_from(node_index);
    n[2] = edges[nodes[node_index].edge_index[2]].traverse_from(node_index);
    return n;
}

Dodecahedron::Dodecahedron() {
    nodes[0].edge_index[0] = 5;
    nodes[0].edge_index[1] = 0;
    nodes[0].edge_index[2] = 1;

    nodes[1].edge_index[0] = 6;
    nodes[1].edge_index[1] = 1;
    nodes[1].edge_index[2] = 2;

    nodes[2].edge_index[0] = 7;
    nodes[2].edge_index[1] = 2;
    nodes[2].edge_index[2] = 3;

    nodes[3].edge_index[0] = 8;
    nodes[3].edge_index[1] = 3;
    nodes[3].edge_index[2] = 4;

    nodes[4].edge_index[0] = 9;
    nodes[4].edge_index[1] = 4;
    nodes[4].edge_index[2] = 0;

    nodes[5].edge_index[0] = 19;
    nodes[5].edge_index[1] = 5;
    nodes[5].edge_index[2] = 10;

    nodes[6].edge_index[0] = 15;
    nodes[6].edge_index[1] = 6;
    nodes[6].edge_index[2] = 11;

    nodes[7].edge_index[0] = 16;
    nodes[7].edge_index[1] = 7;
    nodes[7].edge_index[2] = 12;

    nodes[8].edge_index[0] = 17;
    nodes[8].edge_index[1] = 8;
    nodes[8].edge_index[2] = 13;

    nodes[9].edge_index[0] = 18;
    nodes[9].edge_index[1] = 9;
    nodes[9].edge_index[2] = 14;

    nodes[10].edge_index[0] = 20;
    nodes[10].edge_index[1] = 15;
    nodes[10].edge_index[2] = 10;

    nodes[11].edge_index[0] = 21;
    nodes[11].edge_index[1] = 16;
    nodes[11].edge_index[2] = 11;

    nodes[12].edge_index[0] = 22;
    nodes[12].edge_index[1] = 17;
    nodes[12].edge_index[2] = 12;

    nodes[13].edge_index[0] = 23;
    nodes[13].edge_index[1] = 18;
    nodes[13].edge_index[2] = 13;

    nodes[14].edge_index[0] = 24;
    nodes[14].edge_index[1] = 19;
    nodes[14].edge_index[2] = 14;

    nodes[15].edge_index[0] = 25;
    nodes[15].edge_index[1] = 20;
    nodes[15].edge_index[2] = 29;

    nodes[16].edge_index[0] = 26;
    nodes[16].edge_index[1] = 21;
    nodes[16].edge_index[2] = 25;

    nodes[17].edge_index[0] = 27;
    nodes[17].edge_index[1] = 22;
    nodes[17].edge_index[2] = 26;

    nodes[18].edge_index[0] = 28;
    nodes[18].edge_index[1] = 23;
    nodes[18].edge_index[2] = 27;

    nodes[19].edge_index[0] = 29;
    nodes[19].edge_index[1] = 24;
    nodes[19].edge_index[2] = 28;

    edges[0].node_index[0] = 4;
    edges[0].node_index[1] = 0;

    edges[1].node_index[0] = 0;
    edges[1].node_index[1] = 1;

    edges[2].node_index[0] = 1;
    edges[2].node_index[1] = 2;

    edges[3].node_index[0] = 2;
    edges[3].node_index[1] = 3;

    edges[4].node_index[0] = 3;
    edges[4].node_index[1] = 4;

    edges[5].node_index[0] = 0;
    edges[5].node_index[1] = 5;

    edges[6].node_index[0] = 1;
    edges[6].node_index[1] = 6;

    edges[7].node_index[0] = 2;
    edges[7].node_index[1] = 7;

    edges[8].node_index[0] = 3;
    edges[8].node_index[1] = 8;

    edges[9].node_index[0] = 4;
    edges[9].node_index[1] = 9;

    edges[10].node_index[0] = 5;
    edges[10].node_index[1] = 10;

    edges[11].node_index[0] = 6;
    edges[11].node_index[1] = 11;

    edges[12].node_index[0] = 7;
    edges[12].node_index[1] = 12;

    edges[13].node_index[0] = 8;
    edges[13].node_index[1] = 13;

    edges[14].node_index[0] = 9;
    edges[14].node_index[1] = 14;

    edges[15].node_index[0] = 6;
    edges[15].node_index[1] = 10;

    edges[16].node_index[0] = 7;
    edges[16].node_index[1] = 11;

    edges[17].node_index[0] = 8;
    edges[17].node_index[1] = 12;

    edges[18].node_index[0] = 9;
    edges[18].node_index[1] = 13;

    edges[19].node_index[0] = 5;
    edges[19].node_index[1] = 14;

    edges[20].node_index[0] = 10;
    edges[20].node_index[1] = 15;

    edges[21].node_index[0] = 11;
    edges[21].node_index[1] = 16;

    edges[22].node_index[0] = 12;
    edges[22].node_index[1] = 17;

    edges[23].node_index[0] = 13;
    edges[23].node_index[1] = 18;

    edges[24].node_index[0] = 14;
    edges[24].node_index[1] = 19;

    edges[25].node_index[0] = 15;
    edges[25].node_index[1] = 16;

    edges[26].node_index[0] = 16;
    edges[26].node_index[1] = 17;

    edges[27].node_index[0] = 17;
    edges[27].node_index[1] = 18;

    edges[28].node_index[0] = 18;
    edges[28].node_index[1] = 19;

    edges[29].node_index[0] = 19;
    edges[29].node_index[1] = 15;
}
