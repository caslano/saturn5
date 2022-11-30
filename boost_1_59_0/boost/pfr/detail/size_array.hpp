// Copyright (c) 2016-2022 Antony Polukhin
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PFR_DETAIL_SIZE_ARRAY_HPP
#define BOOST_PFR_DETAIL_SIZE_ARRAY_HPP
#pragma once

#include <boost/pfr/detail/config.hpp>

#include <cstddef>      // metaprogramming stuff

namespace boost { namespace pfr { namespace detail {

///////////////////// Array that has the constexpr
template <std::size_t N>
struct size_array {                         // libc++ misses constexpr on operator[]
    typedef std::size_t type;
    std::size_t data[N];

    static constexpr std::size_t size() noexcept { return N; }

    constexpr std::size_t count_nonzeros() const noexcept {
        std::size_t count = 0;
        for (std::size_t i = 0; i < size(); ++i) {
            if (data[i]) {
                ++ count;
            }
        }
        return count;
    }

    constexpr std::size_t count_from_opening_till_matching_parenthis_seq(std::size_t from, std::size_t opening_parenthis, std::size_t closing_parenthis) const noexcept {
        if (data[from] != opening_parenthis) {
            return 0;
        }
        std::size_t unclosed_parnthesis = 0;
        std::size_t count = 0;
        for (; ; ++from) {
            if (data[from] == opening_parenthis) {
                ++ unclosed_parnthesis;
            } else if (data[from] == closing_parenthis) {
                -- unclosed_parnthesis;
            }
            ++ count;

            if (unclosed_parnthesis == 0) {
                return count;
            }
        }

        return count;
    }
};

template <>
struct size_array<0> {                         // libc++ misses constexpr on operator[]
    typedef std::size_t type;
    std::size_t data[1];

    static constexpr std::size_t size() noexcept { return 0; }

    constexpr std::size_t count_nonzeros() const noexcept {
        return 0;
    }
};

template <std::size_t I, std::size_t N>
constexpr std::size_t get(const size_array<N>& a) noexcept {
    static_assert(I < N, "====================> Boost.PFR: Array index out of bounds");
    return a.data[I];
}



}}} // namespace boost::pfr::detail

#endif // BOOST_PFR_DETAIL_SIZE_ARRAY_HPP

/* size_array.hpp
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
*/