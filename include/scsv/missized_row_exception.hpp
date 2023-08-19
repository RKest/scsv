#pragma once

#include <stdexcept>

namespace scsv
{
    class missized_row_exception : public std::exception
    {
    public:
        missized_row_exception(std::size_t new_expected, std::size_t new_actual) noexcept :
            expected{new_expected},
            actual{new_actual},
            error(std::string{"Expected row containing `"} + std::to_string(expected) +
                  "` fields, but got `" + std::to_string(actual) + "` fields."){};

        [[nodiscard]] auto what() const noexcept -> char const* override { return error.c_str(); }
        [[nodiscard]] auto getExpected() const noexcept -> std::size_t { return expected; }
        [[nodiscard]] auto getActual() const noexcept -> std::size_t { return actual; }

    private:
        std::size_t expected;
        std::size_t actual;
        std::string error;
    };
} // namespace scsv