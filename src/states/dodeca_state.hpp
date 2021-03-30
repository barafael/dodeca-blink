#ifndef DODECA_STATE_HPP
#define DODECA_STATE_HPP

class DodecaState {
    public:
        virtual void advance() = 0;
        virtual bool do_thing(uint8_t id) = 0;
        virtual bool do_thing(uint8_t id, uint8_t* args, size_t count) = 0;
};

#endif // DODECA_STATE_HPP