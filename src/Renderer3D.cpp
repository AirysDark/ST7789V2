#include "Renderer3D.h"
#include "Color.h"
#include <math.h>

#include "Graphics.h"

Renderer3D renderer3D;

// =====================================================
// CONSTRUCTOR
// =====================================================

Renderer3D::Renderer3D()
{
    camera.position.x = 0.0f;
    camera.position.y = 0.0f;
    camera.position.z = -100.0f;

    camera.pitch = 0.0f;
    camera.yaw   = 0.0f;
    camera.roll  = 0.0f;

    camera.fov = 120.0f;
}

// =====================================================
// CAMERA
// =====================================================

void Renderer3D::setCamera(
    float x,
    float y,
    float z
)
{
    camera.position.x = x;
    camera.position.y = y;
    camera.position.z = z;
}

// =====================================================
// PROJECT
// =====================================================

void Renderer3D::project(
    const Vec3& in,
    int16_t& x,
    int16_t& y
)
{
    float z =
        in.z -
        camera.position.z;

    if(z < 1.0f)
    {
        z = 1.0f;
    }

    float scale =
        camera.fov / z;

    x =
        140 +
        (in.x * scale);

    y =
        120 -
        (in.y * scale);
}

// =====================================================
// LINE
// =====================================================

void Renderer3D::drawLine3D(
    Vec3 a,
    Vec3 b,
    uint16_t color
)
{
    int16_t x1;
    int16_t y1;

    int16_t x2;
    int16_t y2;

    project(a, x1, y1);
    project(b, x2, y2);

    graphics.drawLine(
        x1,
        y1,
        x2,
        y2,
        color
    );
}

// =====================================================
// TRIANGLE
// =====================================================

void Renderer3D::drawTriangle3D(
    Triangle3D tri
)
{
    drawLine3D(
        tri.v1,
        tri.v2,
        tri.color
    );

    drawLine3D(
        tri.v2,
        tri.v3,
        tri.color
    );

    drawLine3D(
        tri.v3,
        tri.v1,
        tri.color
    );
}

// =====================================================
// FILLED TRIANGLE
// =====================================================

void Renderer3D::fillTriangle3D(
    Vec3 a,
    Vec3 b,
    Vec3 c,
    uint16_t color
)
{
    int16_t x1,y1;
    int16_t x2,y2;
    int16_t x3,y3;

    project(a,x1,y1);
    project(b,x2,y2);
    project(c,x3,y3);

    graphics.fillTriangle(
        x1,y1,
        x2,y2,
        x3,y3,
        color
    );
}

// =====================================================
// BACKFACE CULLING
// =====================================================

bool Renderer3D::backfaceCull(
    Vec3 a,
    Vec3 b,
    Vec3 c
)
{
    float ax = b.x - a.x;
    float ay = b.y - a.y;

    float bx = c.x - a.x;
    float by = c.y - a.y;

    float cross =
        ax * by -
        ay * bx;

    return cross < 0;
}

// =====================================================
// TRIANGLE DEPTH
// =====================================================

float Renderer3D::triangleDepth(
    Vec3 a,
    Vec3 b,
    Vec3 c
)
{
    return
        (a.z + b.z + c.z)
        * 0.333333f;
}



// =====================================================
// TRANSLATE
// =====================================================

void Renderer3D::translate(
    Vec3& v,
    float x,
    float y,
    float z
)
{
    v.x += x;
    v.y += y;
    v.z += z;
}

// =====================================================
// SCALE
// =====================================================

void Renderer3D::scale(
    Vec3& v,
    float amount
)
{
    v.x *= amount;
    v.y *= amount;
    v.z *= amount;
}

// =====================================================
// ROTATE X
// =====================================================

void Renderer3D::rotateX(
    Vec3& v,
    float angle
)
{
    float s = sin(angle);
    float c = cos(angle);

    float y = v.y;
    float z = v.z;

    v.y = y * c - z * s;
    v.z = y * s + z * c;
}

// =====================================================
// ROTATE Y
// =====================================================

void Renderer3D::rotateY(
    Vec3& v,
    float angle
)
{
    float s = sin(angle);
    float c = cos(angle);

    float x = v.x;
    float z = v.z;

    v.x = x * c + z * s;
    v.z = -x * s + z * c;
}

// =====================================================
// ROTATE Z
// =====================================================

void Renderer3D::rotateZ(
    Vec3& v,
    float angle
)
{
    float s = sin(angle);
    float c = cos(angle);

    float x = v.x;
    float y = v.y;

    v.x = x * c - y * s;
    v.y = x * s + y * c;
}

// =====================================================
// DISTANCE TO CAMERA
// =====================================================

float Renderer3D::distanceToCamera(
    const Vec3& v
)
{
    float dx =
        v.x -
        camera.position.x;

    float dy =
        v.y -
        camera.position.y;

    float dz =
        v.z -
        camera.position.z;

    return sqrtf(
        dx * dx +
        dy * dy +
        dz * dz
    );
}

// =====================================================
// AXIS
// =====================================================

void Renderer3D::drawAxis(
    float length
)
{
    drawLine3D(
        {0,0,0},
        {length,0,0},
        0xF800
    );

    drawLine3D(
        {0,0,0},
        {0,length,0},
        0x07E0
    );

    drawLine3D(
        {0,0,0},
        {0,0,length},
        0x001F
    );
}

// =====================================================
// GRID
// =====================================================

void Renderer3D::drawGrid(
    float size,
    float spacing,
    uint16_t color
)
{
    for(
        float i = -size;
        i <= size;
        i += spacing
    )
    {
        drawLine3D(
            {-size,0,i},
            { size,0,i},
            color
        );

        drawLine3D(
            {i,0,-size},
            {i,0,size},
            color
        );
    }
}

// =====================================================
// MESH
// =====================================================

// =====================================================
// MESH WIREFRAME
// =====================================================

void Renderer3D::drawMesh(
    const Mesh3D& mesh,
    uint16_t color
)
{
    for(
        uint16_t i = 0;
        i < mesh.faceCount;
        i++
    )
    {
        const Face3D& f =
            mesh.faces[i];

        Vec3 a =
        {
            mesh.vertices[f.v1].x,
            mesh.vertices[f.v1].y,
            mesh.vertices[f.v1].z
        };

        Vec3 b =
        {
            mesh.vertices[f.v2].x,
            mesh.vertices[f.v2].y,
            mesh.vertices[f.v2].z
        };

        Vec3 c =
        {
            mesh.vertices[f.v3].x,
            mesh.vertices[f.v3].y,
            mesh.vertices[f.v3].z
        };

        drawLine3D(a,b,color);
        drawLine3D(b,c,color);
        drawLine3D(c,a,color);
    }
}

// =====================================================
// CUBE
// =====================================================

void Renderer3D::drawCube(
    float x,
    float y,
    float z,
    float size,
    uint16_t color
)
{
    float s =
        size * 0.5f;

    Vec3 v[8] =
    {
        {x-s,y-s,z-s},
        {x+s,y-s,z-s},
        {x+s,y+s,z-s},
        {x-s,y+s,z-s},

        {x-s,y-s,z+s},
        {x+s,y-s,z+s},
        {x+s,y+s,z+s},
        {x-s,y+s,z+s}
    };

    const uint8_t edges[12][2] =
    {
        {0,1},
        {1,2},
        {2,3},
        {3,0},

        {4,5},
        {5,6},
        {6,7},
        {7,4},

        {0,4},
        {1,5},
        {2,6},
        {3,7}
    };

    for(
        uint8_t i = 0;
        i < 12;
        i++
    )
    {
        drawLine3D(
            v[edges[i][0]],
            v[edges[i][1]],
            color
        );
    }
}

// =====================================================
// FILLED MESH
// =====================================================

void Renderer3D::drawMeshFilled(
    const Mesh3D& mesh
)
{
    for(
        uint16_t i = 0;
        i < mesh.faceCount;
        i++
    )
    {
        const Face3D& f =
            mesh.faces[i];

        Vec3 a =
        {
            mesh.vertices[f.v1].x,
            mesh.vertices[f.v1].y,
            mesh.vertices[f.v1].z
        };

        Vec3 b =
        {
            mesh.vertices[f.v2].x,
            mesh.vertices[f.v2].y,
            mesh.vertices[f.v2].z
        };

        Vec3 c =
        {
            mesh.vertices[f.v3].x,
            mesh.vertices[f.v3].y,
            mesh.vertices[f.v3].z
        };

        if(
            backfaceCull(
                a,b,c
            )
        )
        {
            continue;
        }

        fillTriangle3D(
            a,
            b,
            c,
            f.color
        );
    }
}

// =====================================================
// TEXTURED TRIANGLE
// =====================================================

void Renderer3D::drawTexturedTriangle(
    Vertex3D v1,
    Vertex3D v2,
    Vertex3D v3,
    const uint16_t* texture,
    int16_t texW,
    int16_t texH
)
{
    int16_t x1,y1;
    int16_t x2,y2;
    int16_t x3,y3;

    project(
        {v1.x,v1.y,v1.z},
        x1,y1
    );

    project(
        {v2.x,v2.y,v2.z},
        x2,y2
    );

    project(
        {v3.x,v3.y,v3.z},
        x3,y3
    );

    graphics.drawTextureTriangle(
        x1,y1,
        x2,y2,
        x3,y3,
        texture,
        texW,
        texH
    );
}

// =====================================================
// TEXTURED MESH
// =====================================================

void Renderer3D::drawMeshTextured(
    const Mesh3D& mesh,
    const uint16_t* texture,
    int16_t texW,
    int16_t texH
)
{
    for(
        uint16_t i = 0;
        i < mesh.faceCount;
        i++
    )
    {
        const Face3D& f =
            mesh.faces[i];

        drawTexturedTriangle(
            mesh.vertices[f.v1],
            mesh.vertices[f.v2],
            mesh.vertices[f.v3],
            texture,
            texW,
            texH
        );
    }
}

// =====================================================
// FILLED CUBE
// =====================================================

void Renderer3D::drawCubeFilled(
    float x,
    float y,
    float z,
    float size,
    uint16_t color
)
{
    float s =
        size * 0.5f;

    Vec3 v[8] =
    {
        {x-s,y-s,z-s},
        {x+s,y-s,z-s},
        {x+s,y+s,z-s},
        {x-s,y+s,z-s},

        {x-s,y-s,z+s},
        {x+s,y-s,z+s},
        {x+s,y+s,z+s},
        {x-s,y+s,z+s}
    };

    const uint8_t tris[12][3] =
    {
        {0,1,2},{0,2,3},
        {4,6,5},{4,7,6},
        {0,4,5},{0,5,1},
        {1,5,6},{1,6,2},
        {2,6,7},{2,7,3},
        {3,7,4},{3,4,0}
    };

    for(
        uint8_t i=0;
        i<12;
        i++
    )
    {
        fillTriangle3D(
            v[tris[i][0]],
            v[tris[i][1]],
            v[tris[i][2]],
            color
        );
    }
}

void Renderer3D::drawSphere(
    float x,
    float y,
    float z,
    float radius,
    uint8_t slices,
    uint8_t stacks,
    uint16_t color
)
{
    // Respect the tessellation requested by the caller.
    // Clamp to safe minimums so division and topology remain valid.
    const int rings = max(2, (int)stacks);
    const int sectors = max(3, (int)slices);

    for(int r = 0; r < rings; r++)
    {
        float lat0 =
            PI *
            (-0.5f +
            (float)r / rings);

        float lat1 =
            PI *
            (-0.5f +
            (float)(r + 1) / rings);

        for(int s = 0; s < sectors; s++)
        {
            float lon0 =
                2.0f *
                PI *
                (float)s /
                sectors;

            float lon1 =
                2.0f *
                PI *
                (float)(s + 1) /
                sectors;

            Vec3 p1 =
            {
                x + cos(lat0) * cos(lon0) * radius,
                y + sin(lat0) * radius,
                z + cos(lat0) * sin(lon0) * radius
            };

            Vec3 p2 =
            {
                x + cos(lat0) * cos(lon1) * radius,
                y + sin(lat0) * radius,
                z + cos(lat0) * sin(lon1) * radius
            };

            Vec3 p3 =
            {
                x + cos(lat1) * cos(lon0) * radius,
                y + sin(lat1) * radius,
                z + cos(lat1) * sin(lon0) * radius
            };

            drawLine3D(
                p1,
                p2,
                color
            );

            drawLine3D(
                p1,
                p3,
                color
            );
        }
    }
}

void Renderer3D::drawPokeball(
    float x,
    float y,
    float z,
    float radius
)
{
    drawSphere(
        x,
        y,
        z,
        radius,
        16,
        16,
        Color::WHITE
    );

    drawLine3D(
        {x - radius, y, z},
        {x + radius, y, z},
        Color::BLACK
    );

    drawSphere(
        x,
        y,
        z,
        radius * 0.25f,
        8,
        8,
        Color::BLACK
    );
}