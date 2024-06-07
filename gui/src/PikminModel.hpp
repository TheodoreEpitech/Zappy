/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Pikmin Model
*/

#pragma once

#include <raylib-cpp.hpp>
#include "ModelBank.hpp"

namespace GUI {
    class PikminModel
    {
        public:
            PikminModel(std::size_t x, std::size_t y);
            ~PikminModel() = default;

            inline void setModel(std::shared_ptr<GuiModel> model) { _model = model; }
            void drawModel(float delta);
            inline void setAnimation(AnimType anim) { _model->SetAnimation(anim); }
            inline void setAnimationFps(float fps) { _animationTime = 1.0F / fps; }

            bool animationUpdate(float delta);

            inline void setMotionVector(raylib::Vector3 newVect) { _motionVector = newVect; }
            void setPositionVector(raylib::Vector3 newPos);

            inline void setRotation(float rotation) { _rotation = rotation; }

            inline void setColor(raylib::Color &color) { _colorMod = color; }

            bool getColision(raylib::Ray &) const;

            inline std::size_t getX(void) { return _position.x; }
            inline std::size_t getY(void) { return _position.z; }

        private:
            std::shared_ptr<GuiModel> _model;
            int _animCount;
            int _frameCount;

            raylib::Vector3 _position;
            raylib::Vector3 _motionVector;
            raylib::Vector3 _rotationAxis;
            float _rotation;
            float _scale;
            raylib::Color _colorMod;

            float _cumulatedTime;
            float _animationTime;
            float _walkTime;

            raylib::BoundingBox _entityBox;
            raylib::Vector3 _size;
            raylib::Vector3 _boxOffset;
    };
}
