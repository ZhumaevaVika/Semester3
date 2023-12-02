#include <iostream>
#include <memory>
#include <cassert>

template <typename state_t>
            struct Cell {
                virtual void flip() = 0;
                virtual state_t current() const = 0;
                virtual ~Cell() { }
};

struct BoolCell final: Cell<bool> {
    BoolCell(bool initial_state): current_state(initial_state) { }

    void flip() override {
        current_state = !current_state;
    }

    bool current() const override {
        return current_state;
    }
private:
    bool current_state;
};

std::ostream& operator<<(std::ostream &os, BoolCell const &cell) {
    return os << cell.current();
}

template <typename state_t>
std::unique_ptr<Cell<state_t>> wrap_into_logger(std::ostream &os, std::unique_ptr<Cell<state_t>> cell);
// TO DO: написать код функции и класса-обёртки

int main() {
    auto wrapped_cell = wrap_into_logger<bool>(std::cout << std::boolalpha, std::make_unique<BoolCell>(true));
    wrapped_cell->flip(); wrapped_cell->flip(); wrapped_cell->flip();
    auto state = wrapped_cell->current();
    assert(false == state);
    return 0;
}


template <typename state_t>
class LoggerCell : public Cell<state_t> {
public:
    LoggerCell(std::ostream& os, std::unique_ptr<Cell<state_t>> cell) : os(os), cell(std::move(cell)) { }

    void flip() override {
        state_t old_state = cell->current();
        cell->flip();
        state_t new_state = cell->current();
        os << "[" << old_state << " > " << new_state << "]";
    }

    state_t current() const override {
        return cell->current();
    }

private:
    std::ostream& os;
    std::unique_ptr<Cell<state_t>> cell;
};

template <typename state_t>
std::unique_ptr<Cell<state_t>> wrap_into_logger(std::ostream &os, std::unique_ptr<Cell<state_t>> cell) {
    return std::make_unique<LoggerCell<state_t>>(os, std::move(cell));
}
