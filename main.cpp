#include <iostream>
#include <list>
#include <chrono>
#include "ticket_generator.h"
#include "my_list.h"

inline void test(TicketGenerator* generator) {
    auto begin = std::chrono::steady_clock::now();

    for (size_t i = 0; i < 20; ++i) {
        Ticket *ticket = generator->generate_ticket();
        ticket->print_ticket();
    }

    auto end = std::chrono::steady_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::cout << "The time: " << elapsed.count() << " ms\n";
}

int main() {
    TicketGenerator *generator = new RussianLotoTicketGenerator;
    for (int i = 0; i < 5; ++i) {
        test(generator);
    }
    return 0;
}
