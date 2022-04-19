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
    explicit Database(std::string name) : filename(std::move(name)) {}

    __forceinline void insert(TData *data, const size_t index) noexcept {
        stream.open(filename, std::ios::binary | std::ios::out | std::ios::app);
        size_t position = sizeof(TData) * index;
        stream.seekp(position);
        stream.write(reinterpret_cast<char*>(data), sizeof(TData));
        stream.close();
    }

    __forceinline TData* select(const size_t index) noexcept {
        stream.open(filename, std::ios::binary | std::ios::in);
        size_t position = sizeof(TData) * index;
        stream.seekg(position);
        auto* data = new TData();
        stream.read(reinterpret_cast<char*>(data), sizeof(TData));
        stream.close();
        return data;
    }

    __forceinline void update(TData *data, const size_t index) noexcept {
        stream.open(filename, std::ios::binary | std::ios::out);
        size_t position = sizeof(TData) * index;
        stream.seekp(position);
        stream.write(reinterpret_cast<char*>(data), sizeof(TData));
        stream.close();
    }

    __forceinline void drop() const noexcept{
        std::ofstream(this->filename);
    }
};

#endif //COURSE_WORK_4TH_DATABASE_H
