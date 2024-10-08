/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Ubuntu]
** File description:
** tile source file
*/

#include "trantor/tile.h"
#include "trantor/config.h"

#include <stdlib.h>


void get_item_count(len_t width, len_t height, tile_t *quants)
{
    len_t total = width * height;

    for (unsigned int i = 0; i < ITEM_COUNT - 1; i++) {
        quants->items[i] = (quant_t) (total * get_item_density(i + 1));
    }
}

quant_t get_total_items(tile_t *tile)
{
    quant_t total = 0;

    for (unsigned int i = 0; i < ITEM_COUNT - 1; i++) {
        total += tile->items[i];
    }
    return total;
}

static bool tile_contains_tile(const tile_t *first, const tile_t *second)
{
    for (unsigned int i = 0; i < ITEM_COUNT - 1; i++) {
        if (first->items[i] < second->items[i])
            return false;
    }
    return true;
}

bool tile_can_invocate(tile_t *tile, unsigned int level)
{
    return tile_contains_tile(tile, get_elev_stones(level));
}

static void take_tile_from_tile(tile_t *container, const tile_t *list)
{
    for (unsigned int i = 0; i < ITEM_COUNT - 1; i++) {
        container->items[i] -= list->items[i];
    }
}

void tile_invocate(tile_t *tile, unsigned int level)
{
    take_tile_from_tile(tile, get_elev_stones(level));
}
