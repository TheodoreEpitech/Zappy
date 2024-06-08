/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pikmin Model
*/

#include "PikminModel.hpp"


namespace GUI {
    PikminModel::PikminModel(int x, int y)
    {
        _model = nullptr;
        _bulb = nullptr;
        _animType = AnimType::IDLE;
        _animCount = 0;
        _frameCount = 0;
        _position = raylib::Vector3(x, 0.5f, y);
        _motionVector = raylib::Vector3(0.0f, 0.0f, 0.0f);
        _rotationAxis = raylib::Vector3(0.0f, 0.0f, 1.0f);
        _rotation = 0;
        _scale = 0.05;
        _size = (raylib::Vector3(1, 1, 1) * _scale);
        _boxOffset = raylib::Vector3(-0.5, -0.5, -0.5) * _scale;
        _entityBox = raylib::BoundingBox(_position + _boxOffset, _position + _size + _boxOffset);
        _pikminColor = raylib::Color::White();
        _bulbColor = raylib::Color::White();
        _cumulatedTime = 0.0f;
        _animationTime = 0.0f;
        _walkTime = 0.0f;
    }

    void PikminModel::setBulbModel(std::shared_ptr<GuiModel> model)
    {
        _bulb = model;
        _bulb->SetAnimation(_animType);
    }

    void PikminModel::setAnimation(AnimType anim)
    {
        _frameCount = 0;
        _animType = anim;
        if (_model)
            _model->SetAnimation(anim);
        if (_bulb)
            _bulb->SetAnimation(anim);
    }

    void PikminModel::setPositionVector(raylib::Vector3 newPos)
    {
        _position = newPos;
        _entityBox.SetMin(_position + _boxOffset);
        _entityBox.SetMax(_position + _size + _boxOffset);
    }

    bool PikminModel::animationUpdate(float delta)
    {
        if (_model == nullptr || _bulb == nullptr) {
            return true;
        }
        _cumulatedTime += delta;
        // if (_cumulatedTime >= _animationTime) {
        //     _cumulatedTime = 0.0f;
            _frameCount++;
            _model->UpdateAnim(_frameCount);
            _bulb->UpdateAnim(_frameCount);
        // }
        return (_frameCount == 0);
    }

    void PikminModel::drawModel(float delta)
    {
        //if (_motionVector != raylib::Vector3::Zero()) {
        //    _walkTime += delta;
        //    _position += _motionVector * (delta / 7);
        //    if (_walkTime > 7.0f) {
        //        _walkTime = 0.0f;
        //        _motionVector = raylib::Vector3::Zero();
        //    }
        //}
        _entityBox.Draw();
        if (_model && _bulb) {
            _model->Draw(_position, _rotationAxis, _rotation, _scale, _pikminColor);
            _bulb->Draw(_position, _rotationAxis, _rotation, _scale, _bulbColor);
        } else {
            DrawCubeV(_position, raylib::Vector3(_scale, _scale, _scale), _pikminColor);
        }
    }

    bool PikminModel::getColision(raylib::Ray &mousePos) const
    {
        raylib::RayCollision colision = GetRayCollisionBox(mousePos, _entityBox);
        return colision.hit;
    }
}
