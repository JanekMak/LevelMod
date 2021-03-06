#ifndef COLLISION_H
#define COLLISION_H
namespace Collision
{

    //Collision chache: 0085A4C4
    enum
    {
        IGNORE0 = true,
    };
    enum class Flags : unsigned char
    {
        Ignore = 0,
        Wallride = 0x4,
        Vert = 0x8,
        Hollow = 0x10,
        Trigger = 0x40,
        Skatable = 0x80,
    };

    bool TriangleIntersectingSphere(D3DXVECTOR3 A, D3DXVECTOR3 B, D3DXVECTOR3 C, D3DXVECTOR3 P, float R);
    bool TriangleInsideSphere(D3DXVECTOR3 A, D3DXVECTOR3 B, D3DXVECTOR3 C, D3DXVECTOR3 P, float R);
};
#endif