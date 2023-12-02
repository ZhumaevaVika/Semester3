#include <iostream>

enum class CellState {A, B};

struct Cell {
    virtual void flip() = 0;
    virtual CellState current() const = 0;
    virtual ~Cell() { }
};

class ABLoopCell : public Cell {
private:
    CellState state;

public:
    ABLoopCell(CellState initial_state) : state(initial_state) {}

    void flip() override {
        state = (state == CellState::A) ? CellState::B : CellState::A;
    }

    CellState current() const override {
        return state;
    }
};

class ABDeadCell : public Cell {
private:
    CellState state;

public:
    ABDeadCell(CellState initial_state) : state(initial_state) {}

    void flip() override {
        if (state == CellState::A) {
            state = CellState::B;
        }
    }

    CellState current() const override {
        return state;
    }
};

class BADeadCell : public Cell {
private:
    CellState state;

public:
    BADeadCell(CellState initial_state) : state(initial_state) {}

    void flip() override {
        if (state == CellState::B) {
            state = CellState::A;
        }
    }

    CellState current() const override {
        return state;
    }
};

void bulk_flip(Cell **begin_cells, Cell **end_cells) {
    for (auto it = begin_cells; it != end_cells; ++it)
        (*it)->flip();
}

int main() {
    ABLoopCell cell1(CellState::A);
    ABDeadCell cell2(CellState::B);
    BADeadCell cell3(CellState::A);

    std::cout << "Initial states:" << std::endl;
    std::cout << "cell1: " << static_cast<int>(cell1.current()) << std::endl;
    std::cout << "cell2: " << static_cast<int>(cell2.current()) << std::endl;
    std::cout << "cell3: " << static_cast<int>(cell3.current()) << std::endl;

    Cell *cells[] = {&cell1, &cell2, &cell3};
    bulk_flip(cells, cells + 3);

    std::cout << "\nStates after flipping:" << std::endl;
    std::cout << "cell1: " << static_cast<int>(cell1.current()) << std::endl;
    std::cout << "cell2: " << static_cast<int>(cell2.current()) << std::endl;
    std::cout << "cell3: " << static_cast<int>(cell3.current()) << std::endl;

    return 0;
}
