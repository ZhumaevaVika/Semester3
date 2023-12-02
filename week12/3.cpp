enum class CellState {A, B, C, D};

template<typename state_t>
struct ListPair final {
    state_t const state;
    ListPair<state_t> *next_state;
};

template <typename state_t>
ListPair<state_t>* make_list_from_arguments(state_t state) {
    ListPair<state_t> *head = new ListPair<state_t>{state, nullptr};
    return head;
}

template <typename state_t, typename... Args>
ListPair<state_t>* make_list_from_arguments(state_t state, Args... states) {
    ListPair<state_t> *head = make_list_from_arguments(states...);
    head = push_list(head, state);
    return head;
}



int main(){
    auto state_list = make_list_from_arguments<CellState>(CellState::A, CellState::B, CellState::C, CellState::D);
}