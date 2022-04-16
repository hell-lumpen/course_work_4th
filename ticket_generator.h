//
// Created by Maxim on 16.04.2022.
//

#ifndef COURSE_WORK_4TH_TICKET_GENERATOR_H
#define COURSE_WORK_4TH_TICKET_GENERATOR_H

#include <vector>
#include <iostream>
#include <ctime>
#include <algorithm>

struct field {
    int value = 0;
    bool is_met = false; // поле говорит о том, что в результате розыгрыша число встретилось и поле помечено
};


class Ticket {

public:
    field *ticket_fields = nullptr;
    virtual ~Ticket() = default;
    virtual void print_ticket() = 0;

    size_t number = 0;
};


class RussianLotoTicket : public Ticket {
public:
    RussianLotoTicket() {
        ticket_fields = new field[6*9];
    }

    ~RussianLotoTicket() override {
        delete [] ticket_fields;
    }

    void print_ticket() override {
        int count = 0;

        std::cout << "Ticket number: " << number << std::endl;
        for (size_t i = 0; i < 6*9; i++) {
            std::cout << ticket_fields[i].value << "  ";
            count++;
            if (count == 9) {
                std::cout << std::endl;
                count = 0;
            }
        }
        std::cout << std::endl;
    }

public:
    [[nodiscard]] size_t getNumber() const {
        return number;
    }

    void setNumber(size_t number) {
        this->number = number;
    }

};


class TicketGenerator {
protected:
    static size_t ticketNumber;
    static size_t generateTicketNumber() {return ticketNumber++;}

public:
    virtual ~TicketGenerator() = default;
    virtual Ticket* generate_ticket() = 0;
};

size_t TicketGenerator::ticketNumber = 0;


class RussianLotoTicketGenerator : public TicketGenerator {

public:

    Ticket* generate_ticket() override {
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
    int generate_value(int index, std::vector<int> &alreadyGenerated) {
        int generatedValue = (index + 1) * 10 + rand() % 10;
        if (std::find(alreadyGenerated.begin(), alreadyGenerated.end(), generatedValue) == alreadyGenerated.end()) {
            alreadyGenerated.push_back(generatedValue);
            return generatedValue;
        } else
            return generate_value(index, alreadyGenerated);
    }
};

#endif //COURSE_WORK_4TH_TICKET_GENERATOR_H
