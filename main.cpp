#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>
//M.Taha
//24i-0584
//Section G

using namespace std;
using namespace sf;

// Initializing Dimensions
const int resolutionX = 960;
const int resolutionY = 640;
const int boxPixelsX = 32;
const int boxPixelsY = 32;
const int gameRows = resolutionX / boxPixelsX; // Total rows on grid
const int gameColumns = resolutionY / boxPixelsY; // Total columns on grid
void movingbee(float& Bee_x, float& Bee_y, bool& beeMovingRight, bool& Bee_exists, sf::Clock& BeeClock, 
             float plantX[], float plantY[], bool plantExists[], int maxPlants, sf::Sprite plantSprites[], sf::Texture& plantTexture, 
             float honeycombX[], float honeycombY[], bool Honeycomb_exists[], const int maxBees, bool preGeneratedHoneycombExists[], 
             float preGeneratedHoneycombX[], float preGeneratedHoneycombY[], int rch,int& lvlend,sf::Text& gametext1);

void drawingfastbee(RenderWindow& window, float& Bfee_x, float& Bfee_y, Sprite& BfeeSprite);
void moveBfee(float& Bfee_x, float& Bfee_y, bool& bfeeMovingRight, bool& Bfee_exists, Clock& BfeeClock,int& lvlend,sf::Text & gametext1);
void drawHoneycombfast(RenderWindow& window, float x, float y, Texture& honeycombTexturefast); 

// Function Declarations
void drawPlayer(RenderWindow& window, float& player_x, float& player_y, Sprite& playerSprite);

void moveBullet(float& bullet_y, bool& bullet_exists, Clock& bulletClock);

void drawBullet(RenderWindow& window, float& bullet_x, float& bullet_y, Sprite& bulletSprite);

void drawBee(RenderWindow& window, float& Bee_x, float& Bee_y, Sprite& BeeSprite);

bool detectCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);

void drawHoneycomb(RenderWindow& window, float x, float y, Texture& honeycombTexture); 

void drawHoneyrandomcomb(RenderWindow& window, float x, float y, Texture& honeycombTexture); 

void drawspray1(RenderWindow& window, float& spray1_x, float& spray1_y, Sprite& spraySprite1);

void drawspray2(RenderWindow& window, float& spray2_x, float& spray2_y, Sprite& spraySprite2);

void drawblueBee(RenderWindow& window, float& Bbee_x, float& Bbee_y, Sprite& BbeeSprite);

void moveBlueBee(float& Bbee_x, float& Bbee_y, Clock& BbeeClock,
                 float honeycombX[], float honeycombY[], bool Honeycomb_exists[],
                 
                 const int maxBees, int& score, sf::Text& gametext, float preGeneratedHoneycombX[],float preGeneratedHoneycombY[],bool preGeneratedHoneycombExists[],int rch);

void drawPlants(RenderWindow& window, float plantX[], float plantY[], bool plantExists[], Sprite plantSprites[], int maxPlants);

bool isPathBlocked(float player_x, float player_y, float moveX, float moveY, float plantX[], float plantY[], bool plantExists[], int maxPlants);


void drawR(RenderWindow& window, float x, float y, Texture& RTexture);

void displayWelcomePage(RenderWindow& window);

int selectionofthelevel(RenderWindow& window, Font& font);
void loadLevel(int level, int& maxBees, Texture& bgTexture, Music& bgMusic);

int GameLevel(RenderWindow& window, int nofhc,int nowb,int nofb,int level);

void appendNameToFile(const string& name);

void appendScoreToFile(const string& name, int score);

void enteringplayername(RenderWindow& window, Font& font, string& playerName) ;

void displayLb(RenderWindow& window, Font& font, string names[], int scores[], int numNames);

void lbfromfile(string names[], int scores[], int& numNames,const int& MAX_LEADERBOARD);


void printscr(RenderWindow& window, Font& font, int score);

int selectionofthelevel(RenderWindow& window, Font& font,const int& MAX_LEADERBOARD);

void displayWelcomePage(RenderWindow& window);




int main() {

    // Create the main window
    RenderWindow window(VideoMode(resolutionX, resolutionY), "Buzz Bombers", Style::Close | Style::Titlebar);

    int score;
    
    const int MAX_LEADERBOARD = 10;
    // Load font
    Font font;
    if (!font.loadFromFile("Font.ttf")) {
        cerr << "Failed to load font!" << endl;
        return -1;
    }

    // Ask for new player name
    string playerName;
    
    
     //window.clear();
    enteringplayername(window, font, playerName);
 displayWelcomePage(window);
 
 
    // Display the welcome page
    Text welcomeText;
    welcomeText.setFont(font);
    welcomeText.setString("Welcome Respected " + playerName + "!");
    welcomeText.setCharacterSize(50);
    welcomeText.setFillColor(Color::Blue);
    welcomeText.setPosition(150, 150);

    window.clear(Color::Black);
    window.draw(welcomeText);
    window.display();

    // Main loop to allow returning to menu
    while (window.isOpen()) {
    
    
        // Level Selection Menu
        int selectedLevel = selectionofthelevel(window, font, MAX_LEADERBOARD );

        // Handle Level Selection
        switch (selectedLevel) {
            case 1:
                score = GameLevel(window, 3, 20, 0, 1);
                break;
            case 2:
                score = GameLevel(window, 9, 15, 5, 2);
                break;
            case 3:
                score = GameLevel(window, 15, 20, 10, 3);
                break;
            case 4:
                break;
        }
        

        // Save the score to leaderboard
        appendScoreToFile(playerName, score);
    }

    return 0;
}



int GameLevel(RenderWindow& window, int nofhc,int nowb, int nofb, int level) {
    Texture bgTexture;

    if(level==1){
    
        bgTexture.loadFromFile("DALL\u00b7E 2024-12-07 20.00.15 - A s.png");
        Music bgMusic1;
    bgMusic1.openFromFile("Music3.ogg");
    bgMusic1.play();
    bgMusic1.setVolume(5);
    }
    else if(level==2){
    
        bgTexture.loadFromFile("background1.png");
        Music bgMusic2;
    bgMusic2.openFromFile("magical_journey.ogg");
    bgMusic2.play();
    bgMusic2.setVolume(5);}
    else if (level==3){
    
        bgTexture.loadFromFile("background3.png");
        Music bgMusic3;
    bgMusic3.openFromFile("risk.ogg");
    bgMusic3.play();
    bgMusic3.setVolume(5);
     }
     
    Sprite bgSprite;
    bgSprite.setTexture(bgTexture);  
 
    	
    int  rch=nofhc;

    // Initialize font
    Font gameFont;
    if (!gameFont.loadFromFile("Font.ttf")) {
        cerr << "Failed to load font!" << endl;
        return -1;
    }

    // Background Music
    Music bgMusic;
    bgMusic.openFromFile("Music3.ogg");
    bgMusic.play();
    bgMusic.setVolume(5);
    
    // Player
    float player_y = (gameColumns-4)*boxPixelsY;
    float player_x = (gameRows-16)*boxPixelsX;
    
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
    
    // random honeycomb
    Texture RTexture;
    Sprite RSprite;
    RTexture.loadFromFile("honeycomb.png");
    RSprite.setTexture(RTexture);
        
    // Define the positions for the pre-generated honeycombs
    float preGeneratedHoneycombX[rch];
    float preGeneratedHoneycombY[rch];
    bool preGeneratedHoneycombExists[rch];
    
    for(int i=0;i<rch;i++){
        preGeneratedHoneycombX[i]=rand()%860;
        preGeneratedHoneycombY[i]=rand()%540;
        preGeneratedHoneycombExists[i]=true;
    }

    // Blue bee
    Texture BbeeTexture;
    Sprite BbeeSprite;
    BbeeTexture.loadFromFile("123.png");
    BbeeSprite.setTexture(BbeeTexture);
    BbeeSprite.setColor(sf::Color::Blue);
        
    bool hummingbirdexist=true;
        
    // plant
    const int maxPlants = 200; // Maximum number of plants allowed
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
    
    float Bbee_x=rand() % (800 - 50); 
    float Bbee_y=rand() % (600 - 50); 
                
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
    const int maxBees = nowb; // Number of bees
    float Bee_x[maxBees];
    float Bee_y[maxBees];
    bool beeMovingRight[maxBees];
    bool Bee_exists[maxBees];
    Clock BeeClock[maxBees];
    bool Honeycomb_exists[maxBees]; // ----

    int score = 0;
    int counter=0;
    
    sf::Font gamefont;
    gamefont.loadFromFile("Arial.ttf");

    sf::Text gametext;
    gametext.setFont(gamefont);
    gametext.setString("score:" + std::to_string(score));
    gametext.setPosition(750,600);
    gametext.setFillColor(sf::Color::Red);
    
    // Initializing bee and honeycomb
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
    
    // Honeycomb Texture
    Texture honeycombTexture;
    honeycombTexture.loadFromFile("honeycomb.png");

    // Honeycomb Positions
    float honeycombX[maxBees], honeycombY[maxBees];
    
        
    // Initialize fast bees
    // Fast Bee Initialization
    Texture BfeeTexture;
    Sprite BfeeSprite;
    BfeeTexture.loadFromFile("Fast_bee.png");
    BfeeSprite.setTexture(BfeeTexture);
    
    // Bee Properties
    const int maxBfees = nofb; // Number of fast bees
    float Bfee_x[maxBfees];
    float Bfee_y[maxBfees];
    bool bfeeMovingRight[maxBfees];
    bool Bfee_exists[maxBfees];
    Clock BfeeClock[maxBfees];
    
    int lvlend=maxBees+maxBfees;
    
    sf::Text gametext1;
    gametext1.setFont(gamefont);
    gametext1.setString(" level:" + std::to_string(lvlend));
    gametext1.setPosition(550,600);
    gametext1.setFillColor(sf::Color::Red);
    
    
    sf::Text displaylvl;
    displaylvl.setFont(gamefont);
    displaylvl.setString(" You are playing level:" + std::to_string(level));
    displaylvl.setPosition(150,600);
    displaylvl.setFillColor(sf::Color::Red);
    
    
    
    for (int i = 0; i < maxBfees; i++) {
        Bfee_x[i] = rand() % (resolutionX - boxPixelsX); // Random horizontal position
        Bfee_y[i] = -(i * 100);                         // Staggered vertical positions
        bfeeMovingRight[i] = rand() % 2;                // Random initial direction
        Bfee_exists[i] = true;                          // All bees start active
    }
    
    // Honeycomb Texture for fast bees
    Texture honeycombTexturefast;
    honeycombTexturefast.loadFromFile("honeycomb_red.png");
    bool Honeycombfast_exists[maxBfees];
         
    for(int i=0;i<maxBfees;i++){
        Honeycombfast_exists[i]=false;
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

    // Initialize fast bee positions
    for (int i = 0; i < maxBfees; i++) {
        Bfee_x[i] = rand() % (resolutionX - boxPixelsX); // Random horizontal position
        Bfee_y[i] = -(i * 100);                         // Staggered vertical positions
        bfeeMovingRight[i] = rand() % 2;                // Random initial direction
        Bfee_exists[i] = true;                          // All bees start active
    }
    
    // Initialize plants
    // Already initialized above

    // Game Loop
    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                return 0;
            }
        }
        
        // Player Movement
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            float next_x = player_x - 2;  // Proposed next x position

            // Check if next position is blocked by a plant
            if (player_x > 0 && !isPathBlocked(player_x, player_y, next_x, player_y, plantX, plantY, plantExists, maxPlants)) {
                player_x = next_x;  // Move left if path is clear
            } else {
                // If blocked, find the nearest available position to move left
                while (next_x >= 0 && isPathBlocked(player_x, player_y, next_x, player_y, plantX, plantY, plantExists, maxPlants)) {
                    next_x -= 2;  // Keep moving left until we find an empty space
                }
                // Update player's position if an empty space is found
                if (next_x >= 0) {
                    player_x = next_x;
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            float next_x = player_x + 2;  // Proposed next x position

            // Check if next position is blocked by a plant
            if (player_x < (gameColumns - 1) * boxPixelsX && !isPathBlocked(player_x, player_y, next_x, player_y, plantX, plantY, plantExists, maxPlants)) {
                player_x = next_x;  // Move right if path is clear
            } else {
                // If blocked, find the nearest available position to move right
                while (next_x < resolutionX - boxPixelsX * 2 && isPathBlocked(player_x, player_y, next_x, player_y, plantX, plantY, plantExists, maxPlants)) {
                    next_x += 2;  // Keep moving right until we find an empty space
                }
                // Update player's position if an empty space is found
                if (next_x < resolutionX - boxPixelsX * 2) {
                    player_x = next_x;
                }
            }
        }
        
        // Fast bee code start
        for (int i = 0; i < maxBfees; i++) {
            if (Bfee_exists[i]) {
                moveBfee(Bfee_x[i], Bfee_y[i], bfeeMovingRight[i], Bfee_exists[i], BfeeClock[i], lvlend ,gametext1);

                // Check for collision with bullet
                if (bullet_exists && detectCollision(bullet_x, bullet_y, boxPixelsX, boxPixelsY, Bfee_x[i], Bfee_y[i], boxPixelsX, boxPixelsY)) {
                    Bfee_exists[i] = false; // Deactivate bee
                    bullet_exists = false; // Reset bullet
                    Honeycombfast_exists[i]=true;
                    lvlend--;
                    gametext1.setString("level:" + std::to_string(lvlend));
                    score += 100;
                    gametext.setString("score:" + std::to_string(score));
                }
            }
            else if (Honeycombfast_exists[i]) {
                if (bullet_exists && detectCollision(bullet_x, bullet_y, boxPixelsX, boxPixelsY, Bfee_x[i], Bfee_y[i], boxPixelsX, boxPixelsY)) {
                    Honeycombfast_exists[i] = false;
                }
            }
        }
        // fast bee end
        
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
                
            }
             if (bulletsFired == (112+56))
            canShoot = false; // Disable shooting
        }
        //----------------------------------------------------------------------
        // movingbee(Bee_x[i], Bee_y[i], beeMovingRight[i], Bee_exists[i], BeeClock[i], plantX, plantY, plantExists, maxPlants, plantSprites,plantTexture);
        // Bullet Logic
        
        if (bullet_exists) {
            moveBullet(bullet_y, bullet_exists, bulletClock);
        }

        // Bee Logic and honeycomb logic
        for (int i = 0; i < maxBees; i++) {
            if (Bee_exists[i]) {
             movingbee(Bee_x[i], Bee_y[i], beeMovingRight[i], Bee_exists[i], BeeClock[i], 
                        plantX, plantY, plantExists, maxPlants, plantSprites, plantTexture, 
                        honeycombX, honeycombY, Honeycomb_exists, maxBees, 
                        preGeneratedHoneycombExists, preGeneratedHoneycombX, preGeneratedHoneycombY, rch, lvlend, gametext1); 
                
                // Check for collision with bullet and bee
                if (bullet_exists && detectCollision(bullet_x, bullet_y, boxPixelsX, boxPixelsY, Bee_x[i], Bee_y[i], boxPixelsX, boxPixelsY)) {
                    Bee_exists[i] = false; // Deactivate bee
                    bullet_exists = false; // Reset bullet
                    honeycombX[i] = Bee_x[i];
                    honeycombY[i] = Bee_y[i];
                    Honeycomb_exists[i] = true; // starting 1st honey comb
                    lvlend -= 1;
                    score += 100;
                    gametext.setString("score:" + std::to_string(score));
                    gametext1.setString("level:" + std::to_string(lvlend));
                    
                    // Check if lvlend is zero, and if so, exit the game loop
                    if (lvlend <= 0) {
                        break; // Exit the game loop to return to menu
                    }
                }
            }
            else if (Honeycomb_exists[i]) {
                if (bullet_exists && detectCollision(bullet_x, bullet_y, boxPixelsX, boxPixelsY, Bee_x[i], Bee_y[i], boxPixelsX, boxPixelsY)) {
                    Honeycomb_exists[i] = false;     // Remove honeycomb
                }
            }
        }
        
        // Handle pre-generated honeycombs
        for (int i = 0; i < rch; i++) {
            if (preGeneratedHoneycombExists[i]) {
                // If bullet hits any of the pre-generated honeycombs, deactivate it
                if (bullet_exists && detectCollision(bullet_x, bullet_y, boxPixelsX, boxPixelsY, preGeneratedHoneycombX[i], preGeneratedHoneycombY[i], boxPixelsX, boxPixelsY)) {
                    preGeneratedHoneycombExists[i] = false; // Deactivate honeycomb
                    bullet_exists = false; // Reset bullet
                    score += 100; // Increment score for hitting pre-generated honeycomb
                    gametext.setString("score:" + std::to_string(score));
                }
            }
        }

        
        // hitting blue bee
        if (bullet_exists && detectCollision(bullet_x, bullet_y, boxPixelsX, boxPixelsY, Bbee_x, Bbee_y, boxPixelsX, boxPixelsY)){
            counter++;
        	
            if(counter==3){
                BbeeSprite.setColor(sf::Color::Green);
            }
            	  
            else if (counter==6){
                hummingbirdexist=false;
            }
            	  
            bullet_exists = false; 
        }
        
        
        // Variables to manage bee reappearance
        sf::Clock beeRespawnClock;
        bool beeRespawnNeeded = false;
        const float respawnDelay = 3.0f; // 3 seconds delay before bee reappears
        sf::Clock clock;
        // During collision detection
        if (bullet_exists && detectCollision(bullet_x, bullet_y, boxPixelsX, boxPixelsY, Bbee_x, Bbee_y, boxPixelsX, boxPixelsY)) {
            counter++;

            if (counter == 3) {
                BbeeSprite.setColor(sf::Color::Green);
            } else if (counter == 6) {
                hummingbirdexist = false; // Temporarily remove the bee
                beeRespawnNeeded = true; // Set flag for respawn
                beeRespawnClock.restart(); // Start the clock for respawn timer
            }

            bullet_exists = false;
        }


// Handle the respawn of the blue bee after 10 seconds
if (!hummingbirdexist && clock.getElapsedTime().asSeconds() > 10) {
    hummingbirdexist = true;  // Make the blue bee visible again
  
}

        // Handle bee reappearance in the game loop
        if (beeRespawnNeeded && beeRespawnClock.getElapsedTime().asSeconds() >= respawnDelay) {
            hummingbirdexist = true;   // Make the bee appear again
              beeRespawnNeeded = false; // Reset the respawn flag
        }
        
        // Draw
        window.clear();
         
        window.draw(bgSprite);
        window.draw(groundRectangle);

        // Display Battery Visualization
        window.draw(batteryOutline);
        window.draw(batteryLevel);
        
        // Draw pre-generated honeycombs
        for (int i = 0; i < rch; i++) {
            if (preGeneratedHoneycombExists[i]) { 
                drawR(window, preGeneratedHoneycombX[i], preGeneratedHoneycombY[i], RTexture);
            }
        }

        // Draw fast bees
        for (int i = 0; i < maxBfees; i++) {
            if (Bfee_exists[i]) {
                drawingfastbee
            (window, Bfee_x[i], Bfee_y[i], BfeeSprite);
            } else if( Honeycombfast_exists[i]){
                drawHoneycombfast(window, Bfee_x[i], Bfee_y[i], honeycombTexturefast);
            }
        }
        
        // Draw Player
        drawPlayer(window, player_x, player_y, playerSprite);

        // Draw Bullet
        if (bullet_exists) {
            drawBullet(window, bullet_x, bullet_y, bulletSprite);
        }

        // Draw Bees
        for (int i = 0; i < maxBees; i++) {
            if (Bee_exists[i]) {
                drawBee(window, Bee_x[i], Bee_y[i], BeeSprite);
            }
        }

        // Draw Blue Bee
        // drawblueBee(window, Bbee_x, Bbee_y, BbeeSprite);
        // Move the blue bee
        
                
        if(hummingbirdexist){
            moveBlueBee(Bbee_x, Bbee_y, BbeeClock, honeycombX, honeycombY, Honeycomb_exists, maxBees, score, gametext, preGeneratedHoneycombX, preGeneratedHoneycombY, preGeneratedHoneycombExists, rch);
            drawblueBee(window, Bbee_x, Bbee_y, BbeeSprite);
        }

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
       // window.draw(gametext1);
        window.draw(displaylvl);
        
        // Draw plants
        drawPlants(window, plantX, plantY, plantExists, plantSprites, maxPlants);
        window.display();
        
        // After drawing, check if lvlend is zero
        if (lvlend <= 0) {
            // Break out of the game loop to return to menu
            break;
        }
    }
    
    return score;
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




void movingbee(float& Bee_x, float& Bee_y, bool& beeMovingRight, bool& Bee_exists, sf::Clock& BeeClock, 
             float plantX[], float plantY[], bool plantExists[], int maxPlants, sf::Sprite plantSprites[], sf::Texture& plantTexture, 
             float honeycombX[], float honeycombY[], bool Honeycomb_exists[], const int maxBees, bool preGeneratedHoneycombExists[], 
             float preGeneratedHoneycombX[], float preGeneratedHoneycombY[], int rch,int& lvlend,sf::Text& gametext1){

             
    if (BeeClock.getElapsedTime().asMilliseconds() < 4)
        return;

    BeeClock.restart();

    // Check for collision with honeycombs
    for (int i = 0; i < maxBees; i++) {
        if (Honeycomb_exists[i] && detectCollision(Bee_x, Bee_y, boxPixelsX, boxPixelsY, honeycombX[i], honeycombY[i], boxPixelsX, boxPixelsY)) {
            Bee_y += boxPixelsY * 2; // Move down by one step
            beeMovingRight = !beeMovingRight; // Reverse direction
            break; // Handle only the first collision
        }
    }
    
   
     for (int i = 0; i < rch; i++) {
        if( preGeneratedHoneycombExists[i] && detectCollision(Bee_x, Bee_y, boxPixelsX, boxPixelsY,preGeneratedHoneycombX[i], preGeneratedHoneycombY[i] , boxPixelsX, boxPixelsY)){
            Bee_y += boxPixelsY * 2; // Move down by one step
            beeMovingRight = !beeMovingRight; // Reverse direction
            break; // Handle only the first collision
        }
    }
    

    // Move bee left or right
    if (beeMovingRight) {
        Bee_x += 10;
        if (Bee_x >= resolutionX - boxPixelsX) {
            beeMovingRight = false;
            Bee_y += 32;
        }
    } else {
        Bee_x -= 10;
        if (Bee_x <= 0) {
            beeMovingRight = true;
            Bee_y += 32;
        }
    }

    if (Bee_y > resolutionY) {
        Bee_exists = false;
    }

    if (Bee_y > resolutionY - boxPixelsY - 60)   {
     lvlend--;
     gametext1.setString("level:" + std::to_string(lvlend));
     // Check if the bee touches the ground
        Bee_exists = false; // The bee disappears after touching the ground
     ///   Bfee_exits=false; 
        // Static variables to track plant placement
        static bool firstBee = true;
        static float lastLeftPlantX = -boxPixelsX;  // Tracks last plant's X on the left side
        static float lastRightPlantX = resolutionX; // Tracks last plant's X on the right side

        if (firstBee) {
       
            // Place plants for the first bee
            firstBee = false;

            // Place plant on the left side
            for (int i = 0; i < maxPlants; i++) {
                if (!plantExists[i]) {
                    plantX[i] = 0; // Leftmost position
                    plantY[i] = resolutionY - boxPixelsY - 65;
                    plantExists[i] = true;
                    plantSprites[i].setTexture(plantTexture);
                    plantSprites[i].setPosition(plantX[i], plantY[i]);

                    lastLeftPlantX = plantX[i]; // Update left side tracker
                    break;
                }
            }

            // Place plant on the right side
            for (int i = 0; i < maxPlants; i++) {
                if (!plantExists[i]) {
                    plantX[i] = resolutionX - boxPixelsX; // Rightmost position
                    plantY[i] = resolutionY - boxPixelsY - 65;
                    plantExists[i] = true;
                    plantSprites[i].setTexture(plantTexture);
                    plantSprites[i].setPosition(plantX[i], plantY[i]);

                    lastRightPlantX = plantX[i]; // Update right side tracker
                    break;
                }
            }
        } else {
            // Place plants for subsequent bees
            bool placed = false;
            float newX; // Position to place the new plant

            // Determine side and update position dynamically
            bool placeLeft = Bee_x <= resolutionX / 2; // Determine side based on bee's position
            if (placeLeft) {
                newX = lastLeftPlantX + boxPixelsX; // Position the new plant to the right of the last left-side plant
            } else {
                newX = lastRightPlantX - boxPixelsX; // Position the new plant to the left of the last right-side plant
            }

            // Loop to find an empty slot and place the plant
            for (int i = 0; i < maxPlants; i++) {
                if (!plantExists[i]) {
                    // Ensure the new position stays within bounds
                    if (newX < 0) newX = boxPixelsX;
                    if (newX > resolutionX - boxPixelsX) newX = resolutionX - 2 * boxPixelsX;

                    // Place the plant
                    plantX[i] = newX;
                   
                    plantY[i] = resolutionY - boxPixelsY - 65; // Fixed height above the ground
                    plantExists[i] = true;
                    plantSprites[i].setTexture(plantTexture);
                    plantSprites[i].setPosition(plantX[i], plantY[i]);

                    // Update the tracker for the last placed plant
                    if (placeLeft) {
                        lastLeftPlantX = plantX[i];
                    } else {
                        lastRightPlantX = plantX[i];
                    }

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


bool detectCollision(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
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
                 bool Honeycomb_exists[], const int maxBees, int& score, sf::Text& gametext, float preGeneratedHoneycombX[],float preGeneratedHoneycombY[],bool preGeneratedHoneycombExists[],int rch) {
    
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
        if (Honeycomb_exists[i] && detectCollision(Bbee_x, Bbee_y, boxPixelsX, boxPixelsY, honeycombX[i], honeycombY[i], boxPixelsX, boxPixelsY)) {

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


   
  
// Check for collision with random honeycomb
    for (int i = 0; i < rch; i++) {
        if (preGeneratedHoneycombExists[i] && detectCollision(Bbee_x, Bbee_y, boxPixelsX, boxPixelsY, preGeneratedHoneycombX[i], preGeneratedHoneycombY[i], boxPixelsX, boxPixelsY)) {

            // Stop the blue bee's movement at the collision point
            isPaused = true;  // Pause the movement
            honeycombCollided = true;  // Mark collision as true
            movePauseClock.restart();  // Reset the timer for the pause

            // Mark the honeycomb for removal after delay
            preGeneratedHoneycombExists[i]=false;
            //honeycombToRemoveIndex = i;
           
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
        if (plantExists[i] && detectCollision(next_x, next_y, boxPixelsX, boxPixelsY,
                                             plantX[i], plantY[i], boxPixelsX, boxPixelsY)) {
            return true; // Collision detected
        }
    }
    return false; // No collision
}
void drawHoneyrandomcomb(RenderWindow& window, float x, float y, Texture& honeycombTexture) {
    Sprite honeycombSprite(honeycombTexture);
    honeycombSprite.setPosition(x, y);
    honeycombSprite.setScale(1.0f, 1.0f);
    window.draw(honeycombSprite);
}

void drawR(RenderWindow& window, float x, float y, Texture& RTexture){
Sprite RSprite(RTexture);
    RSprite.setPosition(x, y);
    RSprite.setScale(1.0f, 1.0f);
    window.draw(RSprite);}
  

void displayWelcomePage(RenderWindow& window) {
    // Load the welcome image
    Texture welcomeTexture;
    if (!welcomeTexture.loadFromFile("welcomeimage.png")) {
        std::cerr << "Failed to load welcome image!" << std::endl;
        return;
    }
    Sprite welcomeSprite(welcomeTexture);
   
   
    // Display welcome page
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                return;
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
                return;  // Proceed to the menu if Enter is pressed
            }
        }

        window.clear();
        window.draw(welcomeSprite);  // Draw the welcome image
        window.display();
    }
}


void drawingfastbee(RenderWindow& window, float& Bfee_x, float& Bfee_y, Sprite& BeeSpritefast) {
    BeeSpritefast.setPosition(Bfee_x, Bfee_y);
    window.draw(BeeSpritefast);
}

void moveBfee(float& Bfee_x, float& Bfee_y, bool& bfeeMovingRight, bool& Bfee_exists, Clock& BfeeClock,int& lvlend,sf::Text & gametext1) {
    if (BfeeClock.getElapsedTime().asMilliseconds() < 5)
        return;

    BfeeClock.restart();

    if (bfeeMovingRight) {
        Bfee_x += 10;
        if (Bfee_x >= resolutionX - boxPixelsX) {
            bfeeMovingRight = false;
            Bfee_y += 32;
        }
    } else {
        Bfee_x -= 10;
        if (Bfee_x <= 0) {
            bfeeMovingRight = true;
            Bfee_y += 32;
        }
    }

    if (Bfee_y > resolutionY-60){
        Bfee_exists = false;
        lvlend--;
        gametext1.setString("score:" + std::to_string(lvlend));
        }
}


// Draw Honeycomb
void drawHoneycombfast(RenderWindow& window, float x, float y, Texture& honeycombTexturefast) {
    Sprite honeycombSpritefast(honeycombTexturefast);
    honeycombSpritefast.setPosition(x, y);
    honeycombSpritefast.setScale(1.0f, 1.0f);
    window.draw(honeycombSpritefast);
}
void appendNameToFile(const string& name) {
    ofstream outputFile("player_name.txt", ios::app); // Open file in append mode
    if (outputFile.is_open()) {
        outputFile << name << endl; // Write the name followed by a newline
        outputFile.close();
    }
}

void appendScoreToFile(const string& name, int score) {
    ofstream outputFile("leaderboard.txt", ios::app); // Open leaderboard file in append mode
    if (outputFile.is_open()) {
        outputFile << name << ":" << score << endl; // Save name and score
        outputFile.close();
    }
}

// Function to get player name
void enteringplayername(RenderWindow& window, Font& font, string& playerName) {
    Text inputText;
    inputText.setFont(font);
    inputText.setCharacterSize(30);
    inputText.setFillColor(Color::White);
    inputText.setPosition(100, 100);

    bool nameEntered = false; // Flag to check if the name is entered

    while (window.isOpen() && !nameEntered) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            // Handle text input
            if (event.type == Event::TextEntered && !nameEntered) {
                if (event.text.unicode == '\b') { // Handle backspace
                    if (!playerName.empty())
                        playerName.pop_back();
                } else if (event.text.unicode == '\r') { // Handle Enter key
                    appendNameToFile(playerName); // Append name when Enter is pressed
                    nameEntered = true; // Mark name as entered
                } else if (event.text.unicode < 128) { // ASCII characters only
                    playerName += static_cast<char>(event.text.unicode);
                }
            }
        }

        // Update the sf::Text object
        inputText.setString("Enter Name: " + playerName);

        // Clear, draw, and display
        window.clear(Color::Black);
        window.draw(inputText);
        window.display();
    }
}

// Function to display the leaderboard
void displayLb(RenderWindow& window, Font& font, string names[], int scores[], int numNames) {
    Text leaderboardTitle;
    leaderboardTitle.setFont(font);
    leaderboardTitle.setString("Leaderboard:");
    leaderboardTitle.setCharacterSize(40);
    leaderboardTitle.setFillColor(Color::White);
    leaderboardTitle.setPosition(100, 50);

    window.clear(Color::Black); // Clear the screen first
    window.draw(leaderboardTitle); // Draw the title

    // Display the names and scores in the leaderboard
    for (int i = 0; i < numNames; i++) {
        Text playerNameText;
        playerNameText.setFont(font);
        playerNameText.setString(names[i] + ": " + to_string(scores[i]));
        playerNameText.setCharacterSize(30);
        playerNameText.setFillColor(Color::White);
        playerNameText.setPosition(100, 100 + (i * 40)); // Adjust the position for each player
        window.draw(playerNameText);
    }

    
    Text returnMessage;
    returnMessage.setFont(font);
    returnMessage.setString("Press Enter to return to the menu");
    returnMessage.setCharacterSize(30);
    returnMessage.setFillColor(Color::White);
    returnMessage.setPosition(100, 100 + (numNames * 40) + 40); // Place it below the leaderboard

    window.draw(returnMessage); // Draw the return message

    window.display(); // Display everything

    
    bool waitingForInput = true;
    while (waitingForInput) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                return;
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Enter) {
                    waitingForInput = false; // Exit the loop and go back to the menu
                }
            }
        }
    }
}
// Function to load all names and scores from the file into arrays
void lbfromfile(string names[], int scores[], int& numNames,const int& MAX_LEADERBOARD) {
    ifstream inputFile("leaderboard.txt");
    numNames = 0;
    string line;
    
    // Read names and scores from the file and store them in the arrays
    while (getline(inputFile, line) && numNames < MAX_LEADERBOARD) {
        size_t separator = line.find(':');
        if (separator != string::npos) {
            names[numNames] = line.substr(0, separator);
            scores[numNames] = stoi(line.substr(separator + 1));
            numNames++;
        }
    }
}

// Function to display the score
void printscr(RenderWindow& window, Font& font, int score) {
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: " + to_string(score)); // Convert score to string
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 10); // Set the position at the top-left corner of the screen

    window.draw(scoreText); // Draw the score text
}

// Level selection menu with leaderboard option
int selectionofthelevel(RenderWindow& window, Font& font,const int& MAX_LEADERBOARD) {
    const char* levels[] = {"Play Level 1", "Play Level 2", "Play Level 3", "Leaderboard", "Exit"};
    const int numLevels = 5;
    Text levelTexts[numLevels];

    // Set up the text for the levels
    for (int i = 0; i < numLevels; i++) {
        levelTexts[i].setFont(font);
        levelTexts[i].setString(levels[i]);
        levelTexts[i].setCharacterSize(40);
        levelTexts[i].setFillColor(i == 0 ? Color::Red : Color::White);
        levelTexts[i].setPosition(400, 200 + i * 60); // Adjust position as needed
    }

    int selectedIndex = 0;

    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
            }
            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Up) {
                    levelTexts[selectedIndex].setFillColor(Color::White);
                    selectedIndex = (selectedIndex - 1 + numLevels) % numLevels;
                    levelTexts[selectedIndex].setFillColor(Color::Red);
                } 
                else if 
                
                (e.key.code == Keyboard::Down) {
                    levelTexts[selectedIndex].setFillColor(Color::White);
                    selectedIndex = (selectedIndex + 1) % numLevels;
                    levelTexts[selectedIndex].setFillColor(Color::Red);
                } else if 
                
                (e.key.code == Keyboard::Enter) {
                    if (selectedIndex == 4) { // Exit selected
                        window.close();
                    } else if 
                    
                    (selectedIndex == 3) { // Leaderboard selected
                        string names[MAX_LEADERBOARD];
                        int scores[MAX_LEADERBOARD];
                        int numNames = 0;
                        lbfromfile(names, scores, numNames,MAX_LEADERBOARD);
                        displayLb(window, font, names, scores, numNames);
                    } else
                     {
                        return selectedIndex + 1; // Return the level number selected (1, 2, 3)
                    }
                }
            }
        }

        window.clear(Color::Black); // Clear the window with black color

        // Draw the level text options
        for (int i = 0; i < numLevels; i++) {
            window.draw(levelTexts[i]);
        }

        window.display();
    }

    return 1; // Default to Level 1 if window closes unexpectedly
}



