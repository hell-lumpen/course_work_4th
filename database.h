//
// Created by Maxim on 17.04.2022.
//

#ifndef COURSE_WORK_4TH_DATABASE_H
#define COURSE_WORK_4TH_DATABASE_H

#pragma once

#include <cstdio>
#include <string>
#include <utility>

#include "ticket.h"

class Database {
private:
    std::string filename {};
    FILE *pFile = nullptr;

public:

    explicit Database(std::string database_filename) noexcept : filename(std::move(database_filename)) {}

    void save(const RussianLotoTicket* record, size_t index);

    RussianLotoTicket* findByTicketNumber ();

    void open_file() {
        pFile = fopen(filename.c_str(), "w");
    }

    void close_file() {
        fclose(pFile);
    }
};

void Database::save(const RussianLotoTicket *record, size_t index) {

}

RussianLotoTicket *Database::findByTicketNumber() {
    return nullptr;
}


#endif //COURSE_WORK_4TH_DATABASE_H
