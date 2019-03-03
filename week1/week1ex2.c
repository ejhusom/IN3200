#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define bufferSize 1000

void analyzeTemperatureData();
void smooth();

int main(int argc, char const *argv[]) {

  // analyzeTemperatureData();

  return 0;
}

void analyzeTemperatureData(){

  int hour, maxHour, minHour, minute, maxMinute, minMinute;
  float temperature;
  double max = -100000;
  double min = 100000;
  double sum = 0;
  double deltaSum = 0;
  double avg, std;
  int sampleCount = 0;
  char buffer[bufferSize];

  FILE *infile;
  infile = fopen("week1_temperatures.dat","r");
  while (fscanf(infile, "%d:%d  %f\n", &hour, &minute, &temperature) == 3) {

    sampleCount++;
    sum += temperature;

    if (temperature > max){
      max = temperature;
      maxHour = hour;
      maxMinute = minute;
    }
    if (temperature < min){
      min = temperature;
      minHour = hour;
      minMinute = minute;
    }

  }
  fclose(infile);

  avg = sum/sampleCount;


  infile = fopen("week1_temperatures.dat","r");
  while (fscanf(infile, "%d:%d  %f\n", &hour, &minute, &temperature) == 3) {
    deltaSum += (temperature - avg)*(temperature - avg);
  }
  fclose(infile);

  std = sqrt(deltaSum/sampleCount);


  printf("Highest tempearture was %.1f measured at %02d:%02d\n", max, maxHour, maxMinute);
  printf("Lowest tempearture was %.1f measured at %02d:%02d\n", min, minHour, minMinute);
  printf("Average temperature: %f\n", avg);
  printf("Standard deviation: %f\n", std);
}

void smooth(){
  
}
