/*
  Copyright 2015 Fred Martin, 
  Y. Rykalova, 2020
  J. Daly 2022
*/

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include <math.h>
#include <limits.h>

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>

#include "CircularBuffer.hpp"
#include "StringSound.hpp"

#define CONCERT_A 220.0
#define SAMPLES_PER_SEC 44100

using namespace std;

vector<sf::Int16> makeSamples(StringSound& gs) {
    std::vector<sf::Int16> samples;

    gs.pluck();
    int duration = 8;  // seconds
    int i;
    for (i= 0; i < SAMPLES_PER_SEC * duration; i++) {
        gs.tick();
        samples.push_back(gs.sample());
    }

    return samples;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(300, 200), "SFML Plucked String Sound Lite");
    sf::Event event;
    double freq;
    vector<sf::Int16> samples;

    freq = CONCERT_A;
    StringSound gs1(freq);
    sf::Sound sound1;
    sf::SoundBuffer buf1;
    samples = makeSamples(gs1);
    cout << samples.size() << endl;
    if (!buf1.loadFromSamples(&samples[0], samples.size(), 2, SAMPLES_PER_SEC))
        throw std::runtime_error("sf::SoundBuffer: failed to load from samples.");
    sound1.setBuffer(buf1);

    // Test
    for(auto x : samples) {
        cout << x << " ";
    }

    freq = CONCERT_A * pow(2, 3.0/12.0);
    StringSound gs2(freq);
    sf::Sound sound2;
    sf::SoundBuffer buf2;
    samples = makeSamples(gs2);
    cout << samples.size() << endl;
    if (!buf2.loadFromSamples(&samples[0], samples.size(), 2, SAMPLES_PER_SEC))
        throw std::runtime_error("sf::SoundBuffer: failed to load from samples.");
    sound2.setBuffer(buf2);

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::A:
                    sound1.play();
                    cout << "A" << endl;
                    break;
                case sf::Keyboard::C:
                    sound2.play();
                    cout << "C" << endl;
                    break;
                default:
                    break;
                }

            default:
                break;
            }

            window.clear();
            window.display();
        }
    }
    return 0;
}
