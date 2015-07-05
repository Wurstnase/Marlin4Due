/*
 * fsr_sensor.cpp
 *
 *  Created on: 05.07.2015
 *      Author: nico
 */

#include "Marlin.h"
#include "fsr_sensor.h"

#define SHORT_SIZE 8
#define LONG_SIZE 16
#define LONG_INTERVAL (2000 / LONG_SIZE)
#define THRESHOLD 0.8

#define FSR_PIN TEMP_1_PIN

millis_t lastLongTime;
uint16_t longSamples[LONG_SIZE];
uint8_t longIndex = 0;
uint16_t longAverage = 0;

uint16_t shortSamples[SHORT_SIZE];
uint8_t averageIndex = 0;

void init_fsr_values()
{
	for (int i = 0; i < SHORT_SIZE; i++)
		shortSamples[i] = 0;

	for (int i = 0; i < LONG_SIZE; i++)
		longSamples[i] = 0;

	lastLongTime = millis();
}

uint16_t UpdateLongSamples(int avg) {
	//
	// If enough time hasn't passed, just return the last value
	//
	millis_t current = millis();
	if (current - lastLongTime <= LONG_INTERVAL)
		return longAverage;

	//
	// Update the log sample with the new value, and then update the long average
	//
	longSamples[longIndex++] = avg;
	if (longIndex >= LONG_SIZE)
		longIndex = 0;

	uint16_t total = 0;
	for (int i = 0; i < LONG_SIZE; i++)
		total += longSamples[i];

	longAverage = total / LONG_SIZE;

	lastLongTime = millis();
	return longAverage;
}

bool CheckIfTriggered() {
	uint16_t total = 0;
	for (int i = 0; i < SHORT_SIZE; i++)
		total += shortSamples[i];

	uint16_t avg = total / SHORT_SIZE;

	uint16_t longAverage = UpdateLongSamples(avg);

	uint16_t threshold = THRESHOLD * longAverage;

	bool triggered = avg < threshold;
	return triggered;
}

bool get_fsr_value() {
	int value = getAdcFreerun(pinToAdcChannel(FSR_PIN), true);

	shortSamples[averageIndex++] = value;
	if (averageIndex >= SHORT_SIZE)
		averageIndex = 0;

	return CheckIfTriggered();
}
