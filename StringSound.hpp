#include <vector>
#include <memory>
#include <random>
#include <chrono>

#include "CircularBuffer.hpp"

#define SAMPLES_PER_SEC 44100
#define ENERGY_DECAY_FACTOR 0.996

unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
std::minstd_rand0 generator(seed);

class StringSound {
    public:
        explicit StringSound(double frequency):
            freq(frequency),
            buffer(new CircularBuffer<sf::Int16>(44100 / frequency)) {}

        explicit StringSound(std::vector<sf::Int16> init):
            buffer(new CircularBuffer<sf::Int16>(init.size())) 
            {
                for(auto i : init) {
                    buffer->enqueue(i);
                }
            }

        StringSound(const StringSound& obj) = delete; // No copy constructor

        void pluck() {
            for(int i = 0; i < (44100 / freq); i++) {
                sf::Int16 val = (generator() % 65535) - 32768;
                buffer->enqueue(val);
            }
        }

        void tick() {
            sf::Int16 temp = buffer->dequeue();
            sf::Int16 newSample = ((temp + buffer->peek()) / 2) * ENERGY_DECAY_FACTOR;
            buffer->enqueue(newSample);
            count++;
        }

        sf::Int16 sample() const {
            return buffer->peek();
        }

        size_t time() const {
            return count;
        }

    private:
        int count = 0;
        int freq;
        std::shared_ptr<CircularBuffer<sf::Int16>> buffer;
};
