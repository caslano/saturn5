
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
uYHgoX5H62KN/ViOxxr7sVxFfjKhfjUrCB7qd3SA4KH+M3HkJxPqZ5VJ8FC/o9sJHup3dIjgoX5W38C6PY2ve7brhd9wb0O36dXl83beOavDRYdRDPKdOOdb7m1wxAl6Kf68myxfIT9vSufrEtAel6LzcA7qsP628S38DnHY+b/jgyZehiuLbPTELDahRdFun6A2FfF6z8mU7fFu+WU8VjpMlP1Svh3nTbAjfXLa65EmPGjaVEi6P55Pw39Jj7Q=
*/