#pragma once
#include <Qt3DCore>
#include <Qt3DExtras>

class Camera : public Qt3DExtras::QAbstractCameraController
{
public:
    Camera(Qt3DCore::QNode *parent = static_cast<Qt3DCore::QNode*>(nullptr));
    ~Camera() override;

    void moveCamera(const InputState &state, float dt) override;
};

