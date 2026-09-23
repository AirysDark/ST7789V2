#pragma once

#include <Arduino.h>

// =====================================================
// VECTOR 2D
// =====================================================

struct Vec2
{
    float x;
    float y;
};

// =====================================================
// VECTOR 3D
// =====================================================

struct Vec3
{
    float x;
    float y;
    float z;
};

// =====================================================
// TEXTURED VERTEX
// =====================================================

struct Vertex3D
{
    float x;
    float y;
    float z;

    float u;
    float v;
};

// =====================================================
// TRIANGLE
// =====================================================

struct Triangle3D
{
    Vec3 v1;
    Vec3 v2;
    Vec3 v3;

    uint16_t color;
};

// =====================================================
// FACE
// =====================================================

struct Face3D
{
    uint16_t v1;
    uint16_t v2;
    uint16_t v3;

    uint16_t color;
};

// =====================================================
// MESH
// =====================================================

struct Mesh3D
{
    Vertex3D* vertices = nullptr;

    uint16_t vertexCount = 0;

    Face3D* faces = nullptr;

    uint16_t faceCount = 0;
};

// =====================================================
// CAMERA
// =====================================================

struct Camera3D
{
    Vec3 position;

    float pitch;
    float yaw;
    float roll;

    float fov;
};

// =====================================================
// RENDERER
// =====================================================

class Renderer3D
{
public:

    Camera3D camera;

    Renderer3D();

    // =====================================================
    // CAMERA
    // =====================================================

    void setCamera(
        float x,
        float y,
        float z
    );

    float distanceToCamera(
        const Vec3& v
    );

    // =====================================================
    // PROJECTION
    // =====================================================

    void project(
        const Vec3& in,
        int16_t& x,
        int16_t& y
    );

    // =====================================================
    // BASIC 3D
    // =====================================================

    void drawLine3D(
        Vec3 a,
        Vec3 b,
        uint16_t color
    );

    void drawTriangle3D(
        Triangle3D tri
    );

    void fillTriangle3D(
        Vec3 a,
        Vec3 b,
        Vec3 c,
        uint16_t color
    );

    // =====================================================
    // TEXTURED
    // =====================================================

    void drawTexturedTriangle(
        Vertex3D v1,
        Vertex3D v2,
        Vertex3D v3,

        const uint16_t* texture,
        int16_t texW,
        int16_t texH
    );

    // =====================================================
    // MESH
    // =====================================================

    void drawMesh(
        const Mesh3D& mesh,
        uint16_t color
    );

    void drawMeshFilled(
        const Mesh3D& mesh
    );

    void drawMeshTextured(
        const Mesh3D& mesh,
        const uint16_t* texture,
        int16_t texW,
        int16_t texH
    );

    // =====================================================
    // PRIMITIVES
    // =====================================================

    void drawCube(
        float x,
        float y,
        float z,
        float size,
        uint16_t color
    );

    void drawCubeFilled(
        float x,
        float y,
        float z,
        float size,
        uint16_t color
    );

    void drawSphere(
        float x,
        float y,
        float z,
        float radius,
        uint8_t slices,
        uint8_t stacks,
        uint16_t color
    );

    void drawPokeball(
        float x,
        float y,
        float z,
        float radius
    );

    // =====================================================
    // WORLD HELPERS
    // =====================================================

    void drawGrid(
        float size,
        float spacing,
        uint16_t color
    );

    void drawAxis(
        float length
    );

    // =====================================================
    // MODEL LOADING
    // =====================================================

    bool loadOBJ(
        const char* filename,
        Mesh3D& mesh
    );

    void freeMesh(
        Mesh3D& mesh
    );

    // =====================================================
    // TRANSFORMS
    // =====================================================

    void translate(
        Vec3& v,
        float x,
        float y,
        float z
    );

    void scale(
        Vec3& v,
        float amount
    );

    void rotateX(
        Vec3& v,
        float angle
    );

    void rotateY(
        Vec3& v,
        float angle
    );

    void rotateZ(
        Vec3& v,
        float angle
    );

    // =====================================================
    // INTERNAL
    // =====================================================

    bool backfaceCull(
        Vec3 a,
        Vec3 b,
        Vec3 c
    );

    float triangleDepth(
        Vec3 a,
        Vec3 b,
        Vec3 c
    );
};

void drawSphere(
    float x,
    float y,
    float z,
    float radius,
    uint16_t color
);

extern Renderer3D renderer3D;