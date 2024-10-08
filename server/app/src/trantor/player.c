/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** player sourcez file
*/

#include "trantor/player.h"
#include "buffer.h"
#include "sstrings.h"
#include "serrorh.h"
#include "trantor/config.h"

#include <stdlib.h>


void init_egg(player_t *player, team_t team, coord_t c)
{
    static unsigned int last_n_given = 1;

    *player = (player_t){0};
    player->is_egg = true;
    player->team = team;
    player->coord[0] = c[0];
    player->coord[1] = c[1];
    player->n = last_n_given;
    last_n_given++;
}

void hatch_egg(player_t *player)
{
    player->is_egg = false;
    player->direction = rand() % 4;
    for (int i = 0; i < ITEM_COUNT - 1; i++) {
        player->inventory.items[i] = 0;
    }
    player->elevation = 1;
    if (str_init(&player->pcmd_buffer, NULL) != BUF_OK)
        LOG_ERROR("Failed to init player pcmd buffer");
    player->npcmd = 0;
    if (str_init(&player->response_buffer, NULL) != BUF_OK)
        LOG_ERROR("Failed to init player response buffer");
    player->incantator = NULL;
    player->time_left = START_LIFE_UNITS;
    player->busy = false;
    player->pcmd_exec.command = 0;
    player->pcmd_exec.exec_time_left = 0;
    player->is_dead = false;
}

void destroy_player(void *player)
{
    player_t *p = player;

    if (!p->is_egg) {
        str_reset(&p->pcmd_buffer);
        str_reset(&p->response_buffer);
    }
}
