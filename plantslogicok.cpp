#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

// Initializing Dimensions
const int resolutionX = 960;
const int resolutionY = 640;
const int boxPixelsX = 32;
const int boxPixelsY = 32;
const int gameRows = resolutionX / boxPixelsX; // Total rows on grid
const int gameColumns = resolutionY / boxPixelsY; // Total columns on grid

// Additional constants
const int MAX_HIVES = 15;
// Function Declarations - Add new hive-related functions
void drawHive(RenderWindow& window, float x, float y, Texture& hiveTexture);
void moveBee(float& Bee_x, float& Bee_y, bool& beeMovingRight, bool& Bee_exists, Clock& BeeClock, 
             float plantX[], float plantY[], bool plantExists[], int maxPlants, 
             Sprite plantSprites[], Texture& plantTexture, 
             float honeycombX[], float honeycombY[], bool Honeycomb_exists[], 
             float hiveX[], float hiveY[], bool Hive_exists[], const int maxBees);

// Function Declarations
void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite);
void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock);
void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite);
void drawBee(RenderWindow& window, float& Bee_x, float& Bee_y, Sprite& BeeSprite);
//void moveBee(float& Bee_x, float& Bee_y, bool& beeMovingRight, bool& Bee_exists, Clock& BeeClock, float plantX[], float plantY[], bool plantExists[], int maxPlants,Sprite plantSprites[],Texture& plantTexture);
/*void moveBee(float& Bee_x, float& Bee_y, bool& beeMovingRight, bool& Bee_exists, Clock& BeeClock, 
           float plantX[], float plantY[], bool plantExists[], int maxPlants, Sprite plantSprites[], Texture& plantTexture,float honeycombX[], float honeycombY[],bool //Honeycomb_exists[],const int maxBees);
           */

bool checkCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
void drawHoneycomb(RenderWindow& window, float x, float y, Texture& honeycombTexture); 
void drawHoneyrandomcomb(RenderWindow& window, float x, float y, Texture& honeycombTexture); 

void drawspray1(RenderWindow& window, float& spray1_x, float& spray1_y, Sprite& spraySprite1);
void drawspray2(RenderWindow& window, float& spray2_x, float& spray2_y, Sprite& spraySprite2);
void drawblueBee(RenderWindow& window, float& Bbee_x, float& Bbee_y, Sprite& BbeeSprite);
//void moveBlueBee(float& Bbee_x, float& Bbee_y, Clock& BbeeClock,float honeycombX[], float honeycombY[], bool Honeycomb_exists[],const int maxBees,int score,sf::Text& gametext);
void moveBlueBee(float& Bbee_x, float& Bbee_y, Clock& BbeeClock,
                 float honeycombX[], float honeycombY[], bool Honeycomb_exists[],
                 const int maxBees, int& score, sf::Text& gametext);

   void drawPlants(RenderWindow& window, float plantX[], float plantY[], bool plantExists[], Sprite plantSprites[], int maxPlants);
bool isPathBlocked(float player_x, float player_y, float moveX, float moveY, float plantX[], float plantY[], bool plantExists[], int maxPlants);


int main() {
    srand(time(0));

    // RenderWindow
    RenderWindow window(VideoMode(resolutionX, resolutionY), "Buzz Bombers", Style::Close | Style::Titlebar);
    window.setPosition(Vector2i(500, 200));

    // Background Music
    Music bgMusic;
    bgMusic.openFromFile("Music/Forest.ogg");
    bgMusic.play();
    bgMusic.setVolume(50);

    // Player
    
    float player_y = (gameColumns - 4) * boxPixelsY;
    //float player_y =32*2;

float player_x = (gameRows -16) * boxPixelsX;
   // float player_x=448;
   
    // Hive Initialization
    float hiveX[MAX_HIVES], hiveY[MAX_HIVES];
    bool Hive_exists[MAX_HIVES];
    Texture hiveTexture;
    hiveTexture.loadFromFile("hive.png"); // Add a hive image

    // Initialize hive data
    for (int i = 0; i < MAX_HIVES; i++) {
        Hive_exists[i] = false;
    }





    Texture playerTexture;
    Sprite playerSprite;
    playerTexture.loadFromFile("spray.png");
    playerSprite.setTexture(playerTexture);

    // Bullet
    float bullet_x = player_x;
    float bullet_y = player_y;
    bool bullet_exists = false;

    Clock bulletClock;
    Texture bulletTexture;
    Sprite bulletSprite;
    bulletTexture.loadFromFile("bullet.png");
    bulletSprite.setTexture(bulletTexture);
    bulletSprite.setScale(3, 3);
    bulletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

    // Bee Initialization
    Texture BeeTexture;
    Sprite BeeSprite;
    BeeTexture.loadFromFile("Regular_bee.png");
    BeeSprite.setTexture(BeeTexture);
    
    // Blue bee
    Texture BbeeTexture;
    Sprite BbeeSprite;
    BbeeTexture.loadFromFile("123.png");
    BbeeSprite.setTexture(BbeeTexture);
    BbeeSprite.setColor(sf::Color::Blue);
    
    
   // sf::IntRect cropArea(32, 0, 32, 32); // Adjust (x, y, width, height) as needed
   // BbeeSprite.setTextureRect(cropArea);
    
    
    
    
    // plant
    const int maxPlants = 20; // Maximum number of plants allowed
	float plantX[maxPlants], plantY[maxPlants];
	bool plantExists[maxPlants];
	Texture plantTexture;
	Sprite plantSprites[maxPlants];
 
    
    // Load plant texture
plantTexture.loadFromFile("obstacles.png");

// Initialize plant data
	for (int i = 0; i < maxPlants; i++) {
    	plantExists[i] = false;
		}

  //  Bbee_x = rand() % (800 - 50);  // Assuming 50 is the bee's width
    //        Bbee_y = rand() % (600 - 50);  
            
            
             float Bbee_x=rand() % (800 - 50); 
    float Bbee_y=rand() % (600 - 50); 
            
            
   // float Bbee_x=rand() % 15; 
  //  float Bbee_y=rand() % 15; 
    bool blueBeeMovingRight = true; // Direction flag for the blue bee
	Clock BbeeClock;               // Clock for controlling blue bee movement timing

    
    // spraylife1
    float spray1_x = 20;
    float spray1_y = 585;
    
    //spraylifecan
    Texture sprayTexture1;
    Sprite spraySprite1;
    sprayTexture1.loadFromFile("spray.png");
    spraySprite1.setTexture(sprayTexture1);
    
    // spraylife2
    float spray2_x = 80;
    float spray2_y = 585;
    
    //spraylifecan
    Texture sprayTexture2;
    Sprite spraySprite2;
    sprayTexture2.loadFromFile("spray.png");
    spraySprite2.setTexture(sprayTexture2);
    
    // Bee Properties
    const int maxBees = 15; // Number of bees
    float Bee_x[maxBees];
    float Bee_y[maxBees];
    bool beeMovingRight[maxBees];
    bool Bee_exists[maxBees];
    Clock BeeClock[maxBees];
    bool Honeycomb_exists[maxBees]; // ----

    int score = 0;

    sf::Font gamefont;
    gamefont.loadFromFile("Arial.ttf");

    sf::Text gametext;
    gametext.setFont(gamefont);
    gametext.setString("score:" + std::to_string(score));
    gametext.setPosition(750,600);
    gametext.setFillColor(sf::Color::Red);

    // Initializing bee and honeycomb
    for (int i = 0; i < maxBees; i++) {
        Bee_x[i] = rand() % (resolutionX - boxPixelsX); // Random horizontal position
        Bee_y[i] = -(i * 100);                         // Staggered vertical positions
        beeMovingRight[i] = rand() % 2;                // Random initial direction
        Honeycomb_exists[i] = false;
        Bee_exists[i] = true;                          // All bees start active
    }

    // Honeycomb Texture
    Texture honeycombTexture;
    honeycombTexture.loadFromFile("honeycomb.png");

// Honeycomb Positions
    float honeycombX[maxBees], honeycombY[maxBees];
    
    			//-----------------------------------------------------------------------------------
    // Initialize bee and honeycomb
for (int i = 0; i < maxBees; i++) {
    // Randomize horizontal start position and side
    if (rand() % 2 == 0) {
        Bee_x[i] = -(rand() % (resolutionX - boxPixelsX)); // Start from left side
        beeMovingRight[i] = true; // Moving right
    } else {
        Bee_x[i] = resolutionX + (rand() % (resolutionX - boxPixelsX)); // Start from right side
        beeMovingRight[i] = false; // Moving left
    }
    
    Bee_y[i] = -(i * 100);                         // Staggered vertical positions
    Honeycomb_exists[i] = false;
    Bee_exists[i] = true;                          // All bees start active
}


    // Ground
    RectangleShape groundRectangle(Vector2f(960, 64));
    groundRectangle.setPosition(0, (gameColumns - 2) * boxPixelsY);
    groundRectangle.setFillColor(Color::Green);

    // Battery Visualization
    RectangleShape batteryOutline(Vector2f(128, 32)); // Outline of the battery
    batteryOutline.setPosition(400, 580);
    batteryOutline.setFillColor(Color::Transparent);
    batteryOutline.setOutlineThickness(2);
    batteryOutline.setOutlineColor(Color::White);
    
    RectangleShape batteryLevel(Vector2f(128, 32)); // Inner battery level
    batteryLevel.setPosition(400, 580);
    batteryLevel.setFillColor(Color::Red);

    int bulletsFired = 0;
    int batteryLevelCount = 8; // Battery starts fully charged (8 segments)
    bool canShoot = true; // Boolean to check if the player can shoot

    // Game Loop
    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                return 0;
            }
        }

        
// Movement checks and updating position

if (Keyboard::isKeyPressed(Keyboard::Left)) {
if(player_x > 0)
    player_x -= 2;  // Move left by 32 pixels
}

if (Keyboard::isKeyPressed(Keyboard::Right) ) {

if( player_x < (gameColumns - 1) * boxPixelsX)
    player_x += 2;  // Move right by 32 pixels
}

// Optional: For a more grid-aligned movement system
// We need to update the movement with grid snapping for precision.

float next_x = player_x;  // Store the proposed next x-coordinate
float next_y = player_y;  // Store the proposed next y-coordinate

if (Keyboard::isKeyPressed(Keyboard::Left) && player_x > 0) {
    next_x = player_x - 2;  // Calculate the next x position
    if (!isPathBlocked(player_x, player_y, next_x, next_y, plantX, plantY, plantExists, maxPlants)) {
        player_x = next_x;  // Update the player's x position if path is clear
    }
}

if (Keyboard::isKeyPressed(Keyboard::Right) && player_x < resolutionX - boxPixelsX*2) {
    next_x = player_x + 2;  // Calculate the next x position
    if (!isPathBlocked(player_x, player_y, next_x, next_y, plantX, plantY, plantExists, maxPlants)) {
        player_x = next_x;  // Update the player's x position if path is clear
    }
}

        // Bullet Firing
        if (canShoot && Keyboard::isKeyPressed(Keyboard::Space) && !bullet_exists) {
            bullet_exists = true;
            bullet_x = player_x + (boxPixelsX / 2);
            bullet_y = player_y;
            bulletsFired++;

            // Reduce battery level every 8 bullets
            if (bulletsFired % 8 == 0 && batteryLevelCount > 0) {
                batteryLevelCount--;
                batteryLevel.setSize(Vector2f(128, batteryLevelCount * 4)); // Reduce the height
                batteryLevel.setPosition(400, 580 + (8 - batteryLevelCount) * 4); // Adjust position
            }

            // After 56 bullets, refill battery and hide spray can 1
            if (bulletsFired == 56) {
                batteryLevelCount = 8; // Refill battery
                batteryLevel.setSize(Vector2f(128, 32)); // Full battery size
                batteryLevel.setPosition(400, 580); // Reset positions
                spraySprite1.setColor(Color::Transparent); // Hide spray can 1
            }

            // After 112 bullets, disable shooting and hide spray can 2
            if (bulletsFired == 112) {
                spraySprite2.setColor(Color::Transparent); // Hide spray can 2
                canShoot = false; // Disable shooting
            }
        }
//----------------------------------------------------------------------moveBee(Bee_x[i], Bee_y[i], beeMovingRight[i], Bee_exists[i], BeeClock[i], plantX, plantY, plantExists, maxPlants, plantSprites,plantTexture);
        // Bullet Logic
        if (bullet_exists) {
            moveBullet(bullet_y, bullet_exists, bulletClock);
        }


 for (int i = 0; i < maxBees; i++) {
            if (Bee_exists[i]) {
                moveBee(Bee_x[i], Bee_y[i], beeMovingRight[i], Bee_exists[i], 
                        BeeClock[i], plantX, plantY, plantExists, maxPlants, 
                        plantSprites, plantTexture, honeycombX, honeycombY, 
                        Honeycomb_exists, hiveX, hiveY, Hive_exists, maxBees);
            }
        }

        // Drawing section - Add hive drawing
        for (int i = 0; i < MAX_HIVES; i++) {
            if (Hive_exists[i]) {
                drawHive(window, hiveX[i], hiveY[i], hiveTexture);
            }
        }

       




//bee collion end

        // Draw
        window.clear();

        window.draw(groundRectangle);

        // Display Battery Visualization
        window.draw(batteryOutline);
        window.draw(batteryLevel);

        // Draw Player
        drawPlayer(window, player_x, player_y, playerSprite);

        // Draw Bullet
        if (bullet_exists) {
            drawBullet(window, bullet_x, bullet_y, bulletSprite);
        }

        // Draw Bee
        for (int i = 0; i < maxBees; i++) {
            if (Bee_exists[i]) {
            
                drawBee(window, Bee_x[i], Bee_y[i], BeeSprite);
            }
        }

        // Draw Blue Bee
       // drawblueBee(window, Bbee_x, Bbee_y, BbeeSprite);
        // Move the blue bee
moveBlueBee(Bbee_x, Bbee_y, BbeeClock,honeycombX,honeycombY, Honeycomb_exists, maxBees, score, gametext);

// Draw the blue bee
drawblueBee(window, Bbee_x, Bbee_y, BbeeSprite);

        
        // Draw spray
        drawspray1(window, spray1_x, spray1_y, spraySprite1);
        drawspray2(window, spray2_x, spray2_y, spraySprite2);

        // Draw Honeycomb
        for (int i = 0; i < maxBees; i++) {
            if (Honeycomb_exists[i]) {
                drawHoneycomb(window, Bee_x[i], Bee_y[i], honeycombTexture);
            }
        }

        // Display Score
        window.draw(gametext);
// Draw plants
drawPlants(window, plantX, plantY, plantExists, plantSprites, maxPlants);
        window.display();
    }

    return 0;
}



// Functions
void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite) {
    playerSprite.setPosition(player_x, player_y);
    window.draw(playerSprite);
}

void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock) {
    if (bulletClock.getElapsedTime().asMilliseconds() < 20)
        return;

    bulletClock.restart();
    bullet_y -= 10;
    if (bullet_y < -32)
        bullet_exists = false;
}

void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite) {
    bulletSprite.setPosition(bullet_x, bullet_y);
    window.draw(bulletSprite);
}

void drawBee(RenderWindow& window, float& Bee_x, float& Bee_y, Sprite& BeeSprite) {
    BeeSprite.setPosition(Bee_x, Bee_y);
    window.draw(BeeSprite);
    
    
}

void moveBee(float& Bee_x, float& Bee_y, bool& beeMovingRight, bool& Bee_exists, sf::Clock& BeeClock, 
             float plantX[], float plantY[], bool plantExists[], int maxPlants, 
             sf::Sprite plantSprites[], sf::Texture& plantTexture, 
             float honeycombX[], float honeycombY[], bool Honeycomb_exists[], 
             float hiveX[], float hiveY[], bool Hive_exists[], const int maxBees) {

    // Control bee movement speed
    if (BeeClock.getElapsedTime().asMilliseconds() < 4)
        return;

    BeeClock.restart();

    // Hive creation variables
    bool hiveCreationPossible = false;
    int stuckHoneycombIndex = -1;

    // Check for collision with honeycombs to trigger hive creation
    for (int i = 0; i < maxBees; i++) {
        if (Honeycomb_exists[i] && 
            checkCollision(Bee_x, Bee_y, boxPixelsX, boxPixelsY, honeycombX[i], honeycombY[i], boxPixelsX, boxPixelsY)) {
            
            // Check if another honeycomb blocks the bee's path
            for (int j = 0; j < maxBees; j++) {
                if (i != j && Honeycomb_exists[j] && 
                    honeycombX[j] == honeycombX[i] && 
                    honeycombY[j] < honeycombY[i] && 
                    honeycombY[j] + boxPixelsY >= honeycombY[i]) {
                    
                    hiveCreationPossible = true;
                    stuckHoneycombIndex = i;
                    break;
                }
            }

            if (hiveCreationPossible) break;
        }
    }

    // Check if bee moves into a plant area
    bool moveBlocked = false;
    for (int i = 0; i < maxPlants; i++) {
        if (plantExists[i] && 
            (Bee_x + boxPixelsX > plantX[i] && Bee_x < plantX[i] + boxPixelsX) && 
            (Bee_y + boxPixelsY > plantY[i] && Bee_y < plantY[i] + boxPixelsY)) {
            moveBlocked = true;
            break;
        }
    }

    // Bee movement logic
    if (!moveBlocked) {
        if (beeMovingRight) {
            Bee_x += 10; // Move right
            if (Bee_x >= resolutionX - boxPixelsX) {
                beeMovingRight = false;
                Bee_y += 32; // Move down a row
            }
        } else {
            Bee_x -= 10; // Move left
            if (Bee_x <= 0) {
                beeMovingRight = true;
                Bee_y += 32; // Move down a row
            }
        }
    }

    // Hive creation logic
    if (hiveCreationPossible && stuckHoneycombIndex != -1) {
        for (int i = 0; i < MAX_HIVES; i++) {
            if (!Hive_exists[i]) {
                // Create the hive at the current bee position
                hiveX[i] = Bee_x;
                hiveY[i] = Bee_y;
                Hive_exists[i] = true;

                Bee_exists = false; // Remove the bee after hive creation
                std::cout << "Hive created at (" << hiveX[i] << ", " << hiveY[i] << ")" << std::endl;
                break;
            }
        }
    }

    // Remove bee if it moves off the screen
    if (Bee_y > resolutionY) {
        Bee_exists = false;
    }

    // Ground collision logic for plant placement
    if (Bee_y > resolutionY - boxPixelsY - 60) {
        Bee_exists = false; // Remove the bee after hitting the ground

        static bool firstBee = true;
        static float lastLeftPlantX = -boxPixelsX;
        static float lastRightPlantX = resolutionX;

        if (firstBee) {
            firstBee = false;

            // Place initial plants on the left and right
            for (int i = 0; i < maxPlants; i++) {
                if (!plantExists[i]) {
                    plantX[i] = 0;
                    plantY[i] = resolutionY - boxPixelsY - 65;
                    plantExists[i] = true;
                    plantSprites[i].setTexture(plantTexture);
                    plantSprites[i].setPosition(plantX[i], plantY[i]);
                    lastLeftPlantX = plantX[i];
                    break;
                }
            }
            for (int i = 0; i < maxPlants; i++) {
                if (!plantExists[i]) {
                    plantX[i] = resolutionX - boxPixelsX;
                    plantY[i] = resolutionY - boxPixelsY - 65;
                    plantExists[i] = true;
                    plantSprites[i].setTexture(plantTexture);
                    plantSprites[i].setPosition(plantX[i], plantY[i]);
                    lastRightPlantX = plantX[i];
                    break;
                }
            }
        } else {
            // Place plants dynamically
            bool placed = false;
            float newX = Bee_x <= resolutionX / 2 ? lastLeftPlantX + boxPixelsX : lastRightPlantX - boxPixelsX;

            for (int i = 0; i < maxPlants; i++) {
                if (!plantExists[i]) {
                    if (newX < 0) newX = boxPixelsX;
                    if (newX > resolutionX - boxPixelsX) newX = resolutionX - 2 * boxPixelsX;

                    plantX[i] = newX;
                    plantY[i] = resolutionY - boxPixelsY - 65;
                    plantExists[i] = true;
                    plantSprites[i].setTexture(plantTexture);
                    plantSprites[i].setPosition(plantX[i], plantY[i]);

                    if (Bee_x <= resolutionX / 2)
                        lastLeftPlantX = plantX[i];
                    else
                        lastRightPlantX = plantX[i];

                    placed = true;
                    break;
                }
            }

            if (!placed) {
                std::cout << "No more space for new plants!" << std::endl;
            }
        }
    }
}


/*
void moveBee(float& Bee_x, float& Bee_y, bool& beeMovingRight, bool& Bee_exists, Clock& BeeClock, 
             float plantX[], float plantY[], bool plantExists[], int maxPlants, 
             Sprite plantSprites[], Texture& plantTexture, 
             float honeycombX[], float honeycombY[], bool Honeycomb_exists[], 
             float hiveX[], float hiveY[], bool Hive_exists[], const int maxBees) {
    // Control bee movement speed
    if (BeeClock.getElapsedTime().asMilliseconds() < 4)
        return;

    BeeClock.restart();

    // Hive creation variables
    bool hiveCreationPossible = false;
    int stuckHoneycombIndex = -1;

    // Check for collision with honeycombs to trigger hive creation
    for (int i = 0; i < maxBees; i++) {
        if (Honeycomb_exists[i] && 
            checkCollision(Bee_x, Bee_y, boxPixelsX, boxPixelsY, honeycombX[i], honeycombY[i], boxPixelsX, boxPixelsY)) {
            
            // Check if another honeycomb blocks the bee's path
            for (int j = 0; j < maxBees; j++) {
                if (i != j && Honeycomb_exists[j] && 
                    honeycombX[j] == honeycombX[i] && 
                    honeycombY[j] < honeycombY[i] && 
                    honeycombY[j] + boxPixelsY >= honeycombY[i]) {
                    
                    hiveCreationPossible = true;
                    stuckHoneycombIndex = i;
                    break;
                }
            }

            if (hiveCreationPossible) break;
        }
    }

    // Bee movement logic
    if (beeMovingRight) {
        Bee_x += 10; // Move right
        if (Bee_x >= resolutionX - boxPixelsX) {
            beeMovingRight = false;
            Bee_y += 32; // Move down a row
        }
    } else {
        Bee_x -= 10; // Move left
        if (Bee_x <= 0) {
            beeMovingRight = true;
            Bee_y += 32; // Move down a row
        }
    }

    // Hive creation logic
    if (hiveCreationPossible && stuckHoneycombIndex != -1) {
        for (int i = 0; i < MAX_HIVES; i++) {
            if (!Hive_exists[i]) {
                // Create the hive at the current bee position
                hiveX[i] = Bee_x;
                hiveY[i] = Bee_y;
                Hive_exists[i] = true;

                Bee_exists = false; // Remove the bee after hive creation
                std::cout << "Hive created at (" << hiveX[i] << ", " << hiveY[i] << ")" << std::endl;
                break;
            }
        }
    }

    // Remove bee if it moves off the screen
    if (Bee_y > resolutionY) {
        Bee_exists = false;
    }

    // Ground collision logic for plant placement
    if (Bee_y > resolutionY - boxPixelsY - 60) {
        Bee_exists = false; // Remove the bee after hitting the ground

        static bool firstBee = true;
        static float lastLeftPlantX = -boxPixelsX;
        static float lastRightPlantX = resolutionX;

        if (firstBee) {
            firstBee = false;

            // Place initial plants on the left and right
            for (int i = 0; i < maxPlants; i++) {
                if (!plantExists[i]) {
                    plantX[i] = 0;
                    plantY[i] = resolutionY - boxPixelsY - 65;
                    plantExists[i] = true;
                    plantSprites[i].setTexture(plantTexture);
                    plantSprites[i].setPosition(plantX[i], plantY[i]);
                    lastLeftPlantX = plantX[i];
                    break;
                }
            }
            for (int i = 0; i < maxPlants; i++) {
                if (!plantExists[i]) {
                    plantX[i] = resolutionX - boxPixelsX;
                    plantY[i] = resolutionY - boxPixelsY - 65;
                    plantExists[i] = true;
                    plantSprites[i].setTexture(plantTexture);
                    plantSprites[i].setPosition(plantX[i], plantY[i]);
                    lastRightPlantX = plantX[i];
                    break;
                }
            }
        } else {
            // Place plants dynamically
            bool placed = false;
            float newX = Bee_x <= resolutionX / 2 ? lastLeftPlantX + boxPixelsX : lastRightPlantX - boxPixelsX;

            for (int i = 0; i < maxPlants; i++) {
                if (!plantExists[i]) {
                    if (newX < 0) newX = boxPixelsX;
                    if (newX > resolutionX - boxPixelsX) newX = resolutionX - 2 * boxPixelsX;

                    plantX[i] = newX;
                    plantY[i] = resolutionY - boxPixelsY - 65;
                    plantExists[i] = true;
                    plantSprites[i].setTexture(plantTexture);
                    plantSprites[i].setPosition(plantX[i], plantY[i]);

                    if (Bee_x <= resolutionX / 2)
                        lastLeftPlantX = plantX[i];
                    else
                        lastRightPlantX = plantX[i];

                    placed = true;
                    break;
                }
            }

            if (!placed) {
                std::cout << "No more space for new plants!" << std::endl;
            }
        }
    }
}
*/

bool checkCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
    return x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2;
}

// Draw Honeycomb
void drawHoneycomb(RenderWindow& window, float x, float y, Texture& honeycombTexture) {
    Sprite honeycombSprite(honeycombTexture);
    honeycombSprite.setPosition(x, y);
    honeycombSprite.setScale(1.0f, 1.0f);
    window.draw(honeycombSprite);
}
void drawspray1(RenderWindow& window, float& spray1_x, float& spray1_y, Sprite& spraySprite1) {
spraySprite1.setScale(0.8f, 0.8f);
    spraySprite1.setPosition(spray1_x, spray1_y);
    window.draw(spraySprite1);
}

void drawspray2(RenderWindow& window, float& spray2_x, float& spray2_y, Sprite& spraySprite2) {
spraySprite2.setScale(0.8f, 0.8f);
    spraySprite2.setPosition(spray2_x, spray2_y);
    window.draw(spraySprite2);
}
void drawblueBee(RenderWindow& window, float& Bbee_x, float& Bbee_y, Sprite& BbeeSprite) {
BbeeSprite.setScale(0.8f, 0.8f);
    BbeeSprite.setPosition(Bbee_x, Bbee_y);
    window.draw(BbeeSprite);
}


void moveBlueBee(float& Bbee_x, float& Bbee_y, Clock& BbeeClock, float honeycombX[], float honeycombY[], 
                 bool Honeycomb_exists[], const int maxBees, int& score, sf::Text& gametext) {
    
    // Static variables to manage random spawn timing
    static bool isBeeSpawned = false;  // Tracks if the blue bee has been spawned
    static Clock spawnClock;          // Tracks the delay for spawning the bee
    static int spawnDelay = rand() % 5 + 2;  // Random delay between 2 to 6 seconds

    // Check if the blue bee should spawn
    if (!isBeeSpawned) {
        if (spawnClock.getElapsedTime().asSeconds() >= spawnDelay) {
            // Spawn the blue bee at a random location after the delay
            Bbee_x = rand() % (resolutionX - boxPixelsX);
            Bbee_y = rand() % (resolutionY - boxPixelsY);
            isBeeSpawned = true;  // Mark the bee as spawned
        } else {
            return;  // Do nothing until the spawn delay has elapsed
        }
    }

    // Delay to control blue bee movement speed
    if (BbeeClock.getElapsedTime().asMilliseconds() < 15)
        return;  // Delay to control the movement speed

    BbeeClock.restart();  // Reset the clock to track next movement time

    // Add pause logic for collision and honeycomb disappearance
    static bool isPaused = false;  // Flag to track pause state
    static Clock movePauseClock;  // Clock to handle the pause duration
    static bool honeycombCollided = false;  // Track if honeycomb collision has occurred
    static bool isRandomStop = false;  // Flag for random stops
    static Clock randomStopClock;  // Timer for random stops

    // Add a timer for honeycomb removal
    static Clock honeycombRemovalClock;
    static int honeycombToRemoveIndex = -1;  // Index of honeycomb to be removed

    // Handle random stops
    if (isRandomStop) {
        // Stop for a random duration (1-2 seconds)
        if (randomStopClock.getElapsedTime().asSeconds() >= 1 + rand() % 2) {
            isRandomStop = false;  // End the random stop
            randomStopClock.restart();
        } else {
            return;  // Remain stationary during the random stop
        }
    }

    // Randomly decide to stop the bee
    if (!isPaused && rand() % 1000 < 5) {  // Adjust the probability as needed
        isRandomStop = true;
        randomStopClock.restart();  // Start the random stop timer
        return;  // Stop the movement for now
    }

    if (isPaused) {
        // Pause for 3 seconds after collision with honeycomb
        if (movePauseClock.getElapsedTime().asSeconds() >= 3) {
            // After 3 seconds, resume movement
            isPaused = false;
            movePauseClock.restart();  // Reset the pause timer

            if (honeycombToRemoveIndex != -1) {
                // Remove the honeycomb after the delay
                Honeycomb_exists[honeycombToRemoveIndex] = false;
                honeycombToRemoveIndex = -1;  // Reset the index
            }

            if (Bbee_y <= 64)
                score += 1000;  // Update score after honeycomb disappears
            else if (Bbee_y > 64 && Bbee_y <= 256)
                score += 800;
            else
                score += 500;
            gametext.setString("score: " + std::to_string(score));  // Update the score display
        }
        return;  // Bee movement is paused, exit function early
    }

    // Check for collision with honeycomb
    for (int i = 0; i < maxBees; i++) {
        if (Honeycomb_exists[i] && checkCollision(Bbee_x, Bbee_y, boxPixelsX, boxPixelsY, honeycombX[i], honeycombY[i], boxPixelsX, boxPixelsY)) {

            // Stop the blue bee's movement at the collision point
            isPaused = true;  // Pause the movement
            honeycombCollided = true;  // Mark collision as true
            movePauseClock.restart();  // Reset the timer for the pause

            // Mark the honeycomb for removal after delay
            honeycombToRemoveIndex = i;
            honeycombRemovalClock.restart();  // Start the timer for honeycomb removal
            return;  // Stop the function so the bee stays at the collision point
        }
    }

    // If no collision, continue moving the blue bee
    int direction = rand() % 4;  // Random value between 0 and 3 for movement direction
    int speed = rand() % 15 + 5;  // Random speed between 5 and 19 pixels

    switch (direction) {
        case 0: // Move Right
            Bbee_x += speed;
            if (Bbee_x > resolutionX - boxPixelsX) {
                Bbee_x = resolutionX - boxPixelsX;  // Keep inside the screen
            }
            break;
        case 1: // Move Left
            Bbee_x -= speed;
            if (Bbee_x < 0) {
                Bbee_x = 0;  // Keep inside the screen
            }
            break;
        case 2: // Move Down
            Bbee_y += speed;
            if (Bbee_y > resolutionY - boxPixelsY) {
                Bbee_y = resolutionY - boxPixelsY;  // Keep inside the screen
            }
            break;
        case 3: // Move Up
            Bbee_y -= speed;
            if (Bbee_y < 0) {
                Bbee_y = 0;  // Keep inside the screen
            }
            break;
    }

    // Prevent the blue bee from going out of bounds
    if (Bbee_x < 0) 
    Bbee_x = 0;
    if (Bbee_x > resolutionX - boxPixelsX) 
    Bbee_x = resolutionX - boxPixelsX*3;
    if (Bbee_y < 0) 
    Bbee_y = 0;
   if (Bbee_y > resolutionY - boxPixelsY - 70)  // Ground is 64 pixels high
    Bbee_y = resolutionY - boxPixelsY - 70 ;  // Make sure the bee doesn't go below the ground
}

    void drawPlants(RenderWindow& window, float plantX[], float plantY[], bool plantExists[], Sprite plantSprites[], int maxPlants) {
    for (int i = 0; i < maxPlants; i++) {
        if (plantExists[i]) {
            window.draw(plantSprites[i]);
        }
    }
}
bool isPathBlocked(float player_x, float player_y, float next_x, float next_y, 
                      float plantX[], float plantY[], bool plantExists[], int maxPlants) {
    for (int i = 0; i < maxPlants; i++) {
        if (plantExists[i] && checkCollision(next_x, next_y, boxPixelsX, boxPixelsY,
                                             plantX[i], plantY[i], boxPixelsX, boxPixelsY)) {
            return true; // Collision detected
        }
    }
    return false; // No collision
}

// Hive drawing function
void drawHive(RenderWindow& window, float x, float y, Texture& hiveTexture) {
    Sprite hiveSprite(hiveTexture);
    hiveSprite.setPosition(x, y);
    hiveSprite.setScale(1.0f, 1.0f);
    window.draw(hiveSprite);
}

