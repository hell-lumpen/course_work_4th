//
// Created by Maxim on 16.04.2022.
//

#ifndef COURSE_WORK_4TH_TICKET_GENERATOR_H
#define COURSE_WORK_4TH_TICKET_GENERATOR_H

#include <vector>
#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>

#include "ticket.h"
#include "database.h"

class TicketGenerator {
protected:
    static size_t ticketNumber;
    inline static size_t generateTicketNumber() noexcept {return ticketNumber++;}

public:
    Database<RussianLotoTicket> db = Database<RussianLotoTicket>("Y:\\data.bin");

public:
    virtual ~TicketGenerator() = default;
    virtual Ticket* generate_ticket() = 0;
};

size_t TicketGenerator::ticketNumber = 1;


class RussianLotoTicketGenerator : public TicketGenerator {

public:

    inline Ticket* generate_ticket() override {
        auto *ticket = new RussianLotoTicket;
        size_t number = generateTicketNumber();
        ticket->setNumber(number);
        std::vector<uint8_t> already_generated;

        std::default_random_engine defEngine(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> intDistribution(0,8);
        std::uniform_int_distribution<int> intDistribution2(0,9);

        for (int i = 0; i < 6; ++i) {
            int count = 5;

            int count_rand = 0;
            while (count) {
                int index = intDistribution(defEngine);
                count_rand++;
                if ((int)*(ticket->fieldValueArray + index + 9 * i) == 0) {
                    *(ticket->fieldValueArray + index + 9 * i) = generate_value(index,
                                                                                already_generated,
                                                                                defEngine,
                                                                                intDistribution2);
                    count--;
                }
            }
            std::cout << count_rand << std::endl;
        }
        this->db.insert(ticket, number);

        return ticket;
    }

private:
    static __forceinline uint8_t
    generate_value(int index, std::vector<uint8_t> &alreadyGenerated, std::default_random_engine &randomEngine,
                   std::uniform_int_distribution<int> &intDistribution) {

        uint8_t generatedValue = (index + 1) * 10 + intDistribution(randomEngine);
        while (std::find(alreadyGenerated.begin(), alreadyGenerated.end(), generatedValue) != alreadyGenerated.end()) {
            generatedValue = (index + 1) * 10 + intDistribution(randomEngine);
        }
        alreadyGenerated.push_back(generatedValue);
        return generatedValue;
    }
};

#endif //COURSE_WORK_4TH_TICKET_GENERATOR_H
