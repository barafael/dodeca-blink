#include <vector>
#include <cstddef>

#include "dodeca_state.hpp"

class BlinkStates {
    public:
        BlinkStates(DodecaState* initial) {
            if (initial != nullptr) {
                states.push_back(initial);
            }
        }

        DodecaState* get_active_state() {
            return states[active_index];
        }

        size_t get_active_index() {
            return active_index;
        }

        void go_to_next() {
            if (active_index == states.size() - 1) {
                active_index = 0;
            } else {
                active_index += 1;
            }
        }

        void go_to_previous() {
            if (active_index == 0) {
                active_index = states.size() - 1;
            } else {
                active_index -= 1;
            }
        }

        void add_state(DodecaState* state) {
            if (state != nullptr) {
                states.push_back(state);
            }
        }

        bool try_set_index(size_t index) {
            if (index < states.size()) {
                active_index = index;
                return true;
            } else {
                return false;
            }
        }

    private:
        size_t active_index = 0;
        std::vector<DodecaState*> states;
};
