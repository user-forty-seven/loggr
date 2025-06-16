#pragma once

#include "misc/color.hpp"

#include <exception>
#include <string>

namespace errors {
    struct LoggrError : public std::exception {
        std::string message;

        explicit LoggrError (const std::string& msg) : message(msg) {} // the explicit keyword prevents cpp from accidently converting string to `LoggrError`

        const char* what() const noexcept override {
            return message.c_str();
        }

        virtual std::string full_message() const { // virtual keyword allows child structs to ovveride it, ig?
            return message;
        }
        
        virtual ~LoggrError() = default;
    };

    struct ParseError : public LoggrError {
        std::string expected;
        std::string extra;

        ParseError (const std::string& msg, const std::string& expected_hint = "", const std::string& extra_stuff="") : LoggrError(std::string(color::RED) + "[PARSE ERROR]: " + color::RESET + msg), expected(expected_hint), extra(extra_stuff) {}

        std::string full_message() const override {
            if (expected.empty()) {
                return extra.empty() ? message : (message + "\n" + extra);
            }
            else {
                return extra.empty() ?  message + "\n" + color::YELLOW + "[EXPECTED]: " + color::RESET + expected : message + "\n" + color::YELLOW + "[EXPECTED]: " + color::RESET + expected + "\n" + color::GREEN + extra + color::RESET;
            }
        }
    };
    
    struct CommandError : public LoggrError {
        CommandError (const std::string& msg) : LoggrError(std::string(color::RED) + "[COMMAND ERROR]: " + color::RESET + msg) {}
    };

    struct TaskError : public LoggrError {
        TaskError (const std::string& msg) : LoggrError(std::string(color::RED) + "[TASK ERROR]: " + color::RESET + msg) {}
    };

    struct DataError : public LoggrError {
        std::string filepath;
        DataError (const std::string& msg, const std::string& path = "") : LoggrError(std::string(color::RED) + "[DATA ERROR]: " + color::RESET + msg), filepath(path) {}

        std::string full_message() const override {
            return filepath.empty() ? message : message + "\nFile: " + filepath;
        }
    };

    struct ConfirmationError : public LoggrError {
    ConfirmationError(const std::string& msg) : LoggrError(std::string(color::RED) + "[CONFIRMATION ERROR]: " + color::RESET + msg) {} 
    };
}
