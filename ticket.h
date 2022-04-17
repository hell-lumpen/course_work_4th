//
// Created by Maxim on 17.04.2022.
//

#ifndef COURSE_WORK_4TH_TICKET_H
#define COURSE_WORK_4TH_TICKET_H

#include <iostream>

struct field {
    int   value  = 0;
    bool  is_met = false;
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
        ticket_fields = new field[54];
    }

    ~RussianLotoTicket() override {
        delete [] ticket_fields;
    }

    inline void print_ticket() noexcept override {
        int count = 0;

        std::cout << "Ticket number: " << number << std::endl;
        for (int i = 0; i < 54; i++) {
            std::cout << (ticket_fields + i)->value << "  ";
            count++;
            if (count == 9) {
                std::cout << std::endl;
                count = 0;
            }
        }
        std::cout << std::endl;
    }

public:
    void setNumber(size_t number) {
        this->number = number;
    }
};

#endif //COURSE_WORK_4TH_TICKET_H
