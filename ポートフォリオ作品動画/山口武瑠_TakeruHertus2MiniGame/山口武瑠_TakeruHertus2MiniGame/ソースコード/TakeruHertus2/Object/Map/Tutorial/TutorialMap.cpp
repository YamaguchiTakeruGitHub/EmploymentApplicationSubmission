#include "TutorialMap.h"

TutorialMap::TutorialMap()
{
    AddComponent<ComponentTransform>();
    m_transform = GetComponent<ComponentTransform>();

    AddComponent<ComponentModel>();
    m_model = GetComponent<ComponentModel>();

}

TutorialMap::~TutorialMap()
{
}

void TutorialMap::Init()
{
    Entity::InitComponent();
    m_transform->position = VGet(0, 0, 0);
    m_model->LoadModel("../Data/Asset/3D/Map/PolygonHitTestMap.mv1");

}

void TutorialMap::Update()
{
    Entity::UpdateComponent();
}

void TutorialMap::Draw()
{
    Entity::DrawComponent();
}

void TutorialMap::Final()
{
    Entity::FinalComponent();
}

void TutorialMap::DrawGrid(float areaSize, int numLines, float lineHeight)
{
    VECTOR pos1, pos2;

    SetUseZBufferFlag(TRUE);

    pos1 = VGet(-areaSize / 2.0f, lineHeight, -areaSize / 2.0f);
    pos2 = VGet(-areaSize / 2.0f, lineHeight, areaSize / 2.0f);
    for (int i = 0; i <= numLines; i++) {
        DrawLine3D(pos1, pos2, GetColor(255, 255, 255));
        pos1.x += areaSize / numLines;
        pos2.x += areaSize / numLines;
    }

    pos1 = VGet(-areaSize / 2.0f, lineHeight, -areaSize / 2.0f);
    pos2 = VGet(areaSize / 2.0f, lineHeight, -areaSize / 2.0f);
    for (int i = 0; i < numLines; i++) {
        DrawLine3D(pos1, pos2, GetColor(255, 255, 255));
        pos1.z += areaSize / numLines;
        pos2.z += areaSize / numLines;
    }

    SetUseZBufferFlag(FALSE);
}

void TutorialMap::DrawBox(VECTOR _boxPos, VECTOR _boxSize)
{
    VECTOR corners[8];
    corners[0] = VGet(_boxPos.x - _boxSize.x / 2, _boxPos.y - _boxSize.y / 2, _boxPos.z - _boxSize.z / 2);
    corners[1] = VGet(_boxPos.x + _boxSize.x / 2, _boxPos.y - _boxSize.y / 2, _boxPos.z - _boxSize.z / 2);
    corners[2] = VGet(_boxPos.x + _boxSize.x / 2, _boxPos.y + _boxSize.y / 2, _boxPos.z - _boxSize.z / 2);
    corners[3] = VGet(_boxPos.x - _boxSize.x / 2, _boxPos.y + _boxSize.y / 2, _boxPos.z - _boxSize.z / 2);
    corners[4] = VGet(_boxPos.x - _boxSize.x / 2, _boxPos.y - _boxSize.y / 2, _boxPos.z + _boxSize.z / 2);
    corners[5] = VGet(_boxPos.x + _boxSize.x / 2, _boxPos.y - _boxSize.y / 2, _boxPos.z + _boxSize.z / 2);
    corners[6] = VGet(_boxPos.x + _boxSize.x / 2, _boxPos.y + _boxSize.y / 2, _boxPos.z + _boxSize.z / 2);
    corners[7] = VGet(_boxPos.x - _boxSize.x / 2, _boxPos.y + _boxSize.y / 2, _boxPos.z + _boxSize.z / 2);

    for (int i = 0; i < 4; i++)
    {
        DrawLine3D(corners[i], corners[(i + 1) % 4], 0xff0000);
        DrawLine3D(corners[i + 4], corners[(i + 1) % 4 + 4], 0xff0000);
        DrawLine3D(corners[i], corners[i + 4], 0xff0000);
    }
}
