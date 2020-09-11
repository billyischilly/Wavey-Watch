int smooth(int input) {
  const int numReadings = 10;

  static int readings[numReadings];      // the readings from the analog input
  static int readIndex = 0;              // the index of the current reading
  static int total = 0;                  // the running total
  static int average = 0;                // the average

  total = total - readings[readIndex];
  readings[readIndex] = input;
  total = total + readings[readIndex];
  readIndex++;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  average = total / numReadings;
  return (average);
  delay(1);        // delay in between reads for stability
}
