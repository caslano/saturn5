
#ifndef BOOST_CONTRACT_DETAIL_ASSERT_HPP_
#define BOOST_CONTRACT_DETAIL_ASSERT_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/exception.hpp>
#include <boost/contract/detail/noop.hpp>
#include <boost/preprocessor/stringize.hpp>

// In detail because used by both ASSERT and CHECK.
// Use ternary operator `?:` and no trailing `;` here to allow `if(...) ASSERT(
// ...); else ...` (won't compile if expands using an if statement instead even
// if wrapped by {}, and else won't compile if expands trailing `;`).
#define BOOST_CONTRACT_DETAIL_ASSERT(cond) \
    /* no if-statement here */ \
    ((cond) ? \
        BOOST_CONTRACT_DETAIL_NOOP \
    : \
        throw boost::contract::assertion_failure( \
                __FILE__, __LINE__, BOOST_PP_STRINGIZE(cond)) \
    ) /* no ; here */

#endif // #include guard


/* assert.hpp
RZ8tzVYOYoefrc3rbKnvZaI8j/D5HNjwKfQNc0Vch3T/2amm/E6jMNr9F7QMBEdw8Ad0VyfozqXjfL3tF31RaaSc94ygOQvs5BRjJ2dL+GTOR/jO5jViF9gOngcylxcH/HYTuzkf0jrZpHWBhJ29yR3UHHbpYDmvgrDyWmV4Xaz9NpYD70PWMLaXRd6lpq/y8zG4T8GHWdu9IiKNR6e4H9gx9A2vhDZaziFwuETbaLGR1WAjVxsbucbYyLdU34yD/ami72uh/Ne474jyv94vE7ZbTffbJt0bTbrfgXRvlHSxnL8rPI8EnjcZnjcbnrcAz5uFJ/qc7xPsKOvvZcxYPwH9vN4fn+ofTCc7cbxYym1EoodWB9i/H8R3yHf0uzWQKmm7f4Btd6beQ4UXH5w5R082NZ/47FsMd+WSXn8E+XGwgwRPfzk/t9dmXVNuXty2It60bEXrGk4WwuJjfiK6nK5ve7LMC2khZL0nYdJHA4f1Lu+7IF/FO0mjNVqu1hXNcXo9fMXixnpqxJsa3Svi9KJ4w0q/nc+BF7l/pn28/Pln5yw87xaefxZdTGNewZuq01jbjYNJ93ReAxXgisFER3Jxpg/wC6crwnenuzvoHetkRzpYo/sJ9xdaBvtp7SvV7HZ48QPCumeFbKepLz24pbF/qI/ftlX4fl6j2zHV51j5SHyjYCGvm6lsldGyuQ09SkPtWRstSSRXLW9dwGUzhrL0SyjP6g9YNl8U3f2ceS5Itg+tW6x3aZTwSN1lnnOiMNJ5a7JjiFc0Q/kfyX3n5Zv6aEluRRdlrdPLwEuZT1uyNzHQ1a9vjjo9Uv66hY2zDSIdcS/Ww/dpG6vHhXwOlbW5b0D61A/g2Efo7H6Yh4T2YaWl9uLu8X7bUFfg/IddPyRHsw7uI2FYkqbIUnwvi+55fDRUL1e0OXy8u5cW+/vS6ngsNPtb8e6Nf/8N9Lj/5DnHHwYV/TxWG377v05llzXpx7luhPmpP3kC5eZ05Zl0ThHC2WSlvOqD4fio9jCoyPqU7Z9ZXulU2jJSEPabnxY++k73bzkfkCTcszLaS9PL633++9TsC5Qj7aOTdd7fgR5KSQ5+akRlkKCmr3oe+REiFr2G3wYXJYN9/B71vAvl+z/WrgS+zqKIf23TtALVNGlKWgqkhyVCLT2SNCkt5m4CaRJzlILC6+vLS/Nokpe+owdaraCIioKKiChaFBEROTwAEeVQERURARERlFNKEaQcSrWos/PNvPd/0y9pivb3e79md2ZnZ2d3Z2fn2509wD7aFalv7OwOtTQwiSBARmZPiMzqRqfZ0d7aUn8qBl+1+dKXTwk9nTNPchtlvCT9sfc0jz06ghqLbNN+UZk8Y2XCZ1FI4fCY48ptJrclcBwexJxzvD97oHEYjpBaDBPTQgiycBw+J3TuGiX2z5SpKAPfX7GLxyGwhm+tw/jRvFIvFdMzSbuXOl2q3Hjgg48neqkkn62QclVyvljf1q+hsR+Gt9KbvWjOG+3Lxff+PPrexzgvD+CvqO1qWxzq6W6qsv4KC0R/xQswzyHuWM4b3y/yGOPzznBWqI+OBNGL2DLPNUbV33CeH4TuMvVH6Sw1DXGc84OxgYGY8CQ8UF4kEVe5cv17sP4xjrMPjDC2dBxNxnEEY64Ax5yOLRgPfFed56t748jLjIkyMyYWylr+CtoqxLsrpWxLijnme9ZyN/x39L+m7X7vIVnH6X/G/Qes65JW+OjvQx+E7uA7pWYPs0/q2Sd8vAF8YHqf2cO6tUTvuRBdTuN5jfHlel4D8WndoHyte7fQ3i20JpZD3ZJWuJXfLim7S8q+BcpieheUDfSpjNKXHMu63MSyFrruf44=
*/