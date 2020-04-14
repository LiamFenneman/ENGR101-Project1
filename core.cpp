#include <iostream>
#include <math.h>
#include "wav.hpp"

using namespace std;

int main(){
    WavSound sound1; // helper

    int sample_rate = 41400; // samples per second
    int duration = 3; // duration in seconds
    float dt = 1/(float)sample_rate; // time between samples
    int n_samples = duration / dt; // total number of samples

    int* waveform = new int[n_samples]; // creates the array

    int amp = 5000;
    int f = 800;

    for (int i = 0; i < n_samples; i++) {
        double t = dt * i;
        waveform[i] = amp*sin(2*M_PI*f*t);
    }
    // generates sound file from waveform array, writes n_samples numbers
    // into sound wav file
    // should know sample_rate for sound timing
    sound1.MakeWavFromInt("core.wav", sample_rate, waveform, n_samples);
    delete(waveform);
    return 0;
}
