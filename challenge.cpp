#include <iostream>
#include <fstream>
#include <math.h>
#include "wav.hpp"

using namespace std;

int getLineCount(string fileName);
float interp(float a, float b, float t);

int main(){
    WavSound sound1; // helper

    string fileName = "score1.txt";

    ifstream scoreSheet;
    scoreSheet.open(fileName);

    if(!scoreSheet)
        cout<<"Couldn't load score sheet."<<endl;

    int noteCount = getLineCount(fileName);
    float notes[noteCount];

	// put each line into a float array
    float a;
    int i = 0;
    while(scoreSheet >> a) {
        notes[i] = a;
        i++;
    }

    scoreSheet.close();



    int sample_rate = 41400; // samples per second
    float note_duration = .5; // length of each note in seconds
    float dt = 1/(float)sample_rate; // time between samples
    int n_samples = sample_rate * note_duration * noteCount; // total number of samples

    int* waveform = new int[n_samples]; // creates the array

	for (int j = 0; j < noteCount; ++j) {
		for (int i = 0; i < n_samples/noteCount; ++i) {
			float t = dt * i;	// time passed through entire audio track
			float f = notes[j];	// get freq. from note score sheet
			
			float amp = 5000;
			
			
			
			amp *= pow(-(2.0*(t/noteCount)-1.0), 2)+1;
			
			/*if (t <= 0.3) {
				amp *= interp(0, .75, t);
			}
			else if (t <= 0.6) {
				amp *= interp(0.75, .55, t);
			}
			else if (t <= 0.8) {
				amp *= .55;
			}
			else {
				amp *= interp(.55, 0, t);
			}*/
			
			waveform[i*j] = amp*sin(2*M_PI*f*t);
		}
	}
    

    // generates sound file from waveform array, writes n_samples numbers
    // into sound wav file
    // should know sample_rate for sound timing
    sound1.MakeWavFromInt("challenge.wav", sample_rate, waveform, n_samples);
    delete(waveform);
    return 0;
}


/* Modified answer from Stack Overflow.
 * https://stackoverflow.com/questions/3482064/counting-the-number-of-lines-in-a-text-file
 */
int getLineCount(string fileName) {
    int number_of_lines = 0;
    string line;
    ifstream file(fileName);
    while (getline(file, line))
        ++number_of_lines;
    file.close();
    return number_of_lines;
}

float interp(float a, float b, float t) {
    return a + t*(b-a);
}
