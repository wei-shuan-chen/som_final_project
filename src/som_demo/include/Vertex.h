#ifndef VERTEX_H
#define VERTEX_H

struct Vertex{
    struct Position{
        float x, y, z;
    };

    struct Normal {
        float xn, yn, zn;
    };
    struct Color{
        float r, g, b;
    };

    struct Texcoord {
        float s,t;
    };

    struct Raypos
    {
        float x, y, z;
    };

    Position position;
    Normal normal;
    Color color;
    Texcoord texcoord;
    Raypos raypos;
};

#endif