#include <stdio.h>
#include <gb/gb.h>
#include "RandomChar.c"

struct ObserverGravity {
    unsigned int gravity;
    unsigned int currentSpeed;
    unsigned int floorPosition;
};

struct ObserverGravity gravity = {-1, 10, 100};

struct Player
{
    unsigned int z;
    unsigned int x;
    unsigned int y;
    BYTE jumping;
};

void setPlayerMove(struct Player *player)
{
    move_sprite(player->z, player->x, player->y);
}

void jump(struct Player *player, struct ObserverGravity *gravity)
{
    if (player->jumping == 0)
    {
        player->jumping = 1;
        gravity->currentSpeed = 10;
    } 
    
    gravity->currentSpeed = gravity->currentSpeed + gravity->gravity;
    player->y = player->y - gravity->currentSpeed;
}

void floorPosition(struct Player *player, struct ObserverGravity *gravity) {
    if(player->y > gravity->floorPosition) {

        player->y = gravity->floorPosition;
        player->jumping = 0;
    }
}

void main()
{
    struct Player player;
    player.z = 0;
    player.x = 10;
    player.y = gravity.floorPosition;
    player.jumping = 0;

    set_sprite_data(0, 0, RandomChar);

    set_sprite_tile(0, 0);
    setPlayerMove(&player);

    DISPLAY_ON;
    SHOW_SPRITES;

    while (1)
    {
        if ((joypad() & J_UP) || player.jumping == 1)
        {
            jump(&player, &gravity);
        }

        if (joypad() & J_LEFT)
        {
            player.x = player.x - 2;
        }

        if (joypad() & J_RIGHT)
        {
            player.x = player.x + 2;
        }

        floorPosition(&player, &gravity);
        setPlayerMove(&player);
        delay(50);
    }
}