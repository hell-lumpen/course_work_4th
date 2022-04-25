//
// Created by Maxim on 17.04.2022.
//

#ifndef COURSE_WORK_4TH_TICKET_H
#define COURSE_WORK_4TH_TICKET_H

#include <iostream>
#include <cstring>

struct Field {
    int value  = 0;
    bool visitFlag = false;
};

class Ticket {
public:
    size_t number = 0;
    unsigned char fieldValueArray[54] {};
    bool fieldVisitArray[54] {};

    virtual ~Ticket() = default;
    virtual void printTicket() = 0;
    virtual bool checkVictory(int lineNumber) = 0;
};


class RussianLotoTicket : public Ticket {
public:
    RussianLotoTicket() {
        memset(fieldValueArray, 0, sizeof(fieldValueArray));
        memset(fieldVisitArray, 0, sizeof(fieldVisitArray));
    };

    ~RussianLotoTicket() override = default;

    inline void printTicket() noexcept override {
        std::cout << "Ticket number: " << number <<std::endl;
        std::cout << "________________________________________________________________" << std::endl;
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (*(fieldValueArray + i*9 + j) == 0)
                    std::cout << "|   0  ";
                else
                    std::cout << "|  " << static_cast<int>(*(fieldValueArray + i*9 + j)) << "  ";
            }
            std::cout << "|" << std::endl;
            for (int j = 0; j < 9; ++j) {
                if (!*(fieldVisitArray + i * 9 + j))
                    std::cout << "|______";
                else
                    std::cout << "|__VV__";
            }
            std::cout << "|" << std::endl;
        }
    }

    bool checkVictory(int lineNumber) override {
        for (int i = (lineNumber - 1) * 9; i < 9 * lineNumber; ++i) {
            if (*(fieldValueArray + i) != 0 && !*(fieldVisitArray + i))
                return false;
        }
        return true;
    }

public:
    void setNumber(size_t number) {
        this->number = number;
    }
};

#endif //COURSE_WORK_4TH_TICKET_H
