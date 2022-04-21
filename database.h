//
// Created by Maxim on 17.04.2022.
//

#ifndef COURSE_WORK_4TH_DATABASE_H
#define COURSE_WORK_4TH_DATABASE_H

#include <iostream>
#include <fstream>

template<class TData>
class Database {
private:
    std::fstream stream;
    std::string filename;

public:
    explicit Database(std::string name) : filename(std::move(name)) {
        stream.exceptions(std::ios::failbit | std::ios::badbit);
    }

    __forceinline void insert(TData *data, const size_t index) noexcept {
        size_t position = sizeof(TData) * index;
        stream.seekp(position);
        stream.write(reinterpret_cast<char *>(data), sizeof(TData));
    }

    __forceinline TData* select(const size_t index) noexcept {
        TData* data;
        size_t position = sizeof(TData) * index;
        stream.seekg(position);
        data = new TData();
        stream.read(reinterpret_cast<char *>(data), sizeof(TData));
        return data;
    }

    __forceinline void update(TData *data, const size_t index) noexcept {
        size_t position = sizeof(TData) * index;
        stream.seekp(position);
        stream.write(reinterpret_cast<char *>(data), sizeof(TData));
    }

    __forceinline void drop() const noexcept {
        std::ofstream(this->filename);
    }

    __forceinline void openDatabaseForUpdate() noexcept {
        this->stream.open(filename, std::ios::binary | std::ios::out);
    }

    __forceinline void openDatabaseForSelect() noexcept {
        this->stream.open(filename, std::ios::binary | std::ios::in);
    }

    __forceinline void openDatabaseForInsert() noexcept {
        this->stream.open(filename, std::ios::binary | std::ios::out | std::ios::app);
    }

    __forceinline void closeDatabase() noexcept {
        this->stream.close();
    }
};

#endif //COURSE_WORK_4TH_DATABASE_H
