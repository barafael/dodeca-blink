#pragma once

class DodecaState {
    public:
        explicit DodecaState(String name): name(name) {}

        virtual void advance() = 0;
        virtual bool do_thing(uint8_t id) = 0;
        virtual bool do_thing(uint8_t id, uint8_t* args, size_t count) = 0;

        String* get_name() {
            return &name;
        }

        virtual ~DodecaState() = default;

    private:
        String name;
};
