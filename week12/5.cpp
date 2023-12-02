#include <iostream>

template <typename state_t>
struct ListPair final {
    state_t const state;
    ListPair<state_t> *next_state;
};


template <typename state_t>
ListPair<state_t>* copy(ListPair<state_t> const *src) {
    if (!src) {
        return nullptr;
    }

    ListPair<state_t>* new_head = nullptr;
    ListPair<state_t>* current = nullptr;

    try {
        new_head = new ListPair<state_t>{src->state, nullptr};
        current = new_head;
        src = src->next_state;

        while (src) {
            current->next_state = new ListPair<state_t>{src->state, nullptr};
            current = current->next_state;
            src = src->next_state;
        }
    } catch (...) {
        while (new_head) {
            ListPair<state_t>* temp = new_head;
            new_head = new_head->next_state;
            delete temp;
        }
        throw;
    }

    return new_head;
}
