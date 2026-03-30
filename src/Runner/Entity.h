#pragma once
#include "../lib/Geometries/Geometry.h"
#include "../lib/Geometries/Geometries.h"

enum Face
{
    Front,
    Back,
    Top,
    Down,
    Right,
    Left,
    NONE
};

class Entity
{
protected:
    const char* m_Name;
    sr::Geometry* m_pGeo;
    bool m_HasCollider = false;
    int m_CollidingFace = (int)Face::NONE;

    int m_Tag = -1;

    bool m_IsVisible = true;
public:
    bool m_ToDestroy = false;

    bool m_LateDestroy = false;

    Entity(const char* name, sr::Geometry* geo) { m_Name = name, m_pGeo = geo; }
    ~Entity();

    //Get
    int GetTag() { return m_Tag; }
    const char* GetName() { return m_Name; }
    sr::Geometry* GetGeo() { return m_pGeo; }
    gce::Vector3f32 GetPosition() { return m_pGeo->GetPosition(); }
    gce::Vector3f32 GetRotation() { return m_pGeo->GetRotation(); }
    gce::Vector3f32 GetScale() { return m_pGeo->GetScale(); }
    bool HasCollider() { return m_HasCollider; }
    const int& GetFace() { return m_CollidingFace; }
    const char* GetFaceInString(int face);
    bool IsVisible() { return m_IsVisible; }

    //Main
    virtual void Start() {};
    virtual void Update() {};

    //Set
    void SetTag(int tag) { m_Tag = tag; }
    void SetPosition(gce::Vector3f32 const& pos) { m_pGeo->SetPosition(pos); }
    void SetRotation(gce::Vector3f32 const& rot) { m_pGeo->SetRotation(rot); }
    void SetScale(gce::Vector3f32 const& scale) { m_pGeo->SetScale(scale); }
    void SetCollider(bool state) { m_HasCollider = state; }
    void SetFace(int face) { m_CollidingFace = face; }
    void SetVisibility(bool state) { m_IsVisible = state; }

    //Transform 
    void Translate(gce::Vector3f32 const& translation) { m_pGeo->Translate(translation); }
    void Rotate(gce::Vector3f32 const& rotation) { m_pGeo->Rotate(rotation); }
    void Scale(gce::Vector3f32 const& scale) { m_pGeo->Scale(scale); }

    void SetTexture(sr::Texture const& texture) { m_pGeo->SetTexture(texture); }
    void SetColor(gce::Vector3f32 const& color) { m_pGeo->SetColor(color); }

    //Collision
    bool IsColliding(Entity* pOther);

    virtual void OnCollision(Entity* pOther);
};
