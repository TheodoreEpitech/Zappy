/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Model Bank
*/

#pragma once

#include <memory>
#include <raylib-cpp.hpp>
#include <map>
#include <vector>

namespace GUI {
    enum ModelType {
        DEFAULT,
        RED_PIKMIN,
        YELLOW_PIKMIN,
        BLUE_PIKMIN,
        PURPLE_PIKMIN,
        WHITE_PIKMIN,
        ROCK_PIKMIN,
        WING_PIKMIN,
        ICE_PIKMIN,
        SPECTRAL_PIKMIN,
        LEAF_TOP,
        BUD_TOP,
        FLOWER_TOP,
        FOOD_MOD,
        LINEMATE_MOD,
        DERAUMERE_MOD,
        SIBUR_MOD,
        MENDIANE_MOD,
        PHIRAS_MOD,
        THYSTAME_MOD,
        MAP,
        WALLS,
        RUG,
        BIGSOFA,
        SOFA
    };

    enum AnimType {
        IDLE,
        WALK,
        INCANTATION,
        BROADCAST,
        DEATH,
        PUSH,
        FALL,
        PLANT,
        PICK,
        DROP,
        LOOK,
        NONE
    };

    class GuiModel {
        public:

            GuiModel();
            GuiModel(std::string modelPath, std::string texturePath, std::string animPath, ModelType type);
            ~GuiModel();

            void DefaultSetup();
            void Draw(raylib::Vector3 pos, raylib::Vector3 axis, float rotation, float scale, raylib::Color color);
            void UpdateAnim(int &frameCount);
            AnimType GetAnimation();
            void SetAnimation(AnimType anim);
            int getNbFrame(void) const;
        protected:
        private:
            AnimType _animType;
            ModelType _type;
            raylib::Model _model;
            float _defaultRotation;
            std::shared_ptr<std::vector<raylib::ModelAnimation>> _animations;
    };

    class ModelBank
    {
        public:

            typedef struct ModelInfo {
                std::string modelPath;
                std::string texturePath;
                std::string animPath;
            } ModelInfo_t;

            static const std::map<ModelType, ModelInfo> modelInfo;
            static std::map<std::string, std::shared_ptr<std::vector<raylib::ModelAnimation>>> loadedAnims;
            static std::map<ModelType, std::shared_ptr<GuiModel>> models;

            static std::shared_ptr<GuiModel> get(ModelType type);
            static void reset(void)
            {
                loadedAnims.clear();
                models.clear();
            }
    };
}