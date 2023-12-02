#include <memory>
template <typename state_t>
struct ListPair final {
    explicit ListPair(state_t state): ListPair(state, std::unique_ptr<ListPair<state_t>>()) { }
    ListPair(state_t state, std::unique_ptr<ListPair<state_t>> &&next): state(state), next_state(std::move(next)) { }

    state_t const state;
    std::unique_ptr<ListPair<state_t>> next_state;
};

template <typename state_t>
std::unique_ptr<ListPair<state_t>> push_list(state_t state) { // создаёт список из одного элемента
    return std::make_unique<ListPair<state_t>>(state);
}

template <typename state_t>
std::unique_ptr<ListPair<state_t>> push_list(state_t state, std::unique_ptr<ListPair<state_t>> tail) { // добавляет новый элемент перед списком tail, передавая владение хвостом списка новой голове списка
    return std::make_unique<ListPair<state_t>>(state, std::move(tail));
}

template <typename state_t>
std::unique_ptr<ListPair<state_t>> reverse_list(std::unique_ptr<ListPair<state_t>> original) {
    std::unique_ptr<ListPair<state_t>> prev = nullptr;
    std::unique_ptr<ListPair<state_t>> current = std::move(original);
    std::unique_ptr<ListPair<state_t>> next = nullptr;

    while (current) {
        next = std::move(current->next_state);
        current->next_state = std::move(prev);
        prev = std::move(current);
        current = std::move(next);
    }

    return prev;
}

enum class ABCellState {A, B};
#include <cassert>
int main() {
    auto list = push_list(ABCellState::A, push_list(ABCellState::B)); // создаёт новый список {ABCellState::A, ABCellState::B}
    auto first_state_ptr = list.get();
    auto second_state_ptr = list->next_state.get();
    assert(ABCellState::A == first_state_ptr->state);
    assert(ABCellState::B == second_state_ptr->state);
    // обычные указатели сохраняют адреса элементов в памяти

    auto reversed_list = reverse_list(std::move(list)); // перенаправляет ссылки в списке {ABCellState::B, ABCellState::A}, функция забирает владение списком
    assert(!list); // владение списком было передано в функцию reverse_list, теперь переменная list не владеет списком
    assert(reversed_list); // новый владелец списка - переменная reversed_list

    assert(ABCellState::A == first_state_ptr->state);
    assert(ABCellState::B == second_state_ptr->state);
    // положение элементов в памяти не меняется, и указатели ссылаются на те же самые данные

    // нет необходимости вызывать функции вида 'delete_list', память списка будет автоматически возвращена в систему, как только переменная reversed_list выйдет из области видимости
    return 0;
}
