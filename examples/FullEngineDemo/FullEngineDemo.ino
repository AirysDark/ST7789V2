#include <ESP32S3WatchEngine.h>


// =====================================================
// GLOBALS
// =====================================================

float angle3D = 0.0f;

uint16_t checkerTexture[16 * 16];

Vertex3D meshVerts[4] =
{
    {-15,-15,0},
    { 15,-15,0},
    { 15, 15,0},
    {-15, 15,0}
};

Vertex3D meshOriginalVerts[4] =
{
    {-20,-20,120},
    { 20,-20,120},
    { 20, 20,120},
    {-20, 20,120}
};

uint16_t meshIndices[] =
{
0,1,2,
0,2,3
};

Face3D meshFaces[2] =
{
{0,1,2,Color::GREEN},
{0,2,3,Color::CYAN}
};

Mesh3D testMesh;

uint32_t lastTime = 0;
uint32_t frames = 0;

// =====================================================
// GENERATE TEST TEXTURE
// =====================================================

void generateTexture()
{
for(int y = 0; y < 16; y++)
{
for(int x = 0; x < 16; x++)
{
bool c =
((x / 4) + (y / 4))
& 1;

checkerTexture[
y * 16 + x
] =
c
? Color::WHITE
: Color::RED;
}
}
}

// =====================================================
// BOOT COLOR TEST
// =====================================================

void bootColorTest()
{
uint16_t colors[] =
{
Color::BLACK,
Color::RED,
Color::GREEN,
Color::BLUE,
Color::WHITE,
Color::CYAN,
Color::MAGENTA,
Color::YELLOW
};

for(uint8_t i = 0; i < 8; i++)
{
graphics.clear(
colors[i]
);

framebuffer.pushRect(
    0,
    0,
    280,
    240
);   

delay(250);
}

graphics.clear(
Color::BLACK
);

framebuffer.pushRect(
    0,
    0,
    280,
    240
);

delay(250);
}

// =====================================================
// 2D TEST
// =====================================================

void graphicsRendererTest()
{
graphics.clear(
Color::BLACK
);

graphics.drawPanel(
10,
10,
260,
220,
Color::BLUE,
Color::WHITE,
Color::BLACK
);

graphics.drawButton(
20,
50,
100,
40,
Color::GREEN,
Color::WHITE
);

graphics.drawProgressBar(
20,
110,
200,
20,
75,
100,
Color::RED,
Color::WHITE
);

graphics.drawCheckBox(
20,
150,
true,
Color::WHITE,
Color::GREEN
);

graphics.drawSlider(
50,
152,
150,
60,
100,
Color::CYAN,
Color::WHITE
);

renderer.drawTextCentered(
140,
25,
"2D ENGINE TEST",
Color::YELLOW,
2
);

framebuffer.pushRect(
    0,
    0,
    280,
    240
);
}

// =====================================================
// TEXTURE TEST
// =====================================================

void texturePolygonTest()
{
graphics.clear(
Color::BLACK
);

graphics.drawTextureRect(
40,
40,
200,
150,
checkerTexture,
16,
16
);

graphics.drawRect(
40,
40,
200,
150,
Color::WHITE
);

renderer.drawTextCentered(
140,
15,
"TEXTURE TEST",
Color::YELLOW,
2
);

framebuffer.pushRect(
    0,
    0,
    280,
    240
);
}

// =====================================================
// 3D TEST
// =====================================================

void render3DScene()
{
graphics.clear(
Color::BLACK
);

framebuffer.clearZBuffer();  

renderer3D.setCamera(  
    0,  
    0,  
    -120  
);  

for(  
    uint16_t i = 0;  
    i < testMesh.vertexCount;  
    i++  
)  
{  
    Vec3 v =  
    {  
        meshOriginalVerts[i].x,  
        meshOriginalVerts[i].y,  
        meshOriginalVerts[i].z  
    };  

    renderer3D.rotateY(  
        v,  
        angle3D  
    );  

    renderer3D.rotateX(  
        v,  
        angle3D * 0.5f  
    );  

    testMesh.vertices[i].x = v.x;  
    testMesh.vertices[i].y = v.y;  
    testMesh.vertices[i].z = v.z;  
}  

renderer3D.drawMesh(  
    testMesh,  
    Color::YELLOW  
);  

renderer3D.drawGrid(  
    50,  
    20,  
    Color::rgb565(  
        40,  
        40,  
        40  
    )  
);  

renderer3D.drawAxis(  
    50  
);  

Vec3 cubePos =  
{  
    -50,  
    0,  
    120  
};  

renderer3D.rotateY(  
    cubePos,  
    angle3D  
);  

renderer3D.drawCubeFilled(  
    cubePos.x,  
    cubePos.y,  
    cubePos.z,  
    35,  
    Color::CYAN  
);  

renderer3D.drawCube(  
    cubePos.x,  
    cubePos.y,  
    cubePos.z,  
    35,  
    Color::WHITE  
);  

Vec3 spherePos =  
{  
    50,  
    0,  
    120  
};  

renderer3D.rotateY(  
    spherePos,  
    -angle3D  
);  

renderer3D.drawSphere(  
    spherePos.x,  
    spherePos.y,  
    spherePos.z,  
    22,  
    8,  
    8,  
    Color::GREEN  
);  

Vec3 ballPos =  
{  
    0,  
    0,  
    180  
};  

renderer3D.rotateY(  
    ballPos,  
    angle3D * 0.5f  
);  

renderer3D.drawPokeball(  
    ballPos.x,  
    ballPos.y,  
    ballPos.z,  
    28  
);  

// graphics.drawTextureTriangle(  
//    70,  
//    190,  
//    140,  
//    110,  
//    210,  
//    190,  
//    checkerTexture,  
//    16,  
//    16  
// );  

graphics.fillTriangle(  
    20,  
    210,  
    60,  
    170,  
    100,  
    210,  
    Color::MAGENTA  
);  

int16_t polyX[5] =  
{  
    180,  
    210,  
    240,  
    220,  
    170  
};  

int16_t polyY[5] =  
{  
    170,  
    140,  
    170,  
    210,  
    210  
};  

graphics.fillPolygon(  
    polyX,  
    polyY,  
    5,  
    Color::CYAN  
);  

// graphics.drawTexturedPolygon(  
//    polyX,  
//    polyY,  
//    5,  
//    checkerTexture,  
//    16,  
//    16  
//);  

uint16_t blendColor =  
    graphics.alphaBlend(  
        Color::RED,  
        Color::BLUE,  
        128  
    );  

graphics.fillRect(  
    120,  
    180,  
    24,  
    24,  
    blendColor  
);  

graphics.drawLED(  
    20,  
    20,  
    6,  
    true,  
    Color::GREEN,  
    Color::RED  
);  

graphics.drawMeter(  
    255,  
    20,  
    10,  
    millis() % 100,  
    100,  
    Color::YELLOW  
);  

graphics.drawCrosshair(  
    140,  
    120,  
    10,  
    Color::RED  
);  

graphics.drawPanel(  
    5,  
    5,  
    270,  
    30,  
    Color::BLUE,  
    Color::WHITE,  
    Color::BLACK  
);  

renderer.drawTextCentered(  
    140,  
    12,  
    "WATCH 3D ENGINE",  
    Color::YELLOW,  
    1  
);  

framebuffer.swapBuffers();
framebuffer.pushRect(
    0,
    0,
    280,
    240
);
}

// =====================================================
// SETUP
// =====================================================

void setup()
{
Serial.begin(115200);

display.begin();  

if(!framebuffer.begin() || !framebuffer.enableDoubleBuffer() || !framebuffer.enableZBuffer())
{  
    Serial.println("FRAMEBUFFER INIT FAILED");  
    while(true) { delay(1000); }  
}  

touch.begin();  

randomSeed(micros());  

testMesh.vertices = meshVerts;  
testMesh.vertexCount = 4;  
testMesh.faces = meshFaces;  
testMesh.faceCount = 2;  

generateTexture();  
bootColorTest();  
delay(500);  
graphicsRendererTest();  
delay(3000);  
texturePolygonTest();  
delay(3000);  
framebuffer.clearZBuffer();  

Serial.println("READY");
}

// =====================================================
// LOOP
// =====================================================

void loop()
{
angle3D += 0.03f;

if(angle3D > (PI * 2.0f))
{  
    angle3D = 0.0f;  
}  

frames++;

if(millis() - lastTime >= 1000)
{
    Serial.printf(
        "FPS: %lu\n",
        frames
    );

    frames = 0;
    lastTime = millis();
}

render3DScene();  

delay(16);
}
