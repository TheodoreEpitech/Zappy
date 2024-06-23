/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include "Communication/Client.hpp"
#include "InputParser.hpp"
#include "ModelBank.hpp"
#include "Pikmin.hpp"
#include "PikminModel.hpp"
#include "Warudo.hpp"
#include "raylib-cpp.hpp"
#include "raylib.h"

int main_grahic()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera mode");

    // Define the camera to look into our 3d world
    Camera3D camera = {0};
    camera.position = (Vector3) {0.0f, 25.0f, 30.0f}; // Camera position
    camera.target = (Vector3) {0.0f, 6.0f, 0.0f}; // Camera looking at point
    camera.up = (Vector3) {0.0f, 1.0f, 0.0f}; // Camera up vector (rotation towards target)
    camera.fovy = 45.0f; // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE; // Camera mode type

    // Pikmin pikmin("yes", 0, 0);
    // pikmin.setModel(ModelBank::get("RedPikmin"));
    // pikmin.setTop(ModelBank::get("LeafTop"));

    // Model pikmin = LoadModel("gui/res/models/RedPikmin.iqm");                 // Load OBJ model
    // Texture2D texture = LoadTexture("gui/res/textures/RedPikmin.png");      // Load model texture
    // SetMaterialTexture(&pikmin.materials[0], MATERIAL_MAP_DIFFUSE, texture);   // Set model diffuse texture
    // pikmin.transform = MatrixRotateXYZ((Vector3){ 5.0f, 0.0f, 0.0f });

    // Model y_pikmin = LoadModel("gui/res/models/YellowPikmin.iqm");                 // Load OBJ model
    // Texture2D y_texture = LoadTexture("gui/res/textures/YellowPikmin.png");      // Load model texture
    // SetMaterialTexture(&y_pikmin.materials[0], MATERIAL_MAP_DIFFUSE, y_texture);   // Set model diffuse
    // texture y_pikmin.transform = MatrixRotateXYZ((Vector3){ 5.0f, 0.0f, 0.0f });

    // Model b_pikmin = LoadModel("gui/res/models/BluePikmin.iqm");                 // Load OBJ model
    // Texture2D b_texture = LoadTexture("gui/res/textures/BluePikmin.png");      // Load model texture
    // SetMaterialTexture(&b_pikmin.materials[0], MATERIAL_MAP_DIFFUSE, b_texture);   // Set model diffuse
    // texture b_pikmin.transform = MatrixRotateXYZ((Vector3){ 5.0f, 0.0f, 0.0f });

    // Model pikminTop = LoadModel("gui/res/models/LeafToptest.iqm");                 // Load OBJ model
    // Texture2D textureTop = LoadTexture("gui/res/textures/LeafTop.png");      // Load model texture
    // SetMaterialTexture(&pikminTop.materials[0], MATERIAL_MAP_DIFFUSE, textureTop);   // Set model diffuse
    // texture pikminTop.transform = MatrixRotateXYZ((Vector3){ 5.0f, 0.0f, 0.0f });

    GUI::PikminModel pikmin(20, 0);
    pikmin.setPikminModel(GUI::ModelBank::get(GUI::RED_PIKMIN));
    pikmin.setBulbModel(GUI::ModelBank::get(GUI::LEAF_TOP));

    GUI::PikminModel pikmin2(10, 0);
    pikmin2.setPikminModel(GUI::ModelBank::get(GUI::YELLOW_PIKMIN));
    pikmin2.setBulbModel(GUI::ModelBank::get(GUI::FLOWER_TOP));

    GUI::PikminModel pikmin3(0, 0);
    pikmin3.setPikminModel(GUI::ModelBank::get(GUI::BLUE_PIKMIN));
    pikmin3.setBulbModel(GUI::ModelBank::get(GUI::BUD_TOP));

    GUI::PikminModel pikmin4(0, 10);
    pikmin4.setPikminModel(GUI::ModelBank::get(GUI::PURPLE_PIKMIN));
    pikmin4.setBulbModel(GUI::ModelBank::get(GUI::FLOWER_TOP));

    GUI::PikminModel pikmin5(10, 10);
    pikmin5.setPikminModel(GUI::ModelBank::get(GUI::WHITE_PIKMIN));
    pikmin5.setBulbModel(GUI::ModelBank::get(GUI::LEAF_TOP));

    GUI::PikminModel pikmin6(20, 10);
    pikmin6.setPikminModel(GUI::ModelBank::get(GUI::ROCK_PIKMIN));
    pikmin6.setBulbModel(GUI::ModelBank::get(GUI::BUD_TOP));

    GUI::PikminModel pikmin7(10, 20);
    pikmin7.setPikminModel(GUI::ModelBank::get(GUI::WING_PIKMIN));
    pikmin7.setBulbModel(GUI::ModelBank::get(GUI::FLOWER_TOP));

    GUI::PikminModel pikmin8(0, 20);
    pikmin8.setPikminModel(GUI::ModelBank::get(GUI::ICE_PIKMIN));
    pikmin8.setBulbModel(GUI::ModelBank::get(GUI::LEAF_TOP));

    GUI::PikminModel pikmin9(20, 20);
    pikmin9.setPikminModel(GUI::ModelBank::get(GUI::SPECTRAL_PIKMIN));
    pikmin9.setBulbModel(GUI::ModelBank::get(GUI::BUD_TOP));

    Model Map = LoadModel("gui/res/models/Map.glb"); // Load OBJ model
    Model Walls = LoadModel("gui/res/models/Walls.glb"); // Load OBJ model
    Model Rug = LoadModel("gui/res/models/Rug.obj"); // Load OBJ model
    Texture2D textureMap = LoadTexture("gui/res/textures/rug_color.png"); // Load model texture
    SetMaterialTexture(&Rug.materials[0], MATERIAL_MAP_DIFFUSE, textureMap); // Set model diffuse texture
    int animIndex = 0;

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        UpdateCamera(&camera, CAMERA_FREE);

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            pikmin.animationUpdate(0);
            pikmin2.animationUpdate(0);
            pikmin3.animationUpdate(0);
            pikmin4.animationUpdate(0);
            pikmin5.animationUpdate(0);
            pikmin6.animationUpdate(0);
            pikmin7.animationUpdate(0);
            pikmin8.animationUpdate(0);
            pikmin9.animationUpdate(0);
        }

        if (IsKeyPressed(KEY_ONE)) {
            pikmin.setBulbModel(GUI::ModelBank::get(GUI::LEAF_TOP));
            pikmin2.setBulbModel(GUI::ModelBank::get(GUI::LEAF_TOP));
            pikmin3.setBulbModel(GUI::ModelBank::get(GUI::LEAF_TOP));
        }

        if (IsKeyPressed(KEY_TWO)) {
            pikmin.setBulbModel(GUI::ModelBank::get(GUI::BUD_TOP));
            pikmin2.setBulbModel(GUI::ModelBank::get(GUI::BUD_TOP));
            pikmin3.setBulbModel(GUI::ModelBank::get(GUI::BUD_TOP));
        }

        if (IsKeyPressed(KEY_THREE)) {
            pikmin.setBulbModel(GUI::ModelBank::get(GUI::FLOWER_TOP));
            pikmin2.setBulbModel(GUI::ModelBank::get(GUI::FLOWER_TOP));
            pikmin3.setBulbModel(GUI::ModelBank::get(GUI::FLOWER_TOP));
        }

        if (IsKeyPressed(KEY_LEFT_SHIFT)) {
            animIndex++;
            if (animIndex > 10)
                animIndex = 0;
            pikmin.setAnimation(static_cast<GUI::AnimType>(animIndex));
            pikmin2.setAnimation(static_cast<GUI::AnimType>(animIndex));
            pikmin3.setAnimation(static_cast<GUI::AnimType>(animIndex));
            pikmin4.setAnimation(static_cast<GUI::AnimType>(animIndex));
            pikmin5.setAnimation(static_cast<GUI::AnimType>(animIndex));
            pikmin6.setAnimation(static_cast<GUI::AnimType>(animIndex));
            pikmin7.setAnimation(static_cast<GUI::AnimType>(animIndex));
            pikmin8.setAnimation(static_cast<GUI::AnimType>(animIndex));
            pikmin9.setAnimation(static_cast<GUI::AnimType>(animIndex));
        }

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
            {
                pikmin.drawModel(0);
                pikmin2.drawModel(0);
                pikmin3.drawModel(0);
                pikmin4.drawModel(0);
                pikmin5.drawModel(0);
                pikmin6.drawModel(0);
                pikmin7.drawModel(0);
                pikmin8.drawModel(0);
                pikmin9.drawModel(0);
                DrawModel(Map, (Vector3) {0, 0, 0}, 0.05f, WHITE);
                DrawModel(Walls, (Vector3) {0, 0, 0}, 0.05f, WHITE);
                DrawModel(Rug, (Vector3) {0, 0, 0}, 0.05f, WHITE);
            }
            EndMode3D();

            // std::string level = "Lvl " + std::to_string(pikmin.getLevel());
            // DrawText(level.c_str(), 400, 400, 50, DARKGRAY);
            DrawText("P I K M I N", 10, 40, 20, DARKGRAY);

            DrawFPS(10, 10);
        }
        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context
    return 0;
}

int main(int ac, char **av)
{
    InputParser input(ac, av);
    bool failed = false;
    try {
        input.parseMandatory();
    } catch (const InputParser::ParseError &e) {
        std::cout << e.what() << std::endl;
        failed = true;
    } catch (const std::exception &e) {
        failed = true;
    }
    if (ac < 3 || failed) {
        std::cerr << "Bad input (./zappy_gui -p port -h ip)" << std::endl;
        return 84;
    }
    input.parseOption();
    GUI::Warudo warudo(100, input);
    try {
        warudo.setUp();
    } catch (const std::exception &e) {
        std::cerr << "Can't connect to server" << std::endl;
        return 84;
    }
    warudo.loop();
    return 0;
}
