#include "M5Unified.h"

int sound_level = 192;
int mode = 0; // initialize the mode

const String mode_names[5] = {"Exam", "Q Code", "Morse", "Callsign", "CQ Training"};
int wpm = 10;    // wpm
int freq = 1500; // frequency
int dit_length = 1200 / wpm;
int letter_pause_length = 4 * dit_length;
int word_pause_length = 8 * dit_length;
String word_cw = "";

// your callsign
String callsign = "JM8UTW";

// Morse code array
const String morsecode[49][2] = {
    {" ", " "}, {".----.", "'"}, {"-.--.-", ")"}, {"--..--", ","}, {"-....-", "-"}, {".-.-.-", "."}, {"-..-.", "/"}, {"-----", "0"}, {".----", "1"}, {"..---", "2"}, {"...--", "3"}, {"....-", "4"}, {".....", "5"}, {"-....", "6"}, {"--...", "7"}, {"---..", "8"}, {"----.", "9"}, {"---...", ":"}, {"-.-.-.", ";"}, {"..--..", "?"}, {".-", "A"}, {"-...", "B"}, {"-.-.", "C"}, {"-..", "D"}, {".", "E"}, {"..-.", "F"}, {"--.", "G"}, {"....", "H"}, {"..", "I"}, {".---", "J"}, {"-.-", "K"}, {".-..", "L"}, {"--", "M"}, {"-.", "N"}, {"---", "O"}, {".--.", "P"}, {"--.-", "Q"}, {".-.", "R"}, {"...", "S"}, {"-", "T"}, {"..-", "U"}, {"...-", "V"}, {".--", "W"}, {"-..-", "X"}, {"-.--", "Y"}, {"--..", "Z"}, {"..--.-", "_"}, {"........", "backspace"}, {"-.--.", "<kn>"}};

// Q Code array
const String qcode[49][2] = {
    {"QRA", "What is the name of your station?"},
    {"QRG", "Will you tell me my exact frequency?"},
    {"QRH", "Does my frequency vary?"},
    {"QRI", "How is the tone of my transmission?"},
    {"QRJ", "How many voice contacts do you want?"},
    {"QRK", "What is the legibility of my signals?"},
    {"QRL", "Are you busy?"},
    {"QRM", "Is my transmission being interfered with?"},
    {"QRN", "Are you troubled by static?"},
    {"QRO", "Shall I increase power?"},
    {"QRP", "Shall I decrease power?"},
    {"QRQ", "Shall I send faster?"},
    {"QRR", "Are you ready for automatic operation?"},
    {"QRS", "Shall I send more slowly?"},
    {"QRT", "Shall I stop sending?"},
    {"QRU", "Do you have anything for me?"},
    {"QRV", "Are you ready?"},
    {"QRW", "Shall I inform ... that you are calling him on ... kHz?"},
    {"QRX", "When will you call me again?"},
    {"QRY", "What is my turn?"},
    {"QRZ", "Who is calling me?"},
    {"QSA", "What is the strength of my signals?"},
    {"QSB", "Shall I send ... telegrams at a time?"},
    {"QSD", "Is my keying defective?"},
    {"QSG", "Shall I send ... messages at a time?"},
    {"QSK", "Can you hear me between your signals and if so can I break in on your transmission?"},
    {"QSL", "Can you acknowledge receipt?"},
    {"QSM", "Shall I repeat the last message which I sent you?"},
    {"QSN", "Did you hear me?"},
    {"QSO", "Can you communicate with ... direct or by relay?"},
    {"QSP", "Will you relay to ... free of charge?"},
    {"QSQ", "Have you a doctor on board?"},
    {"QSR", "Do you require a doctor?"},
    {"QSS", "What working frequency will you use?"},
    {"QST", "General call preceding a message for all amateurs"},
    {"QSU", "Shall I send or reply on this frequency?"},
    {"QSV", "Shall I send a series of VVV's?"},
    {"QSW", "Will you send on this frequency?"},
    {"QSX", "Will you listen to ... on ... kHz?"},
    {"QSY", "Shall I change to transmission on another frequency?"},
    {"QSZ", "Shall I send each word or group more than once?"},
    {"QTA", "Shall I cancel message number ...?"},
    {"QTB", "Do you agree with my counting of words?"},
    {"QTC", "How many telegrams have you to send?"},
    {"QTE", "What is my true bearing from you?"},
    {"QTH", "What is your position in latitude and longitude (or according to any other indication)?"},
    {"QTR", "What is the correct time?"},
    {"QTX", "Will you keep your station open for further communication with me?"},
    {"QUD", "Have you received the urgency signal sent by ...?"}};

// Exam?
const String exam[12] = {"DENPA3", "CHIYODA", "MUSEN5", "QHT", "QSO", "QSY", "QRZ", "CQ CQ CQ", "DE", "AS", "AR", "VA"};

// Function to insigt the morse code
String morseCode(String input)
{
  String morse = "";
  // Find the Morse code for the input string
  if (input == "")
  {
    return "";
  }
  for (int i = 0; i < input.length(); i++)
  {
    char currentChar = input.charAt(i);

    // Find the Morse code for the current character
    for (int j = 0; j < 48; j++)
    {
      if (morsecode[j][1].charAt(0) == currentChar)
      {
        morse += morsecode[j][0];
        break;
      }
    }
    // Add a space between letters
    if (i < input.length() - 1)
    {
      morse += " ";
    }
  }
  return morse;
};

// Function to play
void playMorseCode(String input)
{
  // Play the Morse code for the input string
  if (input == "")
  {
    return;
  }
  for (int i = 0; i < input.length(); i++)
  {
    char currentChar = input.charAt(i);
    String morse = "";

    // Find the Morse code for the current character
    for (int j = 0; j < 48; j++)
    {
      if (morsecode[j][1].charAt(0) == currentChar)
      {
        morse = morsecode[j][0];
        break;
      }
    }

    // Play the Morse code using the buzzer
    for (int k = 0; k < morse.length(); k++)
    {
      // M5.update();
      char symbol = morse.charAt(k);
      if (symbol == '.')
      {

        M5.Speaker.tone(freq, dit_length);
        delay(dit_length);
        M5.Speaker.stop();
      }
      else if (symbol == '-')
      {
        M5.Speaker.tone(freq, 3 * dit_length);
        delay(3 * dit_length);
        M5.Speaker.stop();
      }

      // Add a pause between symbols
      if (k < morse.length() - 1)
      {
        delay(dit_length);
      }
    }

    // Add a pause between letters
    if (i < input.length() - 1)
    {
      delay(3 * dit_length);
    }
  }

  // Add a pause between words
  delay(7 * dit_length);
};
void setup()
{
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Speaker.setVolume(sound_level);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setRotation(3);

  dit_length = 1200 / wpm;
  letter_pause_length = 4 * dit_length;
  word_pause_length = 8 * dit_length;
}

void loop()
{
  M5.update();
  M5.Lcd.clearDisplay();
  M5.Lcd.setFont(&fonts::Font2);
  M5.Lcd.setCursor(5, 0);
  M5.Lcd.print("Mode: ");
  M5.Lcd.print(mode_names[mode]);
  if (M5.BtnB.wasPressed())
  {
    mode = (mode + 1) % 5;
  }
  if (mode == 0)
  {
    // Exam mode
    if (M5.BtnA.wasPressed())
    {
      int randomIndex = random(0, 12);
      word_cw = exam[randomIndex];
      M5.Lcd.setCursor(5, 20);
      M5.Lcd.setFont(&fonts::Font4);
      M5.Lcd.println(word_cw);
      M5.Lcd.println(morseCode(word_cw));
      playMorseCode(word_cw);
    }
  }
  else if (mode == 1)
  {
    // Q Code mode
    if (M5.BtnA.wasPressed())
    {
      int randomIndex = random(0, 49);
      word_cw = qcode[randomIndex][0];
      M5.Lcd.setCursor(5, 20);
      M5.Lcd.setFont(&fonts::Font4);
      M5.Lcd.println(word_cw);
      M5.Lcd.setCursor(5, 40);
      M5.Lcd.println(morseCode(word_cw));
      M5.Lcd.setFont(&fonts::Font2);
      M5.Lcd.setCursor(5, 55);
      M5.Lcd.println(qcode[randomIndex][1]);
      playMorseCode(word_cw);
    }
  }
  else if (mode == 2)
  {
    // Learning Morse mode
    if (M5.BtnA.wasPressed())
    {
      int randomIndex = random(0, 49);
      word_cw = morsecode[randomIndex][1];
      M5.Lcd.setFont(&fonts::Font4);
      M5.Lcd.setTextSize(2);
      M5.Lcd.setCursor(5, 20);
      M5.Lcd.println(morsecode[randomIndex][0]);
      M5.Lcd.setTextSize(1);
      M5.Lcd.println(word_cw);
      playMorseCode(word_cw);
    }
  }
  else if (mode == 3)
  {
    // Callsign mode
    if (M5.BtnA.wasPressed())
    {
      word_cw = callsign;
      M5.Lcd.setFont(&fonts::Font4);
      M5.Lcd.setCursor(5, 20);
      M5.Lcd.println(word_cw);
      M5.Lcd.println(morseCode(word_cw));
      playMorseCode(word_cw);
    }
  }
  else if (mode == 4)
  {
    // CQ mode
    if (M5.BtnA.wasPressed())
    {
      word_cw = sprintf("%s %s %s %s K", "CQ CQ CQ DE", callsign, callsign, callsign);
      M5.Lcd.setFont(&fonts::Font2);
      M5.Lcd.setCursor(5, 20);
      M5.Lcd.printf("CQ CQ CQ\nDE\n%s\n%s\n%s\nK", callsign, callsign, callsign);
      // M5.Lcd.println(morseCode(word_cw));
      playMorseCode(word_cw);
    }
  }
  delay(300);
};
