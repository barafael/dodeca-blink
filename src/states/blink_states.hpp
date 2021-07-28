#include <cstddef>
#include <vector>

#include "dodeca_state.hpp"

class BlinkStateMachine {
    public:
    BlinkStateMachine() = default;

    explicit BlinkStateMachine(DodecaState *initial) {
        if (initial != nullptr) {
            states.push_back(initial);
        }
    }

    DodecaState *get_active_state() const {
        return states[active_index];
    }

    size_t get_active_index() const {
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

    void add_state(DodecaState *state) {
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

    size_t num_states() {
        return states.size();
    }

    std::vector<DodecaState *>::iterator begin() {
        return states.begin();
    }

    std::vector<DodecaState *>::iterator end() {
        return states.end();
    }

    private:
    size_t active_index = 0;

    std::vector<DodecaState *> states;
};
