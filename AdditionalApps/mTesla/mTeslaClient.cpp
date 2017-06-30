#include <Arduino.h>
#include "RF12.h"
#include "sha1.h"
#include "TI_aes_128.c"
#include "../common.h"
const byte LED = 9;


const int MAX_MSG_SIZE = 60;

const int MTESLA_HASH_CHAIN_LENGTH = 1000;
const int EPOCH_DELAY_LENGTH = 11042; // tuned to result in 15000ms in total

const byte KEY_LENGTH = 16;
const byte BLOCK_SIZE = 16;

uint8_t MACKey[HASH_LENGTH];

uint8_t keyMessage[MAX_MSG_SIZE];
char dataMessage[MAX_MSG_SIZE];

unsigned char key_copy[BLOCK_SIZE];
unsigned char hash_copy[HASH_LENGTH];
unsigned char ciphertext[BLOCK_SIZE];

// turn the on-board LED on or off
static void led (bool on) {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, on ? 0 : 1); // inverted logic
}

void printHash(uint8_t* hash) {
  int i;
  for (i=0; i < HASH_LENGTH; i++) {
    Serial.print("0123456789abcdef"[hash[i]>>4]);
    Serial.print("0123456789abcdef"[hash[i]&0xf]);
  }
  Serial.println();
}

static void aes128_block(unsigned const char *key, unsigned const char* plainText, unsigned char *ciphertext, byte encDec) {
  memcpy(ciphertext, plainText, BLOCK_SIZE); // prepare plaintext into output buffer as first step
  memcpy(key_copy, key, BLOCK_SIZE);         // create copy as aes_enc_dec will modify key_copy array
  aes_enc_dec(ciphertext, key_copy, encDec);
}
static void aes128_block_encrypt(unsigned const char *key, unsigned const char* plainText, unsigned char *ciphertext) {
  aes128_block(key, plainText, ciphertext, 0);
}
static void aes128_block_decrypt(unsigned const char *key, unsigned const char* plainText, unsigned char *ciphertext) {
  aes128_block(key, plainText, ciphertext, 1);
}


void computeMACKey(int numHashes, const uint8_t* initialSeed, uint8_t* key) {
  // Compute hash chain
  uint8_t hash[HASH_LENGTH];
  memcpy(hash, initialSeed, HASH_LENGTH);
  for (int i = 0; i < numHashes; i++) {
    Sha1.reset();
    Sha1.update(hash, HASH_LENGTH);
    memcpy(hash, Sha1.result(), HASH_LENGTH);
    if (i % 100 == 0) Serial.print(".");
  }
  memcpy(key, hash, HASH_LENGTH);
  Serial.println();
}

void setup() {
  Serial.begin(57600);

  // TODO: initialize radio properly rf12_initialize()
  rf12_initialize(13, FREQUENCY, 123);
  Serial.println("node initialized");
  // Test computation of hash chain
  memset(MACKey, 0, sizeof(MACKey));
  //computeMACKey(999, MACKey, MACKey);
  //Serial.println("MAC key after 999 hashes: ");
  //printHash(MACKey);
  //Serial.println();
}


int epoch = 0;
unsigned long time = 0;

byte saveHdr, saveLen;
word saveCrc;
char saveData[RF12_MAXDATA];



void loop() {
  led(false);
  if(rf12_recvDone()){
    if(rf12_crc == 0){
      saveLen = rf12_len;
      saveCrc = rf12_crc;
      saveHdr = rf12_hdr;
      memcpy(saveData, (const void*) rf12_data, rf12_len);
      rf12_recvDone();

      if(saveData[0] == 'm' && saveData[1] == 's' && saveData[2] == 'g'){
        Serial.println("msg");

        int receivedEpoch;
        memcpy(&receivedEpoch, saveData+3,2);
        Serial.println(receivedEpoch);
        memcpy(dataMessage, saveData + 5,11);
        String msg = String(dataMessage);
        Serial.println(msg);

      } else if(saveData[0] == 'k' && saveData[1] == 'e' && saveData[2] == 'y'){
        Serial.println("key");
        int receivedEpoch;
        memcpy(&receivedEpoch, saveData+3,2);
        Serial.println(receivedEpoch);

        memcpy(key_copy,saveData +5,BLOCK_SIZE);
        memcpy(hash_copy,saveData + 5,HASH_LENGTH);

        printHash(hash_copy);


      } else {
        Serial.println("else");
      }
    }
  }

  // TODO: implement mTesla client

  led(true);
  //delay(10000);
  led(false);
  //delay(5000);

  //epoch++;

  //Serial.print("Time: ");
  //time = millis();
  //Serial.println(time);
}
