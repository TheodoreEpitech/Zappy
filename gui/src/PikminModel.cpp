/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pikmin Model
*/

#include "PikminModel.hpp"

PikminModel::PikminModel(std::size_t x, std::size_t y)
{
    _model = nullptr;
    _animCount = 0;
    _frameCount = 0;
    _position = raylib::Vector3(x, 1, y);
    _motionVector = raylib::Vector3(0, 0, 0);
    _rotationAxis = raylib::Vector3(0, 0.5, 0);
    _rotation = 0;
    _scale = raylib::Vector3(0.05, 0.05, 0.05);
    _colorMod = raylib::Color::White();
    _cumulatedTime = 0.0f;
    _animationTime = 0.0f;
    _walkTime = 0.0f;
}

bool PikminModel::animationUpdate(float delta)
{
    if (_model == nullptr) {
        return true;
    }
    _cumulatedTime += delta;
    if (_cumulatedTime >= _animationTime) {
        _cumulatedTime = 0.0f;
        _frameCount++;
        _model->UpdateAnim(_frameCount);
    }
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
    if (_model) {
        _model->Draw(_position, _rotationAxis, _rotation, _scale, _colorMod);
    } else {
        DrawCubeV(_position, _scale, _colorMod);
    }
}
