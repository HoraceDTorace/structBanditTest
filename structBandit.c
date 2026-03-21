#include <stdio.h>
#include <stdlib.h>

// You are a bandit, on the run from the law. Three sheriffs are chasing after you. Try to outgun them!
// You have a magical targeting keyboard: type a number, and you'll attack the enemy corresponding to it.


struct entity{
    char name[7];
    int hp;
    int damage;
    char line[50];
    char playerOrEnemy;
};

void entityAttack(struct entity *dealer, struct entity *receiver, int *enemyCount){
    // to do: add a random number between 1 and 3 to determine the sheriff's chance of missing
    // as well as its chance of spawning a friend, based on whether the caller is a entity 'P' or an enemy 'E'
    receiver->hp -= dealer->damage;
    printf("%s dealt %d damage to %s!\n", dealer->name, dealer->damage, receiver->name);
    printf("%s", dealer->line);
        if ((receiver->hp <= 0) && (receiver->playerOrEnemy == 'E')){
            *enemyCount-=1;
        }
}


int main(){

    struct entity player = {"Player", 10, 2, "", 'P'};

    struct entity woody = {"Woody", 6, 2, "\"There's a snake in my boot!\"\n\n", 'E'};
    struct entity goody = {"Goody", 2, 1, "\"No hard feelings...\"\n\n", 'E'};
    struct entity hoody = {"Hoody", 2, 1, "\"I'm just a poor boy. I need no sympathy.\"\n\n", 'E'};

    struct entity* sheriff_array[3] = {&woody, &goody, &hoody};

    int j;

    int len = sizeof(sheriff_array)/sizeof(sheriff_array[0]);
    int enemies_left = len;

    // game loop
    while (player.hp > 0 && enemies_left > 0){
        while (!(j >= 0 && j < len)){
            for(int i = 0; i < len; i++){
                if (sheriff_array[i]->hp > 0){
                    printf("%s\n", sheriff_array[i]->name);
                    printf("Index: %d\n", i);
                    printf("HP: %d\n\n", sheriff_array[i]->hp);
                }
            }
            printf("Select index of enemy to attack: ");
            scanf("%d", &j);
        }
        entityAttack(&player, sheriff_array[j], &enemies_left); // player's turn
        for(int k = 0; k < len; k++){ // enemy's turn
            if (sheriff_array[k]->hp > 0){
                entityAttack(sheriff_array[k], &player, &enemies_left);
            }
        }
        printf("\nPlayer's HP: %d\n", player.hp);
        printf("Enemies left: %d\n\n", enemies_left);
        j = -1; // reset targeted enemy
    }
if(enemies_left == 0){
    printf("You won!\n");
} else {
    printf("Game over!\n");
}
return 0;
}
