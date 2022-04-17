//
// Created by Maxim on 16.04.2022.
//

#ifndef COURSE_WORK_4TH_TICKET_GENERATOR_H
#define COURSE_WORK_4TH_TICKET_GENERATOR_H

#pragma once

#include <vector>
#include <iostream>
#include <ctime>
#include <algorithm>

#include "ticket.h"
#include "database.h"

class TicketGenerator {
protected:
    static size_t ticketNumber;
    inline static size_t generateTicketNumber() noexcept {return ticketNumber++;}

public:
    virtual ~TicketGenerator() = default;
    virtual Ticket* generate_ticket() noexcept = 0;
};

size_t TicketGenerator::ticketNumber = 0;


class RussianLotoTicketGenerator : public TicketGenerator {

public:

    inline Ticket* generate_ticket() noexcept override {
        auto *ticket = new RussianLotoTicket;
        ticket->setNumber(generateTicketNumber());
        std::vector<int> already_generated;
        for (int i = 0; i < 6; ++i) {
            int count = 5;

            while (count) {
                int index = rand() % 9;
                if (ticket->ticket_fields[index + 9*i].value == 0) {
                    ticket->ticket_fields[index + 9*i].value = generate_value(index, already_generated);
                    count--;
                }
            }
        }

        return ticket;
    }

private:
    static __forceinline int generate_value(int index, std::vector<int> &alreadyGenerated) {
        int generatedValue = (index + 1) * 10 + rand() % 10;
        while (std::find(alreadyGenerated.begin(), alreadyGenerated.end(), generatedValue) != alreadyGenerated.end()) {
            generatedValue = (index + 1) * 10 + rand() % 10;
        }
        alreadyGenerated.push_back(generatedValue);
        return generatedValue;
    }
};

#endif //COURSE_WORK_4TH_TICKET_GENERATOR_H
