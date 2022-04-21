#include <iostream>
#include <list>
#include <chrono>
#include "ticket_generator.h"
#include "my_list.h"

inline void test(TicketGenerator* generator) {
    auto begin = std::chrono::steady_clock::now();

    for (size_t i = 0; i < 1'000'000; ++i) {
        Ticket *ticket = generator->generate_ticket();
        delete ticket;
//        ticket->printTicket();
    }

    auto end = std::chrono::steady_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::cout << "The time: " << elapsed.count() << " ms\n";
}

int main() {
    TicketGenerator *generator = new RussianLotoTicketGenerator;
    generator->db.drop();
    generator->db.openDatabaseForInsert();

    std::cout << "Creating 100'000 tickets" << std::endl;
    for (int i = 0; i < 10; ++i) {
        test(generator);
    }
    generator->db.closeDatabase();

    system("pause");

    return 0;
}
