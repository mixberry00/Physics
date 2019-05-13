#include "Camera.h"



Camera::Camera(Qt3DCore::QNode *parent) :
    QAbstractCameraController(parent)
{
}


Camera::~Camera()
{
}

void Camera::moveCamera(const InputState & state, float dt)
{
    if (camera() == nullptr) {
        return;
    }
    camera()->translate(QVector3D(0, 0, state.tzAxisValue * linearSpeed() * dt), camera()->DontTranslateViewCenter);
    camera()->panAboutViewCenter((state.rxAxisValue * lookSpeed()) * dt, QVector3D(0, 1, 0));
    camera()->tiltAboutViewCenter((state.ryAxisValue * lookSpeed()) * dt);
}
