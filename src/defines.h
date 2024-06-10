//------------ COLOR Defines ------------//
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF
//------------ Random Variables ------------//
bool True = true;
bool False = false;
//------------ ESP-8-BIT Variables ------------//
  // Create an instance of the graphics library
ESP_8_BIT_GFX* display = nullptr;
uint16_t text_width_half;
uint16_t text_height_half;
String word_vomit = "In the vast expanse where the sky meets the sea, a battle unfolds with the winds wild and free, airships of steel, majestic and grand, engage in a dance, a duel, hand to hand, their engines roar with a thunderous might, propelling them forward into the fight, cannons ablaze, firing with precision, a symphony of destruction, a daring decision, the captains command with a steadfast resolve, their crews follow bravely, each one absolve, of fear and doubt, as they fight for their cause, their hearts beat as one, obeying the laws, of the sky, where the strong rule supreme, where dreams take flight, and realities gleam, but amidst the chaos, a beauty unfolds, as the airships maneuver, their stories untold, against the canvas of clouds, they dance and they sway, a ballet of warfare, in the light of the day, the sun sets ablaze, painting the sky, with hues of orange, pink, and gold, up high, and as the battle reaches its crescendo, one airship falters, its fate now innuendo, it spirals down, a flaming descent, a tragic end to a valiant intent, but the victor knows, the price they must pay, for in war, there are no winners, just a delay, of peace and harmony, a fleeting reprieve, until once again, the airships will heave, into the sky, for another bout, where courage and honor are never in doubt, and so, the airship battle rages on, a testament to the sky, where dreams are born.";
//-------------------- Text Drawing and Mirroring Variables --------------------------//
const int MAX_LINES = 50;  // Maximum number of lines to store
String lines[MAX_LINES];   // Array to store lines of text
int lineCount = 0;         // Number of lines stored
//------------ ANCS Library Variabels  ------------//
// Create an interface to the BLE notification library
BLENotifications notifications;
// Holds the incoming call's ID number, or zero if no notification
uint32_t incomingCallNotificationUUID;
// Device name (What shows up in BLE menu)
const char* device_name = "SigmaSpecula";