#include <iostream>
#include <list>
#include <chrono>
#include "ticket_generator.h"
#include "my_list.h"

int main() {
    TicketGenerator *generator = new RussianLotoTicketGenerator;

    auto begin = std::chrono::steady_clock::now();

    for (size_t i = 0; i < 10000000; ++i) {
        Ticket *ticket = generator->generate_ticket();
    }

    auto end = std::chrono::steady_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - begin);

    std::cout << "The time: " << elapsed.count() << " s\n";


    return 0;
}
