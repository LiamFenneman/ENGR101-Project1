#include <iostream>
#include <math.h>
#include "wav.hpp"

using namespace std;

int main(){
    WavSound sound1; // helper

    int sample_rate = 41400; // samples per second
    int duration = 4; // duration in seconds
    float dt = 1/(float)sample_rate; // time between samples
    int n_samples = sample_rate * duration; // total number of samples

    int* waveform = new int[n_samples]; // creates the array

    int amp = 5000;

    int n_cycles = 3 * duration;
    int spc = n_samples / n_cycles;

    int tone1_f = 900;
    int tone2_f = 750;
    int f = tone1_f;

    int current_cycle = 0;

    for (int i = 0; i < n_samples; i++) {
        double t = dt * i;

        if (i > spc*current_cycle){
            current_cycle++;
            if (current_cycle % 2)
                f = tone1_f;
            else
                f = tone2_f;
        }

        waveform[i] = amp*sin(2*M_PI*f*t);
    }

    // generates sound file from waveform array, writes n_samples numbers
    // into sound wav file
    // should know sample_rate for sound timing
    sound1.MakeWavFromInt("completion.wav",sample_rate, waveform, n_samples);
    delete(waveform);
    return 0;
}
