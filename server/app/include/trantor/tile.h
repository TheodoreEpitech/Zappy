/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** tile header
*/

#pragma once

#include "trantor/common.h"
#include "trantor/item.h"

#include <stdbool.h>

#define GET_ITEM(tl, tp) ((tl).items[(tp) - 1])
#define SET_ITEM(tl, tp, val) ((tl).items[(tp) - 1] = val)
#define HAS_ITEM(tl, tp) (GET_ITEM(tl, tp) > 0)
#define TAKE_ITEM(tl, tp) (GET_ITEM(tl, tp)--)
#define ADD_ITEM(tl, tp) (GET_ITEM(tl, tp)++)

typedef struct tile_s {
    quant_t items[7];
} tile_t;

typedef len_t coord_t[2];

typedef int unbounded_coord_t[2];

typedef struct loc_tile_s {
    coord_t coord;
    tile_t *tile;
    unsigned int nplayer;
} loc_tile_t;

void get_item_count(len_t width, len_t height, tile_t *quants);
quant_t get_total_items(tile_t *tile);
bool tile_can_invocate(tile_t *tile, unsigned int level);
void tile_invocate(tile_t *tile, unsigned int level);
