/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** writeBuffer
*/

#pragma once

#include <cstdint>
#include <string>
#include <unistd.h>
#include <vector>

class writeBuffer {
private:
    std::vector<uint8_t> _buffer;

public:
    // clang-format off
    class WriteError : public std::exception {
    private:
        const std::string _message;
    public:
        explicit WriteError(const std::string &message): _message(message) {}
        explicit WriteError(const char *const message): _message(message) {}
        virtual ~WriteError() noexcept { }
        const char *what() const noexcept override { return _message.c_str(); }
    };
    // clang-format on

public:
    writeBuffer() = default;
    writeBuffer(uint32_t size);
    ~writeBuffer() = default;

    /***** Function to get info *****/

    auto size(void) -> std::size_t;

    /***** Functions to append new data *****/

    auto write_to_buffer(const void *data, uint32_t size) -> void;

    auto write_to_buffer(const std::vector<uint8_t> &data) -> void;

    auto write_to_buffer(const std::string &data) -> void;


    /***** Functions write the buffer to ... *****/

    auto _write(int fd) -> void;

    auto _write(int fd, const void *data, uint32_t size) -> void;
};