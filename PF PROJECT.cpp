#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <string.h>
#include <windows.h>

int rollDice(int sides);
void waitForRoll();
void BossmockingLines();
void saveGame(int health, int currentQuest);
int loadGame(int * health, int * currentQuest);

int rollDice(int sides) {
  return rand() % sides + 1;
}

void waitForRoll() {
  getchar();
  Beep(400, 200);
}
void BossmockingLines() {
  const char * mockingLines[] = {
    "You dare challenge me? Pathetic Elf!",
    "Your ancestors weep at your feeble attempts!",
    "I will reduce your village to ashes!",
    "This battle will be your last!",
    "You are nothing but an insect beneath my heel!"
  };
  int numLines = sizeof(mockingLines) / sizeof(mockingLines[0]);
  int randomIndex = rand() % numLines;
  printf("The Underworld King Roars: \"%s\"\n", mockingLines[randomIndex]);
}
void saveGame(int health, int currentQuest,const char* heroName) {
  FILE * file = fopen("savegame.txt", "w");
  if (file == NULL) {
    printf("Error saving game.\n");
    return;
  }
  fprintf(file, "%d\n%d\n%s\n", health, currentQuest, heroName);
  fclose(file);
  printf("Game saved successfully!\n");
}
int loadGame(int *health, int *currentQuest, char *heroName) {
    FILE *file = fopen("savegame.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open save file.\n");
        return 0; // Return 0 to indicate failure
    }

    // Reading data from the file
    if (fscanf(file, "%d\n%d\n%[^\n]\n", health, currentQuest, heroName) != 3) {
        printf("Error: Save file format is incorrect.\n");
        fclose(file);
        return 0;
    }

    fclose(file);
    printf("Save file loaded successfully! You are at Quest %d with %d health.\n", *currentQuest, *health);
    return 1; // Return 1 to indicate success
}

int main() {
  srand(time(0));
  char playAgain;
  char heroName[30];
  char swordName[] = "Sword of Legend";
  char inventory[30];
  int itemCount = 0;
  int health = 100;
  int currentQuest = 1;

  printf("Enter your hero's name: ");
  fgets(heroName, sizeof(heroName), stdin);
  heroName[strcspn(heroName, "\n")] = '\0';
  Beep(400, 500);

  while (heroName[0] == '\0') {
    printf("Name cannot be empty. Please enter a hero name: ");
    fgets(heroName, sizeof(heroName), stdin);
    heroName[strcspn(heroName, "\n")] = '\0';
  }
  if (loadGame( &health,& currentQuest, heroName)) {
    char choice;
    printf("\nSave file found! Do you want to continue from your last save? (y/n): ");
    scanf(" %c", & choice);
    getchar();
    Beep(400, 500);
    if (choice != 'y' && choice != 'Y') {
      health = 100;
      currentQuest = 1;
    }
  }

  strncpy(inventory, swordName, sizeof(inventory) - 1);
  inventory[sizeof(inventory) - 1] = '\0';

  printf("\nYou, %s, were born in Eldermoon, the last refuge of the Elven kin in Middle Earth.\n\n", heroName);
  printf("Nestled amidst towering mountains, gushing rivers, and the stately trees of the\n");
  printf("Elven Forest, Eldermoon has been your home for your entire life - a tranquil\n");
  printf("sanctuary far removed from the opulence of grand cities and the intrigues of\n");
  printf("royal courts.\n\n");

  printf("Here, you have known only the gentle cadence of nature, shielded from the tumult\n");
  printf("of human kings and queens. Yet, as the clock strikes midnight, an unsettling\n");
  printf("shadow stirs at the edge of your vision. Its presence is felt, a sinister force\n");
  printf("creeping through the joyous laughter and cheerful smiles of your fellow villagers.\n\n");

  printf("For centuries, dark creatures of the Lower Earth have waged war against the\n");
  printf("creatures of light - the Elves and the noble humans of Middle Earth. In the last\n");
  printf("great conflict, known as the War of the River Styx, the Elven King Midoras\n");
  printf("plunged his legendary Silversong Dagger into the heart of the Underworld King,\n");
  printf("bringing an end to the bloodshed that had plagued his people and their human\n");
  printf("allies.\n\n");

  printf("But the peace he forged was fleeting; the humans, tempted by their darker\n");
  printf("nature, began to see the Elves as a threat, leading to a relentless hunt that\n");
  printf("brought the once-proud Elven race to the brink of extinction.\n\n");

  printf("Today, the village of Eldermoon stands as the last refuge of the Elves, protected\n");
  printf("only by the potent magical borders of the Elven Forest, which incinerate any human\n");
  printf("foolhardy enough to cross. However, it seems that the Underworld King has risen\n");
  printf("once more, thirsting for revenge against both Elves and humans alike. His\n");
  printf("malevolent minions ravage the fields of Eldermoon, leaving devastation in their\n");
  printf("wake.\n\n");

  printf("As chaos erupts, the villagers narrowly escape, clutching the fabled %s - the very\n", swordName);
  printf("blade that King Midoras wielded to vanquish the Underworld King. Legend holds\n");
  printf("that only a true heir of the Elven King can wield the sword and unlock its true\n");
  printf("potential. You, as the descendant of Midoras, are the last hope for your people.\n\n");

  printf("The cries of your kin echo in your heart, urging you to rise against the\n");
  printf("encroaching darkness. Will you take up the mantle of leadership and lead the\n");
  printf("Elves into one final battle for the survival of Elvenkind and the fate of all\n");
  printf("Middle Earth? Embrace your destiny, for the future of your people rests in your\n");
  printf("hands.\n\n");

  printf("Do you want to continue to the battlefield? (y/n): ");
  scanf(" %c", & playAgain);
  getchar();
  Beep(400, 500);

  if (playAgain != 'y' && playAgain != 'Y') {
    printf("\nA horrible tragic ending befalls Eldermoon as you choose to walk away from your destiny.\n");
    printf("The Elves are destroyed, and darkness consumes Middle Earth.\n");
    printf("Game Over.\n");
    exit(0);
  }

  printf("\nYour Inventory:\n");
  printf("- %s\n", inventory);
  printf("Your Health: %d\n\n", health);

  while (health > 0) {
    if (currentQuest == 1) {

      printf("\n--- Quest 1: The Fields of Eldermoon are under attack by a Dark Minion. ---\n");

      while (1) {
        printf("Press Enter to prepare for the dice roll...\n");
        waitForRoll();
        printf("Press Enter again to roll the dice...\n");
        waitForRoll();

        int heroRoll = rollDice(6);
        int enemyRoll = rollDice(6);
        printf("You rolled: %d, Dark Minion rolled: %d\n", heroRoll, enemyRoll);

        if (heroRoll > enemyRoll) {
          printf("You defeated the Dark Minion!\n\n");
          currentQuest++;
          break;
        } else if (heroRoll == enemyRoll) {
          printf("Your swords clashed and sent a loud roar amongst the lands. The battle continues!\n\n");
        } else {
          health -= 20;
          if (health <= 0) {
            printf("You were defeated by the Dark Minion...\n");
            printf("Your health is now: %d\n\n", health);
            printf("Game Over.\n");
            exit(0);
          } else {
            printf("The Dark Minion strikes you! Your health is now: %d\n", health);
            printf("The battle continues...\n\n");
          }
        }
      }
      char exitChoice;
      printf("Do you want to save and exit the game? (y/n): ");
      scanf(" %c", & exitChoice);
      getchar();
      Beep(400, 500);
      if (exitChoice == 'y' || exitChoice == 'Y') {
        saveGame(health, currentQuest, heroName);
        printf("Exiting game...\n");
        exit(0);
      }
    }

    if (currentQuest == 2) {
      printf("\n--- Quest 2: You encounter a mysterious chest in the forest. ---\n");
      printf("Press Enter to prepare for the dice roll...\n");
      waitForRoll();
      printf("Press Enter again to roll the dice...\n");
      waitForRoll();

      int chestResult = rollDice(3);
      if (chestResult == 1) {
        printf("Lucky! You found a health potion in the chest!\n");
        health += 20;
        printf("Your health is now: %d\n\n", health);
        currentQuest++;
        break;
      } else if (chestResult == 2) {
        printf("Oh no! The chest was booby-trapped! You lose 10 health.\n");
        health -= 10;
        printf("Your health is now: %d\n\n", health);
        currentQuest++;
        break;
      } else {
        printf("The chest was a Mimic! It lunges at you, snarling.\n");
        int mimicHealth = 3;
        while (mimicHealth > 0 && health > 0) {
          printf("Press Enter to roll the dice to fight the Mimic...\n");
          waitForRoll();

          int heroRoll = rollDice(6);
          int enemyRoll = rollDice(6);
          printf("You rolled: %d, Mimic rolled: %d\n", heroRoll, enemyRoll);

          if (heroRoll > enemyRoll) {
            mimicHealth--;
            printf("You strike the Mimic! Its health is now %d.\n", mimicHealth);
          } else if (heroRoll == enemyRoll) {
            printf("Your swords clashed with the Mimic, sending sparks flying!\n");
          } else {
            health -= 10;
            printf("The Mimic hits you! Your health is now: %d\n", health);

          }
        }
        if (health == 0) {
          printf("The Mimic devoured you. Game Over.\n");
          return 0;
        } else if (mimicHealth == 0) {
          printf("You defeated the Mimic! Its body dissolves into nothingness.\n");
          currentQuest++;
          break;
        }
      }
    }
    char exitChoice;
    printf("Do you want to save and exit the game? (y/n): ");
    scanf(" %c", & exitChoice);
    Beep(400, 500);
    if (exitChoice == 'y' || exitChoice == 'Y') {
      saveGame(health, currentQuest, heroName);
      printf("Exiting game...\n");
      exit(0);
    }
  }

  if (currentQuest == 3) {

    printf("\n--- Quest 3: A wise old Elf presents you with a riddle. ---\n");
    printf("\"I speak without a mouth and hear without ears. I have no body, but I come alive with wind. What am I?\"\n");
    printf("Choose your answer: (1) A spirit (2) An echo (3) The wind\n");

    int choice;
    scanf("%d", & choice);
    Beep(400, 500);
    if (choice == 2) {
      printf("Correct! You have proven your wisdom.\n\n");
    } else {
      health -= 20;
      printf("Wrong answer. The correct answer was 'An echo'.\n");
      printf("Your health is now: %d\n\n", health);
    }
    currentQuest++;

    char exitChoice;
    printf("Do you want to save and exit the game? (y/n): ");
    scanf(" %c", & exitChoice);
    Beep(400, 500);
    if (exitChoice == 'y' || exitChoice == 'Y') {
      saveGame(health, currentQuest, heroName);
      printf("Exiting game...\n");
      exit(0);
    }
  }

  if (currentQuest == 4) {
    printf("Your health before the Final Quest: %d\n\n", health);
    printf("\n--- Final Quest: The Underworld King emerges from the shadows! ---\n");
    printf("");
    int bossHealth = 8;
    int potion = 1;

    while (bossHealth > 0 && health > 0) {
      BossmockingLines();

      printf("Press Enter to roll the dice to fight the Underworld King...\n");
      waitForRoll();

      int heroRoll = rollDice(6);
      int enemyRoll = rollDice(6);
      printf("You rolled: %d, Underworld King rolled: %d\n", heroRoll, enemyRoll);

      if (heroRoll > enemyRoll) {
        bossHealth -= 2;
        printf("You strike the Underworld King! His health is now %d.\n", bossHealth);
      } else if (heroRoll == enemyRoll) {
        printf("Your swords clashed and sent a loud roar amongst the lands.\n");
      } else {
        health -= 20;
        if (health < 0) health = 0;
        printf("The Underworld King strikes you! Your health is now %d.\n", health);
      }

      if (health <= 20 && potion == 1) {
        printf("A health potion appears from the ruins! You gain 20 health.\n");
        health += 20;
        potion = 0;
      }
      if (health == 0) {
        printf("\nYou were defeated by the Underworld King. Middle Earth falls into darkness.\n");
      }
      if (bossHealth == 0) {
        printf("\nCongratulations,%s! You have defeated the Underworld King and saved Middle Earth!\n", heroName);
        break;
      }
    }


}
return 0;
}
