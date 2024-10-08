/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** pmcd funcs source file
*/

#include "buffer.h"
#include "trantor/map.h"
#include "trantor/map_fn.h"
#include "trantor/pcmd_args.h"
#include "trantor/tile.h"
#include "trantor/string_utils.h"
#include "trantor/config.h"
#include "vector.h"

#include <stdlib.h>
#include <stdio.h>


static void fill_tiles(pcmd_args_t *args, loc_tile_t *tiles)
{
    direction_t ray_dir = (args->player->direction + 1) % 4;
    unbounded_coord_t start =
        {(int) args->player->coord[0], (int) args->player->coord[1]};
    size_t len = 1;

    get_loc_tile_line(args->map,
        (ray_t){{start[0], start[1]}, ray_dir}, 1, tiles);
    for (unsigned int i = 0; i < args->player->elevation; i++) {
        add_direction(&start, args->player->direction);
        add_direction(&start, (ray_dir + 2) % 4);
        get_loc_tile_line(args->map, (ray_t){{start[0], start[1]}, ray_dir},
            (i + 1) * 2 + 1, tiles + len);
        len += (i + 1) * 2 + 1;
    }
}

static loc_tile_t *internal_player_look(pcmd_args_t *args, size_t *lenbuf)
{
    loc_tile_t *tiles;
    size_t len = 0;

    for (unsigned int i = 0; i <= args->player->elevation; i++)
        len += i * 2 + 1;
    tiles = malloc(sizeof(loc_tile_t) * len);
    if (!tiles)
        return NULL;
    *lenbuf = len;
    fill_tiles(args, tiles);
    return tiles;
}

static size_t get_tile_req_size(vector_t *players, loc_tile_t *ltile)
{
    size_t len = 0;
    player_t *p;

    for (size_t i = 0; i < players->nmemb; i++) {
        p = (player_t *) vec_at(players, i);
        if (p->is_dead)
            continue;
        if (!COORD_EQ(p->coord, ltile->coord))
            continue;
        len += 7;
        ltile->nplayer++;
    }
    for (unsigned int i = 0; i < ITEM_COUNT - 1; i++) {
        len += ((get_item_name_len(i + 1) + 1) * ltile->tile->items[i]);
    }
    return len;
}

static void sprintf_tile(char *msg, loc_tile_t *ltile, size_t *len)
{
    for (unsigned int i = 0; i < ltile->nplayer; i++) {
        *len += sprintf(msg + *len, "player ");
    }
    for (unsigned int i = 0; i < ITEM_COUNT - 1; i++) {
        for (unsigned int j = 0; j < ltile->tile->items[i]; j++) {
            *len += sprintf(msg + *len, "%s ", get_item_name(i + 1));
        }
    }
}

static void player_look_msg(
    pcmd_args_t *args, size_t tnb, loc_tile_t *tiles)
{
    char *msg = NULL;
    size_t len = 0;

    msg = STRING_END(&args->player->response_buffer);
    len = sprintf(msg, "[ ");
    for (size_t i = 0; i < tnb; i++) {
        sprintf_tile(msg, tiles + i, &len);
        if (i != tnb - 1)
            len += sprintf(msg + len, ", ");
    }
    free(tiles);
    len += sprintf(msg + len, "]\n");
    args->player->response_buffer.nmemb += len;
}

void player_look(pcmd_args_t *args)
{
    size_t tnb = 0;
    loc_tile_t *tiles = internal_player_look(args, &tnb);
    size_t len = 6 + tnb * 2;

    for (size_t i = 0; i < tnb; i++)
        len += get_tile_req_size(args->players, tiles + i);
    if (vec_reserve(
        str_to_vec(&args->player->response_buffer), len) != BUF_OK) {
        free(tiles);
        return;
    }
    player_look_msg(args, tnb, tiles);
}

void player_inventory(pcmd_args_t *args)
{
    char *msg = NULL;
    size_t len = 4 + 6 + 1;

    for (unsigned int i = 0; i < ITEM_COUNT - 1; i++)
        len += snprintf(NULL, 0, "%s %d", get_item_name(i),
            args->player->inventory.items[i]);
    if (vec_reserve(str_to_vec(&args->player->response_buffer), len) != BUF_OK)
        return;
    msg = STRING_END(&args->player->response_buffer);
    len = sprintf(msg, "[ ");
    for (unsigned int i = 0; i < ITEM_COUNT - 1; i++) {
        len += sprintf(msg + len, "%s %d", get_item_name(i + 1),
            args->player->inventory.items[i]);
        if (i != 6)
            len += sprintf(msg + len, ", ");
    }
    len += sprintf(msg + len, " ]\n");
    args->player->response_buffer.nmemb += len;
}

void player_co_num(pcmd_args_t *args)
{
    talkf(&args->player->response_buffer, "%d\n", args->cnb);
}

void player_take(pcmd_args_t *args)
{
    tile_t *t;

    t = CGET_TILE(args->map, args->player->coord);
    if (!HAS_ITEM(*t, args->item)) {
        SAY_KO(&args->player->response_buffer);
        return;
    }
    TAKE_ITEM(*t, args->item);
    ADD_ITEM(args->player->inventory, args->item);
    SAY_OK(&args->player->response_buffer);
    talkf(args->log, "pgt %d %d\n", args->player->n, args->item - 1);
}
